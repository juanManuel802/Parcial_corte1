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
            return Demanda < getCantidadCorr();
        } else {
            return Demanda < getCantidadExt();
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
        cout << getMarca()<<":  Combustible-> Corriente: "<<cantidadCorr << " /"<<capacidadCorr<<" Extra: "<<cantidadExt<<" /"<<capacidadExt<<"\n";
    }
};

class Operador {
private:
    Bombas bomba;
public:
    Operador(Bombas bomba) {this->bomba = bomba;}
    Bombas getBomba() const {return bomba;}

    Bombas operator+(Bombas &bomba) {
        bomba.setCantidad(bomba.getCapacidadCorr(), bomba.getCapacidadExt());
        return bomba;
    }
};
class Cliente {
    private:
    string nombre;
    int dinero;
    int corriente;
    int extra;

    public:
    Cliente(): nombre("Luk"),dinero(30000), corriente(0), extra(0) {}
    Cliente(string nombre, int dinero, int corriente, int extra) {
        this->nombre = nombre;
        this->dinero = dinero;
        this->corriente = corriente;
        this->extra = extra;
    }
    string getNombre() const {return nombre;}
    int getDinero() const {return dinero;}
    int getCorriente() const {return corriente;}
    int getExtra()const {return extra;}
    void setDinero(int dinero) {this->dinero = dinero;}
    void setCorriente(int corriente) {this->corriente = corriente;}
    void setExtra(int extra) {this->extra = extra;}

    void comprarGasolina (string tipoGasolina, int cantidad, Bombas &bomba) {
        bool gasolina = true;
        int consumo;
        consumo = getDinero() - bomba.calcularPrecios(gasolina, cantidad);
        if (tipoGasolina == "Extra" || tipoGasolina == "extra") {
            gasolina = false;
        }

        if (bomba.verificarCantidad(cantidad,gasolina)) {


            if (consumo>=0) {
                setDinero(consumo);
                cout << "Compra exitosa!!!!" << endl;
                if (gasolina) {
                    bomba.setCantidadCorr(bomba.getCantidadCorr()-cantidad);
                    setCorriente(getCorriente()+cantidad);
                    bomba.registrarCorr(cantidad);
                } else {
                    bomba.setCantidadExt(bomba.getCantidadExt()-cantidad);
                    setExtra(getExtra()+cantidad);
                    bomba.registrarExt(cantidad);
                }
            } else {
                cout << "El cliente " << getNombre() << " no tiene suficiente dinero" << endl;
            }
        } else {
            cout << "El operador ha llenado la bomba que no había suficiente gasolina" << bomba.getCantidadCorr() << bomba.getCantidadExt()<<endl;
            //Podria crar otro objeto bomba para igualarlo a mi bomba??
            Operador oper (bomba);
            bomba = oper + bomba; //this no va porque el primer valor es de un operador
        }
    }
   void mostrarDatos() {
    cout << nombre << "-> Dinero: " << dinero << " || cantidad de gasolina que posee-> Corriente: " << corriente << " Extra: " << extra << endl;
   }
};


void play (Cliente &cliente, Bombas &bomba) {
    string tipG;
    int gal;
    bool quit;
    cout << "Que tipo de gasolina deseas tanquear" << endl;
    cin >> tipG;
    cout << "Cuanto deseas tanquear?" << endl;
    cin >> gal;
    cliente.comprarGasolina(tipG,gal,bomba);
    cout << "Cliente " << cliente.getNombre() << ":\nExtra:  " << cliente.getExtra() <<"\nCorriente: "<<cliente.getCorriente()<<endl;
    
}

int main()
{
    bool quit = true;
    int count = 1;
    vector<Bombas> bombas;
    vector<Cliente> clientes;
  while (quit) {
        string nombre;
        int dinero, corriente, extra;
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

    quit = true;
    while (quit) {
        string marca;
        int capacidadCorr, capacidadExt, cantidadCorr, cantidadExt;
        printf("Ingresa la marca de la bomba: ");
        cin >> marca;
        cin.ignore();
        printf("Ingresa la capacidad de gasolina corriente: ");
        cin >> capacidadCorr;
        printf("Ingresa la capacidad de gasolina extra: ");
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
            printf("Bomba %d: Capacidad Corriente: %d, Capacidad Extra: %d, Cantidad Corriente: %d, Cantidad Extra: %d\n",
                i + 1, bombas[i].getCapacidadCorr(), bombas[i].getCapacidadExt(),
                bombas[i].getCantidadCorr(), bombas[i].getCantidadExt());
        }
        cin >> opBm;
        opBm--;
        cout << "Bomba seleccionada: ";
        bombas[opBm].mostrarDatos();

        play(clientes[opCl],bombas[opBm]);

        clientes[opCl].mostrarDatos();
        bombas[opBm].mostrarDatos();
        cout << "Deseas continuar? (1 para si, 0 para no)" <<endl;
        cin >> quit;
        quit = quit == 1;
    }
    
    

    return 0;
}
//Mostrar m+as datos (verificación de funcionamiento)