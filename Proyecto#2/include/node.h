#ifndef NODE_H
#define NODE_H

template <typename E>
class Node {
private:
    E element;
    Node<E> *next;

public:
    Node(E element, Node<E> *next = nullptr) {
        this->element = element;
        this->next = next;
    }
    Node(Node<E> *next = nullptr) {
        this->next = next;
    }
    E getElement() {
        return element;
    }
    void setElement(E element) {
        this->element = element;
    }
    Node<E>* getNext() {
        return next;
    }
    void setNext(Node<E> *next) {
        this->next = next;
    }
};

#endif // NODE_H
