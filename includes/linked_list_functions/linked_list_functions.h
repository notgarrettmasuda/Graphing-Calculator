#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <cassert>

#include "../node/node.h"

using namespace std;


// Declaration
//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T>* head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key);

template <typename T>
node<T>* _insert_head(node<T>* &head, T insert_this);

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>* &head, node<T>* after_this, T insert_this);

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>* &head, node<T>* before_this, T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>* &head, node<T>* delete_this);

//duplicate the list
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate list and return the last node of the copy
template <typename T>
node<T>* _copy_list(node<T>* &dest, node<T>* src);

//delete all the nodes
template <typename T>
void _clear_list(node<T>* &head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

//Last node in the list, never use this function.
template <typename T>
node<T>* _last_node(node<T>* head);

//Definition 

//TODO

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head)
{
    while(head != nullptr) 
    {
        cout << "["<< head->_item << "]->";
        head = head->_next;
    }
    cout << "|||" << endl;
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T>* head)
{
    if (head == nullptr)
    {
        return;
    }
    _print_list_backwards(head->_next);
    cout << "[" << head->_item << "] ";
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key)
{
    node<T>* temp = head;
    while (temp != nullptr) 
    {
        if (temp->_item == key)
        {
            return temp;
        }
        temp = temp->_next;
    }
    return head;
}

template <typename T>
node<T>* _insert_head(node<T>* &head, T insert_this)
{
    head = new node<T>(insert_this, head);
    return head;
}

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>* &head, node<T>* after_this, T insert_this)
{
    if (head == nullptr)
    {
        return _insert_head(head, insert_this);
    }
    if ((head->_next == nullptr && head == after_this) || after_this == _last_node<T>(head))
    {
        node<T>* tail = _last_node<T>(head);
        tail->_next = new node<T>(insert_this);
        return tail;
    }
    node<T>* res = new node<T>(insert_this, after_this->_next);
    after_this->_next = res;
    return res;
}

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>* &head, node<T>* before_this, T insert_this)
{
    if (head == nullptr || head == before_this)
    {
        head = _insert_head<T>(head, insert_this);
        return head;
    }

    node<T>* temp = head;
    node<T>* prev = _previous_node(temp, before_this);
    node<T>* res = new node<T>(insert_this, before_this);
    temp->_next = res;
    return res;
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prev_to_this)
{
    node<T>* temp = head;
    while (temp->_next != prev_to_this)
    {
        if(temp->_next != nullptr) 
        {
            temp = temp->_next;
        }
    }
    return temp;
}

//delete, return item
template <typename T>
T _delete_node(node<T>* &head, node<T>* delete_this)
{
    if(head == nullptr)
    {
        return T();
    }
    T deleted_item = delete_this->_item;
    if (head == delete_this)
    {
        node<T>* new_head = head->_next;
        head = new_head;
        delete delete_this;
        return deleted_item;
    }
    node<T>* temp = head;
    while (temp->_next != delete_this)
    {
        if(temp->_next != nullptr) 
        {
            temp = temp->_next;
        }
    }
    node<T>* res = temp->_next->_next;
    temp->_next = res;
    delete delete_this;
    return deleted_item;
}

//duplicate the list
template <typename T>
node<T>* _copy_list(node<T>* head)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    node<T>* copy = new node<T>();
    node<T>* temp = head;
    node<T>* copy_i = copy;
    copy->_item = temp->_item;
    copy->_next = nullptr;
    temp = temp->_next;
    while (temp != nullptr)
    {
        _insert_after(copy, copy_i, temp->_item);
        temp = temp->_next;
        copy_i = copy_i->_next;
    }
    return copy;
}

//duplicate list and return the last node of the copy
template <typename T>
node<T>* _copy_list(node<T>* &dest, node<T>* src)
{
    dest = _copy_list(src);
    while (src->_next != nullptr)
    {
        src = src->_next;
    }
    return src->_item;
}

//delete all the nodes
template <typename T>
void _clear_list(node<T>* &head)
{
    while (head != nullptr && head->_next != nullptr)
    {
        _delete_node(head, head->_next);
    }
    head = nullptr;
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos)
{
    node<T>* temp = head;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->_next;
    }
    return temp->_item;
}

//Last node in the list, never use this function.
template <typename T>
node<T>* _last_node(node<T>* head)
{
    node<T>* temp = head;
    while (temp->_next != nullptr)
    {
        temp = temp->_next;
    }
    return temp;
}

#endif // LINKED_LIST_FUNCTIONS_H