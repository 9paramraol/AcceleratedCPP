#include <iostream>

class A
{
  private:
    int i = 0;
  public:
    A () { std::cout << "Constructor called" << std::endl; }
    A& operator=(A&& a) noexcept { std::cout << "Move assignment called" << std::endl; return *this;}
    A (A&& a) noexcept { std::cout << "Move constructor called" << std::endl; }
    A& operator=(const A& a) { std::cout << "Copy assignment called" << std::endl; return *this;}
    A (const A& a) { std::cout << "Copy constructor" << std::endl; }
    ~A () { std::cout << "Destructor called" << std::endl; }
};

A func1 () { return A(); }
A func2 () { A a; return a;}

int main ()
{
  std::cout << "---> Case 1 <---" << std::endl;
  A a = func1();
  std::cout << "---> Case 2 <---" << std::endl;
  A b = A();
  std::cout << "---> Case 3 <---" << std::endl;
  A c = func2();
  std::cout << "---> Case 4 <---" << std::endl;
  A d = std::move (a);
  std::cout << "---> Cases completed  <---" << std::endl;
}

/*
- The compiler on my machine has performed copy elision for case 3, but please note that this entirely at the shraddha of a compiler
- For case 4 move constructor is called becuase this is a construction, object d is being created for the first time.
*/
