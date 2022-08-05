#include <iostream>
#include <math.h>

using namespace std;

void metodo1(int[], int[], int, int);
void metodo2(int[], int[], int, int);
void letras(int[], int, char[]);
int cuentaUnosyCeros(int, int*);
void imprimir(int[], int);
void imprimirCadena(char[]);

int main()
{
    int cod1[] = {1,0,1,1,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,1,1,0,1,0,0,1,1,0,1,1};
    int cod2[] = {0,0,1,0,1,0,0,0,0,0,1,1,0,0,0,1,0,0,1,0,1,0,0,1,0,0,1,1,0,0,1,0};
    int tam = sizeof(cod1) / 4;
    int decodificado[tam * 8];
    int *pCod = cod1;
    int *pDeco = decodificado;
    int num = 4; //Semilla
    char alpha[256];
    int opcion = 0;

    cout << "Ingrese el 1 para usar el primer metodo. " << endl;
    cout << "Ingrese el 2 para usar el segundo metodo. " << endl;
    cout << "La opcion: "; cin >> opcion;
    cout << "Ingrese la semilla de codificacion: "; cin >> num;

    while(opcion != 1 & opcion != 2){
        cout << "Caracter no definido, por favor ingrese otro: ";  cin >> opcion;
    }
    if(opcion == 1){
        metodo1(pCod, pDeco, num, tam);
        imprimir(pDeco, tam);
        cout << "El texto decodificado por el metodo1 es: ";
        letras(decodificado, tam, alpha);
        imprimirCadena(alpha);
    }
    else{
        pCod = cod2;
        metodo2(pCod, pDeco, num, tam);
        imprimir(pDeco, tam);
        cout << "El texto decodificado por el metodo2 es: ";
        letras(decodificado, tam, alpha);
        imprimirCadena(alpha);
    }




    return 0;
}

void metodo1(int codificado[], int decodificado[], int num, int tam){
    int *pCod = codificado;
    int *pDeco = decodificado;
    int bloques = 1;
    for(int i = 0; i < tam; bloques++){
        if(bloques == 1){
            for(int j = 0; j < num; j++){
                if(*(pCod + j) == 1){
                    *pDeco = 0;
                    pDeco++;
                    i++;
                }
                else{
                    *pDeco = 1;
                    pDeco++;
                    i++;
                }
            }
        }
        else{
            if(cuentaUnosyCeros(num, pCod) == 1){
                for(int j = 1; j <= num; j++){
                    if(j % 2 == 0){
                        if(*(pCod + num) == 1){
                            *pDeco = 0;
                            pDeco++;
                            i++;
                            pCod++;
                        }
                        else{
                            *pDeco = 1;
                            pDeco++;
                            pCod++;
                            i++;
                        }
                    }
                    else{
                        *pDeco = *(pCod + num);
                        pDeco++;
                        pCod++;
                        i++;
                    }

                }

            }
            else if(cuentaUnosyCeros(num, pCod) == 0){
                for(int j = 1; j <= num; j++){
                    if(j % 2 == 0){
                        if(*(pCod + num) == 1){
                            *pDeco = 0;
                            pDeco++;
                            pCod++;
                            i++;
                        }
                        else{
                            *pDeco = 1;
                            pDeco++;
                            pCod++;
                            i++;
                        }
                    }
                    else{
                        *pDeco = *(pCod + num);
                        pDeco++;
                        pCod++;
                        i++;
                    }

                }

            }
            else if(cuentaUnosyCeros(num, (pCod+i)) == 2){
                for(int j = 0; j < num; j++){
                    if(*(pCod + num) == 1){
                        *pDeco = 0;
                        pDeco++;
                        pCod++;
                        i++;
                    }
                    else{
                        *pDeco = 1;
                        pDeco++;
                        pCod++;
                        i++;
                    }
                }
            }
        }
    }

}

void metodo2(int codificado[], int decodificado[], int num, int tam){
    int *pCod = codificado;
    int *pDeco = decodificado;

    for(int i = 0; i < tam; i = i + num){
        for(int j = 0; j < num; j++){
            if(j == 0){
                *(pDeco + (num-1)) = *pCod;
                pCod++;
            }
            else{
                *pDeco = *pCod;
                pDeco++;
                pCod++;
            }

        }
        pDeco++;
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

void letras(int binario[], int tam, char alpha[]){
    int bloque = 7;
    int byte = 8;
    int *pBinario = binario;
    int posicion = 0; //Controla la posicion de las letras en el char


    for(int i = 0; i < tam; i = i + byte){
        int suma = 0;
        bloque = 7;
        for(int j = 0; j <= byte; j++){
            if(*(pBinario + bloque) == 1){
                suma = suma + pow(2,j);
                bloque--;
            }
            else{
                bloque--;
            }
        }
        alpha[posicion] = suma;
        posicion++;
        pBinario = pBinario + byte;
    }
}

void imprimirCadena(char alpha[]){
    for(int i = 0; alpha[i] != '\0'; i++){
        cout << alpha[i];
    }
    cout << endl;
}
