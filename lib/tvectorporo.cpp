#include "tvectorporo.h"
#include <iostream>
using namespace std;

TVectorPoro::TVectorPoro():error(){
	dimension=0;
	datos=NULL;
}

TVectorPoro::TVectorPoro(int dimen){
	if(dimen<=0){
		TVectorPoro();
	}
	else{
		dimension=dimen;
		//Llama a constructor por defecto de TPoro 5 veces
		datos=new TPoro[dimension];
	}
}

TVectorPoro::TVectorPoro(const TVectorPoro &original):error(original.error){
	dimension=original.dimension;
	
	datos = new TPoro[dimension];
	for(int i=0; i<dimension;i++){
		datos[i]=original.datos[i];
	}
}

TVectorPoro::~TVectorPoro(){

}

TVectorPoro& TVectorPoro:: operator=(const TVectorPoro &original){
	if(this != &original){
		dimension=original.dimension;
		datos = new TPoro[dimension];
		for(int i=0; i<dimension;i++){
			datos[i]=original.datos[i];
		}
		error=original.error;
	}
	
	return (*this);
}

bool TVectorPoro::operator==(const TVectorPoro &tvp){
	bool temp = false;
	
	if(dimension == tvp.dimension){
		temp = true;
		for(int i = 0; i < dimension && temp; i++)
			if(datos[i] != tvp.datos[i]) return false;
	}
	return temp;
}

bool TVectorPoro::operator!=(const TVectorPoro &tvp){
	return !(*this == tvp);
}

//Parte izquierda (modifica)
TPoro &TVectorPoro::operator[](int index){
	if(index >= 1 && index<=dimension){
		return datos[index-1];
	}
	else{
		return error;
	}
}

//Parte derecha (consultivo)
TPoro TVectorPoro::operator[](int index) const{
	if(index >= 1 && index<=dimension){
		return datos[index-1];
	}
	
		return error;
	
}

int TVectorPoro:: Longitud(){
	return this->dimension;
}

int TVectorPoro:: Cantidad(){
	int contador=0;
	for(int i=0; i<dimension;i++){
		if(!datos[i].EsVacio()){
			contador++;
		}
	}
	return contador;
}

bool TVectorPoro:: Redimensionar(int resize){


	if(resize<=0){
		return false;
	}
	else if(resize==this->Longitud()){
		return false;
	}
	else{

		TPoro *newData = new TPoro[resize]; 
		//Mas grande
		 if(resize>0 && resize>this->Longitud()){
			
			for(int i=0; i<dimension;i++){
				newData[i]=datos[i];
			}
			delete[] datos;
			datos = newData;
			dimension = resize;
		}

		//Más pequeño
		else if(resize>0 && resize<this->Longitud()){
			dimension=resize;
			for(int i=0; i<dimension;i++){
				newData[i] = datos[i];
			}
			delete[] datos;
			datos = newData;
		}
	}	

}

ostream & operator<<(ostream &os, const TVectorPoro &tvp){
	os << "[";
	for( int i=1; i<=tvp.dimension;i++){
		os << i <<" "<<  tvp[i];
		if(i<tvp.dimension){
			os << " ";
		}
	}
	os << "]";
	return os;
}
