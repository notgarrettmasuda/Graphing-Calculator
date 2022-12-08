#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <iomanip>

#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Stack
{
public:
  class Iterator
  {
  public:
    //Give access to list to access _ptr
    friend class Stack;

    //Default CTOR
    Iterator()
    { 
      _ptr = nullptr;
    }
    //Point Iterator to where p is pointing to
    Iterator(node<T>* p)
    { 
      _ptr = p;
    }

    //Casting operator: true if _ptr not NULL
    //This turned out to be a pain!
    operator bool() 
    { 
      if (_ptr != nullptr)
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    //dereference operator
    T& operator *()
    { 
      assert(_ptr != nullptr);
      return _ptr->_item;
    }  
    //member access operator
    T* operator ->()
    { 
      return _ptr;
    }
    //true if _ptr is NULL
    bool is_null()
    { 
      if (_ptr == nullptr)
      {
        return true;
      }
      else
      {
        return false;
      }
    }   

    //true if left != right
    friend bool operator !=(const Iterator &left, const Iterator &right)
    { 
      return left._ptr != right._ptr;
    }
    //true if left == right
    friend bool operator ==(const Iterator &left, const Iterator &right)
    { 
      return left._ptr == right._ptr;
    }

    //member operator:  ++it; or ++it = new_value
    Iterator& operator ++()
    { 
      _ptr = _ptr->_next;
      return *this;
    }                 
    //friend operator: it++
    friend Iterator operator ++(Iterator &it, int unused)
    { 
      Iterator hold = it;
      it._ptr = it._ptr->_next;
      return hold;
    }
    
  private:
    node<T>* _ptr; //pointer being encapsulated
  };

  //constructor: CTOR
  Stack();

  //BIG 3:
  Stack(const Stack<T>& copyMe);
  ~Stack();
  Stack<T>& operator =(const Stack<T>& RHS);

  //Operations:
  void push(T item);
  void pop();

  //Accessors:
  Iterator begin() const;            //Iterator to the head node
  Iterator end() const;              //Iterator to NULL

  //Checkers:
  int size() const;
  bool empty();
  T top();

  template<typename U>
  friend ostream& operator <<(ostream& outs, const Stack<U>& printMe);

private:
  node<T>* _top;
  int _size;
};

//Definition

//TODO

template <typename T>
Stack<T>::Stack()
{
    _size = 0;
    _top = nullptr;
}

//Big 3:
template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe)
{
    _size = copyMe._size;
    _top = _copy_list<T>(copyMe._top);
}

template <typename T>
Stack<T>::~Stack()
{
    _clear_list<T>(_top);
}

template <typename T>
Stack<T>& Stack<T>::operator =(const Stack<T>& RHS)
{
    if(this == &RHS)
    {
      return *this;
    }
    _clear_list<T>(_top);
    _size = RHS._size;
    _top = _copy_list<T>(RHS._top);
    return *this;
}

//Operations:
template <typename T>
void Stack<T>::push(T item)
{
    _size++;
    _insert_head<T>(_top, item);
}

template<typename T>
void Stack<T>::pop()
{
    if (_size > 0)
    {
        _size--;
        _delete_node<T>(_top, _top);
    }
}

//Accessors:
template<typename T>
typename Stack<T>::Iterator Stack<T>::begin() const
{
    Iterator res(_top);
    return res;
}

template<typename T>
typename Stack<T>::Iterator Stack<T>::end() const
{
    return Iterator(nullptr);
}

//Checkers:
template<typename T>
int Stack<T>::size() const
{
    return _size;
}

template<typename T>
bool Stack<T>::empty() 
{
    if (_size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
T Stack<T>::top()
{
    return _at<T>(_top, 0);
}

template<typename U>
ostream& operator <<(ostream& outs, const Stack<U>& printMe)
{
    
    for (typename Stack<U>::Iterator temp = printMe.begin(); temp != printMe.end(); temp++)
    {
        outs << "[" << *temp << "]->";
    }
    outs << "|||" << endl;
    return outs;
}


#endif // MYSTACK_H