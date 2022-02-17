#include <iostream>
#include <string>
using namespace std;
int periodSmart(string s) {
    int n = s.length();
    int period[n];
    period[0] = 0;
    for (int i = 1; i < n; i++) {
        period[i] = 0;
        int z = period[i-1];
        while (z > 0 && s[z] != s[i] ) {
            z = period[z-1];
        }
        if (s[z] == s[i])
            period[i] = z + 1;
    }
    return n-period[n-1];
}

int main() {
    char str[1000];
    cin.getline(str, 1000);
    cout<<periodSmart(str);
    return 0;
}