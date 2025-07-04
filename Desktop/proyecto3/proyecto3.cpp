#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
using namespace std;

class Publicacion {
    private:
        string titulo, autor;
        int anioPublicacion;
    public:
        Publicacion(string t, string a, int anio) : titulo(t), autor(a), anioPublicacion(anio) {}
        virtual ~Publicacion() {}
        string getTitulo() { return titulo; }
        string getAutor() { return autor; }
        int getAnioPublicacion() { return anioPublicacion; }
        virtual void mostrarInfo() {
            cout << "Titulo: " << titulo << " Autor: " << autor << " Año: " << anioPublicacion << endl;
        }
        virtual string getTipo() = 0;
};

class Libro : public Publicacion {
    private:
        int numPaginas;
    public:
        Libro(string t, string a, int anio, int paginas) : Publicacion(t, a, anio), numPaginas(paginas) {}
        void mostrarInfo() override {
            Publicacion::mostrarInfo();
            cout << "Paginas: " << numPaginas << endl;
        }        
        string getTipo() override { return "Libro"; }
};

class Revista : public Publicacion {
    private:
        int numeroEdicion;
    public:
        Revista(string t, string a, int anio, int edicion) : Publicacion(t, a, anio), numeroEdicion(edicion) {}
        void mostrarInfo() override {
            Publicacion::mostrarInfo();
            cout << "Edicion: " << numeroEdicion << endl;
        }
        string getTipo() override { return "Revista"; }
};

class Periodico : public Publicacion {
    private:
        string fechaPublicacion, ciudad;
    public:
        Periodico(string t, string a, int anio, string fecha, string ciudad) : Publicacion(t, a, anio), fechaPublicacion(fecha), ciudad(ciudad) {}
        void mostrarInfo() override {
            Publicacion::mostrarInfo();
            cout << "Fecha: " << fechaPublicacion << "Ciudad: " << ciudad << endl;
        }
        string getTipo() override { return "Periodico"; }
};

Publicacion** catalogo = nullptr;
int capacidad = 5; 
int cantidad = 0;   

void redimensionar(int nuevaCapacidad) {
    Publicacion** nuevo = new Publicacion*[nuevaCapacidad];
    for(int i = 0; i < cantidad; i++) {
        nuevo[i] = catalogo[i];
    }
    delete[] catalogo;
    catalogo = nuevo;
    capacidad = nuevaCapacidad;
}

void agregarPublicacion() {
    int opcion;
    cin >> opcion; cin.ignore();
};

void mostrarPublicaciones() {
}

void buscarPorTitulo() {}

void eliminarPublicacion() {}

void estadisticas() {}

int main() {
    catalogo = new Publicacion*[capacidad];
    
    int opcion;
    do {
        cout << "\n=== MENU PRINCIPAL ===\n"
             << "1. Agregar publicacion\n"
             << "2. Mostrar publicaciones\n"
             << "3. Buscar por titulo\n"
             << "4. Eliminar publicacion\n"
             << "5. Ver estadisticas\n"
             << "6. Salir\n"
             << "Opcion: ";

        if(!(cin >> opcion)) {
            cout << "Opcion invalida\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch(opcion) {
            case 1: agregarPublicacion(); break;
            case 2: mostrarPublicaciones(); break;
            case 3: buscarPorTitulo(); break;
            case 4: eliminarPublicacion(); break;
            case 5: estadisticas(); break;
            case 6: break;
            default: cout << "Opcion no valida\n";
        }
    } while(opcion != 6);
    cout << "Programa terminado\n";
    return 0;
}