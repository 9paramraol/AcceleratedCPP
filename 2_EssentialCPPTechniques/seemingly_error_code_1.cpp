#include<iostream>
// Use the experiment calss for const propgation
class A
{
  public:
    A (int* ptr) : ptr_(ptr) {};
    void set_ptr_val (int a) const { *ptr_ = a;};
  private:
    int* ptr_;
};

int main()
{
  return 0;
}
