
#ifndef CONTRATOMOVIL_H
#define CONTRATOMOVIL_H

#include <iostream> //cin, cout
#include "Fecha.h"
#include "Contrato.h"

using namespace std;

class ContratoMovil: public Contrato {
  float precioMinuto;
  int minutosHablados;
  char *nacionalidad;
public:
  ContratoMovil(long int dni, Fecha f, float p, int m, char *nac);//
  virtual ~ContratoMovil();//
  ContratoMovil(const ContratoMovil& c);//
  float getPrecioMinuto() const { return this->precioMinuto; }//
  int getMinutosHablados() const { return this->minutosHablados; }//
  const char* getNacionalidad() const { return this->nacionalidad; }//
  void setPrecioMinuto(float precio) { this->precioMinuto=precio; }//
  void setMinutosHablados(int m) { this->minutosHablados=m; }//
  void setNacionalidad(char* nac);//
  void ver() const;//
  float factura() const;//
  virtual void nada() const { ; };
};

ostream& operator<<(ostream &s, const ContratoMovil &c);//

#endif // CONTRATOMOVIL_H
