#include <iostream>
#include <string>

const int TAM = 100;

using namespace std;
class Empleado
{
private:
    string clave;
    string nombre;
    string domicilio;
    double sueldo;
    string reportaA;

public:
    Empleado(){}
    void operator=(Empleado &x)
    {
        clave = x.clave;
        nombre = x.nombre;
        domicilio = x.domicilio;
        sueldo = x.sueldo;
        reportaA = x.reportaA;
    }

    Empleado(const string &Clave, const string &Nombre, const string &Domicilio, double Sueldo, const string &ReportaA)
        : clave(Clave), nombre(Nombre), domicilio(Domicilio), sueldo(Sueldo), reportaA(ReportaA) {}

    string getClave() const { return clave; }
    string getNombre() const { return nombre; }
    string getDomicilio() const { return domicilio; }
    double getSueldo() const { return sueldo; }

    bool operator==(const Empleado &p) const
    {
        return (nombre == p.nombre && clave == p.clave && domicilio == p.domicilio && sueldo == p.sueldo && reportaA == p.reportaA);
    }

    friend ostream &operator<<(ostream &o, Empleado &p)
    {
        o << "Clave: " << p.clave << "\t Nombre: " << p.nombre << "\t Domicilio: " << p.domicilio << "\t Sueldo: " << p.sueldo << "\t ReportaA: " << p.reportaA << endl;
        return o;
    }

    friend istream &operator>>(istream &o, Empleado &p)
    {
        cout << "Ingresa clave: ";
        o >> p.clave;
        cout << "Ingresa nombre: ";
        o.ignore();
        getline(o, p.nombre);
        cout << "Ingresa domicilio: ";
        getline(o, p.domicilio);
        cout << "Ingresa sueldo: ";
        o >> p.sueldo;
        cout << "Ingresa reporte: ";
        o.ignore();
        getline(o, p.reportaA);
        return o;
    }


    bool operator!=(const Empleado &p) const
    {
        return !(*this == p);
    }

    bool operator<(const Empleado &p) const
    {
        return nombre < p.nombre;
    }

    bool operator>(const Empleado &p) const
    {
        return nombre > p.nombre;
    }

    Empleado operator+(const Empleado &p) const
    {
        return Empleado(nombre + p.nombre, clave, domicilio + p.domicilio, sueldo + p.sueldo, reportaA + p.reportaA);
    }
};

class Pila
{
private:
    Empleado datos[TAM];
    int ult;

    int inserta(Empleado elem, int pos)
    {
        if (llena() || pos < 0 || pos > ult + 1)
        {
            cout << "\n Error de insercion";
            return 0;
        }
        int i = ult + 1;
        while (i > pos)
        {
            datos[i] = datos[i - 1];
            i--;
        }
        datos[pos] = elem;
        ult++;
        return 1;
    }

    bool elimina(int pos)
    {
        if (vacia() || pos < 0 || pos > ult)
        {
            cout << "\n error de eliminacion";
            return true;
        }
        int i = pos;
        while (i < ult)
        {
            datos[i] = datos[i + 1];
            i++;
        }
        ult--;
        return false;
    }

public:
    Pila() : ult(-1) {}
    bool vacia() const
    {
        if (ult == -1)
            return true;
        return false;
    }

    bool llena() const
    {
        if (ult == TAM - 1)
            return true;
        return false;
    }

    int ultimo() const
    {
        return ult;
    }

    void push(Empleado p)
    {
        inserta(p, ultimo() + 1);
    }
    void pop()
    {
        elimina(ultimo());
    }
    Empleado top()
    {
        if (vacia())
        {
            throw runtime_error("La pila esta vacia.");
        }
        return datos[ult];
    }

    friend ostream &operator<<(ostream &o, Pila &L);
};
int main()
{
    int opcion;
    Pila PilaEmpleados;
    Empleado nuevoEmpleado("13", "Pedro Maromas", "Sabino #23", 15000.00, "Solin");
    PilaEmpleados.push(nuevoEmpleado);
    Empleado x;

    do
    {
        cout << "\nMenu:" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Top" << endl;
        cout << "4. Salir " << endl;
        cout << "\nElija una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "ingrese los datos del empleado\n";
            cin >>x;
            PilaEmpleados.push(x);


            break;
        case 2:
            PilaEmpleados.pop();
            cout << "Elemento eliminado de la pila." << endl;
            break;
        case 3:
            try
            {
                Empleado empleadoEnTop = PilaEmpleados.top();
                cout << "Elemento en la cima de la pila:" << endl;
                cout << empleadoEnTop << endl;
            }
            catch (const runtime_error &e)
            {
                cout << "Error: " << e.what() << endl;
            }
            break;
        case 4:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opción no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 4);

    return 0;
}
