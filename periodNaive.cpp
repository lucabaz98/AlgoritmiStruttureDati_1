#include <iostream>
#include <string>
using namespace std;

int periodNaive(string s) { //algoritmo quadratico
    int n = s.length();
    for (int p = 1; p <= n; p++) {
        int r = n - p; //bordo candidato
        string s1 = s.substr(0, r);
        string s2 = s.substr(p, r);
        if (s1.compare(s2) == 0) //trovato un bordo di lunghezza r
            return p;
    }
    return n;
}

int main() {
    char str[1000];
    cin.getline(str, 1000);
    cout<<periodNaive(str);
    return 0;
}