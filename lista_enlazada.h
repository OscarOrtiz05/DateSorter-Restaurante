//
// Created by oscal on 10/17/2025.
//

#ifndef SITUACION_PROBLEMA_PARTE_2_LISTA_ENLAZADA_H
#define SITUACION_PROBLEMA_PARTE_2_LISTA_ENLAZADA_H

#include <iostream>
using namespace std;

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
	}else {// Si no,  el anterior a aux (viejo first) es ahora el nodo nuevo
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

#endif //SITUACION_PROBLEMA_PARTE_2_LISTA_ENLAZADA_H
