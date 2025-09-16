#include <iostream>
#include <string>
#include <istream>
using namespace std;

#pragma region Estructuras
struct Ingrediente {

	string codigo_ingrediente;
	string nombre_ingrediente;
	int precio_unitario = 0;
	string descripcion_unidad;
	int inventario = 0;
	int inventario_minimo = 0;
};

struct Plato_Ingrediente
{
	Ingrediente* ingrediente;
	int cantidad = 0;

};

struct Plato {
	int codigo = 0;
	string nombre;
	double precio = 0;
	Plato_Ingrediente* ingredientes;
	int num_Ingredientes = 0;
	int vendidos = 0;
};

struct OrdenPlato
{
	Plato* plato;
	int cantidadplato = 0;

};

struct Orden
{
	int codigo = 0;
	OrdenPlato* platos;
	int numero_de_platos = 0;
	double total = 0;

};

#pragma endregion Estructuras

#pragma region Redimension
Plato** redimensionarPlato(Plato** arreglo, int tam, int nuevo_tam) {
	Plato** Nuevo_Plato = new Plato * [nuevo_tam];

	int limite = (tam < nuevo_tam) ? tam : nuevo_tam;
	for (int i = 0; i < limite; i++) {
		*(Nuevo_Plato + i) = *(arreglo + i);
	}

	delete[] arreglo;
	return Nuevo_Plato;
}

Ingrediente** redimensionarIngrediente(Ingrediente** arreglo, int tam, int nuevo_tam) {
	Ingrediente** Nuevo_Ingrediente = new Ingrediente * [nuevo_tam];

	int limite = (tam < nuevo_tam) ? tam : nuevo_tam;
	for (int i = 0; i < limite; i++) {
		*(Nuevo_Ingrediente + i) = *(arreglo + i);
	}

	delete[] arreglo;
	return Nuevo_Ingrediente;
}

Orden** redimensionarOrden(Orden** arreglo, int tam, int nuevo_tam) {
	Orden** Nueva_Orden = new Orden * [nuevo_tam];

	int limite = (tam < nuevo_tam) ? tam : nuevo_tam;
	for (int i = 0; i < limite; i++) {
		*(Nueva_Orden + i) = *(arreglo + i);
	}

	delete[] arreglo;
	return Nueva_Orden;
}




#pragma endregion Redimension


#pragma region Agregar_Platos_Ingredientes
void AgregarIngredientes(Ingrediente**& ingrediente, int& n)
{
	//Aqui se agregan los ingredientes
	int cantidad = 0;
	cout << "cuantos ingredientes desea agregar ?" << endl;
	cin >> cantidad;



	for (int i = 0; i < cantidad; i++)
	{
		//redimensionar los ingredientes para agregarlos dinamicamente
		ingrediente = redimensionarIngrediente(ingrediente, n, n + 1);

		Ingrediente* ingrediente_agregar = new Ingrediente;

		cin.ignore();
//agregar los ingredietnes con los datos requeridos en el enunciado
		cout << "=========Ingrediente agregado numero: " << i + 1 << endl;
		cout << "Codigo: ";
		getline(cin, ingrediente_agregar->codigo_ingrediente);

		cout <<"Nombre del plato: " ;
		getline(cin, ingrediente_agregar-> nombre_ingrediente);

		cout << "Precio Unitario: ";
		cin >> ingrediente_agregar->precio_unitario;

		cin.ignore();

		cout << "Descripcion unidad: ";
		getline(cin, ingrediente_agregar->descripcion_unidad);

		cout << "Inventario: ";
		cin >> ingrediente_agregar->inventario;

		cout << "Inventario Minimo: ";
		cin >> ingrediente_agregar->inventario_minimo;



		*(ingrediente + n) = ingrediente_agregar;
		n++;
	}

}

void AgregarPlatos(Plato**& platos, int& numPlatos, Ingrediente** ingredientes, int numIngredientes) {
	if (numIngredientes == 0) {
		cout << "No puede crear platos sin ingredientes registrados primero." << endl;
		return;
	}

	int cantidad;
	cout << "Cuantos platos desea agregar? ";
	cin >> cantidad;

	for (int i = 0; i < cantidad; i++) {
//redimensionar platos, para agregar los platos que yo quieraa
		platos = redimensionarPlato(platos, numPlatos, numPlatos + 1);

		Plato* nuevoPlato = new Plato;

//llenar los datos del plato de acuerdo al enunciado
		cin.ignore();
		cout << " Plato No#" << (numPlatos + 1) << " =========" << endl;
		cout << "Codigo del plato: ";
		cin >> nuevoPlato->codigo;

		cin.ignore();
		cout << "Nombre del plato: ";
		getline(cin, nuevoPlato->nombre);

		cout << "Precio del plato: ";
		cin >> nuevoPlato->precio;

		cout << "Cuantos ingredientes tendra este plato?: ";
		cin >> nuevoPlato->num_Ingredientes;

		nuevoPlato->ingredientes = new Plato_Ingrediente[nuevoPlato->num_Ingredientes];

		for (int i = 0; i < nuevoPlato->num_Ingredientes; i++) {
			cout << endl << "Seleccione el ingrediente No#" << i + 1 << " de la lista:" << endl;
			for (int j = 0; j < numIngredientes; j++) {
				cout << j + 1 << ". " << ingredientes[j]->nombre_ingrediente << " (" << ingredientes[j]->codigo_ingrediente << ")" << endl;
			}

			int opcionIng;
			cout << "Ingrese el numero del ingrediente: ";
			cin >> opcionIng;

			if (opcionIng < 1 || opcionIng > numIngredientes) {
				cout << "Ingrediente invalido, se asignara el primero." << endl;
				opcionIng = 1;
			}

			nuevoPlato->ingredientes[i].ingrediente = ingredientes[opcionIng - 1];

			cout << "Cantidad necesaria de este ingrediente: ";
			cin >> nuevoPlato->ingredientes[i].cantidad;
		}

		*(platos + numPlatos) = nuevoPlato;
		numPlatos++;
	}
}

#pragma endregion Agregar_Platos_Ingredientes

#pragma region MostrarMenu

void MostrarMenu(Plato** platos, int numPlatos)
{
	if (numPlatos == 0) {
		cout << "No hay platos registrados en el sistema. " << endl;
		return;
	}
	cout << "===== MENU DEL RESTAURANTE =====" << endl;
	for (int i = 0; i < numPlatos; i++) {
		Plato* p = *(platos + i);
		cout << "--------------------------------" << endl;
		cout << "Codigo: " << p->codigo << endl;
		cout << "Nombre: " << p->nombre << endl;
		cout << "Precio: $" << p->precio << endl;
		cout << "Ingredientes: " << endl;

		for (int j = 0; j < p->num_Ingredientes; j++) {
			Plato_Ingrediente platoIngredientes = p->ingredientes[j];
			cout << "   - " << platoIngredientes.ingrediente->nombre_ingrediente
				<< " (" << platoIngredientes.cantidad << " " << platoIngredientes.ingrediente->descripcion_unidad << ")\n";
		}
	}
	cout << "===============================" << endl;






}




#pragma endregion MostrarMenu

#pragma region Main
int main()
{
	Ingrediente** ingredientes = nullptr;
	int num_ingredientes = 0;

	Plato** platos = nullptr;
	int numero_platos = 0;


	int opcion = 0;
	do
	{

		cout << "RESTAURANTE JAVEREST" << endl;
		cout << "opcion 1: agregar ingredientes al sistema" << endl;
		cout << "opcion 2 : agregar platos al sistema" << endl;
		cout << "opcion 3 : mostrar el menu restaurante" << endl;
		cout << "opcion 4 : agregar una orden al sistema " << endl;
		cout << "opcion 5 : mostrar los tres platos más solicitados" << endl;
		cout << "opcion 6 : mostrar los tres platos más rentables " << endl;
		cout << "99. Salir" << endl;
		cout << "escriba su opcion: "; cin >> opcion;


		switch (opcion)
		{
		case 1:
		{
			AgregarIngredientes(ingredientes, num_ingredientes);
			break;
		}
		case 2:
		{
			AgregarPlatos(platos, numero_platos, ingredientes, num_ingredientes);
			break;
		}
		case 3:
		{
			MostrarMenu(platos, numero_platos);
			break;

		}
		/*case 4:
		{}
		case 5:
		{}
		case 6:
		{}*/

		case 99:
		{
			cout << "Usted eligio salir";
			break;
		}
		
	} 
} while (opcion != 99);
}
#pragma endregion Main
