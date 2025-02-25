#include "iostream"

template<typename A, typename B>
auto add (A a, B b) -> decltype (a * b)
{
  if (a > b)
    return a;
  else
    return b;
}

class A_Class
{
  private:
    int a;
  public:
    A_Class (int a) : a(a) {};

    A_Class operator* (const A_Class& other)
    {
     return A_Class(a * other.a);
    }
};

int main()
{
  add (1, 2.0);
  // On a class
  // A_Class a{1};
  // A_Class b{1};
  // add (a, b);
  return 0;
}
