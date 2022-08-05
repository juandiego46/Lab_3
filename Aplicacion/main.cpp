#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>

using namespace std;

bool claveAdministrador(string);

int main()
{
    string claveAdmi;
    cout << "Administrador, ingrese su clave: "; cin >> claveAdmi;
    while(claveAdministrador(claveAdmi) == false){
        cout << "Clave incorrecta!, ingrese su clave de nuevo: "; cin >> claveAdmi;
    }
    return 0;
}

bool claveAdministrador(string intento){
    ifstream fin;
    string claveAdmi;
    fin.open("Sudo.txt");
    if(fin.fail()){
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    while(!fin.eof()){ //Mientras no sea el final del archivo.
        getline(fin,claveAdmi);
        if(claveAdmi == intento){
            return true;
        }
        else{
            return false;
        }
    }
    fin.close();
}
