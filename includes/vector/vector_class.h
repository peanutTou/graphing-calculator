#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H
#include <iostream>
#include <iomanip>
#include <string>
#include "../array_function/array_function.h"
#include "../add_entry/add_entry.h"
using namespace std;

template <class T>
class Vector{
public:

    Vector(int capacity = 100);
    Vector(T *arr, int size);
    
    // big three:

    Vector& operator =(const Vector &right);
    Vector(const Vector &get);
    ~Vector();

    //member access functions:
    T& operator [](int index);
    const T& operator [](int index) const;

    T& at(int index);              //return reference to item at position index
    const T& at(int index) const;  //return a const item at position index

    T& front();                         //return item at position 0.
    T& back();                          //return item at the last position


    //Push and Pop functions:
    Vector& operator +=(const T& item); //push_back
    void push_back(const T& item);      //append to the end
    T pop_back();                       //remove last item and return it


    //Insert and Erase:
    void insert(int insert_here, const T& insert_this); //insert at pos
    void erase(int erase_this_index);        //erase item at position
    int index_of(const T& item);             //search for item. return index.

    //size and capacity:
    void set_size(int size);              //enlarge the vector to this size
    void set_capacity(int capacity);      //allocate this space
    int size() const {return _how_many;}  //return _size
    int capacity() const {return _capacity;} //return _capacity

    bool empty() const;                    //return true if vector is empty

    //OUTPUT:
    template <class U>
    friend ostream& operator <<(ostream& outs, const Vector<U>& _a);

private:
    T *_list;
    int _how_many;
    int _capacity;

};

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
///////////////////                                                /////////////////////
///////////////////                Make a big Cut                  /////////////////////
///////////////////                                                /////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

//construtures
template <class T>
Vector<T>::Vector(int capacity):_capacity(capacity), _how_many(0){
    _list = allocate<T>(_capacity);
}

template <typename T>
Vector<T>::Vector(T *arr, int size):_how_many(size), _capacity(size * 2){
    _list = allocate<T>(_capacity);
    copy_array(_list, arr, size);
}


template <typename T>
T& Vector<T>::operator [](int index){
    return at(index);
}

template <typename T>
const T& Vector<T>::operator [](int index) const{
    return at(index);
}

template <typename T>
T& Vector<T>::at(int index){
    T *ref= _list + index;
    return *ref;
}

template <typename T>
const T& Vector<T>::at(int index) const{
    T *ref= _list + index;
    return *ref;
}

template <typename T>
T& Vector<T>::front(){
    return at(0);
}

template <typename T>
T& Vector<T>::back(){
    return at(_how_many - 1);
}

template <typename T>
Vector<T>& Vector<T>::operator +=(const T& item){
    _list = add_entry(_list, item, _how_many, _capacity);
    return *this;
}

template <typename T>
void Vector<T>::push_back(const T& item){
    _list = add_entry(_list, item, _how_many, _capacity);
}

template <typename T>
T Vector<T>::pop_back(){
    T popped;
    _list = remove_last_entry(_list, popped, _how_many, _capacity);

    return popped;
}

template <typename T>
void Vector<T>::insert(int insert_here, const T& insert_this){

    _list = insert_entry(_list, insert_this, insert_here, _how_many, _capacity);
}

template <typename T>
void Vector<T>::erase(int erase_this_index){
    _list = erase_entry(_list, erase_this_index, _how_many, _capacity);
}

template <typename T>
int Vector<T>::index_of(const T& item){
    int index = search(_list, _how_many, item);
    return index;
}

template <typename T>
void Vector<T>::set_size(int size){
    _how_many = size;
}

template <typename T>
void Vector<T>::set_capacity(int capacity){
    _capacity = capacity;
}

template <typename T>
bool Vector<T>::empty() const{
    if(_how_many == 0)
        return true;
    else
        return false;
}

template <typename U>
ostream& operator << (ostream& outs, const Vector<U>& _a){
    
    outs << array_string(_a._list, _a._how_many);
    return outs;
}


//Big three
template <typename T>
Vector<T>& Vector<T>::operator =(const Vector &right){
    if(this == &right){
        return *this;
    }
    delete[] _list;
    _how_many = right._how_many;
    _capacity = right._capacity;
    _list = allocate<T>(_capacity);
    copy_array(_list, right._list, right._how_many);


    return *this;
}

template <typename T>
Vector<T>::Vector(const Vector &get){
    _how_many = get._how_many;
    _capacity = get._capacity;
    _list = allocate<T>(_capacity);
    copy_array(_list, get._list, get._how_many);

}


template <typename T>
Vector<T>::~Vector(){
    delete[] _list;
    _list = nullptr;
}

#endif