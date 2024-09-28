#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
class Bombas {
private:
    string marca;
    int capacidadCorr, capacidadExt, cantidadCorr, cantidadExt;
    int registroCorr;
    int registroExt;
    public:
    Bombas(): marca(""), capacidadCorr(500), capacidadExt(500), cantidadCorr(500), cantidadExt(500), registroCorr(0), registroExt(0)  {}
    Bombas(string marca, int capacidadCorr, int capacidadExt, int cantidadCorr, int cantidadExt) {
        this->marca = marca;
        this->capacidadCorr = capacidadCorr;
        this->capacidadExt = capacidadExt;
        this->cantidadCorr = cantidadCorr;
        this->cantidadExt = cantidadExt;
        registroCorr = 0;
        registroExt = 0;
    }
    string getMarca() const {return marca;}
    int getCapacidadCorr() const {return capacidadCorr;}
    int getCapacidadExt() const {return capacidadExt;}
    int getCantidadCorr() const {return cantidadCorr;}
    int getCantidadExt() const {return cantidadExt;}
    void setMarca( string marca) {this-> marca = marca;}
    void setCapacidad(int capacidadCorr, int capacidadExtra) {this->capacidadCorr = capacidadCorr; this->capacidadExt = capacidadExtra;}
    void setCantidad(int cantidadCorr, int cantidadExtra) {this->cantidadCorr = cantidadCorr; this->cantidadExt = cantidadExtra;}
    void setCantidadCorr(int corr) {cantidadCorr = corr;}
    void setCantidadExt(int ext) {cantidadExt = ext;}

    

    bool verificarCantidad(int Demanda, bool tipoGasolina) {
        if (tipoGasolina) {
            return Demanda <= getCantidadCorr();
        } else {
            return Demanda <= getCantidadExt();
        }
    }
    int calcularPrecios(bool tipoGasolina, int cantidad) {
        if (tipoGasolina) {
            return 2000*cantidad;
        }
        else {
            return 3500*cantidad;
        }
    }

    void registrarCorr(int corr) {
        registroCorr += corr;
    }
    void registrarExt(int ext) {
        registroExt += ext;
    }
        
    bool operator >(const Bombas &bomba2) {
        int registroMiBomba = this->registroCorr + this->registroExt;
        return registroMiBomba > (bomba2.registroCorr+bomba2.registroExt);
    }
    void inline mostrarDatos(){
        //Agregar datos de transacciones
        cout << getMarca()<<":  Combustible-> Corriente: "<<cantidadCorr << " /"<<capacidadCorr<<" Vendlida("<< registroCorr<< ") - Extra: "<<cantidadExt<<" /"<<capacidadExt<<" Venvida(" << registroExt << ")\n";
    }
};

class Operador {
private:
    Bombas bomba;
public:
    Operador(Bombas bomba) {this->bomba = bomba;}
    Bombas getBomba() const {return bomba;}

    void recargarBomba(Bombas &provedor) {
        //system("cls");
        int op;
        cout << "\nHola, soy el provedor. Qué desea hacer?:\n1)Recargar la bomba desde el proveedor principal.\n2)Recargar la bomba desde otra con suficiente combustible?\n";
        cin >> op;
        if (op=1) {
            int cant, op;
            bool comp;
            provedor.mostrarDatos();
            cout << "Qué tipo de combustible deseas transferir desde el operador hasta la bomba " << this->bomba.getMarca() << "?\n1)Corriente\n2)Extra\n3)Ambas" << endl;
            cin >> op;
            switch (op)
            {
            case 1:
                cout << "Cuanto desdeas transferir de gasolina corriente desde el proveedor hasta la bomba?" << endl;
                do {
                    cin >> cant;
                    //bomba.getCapacidadCorr()-bomba.getCantidadCorr()  Esto es lo que le falta a la bomba de combustible que se quiere proveer para llegar a su capacidad máxima
                    if (cant < (bomba.getCapacidadCorr()-bomba.getCantidadCorr())) {
                        bomba.setCantidadCorr(bomba.getCantidadCorr()+cant);
                    } else if (cant > (bomba.getCapacidadCorr()-bomba.getCantidadCorr())) {
                        cout << "No se permite valores por encima de la capacidad máxima (" << bomba.getCapacidadCorr() << ")\n";
                        comp = true;
                    } else if (cant = 0) {
                        comp = true;
                        //Aquí agragar el uso de exepciones
                        cout << "Ingresa un valor valido" << endl;
                    }                    
                } while (comp);
                bomba.mostrarDatos();
                break;
            case 2:
                cout << "Cuanto desdeas transferir de gasolina extra desde el proveedor hasta la bomba?" << endl;
                do {
                    cin >> cant;
                    //bomba.getCapacidadExt()-bomba.getCantidadExt()  Esto es lo que le falta a la bomba de combustible que se quiere proveer para llegar a su capacidad máxima
                    if (cant < (bomba.getCapacidadExt()-bomba.getCantidadExt())) {
                        bomba.setCantidadExt(bomba.getCantidadExt()+cant);
                    } else if (cant > (bomba.getCapacidadExt()-bomba.getCantidadExt())) {
                        cout << "No se permite valores por encima de la capacidad máxima (" << bomba.getCapacidadExt() << ")\n";
                        comp = true;
                    } else if (cant = 0) {
                        comp = true;
                        //Aquí agragar el uso de exepciones
                        cout << "Ingresa un valor valido" << endl;
                    }
                } while (comp);
                bomba.mostrarDatos();
            default:
                break;
            }
            //bomba = this->bomba; 
        } else if (op=2) {
            //usar el operador aqui
        }
    }

    //Este operador solo see aplicará a la bomba proveedor
    Bombas operator+(Bombas &bomba) {
        bomba.setCantidad(bomba.getCapacidadCorr(), bomba.getCapacidadExt());
        return bomba;
    }
};
class Cliente {
    private:
    string nombre;
    float dinero;
    int corriente;
    int extra;

    public:
    Cliente(): nombre("Luk"),dinero(30000), corriente(0), extra(0) {}
    Cliente(string nombre, float dinero, int corriente, int extra) {
        this->nombre = nombre;
        this->dinero = dinero;
        this->corriente = corriente;
        this->extra = extra;
    }
    string getNombre() const {return nombre;}
    float getDinero() const {return dinero;}
    int getCorriente() const {return corriente;}
    int getExtra()const {return extra;}
    void setDinero(int dinero) {this->dinero = dinero;}
    void setCorriente(int corriente) {this->corriente = corriente;}
    void setExtra(int extra) {this->extra = extra;}

    void comprarGasolina (string tipoGasolina, int cantidad, Bombas &bomba, Bombas &provedor) {
        bool gasolina = true;
        int consumo;
        consumo = getDinero() - bomba.calcularPrecios(gasolina, cantidad);
        if (tipoGasolina == "Extra" || tipoGasolina == "extra") { //Establece el tipo de gasolina de compra
            gasolina = false;
        }
        if (bomba.verificarCantidad(cantidad,gasolina)) { //Primero verifica la bomba tiene suficiente cantidad de la gasolina que se quiere comprar


            if (consumo>=0) { //Luego verifica si al cliente le alcanza la plata
                setDinero(consumo);
                cout << "Compra exitosa " << getNombre() << "!!!" << endl;
                cout << "Dinero (- " << bomba.calcularPrecios(gasolina, cantidad)<<"): " << endl;
                if (gasolina) { //Hace la compra según la gasolina elegida
                    bomba.setCantidadCorr(bomba.getCantidadCorr()-cantidad);
                    setCorriente(getCorriente()+cantidad);
                    bomba.registrarCorr(cantidad);
                } else {
                    bomba.setCantidadExt(bomba.getCantidadExt()-cantidad);
                    setExtra(getExtra()+cantidad);
                    bomba.registrarExt(cantidad);
                }
            } else {
                cout << "Saldo insuficiente para " << getNombre() << endl;
            }
        } else { //Si no hay suficiente cantidad de gasolina en la bomba
            //Podria crar otro objeto bomba para igualarlo a mi bomba?? - Funciona, pero es buena práctica?
            Operador oper (bomba);
            cout << "\nInsuficiente combustible, redirigiendo con el operador..." << endl;
            oper.recargarBomba(provedor);
            bomba = oper.getBomba(); //Si no es bueno hacer esto, podría cambiarse por un método de la clase bomba que haga esto.
            cout << "\nIntentando de nuevo la compra ...\n\n";
            comprarGasolina(tipoGasolina, cantidad, bomba, provedor);
        }
    }
   void mostrarDatos() {
    cout << nombre << "-> Dinero: " << dinero << " || cantidad de gasolina que posee-> Corriente: " << corriente << " Extra: " << extra << endl;
   }
};


void play (Cliente &cliente, Bombas &bomba, Bombas &provedor) {
    string tipG;
    int gal, gasto;
    float dineroInicial;
    bool quit = true;
    dineroInicial = cliente.getDinero();
    while (quit)
    {    
    cout << "Que tipo de gasolina deseas tanquear" << endl;
    cin >> tipG;
    cout << "Cuanto deseas tanquear?" << endl;
    cin >> gal;
    cliente.comprarGasolina(tipG,gal,bomba,provedor); 
    cliente.mostrarDatos();
    cout <<"\n\nDeseas volver a tanquear en la misma bomba con el mismo usuario? (1 para si, 0 para no)\n";
    cin >> quit;
    quit = quit == 1;
    }
    system("cls");
    
}

int main()
{
    bool quit = true;
    int count = 1;
    vector<Bombas> bombas;
    vector<Cliente> clientes;
    //Objeto de clase bomba proveedor de combustible
    Bombas provedor("Proveedor",10000,10000,10000,10000);
  while (quit) {
        string nombre;
        int corriente, extra;
        float dinero;
        printf("Ingresa el nombre del usuario %d: ", count);
        getline(cin, nombre);
        printf("Ingresa el dinero del usuario %d: ", count);
        cin >> dinero;
        cin.ignore(); 
        printf("Ingresa su cantidad de gasolina corriente: ");
        cin >> corriente;
        cin.ignore();
        printf("Ingresa su cantidad de gasolina extra: ");
        cin >> extra;
        cin.ignore();

        Cliente Cliente(nombre, dinero, corriente, extra);
        clientes.push_back(Cliente);

        printf("Cliente agregado: %s\n", Cliente.getNombre().c_str());
        printf("¿Desea agregar otro cliente? (1 para sí, 0 para no): ");
        cin >> quit;
        cin.ignore();
        count++;
    } 
    system("cls");

    quit = true;
    while (quit) {
        string marca;
        int capacidadCorr, capacidadExt, cantidadCorr, cantidadExt;
        printf("Ingresa la marca de la bomba: ");
        cin >> marca;
        cin.ignore();
        printf("Ingresa la capacidad máxima de almacenamiento del tanque de gasolina corriente: ");
        cin >> capacidadCorr;
        printf("Ingresa la capacidad máxima de almacenamiento del tanque de gasolina extra: ");
        cin >> capacidadExt;
        printf("Ingresa la cantidad de gasolina corriente: ");
        cin >> cantidadCorr;
        printf("Ingresa la cantidad de gasolina extra: ");
        cin >> cantidadExt;

        Bombas Bomba(marca, capacidadCorr, capacidadExt, cantidadCorr, cantidadExt);
        bombas.push_back(Bomba);

        printf("Bomba agregada: Capacidad Corriente: %d, Capacidad Extra: %d, Cantidad Corriente: %d, Cantidad Extra: %d\n",
               capacidadCorr, capacidadExt, cantidadCorr, cantidadExt);

        printf("¿Desea agregar otra bomba? (1 para sí, 0 para no): ");
        cin >> quit;
        quit = quit == 1;
    }
    system("cls");
    //Parte de selección de objetos a utilizar e implementacion de la bomba
    quit = true;
    while (quit)
    {
        int opCl, opBm;
        cout << "Selecciona un cliente: \n";
        for (int i = 0; i < clientes.size(); i++) {
            printf("%d) %s.\n", i+1, clientes[i].getNombre().c_str());
        }
        cin >> opCl;
        opCl--;
        cout << "Cliente seleccionado: ";
        clientes[opCl].mostrarDatos();
        cout << "Selecciona una bomba \n";
        for (int i = 0; i < bombas.size(); i++) {
            printf("%d)%s-> Capacidad Corriente: %d, Capacidad Extra: %d, Cantidad Corriente: %d, Cantidad Extra: %d\n",
                i + 1,bombas[i].getMarca().c_str(), bombas[i].getCapacidadCorr(), bombas[i].getCapacidadExt(),
                bombas[i].getCantidadCorr(), bombas[i].getCantidadExt());
        }
        cin >> opBm;
        opBm--;
        cout << "Bomba seleccionada: ";
        bombas[opBm].mostrarDatos();

        play(clientes[opCl],bombas[opBm],provedor);

        clientes[opCl].mostrarDatos();
        bombas[opBm].mostrarDatos();
        system("cls");
        cout << "Gracias por utilizar nuestro servicio.\nDeseas seguir en el programa? (1 para si, 0 para no)" <<endl;
        cin >> quit;
        quit = quit == 1;
        system("cls");
    }
    
    

    return 0;
}
//Mostrar m+as datos (verificación de funcionamiento)