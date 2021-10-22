#ifndef _TAVLPORO_H
#define _TAVLPORO_H
#include <iostream>
#include "tporo.h"
#include "tvectorporo.h"

using namespace std;

class TNodoAVL;

class TAVLPoro{
	friend class TNodoAVL;

	private:
		TNodoAVL *raiz;
		void InordenAux(TVectorPoro &, int &)const;
		void PreordenAux(TVectorPoro &, int &)const;
		void PostordenAux(TVectorPoro &, int &)const;
		void InsertarAux(int &);
		int Max(int, int);
		void Copia(const TAVLPoro &);
		int NodosAux(int ) const;
		TPoro maxValue();
		void updateBalanceFactor(bool);
		int treeDiff();
		void UpdateTree();
    void rr_rotation();
    void ll_rotation();
    void lr_rotation();
    void rl_rotation();

		


	public:
		TAVLPoro ();
		TAVLPoro (const TAVLPoro &);
		~TAVLPoro ();
		TAVLPoro & operator=( const TAVLPoro &);

		bool operator==( TAVLPoro &);
		bool operator!=( TAVLPoro &);

		bool EsVacio()const;
		bool Insertar(TPoro &);
		bool Buscar(TPoro &);
		bool Borrar(TPoro &);
		int Altura();
		TPoro Raiz();
		int Nodos()const;
		int NodosHoja();

		TVectorPoro Inorden()const;
		TVectorPoro Preorden()const;
		TVectorPoro Postorden()const;

		friend ostream & operator<<(ostream &, const TAVLPoro &);
};

class TNodoAVL{
	friend class TAVLPoro;
	private:
		TPoro item;
		TAVLPoro iz, de;
		int fe;
		



	public:
		TNodoAVL();
		TNodoAVL (TNodoAVL &);
		~TNodoAVL ();
		TNodoAVL & operator=( const TNodoAVL &);
};
#endif