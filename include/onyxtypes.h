#ifndef ONYXTYPES_H
#define ONYXTYPES_H

#include "bh.h"

enum BasicKind {
    Basic_Kind_Void,

    Basic_Kind_Bool,

    Basic_Kind_I8,
    Basic_Kind_U8,
    Basic_Kind_I16,
    Basic_Kind_U16,
    Basic_Kind_I32,
    Basic_Kind_U32,
    Basic_Kind_I64,
    Basic_Kind_U64,

    Basic_Kind_F32,
    Basic_Kind_F64,

    Basic_Kind_Rawptr,
};

enum BasicFlag {
    Basic_Flag_Boolean          = BH_BIT(0),
    Basic_Flag_Integer          = BH_BIT(1),
    Basic_Flag_Unsigned         = BH_BIT(2),
    Basic_Flag_Float            = BH_BIT(3),
    Basic_Flag_Pointer          = BH_BIT(4),

    Basic_Flag_Numeric          = Basic_Flag_Integer | Basic_Flag_Float,
    Basic_Flag_Ordered          = Basic_Flag_Integer | Basic_Flag_Float | Basic_Flag_Pointer,
    Basic_Flag_Constant_Type    = Basic_Flag_Boolean | Basic_Flag_Numeric | Basic_Flag_Pointer,
    Basic_Flag_Numeric_Ordered  = Basic_Flag_Numeric | Basic_Flag_Ordered,
};

typedef struct TypeBasic {
    enum BasicKind kind;
    u32 flags;
    i64 size; // NOTE: In bytes
    const char* name;
} TypeBasic;

// NOTE: Forward declaration for some of the types below
typedef struct Type Type;

#define TYPE_KINDS \
    TYPE_KIND(Basic, TypeBasic)                                 \
    TYPE_KIND(Pointer, struct { TypeBasic base; Type *elem; })  \
    TYPE_KIND(Function, struct { Type *return_type; u64 param_count; Type* params[]; })

typedef enum TypeKind {
    Type_Kind_Invalid,

#define TYPE_KIND(k, ...) Type_Kind_##k,
    TYPE_KINDS
#undef TYPE_KIND

    Type_Kind_Count,
} TypeKind;

#define TYPE_KIND(k, ...) typedef __VA_ARGS__ Type ## k;
    TYPE_KINDS
#undef TYPE_KIND

enum TypeFlag {
    Type_Flag_Default
};

struct Type {
    TypeKind kind;

    u32 flags;

    union {
#define TYPE_KIND(k, ...) Type##k k;
        TYPE_KINDS
#undef TYPE_KIND
    };
};

extern Type basic_types[];

struct AstType;
b32 types_are_compatible(Type* t1, Type* t2);
Type* type_build_from_ast(bh_allocator alloc, struct AstType* type_node);
const char* type_get_name(Type* type);

b32 type_is_pointer(Type* type);
b32 type_is_bool(Type* type);

#endif // #ifndef ONYX_TYPES
