#include <iostream>
#include <fstream> 
#include <limits>
#include<cstring>


using namespace std;

struct Car{
	char placa[6];
	char marca[15];
	char modelo[20];
	int year;
	char color[15];
	bool tipo;//true=propio false=consigado
	long valor;
	bool estado;
};

void menu(){
	cout<<"Gestor de Consignataria\n";
	cout<<"Selecciona lo que quieras hacer\n";
	cout<<"1. Registrar vehiculo que ingresa\n";
	cout<<"2. Consulta existencias\n";
	cout<<"3. Actualizar o modiicar la informacion de un vehiculo\n";
	cout<<"4. Eliminar o activvar un vehiculo\n";
	cout<<"5. Salir\n";
	
}


void registrar(){
	Car car;
	ofstream file("carro.dat", ios::binary | ios::app);
    if (!file) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }
    cout<<"Ingresa la placa del vehiculo(debe ser unica)\n";
	cin.getline(car.placa, 6);
	cout<<"Ingresa la marca del vehiculo\n";
	cin.getline(car.marca, 15);
	cout<<"Ingresa el modelo del vehiculo\n";
	cin.getline(car.modelo, 20);
	cout<<"Ingresa el año del modelo del vehiculo\n";
	cin>>car.year;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<"Ingresa el color del vehiculo\n";
	cin.getline(car.color, 15);
	cout<<"Ingresa el tipo del vehiculo(1 para propio, 0 para Consignado)\n";
	cin>>car.tipo;
	cout<<"Ingresa el valor del vehiculo\n";
	cin>>car.valor;
	car.estado=1;
	file.write(reinterpret_cast<const char*>(&car), sizeof(Car));
	file.close();
	cout<<"Vehiculo ingresado correctamente\n";
	
}


void printCar(Car car){
	cout<<"Placa: "<<car.placa;
	cout<<"Marca: "<<car.marca;
	cout<<"Modelo: "<<car.modelo;
	cout<<"anho de lanzamiento: "<<car.year;
	cout<<"Color: "<<car.color;
	cout<<"Tipo: "<<car.modelo?"Propio":"Consignado";
	cout<<"Valor: "<<car.valor;
	cout<<"Estado: "<<car.estado?"Activo":"Inactivo";
}
void consultarMarca(){
	Car car;
	char marca[15];
	ifstream file("carro.dat", ios::binary);
    if (!file) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }
    cout<<"Ingresa la Marca del vehiculo";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(marca,15);
	 while (file.read(reinterpret_cast<char*>(&car), sizeof(Car))) {
        if (strcmp(car.marca, marca) == 0) {
            printCar(car);
        }
    }
}
void consultar(){
	int x;
	cout<<"Ingresa el tipo de consulta que vas a realizar\n";
	cout<<"1. Marca ";
	cout<<"2. Rango de precio";
	cout<<"3. Tipo";
	cin>>x;
	switch(x){
		case 1: consultarMarca();
	}
}
main(){
	int x;
	do{
		menu();
		cin>>x;
		switch(x){
			case 1:registrar();break;
			case 2:consultar();break;
		}
	} while (x!=5);
}
