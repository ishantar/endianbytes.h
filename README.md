# endianbytes.h
unecessarily portable byte-addressed machine words with customizeable, significance-ordered identifiers


Including `endianbytes.h` allows you to declare several types of ENDIANBYTES object; namely ENDIANBYTES_STRUCT_ASCENDING, ENDIANBYTES_STRUCT_DESCENDING, ENDIANBYTES_UNION_ASCENDING and ENDIANBYTES_UNION_DESCENDING.

The ENDIANBYTES_UNION types each have two members: an anonymous structure of the appropriate ENDIANBYTES_STRUCT flavor, and a member with name `word` and `void*` type.

Both ENDIANBYTES_STRUCT types are pointer-sized structures with a `sizeof(void*)` number of members, each of which is type `unsigned char`.  The names for these members are selected automatically to match the target architecture for the current build.  The automatic names are always `u8_0` through `u8_[n]`, where `n+1` is the size of a pointer in bytes.

The automatic names are, as appropriate for the ENDIANBYTES type flavor, assigned to members in byte-significance order.  That is, `u8_0` will always address the least-significant byte in an ENDIANBYTES_STRUCT_ASCENDING, or the most-significant byte in an ENDIANBYTES_STRUCT_DESCENDING, and the names of the other members will proceed in order of significance.

An additional name may be assigned to each member byte.  To set the additional name for a member `u8_[n]`, re-define the macro `u8_[n]()` to expand to the desired name (ie, `#undef u8_[n]`, `#define u8_[n]() [NAME]`).  This must be done before declaring the ENDIANBYTES object or type that is to make use of the name, but *not* before `endianbytes.h` is first \#included.

When an ENDIANBYTES object is declared, it uses any additional names that are currently set.  To unset an additional name, re-define the appropriate `u8_[n]()` macro such that it expands to nothing.  Leaving a `u8_[n]()` macro undefined will cause an error in future declarations.

All additional names are unset when a file \#includes `endianbytes.h`.  Repeatedly \#including `endianbytes.h` is safe, and can serve this purpose.


The ENDIANBYTES object macros each expand to a brace-enclosed statement suitable to serve as a `struct-declaration-list`.  When using the object macros to declare a type or variable, they must appear following a `struct` or `union` type specifier, and be followed by a semicolon (just as would any declaration-list part of such a statement).  The usual permutations remain valid for declarations using the object macros, including tag names, instance variable initialization, declaration as part of a typedef, and declaration of anonymous members or objects.

While this is unlikely to be useful, note that because the object macros simply expand to declaration-lists, either ENDIANBYTES_STRUCT macro could technically be used to declare a union (or vice-versa).  This point is intended to be illustrative, not as actionable advice. :p


An example: the following code would declare a type `struct MyStruct` which contains one anonymous ENDIANBYTES_STRUCT_ASCENDING structure member, and one ENDIANBYTES_STRUCT_DESCENDING structure member named `Desc`, which has type `struct Descending`, and a member with additional name `bottom` addressing its least-significant byte\:

 ```c
 struct MyStruct {
     struct ENDIANBYTES_STRUCT_ASCENDING;
    # undef u8_7
    # define u8_7() bottom
     struct Descending ENDIANBYTES_STRUCT_DESCENDING Desc;
 };
 ```
