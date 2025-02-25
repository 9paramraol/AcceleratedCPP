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

- auto x, has to be initialized.
- binding must specified.
- Usage of auto& and const auto&, its advantages.
- auto&& and advantage over const auto&
- auto&& is a forwarding reference, why?
- Final rules:
  1. const auto : fundamental types + small non fundamental types
  2. const auto&: large types where you want to avoid the copy
  3. auto&& : take and dump type variables.
- minor detail about std::forward, and the calling of the correct function.
- const function and const propogation.
- Different types of operations:
  1. Copy
  2. Swap
  3. Move
- Rule of 3 and the 2 problems that arise because of it, finally the rule of 5.
- What are r-values?
- Copy assignable and move assignable.
- default and its usage. Adding even one of the 5 leads to non-generation of the other (why? answer this part)
- Works in copy but not in move.
- The noexcpet note.
- Default destructors to get more peformance. The case of std::copy and why its not optimized.
- The pitfall of using the default move. Note:
  1. compound types are actaully moved.
  2. simple types are just moved.
- && at the end of the function, how to use it.
- Copy elision, and why we shouldn't always move.
- Cases when copies are ok, cases when copies are not ok.
