#include <iostream>
#include <queue>
#include "tabbporo.h"
#include "tporo.h"
#include "tvectorporo.h"
using namespace std;


/*
*** CLASE TNODOABB
*/

TNodoABB::TNodoABB():item(),iz(),de(){

}

TNodoABB::~TNodoABB(){}


TNodoABB::TNodoABB (TNodoABB &orig):item(orig.item), de(orig.de),iz(orig.iz){}


TNodoABB& TNodoABB :: operator= (const TNodoABB &orig){
   if(this!= & orig){
      (*this).~TNodoABB();
      this->item=orig.item;
      if(!orig.iz.EsVacio()){
         this->iz=orig.iz;
      }
      if(!orig.de.EsVacio()){
         this->de=orig.de;
      }
   }

   return (*this);
}

/*
*** CLASE TABBPORO
*/

TABBPoro::TABBPoro(){
   nodo=NULL;
}
TABBPoro::~TABBPoro(){
   if(!EsVacio()){
      delete nodo;
      nodo=NULL;
   }
}

TABBPoro::TABBPoro(const TABBPoro &tabb){
   Copia(tabb);
}

void TABBPoro::Copia(const TABBPoro &orig){
   if(orig.nodo!=NULL){
         TNodoABB *auxNodo = new TNodoABB();
         auxNodo -> item = orig.nodo->item;
         nodo = auxNodo;
         nodo->iz.Copia(orig.nodo->iz);
         nodo->de.Copia(orig.nodo->de);
      }
      else{
         nodo=NULL;
      }

}

bool TABBPoro::EsVacio() const{
   if(nodo==NULL){
      return true;
   }
   return false;

}

bool TABBPoro::Insertar(TPoro &tp){

   if(this->nodo==NULL){
      nodo = new TNodoABB();
      nodo->item=tp;
      return true;        
   }
   else{
      if(this->nodo->item==tp){
         return false;
      }
      else if(this->nodo->item.Volumen()==tp.Volumen()){
         return false;
      }
      else{
         if(tp.Volumen() < Raiz().Volumen()){
           return (nodo->iz.Insertar(tp));
         }
         else{
            return (nodo->de.Insertar(tp));
         }
      }
   }
   
}


bool TABBPoro::Borrar(const TPoro &tp){
   TPoro auxPoro;
   TNodoABB *borrar;

   if(!EsVacio()){
      if(tp.Volumen() > Raiz().Volumen()){
         return(nodo->de.Borrar(tp));
      }
      else if(tp.Volumen() < Raiz().Volumen()){
         return (nodo->iz.Borrar(tp));
      }
      else if(Raiz() == tp){
         if(nodo->iz.EsVacio() && nodo->de.EsVacio()){
             delete nodo;
            nodo=NULL;
            return true;
         }
         else if(nodo->iz.EsVacio() && !nodo->de.EsVacio()){
            borrar=nodo;
            nodo = nodo->de.nodo;
            borrar->de.nodo=NULL;
            delete borrar;
            return true;
         }
         else if(!nodo->iz.EsVacio() && nodo->de.EsVacio()){
            borrar=nodo;
            nodo = nodo->iz.nodo;
            borrar->iz.nodo=NULL;
            delete borrar;
            return true;
         }
         else{
            auxPoro = this->nodo->iz.maxValue();
            nodo->item=auxPoro;
            nodo->iz.Borrar(auxPoro);
            return true;
         }
      }
      else return false;
         
   }
   else return false;
      
}

TPoro TABBPoro:: maxValue(){
   if(this->nodo->de.EsVacio()){
      return (nodo->item);
   }
   return(this->nodo->de.maxValue());
   
}


bool TABBPoro::Buscar(TPoro &tp){
   if(!EsVacio()){
      if(nodo->item == tp){
         return true;
      }
      else if(tp.Volumen() < Raiz().Volumen()){
         return(nodo->iz.Buscar(tp));
      }
      else{
         return(nodo->de.Buscar(tp));
      }
   }
   return false;
}

TPoro TABBPoro::Raiz(){
   TPoro tp;
   if(!EsVacio()){
      return (nodo->item);
   }
   else return tp;
}

int TABBPoro::Max(int a, int b){
   return ((a>b)?a:b);
}

int TABBPoro::Altura(){
  
   if(EsVacio()){
      return 0;
   }

   int lh = nodo->iz.Altura();
   int rh = nodo->de.Altura();

   return 1 + max(lh,rh);

}
int TABBPoro::NodosAux(int total) const{
	if(!EsVacio())
	{
		total = 1 + nodo->iz.NodosAux(total) + nodo->de.NodosAux(total);
	}
	return total;
}

int TABBPoro::Nodos() const{
 return NodosAux(0);

}

int TABBPoro::NodosHoja(){

   if(EsVacio()){
      return 0;
   }
   else{
      if(nodo->iz.EsVacio() && nodo->de.EsVacio()){
         return 1;
      }
      else{
         return(nodo->de.NodosHoja() + nodo->iz.NodosHoja());
      }
   }

}

void TABBPoro::InordenAux(TVectorPoro &tvp, int &num)const{
   if(!EsVacio()){
      nodo->iz.InordenAux(tvp,num);
      tvp[num]=nodo->item;
      num++;
      nodo->de.InordenAux(tvp,num);
   }
}

TVectorPoro TABBPoro::Inorden() const{
   if(EsVacio()){
      TVectorPoro v;
      return v;
   }

   else{

   int posicion=1;
   TVectorPoro v(Nodos());
   InordenAux(v,posicion);
   return v;

   }
}
TVectorPoro TABBPoro::Preorden()const{
   if(EsVacio()){
      TVectorPoro v;
      return v;
   }
   else{
      int posicion=1;
      TVectorPoro v(Nodos());
      PreordenAux(v,posicion);
   }

}

void TABBPoro::PreordenAux(TVectorPoro &tvp, int &num)const{
   if(!EsVacio()){
      tvp[num] = nodo->item;
      num++;
      nodo->iz.PreordenAux(tvp,num);
      nodo->de.PreordenAux(tvp,num);
   }

}

TVectorPoro TABBPoro::Postorden()const{
   if(EsVacio()){
      TVectorPoro v;
      return v;
   }
   else{
      int posicion=1;
      TVectorPoro v(Nodos());
      PreordenAux(v,posicion);
   }


}
void TABBPoro::PostordenAux(TVectorPoro &tvp, int &num)const{
   if(!EsVacio()){
      nodo->iz.PreordenAux(tvp,num);
      nodo->de.PreordenAux(tvp,num);
      tvp[num] = nodo ->item;
      num++;
   }
}
TVectorPoro TABBPoro::Niveles() const{
   TVectorPoro tvp(Nodos());
   queue <TNodoABB *> cola;
   TNodoABB* aux;
   int it;
  
   if(!EsVacio()){
       it=1;
       cola.push(nodo);
       while(!cola.empty()){
          aux=cola.front();
          cola.pop();
          if(!aux->iz.EsVacio()){
             cola.push(aux->iz.nodo);
          }
          if(!aux->de.EsVacio()){
             cola.push(aux->de.nodo);
          }
          tvp[it]=aux->item;
          it++;
       }
   }
   return tvp;

}

bool TABBPoro:: operator==(TABBPoro &aux){
  if(EsVacio() && aux.EsVacio()){
     return true;
  }
  else if(EsVacio() && !aux.EsVacio() || !EsVacio() && aux.EsVacio()){
     return false;
  }
  else if(Raiz() == aux.Raiz() && nodo->iz == aux.nodo->iz && nodo->de == aux.nodo->de){
      return true;
  }
   else{
      return false;
   }
}

TABBPoro &TABBPoro::operator=(const TABBPoro &a){
   this->~TABBPoro();
   Copia(a);
   return *this;
}

TABBPoro TABBPoro:: operator+(const TABBPoro &aux)const{
   TABBPoro copy(*this);
   TVectorPoro tvp;
   int i =1;
   tvp = aux.Inorden();
   while(i<=tvp.Longitud()) {
      copy.Insertar(tvp[i]);
      i++;
   }

   return copy;



}
TABBPoro TABBPoro::operator-(const TABBPoro &aux)const {
   TABBPoro copy(*this);
	TVectorPoro tvp(aux.Inorden());

	for(int i = 1; i <= tvp.Longitud(); i++){
		copy.Borrar(tvp[i]);
	}
	
	return copy;

}

ostream & operator << (ostream &os, const TABBPoro &tabb){
   os << tabb.Niveles();
}
