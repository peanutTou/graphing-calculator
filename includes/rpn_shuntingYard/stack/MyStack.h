#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include <iomanip>
#include <string>
#include "../linked/linked.h"
#include "assert.h"

using namespace std;

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator():_ptr(nullptr){}                //default ctor
        Iterator(node<T>* p){                    //Point Iterator to where
            _ptr =p;                             //  p is pointing to
        }
        
        bool is_null(){
            return _ptr == nullptr;
        }

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
        node<T>* _ptr;                          //pointer being encapsulated               
        
    };

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template<typename U>
    friend ostream& operator<<(ostream& outs, 
                                const Stack<U>& printMe);

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;





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
Stack<T>::Stack():_top(nullptr), _size(0){

}

template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe): _size(copyMe._size){
    _top = _copy_list(copyMe._top);
}

template <typename T>
Stack<T>::~Stack(){
    _clear_list(_top);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS){
    if(this == &RHS){
        return *this;
    }

    _clear_list(_top);
    _copy_list(_top, RHS._top);
    _size = RHS._size;

    return *this;
}

template <typename T>
T Stack<T>::top(){
    return _top->_item;
}

template <typename T>
bool Stack<T>::empty(){
    return _size == 0;
}

template <typename T>
void Stack<T>::push(T item){
    insert_head_private(item);
}

template <typename T>
T Stack<T>::pop(){
    return Delete(_top);
}

template<typename U>
ostream& operator<<(ostream& outs, 
                    const Stack<U>& printMe)
{
    return _print_list(printMe._top, outs);
}

                                    
template <typename T>           //Iterator to the head node
typename Stack<T>::Iterator Stack<T>::begin() const{
    return Stack<T>::Iterator(_top);
}   

template <typename T>                //Iterator to NULL
typename Stack<T>::Iterator Stack<T>::end() const{
    return Stack<T>::Iterator(nullptr);
}




//*********************************************************************************
//                              legacy
//*********************************************************************************




//inserting
template <typename T>
node<T>* Stack<T>::insert_head_private(T i)
{
    _top = _insert_head(_top, i);
    _size++;
    return _top;
}           //inset i at the head of Stack

template <typename T>
node<T>* Stack<T>::insert_after(T i,           //insert i after iMarker
                      node<T>* iMarker)
{
    _top = _insert_after(_top, iMarker, i);
    _size++;
    return _top;

}

template <typename T>
node<T>* Stack<T>::insert_before(T i,          //insert i before iMarker
                              node<T>* iMarker)
{
    _top = _insert_before(_top, iMarker, i);
    _size++;
    return _top;

}

template <typename T>
node<T>* Stack<T>::insert_sorted_private(T i)
{
    
    _top = _insert_sorted(_top, i);
    _size++;
    return _top;

}         //insert i. Assume sorted Stack

template <typename T>
T Stack<T>::Delete(node<T>* iMarker)
{
    T deleted = _delete_node(_top, iMarker);
    _size--;
    return deleted;
}         //delete node pointed to by iMarker


template <typename T>
node<T>* Stack<T>::search_private(const T &key)
{
    node<T> *searched = _search_Stack(_top, key);
    return searched;

}      //return pointer to node containing
                                                //  key. NULL if not there

template <typename T>
node<T>* Stack<T>::prev(node<T>* iMarker)
{
    node<T> *pre = _previous_node(_top, iMarker);
    return pre;

}    //get the previous node to iMarker


#endif