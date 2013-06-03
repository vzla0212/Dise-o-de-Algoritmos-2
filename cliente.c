// Global variables
int Cap;
double CostoRutaAct=0;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Par.h"
#include "Vector.h"

#define N 100
#define True 1
#define False 0

double Costo(int **Costos,int **Rutas,int **Carga,int **Datos,int veh,int cli){
	double cost = 0.0;
	int i,j;
	for (i=0;i<veh;++i){
		if (Rutas[i][0]!=-1){
			cost = cost + Costos[0][Rutas[i][0]];
			for(j=1;(j<cli) && (Rutas[i][j]!=-1);++j){
				cost = cost + Costos[Rutas[i][j-1]][Rutas[i][j]];
			}
			cost = cost + Costos[Rutas[i][j-1]][0];
		}
	}
	return cost;
}

void Sol_Aleatoria(int **Costos, int **Datos, int* Cargas, int** Rutas, int cli, int veh)
{
  srand(time(NULL)); 
  int i;
  int rnd;
  for(i=1; i<cli; ++i)
  {
    printf("i %d\n", i);
    rnd=rand()%(veh);
    while(!((Cargas[rnd]+Datos[0][i])<=Cap)){
      //printf("CargaAc %d\n", Cargas[rnd]+Datos[0][i]);
      //printf("Cap %d\n", Cap);
      rnd=rand()%(veh);
      printf("Ale %d\n", rnd);
    }
    Cargas[rnd]+=Datos[0][i];
    int R;
    for(R=0;R<cli;++R){
      if(Rutas[rnd][R]==-1){
        Rutas[rnd][R]=i;
        break;
      }
    }
  }  
}

/*
void Costo(int **Costos, int **Rutas, int **Datos, int veh, int cli)
{
  int i;
  for(i=0;i<veh;++i)
  {
   int j;
   for(j=0;j<cli;++j)
   {
    if(Rutas)
    if(Rutas[i][j]==-1)
    {
      break;
    }else
    {
      
    }
      
   }
  }
}
*/

/*hola*/

int main(int argc, char **argv)
{
    FILE *archivo;
    archivo = fopen(argv[1],"r");
    char *buffer=(char *)malloc(N*sizeof(char));
    int number;
    int capacity;
    int id,x,y,d,a,b,s;
    double distancia;
    int c_arco,n,e1,e2;
    int i,j;
    int **Costos;
    int **Datos;
    int **Rutas;
    Pares *par = NULL;
    if (archivo == NULL)
    {
        printf("\nError de apertura del archivo. \n\n");
    }
    else
    {
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%d %d",&number,&capacity);
        Cap=capacity;
        //printf("Numero de vehiculos: %d   Capacidad por vehiculo: %d\n",number,capacity);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        fscanf(archivo,"%s",buffer);
        while (1)
        {
            if (feof(archivo) == True)
            {
                break;
            }
            fscanf(archivo,"%d %d %d %d %d %d %d",&id,&x,&y,&d,&a,&b,&s);
            printf("%d %d %d %d %d %d %d\n",id,x,y,d,a,b,s);
            Insertar(&par,id,x,y,d,a,b,s);
            
        }

    }
   
    int Cargas[number];
    int h;
    
    for(h=0; h<number;++h){
      Cargas[h]=0;
    }
    
    /*
    for(h=0; h<number;++h){
      printf("%d\n",Cargas[h]);
    }*/
    
    n = Longitud(par);
    n = n-1;//Por leer el ultimo 2 veces
    Pares *aux = par;
    Costos = Crear_Matriz(n,n);
    Datos = Crear_Matriz(4,n);
    Rutas = Crear_Matriz(number,n);
    int mi,mj;
    
    for(mi=0;mi<number;++mi){
      for(mj=0;mj<n;++mj){
        Rutas[mi][mj]=-1;
      }
    }
    
    while(aux!=NULL)
    {
        int i,j;
        Pares *aux2 = par;
        i = aux->id;
        while (aux2!=NULL)
        {
            j = aux2->id;
            if (j!=i)
            {
                e1 = pow(((aux2->x)-(aux->x)),2);
                e2 = pow(((aux2->y)-(aux->y)),2);
                distancia = sqrt((e1+e2));
                c_arco = (int)distancia;
                Costos[i][j] = c_arco;
            }
            else
            {
                Costos[i][j] = 0;
            }
            aux2 = aux2->sig;
        }
        aux = aux->sig;
    }

    Pares *aux3 = par;
    while(aux3!=NULL)
    {
        id = aux3->id;
        Datos[0][id] = aux3->dem;
        Datos[1][id] = aux3->vi;
        Datos[2][id] = aux3->vf;
        Datos[3][id] = aux3->ts;
        aux3 = aux3->sig;
    }
    
    Sol_Aleatoria(Costos, Datos, Cargas, Rutas, n, number);
    
    ImprimirMatriz(Rutas,number,n);
    
    for(i=0;i<number;++i){
      printf("veh %d  carga %d \n",i,Cargas[i]);
    }
    
    fclose(archivo);
    exit(0);
}
