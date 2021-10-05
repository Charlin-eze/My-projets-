/*Escriba una funcon que reciba un vector de estructuras y
busque en el mismo un determinado NombreyApellido. Tanto el vector
como el nombre y apellido a buscar deberan ser pasados como
parametros a la funcion desde main. La funcion debera devolver un -1
si no se encuentra el dato buscado o el indice donde se encuentra.
Una vez tenga escrita la funcion, genere dentro de un main un
vector estatico de 15 elementos, carguelo desde teclado siempre y cuando
no ingrese la palabra "FIN" y paselo a la funcion como parametro. 
Tenga en cuenta que pueden ser 15 datos o menos los ingresados.
Ademas dentro de main debera solicitar NombreyApellido a buscar e
imprimir el resultado de la busqueda, esto es un cartel que diga que
diga que no esta, o los datos completos(los tres campos) y el indice
donde fue encontrado. NO USE VARIABLES GOBALES.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define tam 15

struct datos{
              long legajo;
              char NombreyApellido[71];
              short edad;
            }typedef datos;

short busqueda(char *nombreBusq,datos *Agenda);

int main()
{
    datos Agenda[tam];
    char* nombreBusq=NULL;
    char aux;
    char Error[]="FIN\n";
    short indiceBusq=0;
    short cantidad=0;
    short i=0;

    printf("----------------------------------------------\n");
    printf("-----------------Bienvenido-------------------\n");
    printf("----------------------------------------------\n");

    printf("Vamos a cargar nuestra agenda...\n");
    while (i<tam)
    {
        fflush(stdin);
        printf("Ingrese el nombre a cargar,con la plabra 'FIN' finaliza la carga..\n");
        fgets(Agenda[i].NombreyApellido,sizeof(Agenda->NombreyApellido),stdin);
        if(strcmp(Agenda[i].NombreyApellido,Error)!=0)
         {
            printf("Ingrese el legajo...\n");
            fflush(stdin);
            scanf("%ld",&Agenda[i].legajo);
            printf("Ingrese la edad...\n");
            scanf("%hd",&Agenda[i].edad);
            i++;
            
        }
        else
        {
            printf("Finalizando la carga..\n");
            break;
        }
    }
    i=0;
    printf("Ingrese Nombre y Apellido a buscar..\n");
    cantidad=sizeof(Agenda->NombreyApellido);
    nombreBusq=(char *)malloc(cantidad*sizeof(char));
    fflush(stdin);
    fgets(nombreBusq,cantidad,stdin);
    indiceBusq=busqueda(nombreBusq,Agenda);
    if(indiceBusq==-1){
        printf("EL nombre no existe o no fue cargado..\n");
    }
    else{
        printf("Nombre Encontrado: %s",Agenda[indiceBusq].NombreyApellido);
        printf("Nº legajo: %ld\n",Agenda[indiceBusq].legajo);
        printf("Edad: %hd\n",Agenda[indiceBusq].edad);
    }

    free(nombreBusq);
    return 0;
}

short busqueda(char *nombreBusq,datos *Agenda){
    char *vec=nombreBusq;
    datos *miAgenda=Agenda;
    for (short j = 0; j < tam; j++)
    {
        if(strcmp(vec,miAgenda[j].NombreyApellido)==0){
            return j;
        }
        if(j==tam){
            return -1;
        }
    }
}
                                                                             
