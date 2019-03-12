# endianbytes.h
unecessarily portable byte-addressed machine words with customizeable, significance-ordered identifiers


Including `endianbytes.h` allows you to declare several types of ENDIANBYTES object; namely ENDIANBYTES_STRUCT_ASCENDING, ENDIANBYTES_STRUCT_DESCENDING, ENDIANBYTES_UNION_ASCENDING and ENDIANBYTES_UNION_DESCENDING.

The ENDIANBYTES_UNION types each have two members: an anonymous structure of the appropriate ENDIANBYTES_STRUCT flavor, and a member with name `word` and `void*` type.

Both ENDIANBYTES_STRUCT types are pointer-sized structures with a `sizeof(void*)` number of members, each of which is type `unsigned char`.  The names for these members are selected automatically to match the target architecture for the current build.  The automatic names are always `u8_0` through `u8_[n]`, where `n+1` is the size of a pointer in bytes.

The automatic names are, as appropriate for the ENDIANBYTES type flavor, assigned to members in byte-significance order.  That is, `u8_0` will always address the least-significant byte in an ENDIANBYTES_STRUCT_ASCENDING, or the most-significant byte in an ENDIANBYTES_STRUCT_DESCENDING, and the names of the other members will proceed in order of significance.

Additional names may be assigned to each member byte; each additional name must declare a type, which may be any type with sizeof 1.
To set additional names for the member byte with automatic name  `u8_[n]`, re-define the macro `u8_[n]()` as a function-like macro with no parameters which expands to a (semicolon-separated and -terminated) series of declarations that will declare each additional name.
For instance, the following code would cause member byte `u8_0` to have an unsigned additional name `bottom_8` and a signed additional name `b8`:
`#undef u8_0
 #define u8_0() unsigned char bottom_8; signed char b8;`
Any additional names must be set before declaring an ENDIANBYTES object for that object to use those additional names.  Only those additional names set `endianbytes.h` was last #included will be in effect.

When an ENDIANBYTES object is declared, it uses any additional names that are currently set.  To unset additional names, re-define the appropriate `u8_[n]()` macro with the relevant declarations removed from its expansion.
To unset all of a member byte's additional names, its `u8_[n]()` macro should expand to nothing.  Leaving a `u8_[n]()` macro undefined will cause an error.

All additional names are unset for all member bytes whenever a file #includes `endianbytes.h`.  It is safe to repeatedly `#include endianbytes.h` for this purpose.


The ENDIANBYTES object macros each expand to a brace-enclosed statement suitable to serve as a `struct-declaration-list`.  When using the object macros to declare a type or variable, they must appear following a `struct` or `union` type specifier, and be followed by a semicolon (just as would any declaration-list part of such a statement).  The usual permutations remain valid for declarations using the object macros, including tag names, instance variable initialization, declaration as part of a typedef, and declaration of anonymous members or objects.

While this is unlikely to be useful, note that because the object macros simply expand to declaration-lists, either ENDIANBYTES_STRUCT macro could technically be used to declare a union (or vice-versa).  This point is intended to be illustrative, not as actionable advice. :p


An example: the following code would declare a type `struct MyStruct` which contains one anonymous ENDIANBYTES_STRUCT_ASCENDING structure member, and one ENDIANBYTES_STRUCT_DESCENDING structure member named `Desc`, which has type `struct Descending`, and a member with unsigned additional name `bottom` addressing its least-significant byte:

 ```c
 struct MyStruct {
     struct ENDIANBYTES_STRUCT_ASCENDING;
    # undef u8_7
    # define u8_7() unsigned char bottom;
     struct Descending ENDIANBYTES_STRUCT_DESCENDING Desc;
 };
 ```
