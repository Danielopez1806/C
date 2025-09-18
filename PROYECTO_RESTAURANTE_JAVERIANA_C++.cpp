#include<iostream>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;

// Estructura para Ingrediente usando solo char[] para todos los campos
struct Ingrediente {
    int codigo;
    char nombre[100];
    float precioUnidad;
    char descripcion[100];
    int inventarioActual;
    int minimoInventario;
};

// Relación entre Ingrediente y Plato
struct IngredientePlato {
    int codigoIngrediente; // código del ingrediente
    int cantidad; // cantidad de unidades de ese ingrediente en el plato
};

// Estructura para Plato
struct Plato {
    int codigo;
    char nombre[50];
    float precioBase;
    IngredientePlato* ingredientes; // arreglo dinámico de ingredientes
    int numIngredientes;
};

// Relación entre Orden y Plato
struct OrdenPlato {
    int codigoPlato;
    int cantidad;
};

// Estructura para Orden
struct Orden {
    int codigo;
    OrdenPlato* platos; // arreglo dinámico de platos en la orden
    int numPlatos;
    float valor;
};



void agregaringrediente(Ingrediente*& ingredientes, int& totalIngredientes) {
    char nombre_archivo[100];
    cout << "Ingrese el nombre del archivo para guardar los ingredientes (debe ser el archivo de formato .txt) " << endl;
    cin >> nombre_archivo;
    ofstream archivo(nombre_archivo, ios::app);
    int numingredientes;
    cout << "¿Cuántos ingredientes va a adicionar?: ";
    cin >> numingredientes;
    cin.ignore();

    Ingrediente* temp = new Ingrediente[totalIngredientes + numingredientes];

    // Copiar los anteriores
    for (int i = 0; i < totalIngredientes; ++i) {
        *(temp + i) = *(ingredientes + i);
    }

    // Pedir los nuevos ingredientes
    for (int i = 0; i < numingredientes; ++i) {
        cout << "Ingresa el codigo del ingrediente " << (totalIngredientes + i + 1) << ": ";
        cin >> (temp + totalIngredientes + i)->codigo;
        cin.ignore();
        cout << "Ingresa el nombre del ingrediente " << (totalIngredientes + i + 1) << ": ";
        cin.getline((temp + totalIngredientes + i)->nombre, 100);
        cout << "Ingresa el precio por unidad del ingrediente " << (totalIngredientes + i + 1) << ": ";
        cin >> (temp + totalIngredientes + i)->precioUnidad;
        cin.ignore();
        cout << "Ingresa la descripcion del ingrediente " << (totalIngredientes + i + 1) << ": ";
        cin.getline((temp + totalIngredientes + i)->descripcion, 100);
        cout << "Ingresa el inventario actual del ingrediente " << (totalIngredientes + i + 1) << ": ";
        cin >> (temp + totalIngredientes + i)->inventarioActual;
        cin.ignore();
        cout << "Ingresa el minimo inventario del ingrediente " << (totalIngredientes + i + 1) << ": ";
        cin >> (temp + totalIngredientes + i)->minimoInventario;
        cin.ignore();
    }
    archivo << "#código--nombre----precioUnitario---descripciónUnidad---inventario---mínimo" << endl;
    // Guardar en archivo respetando el formato con asteriscos
    for (int i = 0; i < numingredientes; i++) {
        archivo <<(temp + totalIngredientes + i)->codigo<<"   ";
        archivo <<"*"<< (temp + totalIngredientes + i)->nombre<<"   ";
        archivo <<"*"<< (temp + totalIngredientes + i)->precioUnidad<<"   "; 
        archivo <<"*"<< (temp + totalIngredientes + i)->descripcion<<"   ";
        archivo <<"*"<< (temp + totalIngredientes + i)->inventarioActual<<"   ";
        archivo <<"*"<< (temp + totalIngredientes + i)->minimoInventario<<"   ";
        archivo << endl;
    }
    
    delete[] ingredientes;
    ingredientes = temp;
    totalIngredientes += numingredientes;
    cout << "Ingredientes agregados correctamente" << endl;
    archivo.close();
}

    void agregarPlato(Plato*& platos, int& totalPlatos, Ingrediente* ingredientes, int totalIngredientes){

        char nombre_archivo[100];
        cout<<"Ingrese el nombre del archivo para guardar los platos (debe ser el archivo de formato .txt) "<<endl;
        cin>>nombre_archivo;
        ofstream archivo(nombre_archivo, ios::app);
        int numplatos;
        cout << "¿Cuántos platos va a adicionar?: ";
        cin >> numplatos;
        Plato* temp = new Plato[totalPlatos + numplatos];
        // Copiar los anteriores
        for (int i = 0; i < totalPlatos; i++) {
            *(temp + i) = *(platos + i);
        }
        // Pedir los nuevos platos
        for (int i = 0; i < numplatos; i++) {
            cout << "Ingresa el codigo del plato " << (totalPlatos + i + 1) << ": ";
            cin >> (temp + totalPlatos + i)->codigo;
            cout << "Ingresa el nombre del plato " << (totalPlatos + i + 1) << ": ";
            cin.getline((temp + totalPlatos + i)->nombre, 50);
            cin.ignore();
            cout << "¿Cuántos ingredientes tiene el plato " << (totalPlatos + i + 1) << "?: ";
            cin >> (temp + totalPlatos + i)->numIngredientes;
            cin.ignore();
            (temp + totalPlatos + i)->ingredientes = new IngredientePlato[(temp + totalPlatos + i)->numIngredientes];
            for(int j = 0; j < (temp + totalPlatos + i)->numIngredientes; j++) {
                agregarIngredientePlato((temp + totalPlatos + i)->ingredientes, j, ingredientes, totalIngredientes);
            }
        }
        for(int i = 0; i < numplatos; i++) {
            archivo << "#plato" << endl;
            archivo << "#código------nombre------------" << endl;
            archivo << (temp + totalPlatos + i)->codigo << "   ";
            archivo << "*" << (temp + totalPlatos + i)->nombre << "   ";
            archivo <<" # ingredientes"<< endl;
            for(int j = 0; j < (temp + totalPlatos + i)->numIngredientes; j++) {
                archivo << "" << (((temp + totalPlatos + i)->ingredientes) + j)->codigoIngrediente << "   ";
                archivo << "" << (((temp + totalPlatos + i)->ingredientes) + j)->cantidad << "   "<<endl;
            }
            archivo << "0"<<endl; // Indicador de fin de ingredientes
            
        }
        archivo<<"#fin"<<endl; // Indicador de fin de platos
        delete[] platos;  
        platos = temp;
        totalPlatos += numplatos;
        cout << "Platos agregados correctamente" << endl;
        archivo.close();
}

// Función para agregar un IngredientePlato a un plato
void agregarIngredientePlato(IngredientePlato* arreglo, int posicion, Ingrediente* ingredientes, int totalIngredientes) {
    bool existe = false;
    int codigoIngresado;
    do {
        cout << "Ingresa el código del ingrediente " << (posicion + 1) << ": ";
        cin >> codigoIngresado;
        cin.ignore();
        // Buscar si existe en el arreglo de ingredientes
        for (int i = 0; i < totalIngredientes; i++) {
            if (codigoIngresado == (ingredientes + i)->codigo) {
                existe = true;
                (arreglo + posicion)->codigoIngrediente = codigoIngresado;
                break;
            }
        }
        if (!existe) {
            cout << "Código no válido. Intente de nuevo.\n";
        }
    } while (!existe);
    cout << "Ingresa la cantidad de ese ingrediente en el plato: ";
    cin >> (arreglo + posicion)->cantidad;
    cin.ignore();
}

float calcularPrecio(Plato& plato, Ingrediente* ingredientes, int totalIngredientes) {
    float precioTotal = plato.precioBase;
    for (int i = 0; i < plato.numIngredientes; i++) {
        int codigoIngrediente = ((plato.ingredientes) + i)->codigoIngrediente;
        int cantidad = ((plato.ingredientes) + i)->cantidad;
        // Buscar el ingrediente por su código
        for (int j = 0; j < totalIngredientes; ++j) {
            if (((ingredientes + j)->codigo) == codigoIngrediente) {
                precioTotal += ((ingredientes + j)->precioUnidad) * cantidad;
                break;
            }
        }
    }
    return precioTotal;
}


int main() {
    Ingrediente* ingredientes = nullptr;
    int totalIngredientes = 0;
    Plato* platos = nullptr;
    int totalPlatos = 0;
    int numOrden = 1000;
    // Para liberar memoria de órdenes
    Orden* ordenes = nullptr;
    int totalOrdenes = 0;
    while(true){
    cout<<"Restaurante Javedelicia"<<endl;
    cout<<"opción 1: agregar ingredientes al sistema"<<endl;
    cout<<"opción 2: agregar platos al sistema"<<endl;
    cout<<"opción 3: mostrar el menu del restaurante"<<endl;
    cout<<"opción 4: Agregar una orden al sistema"<<endl;
    cout<<"opción 5: mostrar los tres platos mas solicitados"<<endl;
    cout<<"opción 6: mostrar tres platos mas rentables"<<endl;
    cout<<"opción 7: salir"<<endl;
    int opcion;
    cin>>opcion;  
        switch(opcion){
            case 1: {
                agregaringrediente(ingredientes, totalIngredientes);
                break;
            }
            case 2: {
                agregarPlato(platos, totalPlatos, ingredientes, totalIngredientes);
                break;
            }
            case 3: {
                cout << "--MENU DEL RESTAURANTE: lista de platos ofrecidos:" << endl;
                cout << left << setw(10) << "código" << setw(20) << "nombre" << setw(10) << "precio" << endl;
                for(int i = 0; i < totalPlatos; i++) {
                    cout << left << setw(10) << (platos + i)->codigo
                    << setw(20) << (platos + i)->nombre
                    << setw(10) << fixed << setprecision(2)
                    << calcularPrecio(*(platos + i), ingredientes, totalIngredientes) << endl;
                }
                break;
            }
            case 4: {
                // Crear la nueva orden y asignar el código consecutivo
                Orden orden;
                orden.codigo = numOrden;
                cout << "--AGREGAR ORDEN :  " << orden.codigo << endl;
                cout << "--¿Cuántos tipos de platos van en la orden? :  " << endl;
                int numTiposPlatos;
                cin >> numTiposPlatos;
                bool platosValidos = true;
                int* codigosPlato = new int[numTiposPlatos];
                int* cantidadesPlato = new int[numTiposPlatos];
                cout << "--Indique para cada tipo de plato: codigo  cantidad( de unidades/ proporciones)" << endl;
                // Leer todos los platos y cantidades
                for(int i = 0; i < numTiposPlatos; i++) {
                    cin >> *(codigosPlato + i) >> *(cantidadesPlato + i);
                }
                // Validar existencia de todos los platos y guardar índices
                int* indicesPlatos = new int[numTiposPlatos];
                for(int i = 0; i < numTiposPlatos; i++) {
                    bool existe = false;
                    for (int j = 0; j < totalPlatos; j++) {
                        if (*(codigosPlato + i) == (platos + j)->codigo) {
                            *(indicesPlatos + i) = j;
                            existe = true;
                            break;
                        }
                    }
                    if (!existe) {
                        platosValidos = false;
                        break;
                    }
                }
                if (!platosValidos) {
                    cout << "Error: Uno o más códigos de plato no son válidos. La orden no se puede procesar." << endl;
                    delete[] codigosPlato;
                    delete[] cantidadesPlato;
                    delete[] indicesPlatos;
                    break;
                }
                // Simular descuento de inventario en un arreglo temporal
                int* inventarioTemp = new int[totalIngredientes];
                for (int i = 0; i < totalIngredientes; i++) {
                    *(inventarioTemp + i) = (ingredientes + i)->inventarioActual;
                }
                bool inventarioSuficiente = true;
                for (int i = 0; i < numTiposPlatos; i++) {
                    Plato* platoActual = (platos + *(indicesPlatos + i));
                    for (int j = 0; j < platoActual->numIngredientes; j++) {
                        int codigoIng = (platoActual->ingredientes + j)->codigoIngrediente;
                        int cantidadIng = (platoActual->ingredientes + j)->cantidad * (*(cantidadesPlato + i));
                        bool encontrado = false;
                        for (int k = 0; k < totalIngredientes; k++) {
                            if ((ingredientes + k)->codigo == codigoIng) {
                                if (*(inventarioTemp + k) >= cantidadIng) {
                                    *(inventarioTemp + k) -= cantidadIng;
                                } else {
                                    inventarioSuficiente = false;
                                }
                                encontrado = true;
                                break;
                            }
                        }
                        if (!encontrado) {
                            inventarioSuficiente = false;
                        }
                    }
                }
                if (!inventarioSuficiente) {
                    cout << "Error: No hay inventario suficiente para satisfacer la orden completa. La orden no será aceptada." << endl;
                    delete[] codigosPlato;
                    delete[] cantidadesPlato;
                    delete[] indicesPlatos;
                    delete[] inventarioTemp;
                    break;
                }
                // Si todo es válido, aplicar el descuento real
                for (int i = 0; i < totalIngredientes; i++) {
                    (ingredientes + i)->inventarioActual = *(inventarioTemp + i);
                }
                // Calcular y guardar el valor total de la orden
                float valorOrden = 0;
                for (int i = 0; i < numTiposPlatos; i++) {
                    Plato* platoActual = (platos + *(indicesPlatos + i));
                    valorOrden += calcularPrecio(platoActual, ingredientes, totalIngredientes) * ((cantidadesPlato + i));
                }
                orden.valor = valorOrden;
                orden.numPlatos = numTiposPlatos;
                orden.platos = new OrdenPlato[numTiposPlatos];
                for (int i = 0; i < numTiposPlatos; i++) {
                    (orden.platos + i)->codigoPlato = *(codigosPlato + i);
                    (orden.platos + i)->cantidad = *(cantidadesPlato + i);
                }
                // Guardar la orden en el arreglo dinámico de órdenes
                Orden* tempOrdenes = new Orden[totalOrdenes + 1];
                for (int i = 0; i < totalOrdenes; i++) {
                    *(tempOrdenes + i) = *(ordenes + i);
                }
                *(tempOrdenes + totalOrdenes) = orden;
                delete[] ordenes;
                ordenes = tempOrdenes;
                totalOrdenes++;
                cout << "El valor de la orden es $ " << orden.valor << endl;
                delete[] codigosPlato;
                delete[] cantidadesPlato;
                delete[] indicesPlatos;
                delete[] inventarioTemp;
                numOrden++;
                break;
            }
            case 5:
                if (totalPlatos == 0 || totalOrdenes == 0) {
                    cout << "No hay datos suficientes para mostrar platos solicitados." << endl;
                    break;
                }
                // Acumular solicitudes por plato
                int* solicitudes = new int[totalPlatos];
                for (int i = 0; i < totalPlatos; i++)
                 *(solicitudes + i) = 0;
                for (int i = 0; i < totalOrdenes; i++) {
                    for (int j = 0; j < (ordenes + i)->numPlatos; j++) {
                        int codigo = ((ordenes + i)->platos + j)->codigoPlato;
                        int cantidad = ((ordenes + i)->platos + j)->cantidad;
                        for (int k = 0; k < totalPlatos; k++) {
                            if ((platos + k)->codigo == codigo) {
                                *(solicitudes + k) += cantidad;
                                break;
                            }
                        }
                    }
                }
                // Arreglo de índices para ordenar
                int* indices = new int[totalPlatos];
                for (int i = 0; i < totalPlatos; i++) *(indices + i) = i;
                // Ordenar índices por solicitudes (burbuja descendente)
                for (int i = 0; i < totalPlatos-1; i++) {
                    for (int j = 0; j < totalPlatos-1-i; j++) {
                        if (*(solicitudes + *(indices + j + 1)) > *(solicitudes + *(indices + j))) {
                            int tmp = *(indices + j);
                            *(indices + j) = *(indices + j + 1);
                            *(indices + j + 1) = tmp;
                        }
                    }
                }
                cout << "--PLATOS MÁS SOLICITADOS" << endl;
                cout << left << setw(10) << "Código" << setw(20) << "Nombre" << setw(10) << "Solicitudes" << endl;
                for (int i = 0; i < 3; i++) {
                    if (i < totalPlatos) {
                        int posicion = *(indices + i);
                        if (*(solicitudes + posicion) > 0) {
                            cout << left << setw(10) << (platos + posicion)->codigo
                                << setw(20) << (platos + posicion)->nombre
                                << setw(10) << *(solicitudes + posicion) << endl;
                        }
                    }
                }
                delete[] solicitudes;
                delete[] indices;
                break;
            case 6: {
                if (totalPlatos == 0 || totalOrdenes == 0) {
                    cout << "No hay datos suficientes para mostrar platos rentables." << endl;
                    break;
                }
                // Calcular total de ventas por plato
                float* ventas = new float[totalPlatos];
                for (int i = 0; i < totalPlatos; i++){
                *(ventas + i) = 0;   // Inicializar a 0 las ventas
                } 
                for (int i = 0; i < totalOrdenes; i++) {
                    for (int j = 0; j < (ordenes + i)->numPlatos; j++) {
                        int codigo = ((ordenes + i)->platos + j)->codigoPlato;
                        int cantidad = ((ordenes + i)->platos + j)->cantidad;
                        for (int k = 0; k < totalPlatos; k++) {
                            if ((platos + k)->codigo == codigo) {
                                (ventas + k) += calcularPrecio((platos + k), ingredientes, totalIngredientes) * cantidad;
                                break;
                            }
                        }
                    }
                }
                // Arreglo de índices para ordenar
                int* indices = new int[totalPlatos];
                for (int i = 0; i < totalPlatos; i++) *(indices + i) = i;
                // Ordenar índices por ventas (burbuja descendente)
                for (int i = 0; i < totalPlatos-1; i++) {
                    for (int j = 0; j < totalPlatos-1-i; j++) {
                        if (*(ventas + *(indices + j + 1)) > *(ventas + *(indices + j))) {
                            int tmp = *(indices + j);
                            *(indices + j) = *(indices + j + 1);
                            *(indices + j + 1) = tmp;
                        }
                    }
                }
                cout << "--PLATOS MAS RENTABLES:" << endl;
                cout << left << setw(10) << "codigo" << setw(20) << "nombre" << setw(15) << "total de ventas" << endl;
                for (int i = 0; i < 3; i++) {
                    if (i < totalPlatos) {
                        int pos = *(indices + i);
                        if (*(ventas + pos) > 0) {
                            cout << left << setw(10) << (platos + pos)->codigo
                                << setw(20) << (platos + pos)->nombre
                                << setw(15) << fixed << setprecision(0) << *(ventas + pos) << endl;
                        }
                    }
                }
                delete[] ventas;
                delete[] indices;
                break;
            }
                if (totalPlatos == 0) {
                    cout << "No hay datos suficientes para mostrar platos rentables." << endl;
                    break;
                }
                
                
            case 7:
                // Liberar memoria de ingredientes
                delete[] ingredientes;
                // Liberar memoria de platos y sus ingredientes
                for (int i = 0; i < totalPlatos; i++) {
                    delete[] (platos + i)->ingredientes;
                }
                delete[] platos;
                // Liberar memoria de órdenes y sus platos
                for (int i = 0; i < totalOrdenes; i++) {
                    delete[] (ordenes + i)->platos;
                }
                delete[] ordenes;
                return 0;
            default:
                cout<<"Opción no válida"<<endl;
        }   
    }
}
