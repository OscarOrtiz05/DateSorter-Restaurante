//
// Created by oscal on 10/17/2025.
//

#ifndef SITUACION_PROBLEMA_PARTE_2_QUICKSORT_H
#define SITUACION_PROBLEMA_PARTE_2_QUICKSORT_H

#include "lista_enlazada.h"

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


template <class T>
Node<T>* partition(List<T> datos, Node<T>* L, Node<T>* R) {
    Node<T> *i = NULL;
    Node<T> *j = L;

    Node<T> *pivot = R;

    T aux;

    while ( j != R) {
        if (j->value <= pivot->value) {
            if (i == NULL) {
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

    if (i == NULL) {
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


#endif //SITUACION_PROBLEMA_PARTE_2_QUICKSORT_H