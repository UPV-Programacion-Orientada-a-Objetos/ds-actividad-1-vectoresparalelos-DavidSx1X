// ======================= Actividad - Vectores Paralelos =======================
// Problema 1: Registro de Atletas Olímpicos (arreglos estáticos paralelos)
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

// ------------------------------ Datos (paralelos) ------------------------------
struct DB {
    static const int MAX = 1000;      // capacidad fija requerida
    string nombres[MAX];
    string paises[MAX];
    string disciplinas[MAX];
    char   generos[MAX];              // 'M' o 'F' (o '?')
    int    oros[MAX];                 // medallas de oro
    int    n = 0;                     // registros válidos cargados
};

// ------------------------------ Utilidades ------------------------------------
static inline string trim(const string& s) {
    size_t i = 0, j = s.size();
    while (i < j && isspace((unsigned char)s[i])) i++;
    while (j > i && isspace((unsigned char)s[j - 1])) j--;
    return s.substr(i, j - i);
}

static inline bool esNumero(const string& s) {
    if (s.empty()) return false;
    for (char c : s) if (!isdigit((unsigned char)c)) return false;
    return true;
}

// Divide una línea CSV simple en exactamente 5 campos
static bool split5(const string& line, string& a, string& b, string& c, string& d, string& e) {
    a=b=c=d=e="";
    int comas = 0; string cur;
    for (char ch : line) {
        if (ch == ',') {
            if      (comas == 0) a = trim(cur);
            else if (comas == 1) b = trim(cur);
            else if (comas == 2) c = trim(cur);
            else if (comas == 3) d = trim(cur);
            else return false; // más de 4 comas
            cur.clear();
            comas++;
        } else {
            cur.push_back(ch);
        }
    }
    e = trim(cur);
    return comas == 4;
}

// ------------------------------ Carga de CSV ----------------------------------
// Reglas de validación para Problema 1:
// - 5 campos: nombre, país, disciplina, género (M/F), medallas (oro)
// - Ignora encabezado si la 1a línea contiene "nombre" y "medalla"
bool cargarCSV(const string& path, DB& db) {
    ifstream in(path.c_str());
    if (!in.is_open()) {
        cerr << "[ERROR] No se pudo abrir el archivo: " << path << "\n";
        return false;
    }

    string line; int linea = 0;
    while (getline(in, line)) {
        linea++;
        string t = trim(line);
        if (t.empty()) continue;

        if (linea == 1) {
            string low = t; for (char& c : low) c = (char)tolower((unsigned char)c);
            if (low.find("nombre") != string::npos && low.find("medalla") != string::npos) {
                continue; // encabezado
            }
        }

        if (db.n >= DB::MAX) {
            cerr << "[AVISO] Capacidad maxima (" << DB::MAX << ") alcanzada. Ignorando resto.\n";
            break;
        }

        string s0,s1,s2,s3,s4;
        if (!split5(t, s0,s1,s2,s3,s4)) {
            cerr << "[AVISO] Linea " << linea << ": formato invalido (5 campos requeridos).\n";
            continue;
        }
        if (!esNumero(s4)) {
            cerr << "[AVISO] Linea " << linea << ": medallas no numericas.\n";
            continue;
        }
        if (s3.empty()) {
            cerr << "[AVISO] Linea " << linea << ": genero vacio.\n";
            continue;
        }

        char g = (char)toupper((unsigned char)s3[0]);
        if (g != 'M' && g != 'F') {
            cerr << "[AVISO] Linea " << linea << ": genero invalido (use M/F).\n";
            continue;
        }

        int idx = db.n++;
        db.nombres[idx]     = s0;
        db.paises[idx]      = s1;
        db.disciplinas[idx] = s2;
        db.generos[idx]     = g;
        db.oros[idx]        = stoi(s4);
    }

    if (db.n == 0) {
        cerr << "[AVISO] No se cargaron registros validos.\n";
        return false;
    }
    return true;
}

// ------------------------------ Funciones pedido ------------------------------
// (2) Buscar atleta por nombre (insensible a mayúsculas/minúsculas)
void buscarPorNombre(const DB& db, const string& nombre) {
    string q = nombre; for (char& c : q) c = (char)tolower((unsigned char)c);
    bool encontrado = false;
    for (int i = 0; i < db.n; ++i) {
        string n = db.nombres[i]; for (char& c : n) c = (char)tolower((unsigned char)c);
        if (n == q) {
            cout << "Atleta: "      << db.nombres[i]     << "\n"
                 << "Pais: "        << db.paises[i]      << "\n"
                 << "Disciplina: "  << db.disciplinas[i] << "\n"
                 << "Genero: "      << db.generos[i]     << "\n"
                 << "Medallas ORO: "<< db.oros[i]        << "\n";
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontro al atleta \"" << nombre << "\".\n";
}

// (3) Total de medallas de oro por país (coincidencia exacta)
int totalOroPorPais(const DB& db, const string& pais) {
    int suma = 0;
    for (int i = 0; i < db.n; ++i) if (db.paises[i] == pais) suma += db.oros[i];
    return suma;
}

// (4) Atleta(s) con más medallas de oro
void atletasConMasOro(const DB& db) {
    if (db.n == 0) { cout << "Sin registros.\n"; return; }
    int mx = db.oros[0];
    for (int i = 1; i < db.n; ++i) if (db.oros[i] > mx) mx = db.oros[i];

    cout << "Atleta(s) con mas medallas de ORO (" << mx << "):\n";
    for (int i = 0; i < db.n; ++i) if (db.oros[i] == mx)
        cout << " - " << db.nombres[i] << " (" << db.paises[i] << ")\n";
}

// ------------------------------ Menú robusto ----------------------------------
static inline int leerOpcion() {
    string s;
    cout << "Opcion: ";
    if (!getline(cin, s)) return -1;        // EOF/Ctrl+Z
    s = trim(s);
    if (s.empty()) return -2;
    for (char c : s) if (!isdigit((unsigned char)c)) return -2;
    return (int)strtol(s.c_str(), nullptr, 10);
}

void menu(const DB& db) {
    while (true) {
        cout << "\n=== Menu ===\n"
             << "1) Buscar atleta por nombre\n"
             << "2) Total de medallas de ORO por pais\n"
             << "3) Atleta(s) con mas medallas de ORO\n"
             << "4) Listar todos\n"
             << "0) Salir\n";

        int op = leerOpcion();
        if (op == -1) { cout << "Saliendo...\n"; return; }
        if (op == -2) { cout << "Opcion invalida.\n"; continue; }

        if (op == 0) {
            cout << "Saliendo...\n"; return;
        } else if (op == 1) {
            cout << "Nombre exacto: ";
            string nombre; if (!getline(cin, nombre)) return;
            nombre = trim(nombre);
            if (nombre.empty()) { cout << "Nombre vacio.\n"; continue; }
            buscarPorNombre(db, nombre);
        } else if (op == 2) {
            cout << "Pais exacto: ";
            string pais; if (!getline(cin, pais)) return;
            pais = trim(pais);
            if (pais.empty()) { cout << "Pais vacio.\n"; continue; }
            cout << "Total de ORO para " << pais << ": "
                 << totalOroPorPais(db, pais) << "\n";
        } else if (op == 3) {
            atletasConMasOro(db);
        } else if (op == 4) {
            if (db.n == 0) cout << "Sin registros.\n";
            else {
                for (int i = 0; i < db.n; ++i) {
                    cout << i+1 << ") " << db.nombres[i]
                         << " | " << db.paises[i]
                         << " | " << db.disciplinas[i]
                         << " | " << db.generos[i]
                         << " | ORO:" << db.oros[i] << "\n";
                }
            }
        } else {
            cout << "Opcion invalida.\n";
        }
    }
}

// ---------------------------------- Main --------------------------------------
int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(&cout);   // <-- clave: hace flush de cout antes de leer con cin

    // 1) Ruta por argumento, si no la pide
    string path;
    if (argc >= 2) {
        path = argv[1];
    } else {
        cout << "Ruta del CSV (ej. data/data1.csv): ";
        if (!getline(cin, path)) {
            cerr << "[ERROR] No se proporciono ruta.\n";
            return 1;
        }
        path = trim(path);
        if (path.empty()) {
            cerr << "[ERROR] No se proporciono ruta.\n";
            return 1;
        }
    }

    // 2) Cargar datos
    DB db;
    if (!cargarCSV(path, db)) {
        cerr << "No se pudieron cargar datos validos desde \"" << path << "\".\n";
        return 2;
    }

    cout << "Archivo '" << path << "' cargado. Registros validos: " << db.n << "\n";

    // 3) Menú
    menu(db);
    return 0;
}
