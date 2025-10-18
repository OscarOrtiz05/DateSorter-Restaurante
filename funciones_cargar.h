//
// Created by oscal on 10/17/2025.
//

#ifndef SITUACION_PROBLEMA_PARTE_2_FUNCIONES_CARGAR_H
#define SITUACION_PROBLEMA_PARTE_2_FUNCIONES_CARGAR_H

#include "quicksort.h"
#include "date_sorter.h"
#include <fstream>
#include <sstream>

using namespace std;


//Convierte los strings de meses a int (igual que tu versión)
int monthToInt(string const &m){
    if (m == "ene") return 1;
    if (m == "Feb") return 2;
    if (m == "Mar") return 3;
    if (m == "Abr") return 4;
    if (m == "May") return 5;
    if (m == "Jun") return 6;
    if (m == "Jul") return 7;
    if (m == "Ago") return 8;
    if (m == "Sep") return 9;
    if (m == "Oct") return 10;
    if (m == "Nov") return 11;
    if (m == "Dic") return 12;
    return 0;
}


// Carga datos a un ARREGLO de punteros: out[i] = new Order(...)
// - capacity: tamaño máximo del arreglo
// - loaded (salida): cuántos elementos se cargaron realmente
void loadOrderData(const string& filename, List<Order>& out, int capacity) {
    int i = 0;
    string rest,sline,m,r,nm,n,d,h,min,s;
    int index;
    ifstream inFile2(filename);
    if (inFile2.is_open()) {
        // Extraer mes, d a, hora, minuto, segundo, restaurante, platillo y precio
        while (getline(inFile2, sline) && i < capacity) {
            string line = sline;
            index = line.find(" ");
            m = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(" ");
            d = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(":");
            h = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(":");
            min = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(" ");
            s = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(" O:");
            r = line.substr(2, index - 2);
            line = line.substr(index + 3);
            index = line.find("(");
            nm = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(")");
            n = line.substr(0, index);

           int _m = monthToInt(m);
           int _d = stoi(d);
           int _h = stoi(h);
           int _min = stoi(min);
           int _s = stoi(s);
           int _n = stoi(n);

            // Crear un objeto Order y guardarlo en el arreglo
            auto order = Order(_s, _min, _h, _d, _m, _n, r, nm);
            out.insertFirst(order);
            i++;
        }
    }

    inFile2.close();

}

template <class T>
Node<T>* encontrarRestaurante(string restaurante, List<T> lista) {
    Node<T>* aux = lista.getFirst();
    do {
        if (aux->value.getRestaurant() == restaurante) {
            return aux;
        }
        aux = aux->next;
    }while (aux != lista.getFirst());

    return nullptr;

}



#endif //SITUACION_PROBLEMA_PARTE_2_FUNCIONES_CARGAR_H

