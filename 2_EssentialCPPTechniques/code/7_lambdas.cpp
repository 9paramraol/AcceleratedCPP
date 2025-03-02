#include<iostream>
#include<functional>

int main()
{
  // -------- copy related things
  int x = 10;
  auto l = [x] (int a) mutable { std::cout << a * (++x) << std::endl; };
  l(1); // 11
  std::function<void(int)> b = l;
  l(1); // 12
  b(1); // 12

  // --------- rest of things
  auto m = [] (auto x, auto y) { return x * y; };
  auto n = [] <typename T> (T a) { std::cout << a << std::endl;};
  n (1);
  return 0;
}
