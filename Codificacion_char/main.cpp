#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void binario(char, int[], int*);
void primerMetodo(int, int, int[], int[]);
void segundoMetodo(int, int, int[],int[]);
int cuentaUnosyCeros(int, int*);
int longitud(char[]); // Retorna el tamaño real de la cadena ingresada por el usuario
void imprimir(int[], int);


int main()
{


    char cadena[256];
    cout << "Ingrese cadena: "; cin >> cadena;
    int num = 4;
    int tamCadena = longitud(cadena);
    int tamano = longitud(cadena) * 8; //Tamaño del arreglo original y codificado
    int original[tamano];
    int *ptrOrginal = original;
    int codificado[tamano];
    int opcion = 0;


    cout << "Ingrese el 1 para usar el primer metodo. " << endl;
    cout << "Ingrese el 2 para usar el segundo metodo. " << endl;
    cout << "La opcion: "; cin >> opcion;
    cout << "Ingrese la semilla de codificacion: "; cin >> num;

    while(opcion != 1 & opcion != 2){
        cout << "Caracter no definido, por favor ingrese otro: ";  cin >> opcion;
    }
    if(opcion == 1){
        cout << "Original: " << endl;
        for(int i = 0; i < tamCadena; i++){
            binario(cadena[i], original, ptrOrginal);
            ptrOrginal = ptrOrginal + 8;
        }
        imprimir(original, tamano);
        primerMetodo(num, tamano, original, codificado);
        cout << "Codificado: " << endl;
        imprimir(codificado, tamano);
    }
    else{
        cout << "Original: " << endl;
        for(int i = 0; i < tamCadena; i++){
            binario(cadena[i], original, ptrOrginal);
            ptrOrginal = ptrOrginal + 8;
        }
        imprimir(original, tamano);
        segundoMetodo(num, tamano, original, codificado);
        cout << "Codificado: " << endl;
        imprimir(codificado, tamano);
    }


    return 0;
}

void binario(char letra, int original[], int *ptrOrginal){
    int num = letra;
    int digito = num;
    int reves[8]; //Almacena el arreglo al reves para despues invertirlo.
    int *ptrReves = reves;
    int tamano = 0;

    for(int i = num; i >= 1; i=num){
        digito = num % 2;
        num = num / 2;
        *ptrReves = digito;
        ptrReves++;
        tamano++;
    }
    while(tamano < 8){
        *ptrReves = 0;
        tamano++;
    }
    // Invertido.
    for(int i = 8; i > 0; i--){
        *ptrOrginal = *ptrReves;
        ptrReves--;
        ptrOrginal++;
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

void primerMetodo(int num,int tamano, int original[], int codificado[]){
    int *ptrOriginal = original;
    int *ptrCod = codificado;
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
void segundoMetodo(int num, int tamano, int original[],int codificado[]){
    int *ptrOriginal = original;
    int *ptrCod = codificado;
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

int longitud(char cadena[256]){
    int contador = 0;
    for(int i = 0; cadena[i] != '\0'; i++){
        contador++;
    }
    return contador;
}

void imprimir(int cadena[], int tamano){
    for(int i = 0; i < tamano; i++){
        cout << cadena[i];
    }
    cout << endl;
}
