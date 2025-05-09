#include <iostream>
#include <cstdlib>
#include <cstring> //strlen, strcpy
#include <iomanip> //std::setprecision
#include "Contrato.h"
#include "ContratoMovil.h"

ContratoMovil::ContratoMovil(long int dni, Fecha f, float p, int m, char *nac): Contrato(dni, f) {
  this->precioMinuto=p;
  this->minutosHablados=m;
  //this->nacionalidad=nac;  //MAL!!!!
  this->nacionalidad=new char [strlen(nac)+1];
  strcpy(this->nacionalidad, nac);
}

ContratoMovil::~ContratoMovil() {
  delete[] this->nacionalidad;
}

ContratoMovil::ContratoMovil(const ContratoMovil& c):Contrato(c.getDniContrato(), c.getFechaContrato()) { //... o usar esta otra cabecera
  this->precioMinuto = c.precioMinuto;
    this->minutosHablados = c.minutosHablados;
    this->nacionalidad = new char[strlen(c.nacionalidad)+1];
    strcpy(this->nacionalidad, c.nacionalidad);
}

void ContratoMovil::ver() const {
  Contrato::ver(); //IMPORTANTE: llamamos al ver que heredo de mi padre PARA QUE MUESTRE LO DEL PADRE
                   //... y a continuacion solo "me preocupo" de mostrar lo que es exclusivo del hijo
  cout << " " << this->minutosHablados << "m, " << this->nacionalidad << " " << this->precioMinuto;
}

float ContratoMovil::factura() const {
  return precioMinuto*minutosHablados;
}

void ContratoMovil::setNacionalidad(char* nac) {
    delete this->nacionalidad;
    this->nacionalidad = new char[strlen(nac)+1];
    strcpy(this->nacionalidad, nac);
}

ostream& operator<<(ostream &s, const ContratoMovil &c) {
  s << (Contrato &)c;
  s << " " << c.getMinutosHablados() << "m, " << c.getNacionalidad() << " " << c.getPrecioMinuto() << " - ";
  s << c.factura() << "�";
  return s;
}
