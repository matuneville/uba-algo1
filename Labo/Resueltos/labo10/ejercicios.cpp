#include "ejercicios.h"
#include "time.h"
#include <cmath>
#include <ctime>
#include "stdlib.h"
#include <string>
#include<iostream>

using namespace std;

int busquedaBinaria(vector<int> v, int x){  // hecha para ascendente o descendente
	int low = 0, high = int(v.size()-1);
    if (v[low] <= v[high]) {
        int mid;
        while (low <= high) {
            mid = (low + high) / 2;

            if (v[mid] == x)
                return mid;

            else if (v[mid] >= x)
                high = mid - 1;

            else
                low = mid + 1;
        }
    }

    else {
        int mid;
        while (low <= high) {
            mid = (low + high) / 2;

            if (v[mid] == x)
                return mid;

            else if (v[mid] >= x)
                low = mid + 1;

            else
                high = mid - 1;
        }
    }
    return -1;
}

int busquedaJumpSearch(vector<int> v, int x){   // hecha para ascendente
    int jump = floor(sqrt(v.size()));
    int piso = v.size() - jump, techo = v.size()-1;

    for (int i = 0; i < v.size(); i += jump) {
        if (v[i] >= x){
            piso = i - jump;
            techo = i;
            break;
        }
    }
    if (piso < 0) piso = 0;
    for (int i = piso; i <= techo ; ++i) {
        if (v[i] == x) return i;
    }
	return -1;
}

int buscar(vector<int> v, int x){
    return busquedaBinaria(v, x);
    //return busquedaJumpSearch(v, x);
}


double ejemplo_como_calcular_tiempos() {
    clock_t begin = clock();

    for(int i=0 ; i < 100000; i++){
        // nada
    }

    clock_t end = clock();
    double elapsed_msecs = double(end - begin) / CLOCKS_PER_SEC  * 1000; // mide el tiempo en milisegundos
    return elapsed_msecs;
}

vector<int> construir_vector(int size, string mode){
    vector<int> res {};
    time_t t;
    srand((unsigned) time(&t));
    int base = rand() % 100;
    int step;
    for(int i = 0; i < size; i++){
        step = rand() % 100;
        if(mode == "asc") {
            res.push_back(base+step);
            base += step;
        }
        if(mode == "desc"){
            res.push_back(base-step);
            base -= step;
        }
        if(mode == "azar"){
            res.push_back(step);
        }
        if(mode == "iguales"){
            res.push_back(base);
        }
    }
    return res;
}



int indicePico(vector<int> v){
    if (v[0] >= v[1]) return 0;
    else if (v[v.size()-1] >= v[v.size()-2]) return v.size()-1;
    else if (v.size() > 1){
        int i = 1;
        while (i < v.size()-2 && not(v[i] >= v[i-1] && v[i] >= v[i+1]))
            i++;
        return i;
    }
	return -1;
}

int puntoFijo(vector<int> v){
    int jump = floor(sqrt(v.size()));
    int piso = v.size() - jump, techo = v.size()-1;

    for (int i = 0; i < v.size(); i += jump) {
        if (v[i] >= i){
            piso = i - jump;
            techo = i;
            break;
        }
    }
    if (piso < 0) piso = 0;
    for (int i = piso; i <= techo ; ++i) {
        if (v[i] == i) return i;
    }
    return -1;
}   // hecho con jumpsearch

int encontrarRotado(vector<int> v, int x){ // no entendi esto
	return busquedaBinaria(v, x);
}

int menorMasGrande(vector<int> v, int x){
    int jump = floor(sqrt(v.size()));
    int piso = v.size() - jump, techo = v.size()-1;

    for (int i = 0; i < v.size(); i += jump) {
        if (v[i] >= x){
            piso = i - jump;
            techo = i;
            break;
        }
    }
    if (piso < 0) piso = 0;
    for (int i = piso; i <= techo ; ++i) {
        if (v[i] >= x) return i;
    }
    return -1;
}
/*
int menorMasGrande(vector<int> v, int x){
    for (int i = 0; i < v.size() ; ++i) {
        if (v[i] >= x) return i;
    }
    return -1;
}*/

// ************** auxiliares ********************************
int diferenciaAbsoluta (int a, int b){
    if (a > b) return a-b;
    else return b-a;
}

void removerElem(vector<int> &v, int index){
    vector<int> result;
    for (int i = 0; i < v.size(); ++i) {
        if (i != index)
            result.push_back(v[i]);
    }
}

bool estaOrdenado(vector<int> v){
    for(int i = 0; i < v.size() - 1; i++){
        if(v[i] > v[i+1])
            return false;
    }
    return true;
}

void bubbleSort(vector<int> &v){
    while(not estaOrdenado(v)) {
        for (int i = 0; i < v.size() - 1; i++) {
            if (v[i] > v[i + 1]) {
                int a = v[i];
                v[i] = v[i + 1];
                v[i + 1] = a;
            }
        }
    }
}
// **********************************************************

vector<int> masCercanoK(vector<int> v, int k,  int x){
    if (v[0] > v[v.size()-1]) bubbleSort(v);
    vector<int> diferenciasAbs, result;
    for (int i = 0; i < v.size(); ++i) {        // O(n)
        diferenciasAbs.push_back(diferenciaAbsoluta(v[i], x));
    }

    while(result.size() != k){
        int indiceDelMinimo = 0, minimo = diferenciasAbs[0];
        for (int i = 0; i < diferenciasAbs.size(); ++i) {
            if (diferenciasAbs[i] < minimo && diferenciasAbs[i] > 0){
                minimo = diferenciasAbs[i];
                indiceDelMinimo = i;
            }
        }
        result.push_back(v[indiceDelMinimo]);
        diferenciasAbs[indiceDelMinimo] = 0;

        int noHayMasNumeros = 0;
        for (int i = 0; i < diferenciasAbs.size(); ++i) {   // para ver si no hay mas para tomar
            noHayMasNumeros += diferenciasAbs[i];
        }
        if (noHayMasNumeros == 0) break;
    }
    bubbleSort(result);
    return result;
}
