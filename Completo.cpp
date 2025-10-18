#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//Clase para las ordenes
class Order {
private:
    int sec, min, hr, day, month, n;
    string restaurant, name;
public:
    //Constructores
    Order() : sec(0), min(0), hr(0), day(0), month(0), n(0), restaurant(""), name("") {}
    Order(int _s, int _min, int _h, int _d, int _m, int _n, const string& _r, const string& _nm)
       : sec(_s), min(_min), hr(_h), day(_d), month(_m), n(_n),
         restaurant(_r), name(_nm) {}
    Order(int _s, int _min, int _h, int _d, int _m)
        : sec(_s), min(_min), hr(_h), day(_d), month(_m),
          n(0), restaurant(""), name("") {}

    //getters
    int getSec() const { return sec; }
    int getMin() const { return min; }
    int getHour() const { return hr; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getNumber() const { return n; }
    string getName() const { return name; }
    string getRestaurant() const { return restaurant; }

    //Se usa para comparar las ordenes
    int compareTime(const Order& other) const {

        if (month != other.month) {return (month < other.month) ? (-2) : (2);}
        if (day   != other.day)   {return (day   < other.day)   ? (-3) : (3);}
        if (hr    != other.hr)    {return (hr    < other.hr)    ? (-4) : (4);}
        if (min   != other.min)   {return (min   < other.min)   ? (-5) : (5);}
        if (sec   != other.sec)   {return (sec   < other.sec)   ? (-6) : (6);}
        return 0;
    }

    //Operadores de comparacion
    bool operator == (const Order& other) const {
        if (restaurant == other.restaurant) return (compareTime(other) == 0);
        return restaurant == other.restaurant;
    }
    bool operator != (const Order& other) const {
        if (restaurant == other.restaurant) return (compareTime(other) != 0);
        return restaurant != other.restaurant;
    }
    bool operator > (const Order& other) const {
        if (restaurant == other.restaurant) return (compareTime(other) > 0);
        return restaurant > other.restaurant;
    }
    bool operator < (const Order& other) const {
        if (restaurant == other.restaurant) return (compareTime(other) < 0);
        return restaurant < other.restaurant;
    }
    bool operator >= (const Order& other) const {
        if (restaurant == other.restaurant) return (compareTime(other) >= 0);
        return restaurant >= other.restaurant;
    }
    bool operator <= (const Order& other) const {
        if (restaurant == other.getRestaurant()) return (compareTime(other) <= 0);
        return restaurant <= other.getRestaurant();
    }

    //Cambia el mes de un numero a un string
    string monthName() const {
        switch (month) {
            case 1:
                return "ENE";
            case 2:
                return "FEB";
            case 3:
                return "MAR";
            case 4:
                return "ABR";
            case 5:
                return "MAY";
            case 6:
                return "JUN";
            case 7:
                return "JUL";
            case 8:
                return "AGO";
            case 9:
                return "SEP";
            case 10:
                return "OCT";
            case 11:
                return "NOV";
            case 12:
                return "DIC";
            default:
                return "???";
        }
    }

    //Operador de stream de output
    friend ostream& operator<<(ostream& os, const Order& order){
      os << order.monthName() << " " << order.getDay() << " " << order.getHour() << ":" << order.getMin() << ":" << order.getSec()
        << " R:" << order.getRestaurant() << " O:" << order.getName() << "(" << order.getNumber() << ")";

      return os;
    }

};


//------------------------------------------Clases Node y List utilizadas como las estructuras de datos de las ordenes -----------------------------------------------------
// class node: un valor y un puntero a otro nodo
template <class T>		//	Esta linea permite que podamos crear listas de cualquier tipo de dato
class Node
{	public:
		//	Atributos del nodo

		//int value;		// En lugar de que el nodo guarde un entero, guarda algo de tipo T
		T value; 			// valor almacenado

		Node<T> *prev; 	 	//	dir del nodo anterior
		Node<T> *next;		//	dir del nodo siguiente


		Node( T valor )
		{	this->value = valor;
			this->prev = nullptr;
			this->next = nullptr;
		}
};

//  Clase lista enlazada doble:
template <class T>
class List
{	//	Que atributos necesita??

	Node<T> *first;		//	puntero al primer nodo
	Node<T> *last; 		//	puntero al ultimo nodo
	int size;			//	numero de elementos que tiene la lista

	public:
		//	Que valores deberia tener la lista por default??
		List()
		{	this->first = nullptr;
			this->last = nullptr;
			this->size = 0;
		}

		//	Funciones similares a las de la lista simple


		int getSize(){ return size; }	//	Funcion para obtener el tamanaño de la lista
		void showList();				//	Funcion para mostrar la lista
		void showListReverse();			//	Funcion para mostrar la lista en reversa

		//	Funciones para insertar elementos
		void insertFirst(T);				//	al principio
		void insertLast(T);					//	al final
		bool insertAtIndex(int, T); 		//	en un indice

		//	Funciones para eliminar elementos
		void deleteFirst();					//	al principio
		void deleteLast();					//	al final
		void deleteAtIndex(int); 			//	en un indice

		Node<T>* find(T, int*);			//	Encontrar un valor
		void update(int, T);

		Node<T>* getFirst() {
			return first;
		}
		Node<T>* getLast() {
			return last;
		}
};
/**/
// inserta en un indice especifico
template<class T>
bool List<T>::insertAtIndex(int index, T newValue) {
	//Revisa si el indice esta fuera de rango
	if (index < 0 || index > this->size) {
		return false;
	}

	//	insertar al inicio
	if (index == 0 )
	{	this->insertFirst(newValue);
		return true;
	}
	// insertar al final
	if (index == this->size)
	{	this->insertLast(newValue);
		return true;
	}

	Node<T> *nuevo = new Node<T> ( newValue );

	if ( index < size/2 )		//	cuando es mas barato insertar desde el inicio
	{	Node<T> *aux = first;
		int i = 0;

		while( i < index-1 )
		{
			aux = aux->next;
			i++;
		}

		//Insertar el valor en el lugar adecuado
		nuevo->next = aux->next;
		nuevo->prev = aux;
		aux->next = nuevo;
		nuevo->next->prev = nuevo;

	}else {
		//	cuando es mas barato insertar desde el final
		Node<T> *aux = last;
		int i = size-1;
		while( i > index ) {
			aux = aux->prev;
			i--;
		}
		//Instertar en el lugar adecuado
		nuevo->prev = aux->prev;
		nuevo->next = aux;
		aux->prev = nuevo;
		nuevo->prev->next = nuevo;

	}

	//Actualiza el tamaño
	this->size++;
	return true;
}

template<class T>
Node<T>* List<T>::find( T value, int *index)
{
	Node<T> *aux = this->first;
	int i = 0;

	//Itera hasta ecnontrar el valor
	while ( aux != this->last ) {
		if (aux->value == value) {
			//Actualiza el indice y regresar el valor en memoria
			*index = i;
			return aux;
		}
		aux = aux->next;
		i++;
	}

	//Cambia el indice a -1 y regresa nullptr si no se encontro el valor
	*index = -1;
	return nullptr;
}


// inserta al inicio
template<class T>
void List<T>::deleteFirst()
{	//  Crear un  auxiliar que guarde la direccion de first
	Node<T> *aux = this->first;
	//	Crear una puntero, llamado segundo, que tome la direccion del nodo siguiente de first
	Node<T> *segundo = this->first->next;
	//  Asigna que el anterior a segundo ahora es last
	segundo->prev = this->last;
	//  Y que el siguiente de last es segundo
	this->last->next = segundo;

	// Elimina aux con un delete
	delete aux;

	// Ahora first es segundo
	this->first = segundo;

	// Decrementa el tamaño
	this->size--;
}

// inserta al inicio
template<class T>
void List<T>::insertFirst(T newValue)
{	// Crear un nodo nuevo
	Node<T> *nuevo = new Node<T>(newValue);

	// Crear un puntero auxiliar que guarde la direccion de first
	auto aux = this->first;

	// Hacer que el siguiente del nodo nuevo sea el auxiliar
	// Y que el first ahora sea el nodo nuevo
	nuevo->next = aux;
	this->first = nuevo;

	// Si la lista esta vacia
	if (size == 0) {
		//	el ultimo es tambien el nodo nuevo
		this->last = nuevo;
	}else {// Si no, el anterior a aux (viejo first) es ahora el nodo nuevo
		aux->prev = nuevo;
	}

	// Para asegurar que la lista es circular
	// El anterior a first es last
	// El siguiente de last es firs
	this->first->prev = this->last;
	this->last->next = this->first;


	//	Finalmente actualizar el tamaño de la lista
	this->size++;
}
// inserta al final
template<class T>
void List<T>::insertLast(T newValue)
{	// Crear un nodo nuevo
	Node<T> *nuevo = new Node<T>(newValue);

	// Crear un puntero auxiliar que guarde la direccion de last
	auto aux = this->last;

	// Hacer que el anterior del nodo nuevo sea el auxiliar (viejo last)
	// Y que el nuevo last ahora sea el nodo nuevo
	nuevo->prev = aux;
	this->last = nuevo;

	// Si la lista esta vacia
	if (size == 0) {
		//	el first es tambien el nodo nuevo
		this->first = nuevo;
	}else {
		// Si no, el siguiente a aux (viejo last) es ahora el nodo nuevo
		aux->next = nuevo;
	}
	// Para asegurar que la lista es circular
	// El anterior a first es last
	// El siguiente de last es firsT
	this->last->next = this->first;
	this->first->prev = this->last;

	//	Finalmente actualizar el tamaño de la lista
	this->size++;

}

template<class T>
void List<T>::showList( )
{	// Crea un nodo auxiliar para iterar en la lista
	// auxiliar inicia en first
	Node<T> *aux = this->first;

	// Declara un contador i que inicie en 0
	int i = 0;

	// Imprime el tamaño de la lista
	cout << "Size: \t " << this->size << endl;

	// Mientras i sea menor que el tamaño...
	while( i < this->size )
	{	// Imprime el nodo
		cout <<"\t[" << i << "]:\t" << aux->value << endl;
		// aux avanza a aux->next
		// i incrementa
		aux = aux->next;
		i++;
	}
	cout << endl;

}
template<class T>
void List<T>::showListReverse( )
{
	//Crea un nodo auxiliar para iterar en la lista
	//auxiliar inicia en last
	Node<T> *aux = this->last;

	// Declara un contador i que inicie en el ultimo indice
	int i = this->size - 1;
	// Imprime el tamaño de la lista
	cout << "Size: \t " << this->size << endl;

	//mientras i sea mayor o igual a uno
	while( i >= 0)
	{//imprime el nodo
		cout <<"\t[" << i << "]:\t" << aux->value << endl;

		//aux avanza a aux->prev
		//i disminuye
		aux = aux->prev;
		--i;
	}

	cout << endl;

}

template<class T>
void List<T>::deleteLast() {
	//  Crear un  auxiliar que guarde la direccion de last
	Node<T> *aux = this->last;
	//	Crear una puntero, llamado segundo, que tome la direccion del nodo anterior de last
	Node<T> *segundo = this->last->prev;
	//  Asigna que el siguiente a segundo ahora es first
	segundo->next = this->first;
	//  Y que el anterior de first es segundo
	this->first->prev = segundo;

	// Elimina aux con un delete
	delete aux;

	// Ahora last es segundo
	this->last = segundo;

	// Decrementa el tamaño
	this->size--;
}

template<class T>
void List<T>::deleteAtIndex(int index) {
	//	Borrar al inicio
	if (index == 0 ) {	this->deleteFirst(); }

	//Borrar al final
	if (index == this->size) { this->deleteLast(); }

	if ( index < size/2 )		//	cuando es mas barato insertar desde el inicio
	{
		Node<T> *aux = first;
		int i = 0;

		while( i < index-1 )
		{
			aux = aux->next;
			i++;
		}

		//Borra el valor deseado
		Node<T> *aux2 = aux->next;
		aux->next = aux->next->next;
		aux->next->prev = aux;
		delete aux2;
	}else {
		//	cuando es mas barato insertar desde el final
		Node<T> *aux = last;
		int i = size-1;
		while( i > index ) {
			aux = aux->prev;
			i--;
		}
		aux->prev->next = aux->next;
		aux->next->prev = aux->prev;
		delete aux;
	}

	this->size--;

}

template<class T>
void List<T>::update(int index, T newValue) {
	//	Actualiza al inicio
	if (index == 0 ) {	this->first->value = newValue; }

	//Actualiza al final
	if (index == this->size) { this->last->value = newValue; }

	if ( index < size/2 )		//	cuando es mas barato insertar desde el inicio
	{
		Node<T> *aux = first;
		int i = 0;
		//itera hasta encontrar el indice
		while( i < index-1 )
		{
			aux = aux->next;
			i++;
		}

		//Actualiza el valor deseado
		aux->next->value = newValue;

	}else {
		//	cuando es mas barato insertar desde el final
		Node<T> *aux = last;
		int i = size-1;
		//itera hasta llegar al indice
		while( i > index ) {
			aux = aux->prev;
			i--;
		}
		//Actualiza el valor deseado
		aux->value = newValue;
	}
}

//Stack utilizado en el algoritmo de quick sort
template <class T>
class Stack
{	List<T> lista;

public:
    Stack() {}

    int getSize()
    { return this->lista.getSize(); }

    bool isEmpty()
    {return this->lista.getSize()==0;}

    void show() {this->lista.showList();}

    void push(T newValue) {
        this->lista.insertFirst(newValue);
    }

    T pop() {
        T aux = this->lista.getFirst()->value;
        this->lista.deleteFirst();
        return aux;
    }
};

//-------------------Algoritmo de quick sort para Listas enlazadas dobles---------------------------------------
template <class T>
Node<T>* partition(List<T> datos, Node<T>* L, Node<T>* R) {
    Node<T> *i =  nullptr;
    Node<T> *j = L;

    Node<T> *pivot = R;

    T aux;

    while ( j != R) {
        if (j->value <= pivot->value) {
            if (i == nullptr) {
                i = L;
            }else {
                i = i->next;
            }

            aux = j->value;
            j->value = i->value;
            i->value = aux;
        }
        j = j->next;
    }

    if (i == nullptr) {
        i = L;
    } else {
        i = i->next;
    }

    aux = pivot->value;
    pivot->value = i->value;
    i->value = aux;

    return i;
}


template <class T>
void quicksort (List<T> datos) {
    Stack< Node<T>* > stack;

    Node<T>* L = datos.getFirst();
    Node<T>* R = datos.getLast();

    Node<T>* pivot;

    stack.push(L);
    stack.push(R);

    while ( !stack.isEmpty()) {
        R = stack.pop();
        L = stack.pop();

        pivot  = partition(datos, L, R);

        if ( L != pivot && L != pivot->prev) {
            stack.push(L);
            stack.push(pivot->prev);
        }

        if (R != pivot && R != pivot->next) {
            stack.push(pivot->next);
            stack.push(R);
        }
    }
}

//--------------------------------------------Funciones utilizadas en el main() ---------------------------------------------
//Convierte los strings de meses a int
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


// Carga datos a una Lista enlazada doble de Order
// - capacity: tamaño de los datos a cargar
void loadOrderData(const string& filename, List<Order>& out, int capacity) {
    //Setup de variables utilizadas para leer las entradas
    int i = 0;
    string rest,sline,m,r,nm,n,d,h,min,s;
    int index;

    //Se abre el archivo
    ifstream inFile2(filename);
    if (inFile2.is_open()) {
        // Extrae mes, dias, hora, minuto, segundo, restaurante, orden, precio
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

            //Convierte en enteros los valores que se necesitan como enteros
           int _m = monthToInt(m);
           int _d = stoi(d);
           int _h = stoi(h);
           int _min = stoi(min);
           int _s = stoi(s);
           int _n = stoi(n);

            // Crear un objeto Order y guardarlo en la lista
            auto order = Order(_s, _min, _h, _d, _m, _n, r, nm);
            out.insertFirst(order);
            i++;
        }
    }

    inFile2.close();

}

//Busca el nombre de un restaurante ingresado
template <class T>
Node<T>* encontrarRestaurante(string restaurante, List<T> lista) {
    Node<T>* aux = lista.getFirst();
    //Cicla la lista hasta encontrar la primer orden con ese restaurante
    do {
        if (aux->value.getRestaurant() == restaurante) {
            return aux;
        }
        aux = aux->next;
    }while (aux != lista.getFirst());

    //Regresa nullptr si no se encuentra el restaurante
    return nullptr;

}

int main(){

    const int n = 10000;       // capacidad
    List<Order> _orders;         // Lista de Order

    //Carga los datos del archivo a una lista enlazada
    loadOrderData("orders.txt", _orders, n);

    //Acomoda los datos por restaurante y por fecha de manera secundaria
    quicksort(_orders);

    //Guarda el nombre del restaurante
    string restaurant;
    cout << "Ingrese el nombre del restaurante: " << endl;
    getline(cin, restaurant);

    //Abre un archivo de texto donde se guardaran los datos
    ofstream ordenados("ordenados.txt");

    int i = 0;
    auto buscado = encontrarRestaurante(restaurant, _orders);
    while (buscado->value.getRestaurant() == restaurant) {
        //Muestra todos las ordenes de ese restaurante y las guarda en el archivo de texto
        cout << buscado->value << endl;
        ordenados << buscado->value << endl;
        buscado = buscado->next;
        ++i;
    }
    cout << "Se encontraron: " << i << " registros." << endl;

    //Cierra el archivo
    ordenados.close();
    
    return 0;
}
