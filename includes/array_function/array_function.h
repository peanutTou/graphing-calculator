#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H
#include <iostream>
#include <string>
using namespace std;


const int MINIMUM_CAPACITY = 3;

template<typename T>
T* allocate(int capacity= MINIMUM_CAPACITY);            //allocate 'capacity' 
                                                        //      elements. 
                                                        //  return array

template<typename T>
T* reallocate(T* a, int size, int capacity);            //take array, resize it 
                                                        //  return new array. 
                                                        //  delete old array

template<typename T>
void print_array(T* a, int size, 
            int capacity = 0, ostream& outs = cout);    //prints 
                                                        //  (size/capacity)
                                                        //  for debugging

template <typename T>
void print(T* a, unsigned int how_many, 
                                ostream& outs = cout);  //print array

template<typename T>
T* search_entry(T* a, int size, const T& find_me);      //search for 'find me'

template <typename T>
int search(T* a, int size, const T& find_me);           //search for 'find_me' 

template <typename T>
void shift_left(T* a, int& size, int shift_here);       //shift left @ pos:
                                                        //    erases @ pos
template <typename T>
void shift_left(T* a, int& size, T* shift_here);        //shift left @ pos: 
                                                        //    erases @ pos

template <typename T>
void shift_right(T *a, int &size, int shift_here);      //shift right: 
                                                        //      make a hole

template <typename T>
void shift_right(T *a, int &size, T* shift_here);       //shift right: 
                                                        //   make a hole

template<typename T>
void copy_array(T *dest, const T* src, 
                                int many_to_copy);      //copy from src to dest

template <typename T>
T* copy_array(const T *src, int size);                  //return a 
                                                        //  copy of src

template <typename T>
string array_string(const T *a, int size);              //return array 
                                                        //  as a string

template <typename T>
string getString(T val);                                //get val in string

string getString(char c);                               //overload getString by char

string getString(string str);                           //overload for string


//appned an element at the end
template<typename T>
void appened(T *arr, int &size, T appened_me);

//initizalied array with a specific value
template<typename T>
void array_init(T *arr, int size, T value);

/***************************************************************
 *                                                             *
 *                  Make a cut here                            *
 *                                                             *
 ***************************************************************/

//return an array with T type
template<typename T>
T* allocate(int capacity)
{
    bool debug = false;
    if(debug)
    {
        cout << "allocate(" << capacity << ");" << endl;
    }

    return new T[capacity];
}

//resize the capacity of the old array and return the new array
//delete the old array
template<typename T>
T* reallocate(T* a, int size, int capacity)
{
    bool debug = false;
    if(debug)
    {
        cout << "reallocate(" << array_string(a, size) << ", " << size << ", " << capacity << ");" << endl;
    }

    T *newArr = allocate<T>(capacity);
    
    copy_array(newArr, a, size);

    delete[] a;
    a = nullptr;
    return newArr;
}

//print array with capacity and size
template<typename T>
void print_array(T* a, int size, int capacity, ostream& outs)
{
    bool debug = false;
    if(debug)
    {
        cout << "print_array(" << array_string(a, size) << ", " << size << ", " << capacity << ");" << endl;
    }

    cout << "\n(" << size << " / " << capacity << ") ";
    print(a, size, outs);
}

//print array
template <typename T>
void print(T* a, unsigned int how_many, ostream& outs)
{
    bool debug = false;
    if(debug)
    {
        cout << "print(" << array_string(a, how_many) << ", " << how_many << ");" << endl;
    }

    T *walker = a;

    //get array in string, and output it
    outs << array_string(a, how_many) << endl;
}

//search for element and return address
template<typename T>
T* search_entry(T* a, int size, const T& find_me)
{
    bool debug = false;
    if(debug)
    {
        cout << "search_entry(" << array_string(a, size) << ", " << size << ", " << find_me << ");" << endl;
    }

    T *walker = a;
    T *endPoint = a + size;

    while(walker != endPoint)
    {
        if(*walker == find_me)
        {
            return walker;
        }
        walker++;
    }
    return nullptr;
}

//search for element and return index
template <typename T>
int search(T* a, int size, const T& find_me)
{
    bool debug = false;
    if(debug)
    {
        cout << "search(" << array_string(a, size) << ", " << size << ", " << find_me << ");" << endl;
    }

    T *sol = search_entry(a, size, find_me);
    if(sol == nullptr)
    {
        return -1;
    }
    else
    {
        return sol - a;
    }
}

//shift every thing @pos to left, ersase the element from that position, size--
template <typename T>
void shift_left(T* a, int& size, int shift_here)
{
    bool debug = false;
    if(debug)
    {
        cout << "shift_left(" << array_string(a, size) << ", " << size << ", " << shift_here << ");" << endl;
    }

    T *walker = a + shift_here;
    for(int i = shift_here; i < size - 1; i++)
    {
        *walker = *(walker + 1);
        walker++;
    }
    size--;
}

//shift every thing @pos to left, ersase the element from that position, size--
template <typename T>
void shift_left(T* a, int& size, T* shift_here)
{
    bool debug = false;
    if(debug)
    {
        cout << "shift_left(" << array_string(a, size) << ", " << size << ");" << endl;
    }

    int shiftSize = shift_here - a;
    shift_left(a, size, shiftSize);
}

//shift every thing @pos to right, the element on that position stay same, size++
template <typename T>
void shift_right(T *a, int &size, int shift_here)
{
    bool debug = false;
    if(debug)
    {
        cout << "shift_right(" << array_string(a, size) << ", " << size << ", " << shift_here << ");" << endl;
    }
    T *walker = a + size;
    for(int i = size; i > shift_here; i--)
    {
        *walker = *(walker - 1);
        walker--;
    }
    size++;
}

//shift every thing @pos to right, the element on that position stay same, size++
template <typename T>
void shift_right(T *a, int &size, T* shift_here)
{
    bool debug = false;
    if(debug)
    {
        cout << "shift_right(" << array_string(a, size) << ", " << size << ");" << endl;
    }

    int shiftSize = shift_here - a;
    shift_right(a, size, shiftSize);
}

//make a copy from src to dest
template<typename T>
void copy_array(T *dest, const T* src, int many_to_copy)
{
    bool debug = false;
    if(debug)
    {
        cout << "copy_array(" << array_string(dest, many_to_copy) << ", " << src << ", " << many_to_copy << ");" << endl;
    }

    const T *searcher = src;
    T *walker = dest;
    for(int i = 0; i < many_to_copy; i++)
    {
        *walker = *searcher;
        searcher++;
        walker++;
    }
}

//make a copy of the array, return the address of that array
template <typename T>
T* copy_array(const T *src, int size)
{
    bool debug = false;
    if(debug)
    {
        cout << "copy_array(" << array_string(src, size) << ", " << size << ");" << endl;
    }

    T *copied = new T[size];
    copy_array(copied, src, size);
    return copied;
}

//translate array to string
template <typename T>
string array_string(const T *a, int size)
{
    bool debug = false;
    if(debug)
    {
        cout << "array_string(" << size << ");" << endl;
    }

    string msg = "[";
    const T *walker = a;

    for(int i = 0; i < size; i++)
    {
        msg += getString(*walker);
        if(i < size - 1)
        {
            msg += ", ";
        }
        walker++;
    }
    msg += "]";
    return msg;
}

//convery value to string
template<typename T>
string getString(T val)
{
    bool debug = false;
    if(debug)
    {
        cout << "getString(" << val << ");" << endl;
    }
    return to_string(val);
}
//overload for char
inline string getString(char c)
{
    bool debug = false;
    if(debug)
    {
        cout << "getString(" << c << ");" << endl;
    }
    string str(1, c);
    return str;
}

inline string getString(string str)
{
    return str;
}


//appned an element at the end
template<typename T>
void appened(T *arr, int &size, T appened_me)
{
    bool debug = false;
    if(debug)
    {
        cout << "appened(" << array_string(arr, size) <<", " << size << ", " <<appened_me << ");" << endl;
    }
    T *walker = arr + size;
    *walker = appened_me;
    size++;
}

//initizalied array with a specific value
template<typename T>
void array_init(T *arr, int size, T value)
{
    T *walker = arr + size;
    for(; walker != arr; walker--)
    {
        *(walker - 1) = value;
    }
}

#endif