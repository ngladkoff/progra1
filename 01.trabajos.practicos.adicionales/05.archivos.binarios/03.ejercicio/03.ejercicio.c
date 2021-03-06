/*Repetir el ejercicio 1 considerando que el archivo ha sido ordenado mediante el programa del
ejercicio 2. Utilizar el método de búsqueda binaria.*/
#include <stdio.h>
int grabarArch(char *nombre);
int mostrar(char *nombre);
int ordenar(char *nombre);
int leerReg(FILE *in, int numReg);
void grabarReg(FILE *out, int numReg, int valor);
int buscar(char *nombre, int valor);
int main(){
  int pos;
  grabarArch("enteros.dat");
  mostrar("enteros.dat");
  ordenar("enteros.dat");
  mostrar("enteros.dat");
  pos = buscar("enteros.dat", 2);

  if(pos != -1) printf("Se encontro a %d en la posición: %d", 2, pos);
  else puts("No se encontro el 2 en el archivo");

  return 0;
}
int grabarArch(char *nombre){
  FILE *out;
  int numeros[10] = {9,2,3,1,4,7,6,8,0,5};
  int i;

  if((out = fopen(nombre, "wb")) == NULL){
    printf("No pudo grabarse >\'%s\'", nombre);
    return 0;
  }

  for(i = 0; i < 10; i++){
    fwrite(&numeros[i], sizeof(int), 1, out);
  }

  fclose(out);
  return 1;
}
int mostrar(char *nombre){
  FILE *in;
  int i;

  if((in = fopen(nombre,"rb")) == NULL){
    printf("No pudo leerse > \'%s\'", nombre);
    return 0;
  }

  fread(&i, sizeof(int), 1, in);
  while(!feof(in)){
    printf("%4d", i);
    fread(&i, sizeof(int), 1, in);
  }
  printf("\n");

  fclose(in);
  return 1;
}
int ordenar(char *nombre){
  FILE *archivo;
  int i, j, aux1 = 0, aux2 = 0, size = 0;

  if((archivo = fopen(nombre, "rb+")) == NULL){
    printf("No pudo abrirse > \'%s\'", nombre);
    return 0;
  }

  fseek(archivo, 0, SEEK_END);
  size = ftell(archivo) / sizeof(int);
  fseek(archivo, 0, SEEK_SET);

  for(i = 0; i < size-1; i++){
    for(j = i +1; j < size; j++){
      aux1 = leerReg(archivo, i);
      aux2 = leerReg(archivo, j);
      if(aux1 > aux2){
        grabarReg(archivo, j, aux1);
        grabarReg(archivo, i, aux2);
      }
    }
  }

  fclose(archivo);
  return 1;
}
int leerReg(FILE *in, int numReg){
  int valor = 0;
  fseek(in, sizeof(int) * numReg, SEEK_SET);
  fread(&valor, sizeof(int), 1, in);
  return valor;
}
void grabarReg(FILE *out, int numReg, int valor){
  fseek(out, sizeof(int) * numReg, SEEK_SET);
  fwrite(&valor, sizeof(int), 1, out);
}

int buscar(char *nombre, int valor){
  //Recibe nombre de archivo y valor a buscar
  //Como requisito el archivo debe estar ordenado
  //Retorna la posición donde se encontro la coincidencia
  //Caso contrario retorna -1
  FILE *in;
  int pos = -1, size = 0, izq = 0, der, medio, contMedio;


  if((in = fopen(nombre, "rb")) == NULL){
    printf("No pudo leerse >\'%s\'", nombre);
  }

  fseek(in, 0, SEEK_END);
  size = ftell(in) / sizeof(int);
  rewind(in);

  der = size -1;
  izq = 0;

  while(izq <= der){
    medio = ((izq + der) / 2);//posición de medio
    contMedio = leerReg(in, medio);//valor guardado en posición de medio

    if(contMedio == valor){
      fclose(in);
      return medio;//retorna posición donde se encontro la coincidencia
    }else if(contMedio < valor)                     izq = medio + 1;
    else                                            der = medio - 1;
  }

  fclose(in);
  return -1;
}
