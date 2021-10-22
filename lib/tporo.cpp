#include "tporo.h"
#include <iostream>
#include <cstring>
using namespace std;


//COnstructor por defecto
TPoro::TPoro(){
	x=0;
	y=0;
	volumen=0.0;
	color=NULL;
}
//Constructor
TPoro::TPoro(int posx, int posy, double vol, const char* col){
	x=posx;
	y=posy;
	volumen=vol;

	if(col!=NULL){

		color=new char[strlen(col)+1];
		int i=0;
		for( i=0; i<strlen(col); i++){
			color[i] = tolower(col[i]);
		}
		color[i]='\0';
	}
	else {
	//	delete[] color;
		color=NULL;
	}
	
}
 //Constructor de copia
TPoro::TPoro(const TPoro &original){
	x=original.x;
	y=original.y;
	volumen=original.volumen;
	if(original.color!=NULL){
		color= new char [strlen(original.color)+1];
		int i=0;
		for(i=0; i<strlen(original.color); i++){
			color[i] = tolower(original.color[i]);
		}
		color[i]='\0';
	}
	else{ 
		//delete[] color;
		color=NULL;
	}
}
//Constructor
TPoro::TPoro(int posx, int posy, double vol){
	x=posx;
	y=posy;
	volumen=vol;
	color=NULL;
} 


TPoro::~TPoro(){ //DESTRUCTOR
	x=y=0;
	volumen=0;
	
	if(color!=NULL){
		delete[] color;
		color=NULL;
	}
}

//Overload
TPoro& TPoro:: operator=(const TPoro &a){
	if(this != &a){
		x=a.x;
		y=a.y;
		volumen=a.volumen;
		
		if(a.color!=NULL){
			
			color= new char [strlen(a.color)+1];
			int i=0;
			for(i=0; i<strlen(a.color); i++){
				color[i] = tolower(a.color[i]);
			}
			color[i]='\0';
		}
		else {
			
			color=NULL;
		}
	}
	return (*this);
}

//Overload
bool TPoro::operator==(const TPoro &a){
	bool temp=false;

	if(x==a.x && y==a.y && volumen==a.volumen){
		if(color!=NULL && a.color!=NULL){
			if(strcmp(color,a.color)==0){
				temp=true;
			}
		}
		else if(color==NULL && a.color==NULL){
			temp=true;
		}
	}
	return temp;
}

// Sobrecarga del operador asignación
bool TPoro ::operator!=(TPoro &a){
	return !(*this == a);
}

//Setter
void TPoro:: Posicion(int posx, int posy){
	x=posx;
	y=posy;
}

//Seter
void TPoro:: Volumen(double vol){
	volumen=vol;
}

//Setter
void TPoro:: Color(const char* col){
	if(col!=NULL){
		color=new char[strlen(col)+1];
		int i=0;
		for( i=0; i<strlen(col); i++){
			color[i] = tolower(col[i]);
		}
		color[i]='\0';
		
	}
	else{
	  //delete[] color; 
	  color=NULL; //¡¡IMPORTANTE!!
	}
}

//Getter
int TPoro:: PosicionX()const{
	return x;
}

//Getter
int TPoro:: PosicionY()const{
	return y;
}

//Getter
double TPoro:: Volumen()const{
	return volumen;
}

//Getter
char* TPoro:: Color()const{
	return color;
}

//Getter
bool TPoro::EsVacio ()const{
	if(x==0 && y==0 && volumen==0.0 && color==NULL){
		return true;
	}
	return false;
}

ostream & operator<<(ostream &os,const TPoro &poro){
	
	if(!poro.EsVacio()){
		os.setf(ios::fixed);
		os.precision(2);
		os<<"("<<poro.x<<", "<<poro.y<<") "<<poro.volumen<<" ";
		if(poro.color!=NULL)
			os<<poro.color;
		else
			os<<"-";
	}
	else
		os << "()";
	return os;
	
}


