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
    ifstream file(filename);
    string line;
    int i = 0;

    while (getline(file, line)){
        stringstream ss(line);
        string s, min, hr, day, month, year, n, r, o, waste;

        // obtiene cada elemento de la orden (tu mismo parseo)
        getline(ss, month,' ');
        getline(ss, day, ' ');
        getline(ss, hr, ':');
        getline(ss, min, ':');
        getline(ss, s, ' ');
        getline(ss, waste, ':');
        getline(ss, r, 'O');
        if (i == 345) {
            cout << r << endl;
        }
        getline(ss, waste, ':');
        getline(ss, o, '(');
        getline(ss, n, ')');

        if (i == 345) {
            cout << r << endl;
        }

        // convierte strings a numeros
        int _s   = stoi(s);
        int _min = stoi(min);
        int _hr  = stoi(hr);
        int _day = stoi(day);
        int _month = monthToInt(month);
        int _n   = stoi(n);

        // crea y guarda puntero

        auto aux = Order(_s,_min,_hr,_day,_month,_n,r,o);
        out.insertLast(aux);

        if ( i == 345) {
            cout << aux << endl;
        }

        ++i;
    }
    file.close();
    loaded = i;

}

int main(){

    const int n = 10000;       // capacidad
    List<Order> _orders;         // arreglo de PUNTEROS a Order
    int loaded = 0;            // cuántos cargamos

    loadOrderData("orders.txt", _orders, n, loaded);

    Order find = Order(8,53,18,1,1,277,"","Bratwurst con Chucrut");
    int i = 0;
    auto result = _orders.find(find,&i);
    cout << result->value << endl;

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
