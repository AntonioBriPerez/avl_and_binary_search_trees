#include <iostream>
#include "tavlporo.h"
#include "tporo.h"
#include "tvectorporo.h"
using namespace std;

/*
**CLASE TNODOAVL
*/


TNodoAVL::TNodoAVL():item(),iz(),de(){
fe=0;
}

TNodoAVL::~TNodoAVL(){}

TNodoAVL::TNodoAVL(TNodoAVL &orig):item(orig.item),de(orig.de),iz(orig.iz){}

TNodoAVL &TNodoAVL::operator=(const TNodoAVL &orig){
	if(this!= & orig){
      (*this).~TNodoAVL();
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
**CLASE TAVLPORO
*/

TAVLPoro::TAVLPoro(){
	raiz=NULL;
}
TAVLPoro::~TAVLPoro(){
	if(!EsVacio()){
		delete raiz;
		raiz=NULL;
	}
}

void TAVLPoro::Copia(const TAVLPoro &orig){
   if(orig.raiz!=NULL){
         TNodoAVL *auxNodo = new TNodoAVL();
         auxNodo -> item = orig.raiz->item;
         raiz = auxNodo;
         raiz->iz.Copia(orig.raiz->iz);
         raiz->de.Copia(orig.raiz->de);
      }
      else{
         raiz=NULL;
      }

}

TAVLPoro::TAVLPoro(const TAVLPoro &orig){
	Copia(orig);
}

TAVLPoro &TAVLPoro::operator=(const TAVLPoro &orig){
   this->~TAVLPoro();
   Copia(orig);
   return *this;
}

int TAVLPoro::Max(int a, int b){
   return ((a>b)?a:b);
}

bool TAVLPoro::operator==(TAVLPoro &aux){
	if(EsVacio() && aux.EsVacio()){
     return true;
  }
  else if(EsVacio() && !aux.EsVacio() || !EsVacio() && aux.EsVacio()){
     return false;
  }
  else if(Raiz() == aux.Raiz() && raiz->iz == aux.raiz->iz && raiz->de == aux.raiz->de){
      return true;
  }
   else{
      return false;
   }
}

bool TAVLPoro::operator!=(TAVLPoro &orig){
	if(this == &orig){
		return true;
	}
	else{
		return false;
	}
}

bool TAVLPoro:: EsVacio()const{

	if(raiz==NULL){
		return true;
	}
	else
		return false;
}



bool TAVLPoro::Buscar(TPoro &tp){
	if(!EsVacio()){
      if(raiz->item == tp){
         return true;
      }
      else if(tp.Volumen() < Raiz().Volumen()){
         return(raiz->iz.Buscar(tp));
      }
      else{
         return(raiz->de.Buscar(tp));
      }
   }
   return false;
}

bool TAVLPoro::Borrar(TPoro &tp){
	 TPoro auxPoro;
   TNodoAVL *borrar;

   if(!EsVacio()){
      if(tp.Volumen() > Raiz().Volumen()){
         return(raiz->de.Borrar(tp));
      }
      else if(tp.Volumen() < Raiz().Volumen()){
         return (raiz->iz.Borrar(tp));
      }
      else if(Raiz() == tp){
         if(raiz->iz.EsVacio() && raiz->de.EsVacio()){
             delete raiz;
            raiz=NULL;
            return true;
         }
         else if(raiz->iz.EsVacio() && !raiz->de.EsVacio()){
            borrar=raiz;
            raiz = raiz->de.raiz;
            borrar->de.raiz=NULL;
            delete borrar;
            return true;
         }
         else if(!raiz->iz.EsVacio() && raiz->de.EsVacio()){
            borrar=raiz;
            raiz = raiz->iz.raiz;
            delete borrar;
            return true;
         }
      }
   }
   return false;
}

TPoro TAVLPoro:: maxValue(){
   if(this->raiz->de.EsVacio()){
      return (raiz->item);
   }
   return(this->raiz->de.maxValue());
   
}




void TAVLPoro::rr_rotation()
{

	TNodoAVL *root = raiz;
	TNodoAVL *rightRoot = raiz->de.raiz; 
	TNodoAVL *leftRoot = rightRoot->iz.raiz; 

	raiz = rightRoot;

	root->de.raiz = leftRoot;

	raiz->iz.raiz = root;


}

void TAVLPoro::ll_rotation() {
	TNodoAVL *root = raiz; 
	TNodoAVL *leftRoot = raiz->iz.raiz; 
	TNodoAVL *rightRoot = leftRoot->de.raiz; 

	raiz = raiz->iz.raiz;

	raiz->de.raiz = root;

	raiz->de.raiz->iz.raiz = rightRoot;
}

void TAVLPoro::lr_rotation() {
	raiz->iz.rr_rotation();
	ll_rotation();
}

void TAVLPoro::rl_rotation() {
	raiz->de.ll_rotation();
	rr_rotation();
}

int TAVLPoro::treeDiff(){
	int balFactor=0;

	int r_height = raiz->de.Altura();
	int l_height = raiz->iz.Altura();
	balFactor = r_height - l_height;

	return balFactor;


}

void TAVLPoro::UpdateTree() {
	
	if(!EsVacio())
	{
		raiz->iz.UpdateTree();
		raiz->de.UpdateTree();
		if(this->treeDiff()<=-2 || this->treeDiff()>=2)
		{
			if(treeDiff()==2){
				if(raiz->de.treeDiff()==-1){
					
               rl_rotation();
				}
				else{
					rr_rotation();
				}
			}
			else if(treeDiff()==-2){
				if(raiz->iz.treeDiff()==1){
					
               lr_rotation();
				}
				else{
					ll_rotation();
				}
			}
		}
	}


}

bool TAVLPoro::Insertar(TPoro &otro){
	bool insertar = false;
	bool rightOrLeft=false;

	TNodoAVL *nuevo = new TNodoAVL();
	nuevo->item = otro;


	if(!Buscar(otro) && EsVacio()) {
		raiz = nuevo;
		return true;
	}
	else{

		if(otro.Volumen() > raiz->item.Volumen()){
			insertar = raiz->de.Insertar(otro);
			rightOrLeft=insertar;
		}

	  else if(otro.Volumen() < raiz->item.Volumen()){
		  insertar = raiz->iz.Insertar(otro);
			rightOrLeft=insertar;
		}

		else if(otro.Volumen() == raiz->item.Volumen()){
			return false;
		}
		updateBalanceFactor(rightOrLeft);
	}
	
	return insertar;
	

}

void TAVLPoro::updateBalanceFactor(bool rightOrLeft){

		if(treeDiff()<0){
			UpdateTree();
		}

		else if(treeDiff()>1) {
			UpdateTree();
		}
		else{
			if(rightOrLeft){
				raiz->fe = -1;
			}
			else{
				raiz->fe = 1;
			}
		}

}

int TAVLPoro::Altura(){
	if(EsVacio()){
      return 0;
   }

   int lh = raiz->iz.Altura();
   int rh = raiz->de.Altura();

   return 1 + max(lh,rh);

   
}

TPoro TAVLPoro::Raiz(){
	TPoro tp;
   if(!EsVacio()){
      return (raiz->item);
   }
   else return tp;
}

int TAVLPoro::Nodos()const{
	 return NodosAux(0);
}

int TAVLPoro::NodosAux(int total) const{
	if(!EsVacio())
	{
		total = 1 + raiz->iz.NodosAux(total) + raiz->de.NodosAux(total);
	}
	return total;
}

int TAVLPoro::NodosHoja(){
	if(EsVacio()){
      return 0;
   }
   else{
      if(raiz->iz.EsVacio() && raiz->de.EsVacio()){
         return 1;
      }
      else{
         return(raiz->de.NodosHoja() + raiz->iz.NodosHoja());
      }
   }

}

TVectorPoro TAVLPoro::Inorden()const{
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

void TAVLPoro:: InordenAux(TVectorPoro &tvp, int &num)const{
	if(!EsVacio()){
      raiz->iz.InordenAux(tvp,num);
      tvp[num]=raiz->item;
      num++;
      raiz->de.InordenAux(tvp,num);
   }
}



TVectorPoro TAVLPoro::Preorden()const{
	
      int posicion=1;
      TVectorPoro v(Nodos());
      PreordenAux(v,posicion);
      return v;
   
}

void TAVLPoro:: PreordenAux(TVectorPoro &tvp, int &num)const{
	if(!EsVacio()){
      tvp[num] = raiz->item;
      num++;
      raiz->iz.PreordenAux(tvp,num);
      raiz->de.PreordenAux(tvp,num);
   }
}


TVectorPoro TAVLPoro::Postorden()const{
	
      int posicion=1;
      TVectorPoro v(Nodos());
      PostordenAux(v,posicion);
      return v;
   
}

void TAVLPoro:: PostordenAux(TVectorPoro &tvp, int &num)const{
	if(!EsVacio()){
      raiz->iz.PostordenAux(tvp,num);
      raiz->de.PostordenAux(tvp,num);
      tvp[num] = raiz ->item;
      num++;
   }
}

ostream & operator << (ostream &os, const TAVLPoro &tavl){
   os << tavl.Inorden();
   return os;

}





