#include "date_sorter.h"
#include "quicksort.h"
#include <fstream>
#include <sstream>
#include <string>
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
void loadOrderData(const string& filename, List<Order>& out, int capacity, int &loaded) {
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
        cout << "Registros procesados exitosamente: " << i << endl;
    }

    inFile2.close();

}

int main(){

    const int n = 10000;       // capacidad
    List<Order> _orders;         // arreglo de PUNTEROS a Order
    int loaded = 0;            // cuántos cargamos

    loadOrderData("orders.txt", _orders, n, loaded);

    quicksort(_orders);

    cout << _orders.getFirst()->value;

    // muestra los primeros 10 (o menos si loaded < 10)
    // int limit = (loaded < 10) ? loaded : 10;
    // for (int i = 0; i < limit; ++i){
    //     cout << *_orders[i] << '\n';
    // }




    // borra los objetos creados

    return 0;
}
