## rules of auto and relation to decltype.
  - const and referenceness:
    1. Remove the const and refrece parameters from the type to be matched.
    2. Not match the type.
```
int a = 10;
const int& b = a;
auto c = b; // type of c is  int
```
## why auto& takes the constantness too
Basically if reference is used then in that case the what we expect is that the type matches one to one compared to the object.
```
auto& c = b;
/* the intent over here is to get b as it is, so => the exact type of b should be taken along with the constantness */
```
## decltype (auto)
- Just take the rhs and get its type.
```
decltype(auto) c = b;
/* c take the type that is same as b*/
```
## Trailing return types and when to use them.
- Copy elision cases.
- Why it does not work in case of std::move()
- AUTO& constantness preserving
- copy elision: Cases when it is allowed and not allowed
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
