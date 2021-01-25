#ifndef NODO_H
#define NODO_H
#include "arraylist.h"

template <typename E>
class Nodo {
private:
    E element;
    ArrayList<E> * conexiones;
    ArrayList<E> * vecinos;

public:
    Nodo(E element){
        this->element = element;
        conexiones = new ArrayList<E>();
        vecinos = new ArrayList<E>();
    }
    Nodo(){
        conexiones = new ArrayList<E>();
        vecinos = new ArrayList<E>();
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

    ArrayList<Nodo<E> > * getConexiones(){
        ArrayList<Nodo<E> > * result = new ArrayList<Nodo<E> >();
        for (conexiones->goToStart(); !conexiones->atEnd(); conexiones->next())
            result->append(Nodo<E> (conexiones->getElement()));
        return result;
    }

    bool isVecino(E vecino){
        return vecinos->contains(vecino);
    }

    bool isLinked(E nodito){
        return conexiones->contains(nodito) && vecinos->contains(nodito);
    }

    void addVecino(E vecino){
        vecinos->append(vecino);
    }

    void removeVecino(E vecino){
        vecinos->goToPos(vecinos->indexOf(vecino));
        vecinos->remove();
    }

    void addConexion(E elemento){
        conexiones->append(elemento);
    }

    void removeConexion(E elemento){
        conexiones->remove(elemento);
    }

    void clear(){
        conexiones->clear();
    }

    ArrayList<Nodo<E> > * getVecinos(){
        cout << "getVecinos" << endl;
        ArrayList<Nodo<E> > * result = new ArrayList<Nodo<E> >();
        cout << "result" << endl;
        for (vecinos->goToStart(); !vecinos->atEnd(); vecinos->next()){
                cout << vecinos->getElement() << endl;
            result->append(Nodo<E> (vecinos->getElement()));
                cout << vecinos->getElement() << "x2" << endl;
        }
        cout << "finish" << endl;
        return result;
    }

};
#endif // NODO_H
