#ifndef MIS_FUNCIONES_H
#define MIS_FUNCIONES_H
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#endif // MIS_FUNCIONES_H

void binario(char letra, int *ptrOrginal){
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

void binario(string cadena, int almacena[]){
    int *ptr =  almacena;
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

void codificacionMetodo1(int num, int tamano, int original[], int codificado[]){
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
void codificacionMetodo2(int num, int tamano, int original[],int codificado[]){
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

void decodificacionMetodo1(int codificado[], int decodificado[], int num, int tam){
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

void decodificacionMetodo2(int codificado[], int decodificado[], int num, int tam){
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

void escribeArchivo(int codificado[]){
    int tamano = 32;
    ofstream fout;
    fout.open("Sudo.txt");
    for(int i = 0; i < tamano; i++){
        fout << codificado[i];
    }
    fout.close();
}

void registroUsuarios(int cedula[], int clave[], int saldo[], int n){
    cout << "Cuantos usurios desea registrar: "; cin >> n;
    for(int i = 0; i < n; i++){
        cout << "Ingrese la cedula del usuario: "; cin >> cedula[i];
        for(int j = 0; j < i; j++){
            while(cedula[i] == cedula[j]){
                cout << "Esta persona ya esta registrada, por favor ingrese otra: "; cin >> cedula[i];
            }
        }
        cout << "Ingrese la clave del usuario: "; cin >> clave[i];
        cout << "Ingrese el saldo del usuario: "; cin >> saldo[i];
    }
}

bool claveAdministrador(string intento){
    int tam = intento.size() * 8;
    int almacena[tam];
    int semilla = 4;
    binario(intento, almacena);
    int codificado[tam];
    codificacionMetodo1(semilla, tam, almacena, codificado);
    ifstream fin;
    int claveAdmi[tam]; //Arreglo que va a contener la clave real del administrador.
    fin.open("Sudo.txt");
    fin.seekg(0);
    if(fin.fail()){
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    while(fin.good()){ //Mientras no sea el final del archivo.
        for(int i = 0; i < tam; i++){
            char letra = fin.get();
            int numero = letra - '0';
            claveAdmi[i] = numero;
        }
        fin.close();
        for(int i = 0; i < tam; i++){
            if(claveAdmi[i] != codificado[i]){
                return false;
            }
        }
        return true;
    }

}

void cambiarClaveAdmi(string clave){
    int tam = clave.size() * 8;
    int bina[tam];
    int codificado[tam];
    int *pAlma = bina;
    int *pCod = codificado;
    int semilla = 4;
    binario(clave, pAlma);
    codificacionMetodo1(semilla, tam, pAlma, pCod);
    ofstream fout;
    fout.open("Sudo.txt");
    for(int i = 0; i < tam; i++){
        fout << codificado[i];
    }
    fout.close();
}

