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

void agregarPublicacionCatalogo(Publicacion* p) {
    if(cantidad >= capacidad) {
        redimensionar(capacidad * 2);
    }
    catalogo[cantidad++] = p;
}

void liberarMemoria() {
    for(int i = 0; i < cantidad; i++) {
        delete catalogo[i];
    }
    delete[] catalogo;
}

void agregarPublicacion() {
    int tipo, anio, paginas, edicion;
    string titulo, autor, fecha, ciudad;
    
    do {
        cout << "=== TIPOS DE PUBLICACION ===\n";
        cout << "1. Libro\n";
        cout << "2. Revista\n";
        cout << "3. Periodico\n";
        cout << "4. Volver al menu\n";
        cout << "Opcion: "; cin >> tipo;
        cin.ignore();
        if (tipo == 4) return;
        if (tipo < 1 || tipo > 3) {
            cout << "Opcion no valida\n"; 
            continue;
        }
        do {
            cout << "\nTitulo: "; getline(cin, titulo);
            if (titulo.empty()) cout << "El titulo no puede estar vacio\n";
        } while (titulo.empty());
        do {
            cout << "Autor: "; getline(cin, autor);
            if (autor.empty()) cout << "El autor no puede estar vacio\n";
        } while (autor.empty());
        while (true) {
            cout << "Anio (1500-2025): ";
            if (!(cin >> anio) || anio < 1500 || anio > 2025) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Anio invalido. Debe ser entre 1500 y 2025\n";
                continue;
            }
            break;
        }
        cin.ignore();
        switch(tipo) {
            case 1: {
                while (true) {
                    cout << "Numero de paginas: ";
                    if (!(cin >> paginas) || paginas <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Debe ser un numero mayor que 0\n";
                        continue;
                    }
                    break;
                }
                cin.ignore();
                if (cantidad >= capacidad) redimensionar(capacidad * 2);
                catalogo[cantidad++] = new Libro(titulo, autor, anio, paginas); 
                break;
            }
            case 2: {
                while (true) {
                    cout << "Numero de edicion: ";
                    if (!(cin >> edicion) || edicion <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Debe ser un numero mayor que 0\n";
                        continue;
                    }
                    break;
                }
                cin.ignore();
                if (cantidad >= capacidad) redimensionar(capacidad * 2);
                catalogo[cantidad++] = new Revista(titulo, autor, anio, edicion); 
                break;
            }
            case 3: {
                do {
                    cout << "Fecha (DD/MM/AAAA): "; 
                    getline(cin, fecha);
                    if (fecha.empty()) cout << "La fecha no puede estar vacia\n";
                } while (fecha.empty());
                do {
                    cout << "Ciudad: "; 
                    getline(cin, ciudad);
                    if (ciudad.empty()) cout << "La ciudad no puede estar vacia\n";
                } while (ciudad.empty());
                if (cantidad >= capacidad) redimensionar(capacidad * 2);
                catalogo[cantidad++] = new Periodico(titulo, autor, anio, fecha, ciudad);
                break;
            }
        }
    } while (true);
}

void mostrarPublicaciones() {
    if(cantidad == 0) {
        cout << "No hay publicaciones\n";
        return;
    }
    cout << "\n=== CATALOGO (" << cantidad << "/" << capacidad << ") ===\n";
    for(int i = 0; i < cantidad; i++) {
        cout << "\n#" << i+1 << " [" << catalogo[i]->getTipo() << "]\n";
        catalogo[i]->mostrarInfo();
    }
}

void buscarPorTitulo() {
    if (cantidad == 0) {
        cout << "\nNo hay publicaciones en el catalogo.\n";
        return;
    }
    string termino;
    cout << "\nIngrese el titulo a buscar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, termino);

    if (termino.empty()) {
        cout << "No ingreso ningun titulo para buscar\n";
        return;
    }
    transform(termino.begin(), termino.end(), termino.begin(), ::tolower);

    bool encontrado = false;
    cout << "\n=== RESULTADOS ===";
    for (int i = 0; i < cantidad; i++) {
        string titulo = catalogo[i]->getTitulo();
        string tituloLower = titulo;
        transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);
        if (tituloLower.find(termino) != string::npos) {
            if (!encontrado) {
                cout << "\nPublicaciones encontradas:\n";
            }
            encontrado = true;
            cout << "\n#"<< (i+1) << " - Tipo: " << catalogo[i]->getTipo() 
                 << "\nTitulo: " << titulo << "\n";
            catalogo[i]->mostrarInfo();
        }
    }
    if (!encontrado) {
        cout << "\nNo se encontraron publicaciones con: '" << termino << "'\n";
    }
}

void eliminarPublicacion() {
    if(cantidad == 0) {
        cout << "No hay publicaciones\n";
        return;
    }
    mostrarPublicaciones();
    int indice;
    cout << "\nIndice a eliminar (0=cancelar): ";
    if(!(cin >> indice) || indice < 0 || indice > cantidad) {
        cout << "Indice invalido\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if(indice == 0) {
        cout << "No se elimino\n"; return;
    }
    cout << "¿Eliminar '" << catalogo[indice-1]->getTitulo() << "'? (s/n): ";
    char op; cin >> op;
    cin.ignore();

    if(tolower(op) == 's') {
        delete catalogo[indice-1];
        for(int i = indice-1; i < cantidad-1; i++) {
            catalogo[i] = catalogo[i+1];
        }
        cantidad--;
        cout << "Eliminado\n";
        if(cantidad > 0 && cantidad <= capacidad/4) {
            redimensionar(capacidad/2);
        }
    }
    else {
        cout << "No se elimino\n";
    }
}

void estadisticas() {
    if(cantidad == 0) {
        cout << "No hay estadisticas\n"; return;
    }
    int libros = 0, revistas = 0, periodicos = 0;
    int minAnio = catalogo[0]->getAnioPublicacion();
    int maxAnio = catalogo[0]->getAnioPublicacion();
    string viejo = catalogo[0]->getTitulo();
    string nuevo = catalogo[0]->getTitulo();
    
    for(int i = 0; i < cantidad; i++) {
        string tipo = catalogo[i]->getTipo();
        if(tipo == "Libro") libros++;
        else if(tipo == "Revista") revistas++;
        else if(tipo == "Periodico") periodicos++; 
        
        int anio = catalogo[i]->getAnioPublicacion();
        if(anio < minAnio) {
            minAnio = anio;
            viejo = catalogo[i]->getTitulo();
        }
        if(anio > maxAnio) {
            maxAnio = anio;
            nuevo = catalogo[i]->getTitulo();
        }
    }
    cout << "\n=== ESTADISTICAS ===\n";
    cout << "Total: " << cantidad << endl;
    cout << "Libros: " << libros << endl;
    cout << "Revistas: " << revistas << endl;
    cout << "Periodicos: " << periodicos << endl;
    cout << "\nMas antiguo: " << viejo << " (" << minAnio << ")\n";
    cout << "Mas reciente: " << nuevo << " (" << maxAnio << ")\n";
}

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
    liberarMemoria();
    cout << "Programa terminado\n";
    return 0;
}