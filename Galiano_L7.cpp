// Tenemos 3 arreglos los cuales se iran llenando en base a nuestra funcion leerCaracteres(), la cual extrae los caracteres de los archivos previamente abiertos con nuestra funcion abrirArchivo. Tenemos nuestra
// funcion validarLargo() y la funcion avisarMenosCaracteres() pero no soy tan relevantes para la resolucion.

// Una vez los arreglos 1, 2 y 3 esten con su respectivo contenido, se crea un nuevo arreglo el cual corresponde a la union del arreglo 1 y el arreglo 2. Para calcular esta union utilizamos la formula que nos
// indica que la union entre dos conjuntos es el primer conjunto + el segundo - la interseccion de estos 2. Para eso utilizamos un bucle for para llenar nuestro nuevo arreglo con el total del primer arreglo
// y luego le agregamos el segundo arreglo nuevamente con un for pero evaluando este si es que el caracter ya se encontraba dentro, siendo el caso donde si es si, se omite este caracter permitiendonos asi eliminar
// la interseccion de estos conjuntos. Luego una vez terminamos con la union utilizamos un for repitiendo el mismo paso anterior, donde evaluamos la interseccion de 2 arreglos, pero con el tercer arreglo y el arreglo
// momentaneo que creamos. Agregando el resultado de este for a un nuevo arreglo que denominamos final.

// Para evitar que se repitan los datos de la interseccion utilizaremos ultimo for el cual nos cambia una bandera en caso de ya encontrarse el caracter evaluado dentro del arreglo final


#include <iostream>
#include <fstream>

#define Largo 30
#define MAX 5000
#define ULTRA 10000
#define ULTRA_PLUS 15000

using namespace std;

// Declaración de funciones
int abrirArchivo(ifstream& archivo, char nombre[]); // Esta funcion se encarga de pedir el nombre del archivo para poder abrirlo, tambien evalua si es que el archivo no se encuentra
void validarLargo (int& L); // Esta funcion se encarga de pedir un L correspondiente a la cantidad de caracteres a ingresar en los arreglos (entre 500 y 5000)
void leerCaracteres(ifstream& archivo, char arreglo[], int& cantidad_caracteres, int L, int& fin); // Esta funcion nos lee caracter a caracter del archivo y lo ingresa al arreglo correspondiente
void avisarMenosCaracteres(int cantidad_caracteres, int L); // Esta funcion avisa si es que el texto tenia menos de los L caracteres solicitados anteriormente
void mostrarArreglos(char arreglo[], int i, int fin); // Se encarga de mostrar el contenido de el arreglo recibido

// Funcion main
int main(){
    char nombre1[Largo], nombre2[Largo], nombre3[Largo]; // Aca se define el maximo de caracteres para el nombre de los archivos
    char caracter; // Este vendria a ser un caracter el cual luego iremos extrayendo de los archivos
    int cantidad_caracteres = 0, L = 0, i = 0, j = 0, k = 0; // Contador de caracteres ingresados | Cantidad de caracteres a extraer | Variables para bucles for
    char arreglo1[MAX], arreglo2[MAX], arreglo3[MAX]; // Los 3 arreglos principales limitados a un maximo
    int fin1 = 0, fin2 = 0, fin3 = 0, nueva_union = 0, contador; // Indice final de cada arreglo (incluyendo arreglo union y arreglo final)
    char arreglo_union[ULTRA], arreglo_final[ULTRA_PLUS]; // Arreglo donde se guarda la union de 1 y 2 | Arreglo final con la interseccion de 3 y la union de los 2 primeros
    bool repetido = false, ya_esta = false; // Booleanos utilizados para la evaluacion de repetidos
    ifstream archivo1, archivo2, archivo3; // Extraccion de datos en archivos / Archivos como tal

    if (!abrirArchivo(archivo1, nombre1)) return 0;
    validarLargo(L);
    leerCaracteres(archivo1, arreglo1, cantidad_caracteres, L, fin1);
    avisarMenosCaracteres(cantidad_caracteres, L);
    archivo1.close();
    cantidad_caracteres = 0;
    L = 0;

    if (!abrirArchivo(archivo2, nombre2)) return 0;
    validarLargo(L);
    leerCaracteres(archivo2, arreglo2, cantidad_caracteres, L, fin2);
    avisarMenosCaracteres(cantidad_caracteres, L);
    archivo2.close();
    cantidad_caracteres = 0;
    L = 0;

    if (!abrirArchivo(archivo3, nombre3)) return 0;
    validarLargo(L);
    leerCaracteres(archivo3, arreglo3, cantidad_caracteres, L, fin3);
    avisarMenosCaracteres(cantidad_caracteres, L);
    archivo3.close();
    cantidad_caracteres = 0;
    L = 0;

    // Aca se trabaja la union y la interseccion de los arreglos
    nueva_union = fin1 + 1;

    for(i; i < fin1; i++){
        arreglo_union[i] = arreglo1[i];
        //cout<<arreglo_union[i];
    }
    i=0;

    for (i; i<fin2; i++){
        repetido = false;
        for (j = 0; j<fin1; j++){
            if (arreglo_union[j] == arreglo2[i]){
                repetido = true;
                break;
            }
        }
        if (!repetido) {
            arreglo_union[nueva_union] = arreglo2[i];
            nueva_union++;
        }
    }

    i = 0;
    j = 0;

    contador = 0;
    for (i; i<fin3; i++){
        repetido = false;
        for (j = 0; j<nueva_union; j++){
            if (arreglo_union[j] == arreglo3[i]){
                repetido = true;
                break;
            }
        }
        if (repetido) {
            ya_esta = false;
            for (k = 0; k < contador; k++){
                if (arreglo_final[k] == arreglo3[i]){
                    ya_esta = true;
                    break;
                }
            }

            if (!ya_esta){
                arreglo_final[contador] = arreglo3[i];
                contador++;
            }
        }
    }

    i = 0;
    j = 0;

    // Aca se muestran los arreglos con su contenido
    cout<<endl<<"El primer arreglo tiene los siguientes caracteres: ";
    mostrarArreglos(arreglo1, i, fin1);
    cout<<endl<<endl<<endl<<"El segundo arreglo tiene los siguientes caracteres: ";
    mostrarArreglos(arreglo2, i, fin2);
    cout<<endl<<endl<<endl<<"El tercer arreglo tiene los siguientes caracteres: ";
    mostrarArreglos(arreglo3, i, fin3);
    cout<<endl<<endl<<endl<<"La interseccion entre el tercer arreglo y la union del primero con el seguindo seria: ";
    mostrarArreglos(arreglo_final, i, contador);

    return 0;
}

// Todas las funciones
int abrirArchivo(ifstream& archivo, char nombre[]) {
    cout<<"Ingrese el nombre del archivo: ";
    cin>>nombre;
    archivo.open(nombre);
    if (archivo.fail()){
        cout<<endl<<endl<<"Archivo no existe";
        return 0;
    }
    return 1;
}; // Abre archivos

void validarLargo (int& L) {
    do {
        cout<<"Ingrese el numero de caracteres que desea ingresar al arreglo (500 | 5000): ";
        cin>>L;
    } while ((L < 500) || (L > 5000));
}; // Valida el largo de caracteres

void leerCaracteres(ifstream& archivo, char arreglo[], int& cantidad_caracteres, int L, int& fin){
    char caracter;
    while ((cantidad_caracteres < L) && archivo.get(caracter)) {
        arreglo[cantidad_caracteres] = caracter;
        //cout<<arreglo[cantidad_caracteres];
        cantidad_caracteres++;
    }
    fin = cantidad_caracteres;
};

void avisarMenosCaracteres(int cantidad_caracteres, int L){
    if (cantidad_caracteres < L) {
        cout<<endl<<"La cantidad de caracteres solicitada era mayor a la cantidad dentro del archivo"<<endl<<"El arreglo se lleno con "<<(cantidad_caracteres-1)<<" caracteres"<<endl<<endl;
    }
};

void mostrarArreglos(char arreglo[], int i, int fin){
    for (i; i<fin; i++){
        cout<<arreglo[i];
    }
    cout<<endl;
}
