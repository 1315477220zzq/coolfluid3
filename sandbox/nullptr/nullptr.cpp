#include <iostream>
#include <typeinfo>

template < typename T>
void use_variable( T x )
{
  std::cout<<x<<std::endl;
}

const // It is a const object...
class nullptr_t 
{
  public:
    template<class T>
      operator T*() const // convertible to any type of null non-member pointer...
    { return 0; }
 
#if 0
    template<class C, class T>
    operator T C::*() const   // or any type of null member pointer...
    { return 0; }
#endif

  private:
    void operator&() const;  // Can't take address of nullptr
 
} nullptr = {};
 
struct C
{
  void func();
};
 
template<typename T> 
void g( T* t ) {}
 
template<typename T> 
void h( T t ) {}
 
void func (double *) {}
void func (int) {}
 
int main(void)
{
  char * ch = nullptr;        // ok
  use_variable( ch );

  func (nullptr);             // Calls func(double *)
  func (0);                   // Calls func(int)
  void (C::*pmf2)() = 0;      // ok

  use_variable(pmf2);

//  void (C::*pmf)() = nullptr; // ok
  nullptr_t n1, n2;
  n1 = n2;
  
  // nullptr_t *null = &n1;    // Address can't be taken.
  //if (nullptr == ch) {}       // ok
  // if (nullptr == pmf) {}      // Valid statement; but fails on g++ 4.1.1 due to bug #33990
  
  const int n = 0;
//  if (nullptr == n) {}        // Should not compile; but only Comeau shows an error.
  use_variable(n);

  //int p = 0;
  //if (nullptr == p) {}      // not ok
  //g (nullptr);              // Can't deduce T
  
  int expr = 0;
  char* ch3 = expr ? nullptr : nullptr; // ch1 is the null pointer value
  use_variable(ch3);

  //char* ch4 = expr ? 0 : nullptr;     // error, types are not compatible
  //int n3 = expr ? nullptr : nullptr;  // error, nullptr can’t be converted to int
  //int n4 = expr ? 0 : nullptr;        // error, types are not compatible
 
  h( 0 );                // deduces T = int
  h( nullptr );          // deduces T = nullptr_t
  h( (float*) nullptr ); // deduces T = float*
 
  use_variable( sizeof( nullptr ) );             // ok
  use_variable( typeid( nullptr_t ).name() );    // ok

  try{
      throw nullptr;         // ok
  } catch (...) {};

  return 0;
}
