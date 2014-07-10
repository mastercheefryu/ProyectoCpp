#include <iostream> 
#include <stdio.h>
#include <math.h>       /* log2 */
#include <vector>
//namespace std;

int main()
{
  unsigned int indice, mov_choque;
  unsigned char parte_alta, parte_baja, caracter;
  unsigned int caracter_guardado, indice_guardado;
  unsigned int Numero = 0, numero2 = 0, i = 0, j = 0;
  char lifo[65536];
  //Hacemos la memoria hash cero
  int tabla_hash[65536];
  for(i=0;i<65536;i++){
    tabla_hash[i]=0;
  } 

  // Lee el archivo.txt y toma un caracter
  FILE *pFile;
  FILE *pFile2;
  pFile = fopen("Comprimido.ilsh" , "r"); //Lee el archivo .txt
  //pFile = fopen ("Primeras10000lineas.txt" , "r"); //Lee el archivo .txt  
  
  pFile2 = fopen("Descomprimido.ilsh","w"); //Escribe un .ilsh

  if (pFile == NULL && pFile2 == NULL) perror ("Error opening file"); 
  else {
    while(feof(pFile) == 0){
      j=0;
      mov_choque = 3; //Varaible para mover posiciones en caso de choque en el hash
      //Cargar el indice y el caracter
      parte_alta = fgetc (pFile);
      indice = (parte_alta << 8);
      parte_baja = fgetc (pFile);
      indice += parte_baja;
      caracter = fgetc (pFile);
      
      unsigned int trasl_caracter = (caracter << 8);

      //Busco el hash
      unsigned int hash = (indice ^ trasl_caracter) & 65535;

      //Almaceno el indice y el caracter en la posicion del hash
      while(1){
	  ///Revisamos con el Hash si la posicion de memoria esta ocupada
	  if(tabla_hash[hash] > 16777215){
	    caracter_guardado = (tabla_hash[hash] & 255);
	    indice_guardado = ((tabla_hash[hash]>>8) & 65535);
	    
	    ///Revisamos si la informacion ya esta guardada
	    if((caracter == caracter_guardado) && (indice == indice_guardado)){
	      break;
	    }
	    else{
	      if(mov_choque < 4){
		mov_choque = 7;
		hash = hash + 3;
	      }
	      else{
		hash = hash + 4;
		if(mov_choque > 14){
		  break;
		}
	      }
	    }
	  }
	  ///Si la posicion de la memoria esta desocupada guardo los datos
	  else{
	    tabla_hash[hash] = 16777216 + (indice << 8) + caracter;
	    break;
	  }
      }//while

      //Guardo caracteres en el lifo;
      while(1){
	caracter_guardado = (tabla_hash[hash] & 255);
	indice_guardado = ((tabla_hash[hash]>>8) & 65535);
	if (indice_guardado != 0){
	  hash = indice_guardado;
	  //Guardo en el BUFFER LIFO
	  lifo[j]=caracter_guardado;
	  j++;   
	}
	else{
	  fputc (caracter_guardado,pFile2); //Guardo primer caracter
	  break;
	}
      }//while caracteres
      

      //Descargo el Lifo
      for(i=j;i>0;i--){
	fputc (lifo[i-1],pFile2);
      }
    }//while
    fclose (pFile);
    fclose (pFile2);
  }//else
  std::cout << " FIN \n " << '\n';
}//main
