#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include <iostream>
#include <iomanip>
#include <string>
#include <assert.h>
#include "../node/node.h"

using namespace std;


//Linked List General Functions:
template <typename ITEM_TYPE>
ostream& _print_list(node<ITEM_TYPE>* head, ostream &outs = cout);

//recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head);

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                            ITEM_TYPE key);


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                            ITEM_TYPE insert_this);

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                             node<ITEM_TYPE> *after_this,
                             ITEM_TYPE insert_this);

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                              node<ITEM_TYPE>* before_this,
                              ITEM_TYPE insert_this);

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                              node<ITEM_TYPE>* prev_to_this);

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                     node<ITEM_TYPE>* delete_this);

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head);

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src);


//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head);

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>*& head, int pos);

//find the node at the position
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_position(node<ITEM_TYPE>* head, int pos);

//delete the head value
template <typename T>
node<T>* _delete_head(node<T>*& head);

//return the length of the list
template <typename T>
int _list_length(node<T>* head);
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                              ITEM_TYPE item,
                              bool ascending=true);

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                      ITEM_TYPE item,
                                      bool ascending=true);
//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                               ITEM_TYPE item,
                               bool ascending=true);
//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head); 

template <typename ITEM_TYPE>
bool _compare_list(const node<ITEM_TYPE>*& left, const node<ITEM_TYPE>*& right);
/*************************************************
 *                                               *
 *                  BIG CUT                      *
 *                                               *
 *************************************************/


//defintion of functions

//******************* insert functions *******************

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this){
    node<ITEM_TYPE> *temp = new node<ITEM_TYPE>(insert_this);
    temp->_next = head;
    head = temp;

    return head;
}


//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                             node<ITEM_TYPE> *after_this,
                             ITEM_TYPE insert_this)
{
    node<ITEM_TYPE> *temp = new node<ITEM_TYPE>(insert_this);
    temp->_next = after_this->_next;
    after_this->_next = temp;

    return head;
}


//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                              node<ITEM_TYPE>* before_this,
                              ITEM_TYPE insert_this)
{
    node<ITEM_TYPE> *temp = _previous_node(head, before_this);
    if(temp == nullptr){
        head = _insert_head(head, insert_this);
    }else{
        head = _insert_after(head, temp, insert_this);
    }

    return head;
}

//******************* delete functions *******************

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                     node<ITEM_TYPE>* delete_this)
{
    ITEM_TYPE item = delete_this->_item;
    node<ITEM_TYPE> *temp = _previous_node(head, delete_this);
    if(temp == nullptr){
        head = _delete_head(head);
    }else{
        temp->_next = delete_this->_next;
        delete delete_this;
    }

    return item;
}

//delete the head value
template <typename T>
node<T>* _delete_head(node<T>*& head){
    if(head == nullptr){
        return nullptr;
    }

    node<T>* the_next = head->_next;

    delete head;
    head = the_next;
    return head;
}


//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head){
    node<ITEM_TYPE>* walker = head;
    node<ITEM_TYPE>* follows;
    while(walker != nullptr){
        follows = walker;
        walker = walker->_next;
        delete follows;
    }

    head = nullptr;
}
//******************* print functions *******************

//print the list
template <typename ITEM_TYPE>
ostream& _print_list(node<ITEM_TYPE>* head, ostream &outs){
    node<ITEM_TYPE> *walker = head;
    while(walker != nullptr){
        outs << *walker;
        walker = walker->_next;
    }
    outs << "nullptr" << endl;
    return outs;
}

template <typename T>
void _print_list_backwards(node<T> *head){
    node<T> *contains = new node<T>();
    node<T> *walker = head;

    while(walker != nullptr){
        //if it is the first time enter the list, replace node's value from default to _item
        if(walker == head){
            contains->_item = walker->_item;
        }else{
            _insert_head(contains, walker->_item);
        }
        
        walker = walker->_next;
    }

    _print_list(contains);

    _clear_list(contains);
    contains = nullptr;

}


//******************* searchers *******************

//search in linked list, return the value by reference of the position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>*& head, int pos){
    node<ITEM_TYPE>* walker = head;
    while(walker != nullptr){
        if(pos == 0){
            return walker->_item;
        }
        pos--;
        walker = walker->_next;
    }
    //if position not avaliable
    assert(false && "list doesn't long enough, position was too large");
    return head->_item;
}

//search in linked list, return the pointer of the first key appears
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                            ITEM_TYPE key){
    node<ITEM_TYPE>* walker = head;
    while(walker != nullptr){
        if(walker->_item == key){
            return walker;
        }
        walker = walker->_next;
    }
    //if position not avaliable
    return nullptr;
}



//search in linked list, return the pointer of the position
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_position(node<ITEM_TYPE>* head, int pos){
    
    node<ITEM_TYPE>* walker = head;
    while(walker != nullptr){
        if(pos <= 0){
            return walker;
        }
        pos--;
        walker = walker->_next;
    }
    //if position not avaliable
    return nullptr;
}


//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this)
{
    //prev_to_this was the head
    if(head == prev_to_this){
        return nullptr;
    }

    //find the previous node
    node<ITEM_TYPE> *walker = head;
    while(walker->_next != nullptr){
        if((walker->_next) == prev_to_this){
            return walker;
        }
        walker = walker->_next;
    }

    //if prev_to_this is a nullptr, return the last node
    if(prev_to_this == nullptr){
        return walker;
    }
    
    //node doesn't exist
    assert(false && "node doesn't exist");

    return nullptr;
}



//****************** copys *******************

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head){
    node<ITEM_TYPE>* dest;
    dest = nullptr;
    _copy_list(dest, head);

    return dest;
}

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src){
    node<T> *walker = src;
    node<T> *lastOne;
    while(walker != nullptr){
        if(dest == nullptr){
            _insert_head(dest, walker->_item);
            lastOne = dest;
        }else{
            _insert_after(dest, lastOne, walker->_item);
            lastOne = lastOne->_next;
        }
        walker = walker->_next;
    }

    return lastOne;
}

//****************** used *******************

template <typename T>
int _list_length(node<T>* head){
    int i = 0;
    node<T> *walker = head;
    while(walker != nullptr){
        walker = walker->_next;
        i++;
    }
    return i;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                              ITEM_TYPE item,
                              bool ascending)
{
    _where_this_goes(head, item, ascending);
    return head;
}

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                      ITEM_TYPE item,
                                      bool ascending)
{
    return head;
}
//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                               ITEM_TYPE item,
                               bool ascending)
{
    //if head is nullptr, insert head
    if(head == nullptr){
        _insert_head(head, item);
        return head;
    }

    node<ITEM_TYPE>* walker = head;
    //for the case if item should go before head
    if(!ascending){
        if(walker->_item > item){
            _insert_head(head, item);
            return walker->_next;
        }
    }else{
        if(walker->_item < item){
            _insert_head(head, item);
            return walker->_next;
        }
    }
    //insert item if it can goes into body
    while(walker->_next != nullptr){
        if(!ascending){
            if((walker->_next->_item > item)){
                _insert_after(head, walker, item);
                return walker->_next;
            }
        }
        else{
            if((walker->_next->_item < item)){
                _insert_after(head, walker, item);
                return walker->_next;
            }
        }
        walker = walker->_next;
    }

    //add to the end
    _insert_after(head, walker, item);
    return walker->_next;
}

//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head){
    return nullptr;
}




template <typename ITEM_TYPE>
bool _compare_list(const node<ITEM_TYPE>*& left, const node<ITEM_TYPE>*& right){
    node<ITEM_TYPE>* leftPtr = left;
    node<ITEM_TYPE>* rightPtr = right;

    while(leftPtr != nullptr && rightPtr != nullptr)
    {
        if(leftPtr->_item != rightPtr->_item){
            return false;
        }
        leftPtr = leftPtr->_next;
        rightPtr = rightPtr->_next;
    }

    return true;
}
#endif
