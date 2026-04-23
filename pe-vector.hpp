#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <memory>

namespace knk
{
  template< class T >
  class Vector
  {
  public:
    ~Vector();
    Vector();
    Vector(size_t size, const T& value);
    explicit Vector(std::initializer_list< T > il);

    Vector(const Vector< T >& rhs);
    Vector(Vector< T >&& rhs) noexcept;
    Vector< T >& operator=(const Vector< T >& rhs);
    Vector< T >& operator=(Vector< T >&& rhs) noexcept;
    void swap(Vector< T >& rhs) noexcept;

    void insert(size_t id, const T& t);
    void insert(size_t id, const Vector< T >& rhs, size_t begin, size_t end);
    void erase(size_t id);
    void erase(size_t begin, size_t end);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& t);
    void pushBackRepeat(const T& t, size_t k);
    void popBack();
    void pushFront(const T& t);

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

  private:
    T* data_;
    size_t size_, capacity_;

    explicit Vector(size_t size);
  };

  template< class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);

  template< class T >
  bool operator!=(const Vector< T >& lhs, const Vector< T >& rhs);
}

template< class T >
knk::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
knk::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
knk::Vector< T >::Vector(size_t size, const T& value):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = value;
  }
}

template< class T >
knk::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  size_t i = 0;
  for (const T& value: il)
  {
    data_[i++] = value;
  }
}

template< class T >
knk::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    data_[i] = rhs.data_[i];
  }
}

template< class T >
knk::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  Vector()
{
  swap(rhs);
}

template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > copy(rhs);
  swap(copy);
  return *this;
}

template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  Vector< T > moved(std::move(rhs));
  swap(moved);
  return *this;
}

template< class T >
void knk::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
knk::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
bool knk::Vector< T >::isEmpty() const noexcept
{
  return size_ == 0;
}

template< class T >
size_t knk::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t knk::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
const T& knk::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
T& knk::Vector< T >::operator[](size_t id) noexcept
{
  return const_cast< T& >((*static_cast< const Vector< T >* >(this))[id]);
}

template< class T >
const T& knk::Vector< T >::at(size_t id) const
{
  if (id >= getSize())
  {
    throw std::out_of_range("id out of bound");
  }
  return (*this)[id];
}

template< class T >
T& knk::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  const T& ref = cthis->at(id);
  return const_cast< T& >(ref);
}

template< class T >
void knk::Vector< T >::pushBack(const T& t)
{
  Vector< T > v(getSize() + 1);
  for (size_t i = 0; i < getSize(); ++i)
  {
    v[i] = (*this)[i];
  }
  v[getSize()] = t;
  swap(v);
}

template< class T >
void knk::Vector< T >::pushBackRepeat(const T& t, size_t k)
{
  Vector< T > copy(*this);
  for (size_t i = 0; i < k; ++i)
  {
    copy.pushBack(t);
  }
  swap(copy);
}

template< class T >
void knk::Vector< T >::pushFront(const T& t)
{
  Vector< T > v(getSize() + 1);
  v[0] = t;
  for (size_t i = 0; i < getSize(); ++i)
  {
    v[i + 1] = (*this)[i];
  }
  swap(v);
}

template< class T >
void knk::Vector< T >::popBack()
{
  if (isEmpty())
  {
    throw std::out_of_range("Vector is empty");
  }

  Vector< T > v(getSize() - 1);
  for (size_t i = 0; i < v.getSize(); ++i)
  {
    v[i] = (*this)[i];
  }
  swap(v);
}

template< class T >
void knk::Vector< T >::insert(size_t id, const T& t)
{
  if (id > getSize())
  {
    throw std::out_of_range("id out of bound");
  }

  Vector< T > v(getSize() + 1);

  for (size_t i = 0; i < id; ++i)
  {
    v[i] = (*this)[i];
  }

  v[id] = t;

  for (size_t i = id; i < getSize(); ++i)
  {
    v[i + 1] = (*this)[i];
  }

  swap(v);
}

template< class T >
void knk::Vector< T >::insert(size_t id, const Vector< T >& rhs, size_t begin, size_t end)
{
  if (id > getSize())
  {
    throw std::out_of_range("id out of bound");
  }

  if (begin > end || end > rhs.getSize())
  {
    throw std::out_of_range("range out of bound");
  }

  size_t addCount = end - begin;
  Vector< T > v(getSize() + addCount);

  for (size_t i = 0; i < id; ++i)
  {
    v[i] = (*this)[i];
  }

  for (size_t i = begin; i < end; ++i)
  {
    v[id + (i - begin)] = rhs[i];
  }

  for (size_t i = id; i < getSize(); ++i)
  {
    v[addCount + i] = (*this)[i];
  }

  swap(v);
}

template< class T >
void knk::Vector< T >::erase(size_t id)
{
  if (id >= getSize())
  {
    throw std::out_of_range("id out of bound");
  }

  Vector< T > v(getSize() - 1);

  for (size_t i = 0; i < id; ++i)
  {
    v[i] = (*this)[i];
  }

  for (size_t i = id + 1; i < getSize(); ++i)
  {
    v[i - 1] = (*this)[i];
  }

  swap(v);
}

template< class T >
void knk::Vector< T >::erase(size_t begin, size_t end)
{
  if (begin > end || end > getSize())
  {
    throw std::out_of_range("range out of bound");
  }

  size_t removeCount = end - begin;
  Vector< T > v(getSize() - removeCount);

  for (size_t i = 0; i < begin; ++i)
  {
    v[i] = (*this)[i];
  }

  for (size_t i = end; i < getSize(); ++i)
  {
    v[i - removeCount] = (*this)[i];
  }

  swap(v);
}

template< class T >
bool knk::operator==(const Vector< T >& lhs, const Vector< T >& rhs)
{
  if (lhs.getSize() != rhs.getSize())
  {
    return false;
  }

  for (size_t i = 0; i < lhs.getSize(); ++i)
  {
    if (lhs[i] != rhs[i])
    {
      return false;
    }
  }

  return true;
}

template< class T >
bool knk::operator!=(const Vector< T >& lhs, const Vector< T >& rhs)
{
  return !(lhs == rhs);
}

#endif
