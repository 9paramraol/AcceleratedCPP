## 1. rules of auto and relation to decltype.
  - const and referenceness:
    1. Remove the const and refrece parameters from the type to be matched.
    2. Not match the type.
```cpp
int a = 10;
const int& b = a;
auto c = b; // type of c is  int
```

## 2. why auto& takes the constantness too
Basically if reference is used then in that case the what we expect is that the type matches one to one compared to the object.
```cpp
auto& c = b;
/* the intent over here is to get b as it is, so => the exact type of b should be taken along with the constantness */
```

## 3. decltype (auto)
- Just take the rhs and get its type.
```cpp
decltype(auto) c = b;
/* c take the type that is same as b*/
```

## 4. Trailing return types and when to use them.
- Certain cases where template functions are used, the return type is often deducable by the compiler, in those cases it is prudent to give the trailing return type.
```cpp
tempate<typename T, typename U>
auto func (T a, U b, bool m) -> decltype (a * b)
{
  if (m)
    return a;
  else
    return b;
}

func (1.0, 1); /* the function may not know what to return*/
```

## 5. Copy elision cases
**NOTE**: elision was gurateed post c++17 prior to that it was the will of the compiler
- Guranteed:
  1. When a function returns are temporary object.
  2. When a variable is assigned a temporary created object.
```cpp
A func () { return A();}
A a (func()); // the object is directly allocated inside

A a = A(); // the A() can be directly moved to a
```
- Not guranteed:
  1. In case a local variable is returned (**destructor if present has to be called so we can not elide away**).
  2. When we call std::move, basically now the move operator needs to be invoked.
```cpp
A func()
{
  A a;
  return a;
}
// now the destructor of a will be called hence this cannot be elided, a temporry object wille created w
A a = std::move (b); // Explicit instructtion to use the move assignment operator
```

## 6. auto x, has to be initialized.
Nothing fancy over here, just a generic way to initialize any variable.
```cpp
auto x = a;
auto b = Obj();
```
**Note**: copy-elision is guranteed post c++17 so these initializations will be optimized whenever possible.

## 7. Usage of auto& and const auto&, its advantages.
- **const auto&** can bind to anything, weather it be a normal object or a temporary object. The only caveat is that the object remaing constant througout the lifetime and can not be mutated.
- **auto&**: should be used if the object needs to be mutated but this will not bind to the r-values.
```cpp
const auto& a = A(); // this was a temporary object that will remain till the scope ends
const auto& b = c; // this will remaing till c is not destroyed
```

## 8. auto&& and advantage over const auto&, and why is it called forwarding refrence..
- auto&& allows us to mutate the objects, but const does not.
- auto&& transferes the type as it is. It forwards l-values as l-valyes and r-values as r-values.

**Final rules:**
  1. const auto : fundamental types + small non fundamental types, they were going to be copied anyways.
  2. const auto&: large types where you want to avoid the copy.
  3. auto&& : take and dump type variables.

## 9. minor detail about std::forward, and the calling of the correct function.
```cpp
#include <iostream>
#include <utility>

template <typename T>
void forwarder(T&& arg) {
      process(std::forward<T>(arg));  // Perfect forwarding
}

void process(int& x) { std::cout << "Lvalue\n"; }
void process(int&& x) { std::cout << "Rvalue\n"; }

int main() {
  int a = 5;
  forwarder(a);   // Calls process(int&) -> "Lvalue"
  forwarder(10);  // Calls process(int&&) -> "Rvalue"
}
```

## 10. const function and const propogation
- **std::experimental::propogate_const** is the type that is present in std, the pointer's constantness is porpogated to the value too.

# Move semantics:
- Different types of operations:
  1. Copy : take the object memcpy and thats it.
  2. Swap : take the object and change the pointers.
  3. Move : take the object and memmove, the original memory may get destroyed.

## 11. Rule of 3 and the 2 problems that arise because of it, finally the rule of 5.
- In the earlier versions of cpp there was not move constructor or assignment operator.
- This lead to a lot of deep copies being created.
- So move-tor's were introduced to reduce the memory footprints and make operations more optimized.

## 12. What are r-values?
- They are non-named values in code or the ones which have std::move wrapped around them.
 
## 13. default and its usage
- If no tor is added the the compiler will generate its own tor's.
- If a copy constructor is added then the compiler **won't** generate the move operators. This is becase the programmer may have intented to us the copy constructors instead of the move ones.
- For move, this is not the case as there will definitely be cases where the deep copy needs to be created.
- **Note** : add noexcept in move, or else compiler may not recognize it.

## 14. Default destructors to get more peformance
- When default destructors are not used, then all the named variables are destructed when they go out of scope, thus preventing copy-elision in some compilers.
- Think of an example where this would be a problem (hint its copy related).

## 15. The pitfall of using the default move.
Note:
  1. compound types are actaully moved.
  2. simple types are just moved.
```cpp
class A
{
  int a; // this value will remain as it is if the move is used
  std::vector<int> b; // this will be swapped by the defautlt move
}
```
- Access to b[a] will just f things up.

## 16. && at the end of the function, how to use it.
```cpp
class A
{
  void func() && { std::cout << "This is && function" << std::endl;}
  void func() { std::cout << "This is l value function" << std::endl;}
}
```
pretty much the same as function overloading, basicall && at the end of the function indicates that this function should be used incase the call comes from a temporary object.

## 17. Cases when copies are ok, cases when copies are not ok.
- If the function is transforming from the original input, then copies are alright since they were going to be formed any way.
- If just assignment is taking place then nah.. just give the refrence, or move the object.
