#include <bits/stdc++.h>
using namespace std;

static inline string trim(string s) {
    auto l = s.find_first_not_of(" \t\r\n");
    auto r = s.find_last_not_of(" \t\r\n");
    if (l == string::npos) return "";
    return s.substr(l, r - l + 1);
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string path;
    if (argc >= 2) {
        path = argv[1];
    } else {
        cout << "Ruta del CSV (ej. data/atletas.csv): ";
        getline(cin, path);
        path = trim(path);
    }

    if (path.empty()) {
        cerr << "No se proporciono ruta de archivo.\n";
        return 1;
    }

    ifstream in(path);
    if (!in) {
        cerr << "No se pudo abrir: " << path << "\n";
        return 2;
    }
    cout << "Archivo encontrado: " << path << "\n";
    return 0;
}
