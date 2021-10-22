#ifndef _TVECTOR_H_
#define _TVECTOR_H_
#include <iostream>
#include "tporo.h"
using namespace std;

class TVectorPoro{
	private:
		int dimension;
		TPoro *datos;
		TPoro error;

	public:
		TVectorPoro();
		TVectorPoro(int);
		TVectorPoro(const TVectorPoro &);
		~TVectorPoro();
		TVectorPoro & operator=(const TVectorPoro &);


		bool operator==(const TVectorPoro &);
		bool operator!=(const TVectorPoro &);
		TPoro & operator[](int);
		TPoro operator[](int) const;
		int Longitud();
		int Cantidad();
		bool Redimensionar(int);

	friend ostream & operator << (ostream &,  const TVectorPoro &);

};
#endif

