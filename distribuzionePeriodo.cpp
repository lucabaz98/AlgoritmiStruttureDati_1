#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <math.h>
using namespace std;
using namespace std::chrono;

string genString(int n){
   
    string s(n,'a');
    int q = ((int) rand()) % n+1;
    for(int i = 0; i < q; i++){
        s[i] = 'a' + ((int) rand()) %2;
    }
    for(int i = q; i < n; i++){
        s[i] = s[i%q];
    }
    return s;
}
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
void distribuzionePeriodo(int distribuzione[], int dimensioneCampione){
    string s;

    for(int i = 0; i < dimensioneCampione; i++){
        s = genString(100);
        distribuzione[periodSmart(s)]+= 1;
    }
}

int main() {
    int distribuzione[101] = {0};
    int media[101] = {0};
    int varianza[101] = {0};

    for (int i = 0; i < 20; i++){
        distribuzionePeriodo(distribuzione, 1000000);
        for(int j = 1; j < 101; j++){
            media[j] += distribuzione[j];
            varianza[j] += pow(distribuzione[j],2);
        }
    }

    for (int i = 1; i < 101; i++){
        media[i] = (double)media[i]/20;
        varianza[i] = ((double)varianza[i]/20)-pow(media[i],2);
    }
    for(int i = 1; i < 101; i++)
        cout<<media[i]<<endl;
    for(int i = 1; i < 101; i++)
        cout<<varianza[i]<<endl;

    return 0;

}