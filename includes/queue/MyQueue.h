#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <iomanip>

#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Queue
{
public:
  class Iterator
  {
  public:
    //Give access to list to access _ptr
    friend class Queue;

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
  Queue();

  //BIG 3:
  Queue(const Queue<T>& copyMe);
  ~Queue();
  Queue<T>& operator =(const Queue<T>& RHS);

  //Operations:
  void push(T item);                  //Enqueue
  void pop();                         //Dequeue

  //Accessors:
  Iterator begin() const;             //Iterator to the head node
  Iterator end() const;               //Iterator to NULL

  //Checkers:
  int size() const;
  bool empty();
  T front();
  T back();

  template<typename U>
  friend ostream& operator <<(ostream& outs, const Queue<U>& printMe);
  
private:
  node<T>* _front;
  node<T>* _rear;
  int _size;
};


//Definition

//TODO

//CTOR:
template<typename T>
Queue<T>::Queue()
{
  _front = nullptr;
  _rear = nullptr;
  _size = 0;
}

//Big 3:
template<typename T>
Queue<T>::Queue(const Queue<T>& copyMe)
{
  _size = copyMe._size;
  _front = _copy_list<T>(copyMe._front);
  _rear = _last_node<T>(copyMe._front);
}

template<typename T>
Queue<T>::~Queue()
{
  _clear_list<T>(_front);
  _rear = nullptr;
  _size = 0;
}

template<typename T>
Queue<T>& Queue<T>::operator =(const Queue<T>& RHS)
{
  if (this == &RHS)
  {
    return *this;
  }
  _clear_list<T>(_front);
  _size = RHS._size;
  _front = _copy_list<T>(RHS._front);
  _rear = _last_node<T>(RHS._front);
  return *this;
}

//Operations:
template <typename T>
void Queue<T>::push(T item)
{
  _size++;
  _insert_after<T>(_front, _rear, item);
  _rear = _last_node<T>(_front);
}

template <typename T>
void Queue<T>::pop()
{
  if (_size > 0)
  {
    _size--;
    _delete_node<T>(_front, _front);
  }
}

//Accessors:
template<typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
  Iterator res(_front);
  return res;
}

template<typename T>
typename Queue<T>::Iterator Queue<T>::end() const
{
  Iterator res(_rear->_next);
  return res;
}

//Checkers:
template<typename T>
int Queue<T>::size() const
{
  return _size;
}

template<typename T>
bool Queue<T>::empty()
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
T Queue<T>::front()
{
  if (!empty())
  {
    return _at<T>(_front, 0);
  }
  else
  {
    return T();
  }
}

template<typename T>
T Queue<T>::back()
{
  if(!empty())
  {
    return _at<T>(_front, _size - 1);
  }
  else
  {
    return T();
  }
}

template<typename U>
ostream& operator <<(ostream& outs, const Queue<U>& printMe)
{
  for (typename Queue<U>::Iterator temp = printMe.begin(); temp != printMe.end(); temp++)
  {
    outs << "[" << *temp << "]->";
  }
  outs << "|||" << endl;
  return outs;
}

#endif //MYQUEUE_H