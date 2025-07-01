#include <iostream>
#include <string>
using namespace std;

class Publicacion {
    private:
        string titulo;
        string autor;
        int anioPublicacion;
    public:
        Publicacion(string t, string a, int anio) : titulo(t), autor(a), anioPublicacion(anio) {}
        string getTitulo() const { return titulo; }
        string getAutor() const { return autor; }
        int getAnioPublicacion() const { return anioPublicacion; }
        virtual void mostrarInformacion() const {
            cout << "Titulo: " << titulo << ", Autor: " << autor << ", Anio: " << anioPublicacion << endl;   
        }
        virtual string getTipo() const = 0;
};

class Libro : public Publicacion {
    int numPaginas;
    public:
        Libro(string t, string a, int anio, int paginas) : Publicacion(t, a, anio), numPaginas(paginas) {}
        void mostrarInformacion() const override {
            Publicacion::mostrarInformacion();
            cout << "Numero de Paginas: " << numPaginas << endl;
        }
        string getTipo() const override { return "Libro"; }
};

class Revista : public Publicacion {
    int numeroEdicion;
};

class Periodico : public Publicacion {
    string fechaPublicacion;
    string ciudad;                         
};

void agregarPublicacion() {
    int opcion;
    cin >> opcion; cin.ignore();
};

void mostrarPublicaciones() {
}

void buscarPorTitulo() {}

void eliminarPublicacion() {}

void estadisticas() {}

int main(){
    int opcion;
    do {
        cout << "1. Agregar nueva Publicacion\n";
        cout << "2. Mostrar todas las Publicaciones\n";
        cout << "3. Buscar publicacion por titulo\n";
        cout << "4. Eliminar Publicacion\n";
        cout << "5. Mostrar estadisticas\n";
        cout << "6. Salir del programa\n";
        cin >> opcion;
        cin.ignore();
        switch (opcion) {
            case 1: agregarPublicacion(); break;
            case 2: mostrarPublicaciones(); break;
            case 3: buscarPorTitulo(); break;
            case 4: eliminarPublicacion(); break;
            case 5: estadisticas(); break;
            case 6: cout << "Saliendo" << endl; break;
            default: cout << "Intente de nuevo." << endl;
        }
    }
    while (opcion != 6);
    return 0;
}