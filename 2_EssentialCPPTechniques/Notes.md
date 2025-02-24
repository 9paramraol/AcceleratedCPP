# TRAILING RETURN TYPES FOR AUTO
# THE AUTO AND DECLTYPE RULES

- auto and decltype (auto)
- rules of auto and relation to decltype.
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
