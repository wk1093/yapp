# XPP

A C++ based programming language that removes the need for headers and source separation by using a single file for both declarations and definitions. It is designed to be simple and easy to use, while still providing the power and flexibility of C++.

Whether something is in the "header" or "public" section is determined by the `pub` and `priv` keywords. If a member is declared with the `pub` keyword, it is considered public and can be accessed from outside the class. If a member is declared with the `priv` keyword, it is considered private and can only be accessed from within the class.

There is some exceptions and special cases to this rule. `inline` functions are always considered public.

Default behavior (`pub` and `priv` not specified) is different depending on many things, such as whether it is a function, variable, or type. As well as if it is a declaration or definition.