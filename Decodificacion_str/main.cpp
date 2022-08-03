#include <iostream>
#include <math.h>

using namespace std;

void metodo1(int[], int[], int, int);
void metodo2(int[], int[], int, int);
int cuentaUnosyCeros(int, int*);
void imprimir(int[], int);
void texto(int[], string, int);

int main()
{
    int cod1[] = {1,0,1,1,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,1,1,0,1,0,0,1,1,0,1,1};
    int cod2[] = {0,0,1,0,1,0,0,0,0,0,1,1,0,0,0,1,0,0,1,0,1,0,0,1,0,0,1,1,0,0,1,0};
    int tam = sizeof(cod1) / 4;
    int decodificado[tam * 8];
    int *pCod = cod1;
    int *pDeco = decodificado;
    int num = 4; //Semilla
    string cadena = "";

    metodo1(pCod, pDeco, num, tam);
    texto(decodificado, cadena, tam);
    cout << cadena << endl;


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

void texto(int binario[], string alpha, int tam){
    int bloque = 7;
    int byte = 8;
    int *pBinario = binario;
    string letra = "";
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
        letra = suma;
        alpha[posicion] = suma;
        posicion++;
        pBinario = pBinario + byte;
    }
}
