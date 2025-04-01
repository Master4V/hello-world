#ifndef CONTRATOTP_H
#define CONTRATOTP_H

#include <iostream> //cin, cout
#include "Fecha.h"
#include "Contrato.h"

using namespace std;

class ContratoTP: public Contrato{
  static int minutosTP;
  static float precioTP;
  int minutosHablados;
  static const float precioExcesoMinutos;

public:
  ContratoTP(long int dni, Fecha f, int m);
  virtual ~ContratoTP();
  ContratoTP(const ContratoTP& c);
  //ContratoTP& operator=(const ContratoTP& c); //¿es necesario? pensar y reflexionad

  static int getLimiteMinutos() { return ContratoTP::minutosTP; }//
  static float getPrecio() { return ContratoTP::precioTP; }//
  static void setLimiteMinutos(int l);//
  static void setPrecio(float p);//
  static void setTarifaPlana(int m, float p);//
  void ver() const;//
  float factura() const;//
  virtual void nada() const { ; };
};

ostream& operator<<(ostream &s, const ContratoTP &c);

#endif // CONTRATOTP_H
