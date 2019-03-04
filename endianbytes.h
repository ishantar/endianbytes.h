/*  `endianbytes.h`
 *
 * Including `endianbytes.h` allows you to declare several types of ENDIANBYTES
 * object; namely ENDIANBYTES_STRUCT_ASCENDING, ENDIANBYTES_STRUCT_DESCENDING,
 * ENDIANBYTES_UNION_ASCENDING and ENDIANBYTES_UNION_DESCENDING.  
 *
 * The ENDIANBYTES_UNION types each have two members: an anonymous structure of
 * the appropriate ENDIANBYTES_STRUCT flavor, and a member with name `word` and
 * `void*` type.
 *
 * Both ENDIANBYTES_STRUCT types are pointer-sized structures with a
 * `sizeof(void*)` number of members, each of which is type `unsigned char`.
 * The names for these members are selected automatically to match the target
 * architecture for the current build.  The automatic names are always `u8_0`
 * through `u8_[n]`, where `n+1` is the size of a pointer in bytes.
 *
 * The automatic names are, as appropriate for the ENDIANBYTES type flavor,
 * assigned to members in byte-significance order.  That is, `u8_0` will always
 * address the least-significant byte in an ENDIANBYTES_STRUCT_ASCENDING, or the
 * most-significant byte in an ENDIANBYTES_STRUCT_DESCENDING, and the names of
 * the other members will proceed in order of significance.
 *
 * An additional name may be assigned to each member byte.  To set the
 * additional name for a member `u8_[n]`, re-define the macro `u8_[n]()` to
 * expand to the desired name (ie, `#undef u8_[n]`, `#define u8_[n]() [NAME]`).
 * This must be done before declaring the ENDIANBYTES object or type that is to 
 * make use of the name, but *not* before `endianbytes.h` is first #included.
 *
 * When an ENDIANBYTES object is declared, it uses any additional names that are
 * currently set.  To unset an additional name, re-define the appropriate 
 * `u8_[n]()` macro such that it expands to nothing.  Leaving a `u8_[n]()` macro
 * undefined will cause an error in future declarations.
 *
 * All additional names are unset when a file #includes `endianbytes.h`.
 * Repeatedly #including `endianbytes.h` is safe, and can serve this purpose.
 *
 *
 * The ENDIANBYTES object macros each expand to a brace-enclosed statement
 * suitable to serve as a `struct-declaration-list`.  When using the object 
 * macros to declare a type or variable, they must appear following a `struct`
 * or `union` type specifier, and be followed by a semicolon (just as would any
 * declaration-list part of such a statement).  
 * The usual permutations remain valid for declarations using the object
 * macros, including tag names, instance variable initialization, declaration
 * as part of a typedef, and declaration of anonymous members or objects.
 *
 * While this is unlikely to be useful, note that because the object macros
 * simply expand to declaration-lists, either ENDIANBYTES_STRUCT macro could
 * technically be used to declare a union (or vice-versa).  This point is
 * intended to be illustrative, not as actionable advice. :p
 * 
 *
 * An example: the following code would declare a type `struct MyStruct` which
 * contains one anonymous ENDIANBYTES_STRUCT_ASCENDING structure member, and one
 * ENDIANBYTES_STRUCT_DESCENDING structure member named `Desc`, which has type 
 * `struct Descending`, and a member with additional name `bottom` addressing
 * its least-significant byte:
 *
 *  struct MyStruct {
 *      struct ENDIANBYTES_STRUCT_ASCENDING;
 *     # undef u8_7
 *     # define u8_7() bottom
 *      struct Descending ENDIANBYTES_STRUCT_DESCENDING Desc;
 *  };
 *
 */


#if !defined __BYTE_ORDER__ || !defined __SIZEOF_POINTER__
 # error error: `endianbytes.h` requires the __BYTE_ORDER__ and __SIZEOF_POINTER__ configuration macros, one or more of which has not been defined.  While normally a system header task, `endianbytes.h` is satisfied regardless of who #defines them.  Use the values `__ORDER_[ARCH]_ENDIAN__` and `[NUMBER]`, respectively, substituting `[ARCH]` with `LITTLE`, `BIG`, or `PDP` and `[NUMBER]` with either `4` or `8`, whichever describes your target architecture.

#elif !(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ || \
        __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__    || \
        __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__)   || \
      !(__SIZEOF_POINTER__ == 4 || \
        __SIZEOF_POINTER__ == 8)
 # error error: `endianbytes.h` sadly does not support your architecture.

#elif !defined ENDIAN_BYTES_OK && \
      defined u8_0 || defined u8_1 || defined u8_2 || defined u8_3 || \
      defined u8_4 || defined u8_5 || defined u8_6 || defined u8_7
  # error warning: `endianbytes.h` redefines the macros `u8_0` through `u8_7`, one or more of which has been set by another file in your program.  The author recommends using an altered copy of `endianbytes.h` that uses appropriate alternatives in place of said identifiers (though note that this alters the member names in `ENDIANBYTES_STRUCT`).
  # error To override this warning (allowing `u8_0`, etc to be redefined), compile with -DENDIAN_BYTES_OK or #define ENDIAN_BYTES_OK before #including `endianbytes.h`.

#endif

#ifdef __GNUC__
 # pragma GCC warning "Declaring an ENDIANBYTES_STRUCT or ENDIANBYTES_UNION may generate several warnings regarding missing declarations or declarations lacking identifiers.  These warnings describe the intended behaviour and may be disregarded."
#endif

#undef u8_0
#undef u8_1
#undef u8_2
#undef u8_3
#undef u8_4
#undef u8_5
#undef u8_6
#undef u8_7
#define u8_0()
#define u8_1()
#define u8_2()
#define u8_3()
#define u8_4()
#define u8_5()
#define u8_6()
#define u8_7()

#ifndef ENDIAN_BYTES_H
 #define ENDIAN_BYTES_H
 #define ENDIAN_BYTES_OK

 #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  # if __SIZEOF_POINTER__ == 4
   #define EB_CHAR1 u8_0
   #define EB_CHAR2 u8_1
   #define EB_CHAR3 u8_2
   #define EB_CHAR4 u8_3
  # elif __SIZEOF_POINTER__ == 8
   #define EB_CHAR1 u8_0
   #define EB_CHAR2 u8_1
   #define EB_CHAR3 u8_2
   #define EB_CHAR4 u8_3
   #define EB_CHAR5 u8_4
   #define EB_CHAR6 u8_5
   #define EB_CHAR7 u8_6
   #define EB_CHAR8 u8_7
  # endif
 #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  # if __SIZEOF_POINTER__ == 8
   #define EB_CHAR1 u8_7
   #define EB_CHAR2 u8_6
   #define EB_CHAR3 u8_5
   #define EB_CHAR4 u8_4
   #define EB_CHAR5 u8_3
   #define EB_CHAR6 u8_2
   #define EB_CHAR7 u8_1
   #define EB_CHAR8 u8_0
  # elif __SIZEOF_POINTER__ == 4
   #define EB_CHAR1 u8_3
   #define EB_CHAR2 u8_2
   #define EB_CHAR3 u8_1
   #define EB_CHAR4 u8_0
  # endif
 #elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
  # if __SIZEOF_POINTER__ == 8  /* hey, you never know */
   #define EB_CHAR1 u8_6
   #define EB_CHAR2 u8_7
   #define EB_CHAR3 u8_4
   #define EB_CHAR4 u8_5
   #define EB_CHAR5 u8_2
   #define EB_CHAR6 u8_3
   #define EB_CHAR7 u8_0
   #define EB_CHAR8 u8_1
  # elif __SIZEOF_POINTER__ == 4
   #define EB_CHAR1 u8_2
   #define EB_CHAR2 u8_3
   #define EB_CHAR3 u8_0
   #define EB_CHAR4 u8_1
  # endif
 #endif


 #if __SIZEOF_POINTER__ == 4
  #define ENDIANBYTES_STRUCT_ASCENDING { \
    union { unsigned char EB_CHAR1;  unsigned char EB_CHAR1(); }; \
    union { unsigned char EB_CHAR2;  unsigned char EB_CHAR2(); }; \
    union { unsigned char EB_CHAR3;  unsigned char EB_CHAR3(); }; \
    union { unsigned char EB_CHAR4;  unsigned char EB_CHAR4(); }; \
  }
  #define ENDIANBYTES_STRUCT_DESCENDING { \
    union { unsigned char EB_CHAR4;  unsigned char EB_CHAR4(); }; \
    union { unsigned char EB_CHAR3;  unsigned char EB_CHAR3(); }; \
    union { unsigned char EB_CHAR2;  unsigned char EB_CHAR2(); }; \
    union { unsigned char EB_CHAR1;  unsigned char EB_CHAR1(); }; \
  }
 #elif __SIZEOF_POINTER__ == 8
  #define ENDIANBYTES_STRUCT_ASCENDING { \
    union { unsigned char EB_CHAR1;  unsigned char EB_CHAR1(); }; \
    union { unsigned char EB_CHAR2;  unsigned char EB_CHAR2(); }; \
    union { unsigned char EB_CHAR3;  unsigned char EB_CHAR3(); }; \
    union { unsigned char EB_CHAR4;  unsigned char EB_CHAR4(); }; \
    union { unsigned char EB_CHAR5;  unsigned char EB_CHAR5(); }; \
    union { unsigned char EB_CHAR6;  unsigned char EB_CHAR6(); }; \
    union { unsigned char EB_CHAR7;  unsigned char EB_CHAR7(); }; \
    union { unsigned char EB_CHAR8;  unsigned char EB_CHAR8(); }; \
  }
  #define ENDIANBYTES_STRUCT_DESCENDING { \
    union { unsigned char EB_CHAR8;  unsigned char EB_CHAR8(); }; \
    union { unsigned char EB_CHAR7;  unsigned char EB_CHAR7(); }; \
    union { unsigned char EB_CHAR6;  unsigned char EB_CHAR6(); }; \
    union { unsigned char EB_CHAR5;  unsigned char EB_CHAR5(); }; \
    union { unsigned char EB_CHAR4;  unsigned char EB_CHAR4(); }; \
    union { unsigned char EB_CHAR3;  unsigned char EB_CHAR3(); }; \
    union { unsigned char EB_CHAR2;  unsigned char EB_CHAR2(); }; \
    union { unsigned char EB_CHAR1;  unsigned char EB_CHAR1(); }; \
  }
 #endif

 #define ENDIANBYTES_UNION_ASCENDING { \
    struct ENDIANBYTES_STRUCT_ASCENDING; \
    void *word; \
 }
 #define ENDIANBYTES_UNION_DESCENDING { \
    struct ENDIANBYTES_STRUCT_DESCENDING; \
    void *word; \
 }

#endif
