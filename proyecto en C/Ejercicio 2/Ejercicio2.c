/*En este ejercicio vamos a recopilar informacion atravez de un archivo ya otorgado,
se necesita imprimir en pantalla las personas que tengan de condicion "ESTABLE" 
y ademas seguro "SNP"
Ademas se debe generar un archivo "salida.txt" con la info encontrada
Ademas se debe informar: Promedio de sueeldos pagados, Cuantos empleados hay y 
cuantos empleados no tienen hijos.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


typedef struct datos
{
    char carnet[10];
    char ApellidoyNombre[50];
    char ingreso[15];
    char categoria[2];
    char sexo[2];
    char estadocivil[2];
    char hijos[2];
    char legajo[20];
    char ocupacion[20];
    char condicion[15];
    char sueldo[15];
    char seguro[15];
} Datos;

float iterar(char* array);

int main(){
    Datos *ListaEmpleados=NULL;
    Datos aux[1];
    FILE *Planilla;
    FILE *salida;
    unsigned short i=0;
    float sueldos=0;
    float sueldosAcu=0;
    float sueldospromedios=0;
    short acumulador=0;
    short contador=0;
    char FILTRO[]={"ESTABLE"};
    char FILTRO2[]={"SNP"};
    char *array;
    
    printf("+----------------------Bienvenidos-----------------------------+\n");
    printf("+---Vamos a decodificar informacion del archivo BINARIO.BIN----+\n");
    
    if (access("binario.bin", F_OK) != -1){

       printf("Recopilando informacion de archivo...\n");
       Planilla=fopen("binario.bin","rb");
       salida=fopen("Salida.txt","wt");
       if(Planilla!=NULL){
           printf("Almacenando datos del archivo...\n");
           printf("Filtrando empleados por seguro SNP y por condicon ESTABLE\n");
           fprintf(salida,"Filtrando empleados por seguro SNP y por condicon ESTABLE\n");
           fread(aux,sizeof(Datos),1,Planilla);
           while (!feof(Planilla))
           {
               ListaEmpleados=realloc(ListaEmpleados,(i+1)*sizeof(Datos));
               ListaEmpleados[i]=*aux;
               fread(aux,sizeof(Datos),1,Planilla);
               i++;
            }
            acumulador=i;
               
            i=0;
               
           fclose(Planilla);
           fprintf(salida,"+--------------------------------------------------------------+\n");
           fprintf(salida,"|        Lista filtrada segun los parametros indicados         |\n");
           fprintf(salida,"+--------------------------------------------------------------+\n\n");
           printf("+------------------------------+----+-----+--------------------+\n");
           printf("|%-30s|%-4s|%-3s|%-20s|\n","Apellido y Nombre","Sexo","Hijos","Legajo");
           printf("+------------------------------+----+-----+--------------------+\n");
           fprintf(salida,"+------------------------------+----+-----+--------------------+\n");
           fprintf(salida,"|%-30s|%-4s|%-3s|%-20s|\n","Apellido y Nombre","Sexo","Hijos","Legajo");
           fprintf(salida,"+------------------------------+----+-----+--------------------+\n");
          
           while (i<acumulador)
           {
             if((strcmp(ListaEmpleados[i].condicion,FILTRO)==0)&&(strcmp(ListaEmpleados[i].seguro,FILTRO2)==0)){
                  printf("|%-30s|%-4s|%-5s|%-20s|\n",ListaEmpleados[i].ApellidoyNombre,ListaEmpleados[i].sexo,ListaEmpleados[i].hijos,ListaEmpleados[i].legajo);
                  fprintf(salida,"|%-30s|%-4s|%-5s|%-20s|\n",ListaEmpleados[i].ApellidoyNombre,ListaEmpleados[i].sexo,ListaEmpleados[i].hijos,ListaEmpleados[i].legajo);
                }
             i++;
            }
            printf("+------------------------------+----+-----+--------------------+\n");
            fprintf(salida,"+------------------------------+----+-----+--------------------+\n");
            printf("Guardando los datos del archivo en un fichero de texto...\n");
            
        }
    } else
      {
       printf("!!...NO SE ENCUENTRA ARCHIVO...!!\n");
       exit(-1);
       }
    
   
    i=0;
    while (i<acumulador)
    {  array=ListaEmpleados[i].sueldo;
       sueldos=iterar(array);
       printf("Sueldo leido: $%.2f\n",sueldos);
       sueldosAcu+= sueldos;
       i++;
    }
    printf("Dinero total que se pago: $$%.2f\n",sueldosAcu);
    fprintf(salida,"Dinero total que se pago: $%.2f\n",sueldosAcu);
    sueldospromedios=sueldosAcu/acumulador;
    printf("El promedio de sueldo pagados es: $%.2f\n\n",sueldospromedios);
    fprintf(salida,"El promedio de sueldo pagados es: $%.2f\n\n",sueldospromedios);
    i=0;

    printf("+--------------------------+------------------------------+\n");
    printf("|Los empleados totales son:|%-30hd|\n",acumulador);
    printf("+--------------------------+------------------------------+\n");
    fprintf(salida,"+--------------------------+------------------------------+\n");
    fprintf(salida,"|Los empleados totales son:|%-30hd|\n",acumulador);
    fprintf(salida,"+--------------------------+------------------------------+\n\n");

    printf("+--------------------------+------------------------------+\n");
    fprintf(salida,"+--------------------------+------------------------------+\n");
    while (i<acumulador)
    { 
       if(strcmp(ListaEmpleados[i].hijos,"0")==0){
          printf("|El personal sin hijos es: |%-30s|\n",ListaEmpleados[i].ApellidoyNombre);
          fprintf(salida,"|El personal sin hijos es: |%-30s|\n",ListaEmpleados[i].ApellidoyNombre);
       } 
       i++;
    }
    printf("+--------------------------+------------------------------+\n");
    fprintf(salida,"+--------------------------+------------------------------+\n");
    printf("Guardando los datos del archivo en un fichero de texto...\n");

    fclose(salida);
    free(ListaEmpleados);
    array=NULL;
    free(array);
    system("pause");
    return 0;
}

float iterar(char* array){
    char* vec=array;
    char* ptr;
    char inadmisible[]={"."};
    short cantidad=sizeof(vec)/sizeof(vec[0]);
    float dato;
    short bandera=0;
    
       for (short j = 0; j < cantidad; j++)
       {
           if(vec[j]=='.'){
              bandera=j;
              break;
            }
        }
       if(bandera==1){
           for(short j=bandera; j < cantidad; j++)
           {
               vec[j]=vec[j+1];
            }
       }
       
    dato=strtof(vec, &ptr);
    return dato;

}