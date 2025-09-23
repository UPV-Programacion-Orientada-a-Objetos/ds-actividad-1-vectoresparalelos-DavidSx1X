#include <bits/stdc++.h>
using namespace std;

static inline string trim(string s) {
    auto l = s.find_first_not_of(" \t\r\n");
    auto r = s.find_last_not_of(" \t\r\n");
    if (l == string::npos) return "";
    return s.substr(l, r - l + 1);
}

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
    string line;
    size_t cnt = 0;
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

struct Data {
    unique_ptr<string[]> nombres;
    unique_ptr<string[]> paises;
    unique_ptr<string[]> disciplinas;
    unique_ptr<string[]> generos;
    unique_ptr<int[]>    oros;
    size_t n = 0;
};

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
    if (path.empty()) { cerr << "No se proporciono ruta.\n"; return 1; }

    size_t n = contarRegistrosValidos(path);
    if (n == 0) { cerr << "Sin registros validos.\n"; return 2; }

    Data d;
    d.nombres     = make_unique<string[]>(n);
    d.paises      = make_unique<string[]>(n);
    d.disciplinas = make_unique<string[]>(n);
    d.generos     = make_unique<string[]>(n);
    d.oros        = make_unique<int[]>(n);
    d.n = n;

    cout << "Capacidad fija creada para " << d.n << " registros.\n";
    return 0;
}
