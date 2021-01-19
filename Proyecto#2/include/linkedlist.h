#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "list.h"
#include "node.h"
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename E>
class LinkedList : public List<E> {
private:
    Node<E> *head;
    Node<E> *current;
    Node<E> *tail;
    int size;

public:
    LinkedList() {
        tail = current = head = new Node<E>();
        size = 0;
    }
    ~LinkedList() {
        clear();
        delete head;
    }
    void insert(E element) {
        current->setNext(new Node<E>(element, current->getNext()));
        if (tail == current) {
            tail = current->getNext();
        }
        size++;
    }

    void append(E element) {
        tail->setNext(new Node<E>(element));
        tail = tail->getNext();
        size++;
    }
    E remove() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->getNext() == nullptr)
            throw runtime_error("No current element.");
        E result = current->getNext()->getElement();
        Node<E> *temp = current->getNext();
        current->setNext(temp->getNext());
        if (temp == tail)
            tail = current;
        delete temp;
        size--;
        return result;
    }
    void clear() {
        current = head->getNext();
        while (current != nullptr) {
            head->setNext(current->getNext());
            delete current;
            current = head->getNext();
        }
        tail = current = head;
        size = 0;
    }
    E getElement() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->getNext() == nullptr)
            throw runtime_error("No current element.");
        return current->getNext()->getElement();
    }
    void goToStart() {
        current = head;
    }
    void goToEnd() {
        current = tail;
    }
    void goToPos(int pos) {
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of range.");
        current = head;
        for (int i = 0; i < pos; i++) {
            current = current->getNext();
        }
    }
    void next() {
        if (current != tail) {
            current = current->getNext();
        }
    }
    void previous() {
        if (current != head) {
            Node<E> *temp = head;
            while (temp->getNext() != current)
                temp = temp->getNext();
            current = temp;
        }
    }
    bool atStart() {
        return current == head;
    }
    bool atEnd() {
        return current == tail;
    }
    int getPos() {
        int pos = 0;
        for (Node<E> *temp = head; temp != current; temp = temp->getNext()) {
            pos++;
        }
        return pos;
    }
    int getSize() {
        return size;
    }

    void reverse(){
        LinkedList<E> temp;
        goToStart();
        while(current->getNext()!=nullptr){
            temp.goToStart();
            temp.insert(getElement());
            current=current->getNext();
        }

        goToStart();
        temp.goToStart();

        while(current->getNext()!=nullptr){
            current=current->getNext();
            current->setElement(temp.getElement());
            temp.next();

        }

        temp.clear();
    }

    bool equals(List<E> * L){
        goToStart();
        L->goToStart();
        bool var= false;

        while (current->getNext() != nullptr){

            if (getElement()== L->getElement())
                var=true;
            L->next();
            current=current->getNext();
        }
        return var;


    }
};

#endif // LINKEDLIST_H
