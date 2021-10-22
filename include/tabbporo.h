#ifndef _TABPORO_H
#define _TABPORO_H
#include <iostream>
#include "tporo.h"
#include "tvectorporo.h"


using namespace std;


class TNodoABB;


class TABBPoro{
    friend class TNodoABB;
    private:
        TNodoABB *nodo;
        void InordenAux(TVectorPoro &, int &) const;
        void PreordenAux(TVectorPoro &, int &)const;
        void PostordenAux(TVectorPoro &, int &)const;
        int Max(int, int);
        int NodosAux(int ) const;
        void Copia(const TABBPoro &);
        TPoro maxValue();
      
    
    public:
        TABBPoro();
        TABBPoro(const TABBPoro &);
        ~TABBPoro();
        TABBPoro & operator=(const TABBPoro &);

        bool operator==(TABBPoro &);
        bool EsVacio() const;
        bool Insertar(TPoro &);
        bool Borrar(const TPoro &);
        bool Buscar(TPoro &);
        TPoro Raiz();
        int Altura();
        int Nodos() const;
        int NodosHoja();

        TVectorPoro Inorden() const;
        TVectorPoro Preorden()const;
        TVectorPoro Postorden()const;
        TVectorPoro Niveles() const;

        TABBPoro operator+(const TABBPoro &)const;
        TABBPoro operator-(const TABBPoro &)const;

        friend ostream & operator << (ostream &, const TABBPoro &);

};

class TNodoABB{
    friend class TABBPoro;
    private:
        TPoro item;
        TABBPoro iz, de;
       
    
    public:
        TNodoABB();
        TNodoABB(TNodoABB &);
        ~TNodoABB();
        TNodoABB & operator= (const TNodoABB &);

};
#endif