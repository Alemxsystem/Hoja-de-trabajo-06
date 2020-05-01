/*
EJERCICIO # 1
En una libreria se venden 4 modelos diferentes de cuadernos, con los siguientes precios:
„h Modelo#1 ¡V Q10.00
„h Modelo#2 ¡V Q15.00
„h Modelo#3 ¡V Q18.50
„h Modelo#4 ¡V Q25.00
Por otra parte, se tiene informacion sobre las ventas realizadas durante los ultimos 30 dias, estos
movimientos se deben de guardar en un archivo de la siguiente forma:
DIA1,MOD,CANT
DIA2,MOD,CANT
.
.
.
DIA30,MODELO,CANTIDAD
DIAi = Variable que representa el dia que se efectuo la venta i (1 - 30)
MOD= Variable que representa codigo de Modelo que se vendio. (1 ¡V 4)
CANT= Variable que representa la cantidad de unidades vendidas.
El programa debe ser capaz de:
„h Modificar el numero de unidades vendidas, solicitando al usuario el dia y codigo de articulo
(modificacion del archivo)
„h Eliminacion de un dia especifico de venta (modificacion del archivo)
„h Calcular el total recaudado por modelo en los 30 dias.
„h Calcular cual fue el modelo que se vendio mas en los 30 dias
*/
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct cuadernos{
  string descripcion;
  float precio;
  int cantidad;
} cuaderno[4];

struct lectura{
  int dia;
  int modelo;
  int cantidad;
};

vector<lectura> registro;


void pausar_pantalla(){
      // Pause
    system("pause");
    cout << "\nPresione cualquier tecla para continuar \n";
}


void iniciar_variables(){
  // lista de Cuadernos
  cuaderno[0]={"Modelo#1",10,0};
  cuaderno[1]={"Modelo#2",15,0};
  cuaderno[2]={"Modelo#3",18.50,0};
  cuaderno[3]={"Modelo#4",25,0};
  // Limpio el vector de registro
  registro.clear();
};

void ingresar(){
  int dia, modelo, cantidad;
  bool control=false;
  
  while (control==false) {
  cout << "Ingrese el dia de la venta: ";
  cin >> dia;
    // comprombamos si el dia esta en los parametros 1 al 31
    if (dia>=1 and dia<=31) {
      control=true;
    } else {
      control=false;
    }
  }
  control=false;
  
  while (control==false) {
    cout << "Ingrese el modelo del cuaderno: ";
    cin >> modelo;
    modelo=modelo-1;
    
    // comparamos que el modelo si este en el rango de la lista
    if (modelo>=0 and modelo<=3) {
      control=true;
    } else {
      cout << "El modelo ingresado no es valido, intente de nuevo"<< endl;
      control=false;
    }
  }
  
    cout << "Ingrese la cantidad de ventas del cuaderno: ";
    cin >> cantidad;
    
  ofstream archivo;
  try {
    archivo.open("archivo.txt",ios::app);

    archivo<<dia<<","<<modelo+1<<","<<cantidad<<endl;

    archivo.close();
  } catch(exception X){
		cout<<"Error en la manipulacion del archivo"<<endl;
		
    // Esto es una pausa para ingresar enter
    cout << "Presione enter para continuar.... "<< endl;
  
    pausar_pantalla();
    system("cls");
	};
}

void leer_archivo_a_memoria(){
  lectura x;
  ifstream archivo; // Creamos el objeto
  string input;
  try {
    archivo.open("archivo.txt", ios::in);

    while(!archivo.eof()){
      getline(archivo,input,','); //Obtengo el primer string
			x.dia = atoi(input.c_str()); // Lo convierto en integer
      getline(archivo,input,',');
			x.modelo = atoi(input.c_str());
      getline(archivo,input,'\n');
			x.cantidad = atoi(input.c_str());
      
      // Lo almacenamos en un vector;
      if (x.dia !=0 and x.modelo != 0 and x.cantidad !=0){
        registro.push_back(x);
      }
      
    }
    
    // cierro el archivo.
    archivo.close();
  }
  catch (exception X){
    cout<<"Error en la manipulacion del archivo"<<endl;
    pausar_pantalla();
    system("cls");
  }
};

void mostrar(){
  system("cls");
  registro.clear();
  leer_archivo_a_memoria();
  cout << "Día " <<"\t" <<"Modelo" <<"\t"<<"Cantidad"<<endl;
  cout << "------------------------------" << endl;
  for (int i=0; i<registro.size(); i++){
    cout << registro[i].dia  << setw(8) << registro[i].modelo << setw(10) << registro[i].cantidad << "\n";
  }
  cin.ignore();
  pausar_pantalla();


};



void memoria_a_archivo(){
  ofstream archivo;
  archivo.open("archivo.txt", ios::out);

  // pasamos de la memoria al archivo.
  for (int i=0; i<registro.size(); i++){
    // Si es distinto de  0 en el archivo no lo graba
    if (registro[i].dia != 0 and registro[i].modelo != 0 and registro[i].cantidad != 0){
      archivo << registro[i].dia <<","<<registro[i].modelo<<","<<registro[i].cantidad<<"\n";
    }
    
  }

  //Cerrramos el archivo.
  archivo.close();
}

void calculo(){
  registro.clear();
  int modelo1, modelo2, modelo3, modelo0;
  float total1, total2, total3, total0;
  leer_archivo_a_memoria();
  
  int modelo;
  
  // Contamos cuantos modelos se vendieron en total
  for (int i=0; i<registro.size(); i++){
    modelo=registro[i].modelo-1;
    cuaderno[modelo].cantidad+=registro[i].cantidad;
  }

  float total=0;
  for (int i=0; i<4; i++){
    total=((cuaderno[i].precio*cuaderno[i].cantidad));
    cout << "Total recaudado por "<< cuaderno[i].descripcion <<" es de: Q." << total<< "\n";
  }

  int mayor;
  if (cuaderno[0].cantidad>cuaderno[1].cantidad and cuaderno[0].cantidad>cuaderno[2].cantidad and cuaderno[0].cantidad>cuaderno[3].cantidad) {
    mayor=0;
  } else if  
    (cuaderno[1].cantidad>cuaderno[2].cantidad and cuaderno[1].cantidad>cuaderno[3].cantidad and cuaderno[1].cantidad>cuaderno[0].cantidad) {
    mayor=1;
  }
   else if  
    (cuaderno[2].cantidad>cuaderno[3].cantidad and cuaderno[2].cantidad>cuaderno[0].cantidad and cuaderno[2].cantidad>cuaderno[1].cantidad) {
    mayor=2;
  } else{
    mayor=3;
  }

  cout << "El modelo mas vendidco es: " << cuaderno[mayor].descripcion << "\n";
      cout <<"Con la cantidad de: " << cuaderno[mayor].cantidad << " Unidades vendidas" << "\n";

}

void modificar(){
  mostrar();
  int dia, modelo, cantidad;
  cout << "Ingrese el dia: ";
  cin >> dia;
  cout << "Ingrese modelo: ";
  cin >> modelo;
  cout << "Ingrese la nueva cantidad: ";
  cin >> cantidad;
  
  int position=0;
  bool encontrado=false;
  
  for (int i=0; i<registro.size(); i++){
    if(registro[i].dia==dia and registro[i].modelo==modelo) {
      position=i;
      encontrado=true;
    } else {
      encontrado=false;
    }

  }
  
  if (encontrado){
    registro[position].cantidad=cantidad; // Eliminamos el 
  } else {
    cout << "Ingreso un dato incorrecto" << endl;
    pausar_pantalla();
  }
  //registro de la memoria.
  memoria_a_archivo();
  mostrar();
  return;
};

void eliminar(){
  mostrar();
  int dia, modelo;
  cout << "Ingrese el dia: ";
  cin >> dia;
  cout << "Ingrese modelo: ";
  cin >> modelo;
  bool encontrado=false;
  int position=0;
  
  for (int i=0; i<registro.size(); i++){
    if(registro[i].dia==dia and registro[i].modelo==modelo) {
      position=i;
      encontrado=true;
    } else {
      encontrado=false;
    }

  }
  
  if (encontrado){
    registro.erase(registro.begin() + position); // Eliminamos el 
  } else {
    cout << "Ingreso un dato incorrecto" << endl;
    pausar_pantalla();
  }
  //registro de la memoria.
  memoria_a_archivo();
  mostrar();
  return;
};

void mp(){
	int selec;
	do {
    // limpiamos pantalla
    system("cls");
		cout<<"--------------------------"<<"\n";
		cout<<" Menu Principal"<<"\n";
		cout<<"-------------------"<<"\n";
		cout<<" 1 - Ingresar registro "<<"\n";
		cout<<" 2 - Reporte "<<"\n";
    	cout<<" 3 - Modificar"<<"\n";
		cout<<" 4 - Eliminar"<<"\n";
  		cout<<" 5 - Salir"<<"\n";
		cout<<"--------------------------"<<"\n";
		cout<<" Seleccione su opcion: ";
		cin>>selec;
		if (selec==1){		
			  // limpiamos pantalla
      		system("cls");
			ingresar();			
		}
		else if (selec==2){
			mostrar();
      		calculo();
      		pausar_pantalla();
		}
    	else if (selec==3){		
  		 	modificar();
		}
    	else if (selec==4){		
      		eliminar();
		}
		else if (selec==5)
			break;
		else 
			break;
		
	} while(selec!=5);	
};


int main(){
  iniciar_variables();
  mp();
  return 0;
};