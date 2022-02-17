#include <iostream>
#include <string>
#include <chrono>
#include <math.h>
using namespace std;
using namespace std::chrono;

string genString(int m) {
    int nMax = 500000;
    int a = 1000;
    double b = exp((log(nMax) - log(a)) / 99);
    int n = a * pow(b, m);
    string s(n, 'a');
    int q = ((int)rand()) % n + 1;

    for (int i = 0; i < q; i++)
        s[i] = 'a' + ((int)rand()) % 2;
    
    s[q] = 'c';
    
    for (int i = q + 1; i < n; i++)
        s[i] = s[i % q];
    
    return s;
}
double getResolution() {
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    typedef duration<double, seconds::period> secs;
    return duration_cast<secs>(end - start).count();
}
int periodNaive(string s) {
    int n = s.length();
    for (int p = 1; p <= n; p++) {
        int r = n - p;
        string s1 = s.substr(0, r);
        string s2 = s.substr(p, r);
        if (s1.compare(s2) == 0)
            return p;
    }
    return n;
}
int periodSmart(string s) {
    int n = s.length();
    int period[n];
    period[0] = 0;
    for (int i = 1; i < n; i++) {
        period[i] = 0;
        int z = period[i-1];
        while (z > 0 && s[z] != s[i] )
            z = period[z-1];

        if (s[z] == s[i])
            period[i] = z + 1;
    }
    return n-period[n-1];
}
void calcTime(double arrayTimes[], int iterations, int (*function)(string) ) {
    double r = getResolution();
    double Emax = 0.001;
    double minTime = (r * ((1 / Emax) + 1));
    typedef duration<double, seconds::period> secs;
    for (int n = 0; n < iterations; n++) {
        string s = genString(n);
        steady_clock::time_point start = steady_clock::now(), end;
        int counter = 0;
        do {
            function(s);
            end = steady_clock::now();
            counter++;
        } while (duration_cast<secs>(end - start).count() < minTime);
        arrayTimes[n] = duration_cast<secs>(end - start).count() / counter;
    }
}
int main() {
    int iterations = 100;
    double arrayPeriodNaive[iterations];
    calcTime(arrayPeriodNaive, iterations, periodNaive);
    for (int i = 0; i < iterations; i++){
        cout << arrayPeriodNaive[i] << endl;
    }
    double arrayPeriodSmart[iterations];
    calcTime(arrayPeriodSmart, iterations, periodSmart);
    for (int i = 0; i < iterations; i++)
        cout << arrayPeriodSmart[i] << endl;
}