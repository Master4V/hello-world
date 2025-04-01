#include "Empresa.h"
#include "Fecha.h"
#include <cstdio>

//el constructor de la clase empresa debe crear un array dinámico de tamaño inicial 10
//debe inicializar a 0 los contadores de clientes (ncli) y contratos (ncon)
//y debe inicializar la constante nmaxcli a 100 y la variable nmaxcon a 10

Empresa::Empresa():nmaxcli(100) {
    this->ncli=0;
    this->ncon=0;
    this->contratos=new Contrato *[10]; //inicialmente capacidad para 10 Contratos
    this->nmaxcon=10;
}
//el destructor debe, además de eliminar el array dinámico creado en el constructor,
//eliminar los objetos clientes y contratos apuntados por ambos arrays

Empresa::~Empresa() {
    for(int i=0; i<this->ncon; i++) { //primero elimino los objetos contratos
        delete this->contratos[i];
    }
    delete [] this->contratos; //luego elimino el array de punteros
    for(int i=0; i<this->ncli; i++) { //primero elimino los objetos contratos
        delete this->clientes[i];
    }
//delete [] this->clientes; //ERROR el array clientes no es dinámico
}
//método auxiliar usado por el método crearContrato

int Empresa::altaCliente(Cliente *c) { //añade cliente apuntado por c al array clientes
    int pos=-1; //devuelve -1 si no cabe y la posición donde
    if (this->ncli<nmaxcli) { //donde lo he metido si cabe
        this->clientes[this->ncli]=c;
        pos=this->ncli;
        this->ncli++;
    }
    else {
    cout << "Lo siento, el cupo de clientes esta lleno";
    pos=-1;
    }
return pos;
}
//método auxiliar usado por el método crearContrato

int Empresa::buscarCliente(long int dni) const { //si no existe devuelve -1 y si existe
//devuelve la posición del cliente
    bool encontrado=false;
    int i = 0;
    while((i < ncon)||(!encontrado)){
        if(contratos[i]->getDniContrato() == dni){
            encontrado=true;
            return i;
            }
        else
            i++;
    }
}

void Empresa::crearContrato() { //EL ALUMNO DEBE TERMINAR DE IMPLEMENTAR ESTE METODO
    long int dni;
    int pos;
    cout << "Introduce DNI: ";
    cin >> dni;
//supongo que hay un metodo buscarCliente(dni) que devuelve -1 si no existe y si
//existe devuelve la posicion del cliente en el array this->cli
    pos=this->buscarCliente(dni); //OJO ESTE METODO HAY QUE IMPLEMENTARLO
    if (pos==-1) { //el cliente no existe y hay que darlo de alta
        int dia, mes, anio;
        char nombre[100];
        Cliente *c; //NO CREO NINGUN CLIENTE SINO SOLO UN PUNTERO A CLIENTE
        cout << "Introduce Nombre: ";
        cin >> nombre;
        cout << "Introduce Fecha (dd mm aaaa): ";
        cin >> dia >> mes >> anio;
        c=new Cliente(dni, nombre, Fecha(dia, mes, anio));
        pos=this->altaCliente(c); //OJO HAY QUE IMPLEMENTARLO
    }
//viendo cuanto vale la variable pos sé si el cliente se ha dado de alta o no
    if (pos!=-1) {
        int tipoContrato;
        cout << "Tipo de contrato a abrir (1-Tariafa Plana, 2-Movil): ";
        cin >> tipoContrato;
        int dia, mes, anio;
        cout << "Fecha del contrato (dia, mes, anio): ";
        cin >> dia >> mes >> anio;
        int minutosHablados;
        cout << "Introduzca los minutos hablados: ";
        cin >> minutosHablados;

        if(tipoContrato == 2){
            float precioMinuto;
            cout << "Precio minuto: ";
            cin >> precioMinuto;
            char nac[20];
            cout << "Nacionalidad: ";
            cin >> nac;
            contratos[ncon++] = new ContratoMovil(dni, Fecha(dia, mes, anio), precioMinuto, minutosHablados, nac);
        }else if(tipoContrato == 1){
            contratos[ncon++] = new ContratoTP(dni, Fecha(dia, mes, anio), minutosHablados);
        }else{
            cout << "Tipo de contrato invalido.\n Operación cancelada.\n";
        }
        if(ncon == nmaxcon){
            nmaxcon *= 2;
            Contrato **tmp = new Contrato*[nmaxcon];
            for(int i = 0; i < ncon; i++)
                tmp[i] = contratos[i];
            delete [] contratos;
            contratos = tmp;
        }
    }else{
        cout << "No se pudo registrar al cliente.\n";
    }
    cout << endl;
    }

bool Empresa::cancelarContrato(int idContrato){
    bool eliminado = false;
    int i = 0;
    while(i < ncon && !eliminado){
        if(contratos[i]->getIdContrato() == idContrato){
            delete contratos[i];
            while(i < ncon-1)
                contratos[i] = contratos[++i];
            ncon--;
            eliminado = true;
        }else i++;
    }
    if(ncon < nmaxcon/2){
        nmaxcon /= 2;
        Contrato **tmp = new Contrato*[nmaxcon];
        for(int i = 0; i < ncon; i++)
            tmp[i] = contratos[i];

        delete [] contratos;
        contratos = tmp;
    }
    return eliminado;
}

bool Empresa::bajaCliente(long int dni){
    bool eliminado = false;
    int i = 0;
    while(i < ncon){
        if(contratos[i]->getDniContrato() == dni){
            cancelarContrato(contratos[i]->getIdContrato());
        }else i++;
    }
    i = 0;
    while(i < ncli && !eliminado){
        if(clientes[i]->getDni() == dni){
            delete clientes[i];
            while(i < ncli-1){
                clientes[i] = clientes[i+1];
                i++;
            }
            ncli--;
            eliminado = true;
        }else i++;
    }
    return eliminado;
}

int Empresa::descuento (float porcentaje) const{
    int afectados = 0;
    porcentaje = 1 - porcentaje/100;

    for(int i = 0; i < ncon; i++){
        if(ContratoMovil *c = dynamic_cast<ContratoMovil*>(contratos[i])){
            c->setPrecioMinuto(c->getPrecioMinuto()*porcentaje);
            afectados++;
        }
    }
    return afectados;
}

int Empresa::nContratosTP() const{
    int tarifasPlanas = 0;
    for(int i = 0; i < ncon; i++){
        if(typeid(*contratos[i]) == typeid(ContratoTP))
            tarifasPlanas++;
    }
    return tarifasPlanas;
}

void Empresa::cargarDatos() {
    Fecha f1(29,2,2001), f2(31,1,2002), f3(1,2,2002);
    this->clientes[0] = new Cliente(75547001, "Peter Lee", f1);
    this->clientes[1] = new Cliente(45999000, "Juan Perez", Fecha(29,2,2000));
    this->clientes[2] = new Cliente(37000017, "Luis Bono", f2);
    this->ncli=3;
    this->contratos[0] = new ContratoMovil(75547001, f1, 0.12, 110, "DANES"); //habla 110m a 0.12€/m
    this->contratos[1] = new ContratoMovil(75547001, f2, 0.09, 170, "DANES"); //habla 170m a 0.09€/m
    this->contratos[2] = new ContratoTP(37000017, f3, 250); //habla 250m (300m a 10€, exceso 0.15€/m)
    this->contratos[3] = new ContratoTP(75547001, f1, 312); //habla 312m (300m a 10€, exceso 0.15€/m)
    this->contratos[4] = new ContratoMovil(45999000, f2, 0.10, 202, "ESPAÑOL"); //habla 202m a 0.10/m
    this->contratos[5] = new ContratoMovil(75547001, f2, 0.15, 80, "DANES"); //habla 80m a 0.15€/m
    this->contratos[6] = new ContratoTP(45999000, f3, 400); //habla 400m (300m a 10€, exceso 0.15€/m)
    this->ncon=7;
}

void Empresa::ver() const{
    cout << "La Empresa tiene "<<ncli<<" clientes y "<<ncon<<" contratos" << endl;
    cout << "Clientes:" << endl;
    for(int i = 0; i < ncli; i++)
        cout << *clientes[i] << endl;
    cout << endl << "Contratos:" << endl;
    for(int i = 0; i < ncon; i++){
        contratos[i]->ver();
        cout << endl;
    }
}
