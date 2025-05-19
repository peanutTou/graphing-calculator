#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <iostream>
#include <iomanip>
#include <string>
#include "../linked/linked.h"
#include "assert.h"

using namespace std;

template <typename T>
class Queue{
public:
    class Iterator{
    public:
        friend class Queue;

        Iterator():_ptr(nullptr){}
        Iterator(node <T>* p):_ptr(p){}



        friend bool operator !=(const Iterator &LHS, const Iterator &RHS){
            return !(LHS == RHS);
        }

        friend bool operator ==(const Iterator &LHS, const Iterator &RHS){
            return LHS._ptr == RHS._ptr;
        }

        Iterator& operator ++(){        //++it
            assert(_ptr);
            _ptr = _ptr->_next;
            return _ptr;
        }

        friend Iterator operator ++(Iterator &it, int unused){  //it++
            assert(it._ptr && "the iterator can't do ++ because it is nullptr\n");
            Iterator temp(it._ptr);
            it._ptr = it._ptr->_next;
            return temp;
        }

        bool is_null(){
            return _ptr == nullptr;
        }

        T operator *()                        //dereference operator
        {
            assert(_ptr);
            return _ptr->_item;
        }

        T* operator ->()                       //member access operator
        {
            assert(_ptr);
            return &(_ptr->_item);
        }

        const T& operator *() const                        //dereference operator
        {
            assert(_ptr);
            return _ptr->_item;
        }

        const T* operator ->() const                      //member access operator
        {
            assert(_ptr);
            return &(_ptr->_item);
        }

        friend ostream& operator <<(ostream& outs, Iterator &it){
            outs << *it._ptr;
            return outs;
        }

    private:
        node<T>* _ptr;
    };

    Queue();

    Queue(const Queue<T> &copy);
    ~Queue();
    Queue<T>& operator =(const Queue<T> &rhs);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;
    Iterator end() const;

    void print_pointers();
    int size()const{return _size;}


    template <typename U>
    friend ostream& operator <<(ostream &outs, const Queue<U> &print);

private:
    node<T>* _front;
    node<T>* _rear;
    int _size;


    T at(node<T>* iMarker);

    node<T>* insert_head_private(T i);           //inset i at the head of list

    node<T>* insert_after(T i,           //insert i after iMarker
                                node<T>* iMarker);

    node<T>* insert_before(T i,          //insert i before iMarker
                                node<T>* iMarker);

    node<T>* insert_sorted_private(T i);         //insert i. Assume sorted list



    T Delete(node<T>* iMarker);         //delete node pointed to by iMarker


    node<T>* search_private(const T &key);      //return pointer to node containing
                                                        //  key. NULL if not there

    node<T>* prev(node<T>* iMarker);    //get the previous node to iMarker  
};



template <typename T>
Queue<T>::Queue():_front(nullptr), _rear(nullptr), _size(0){

}

template <typename T>
Queue<T>::Queue(const Queue<T> &copy):_size(copy._size), _front(nullptr){
    _rear = _copy_list(_front, copy._front);
}

template <typename T>
Queue<T>::~Queue(){
    _clear_list(_front);
}

template <typename T>
Queue<T>& Queue<T>::operator =(const Queue<T> &rhs){
    if(this == &rhs){
        return *this;
    }
    _clear_list(_front);
    _front = nullptr;
    _rear = _copy_list(_front, rhs._front);
    _size = rhs._size;

    return *this;
}


template <typename T>
bool Queue<T>::empty(){
    return _size == 0;
}

template <typename T>
T Queue<T>::front(){
    return at(_front);
}

template <typename T>
T Queue<T>::back(){
    return at(_rear);
}

template <typename T>
void Queue<T>::push(T item){
    if(_front == nullptr){
        insert_head_private(item);
        _rear = _front;
    }
    else{
        _rear = insert_after(item, _rear);
    }
}

template <typename T>
T Queue<T>::pop(){

    return Delete(_front);
}


template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{

    return Queue<T>::Iterator(_front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const{

    return Queue<T>::Iterator(nullptr);
}

template <typename T>
void Queue<T>::print_pointers(){
    _print_list(_front);
}


template <typename U>
ostream& operator <<(ostream &outs, const Queue<U> &print){
    return _print_list(print._front, outs);
}







template <typename T>
T Queue<T>::at(node<T>* iMarker){
    return iMarker->_item;
}

//*********************************************************************************
//                              legacy
//*********************************************************************************




//inserting
template <typename T>
node<T>* Queue<T>::insert_head_private(T i)
{
    _front = _insert_head(_front, i);
    _size++;
    return _front;
}           //inset i at the head of Queue


template <typename T>
node<T>* Queue<T>::insert_after(T i,           //insert i after iMarker
                      node<T>* iMarker)
{
    _front = _insert_after(_front, iMarker, i);
    _size++;
    return iMarker->_next;

}

template <typename T>
node<T>* Queue<T>::insert_before(T i,          //insert i before iMarker
                              node<T>* iMarker)
{
    _front = _insert_before(_front, iMarker, i);
    _size++;
    return _front;

}

template <typename T>
node<T>* Queue<T>::insert_sorted_private(T i)
{
    
    _front = _insert_sorted(_front, i);
    _size++;
    return _front;

}         //insert i. Assume sorted Queue

template <typename T>
T Queue<T>::Delete(node<T>* iMarker)
{
    T deleted = _delete_node(_front, iMarker);
    _size--;
    return deleted;
}         //delete node pointed to by iMarker


template <typename T>
node<T>* Queue<T>::search_private(const T &key)
{
    node<T> *searched = _search_Queue(_front, key);
    return searched;

}      //return pointer to node containing
                                                //  key. NULL if not there

template <typename T>
node<T>* Queue<T>::prev(node<T>* iMarker)
{
    node<T> *pre = _previous_node(_front, iMarker);
    return pre;

}    //get the previous node to iMarker

#endif