#include <iostream>
#include "pe-vector.hpp"
using knk::Vector;
bool testConstructAndDestruct(const char ** pname){
        *pname = __func__;
    knk::Vector< int > v;
     return true;
}
bool testDefaultVectorIsEmpty(const char ** pname){
    *pname = __func__;
     knk::Vector< int > v;
     return v.isEmpty() && (!v.getSize());

}
bool testSizeOfEmptyVector(const char ** pname){
    *pname = __func__;
     knk::Vector< int > v;
     bool case1 = !v.getSize();
     return case1;
}
bool testSizeOfNonEmptyVector(const char ** pname){
    *pname = __func__;
  constexpr size_t size = 2ull;
  try
  {
    knk::Vector<int> v(size, 10);
      return v.getSize() == size;

  }
  catch(...)
  {
    throw;
  }
}
int main()
{
    size_t failed = 0;
    using test_t = bool(*)(const char **);
    using case_t = std::pair< test_t, const char * >;
    case_t tests[] = {
        {testConstructAndDestruct, "Vector must be default consturctable"},
        {testDefaultVectorIsEmpty, "Default constructed vector must be empty"},
        {testSizeOfEmptyVector, "Size of empty vector must be zero"},
       {testSizeOfNonEmptyVector, "Size of non empty vector must be greater than zero"},


    };
    constexpr size_t count = sizeof(tests) / sizeof(case_t);
    for(size_t i = 0; i < count; ++i){
        const char * testName = nullptr;
        bool r = tests[i].first(&testName);
        if(!r){
            ++failed;
            std::cout << "[FAIL] " << testName << "\n";
            std::cout << "\t " << tests[i].second << "\n";

        }
    }
                std::cout << "Summary: " << (count - failed) << "passed\n";
                std::cout << "\t " << count << "total\n";
}
