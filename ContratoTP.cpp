#include "ContratoTP.h"

int ContratoTP::minutosTP=300;
float ContratoTP::precioTP=10;
const float ContratoTP::precioExcesoMinutos=0.15;


//static se pone en el .h (no se pone en el .cpp)
ContratoTP::ContratoTP(long int dni, Fecha f, int m) :Contrato(dni,f) {
    this->minutosHablados = minutosHablados;
}

ContratoTP::~ContratoTP(){

}

ContratoTP::ContratoTP(const ContratoTP& c) :Contrato(c.getDniContrato(),c.getFechaContrato()){
    this->minutosHablados = c.minutosHablados;
}

void ContratoTP::setLimiteMinutos(int l){
    minutosTP = l;
}

void ContratoTP::setPrecio(float p){
    precioTP = p;
}

void ContratoTP::setTarifaPlana(int m, float p) {
  ContratoTP::minutosTP=m; //puedo poner minutosTP=m ...pongo ContratoTP::minutosTP para recordar que es estatico
  ContratoTP::precioTP=p;  //puedo poner precioTP=p  ...pongo ContratoTP::precioTP para recordar que es estatico
}

void ContratoTP::ver() const{
    cout << *this;
}

float ContratoTP::factura() const{
    return precioTP + (minutosHablados>minutosTP?(minutosHablados-minutosTP)*precioExcesoMinutos:0);
}

ostream& operator<<(ostream &s, const ContratoTP &c){
    s << c.getDniContrato() << " (" << c.getIdContrato() << " - " << c.getFechaContrato() << ") " << c.getLimiteMinutos() << "m, " << ContratoTP::getLimiteMinutos() << "(" << ContratoTP::getPrecio() << ") " << " - " << c.factura() << "e";
    return s;
}
