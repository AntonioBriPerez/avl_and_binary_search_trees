#ifndef _TLISTAPORO_H_
#define _TLISTAPORO_H_
#include <iostream>
#include "tporo.h"
using namespace std;

class TListaNodo{
    friend class TListaPoro;
    friend class TListaPosicion;

    private:
        TPoro e;
        TListaNodo *anterior;
        TListaNodo *siguiente;

    public:
        TListaNodo();
        TListaNodo (TListaNodo &);
        ~TListaNodo();
        TListaNodo & operator=(const TListaNodo &);


};


class TListaPosicion{
    friend class TListaNodo;
    friend class TListaPoro;

    private:
        TListaNodo *pos;
    
    public:
        TListaPosicion();
        TListaPosicion(const TListaPosicion &);
        ~TListaPosicion();
        TListaPosicion& operator=(const TListaPosicion &);

        bool operator==(const TListaPosicion &) const;
        TListaPosicion Anterior()const;
        TListaPosicion Siguiente()const;
        bool EsVacia() const;

};

class TListaPoro{
    friend class TListaNodo;
    friend class TListaPosicion;
    private:
        TListaNodo *primero;
        TListaNodo *ultimo;

    public:
        TListaPoro();
        TListaPoro(TListaPoro &);
        ~TListaPoro();
        TListaPoro & operator=( const TListaPoro &);

        //Metodos

        bool operator==(TListaPoro &);
        TListaPoro operator+(TListaPoro &);
        TListaPoro operator-(TListaPoro &);
        bool EsVacia() const;
        bool Insertar(const TPoro &);
        bool Borrar(TPoro &);
        bool Borrar(TListaPosicion &);
        TPoro Obtener(TListaPosicion &) const ;
        bool Buscar(TPoro &);
        int Longitud();
        TListaPosicion Primera() const;
        TListaPosicion Ultima() const;
        TListaPoro ExtraerRango (int n1, int n2);

        friend ostream & operator<<(ostream &, const TListaPoro  &);
};

#endif