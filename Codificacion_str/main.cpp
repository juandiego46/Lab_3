#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>

using namespace std;

void binario(string, int*);
void metodo1(int, int, int*, int*);
void metodo2(int, int, int*, int*);
int cuentaUnosyCeros(int, int*);
void imprimir(int[], int);


int main()
{
    ofstream fout;
    string cadena = "";
    cout << "Ingrese lo que desee: "; cin >> cadena;
    fout.open("Sudo.txt");

    int num = 4;    // Semilla.
    int tamCadena = cadena.size();
    int original[tamCadena * 8];
    int *pOriginal = original;
    int codificado[tamCadena * 8];
    int *pCodificado = codificado;
    int opcion = 0;

    cout << "Ingrese el 1 para usar el primer metodo. " << endl;
    cout << "Ingrese el 2 para usar el segundo metodo. " << endl;
    cout << "La opcion: "; cin >> opcion;
    cout << "Ingrese la semilla de codificacion: "; cin >> num;

    while(opcion != 1 & opcion != 2){
        cout << "Caracter no definido, por favor ingrese otro: ";  cin >> opcion;
    }
    if(opcion == 1){
        metodo1(num, (tamCadena * 8), pOriginal, pCodificado);
        fout << codificado;
        fout.close();
    }
    else{
        metodo2(num, (tamCadena * 8), pOriginal, pCodificado);
        fout << codificado;
        fout.close();
    }


    return 0;
}

void binario(string cadena, int *ptr){
    int tamCadena = cadena.size();
    for(int i = 0; i < tamCadena; i++){
        int n = cadena[i];
        int digito = 0;
        int iteraciones = 0;
        int copia[8];
        int *pCopia = copia;
        for(int j = 0; n > 0; j++){
            digito = n % 2;
            n = n / 2;
            *(pCopia + j) = digito;
            iteraciones++;
        }
        if(iteraciones < 8){
            *(ptr + 7) = 0;
        }
        for(int j = 7; j >= 0; j--){
            *ptr = *(pCopia + j);
            ptr++;
        }
    }
}


void metodo1(int num, int tamano, int *ptrOriginal, int *ptrCod){
    int contaPos = 0;
    int contaBit = 0;

   for(int i = 0; i < tamano; i = i + num){
       if(contaPos < num){ //Primer bloque donde se invierten todos los digitos.
           for(int j = 0; j < num; j++){
               if(*(ptrOriginal + contaPos) == 0){
                  *(ptrCod + contaPos) = 1;
                  contaPos++;
              }
              else{
                  *(ptrCod + contaPos) = 0;
                  contaPos++;
                  }
           }
           ptrCod = ptrCod + num;
       }
       else{
           if(cuentaUnosyCeros(num, ptrOriginal) == 2){ // Cuando hay igual cantidad de unos y ceros.
               for(int j = 0; j < num; j++){
                   if(*(ptrOriginal + (num+j)) == 0){
                       *ptrCod = 1;
                       ptrCod++;
                   }
                   else{
                       *ptrCod = 0;
                       ptrCod++;
                   }
               }
               ptrOriginal = ptrOriginal + num;
           }

           else if(cuentaUnosyCeros(num, ptrOriginal) == 0){ // Si hay mayor cantidad de ceros.
               contaBit = 0;
               for(int j = 0; j < num; j++){
                   if(contaBit % 2 == 1){
                       if(*(ptrOriginal + (num+j)) == 0){
                           *ptrCod = 1;
                           ptrCod++;
                           contaBit++;

                       }
                       else{
                           *ptrCod = 0;
                           ptrCod++;
                           contaBit++;
                       }
                   }
                   else{
                       *ptrCod = *(ptrOriginal + (num+j));
                       ptrCod++;
                       contaBit++;
                   }
               }
               ptrOriginal = ptrOriginal + num;
           }
           else if(cuentaUnosyCeros(num, ptrOriginal) == 1){ // Si hay mayor cantidad de Unos.
               contaBit = 1;
               for(int j = 0; j < num; j++){
                   if(contaBit % 3 == 0){
                       if(*(ptrOriginal + (num+j)) == 0){
                           *ptrCod = 1;
                           ptrCod++;
                           contaBit++;
                       }
                       else{
                           *ptrCod = 0;
                           ptrCod++;
                           contaBit++;
                       }
                   }
                   else{
                       *ptrCod = *(ptrOriginal + (num+j));
                       ptrCod++;
                       contaBit++;
                   }
               }
               ptrOriginal = ptrOriginal + num;
           }
       }
   }

}

void metodo2(int num, int tamano, int *ptrOriginal, int *ptrCod){
    int contaBit = 0;

    for(int i = 0; i < tamano; i = i + num){
        for(int j = (num-1); j >= 0; j--){
            contaBit = 0;
            if(j == (num-1)){
                *ptrCod = *(ptrOriginal + j);
                ptrCod++;

            }
            else{
                *ptrCod = *ptrOriginal;
                ptrCod++;
                contaBit++;
                ptrOriginal++;
            }
        }
        ptrOriginal++;
    }
}


int cuentaUnosyCeros(int num, int *ptrOriginal){
    int unos = 0;
    int ceros = 0;
    int contaBits = 0;

    for(int i = 0; i < num; i++){
        if(*(ptrOriginal + contaBits) == 0){
            ceros++;
            contaBits++;
        }
        else{
            unos++;
           contaBits++;
        }
    }
    if(ceros > unos){
        return 0;
    }
    else if(unos > ceros){
        return 1;
    }
    else if(unos == ceros){
        return 2;
    }
}

void imprimir(int cadena[], int tamano){
    for(int i = 0; i < tamano; i++){
        cout << cadena[i];
    }
    cout << endl;
}
