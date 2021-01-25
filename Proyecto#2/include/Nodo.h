#ifndef NODO_H
#define NODO_H
#include "arraylist.h"

template <typename E>
class Nodo {
private:
    E element;
    ArrayList<Nodo<E> > * conexiones;
    ArrayList<Nodo<E> > * vecinos;

public:
    Nodo(E element){
        this->element = element;
        conexiones = new ArrayList<Nodo<E> >();
        vecinos = new ArrayList<Nodo<E> >();
    }
    Nodo(){
        conexiones = new ArrayList<Nodo<E> >();
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

    ArrayList<Nodo<E> > getConexiones(){
        return conexiones;
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

    void addConexion(Nodo<E> elemento){
        conexiones->append(elemento);
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
