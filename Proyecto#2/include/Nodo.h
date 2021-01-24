#ifndef NODO_H
#define NODO_H
#include "HashTable.h"
#include "arraylist.h"

template <typename E>
class Nodo {
private:
    E element;
    HashTable<Nodo<E>, int> * conexiones;
    ArrayList<Nodo<E> > * vecinos;

public:
    Nodo(E element){
        this->element = element;
        conexiones = new HashTable<Nodo<E>, int>();
        vecinos = new ArrayList<Nodo<E> >();
    }
    void operator= (const Nodo &other) {
        element = other.element;
        conexiones = other.conexiones;
    }
    bool operator== (const Nodo &other) {
        return element == other.element;
    }
    bool operator!= (const Nodo &other) {
        return element != other.element;
    }
    bool operator< (const Nodo &other) {
        return element < other.element;
    }
    bool operator<= (const Nodo &other) {
        return element <= other.element;
    }
    bool operator> (const Nodo &other) {
        return element > other.element;
    }
    bool operator>= (const Nodo &other) {
        return element >= other.element;
    }

    ~Nodo(){
        delete conexiones;
    }

    E getElement(){
        return element;
    }

    HashTable<Nodo<E>, int> getConexiones(){
        return conexiones;
    }

    int getPeso(Nodo<E> nodito){
        return conexiones->getValue(nodito);
    }

    bool isVecino(Nodo<E> vecino){
        return vecinos->contains(vecino);
    }

    bool isLinked(Nodo<E> nodito){
        return conexiones->contains(nodito) && vecinos->contains(nodito);
    }

    void addVecino(Nodo<E> vecino){
        vecinos->append(vecino);
    }

    void removeVecino(Nodo<E> vecino){
        vecinos->goToPos(vecinos->indexOf(vecino));
        vecinos->remove();
    }

    void addConexion(Nodo<E> elemento, int peso){
        conexiones->insert(elemento, peso);
    }

    void removeConexion(Nodo<E> elemento){
        conexiones->remove(elemento);
    }

    void clear(){
        conexiones->clear();
    }

    ArrayList<Nodo<E> > * getVecinos(){
        return vecinos;
    }

};
#endif // NODO_H
