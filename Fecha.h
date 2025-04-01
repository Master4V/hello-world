#ifndef FECHA_H
#define FECHA_H

#include <iostream>

using namespace std;

class Fecha {
  int dia;
  int mes, anio;
public:
  Fecha(const int &dia, const int &m, const int &anio);//
  int getDia() const { return dia; }//
  int getMes() const { return this->mes; }//
  int getAnio() const { return this->anio; }//
  void setFecha(const int &dia, const int &mes, const int &a);//
  void ver() const;//
  bool bisiesto() const;//
  Fecha operator++();//   //++f
  Fecha operator++(int i); //f++
  Fecha operator+(const int &i) const; //f+5

  friend Fecha operator+(const int &i, const Fecha &f);
  friend ostream& operator<<(ostream &s, const Fecha &f);
};
Fecha operator+(const int &i, const Fecha &f);//
ostream& operator<<(ostream &s, const Fecha &f);
#endif
