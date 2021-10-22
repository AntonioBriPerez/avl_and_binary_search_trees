#ifndef _TPORO_H_
#define _TPORO_H_
#include <iostream>
using namespace std;

class TPoro{
	
	private:
		int x;
		int y;
		double volumen;
		char* color;
		
	public:
	
		TPoro();
		TPoro(int, int, double);
		TPoro(int, int, double, const char *);
		TPoro(const TPoro &);
		~TPoro();
		TPoro& operator=(const TPoro &);
		bool operator==(const TPoro &);
		bool operator!=(TPoro &);
		bool EsVacio() const;
		void Posicion(int, int);
		void Volumen(double);
		void Color(const char *);
		int PosicionX() const;
		int PosicionY() const;
		double Volumen() const;
		char * Color() const;

		
	
		friend ostream & operator<<(ostream &, const TPoro &);
	
};
#endif
