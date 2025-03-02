## Contracts:
- This is just a formal way of looking at a program in terms of a caller and a calle. The fundamental concepts for it are as follows:
  1. Precondition: The condition that must be satisfied before the caller calls the calle.
  2. Postcondition: The condition that must be satisfied before the calle passes over the control to the caller.
  3. Invariant: the condition that always holds true (except may be temporarily).

This book suggests if the class is cohesive enough to have an invariant then it can lead to faster debugging, or even better to a code that has lesser number of bugs.

## Managing contracts:
- There are two ways to manage a contract in cpp:
  1. static\_assert: these checks are performed during the compilation.
  2. assert: the checks in this are performed during runtime.

## Errors

- The errors are primarily of 2 types:
  1. Programming errors : These are the ones that can be avoided using the assert statements in your code, to ensure the that the precondition and post condition are always satisfied. There are not performance hits as everything all the assert statements are not there during the runtime.
  2. Runtime errors:
  - Can be recoverable: Some techiniques to ensure that your code works correctly during these are as follows:
    * Preserve the intermediate states and swap only when all the functions have been performed correctly.
    ```cpp
    void function (std::string& str)
    {
      std::string temp {str};
      temp += f1();
      temp += f2();
      std::swap (temp, str);
    }
    ```
    Note: this ensures that even if f1, f2 throw out an error str is still intact.
  * Use std::pair or std::optional to indicate the return the values, this ensures that the code code works despite the occurance.
  * We can always throw an exception but this would come with a performance hit, but always compare a hit to the corresponding if/else code and not the generic errorless code.
  * **noexpcet** should be used if you are expecting that the function is never going throw an exception.If the function still thorws an exeception the the compiler calls std::terminate instead of unwinding the stack.

## Lambdas:

1. The capture clause:
- The varible present in the scope of code can be captured inside the lambda as a copy, or as a reference.
```cpp
auto a = [x] () { std::cout << x << std::endl; }; // x is passed as a copy
auto b = [&x] () { ++x;};
auto c = [&] () { std::cout << "Addr of x is same : " << &x << std::endl;}; // all the variables that are there inside the lambda will be taken as reference.
auto d = [=] () { std::cout << "Addr of x is different : " << &x << std::endl;}; // all the variables that are there inside the lambda will be take as copy
```
**Note**: in the first example x inside the function can't be modifed as the lambda function is basically a const function.

2. The expansion:
The lambdas are basically converted into a class whose **operator()()** function corresponds to the lambda:
```cpp
auto check = [&x] (int a)  { std::cout << a * (++x) << std::endl; };
class L
{
  private:
    int& x_;
  public:
    L (int& x) : x_ (x) {}
  auto operator () (int a) const
  {
    std:cout << a * (++x_) << std::endl;
  }
};
L l (x);
l(); // calling of the lambda
```

3. Mutatble
- The thing to note is that in the expanded form of lambd, the **operator ()()** is a const function. This implies that the lambda can't change it private variables. So use the key word mutable, this internally removes the const from the operator.
```cpp
auto check2 = [x] () mutable { ++x; std::cout << x << std::endl; };
```

4. Why the capture related lambdas can't be copied, and how to deal with it.
- Lambdas by default do not have copy assignment operator, and since the capture lambdas basically hold a state without any way to copy them these can't be copied. This can be overriden using std::function, but the caveat is that the variables of the lambda need to be copyable (not like unique pointer). It copies the lambda class into heap and does its magic.
```cpp
auto l = [x] (int a) mutable { std::cout << a * (++x) << std::endl; };
l();
std::function<void(int)> b = l;
b();
```

5. Which is better for performance and the why?
- Lambdas are because they allow inlining, are on stack whereas std::functions are on heap.

6. Generic lambdas, mention the typename-one too
- Simply just write auto or typename and you can use lambdas for multiple types.
```cpp
auto l = [] (auto x, auto y) { return x * y; };
auto m = [] <typename T> (T a) { std::cout << a << std::endl;};
```
