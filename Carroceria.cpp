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
	cout<<"\nGestor de Consignataria\n";
	cout<<"Selecciona lo que quieras hacer\n";
	cout<<"1. Registrar vehiculo que ingresa\n";
	cout<<"2. Consulta existencias\n";
	cout<<"3. Actualizar o modiicar la informacion de un vehiculo\n";
	cout<<"4. Eliminar o activar un vehiculo\n";
	cout<<"5. Salir\n";
	
}

bool checkPlaca(char placa[6]){
	Car car;
	ifstream file("carro.dat", ios::binary);
    if (!file) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }
    while (file.read(reinterpret_cast<char*>(&car), sizeof(Car))) {
        if (strcmp(car.placa, placa) == 0) {
            return true;
        }
    }
    file.close();
    return false;
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
	if(checkPlaca(car.placa)==0){
		cout<<"La placa del vehiculo ya esta registrada";
		file.close();
		return;
	}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
	cout<<"\nPlaca: "<<car.placa;
	cout<<"\nMarca: "<<car.marca;
	cout<<"\nModelo: "<<car.modelo;
	cout<<"\nanho de lanzamiento: "<<car.year;
	cout<<"\nColor: "<<car.color;
	cout<<"\nTipo: "<<car.modelo?"Propio":"Consignado";
	cout<<"\nValor: "<<car.valor;
	cout<<"\nEstado: "<<car.estado?"Activo":"Inactivo";
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
    	file.close();
}
void consultarPrecio(){
	Car car;
	int min, max;
	ifstream file("carro.dat", ios::binary);
    if (!file) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }
    cout<<"Ingresa el valor minimo del vehiculo";
    cin>>min;
    cout<<"Ingresa el valor maximo del vehiculo";
    cin>>max;
	 while (file.read(reinterpret_cast<char*>(&car), sizeof(Car))) {
        if (car.valor>=min ||car.valor<=max ) {
            printCar(car);
        }
    }
    	file.close();
}

void consultarTipo(){
	Car car;
	bool tipo;
	ifstream file("carro.dat", ios::binary);
    if (!file) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }
    cout<<"Ingresa el tipo del vehiculo(1 para propio, 0 para consignado)";
    cin>>tipo;
	 while (file.read(reinterpret_cast<char*>(&car), sizeof(Car))) {
        if (tipo==car.tipo) {
            printCar(car);
        }
    }
    	file.close();
}
void consultar(){
	int x;
	cout<<"Ingresa el tipo de consulta que vas a realizar\n";
	cout<<"1. Marca 2. Rango de precio 3. Tipo \n";
	cin>>x;
	switch(x){
		case 1: consultarMarca();
		case 2: consultarPrecio();
		case 3:consultarTipo();
	}
}

void modificar(){
	Car car;
	bool ask;
	char placa[6];
	cout<<"Ingresa la placa del vehiculo";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.getline(placa,6);
	fstream file("carro.dat", ios::binary | ios::in | ios::out);
    
    if (!file) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }
     while (file.read(reinterpret_cast<char*>(&car), sizeof(Car))) {
        if (strcmp(car.placa, placa) == 0) {
            cout << "\nProducto encontrado!";
            cout<<"Vas a modificar el tipo o el valor? (1 para valor, 0 para tipo)";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin>>ask;
            if(ask){
            	cout<<"Ingresa el nuevo valor";
            	cin>>car.valor;
            	file.seekp(-static_cast<int>(sizeof(Car)), ios::cur);
            	file.write(reinterpret_cast<const char*>(&car), sizeof(Car));
            	file.close();
            	cout << "Producto modificado con exito." << endl;
			}else{
				cout<<"Ingresa el nuevo tipo(1 para propio, 0 para consignado)";
            	cin>>car.tipo;
            	file.seekp(-static_cast<int>(sizeof(Car)), ios::cur);
            	file.write(reinterpret_cast<const char*>(&car), sizeof(Car));
            	file.close();
            	cout << "Producto modificado con exito." << endl;
			}
        }
    }
}
void eliminar(){
	Car car;
	char placa[6];
	cout<<"Ingresa la placa del vehiculo";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.getline(placa,6);
	fstream file("carro.dat", ios::binary | ios::in | ios::out);
    
    if (!file) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }
    if (strcmp(car.placa, placa) == 0){
        if(car.estado){
        	car.estado=0;
           	file.seekp(-static_cast<int>(sizeof(Car)), ios::cur);
           	file.write(reinterpret_cast<const char*>(&car), sizeof(Car));
           	file.close();
            cout << "Producto desactivado con exito." << endl;
		}else{
        	car.estado=1;
           	file.seekp(-static_cast<int>(sizeof(Car)), ios::cur);
           	file.write(reinterpret_cast<const char*>(&car), sizeof(Car));
           	file.close();
            cout << "Producto activado con exito." << endl;
		}
		
		   	
	}
}
int main(){
	int x;
	do{
		menu();
		cin>>x;
		
		switch(x){
			case 1:registrar();break;
			case 2:consultar();break;
			case 3:modificar();break;
			case 4:eliminar();break;
		}
	} while (x!=5);
}
