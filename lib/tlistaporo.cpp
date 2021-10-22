#include "tlistaporo.h"
#include "tporo.h"
#include <iostream>
using namespace std;




TListaNodo::TListaNodo(): e(){
    anterior=siguiente=NULL;
}

TListaNodo::TListaNodo(TListaNodo &copia):e(copia.e){
    anterior=siguiente=NULL;
}

TListaNodo::~TListaNodo(){
    anterior=siguiente=NULL;
}

TListaNodo& TListaNodo::operator=(const TListaNodo &asig){

    if(this != &asig){
        (*this).~TListaNodo();
        e=asig.e;
    }
    return (*this);

}

//TLISTAPOSICION
TListaPosicion::TListaPosicion(){
    pos=NULL;
}
TListaPosicion::TListaPosicion(const TListaPosicion &copia){
    if(copia.pos!=NULL){
        pos=copia.pos;
    }
    else
        pos=NULL;

}

TListaPosicion::~TListaPosicion(){
    pos=NULL;
}


TListaPosicion& TListaPosicion:: operator=(const TListaPosicion &asig){
     if(this != &asig){
         (*this).~TListaPosicion();
         pos=asig.pos;
     }

     return (*this);

}

bool TListaPosicion::operator==(const TListaPosicion &equal)const{
    bool temp=false;
    if(equal.pos!=NULL && pos!=NULL){
        if(equal.pos==pos){
            temp=true;
        }
    }
    else if(equal.pos==NULL && pos == NULL){
        temp=true;
    }

    return temp;

}

TListaPosicion TListaPosicion:: Anterior() const{
    TListaPosicion listPosi;
    if(pos!=NULL){
        listPosi.pos=pos->anterior;
    }
    else
        listPosi.pos=NULL;
    
    return listPosi;
   
}

TListaPosicion TListaPosicion:: Siguiente()const{
    TListaPosicion listPosi;
    if(pos!=NULL){
        listPosi.pos=pos->siguiente;
    }
    else
        listPosi.pos=NULL;
    
    return listPosi;

}

bool TListaPosicion::EsVacia()const{
    if(pos==NULL){
        return true;
    }
    else
        return false;

}

//TLISTAPORO

TListaPoro:: TListaPoro(){
    primero=ultimo=NULL;
}

TListaPoro:: TListaPoro(TListaPoro &copia){

    if(copia.primero==NULL){
        primero=NULL;
    }
    else
        primero=copia.primero;

    if(copia.ultimo=NULL){
        ultimo=NULL;
    }
    else
        ultimo=copia.ultimo;


}

TListaPoro::~TListaPoro(){
    primero=ultimo=NULL;
}

TListaPoro& TListaPoro::operator=( const TListaPoro &asig){
    if(this!=&asig){
       (*this).~TListaPoro();
        primero=ultimo=NULL;
        for(TListaPosicion i = asig.Primera(); !i.EsVacia(); i = i.Siguiente()){
          Insertar(i.pos->e);
        }
    }

}

bool TListaPoro::operator==(TListaPoro &compare){
    TListaPosicion posi = compare.Primera();
    //Iteramos sobre tlistaposicion mientras este vacia
    for(TListaPosicion it = Primera(); !it.EsVacia();it.Siguiente()) {
        //Si posi vacia o nodos distintos son distintas
        if(posi.EsVacia() || it.pos->e != posi.pos->e){
            return false;
        }
        posi = posi.Siguiente();
    }

    return true;
}

TListaPoro TListaPoro:: operator+(TListaPoro &aux){
    TListaPoro tlp;
    for(TListaPosicion it = Primera(); !it.EsVacia();it=it.Siguiente()){
        tlp.Insertar(it.pos->e);
    }
    for(TListaPosicion it= aux.Primera();!it.EsVacia();it=it.Siguiente()){
        tlp.Insertar(it.pos->e);
    }

    return tlp;
}

TListaPoro TListaPoro:: operator-(TListaPoro &aux){
    TListaPoro tlp;
    for(TListaPosicion it = Primera(); !it.EsVacia();it=it.Siguiente()){
        if(!aux.Buscar(it.pos->e)){
            tlp.Insertar(it.pos->e);
        }
    }

    return tlp;

}

bool TListaPoro:: EsVacia()const{
    if(primero==NULL && ultimo==NULL){
        return true;
    }
    return false;

}

bool TListaPoro:: Insertar(const TPoro &insert){
    
    if(EsVacia()){
            TListaNodo *tln = new TListaNodo();
            tln->e = insert;
            primero=ultimo=tln;
            return true;
    }
    else{
        TListaPosicion index = Primera();
        double poroVol=insert.Volumen();

        while(!index.EsVacia()){
            double auxVol=index.pos->e.Volumen();
            if(index.pos->e==insert){
                return false;
            }
            else if(poroVol>=auxVol){
                index=index.Siguiente();
            }
            
            //Primera
            else if(index==Primera()){
                TListaNodo *tln = new TListaNodo();
                tln->e = insert;
                primero->anterior=tln;
                tln->siguiente=primero;
                primero=tln;
             
                return true;
            }
            else{
                TListaNodo *tln = new TListaNodo();
                tln->e=insert;
                tln->siguiente = index.pos;
                tln->anterior=index.pos->anterior;
                index.pos->anterior->siguiente=tln;
                index.pos->anterior=tln;
                return true;
                
            }
        }
        TListaNodo *tln = new TListaNodo();
        tln->e = insert;
        ultimo->siguiente=tln;
        tln->anterior=ultimo;
        ultimo=tln;
        return true;
    }
      

}

bool TListaPoro:: Borrar(TPoro &aux){
    for(TListaPosicion it = Primera();!it.EsVacia();it=it.Siguiente()){
        if(it.pos->e == aux){
            Borrar(it);
            return true;
        }
    }
    return false;

}


bool TListaPoro:: Borrar(TListaPosicion &poro){
	if(!EsVacia()) {
		if(poro == Primera()) {
			if(primero == ultimo) {
                 primero = ultimo = NULL;
            } 
			else {
				primero = primero->siguiente; 
				primero->anterior = NULL;
			}
			return true;
		}
		else if(poro == Ultima()) {
			ultimo = ultimo->anterior; 
			ultimo->siguiente = NULL;
			return true;
		}
		else {
			for(TListaPosicion i = Primera(); !i.EsVacia(); i = i.Siguiente()) {
				if(poro == i) { 
					i.pos->siguiente->anterior = i.pos->anterior;
					i.pos->anterior->siguiente = i.pos->siguiente;
					return true;
				}
			}
		}
			delete poro.pos;
			poro.pos = NULL;
		
	}
    return false;

}

TPoro TListaPoro::Obtener(TListaPosicion &aux) const{

    for(TListaPosicion it = Primera(); !it.EsVacia();it=it.Siguiente()){
        if(it==aux){
             return (it.pos->e);
        }
    }
    return TPoro();
}

bool TListaPoro:: Buscar(TPoro &aux){
    for(TListaPosicion it = Primera();!it.EsVacia();it=it.Siguiente()){
        if(it.pos->e == aux){
            return true;
        }
    }
    return false;
}

int TListaPoro:: Longitud(){
    int size=0;
    for(TListaPosicion i = Primera();!i.EsVacia();i=i.Siguiente()){
        size++;
    }

    return size;

}

TListaPosicion TListaPoro::Primera()const{
    TListaPosicion p;
    p.pos=primero;
    return p;

}

TListaPosicion TListaPoro::Ultima()const{
    TListaPosicion p;
    p.pos=ultimo;
    return p;

}

TListaPoro TListaPoro:: ExtraerRango (int n1, int n2){
   
}

ostream & operator<<(ostream &os, const TListaPoro &tlp){

    os << "(";
	for(TListaPosicion i = tlp.Primera(); !i.EsVacia(); i = i.Siguiente()) {
		os << tlp.Obtener(i);
		if(i == tlp.Ultima()) {
        
        }
        else{
         os << " ";
        }
	}
	os << ")";
	return os;
}
