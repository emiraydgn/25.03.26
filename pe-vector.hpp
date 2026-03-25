#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP

#include <cstddef>

namespace knk

{
  template<class T>
  
  struct Vector {
    Vector();
     ~Vector();
    Vector(size_t size, const T & value);
    Vector(const Vector<T> & rhs) = delete;

    Vector<T> & operator=(const Vector<T> & rhs) = delete;
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    size_t getCapacity() const noexcept; // написать тест и реализовать (ДЗ)
    void pushBack(const T &); // 
    void popBack(); // 

    private:
      explicit Vector(size_t size);
      T * data;
      size_t size_, capacity;
  };
}

template<class T>
bool knk::Vector<T>::isEmpty() const noexcept
{
  return !size_;
}

template<class T>
size_t knk::Vector<T>::getSize() const noexcept
{
  return size_;
}

template<class T>
knk::Vector<T>::Vector(size_t size, const T & value):
  Vector(size)
{
  for (size_t i = 0; i < size; i++)
  {
    data[i] = value;
  }
}
template<class T>
knk::Vector<T>::Vector():
  data(nullptr),
  size_(0),
  capacity(0)
{}
template <class T>
knk::Vector<T>::~Vector()
{
  delete [] data;
}

template<class T>
  knk::Vector<T>::Vector(size_t size):
  data(size ? new T[size] : nullptr),
  size_(size),
  capacity(size)
{}
#endif
