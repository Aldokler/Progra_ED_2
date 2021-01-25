#ifndef LISTAADYACENTE_H
#define LISTAADYACENTE_H
#include "LinkedList.h"
#include "Nodo.h"

#include "KVPair.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <winbgim.h>
#include <math.h>

using namespace std;
/* Creado por Samuel Artavia//Aivy Masis// David Pastor

esta es la clase que genera y maneja las listas adyacentes y los nodos que conectan los grafos
para las varias formas de crear un laberinto, ademas este dibuja en pantalla el Laberinto
 y el algoritmo de djikstra es usado para resolverlos.
*/
template <typename E>
class ListaAdyacente{
    private:

        ArrayList<Nodo<E> > * escrofulas;
        LinkedList<int> *nodos;
        int size;
        int jugador;
        int lado;
        int fin;
        int tam = 30;
        int espacio;
        int midx;
        int midy;
        bool *visitados;
        int *camino;
        int *distancias;

        LinkedList<int> objects;

        ArrayList<KVPair<Nodo<E>, Nodo<E> > > * shuffle(ArrayList<KVPair<Nodo<E>, Nodo<E> > > * lista){
            ArrayList<KVPair<Nodo<E>, Nodo<E> > > * nuevo = new ArrayList<KVPair<Nodo<E>, Nodo<E> > >();
            while (lista->getSize() != 0){
                int pos = rand() % lista->getSize();
                lista->goToPos(pos);
                nuevo->append(lista->remove());
            }
            return nuevo;
        }

        int getOcurrence(ArrayList<Nodo<E> > lista, Nodo<E> element){
            for (int x = 0; x < lista.getSize(); x++)
                if (lista.contains(element))
                    return x;
            return -1;
        }

        bool finished(){
            for (escrofulas->goToStart(); !escrofulas->atEnd(); escrofulas->next())
                if (escrofulas->getElement().getConexiones()->getSize() == 0)
                    return false;
            return true;
        }
    public:
        ListaAdyacente(int size){

            this->size=size;
            lado = sqrt(size);
            nodos = new LinkedList<int> [size];
            camino = new int[size];
            distancias = new int[size];
            visitados = new bool[size];
            espacio = (lado+lado-1)*(tam/2);
            midx = (1360 - espacio)/2;
            midy = (760 - espacio)/2;
            escrofulas = new ArrayList<Nodo<E> >(size);
            for (int x = 0; x < size; x++){
                Nodo<E> escrofo(x);
                escrofulas->append(escrofo);
            }
            /*escrofulas->goToStart();
            for(int i=0;i<size;i++){
                if(i-lado>=0){
                    escrofulas->goToPos(i-lado);
                    Nodo<E> escrofo = (escrofulas->getElement());
                    escrofulas->goToPos(i);
                    escrofulas->getElement().addVecino(escrofo.getElement());
                }
                if(i-1>=0 && (i-1)/lado==i/lado){
                    escrofulas->goToPos(i-1);
                    Nodo<E> escrofo = (escrofulas->getElement());
                    escrofulas->goToPos(i);
                    escrofulas->getElement().addVecino(escrofo.getElement());
                }
                if(i+1<size && (i+1)/lado==i/lado){
                    escrofulas->goToPos(i+1);
                    Nodo<E> escrofo = (escrofulas->getElement());
                    escrofulas->goToPos(i);
                    escrofulas->getElement().addVecino(escrofo.getElement());
                }
                if(i+lado<size){
                    escrofulas->goToPos(i+lado);
                    Nodo<E> escrofo = (escrofulas->getElement());
                    escrofulas->goToPos(i);
                    escrofulas->getElement().addVecino(escrofo.getElement());
                }
                        cout << i << endl;
                escrofulas->next();
            }*/
        }
        ~ListaAdyacente(){
            for(int i=0;i<size;i++){
                nodos[i].clear();
            }
            delete nodos;
        }




        void clear(){//limpia las listas
            for(int i=0;i<size;i++){
                nodos[i].clear();
            }
        }



        void setSize(int size){//dependiendo de los nodos dentro de la lista de adyacencia esta funcion los modifica
            clear();
            this->size=size;
            lado = sqrt(size);
            nodos = new LinkedList<int> [size];
            espacio = (lado+lado-1)*(tam/2);
            midx = (1360 - espacio)/2;
            midy = (760 - espacio)/2;

            camino = new int[size];
            distancias = new int[size];
            visitados = new bool[size];

            escrofulas->clear();
            for (int x = 0; x < size; x++){
                Nodo<E> escrofo(x);
                escrofulas->append(escrofo);
            }
            /*escrofulas->goToStart();
            for(int i=0;i<size;i++){
                if(i-lado>=0){
                    escrofulas->goToPos(i-lado);
                    Nodo<E> escrofo = (escrofulas->getElement());
                    escrofulas->goToPos(i);
                    escrofulas->getElement().addVecino(escrofo.getElement());
                }
                if(i-1>=0 && (i-1)/lado==i/lado){
                    escrofulas->goToPos(i-1);
                    Nodo<E> escrofo = (escrofulas->getElement());
                    escrofulas->goToPos(i);
                    escrofulas->getElement().addVecino(escrofo.getElement());
                }
                if(i+1<size && (i+1)/lado==i/lado){
                    escrofulas->goToPos(i+1);
                    Nodo<E> escrofo = (escrofulas->getElement());
                    escrofulas->goToPos(i);
                    escrofulas->getElement().addVecino(escrofo.getElement());
                }
                if(i+lado<size){
                    escrofulas->goToPos(i+lado);
                    Nodo<E> escrofo = (escrofulas->getElement());
                    escrofulas->goToPos(i);
                    escrofulas->getElement().addVecino(escrofo.getElement());
                }
                escrofulas->next();
            }*/
        }



        void labDisplay(){// dibuja el laberinto con lineas gracias a MinGW en pantalla

            objectCheck();
            setcolor(15);
            setfillstyle(1,15);

            for(int i=0;i<size;i++){

                bar(tam*(i%lado) + midx,(i/lado)*tam + midy,tam/2+tam*(i%lado) + midx,(i/lado)*tam+tam/2 + midy);
                nodos[i].goToStart();
                for(int k=0;k<nodos[i].getSize();k++){
                    if(nodos[i].getElement()==i-1){
                        line(tam*(i%lado) + midx, (i/lado)*tam+8 + midy,tam*(i%lado)-tam + midx, (i/lado)*tam+8 + midy);
                    }
                    if(nodos[i].getElement()==i+1){
                        line(tam*(i%lado) + midx, (i/lado)*tam+8 + midy,tam*(i%lado)+tam + midx, (i/lado)*tam+8 + midy);
                    }
                    if(nodos[i].getElement()==i-lado){
                        line(tam*(i%lado)+8 + midx, (i/lado)*tam + midy,tam*(i%lado)+8 + midx, (i/lado)*tam+8-tam + midy);
                    }
                    if(nodos[i].getElement()==i+lado){
                        line(tam*(i%lado)+8 + midx, (i/lado)*tam + midy,tam*(i%lado)+8 + midx, (i/lado)*tam+8+tam + midy);
                    }
                    nodos[i].next();
                }

            }

            setfillstyle(1,1);
            bar(tam*(fin%lado) + midx,(fin/lado)*tam + midy,tam/2+tam*(fin%lado) + midx,(fin/lado)*tam+tam/2 + midy);
            setfillstyle(1,10);
            objects.goToStart();

            for(int i=0;i<objects.getSize();i++){

                int e=objects.getElement();
                bar(tam*(e%lado)+3 + midx,(e/lado)*tam+3 + midy,tam/2+tam*(e%lado)-3 + midx,(e/lado)*tam+tam/2-3 + midy);
                objects.next();
            }

        }
        /*
        vecinos se utiliza para crear un laberinto logico en el que cada uno de los nodos estara unido por
        sus cuatro vecinos nodo derecho, izquierdo, superior e inferior de existir estos.
        */
        void vecinos(){
            for(int i=0;i<size;i++){

                nodos[i].clear();
                if(i-lado>=0){
                    nodos[i].append(i-lado);
                }
                if(i-1>=0 && (i-1)/lado==i/lado){
                    nodos[i].append(i-1);
                }
                if(i+1<size && (i+1)/lado==i/lado){
                    nodos[i].append(i+1);
                }
                if(i+lado<size){
                    nodos[i].append(i+lado);
                }
            }
        }


        /*
        deepSearch se encarga de hacer una busqueda en base a la lista de adyacencia actual.
        Es necesaria para para la busquedaAux
        */
        void deepSearch(){

            bool visited[size] = {false};
            srand(time(0));
            int nodo = rand()%size;
            visited[nodo] = true;
            LinkedList<int> noVisitados;
            nodos[nodo].goToStart();
            for(int i=0;i<nodos[nodo].getSize();i++){

                noVisitados.append(nodos[nodo].getElement());
                nodos[nodo].next();
            }
            nodos[nodo].clear();
            for(int i=0;i<noVisitados.getSize();i++){

                noVisitados.goToPos(rand()%noVisitados.getSize());
                int nodo2 = noVisitados.getElement();
                if(visited[nodo2]==false){
                    busquedaAux(visited, nodo, nodo2);
                }
            fixCheck();
            }
        }

        /*
        Esta funcion se encarga de crear el laberinto con base al algoritmo de kruskal
        */
        void kruskal(){

            ArrayList<KVPair<Nodo<E>, Nodo<E> > > * arcos = new ArrayList<KVPair<Nodo<E> , Nodo<E> > >();

            ArrayList<Nodo<E> > * conjuntos = new ArrayList<Nodo<E> > [escrofulas->getSize()];

            escrofulas->goToStart();

            for (int x = 0; x < escrofulas->getSize(); x++){

                conjuntos[x].append(escrofulas->getElement());

                ArrayList<Nodo<E> > * vecinos;

                Nodo<E> jota = escrofulas->getElement();

                vecinos = jota.getVecinos();

                for(vecinos->goToStart(); !vecinos->atEnd(); vecinos->next()){

                        Nodo<E> uno = escrofulas->getElement();

                        Nodo<E> dos = vecinos->getElement();

                        KVPair<Nodo<E>, Nodo<E> > par;

                        par.setKey(uno);// error a veces..

                        par.setValue(dos);

                    arcos->append(par);

                }
                escrofulas->next();
            }
            //arcos = shuffle(arcos);

            for (arcos->goToStart(); !arcos->atEnd(); arcos->next()){
                int posUno = 0;
                int posDos = 0;
                for (int x = 0; x < escrofulas->getSize(); x++){
                    if (conjuntos[x].contains(arcos->getElement().getKey())){
                        posUno = x;
                        break;
                    }
                }
                for (int x = 0; x < escrofulas->getSize(); x++){
                    if (conjuntos[x].contains(arcos->getElement().getValue())){
                        posDos = x;
                        break;
                    }
                }
                conjuntos[posUno].goToPos(getOcurrence(conjuntos[posUno], arcos->getElement().getKey()));
                ArrayList<Nodo<E> > * one = &conjuntos[posUno];
                conjuntos[posDos].goToPos(getOcurrence(conjuntos[posDos], arcos->getElement().getValue()));
                ArrayList<Nodo<E> > * two = &conjuntos[posDos];
                if (!one->contains(arcos->getElement().getValue())){
                    escrofulas->goToPos(escrofulas->indexOf(arcos->getElement().getKey()));
                    escrofulas->getElement().addConexion(arcos->getElement().getValue().getElement());
                    escrofulas->goToPos(escrofulas->indexOf(arcos->getElement().getValue()));
                    escrofulas->getElement().addConexion(arcos->getElement().getKey().getElement());
                    if (one->getSize() >= two->getSize()){
                        two->goToStart();
                        while (!two->atEnd())
                            one->append(two->remove());
                    }
                    else{
                        one->goToStart();
                        while (!one->atEnd())
                            two->append(one->remove());
                    }
                }
                if (finished())
                    return;
            }
        }


        /*
        Esta funcion se encarga de crear el laberinto con base al algoritmo de prim
        */
        void prim(){
            ArrayList<Nodo<E> > * resultante = new ArrayList<Nodo<E> >();
            ArrayList<KVPair<Nodo<E>, Nodo<E> > > * arcos = new ArrayList<KVPair<Nodo<E>, Nodo<E> > >();
            E cualquiera = rand() % escrofulas->getSize();
            escrofulas->goToPos(cualquiera);
            resultante->append(escrofulas->getElement());
            ArrayList<Nodo<E> > * vecinoz = escrofulas->getElement().getVecinos();
            for(vecinoz->goToStart(); !vecinoz->atEnd(); vecinoz->next()){
                arcos->append(KVPair<Nodo<E>, Nodo<E> >(escrofulas->getElement(), vecinoz->getElement()));
            }
            while (!arcos->isEmpty()){
                cualquiera = rand() % arcos->getSize();
                arcos->goToPos(cualquiera);
                if (resultante->contains(arcos->getElement().getValue())){
                    arcos->remove();
                }
                else{
                    escrofulas->goToPos(escrofulas->indexOf(arcos->getElement().getKey()));
                    escrofulas->getElement().addConexion(arcos->getElement().getValue().getElement());
                    escrofulas->goToPos(escrofulas->indexOf(arcos->getElement().getValue()));
                    escrofulas->getElement().addConexion(arcos->getElement().getKey().getElement());
                    resultante->append(arcos->getElement().getValue());
                    vecinoz->clear();
                    vecinoz = arcos->getElement().getValue().getVecinos();
                    for (vecinoz->goToStart(); !vecinoz->atEnd(); vecinoz->next())
                        if (vecinoz->getElement() != arcos->getElement().getKey().getElement())
                            arcos->append(KVPair<Nodo<E>, Nodo<E> >(arcos->getElement().getValue(), vecinoz->getElement()));
                }
                if (finished())
                    return;
            }
        }


        /*
        addExtra es un metodo que se encarga de agregar arcos extra a el laberinto permitiendo que este se encicle.
        */
        void addExtra(int cantidad){
            srand(time(0));
            for(int i =0;i<cantidad;i++){

                int j = rand()%(size-1);
                if(j-lado>=0){
                    nodos[j].append(j-lado);
                }
                if(j-1>=0 && (j-1)/lado==j/lado){
                    nodos[j].append(j-1);
                }
                if(j+1<size && (j+1)/lado==j/lado){
                    nodos[j].append(j+1);
                }
                if(j+lado<size){
                    nodos[j].append(j+lado);
                }
            }
            fixCheck();
        }
        /*
        initialize es un metodo que se encarga de setear la posicion del jugador, la salida y los objetos
        del laberinto de manera alearotia.
        */
        void initialize(){
            srand(time(0));
            objects.clear();
            fin = rand()%size;
            jugador = rand()%size;
            while(jugador==fin){
                jugador = rand()%size;
            }
            for(int i=0;i<lado-1;i++){
                int e = rand()%size;
                while(e == jugador || e == fin){
                    e=rand()%size;
                }
                objects.append(e);
            }
        }
        /*
        setPlayerPos es un metodo encargado de revisar las movidas del jugador y si estas son
        validas de dibujar al jugador en pantalla con su nueva posicion.
        */
        void setPlayerPos(int pos=0){
            switch(pos){
            case 0:
                setfillstyle(1,4);
                bar(tam*(jugador%lado) + midx, (jugador/lado)*tam + midy,tam/2+tam*(jugador%lado) + midx, (jugador/lado)*tam+tam/2 + midy);
                break;
            case 1:
                if((jugador-lado >= 0 )&& (check(jugador-lado,jugador))){
                    jugador-=lado;
                }
                setfillstyle(1,4);
                bar(tam*(jugador%lado) + midx, (jugador/lado)*tam + midy,tam/2+tam*(jugador%lado) + midx, (jugador/lado)*tam+tam/2 + midy);
                break;
            case 2:
                if((jugador-1>=0 )&& ((jugador-1)/lado==jugador/lado && check(jugador-1, jugador))){
                    jugador--;
                }
                setfillstyle(1,4);
                bar(tam*(jugador%lado) + midx, (jugador/lado)*tam + midy, tam/2+tam*(jugador%lado) + midx, (jugador/lado)*tam+tam/2 + midy);
                break;
            case 3:
                if(jugador+1<size && (jugador+1)/lado==jugador/lado && check(jugador+1, jugador)){
                    jugador++;
                }
                setfillstyle(1,4);
                bar(tam*(jugador%lado) + midx, (jugador/lado)*tam + midy, tam/2+tam*(jugador%lado) + midx, (jugador/lado)*tam+tam/2 + midy);
                break;
            case 4:
                if((jugador+lado < size) && (check(jugador+lado, jugador))){
                    jugador+=lado;
                }
                setfillstyle(1,4);
                bar(tam*(jugador%lado) + midx, (jugador/lado)*tam + midy, tam/2+tam*(jugador%lado) + midx, (jugador/lado)*tam+tam/2 + midy);
                break;
            default:
                setfillstyle(1,4);
                bar(tam*(jugador%lado) + midx,(jugador/lado)*tam + midy,tam/2+tam*(jugador%lado) + midx,(jugador/lado)*tam+tam/2 + midy);
                break;
            }
        }

        /*
        djikstraAlgorithm es el metodo encargado de realizar el algoritmo de djikstra en la lista de
        adyacencia actual con respecto a la posicion del jugador. Inicializa los valores necesarios para que se
        de la recursion en el metodo djikstraAux.
        */
        void djikstraAlgorithm(){
            for(int i=0;i<size;i++){
                camino[i] = 99999;
                distancias[i] = 99999;
                visitados[i] = false;
            }
            camino[jugador]=jugador;
            distancias[jugador]=0;
            visitados[jugador]=true;
            djikstraAux(jugador);
        }
        /*
        hint se encarga de dibujar el laberinto con base al algoritmo de djikstra, mostrando el
        laberinto con un camino resaltado siendo este el mas corto entre el jugador y la salida.
        */
        void hint(){
            djikstraAlgorithm();
            setcolor(5);
            setfillstyle(1,15);
            int nodo = camino[fin];
            hintDraw(fin,nodo);
            setfillstyle(1,1);
            bar(tam*(fin%lado) + midx,(fin/lado)*tam + midy,tam/2+tam*(fin%lado) + midx,(fin/lado)*tam+tam/2 + midy);
            setfillstyle(1,4);
            bar(tam*(jugador%lado) + midx,(jugador/lado)*tam + midy,tam/2+tam*(jugador%lado) + midx,(jugador/lado)*tam+tam/2 + midy);

        }
        /*
        atEnd es un metodo que se encarga de revisar si el jugador se encuentra en la salida y si este ha recogido todos los
        objetos en el laberinto. Utilizado para avanzar de nivel.
        */
        bool atEnd(){
            if(jugador==fin && objects.getSize()==0){
                return true;
            }
            return false;
        }

        /*
        busquedaAux es un metodo encargado de implementar la recursion del algoritmo de busqueda por profundidad
        encargado de la parte logica de la creacion del laberinto.
        */
        void busquedaAux(bool visited[], int nodo, int nodo2){
            visited[nodo2]=true;
            nodos[nodo].append(nodo2);
            nodo=nodo2;

            LinkedList<int> noVisitados;
            nodos[nodo].goToStart();
            for(int i=0;i<nodos[nodo].getSize();i++){
                noVisitados.append(nodos[nodo].getElement());
                nodos[nodo].next();
            }
            nodos[nodo].clear();
            for(int i=0;i<noVisitados.getSize();i++){
                noVisitados.goToPos(rand()%noVisitados.getSize());
                nodo2 = noVisitados.getElement();
                if(visited[nodo2]==false){
                    busquedaAux(visited, nodo, nodo2);
                }
            }
        }
        /*
        djikstraAux es un metodo que se encarga de implementar la recursion del algoritmo de djikstra, encargado
        de la busqueda del camino mas corto entre sus nodos
        */
        void djikstraAux(int nodo){
            nodos[nodo].goToStart();
            for(int i=0;i<nodos[nodo].getSize();i++){
                int vecino = nodos[nodo].getElement();
                int distancia = distancias[nodo]+1;
                if(distancia<distancias[vecino]){
                    distancias[vecino]=distancia;
                    camino[vecino]=nodo;
                }
                nodos[nodo].next();
            }
            int distancia = 99999;
            int menor=0;
            for(int i=0;i<size;i++){
                if(visitados[i]==false && distancias[i]<distancia){
                    menor = i;
                    distancia = distancias[menor];
                }
            }
            visitados[menor]=true;
            if(!checkVisitados()){
                djikstraAux(menor);
            }
            return;
        }
        /*
        hintDraw es un metodo para dibujar el camino mas corto entre los nodos.
        */
        void hintDraw(int nodo, int nodo2){
            setcolor(14);
            setfillstyle(1,14);
            bar(tam*(nodo%lado) + midx,(nodo/lado)*tam + midy,tam/2+tam*(nodo%lado) + midx,(nodo/lado)*tam+tam/2 + midy);
            bar(tam*(nodo2%lado) + midx,(nodo2/lado)*tam + midy,tam/2+tam*(nodo2%lado) + midx,(nodo2/lado)*tam+tam/2 + midy);
            if(nodo2==nodo-1){
                line(tam*(nodo%lado) + midx, (nodo/lado)*tam+8 + midy,tam*(nodo%lado)-tam + midx, (nodo/lado)*tam+8 + midy);
            }
            if(nodo2==nodo+1){
                line(tam*(nodo%lado) + midx, (nodo/lado)*tam+8 + midy,tam*(nodo%lado)+tam + midx, (nodo/lado)*tam+8 + midy);
            }
            if(nodo2==nodo-lado){
                line(tam*(nodo%lado)+8 + midx, (nodo/lado)*tam + midy,tam*(nodo%lado)+8 + midx, (nodo/lado)*tam+8-tam + midy);
            }
            if(nodo2==nodo+lado){
                line(tam*(nodo%lado)+8 + midx, (nodo/lado)*tam + midy,tam*(nodo%lado)+8 + midx, (nodo/lado)*tam+8+tam + midy);
            }
            nodo=nodo2;
            nodo2=camino[nodo2];
            if(nodo!=jugador){
                hintDraw(nodo,nodo2);
            }
            return;
        }
        /*
        objectCheck es un metodo para identificar el objeto y removerlo si el jugador esta encima de el
        */

        void objectCheck(){
            objects.goToStart();
            for(int i=0;i<objects.getSize();i++){
                if(jugador==objects.getElement()){
                    objects.remove();
                }
                objects.next();
            }
        }
        /*
        checkVisitados es una funcion booleana que verifica si los objetos fueron todos visitados
        */
        bool checkVisitados(){
            for(int i=0;i<size;i++){
                if(visitados[i]==false){
                    return false;
                }
            }
            return true;
        }
        /*
        check es una funcion encargada de revisar si hay una instancia de un nodo en la lista de vecinos de otro. Utilizado
        para debuggear y para revisar que el movimiento del jugador sea valido.
        */
        bool check(int nodo, int nodo2){
            nodos[nodo2].goToStart();
            for(int i=0;i<nodos[nodo2].getSize();i++){
                if(nodos[nodo2].getElement()==nodo){
                    return true;
                }
                nodos[nodo2].next();
            }
            return false;
        }
        /*
        fixCheck es un metodo que revisa y aregla la union con los nodos, necesario para permitir el sentido doble del movimiento del jugador
        en el laberinto.
        */
        void fixCheck(){
            for(int i=0;i<size;i++){
                nodos[i].goToStart();
                for(int j=0;j<nodos[i].getSize();j++){
                    int e = nodos[i].getElement();
                    if(!check(i,e)){
                        nodos[e].append(i);
                    }
                    nodos[i].next();
                }
            }
        }

        void convert(){
            escrofulas->goToStart();
            for (int x = 0; x < size; x++){
                    cout << x << endl;
                for (escrofulas->getElement().getConexiones()->goToStart();
                    !escrofulas->getElement().getConexiones()->atEnd();
                     escrofulas->getElement().getConexiones()->next()){
                    nodos[x].append(escrofulas->getElement().getConexiones()->getElement().getElement());
                }
                escrofulas->next();
            }
        }

};

#endif // LISTAADYACENTE_H
