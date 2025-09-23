#include <bits/stdc++.h>
using namespace std;

static inline string trim(string s) {
    auto l = s.find_first_not_of(" \t\r\n");
    auto r = s.find_last_not_of(" \t\r\n");
    if (l == string::npos) return "";
    return s.substr(l, r - l + 1);
}

struct Data {
    unique_ptr<string[]> nombres;
    unique_ptr<string[]> paises;
    unique_ptr<string[]> disciplinas;
    unique_ptr<string[]> generos;
    unique_ptr<int[]>    oros;
    size_t n = 0;
};

static bool splitCSVLine(const string& line, array<string,5>& out) {
    vector<string> parts;
    string cur;
    for (char c : line) {
        if (c == ',') { parts.push_back(cur); cur.clear(); }
        else          { cur.push_back(c); }
    }
    parts.push_back(cur);
    if (parts.size() != 5) return false;
    for (int i = 0; i < 5; ++i) out[i] = trim(parts[i]);
    return true;
}

static size_t contarRegistrosValidos(const string& path) {
    ifstream in(path);
    if (!in) return 0;
    string line; size_t cnt = 0;
    while (getline(in, line)) {
        if (trim(line).empty()) continue;
        array<string,5> f;
        if (!splitCSVLine(line, f)) continue;
        if (f[0].empty() || f[1].empty() || f[2].empty() || f[3].empty() || f[4].empty()) continue;
        try {
            size_t idx=0; int m = stoi(f[4], &idx);
            if (idx != f[4].size() || m < 0) continue;
        } catch (...) { continue; }
        cnt++;
    }
    return cnt;
}

static bool cargarCSV(const string& path, Data& d, vector<string>& warnings) {
    size_t n = contarRegistrosValidos(path);
    if (n == 0) { warnings.push_back("No hay registros válidos."); return false; }

    d.nombres     = make_unique<string[]>(n);
    d.paises      = make_unique<string[]>(n);
    d.disciplinas = make_unique<string[]>(n);
    d.generos     = make_unique<string[]>(n);
    d.oros        = make_unique<int[]>(n);

    ifstream in(path);
    if (!in) { warnings.push_back("No se pudo abrir el archivo."); return false; }

    string line; size_t i = 0; size_t lineNo = 0;
    while (getline(in, line)) {
        lineNo++;
        if (trim(line).empty()) continue;
        array<string,5> f;
        if (!splitCSVLine(line, f)) { warnings.push_back("Linea " + to_string(lineNo) + ": 5 campos requeridos."); continue; }
        if (f[0].empty() || f[1].empty() || f[2].empty() || f[3].empty() || f[4].empty()) { warnings.push_back("Linea " + to_string(lineNo) + ": campo vacío."); continue; }
        int med; try {
            size_t idx=0; med = stoi(f[4], &idx);
            if (idx != f[4].size() || med < 0) { warnings.push_back("Linea " + to_string(lineNo) + ": medallas no válidas."); continue; }
        } catch (...) { warnings.push_back("Linea " + to_string(lineNo) + ": medallas no numéricas."); continue; }

        d.nombres[i]     = f[0];
        d.paises[i]      = f[1];
        d.disciplinas[i] = f[2];
        d.generos[i]     = f[3];
        d.oros[i]        = med;
        i++;
        if (i == n) break;
    }
    d.n = i;
    return d.n > 0;
}

static void imprimirRegistro(const Data& d, size_t i) {
    cout << "Nombre: " << d.nombres[i]
         << " | Pais: " << d.paises[i]
         << " | Disciplina: " << d.disciplinas[i]
         << " | Genero: " << d.generos[i]
         << " | Oros: " << d.oros[i] << "\n";
}

static vector<size_t> indicesDeNombre(const Data& d, const string& nombre) {
    vector<size_t> r;
    for (size_t i = 0; i < d.n; ++i) if (d.nombres[i] == nombre) r.push_back(i);
    return r;
}

static int totalOrosPais(const Data& d, const string& pais) {
    long long s = 0;
    for (size_t i = 0; i < d.n; ++i) if (d.paises[i] == pais) s += d.oros[i];
    return (int)s;
}

static vector<size_t> indicesTopOro(const Data& d) {
    vector<size_t> r; if (d.n == 0) return r;
    int mx = d.oros[0];
    for (size_t i = 1; i < d.n; ++i) mx = max(mx, d.oros[i]);
    for (size_t i = 0; i < d.n; ++i) if (d.oros[i] == mx) r.push_back(i);
    return r;
}

static void menu(const Data& d) {
    while (true) {
        cout << "\n=== Menu ===\n"
             << "1) Buscar atleta por nombre\n"
             << "2) Total de medallas de oro por pais\n"
             << "3) Atleta(s) con mas medallas de oro\n"
             << "4) Listar todos\n"
             << "0) Salir\n"
             << "Opcion: ";
        string op; if (!getline(cin, op)) return;
        op = trim(op);
        if (op == "0") return;
        else if (op == "1") {
            cout << "Nombre exacto: ";
            string nombre; getline(cin, nombre); nombre = trim(nombre);
            if (nombre.empty()) { cout << "Nombre vacío.\n"; continue; }
            auto idxs = indicesDeNombre(d, nombre);
            if (idxs.empty()) cout << "No se encontró.\n";
            else for (auto i : idxs) imprimirRegistro(d, i);
        } else if (op == "2") {
            cout << "Pais exacto: ";
            string pais; getline(cin, pais); pais = trim(pais);
            if (pais.empty()) { cout << "Pais vacío.\n"; continue; }
            cout << "Total de oros para " << pais << ": " << totalOrosPais(d, pais) << "\n";
        } else if (op == "3") {
            auto idxs = indicesTopOro(d);
            if (idxs.empty()) cout << "No hay registros.\n";
            else {
                cout << "Top oros:\n";
                for (auto i : idxs) imprimirRegistro(d, i);
            }
        } else if (op == "4") {
            for (size_t i = 0; i < d.n; ++i) imprimirRegistro(d, i);
        } else {
            cout << "Opción inválida.\n";
        }
    }
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string path;
    if (argc >= 2) path = argv[1];
    else {
        cout << "Ruta del CSV (ej. data/atletas.csv): ";
        getline(cin, path);
        path = trim(path);
    }
    if (path.empty()) { cerr << "No se proporcionó ruta.\n"; return 1; }

    vector<string> warnings;
    Data d;
    if (!cargarCSV(path, d, warnings)) {
        for (auto& w : warnings) cerr << "[AVISO] " << w << "\n";
        cerr << "No se pudo cargar datos válidos.\n";
        return 2;
    }
    for (auto& w : warnings) cerr << "[AVISO] " << w << "\n";

    cout << "Registros cargados: " << d.n << "\n";
    menu(d);
    return 0;
}
