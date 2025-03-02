#include<iostream>
#include<cassert>

int main()
{
  constexpr int a = 10;
  static_assert (a == 10);

  for (int i = 0; i < a; ++i)
  {
    assert (i < 10);
  }
  return 0;
}
