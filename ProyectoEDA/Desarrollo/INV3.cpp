#include <iostream> 
#include <stdio.h>
#include <math.h>       /* log2 */
#include <vector>
//namespace std;

int main()
{
  char parte_alta, parte_baja;
  int caracter_guardado, indice_guardado;
  int Numero = 0, numero2 = 0;
  //Hacemos la memoria hash cero
    int tabla_hash[65536];
    for(int i=0;i<65536;i++){
      tabla_hash[i]=0;
    } 
    //std::cout << "while" << '\n';
    // Lee el archivo.txt y toma un caracter
    FILE *pFile; 
    FILE *pFile2;
    pFile = fopen ("D" , "r"); //Lee el archivo .txt
    //pFile = fopen ("Primeras10000lineas.txt" , "r"); //Lee el archivo .txt
    //std::cout << "while" << '\n';
  
    pFile2 = fopen("Comprimido.ilsh","w"); //Escribe un .javi
    if (pFile == NULL && pFile2 == NULL) perror ("Error opening file"); 
    else {
      int indice = 0;
      unsigned char c;
      //std::cout << "while3" << '\n';
      //while (fgets(instruccion, 15 , pFile) && feof(pFile) == 0){
      while(feof(pFile) == 0){
	c = fgetc (pFile);
	numero2++;
	//std::cout << "Numero2 " << numero2 << '\n';
	//std::cout << "Caracter " << c << '\n';
	int caracter = c;
	int mov_choque = 3;
	//Hacemos la xor del indice contra el caracter y obtenemos el hash
	int trasl_caracter = caracter<<8;
	int hash = indice ^ trasl_caracter;
	hash = hash & 65535;
	//std::cout << "indice" << indice << "hash " << hash << '\n';
	while(1){
	  ///Revisamos con el Hash si la posicion de memoria esta ocupada
	  if(tabla_hash[hash] > 16777216){
	    caracter_guardado = (tabla_hash[hash] & 255);
	    indice_guardado = ((tabla_hash[hash]>>8) & 65535);
	    //std::cout << "TH "   << tabla_hash[hash] << '\n';
	    //std::cout << "caracter "   << caracter << '\n';
	    //std::cout << "caracter guardado "   << caracter_guardado << '\n';
	    //std::cout << "indice "   << indice << '\n';
	    //std::cout << "indice guardado "   << indice_guardado << '\n';
	    
	    ///Revisamos si la informacion ya esta guardada
	    if((caracter == caracter_guardado) && (indice == indice_guardado)){
	      indice = hash;
	      //std::cout << "ya esta2 "   << indice << '\n';
	      break;
	      ///tomo otro caracter
	    }
	    else{
	      //std::cout << "ya esta otra vez" << '\n';
	      if(mov_choque < 4){
		mov_choque = 7;
		hash = hash + 3;
	      }
	      else{
		hash = hash + 4;
		if(mov_choque > 14){
		  /// FALTA GUARDAR EL INDICE Y EL CARACTER FUERA .javi
		  Numero++;
		  parte_alta = (indice >> 8) & 255;
		  parte_baja = indice & 255;
		  fputc (parte_alta,pFile2);
		  fputc (parte_baja,pFile2);
		  fputc (caracter,pFile2);
		  indice = 0; 
		  break;
		}
	      }
	    }
	  }
	  ///Si la posicion de la memoria esta desocupada guardo los datos
	  else{
	    Numero++;
	    //std::cout << Numero << " guardo \n " << '\n';
	    tabla_hash[hash] = 16777216 + (indice << 8) + caracter;
	  
	    /// FALTA GUARDAR EL INDICE Y EL CARACTER FUERA .javi
	    parte_alta = (indice >> 8) & 255;
	    parte_baja = indice & 255;
	    fputc (parte_alta,pFile2);
	    fputc (parte_baja,pFile2);
	    fputc (caracter,pFile2);
	    indice = 0;
	    break;
	  }
	}//while
	
	//printf("%d: %s",f, instruccion);
	//std::cout << "Cantidad de misses: " << miss << '\n';
      }//while
      fclose (pFile);
      fclose (pFile2);
    }//else
     std::cout << Numero << " FIN \n " << '\n';
}//main

