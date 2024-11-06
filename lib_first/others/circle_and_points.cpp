#include<bits/stdc++.h>
using namespace std;

vector<long double> x(1010), y(1010);

long double cos(int i, int j, int k) {
    long double tx = x[i] - x[j];
    long double ty = y[i] - y[j];
    long double nx = x[k] - x[j];
    long double ny = y[k] - y[j];
    long double dot = tx * nx + ty * ny;
    long double len = hypot((long double)tx, ty)*hypot((long double)nx, ny);
    return dot / len;
}

long double sin(int i, int j, int k) {
    long double c = cos(i, j, k);
    return sqrt(1 - c * c);
}

long double R(int i, int j, int k) {
    long double A = hypot(x[i]-x[k], y[i]-y[k]);
    return A / sin(i, j, k) / 2;
}

pair<long double, long double> cent(int i, int j, int k) {
    long double tx = x[i] - x[j];
    long double ty = y[i] - y[j];
    long double nx = x[k] - x[j];
    long double ny = y[k] - y[j];
    long double t = (tx*tx + ty*ty - tx*nx - ty*ny) / (ty*nx - tx*ny) / 2;
    return {(long double)x[j] + nx/2. - t*ny, (long double) y[j] + ny/2. + t*nx};
}