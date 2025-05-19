#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


template <typename ITEM_TYPE>
struct node
{
public:
    node(const ITEM_TYPE& item = ITEM_TYPE(), node* next = nullptr);

    template <typename T>
    friend std::ostream& operator <<(std::ostream& outs,
                                const node<T> &printMe);

    ITEM_TYPE _item;
    node* _next;
};




//for definition
template <typename ITEM_TYPE>
node<ITEM_TYPE>::node(const ITEM_TYPE& item, node* next){
    _item = item;
    _next = next;
}

template<typename T>
ostream& operator <<(ostream& outs, const node<T>& print_me){
    outs << "[" << print_me._item << "]->";
    return outs;
}





#endif