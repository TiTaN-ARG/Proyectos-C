#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Comun/Defs.h"
#include "../Fechas/Fechas.h"

#define ERR_ARCHIVO 1
#define ERR_ARG 0
#define ERR_LINEA_LARGA 0
#define ERR_CANT_CAMPOS 0

#define CANT_PROD_INI 9
#define CANT_MOV_INI 12

#define ARG_PROD 1
#define ARG_MOV 2
#define ARG_TXT 3
#define ARG_TIPO_TXT 4
#define ARG_PROD_TXT_A_BIN 4

#define TAM_LINEA 500

typedef struct
{
     char codigo[31];
     char descripcion[101];
     Fecha ultPrecio;
     float precioUnitario;
     int cantidad;

} Producto;

typedef int (*TxtABin)(char *linea, Producto *prod);

int generarArchivoProd(const char *nombreArchivo);
int generarArchivoMov(const char *nombreArchivo);
int mostrarArchivo();
void mostrarProd(const Producto *prod);
int actualizarArchivo();
int merge(const char *nombreProductos, const char *nombreMovimientos);
int archivoBinATxt(const char *nomArchBin, const char *nomArchTxt, char tipoTxt);
int archivoTxtABin(const char *nomArchTxt, char tipoTxt, const char *nomArchBin);
int txtVaraBin(char *linea, Producto *prod);
int txtFijoABin(char *linea, Producto *prod);
void rTrim(char *cadena);

int main(int argc, char *argv[])
{
     if (argc != 6)
     {
          printf("Cantidad incorrecta de argumentos: %d. Debio pasar 2 argumentos.", argc);
          return ERR_ARG;
     }

     int ret;

     ret = generarArchivoProd(argv[ARG_PROD]);

     if (ret != TODO_OK)
          return ret;

     ret = generarArchivoMov(argv[ARG_MOV]);

     if (ret != TODO_OK)
          return ret;

     puts("Movimientos:");

     ret = mostrarArchivo(argv[ARG_MOV]);

     if (ret != TODO_OK)
          return ret;

     puts("Antes del merge:");

     puts("Productos:");

     ret = mostrarArchivo(argv[ARG_PROD]);

     if (ret != TODO_OK)
          return ret;

     ret = merge(argv[ARG_PROD], argv[ARG_MOV]);

     if (ret != TODO_OK)
          return ret;

     puts("Despues del merge:");

     puts("Productos:");

     ret = mostrarArchivo(argv[ARG_PROD]);

     if (ret != TODO_OK)
          return ret;

     ret = archivoBinATxt(argv[ARG_PROD], argv[ARG_TXT], argv[ARG_TIPO_TXT][0]);

     if (ret != TODO_OK)
          return ret;

     ret = archivoTxtABin(argv[ARG_TXT], argv[ARG_TIPO_TXT][0], argv[ARG_PROD_TXT_A_BIN]);

     puts("Archivo Productos convertido de Txt a Bin:");
     ret = mostrarArchivo(argv[ARG_PROD_TXT_A_BIN]);

     return ret;
}

int generarArchivoProd(const char *nombreArchivo)
{
     FILE *arch = fopen(nombreArchivo, "wb");

     if (!arch)
     {
          printf("El archivo %s no se pudo abrir.\n", nombreArchivo);
          return ERR_ARCHIVO;
     }

     Producto producto[CANT_PROD_INI] =
         {
             {"arandano", "Arandano", {12, 4, 2021}, 70, 60},
             {"banana", "Banana", {1, 9, 2021}, 160, 150},
             {"kiwi", "Kiwi", {2, 2, 2021}, 200, 30},
             {"manz", "Manzana", {3, 5, 2021}, 80, 150},
             {"naran", "Naranja", {4, 3, 2021}, 50, 90},
             {"pera", "Pera", {5, 1, 2021}, 60, 100},
             {"pome", "Pomelo", {6, 8, 2021}, 140, 20},
             {"sandia", "Sandia", {7, 7, 2021}, 100, 40},
             {"uva", "Uva", {8, 9, 2021}, 130, 89},
         };

     fwrite(producto, sizeof(Producto), CANT_PROD_INI, arch);

     fclose(arch);

     return TODO_OK;
}

int generarArchivoMov(const char *nombreArchivo)
{
     FILE *arch = fopen(nombreArchivo, "wb");

     if (!arch)
     {
          printf("El archivo %s no se pudo abrir.\n", nombreArchivo);
          return ERR_ARCHIVO;
     }

     Producto producto[CANT_PROD_INI] =
         {
             {"banana", "Banana", {1, 9, 2021}, 160, 150},
             {"kiwi", "Kiwi", {2, 2, 2021}, 200, 30},
             {"mango", "Mango", {5, 7, 2021}, 100, 30},
             {"mango", "Mango", {7, 7, 2021}, 105, 50},
             {"manz", "Manzana", {5, 5, 2021}, 80, 150},
             {"naran", "Naranja", {5, 3, 2021}, 50, 90},
             {"naran", "Naranja", {6, 3, 2021}, 55, 30},
             {"pera", "Pera", {6, 1, 2021}, 60, 100},
             {"pome", "Pomelo", {7, 8, 2021}, 140, 20},
             {"sandia", "Sandia", {8, 7, 2021}, 100, 40},
             {"zana", "Zanahoria", {8, 9, 2021}, 80, 30},
             {"zana", "Zanahoria", {9, 9, 2021}, 85, 20},
         };

     fwrite(producto, sizeof(Producto), CANT_PROD_INI, arch);

     fclose(arch);

     return TODO_OK;
}

int mostrarArchivo(const char *nombreArchivo)
{
     FILE *arch = fopen(nombreArchivo, "rb");

     if (!arch)
     {
          printf("El archivo %s no se pudo abrir.\n", nombreArchivo);
          return ERR_ARCHIVO;
     }

     Producto prod;

     fread(&prod, sizeof(Producto), 1, arch);
     while (!feof(arch))
     {
          mostrarProd(&prod);
          fread(&prod, sizeof(Producto), 1, arch);
     }

     fclose(arch);

     return TODO_OK;
}

void mostrarProd(const Producto *prod)
{
     printf("[codigo: %s, Descr: %s, Ult. Pre: %d/%d/%d, PreUni: %.2f, Cant: %d]\n", prod->codigo, prod->descripcion, prod->ultPrecio.dia, prod->ultPrecio.mes, prod->ultPrecio.anio, prod->precioUnitario, prod->cantidad);
}

/*
int actualizarArchivo()
{
     FILE *arch = fopen(NOM_ARCH_PROD, "r+b");

     if (!arch)
     {
          printf("El archivo %s no se pudo abrir.\n", NOM_ARCH_PROD);
          return ERR_ARCHIVO;
     }

     Producto prod;

     fread(&prod, sizeof(Producto), 1, arch);
     while (!feof(arch))
     {
          prod.precioUnitario *= 1.10f;
          fseek(arch, -(long)sizeof(Producto), SEEK_CUR);
          fwrite(&prod, sizeof(Producto), 1, arch);
          fseek(arch, 0, SEEK_CUR);
          fread(&prod, sizeof(Producto), 1, arch);
     }

     fclose(arch);

     return TODO_OK;
}
*/
int merge(const char *nombreProductos, const char *nombreMovimientos)
{
     FILE *archProd = fopen(nombreMovimientos, "rb");
     FILE *archMov = fopen(nombreMovimientos, "rb");
     FILE *archTmp = fopen("prod.tmp", "wb");

     if (!archProd || !archMov || !archTmp)
     {
          fclose(archProd);
          fclose(archMov);
          fclose(archTmp);
          return ERR_ARCHIVO;
     }

     Producto prod, mov, prodNue;
     int comp;

     fread(&prod, sizeof(Producto), 1, archProd);
     fread(&prod, sizeof(Producto), 1, archMov);
     while (!feof(archProd) && !feof(archMov))
     {
          comp = strcmp(prod.codigo, mov.codigo);

          if (comp == 0)
          {
               prod.cantidad += mov.cantidad;
               prod.precioUnitario = mov.precioUnitario;
               fread(&prod, sizeof(Producto), 1, archMov);
          }

          if (comp < 0)
          {
               fwrite(&prod, sizeof(Producto), 1, archTmp);
               fread(&prod, sizeof(Producto), 1, archProd);
          }

          if (comp > 0)
          {
               prodNue = mov;
               fread(&prod, sizeof(Producto), 1, archMov);
               while (!feof(archMov) && strcmp(mov.codigo, prodNue.codigo) == 0)
               {
                    prodNue.cantidad += mov.cantidad;
                    prodNue.precioUnitario = mov.precioUnitario;
                    fread(&mov, sizeof(Producto), 1, archMov);
               }

               fwrite(&prodNue, sizeof(Producto), 1, archTmp);
          }
     }

     while (!feof(archProd))
     {
          fwrite(&prod, sizeof(Producto), 1, archTmp);
          fread(&prod, sizeof(Producto), 1, archProd);
     }

     while (!feof(archMov))
     {
          prodNue = mov;
          fread(&prod, sizeof(Producto), 1, archMov);
          while (!feof(archMov) && strcmp(mov.codigo, prodNue.codigo) == 0)
          {
               prodNue.cantidad += mov.cantidad;
               prodNue.precioUnitario = mov.precioUnitario;
               fread(&mov, sizeof(Producto), 1, archMov);
          }

          fwrite(&prodNue, sizeof(Producto), 1, archTmp);
     }

     fclose(archProd);
     fclose(archMov);
     fclose(archTmp);

     remove(nombreProductos);
     rename("prod.tmp", nombreProductos);

     return TODO_OK;
}

int archivoBinATxt(const char *nomArchBin, const char *nomArchTxt, char tipoTxt)
{
     FILE *archBin = fopen(nomArchBin, "rb");

     if (!archBin)
     {
          printf("El archivo %s no se pudo abrir.\n", nomArchBin);
          return ERR_ARCHIVO;
     }

     FILE *archTxt = fopen(nomArchTxt, "wt");

     if (!archTxt)
     {
          printf("El archivo %s no se pudo abrir.\n", nomArchTxt);
          return ERR_ARCHIVO;
     }

     Producto prod;

     const char *formato = toupper(tipoTxt) == 'V' ? "%s|%s|%d|%d|%d|%.2f|%d\n" : "%-30s%-100s%02d%02d%04d%07.2f%04d\n";

     fread(&prod, sizeof(Producto), 1, archBin);
     while (!feof(archBin))
     {
          fprintf(archTxt, formato, prod.codigo, prod.descripcion, prod.ultPrecio.dia, prod.ultPrecio.mes, prod.ultPrecio.anio, prod.precioUnitario, prod.cantidad);

          fread(&prod, sizeof(Producto), 1, archBin);
     }

     fclose(archBin);
     fclose(archTxt);

     return TODO_OK;
}

int archivoTxtABin(const char *nomArchTxt, char tipoTxt, const char *nomArchBin)
{
     FILE *archBin = fopen(nomArchBin, "wb");

     if (!archBin)
     {
          printf("El archivo %s no se pudo abrir.\n", nomArchBin);
          return ERR_ARCHIVO;
     }

     FILE *archTxt = fopen(nomArchTxt, "rt");

     if (!archTxt)
     {
          printf("El archivo %s no se pudo abrir.\n", nomArchTxt);
          return ERR_ARCHIVO;
     }

     Producto prod;

     const char *formato = toupper(tipoTxt) == 'V' ? "%[^|]|%[^|]|%d|%d|%d|%f|%d\n" : "%30s%100s%2d%2d%4d%7f%4d\n";

     int cantCampos;

     while ((cantCampos = fscanf(archTxt, formato, prod.codigo, prod.descripcion, &prod.ultPrecio.dia, &prod.ultPrecio.mes, &prod.ultPrecio.anio, &prod.precioUnitario, &prod.cantidad)) != EOF)
     {
          if (cantCampos == 7)
               fwrite(&prod, sizeof(Producto), 1, archBin);
     }

     fclose(archBin);
     fclose(archTxt);

     return TODO_OK;
}

int archivoTxtABinCValidacion(const char *nomArchTxt, char tipoTxt, const char *nomArchBin)
{
     FILE *archBin = fopen(nomArchBin, "wb");

     if (!archBin)
     {
          printf("El archivo %s no se pudo abrir.\n", nomArchBin);
          return ERR_ARCHIVO;
     }

     FILE *archTxt = fopen(nomArchTxt, "rt");

     if (!archTxt)
     {
          printf("El archivo %s no se pudo abrir.\n", nomArchTxt);
          return ERR_ARCHIVO;
     }

     Producto prod;
     int cantCampos;
     char linea[TAM_LINEA];
     boolean errorCatastrofico = FALSO;
     int codError;

     TxtABin txtABin = tipoTxt == 'V' ? txtVaraBin : txtFijoABin;

     while (!errorCatastrofico && fgets(linea, TAM_LINEA, archTxt))
     {
          int cadError = txtABin(linea, &prod);

          //    errorCatastrofico = esErrorCatastrofico(codError);

          if (cadError == TODO_OK)
               fwrite(&prod, sizeof(Producto), 1, archBin);
     }

     fclose(archBin);
     fclose(archTxt);

     return codError;
}

int txtVaraBin(char *linea, Producto *prod)
{
     int codError = TODO_OK;

     char *act = strchr(linea, '\n');

     if (!act)
          codError = ERR_LINEA_LARGA;
     /*
            cantCampos = contarCampos(linea);

          if (cantCampos != 5)
               codError = ERR_CANT_CAMPOS;
     */
     //        Cantidad

     *act = '\0';
     act = strrchr(linea, '|');

     //   codError = verificarEntero(act + 1);

     if (codError == TODO_OK)
          sscanf(act + 1, "%d", &prod->cantidad);

     //        Precio Unitario

     *act = '\0';
     act = strrchr(linea, '|');

     //   codError = verificarDecimal(act + 1);

     if (codError == TODO_OK)
          sscanf(act + 1, "%f", &prod->precioUnitario);

     //        Fecha Ult Precio

     *act = '\0';
     act = strrchr(linea, '|');

     //  codError = verificarFecha(act + 1);

     if (codError == TODO_OK)
          sscanf(act + 1, "%d/%d/%d", &prod->ultPrecio.dia, &prod->ultPrecio.mes, &prod->ultPrecio.anio);

     //        Descripcion

     *act = '\0';
     act = strrchr(linea, '|');

     //   codError = verificarDescripcion(act + 1);

     if (codError == TODO_OK)
          strcpy(prod->descripcion, act + 1);

     //        Codigo

     *act = '\0';

     //   codError = verificarCodigo(linea);

     if (codError == TODO_OK)
          strcpy(prod->codigo, linea);
}

int txtFijoABin(char *linea, Producto *prod)
{
     int codError = TODO_OK;

     char *act = strchr(linea, '\n');

     if (!act)
          codError = ERR_LINEA_LARGA;

     //  cantCampos = contarCampos(linea);
     /*
          if (cantCampos != 5)
               codError = ERR_CANT_CAMPOS;
     */
     //        Cantidad

     *act = '\0';
     act -= 4;

     //   codError = verificarEntero(act);

     if (codError == TODO_OK)
          sscanf(act, "%d", &prod->cantidad);

     //        Precio Unitario

     *act = '\0';
     act -= 7;

     //   codError = verificarDecimal(act);

     if (codError == TODO_OK)
          sscanf(act, "%f", &prod->precioUnitario);

     //        Fecha Ult Precio

     *act = '\0';
     act -= 8;

     //  codError = verificarFecha(act);

     if (codError == TODO_OK)
          sscanf(act, "%2d%2d%4d", &prod->ultPrecio.dia, &prod->ultPrecio.mes, &prod->ultPrecio.anio);

     //        Descripcion

     *act = '\0';
     act -= 100;

     //   codError = verificarDescripcion(act);

     if (codError == TODO_OK)
     {
          rTrim(act);
          strcpy(prod->descripcion, act);
     }

     //        Codigo

     *act = '\0';

     //   codError = verificarCodigo(linea);

     if (codError == TODO_OK)
     {
          rTrim(act);
          strcpy(prod->codigo, linea);
     }

     return codError;
}

void rTrim(char *cadena)
{
     cadena += strlen(cadena);
     while (*cadena == ' ')
     {
          cadena--;
     }
     *(cadena + 1) = '\0';
}