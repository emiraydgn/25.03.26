#include "pe-vector.hpp"
#include <iostream>
#include <cstring>

using knk::Vector;

bool testConstructAndDestruct(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  return true;
}

bool testDefaultVectorIsEmpty(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  return v.isEmpty();
}

bool testSizeOfEmptyVector(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  return v.getSize() == 0;
}

bool testSizeOfNonEmptyVector(const char** pname)
{
  *pname = __func__;
  Vector<int> v(3, 5);
  return v.getSize() == 3;
}

bool testCapacity(const char** pname)
{
  *pname = __func__;
  Vector<int> v(4, 1);
  return v.getCapacity() == 4;
}

bool testPushBack(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  v.pushBack(10);
  return v.getSize() == 1 && v[0] == 10;
}

bool testPushBackRepeat(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  v.pushBack(3);
  v.pushBackRepeat(7, 3);
  return v.getSize() == 4 && v[0] == 3 && v[1] == 7 && v[2] == 7 && v[3] == 7;
}

bool testPushFront(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  v.pushBack(2);
  v.pushFront(1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testPopBack(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.popBack();
  return v.getSize() == 1 && v[0] == 1;
}

bool testPopBackException(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  try
  {
    v.popBack();
    return false;
  }
  catch (const std::out_of_range& e)
  {
    return !std::strcmp(e.what(), "Vector is empty");
  }
  catch (...)
  {
    return false;
  }
}

bool testAtAccess(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  v.pushBack(5);
  return v.at(0) == 5;
}

bool testAtConstAccess(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  v.pushBack(9);
  const Vector<int>& cv = v;
  return cv.at(0) == 9;
}

bool testAtException(const char** pname)
{
  *pname = __func__;
  Vector<int> v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range& e)
  {
    return !std::strcmp(e.what(), "id out of bound");
  }
  catch (...)
  {
    return false;
  }
}

bool testAtConstException(const char** pname)
{
  *pname = __func__;
  const Vector<int> v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range& e)
  {
    return !std::strcmp(e.what(), "id out of bound");
  }
  catch (...)
  {
    return false;
  }
}

bool testBracketReadWrite(const char** pname)
{
  *pname = __func__;
  Vector<int> v(3, 0);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;
  return v[0] == 10 && v[1] == 20 && v[2] == 30;
}

bool testConstBracketRead(const char** pname)
{
  *pname = __func__;
  Vector<int> v{4, 5};
  const Vector<int>& cv = v;
  return cv[0] == 4 && cv[1] == 5;
}

bool testCopyConstructor(const char** pname)
{
  *pname = __func__;
  Vector<int> v{1, 2, 3};
  Vector<int> copy = v;
  return copy == v;
}

bool testMoveConstructor(const char** pname)
{
  *pname = __func__;
  Vector<int> v{1, 2, 3};
  Vector<int> moved(std::move(v));
  return moved.getSize() == 3 && moved[0] == 1 && moved[1] == 2 && moved[2] == 3;
}

bool testCopyAssignment(const char** pname)
{
  *pname = __func__;
  Vector<int> v{1, 2};
  Vector<int> x;
  x = v;
  return x == v;
}

bool testMoveAssignment(const char** pname)
{
  *pname = __func__;
  Vector<int> v{7, 8};
  Vector<int> x;
  x = std::move(v);
  return x.getSize() == 2 && x[0] == 7 && x[1] == 8;
}

bool testInsertSingle(const char** pname)
{
  *pname = __func__;
  Vector<int> v{1, 3};
  v.insert(1, 2);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertSingleException(const char** pname)
{
  *pname = __func__;
  Vector<int> v{1};
  try
  {
    v.insert(2, 9);
    return false;
  }
  catch (const std::out_of_range& e)
  {
    return !std::strcmp(e.what(), "id out of bound");
  }
  catch (...)
  {
    return false;
  }
}

bool testInsertRange(const char** pname)
{
  *pname = __func__;
  Vector<int> a{1, 4};
  Vector<int> b{2, 3, 5};
  a.insert(1, b, 0, 2);
  return a.getSize() == 4 && a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4;
}

bool testInsertRangeException(const char** pname)
{
  *pname = __func__;
  Vector<int> a{1, 4};
  Vector<int> b{2, 3, 5};
  try
  {
    a.insert(1, b, 0, 5);
    return false;
  }
  catch (const std::out_of_range& e)
  {
    return !std::strcmp(e.what(), "range out of bound");
  }
  catch (...)
  {
    return false;
  }
}

bool testEraseSingle(const char** pname)
{
  *pname = __func__;
  Vector<int> v{1, 2, 3};
  v.erase(1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}

bool testEraseSingleException(const char** pname)
{
  *pname = __func__;
  Vector<int> v{1, 2};
  try
  {
    v.erase(2);
    return false;
  }
  catch (const std::out_of_range& e)
  {
    return !std::strcmp(e.what(), "id out of bound");
  }
  catch (...)
  {
    return false;
  }
}

bool testEraseRange(const char** pname)
{
  *pname = __func__;
  Vector<int> v{1, 2, 3, 4, 5};
  v.erase(1, 4);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 5;
}

bool testEraseRangeException(const char** pname)
{
  *pname = __func__;
  Vector<int> v{1, 2, 3};
  try
  {
    v.erase(1, 5);
    return false;
  }
  catch (const std::out_of_range& e)
  {
    return !std::strcmp(e.what(), "range out of bound");
  }
  catch (...)
  {
    return false;
  }
}

bool testEquality(const char** pname)
{
  *pname = __func__;
  Vector<int> a{1, 2, 3};
  Vector<int> b{1, 2, 3};
  Vector<int> c{1, 2, 4};
  return (a == b) && (a != c);
}

int main()
{
  using test_t = bool(*)(const char**);
  using case_t = std::pair<test_t, const char*>;

  case_t tests[] = {
    { testConstructAndDestruct, "Constructor/destructor must work" },
    { testDefaultVectorIsEmpty, "Default constructed vector must be empty" },
    { testSizeOfEmptyVector, "Size of empty vector must be zero" },
    { testSizeOfNonEmptyVector, "Size of non-empty vector must be correct" },
    { testCapacity, "Capacity must match constructed size" },
    { testPushBack, "pushBack must append an element" },
    { testPushBackRepeat, "pushBackRepeat must append repeated values" },
    { testPushFront, "pushFront must insert at the beginning" },
    { testPopBack, "popBack must remove the last element" },
    { testPopBackException, "popBack on empty vector must throw" },
    { testAtAccess, "at must return correct element" },
    { testAtConstAccess, "const at must return correct element" },
    { testAtException, "at out of bound must throw" },
    { testAtConstException, "const at out of bound must throw" },
    { testBracketReadWrite, "operator[] must support read/write" },
    { testConstBracketRead, "const operator[] must support read" },
    { testCopyConstructor, "Copy constructor must copy elements" },
    { testMoveConstructor, "Move constructor must move elements" },
    { testCopyAssignment, "Copy assignment must copy elements" },
    { testMoveAssignment, "Move assignment must move elements" },
    { testInsertSingle, "Single insert must work" },
    { testInsertSingleException, "Single insert out of bound must throw" },
    { testInsertRange, "Range insert must work" },
    { testInsertRangeException, "Range insert with invalid bounds must throw" },
    { testEraseSingle, "Single erase must work" },
    { testEraseSingleException, "Single erase out of bound must throw" },
    { testEraseRange, "Range erase must work" },
    { testEraseRangeException, "Range erase with invalid bounds must throw" },
    { testEquality, "Equality operators must work" }
  };

  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;

  for (size_t i = 0; i < count; ++i)
  {
    const char* name = nullptr;
    bool result = false;

    try
    {
      result = tests[i].first(&name);
    }
    catch (...)
    {
      result = false;
    }

    if (!result)
    {
      ++failed;
      std::cout << "[FAIL] " << name << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }

  std::cout << "Summary:\n";
  std::cout << "\t" << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
}
