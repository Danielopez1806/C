#include <iostream>
#include <string>
#include <istream>
using namespace std;

//Prueba



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
		ingrediente = redimensionarIngrediente(ingrediente, n, n + 1);

		Ingrediente* ingrediente_agregar = new Ingrediente;

		cin.ignore();

		cout << "=========Ingrediente agregado numero: " << i + 1 << endl;
		cout << "Codigo: ";
		getline(cin, ingrediente_agregar->codigo_ingrediente);

		cout << "Precio Unitario: ";
		cin >> ingrediente_agregar->precio_unitario;

		cin.ignore();

		cout << "Descripcion unidad: ";
		getline(cin, ingrediente_agregar->descripcion_unidad);

		cout << "Inventario: ";
		cin >> ingrediente_agregar->inventario;

		cout << "Inventario Minimo";
		cin >> ingrediente_agregar->inventario_minimo;



		*(ingrediente + n) = ingrediente_agregar;
		n++;
	}

}


#pragma endregion Agregar_Platos_Ingredientes


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
		cout << "opcion 3 : mostrar el menú del restaurante" << endl;
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
		/*case 2:
		{}
		case 3:
		{}
		case 4:
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
