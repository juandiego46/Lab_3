#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>
#include "Mis_funciones.h"

using namespace std;


int main()
{
    char opcion;
    char opcionSalir = 'o';
    char opcionUsuarios = 's';
    int n = 1; // numero de usuarios.
    int cedula[n];
    int clave[n];
    int saldo[n];

    while(opcionSalir == 'o'){
        cout << "Si usted es el administrador ingrese la letra 'a': " << endl ;
        cout << "Si usted es usuario ingrese la letra 'u': " << endl ;
        cout << "opcion: "; cin >> opcion;
        if(opcion == 'a'){
            string claveAdmi;
            cout << "Administrador, ingrese su clave: "; cin >> claveAdmi;
            while(claveAdministrador(claveAdmi) == false){
                cout << "Clave incorrecta!, ingrese su clave de nuevo: "; cin >> claveAdmi;
            }
            registroUsuarios(cedula, clave, saldo, n);
            cout << "Desea salir de la aplicacion, ingrese 'i' para si o ingrese 'o' para no: "; cin >> opcionSalir;
        }
        else{
            int nUsuario = 0;
            int ced = 0;
            cout << "Usuario por favor ingrese su numero de cedula: "; cin >> ced;
            for(int i = 0; i < n; i++){
                if(cedula[i] == ced){
                    nUsuario = i;
                    break;
                }
                else{
                    nUsuario++;
                }
            }
            cout << "Desea consular su saldo, ingrese  la letra 's': " << endl;
            cout << "Desea retirar dinero, ingrese la letra 'd': " << endl;
            cout << "opcion: "; cin >> opcionUsuarios;
            if(opcionUsuarios == 's'){
                cout << "Su saldo es: " << "$" << saldo[nUsuario] << endl;
                saldo[nUsuario] = saldo[nUsuario] - 1000;
                cout << "Con el descuento le quedaria en: " << "$" << saldo[nUsuario] << endl;
            }
            else{
                int retiro = 0;
                cout << "Cuanto dinero desea retirar: "; cin >> retiro;
                saldo[nUsuario] = (saldo[nUsuario] - retiro) - 1000;
                cout << "Su dinero actual es: " << "$" << saldo[nUsuario] << endl;
            }

        }
    }

    return 0;
}

