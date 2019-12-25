﻿#ifndef PPX_BASE_CONSTRUCTOR_MAGIC_H__
#define PPX_BASE_CONSTRUCTOR_MAGIC_H__

// Put this in the declarations for a class to be uncopyable.
#define PPX_DISALLOW_COPY(TypeName) TypeName(const TypeName &) = delete

// Put this in the declarations for a class to be unassignable.
#define PPX_DISALLOW_ASSIGN(TypeName) void operator=(const TypeName &) = delete

// A macro to disallow the copy constructor and operator= functions. This should
// be used in the declarations for a class.
#define PPX_DISALLOW_COPY_AND_ASSIGN(TypeName)                                                     \
  TypeName(const TypeName &) = delete;                                                             \
  PPX_DISALLOW_ASSIGN(TypeName)

// A macro to disallow all the implicit constructors, namely the default
// constructor, copy constructor and operator= functions.
//
// This should be used in the declarations for a class that wants to prevent
// anyone from instantiating it. This is especially useful for classes
// containing only static methods.
#define PPX_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName)                                               \
  TypeName() = delete;                                                                             \
  PPX_DISALLOW_COPY_AND_ASSIGN(TypeName)

#endif // ! PPX_BASE_CONSTRUCTOR_MAGIC_H__
