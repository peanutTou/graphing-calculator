#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H
#include <iostream>
#include "../array_function/array_function.h"
using namespace std;


 //appened new_entry to the end of list
template<class T>
T* add_entry(T* list, const T& new_entry,
                  int& size, int& capacity);

//remove the first entry in the list
template<class T>
T* remove_entry(T* list, const T& delete_me,
                     int& size, int& capacity);

//pop last element, save to the argument popped
template <class T>
T *remove_last_entry(T *list, T &popped,
                     int &size, int &capacity);

//inset the entry at the target position, move everyting to the right
template <class T>
T *insert_entry(T *list, const T &insert_this,
                int insert_here,
                int &size,
                int &capacity);

//erease the element at the position
//move every left to fix the hold
template <class T>
T *erase_entry(T *list, int index,
               int &size, int &capacity);

//if the capacity was less than MINIMUM_CAPACITY, set it equal to MINIMUM_CAPACITY
//if the capacity was not enough, double it
template <typename T>
T *extentCapacity(T *list, int &size, int &capaity);

//if the capacity have too much empty memory space, only 1/4 has used, shink it by half
//the capacity can't less than MINIMUM_CAPACITY
template <typename T>
T *shinkCapacity(T *list, int &size, int &capaity);

/***************************************
 * 
 *          implement cut
 * 
 **************************************/

 //appened new_entry to the end of list
 template<class T>
 T* add_entry(T* list, const T& new_entry, int& size, int& capacity)
{
    bool debug = false;
    if(debug)
    {
        cout << "add_entry: (" << array_string(list, size) << ", " << new_entry << ", " << size;
        cout << ", " << capacity << ");\n";
    }

    T* return_entry = list;
    //extent when capacity was full
    if(size >= capacity){
        return_entry = extentCapacity(list, size, capacity);
    }

    appened(return_entry, size, new_entry);


    return return_entry;
}

//remove the first entry in the list
 template<class T>
 T* remove_entry(T* list, const T& delete_me, int& size, int& capacity)
{
    bool debug = false;
    if(debug)
    {
        cout << "remove_entry: (" << array_string(list, size) << ", " << delete_me << ", " << size;
        cout << ", " << capacity << ");\n";
    }

    T* return_entry = list;
    int pos = search(list, size, delete_me);

    if(pos >= 0)
    {
        shift_left(list, size, pos);
    }

    //check for shink condition
    if(size <= capacity / 4 && size >= MINIMUM_CAPACITY)
    {
        return_entry = shinkCapacity(list, size, capacity);
    }

    return return_entry;

}
 //pop last element, save to the argument popped
 template <class T>
 T *remove_last_entry(T *list, T &popped, int &size, int &capacity)
{
    bool debug = false;
    if(debug)
    {
        cout << "remove_last_entry: (" << array_string(list, size) << ", " << size;
        cout << ", " << capacity << ");\n";
    }

    T* return_entry = list;
    T* poppedWalker = list + size - 1;
    
    popped = *(poppedWalker);
    shift_left(list, size, size - 1);

    //check for shink condition
    if(size <= capacity / 4 && size >= MINIMUM_CAPACITY)
    {
        return_entry = shinkCapacity(list, size, capacity);
    }
    return return_entry;
}
 
//inset the entry at the target position, move everyting to the right
 template <class T>
 T *insert_entry(T *list, const T &insert_this, int insert_here, int &size, int &capacity)
{
    bool debug = true;
    if(debug)
    {
        cout << "insert_entry: (" << array_string(list, size) << ", " << insert_this << ", " << insert_here << ", " << size;
        cout << ", " << capacity << ");\n";
    }

    T* return_entry = list;
    //extent when capacity was full
    if(size >= capacity){
        return_entry = extentCapacity(list, size, capacity);
    }

    shift_right(return_entry, size, insert_here);
    T *insertWalker = return_entry + insert_here;
    *insertWalker = insert_this;


    return return_entry;
}

//erease the element at the position
//move every left to fix the hold
 template <class T>
 T *erase_entry(T *list, int index, int &size, int &capacity)
{
    bool debug = false;
    if(debug)
    {
        cout << "earse_entry: (" << array_string(list, size) << ", " << index << ", " << size;
        cout << ", " << capacity << ");\n";
    }

    T* return_entry = list;
    if(index >= 0)
    {
        shift_left(list, size, index);

        //check for shink condition
        if(size <= capacity / 4 && size >= MINIMUM_CAPACITY)
        {
            return_entry = shinkCapacity(list, size, capacity);
        }
    }

    return return_entry;
}


//if the capacity was less than MINIMUM_CAPACITY, set it equal to MINIMUM_CAPACITY
//if the capacity was not enough, double it
template <typename T>
T *extentCapacity(T *list, int &size, int &capacity)
{
    bool debug = false;
    T *return_entry = list;
    //output when reallocate memory
    if(debug)
    {
        cout << "\nExtent Capacity: ";
        cout << "Reallocate happened: array memory was too small: (" << size << " / " << capacity << ")\n";
    }

    if(capacity < MINIMUM_CAPACITY){
        capacity = MINIMUM_CAPACITY;
    }else{
        capacity *= 2;
    }

    return_entry = reallocate(list, size, capacity);

    if(debug)
        cout << "Reallocate successly: now array size / capacity: (" << size << " / " << capacity << ")\n";

    return return_entry;
}

//if the capacity have too much empty memory space, only 1/4 has used, shink it by half
//the capacity can't less than MINIMUM_CAPACITY
template <typename T>
T *shinkCapacity(T *list, int &size, int &capacity)
{
    bool debug = false;
    T *return_entry = list;
    //output when reallocate memory
    if(debug)
    {
        cout << "\nShink Capacity: ";
        cout << "Reallocate happened: array memory was too large: (" << size << " / " << capacity << ")\n";
    }
    capacity = size * 2;
    capacity = (capacity < MINIMUM_CAPACITY)? MINIMUM_CAPACITY : capacity;
    return_entry = reallocate(list, size, capacity);

    if(debug)
        cout << "Reallocate successly: now array size / capacity: (" << size << " / " << capacity << ")\n";

    return return_entry;

}


#endif