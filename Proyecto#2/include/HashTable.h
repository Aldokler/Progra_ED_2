#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Dictionary.h"
#include "KVPair.h"
#include "LinkedList.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

template <typename K, typename V>
class HashTable : public Dictionary<K, V> {
private:
    LinkedList<KVPair<K, V> > *buckets;
    int nbuckets;
    int size;

    int h(K key) {
        return compress(hashCodePolynomial(key));
    }
    // Genera un c�digo hash polinomial con constante de 33
    template <typename T>
    int hashCodePolynomial(T key) {
        int a = 33;
        int result = 0;
        char* bytes = reinterpret_cast<char*>(&key);
        for (unsigned int i = 0; i < sizeof(K); i++) {
            result += bytes[i] * pow(a, i);
        }
        return result;
    }
    int hashCodePolynomial(string key) {
        int a = 33;
        int result = 0;
        for (unsigned int i = 0; i < key.length(); i++) {
            result += key[i] * pow(a, i);
        }
        return result;
    }
    // Funci�n de compresi�n por multiplicaci�n, suma y divisi�n
    int compress(int hashCode) {
        int a = 1097;
        int b = 1279;
        return abs(a * hashCode + b) % nbuckets;
    }
    // M�todo auxiliar que verifica que una llave no exista.
    // Si se encuentra la llave, lanza exepci�n.
    // La posici�n actual de la lista queda se�alando al final
    // de la lista.
    void checkNotExisting(K key){
        if (buckets[h(key)].contains(key))
            throw runtime_error("Duplicated key.");
    }
    // M�todo auxiliar que verifica que una llave s� exista.
    // Si no se encuentra la llave, lanza excepci�n
    // La posici�n actual de la lista queda se�alando al
    // elemento buscado.
    void checkExisting(K key){
        if (!buckets[h(key)].contains(key)) {
            throw runtime_error("Key not found.");
        }
    }

public:
    HashTable(int nbuckets = 1021) {
        buckets = new LinkedList<KVPair<K, V> >[nbuckets];
        this->nbuckets = nbuckets;
        size = 0;
    }
    ~HashTable() {
        delete [] buckets;
    }
    void insert(K key, V value) {
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        buckets[h(key)].append(p);
        size++;
    }
    V remove(K key) {
        checkExisting(key);
        KVPair<K, V> p(key);
        p = buckets[h(key)].remove();
        size--;
        return p.getValue();
    }
    V getValue(K key) {
        checkExisting(key);
        KVPair<K, V> p = buckets[h(key)].getElement();
        return p.getValue();
    }
    void setValue(K key, V value) {
        checkExisting(key);
        buckets[h(key)].remove();
        KVPair<K, V> p(key, value);
        buckets[h(key)].append(p);
    }
    void clear() {
        for (int i = 0; i < nbuckets; i++) {
            buckets[i].clear();
        }
    }
    bool contains(K key) {
        KVPair<K, V> p(key);
        return buckets[h(key)].contains(p);
    }
    List<K>* getKeys() {
        List<K> *keys = new LinkedList<K>();
        for(int x = 0; x < nbuckets; x++){
            buckets[x].goToStart();
            for (int y = 0; y < buckets[x].getSize(); y++){
                keys->append(buckets[x].getElement().getKey());
                buckets[x].next();
            }
            buckets[x].goToStart();
        }
        return keys;
    }
    List<V>* getValues() {
        List<V> *values = new LinkedList<V>();
        for(int x = 0; x < nbuckets; x++){
            buckets[x].goToStart();
            for (int y = 0; y < buckets[x].getSize(); y++){
                values->append(buckets[x].getElement().getValue());
                buckets[x].next();
            }
            buckets[x].goToStart();
        }
        return values;
    }
    int getSize() {
        return size;
    }

    void update(Dictionary<K, V> *D) {
        List<K> *keys = D->getKeys();
        List<V> *values = D->getValues();
        values->goToStart();
        for (keys->goToStart(); !keys->atEnd(); keys->next()){
            if (contains(keys->getElement()))
                setValue(keys->getElement(), values->getElement());
            else
                insert(keys->getElement(), values->getElement());
            values->next();
        }
    }

    void zip(List<K> *keys, List<V> *values) {
        int largo = keys->getSize();
        if (values->getSize() < largo)
            largo = values->getSize();
        keys->goToStart();
        values->goToStart();
        for (int x = 0; x < largo; x++){
            if (contains(keys->getElement())){}
            else
                insert(keys->getElement(), values->getElement());
            keys->next();
            values->next();
        }
    }
};

#endif // HASHTABLE_H
