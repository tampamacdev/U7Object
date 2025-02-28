#!/bin/bash

# Check if the correct number of arguments are provided
if [ "$#" -ne 3 ]; then
    #               $1     $2           $3                
    echo "Usage: $0 prefix parent_camel name_camel"

    exit 1
fi

# Assign input arguments to variables
prefix="$1"
parent_camel="$2"
name_camel=$3

PREFIX=$(echo "$prefix" | tr '[:lower:]' '[:upper:]')
ClassName=$PREFIX$name_camel

name=$(echo "$name_camel" | tr '[:upper:]' '[:lower:]')
parent_lowercase=$(echo "$parent_camel" | tr '[:upper:]' '[:lower:]')
prefix_parent=${prefix}_$parent_lowercase
PREFIX_PARENT=$(echo "$prefix_parent" | tr '[:lower:]' '[:upper:]')

ParentClassName=$PREFIX$parent_camel


# Generate lowercase version of the name
NN=$(echo "$name" | tr '[:lower:]' '[:upper:]')
PP=$(echo "$prefix" | tr '[:lower:]' '[:upper:]')

pn="$prefix$name"
p_n="${prefix}_${name}"
ClassNameClass="${ClassName}Class"
PP_NN_CC="${PP}_${NN}_CLASS"

#     #include "u7array.h"
#     
#     struct _U7Array {
#         GObject parent_instance;
#     };
#     
#     struct _U7ArrayClass {
#         GObjectClass parent_class;
#     };
#     
#     G_DEFINE_TYPE(U7Array, u7_array, G_TYPE_OBJECT)
#     
#     static void u7_array_dispose(GObject *object) {
#         printf("u7_array_dispose\n");
#     }
#     
#     static void u7_array_class_init(U7ArrayClass *klass) {
#         // Class initialization logic, if needed
#         GObjectClass *object_class = G_OBJECT_CLASS(klass);
#         object_class->dispose = u7_array_dispose;
#     }
#     
#     static void u7_array_init(U7Array *self) {
#         printf("u7_array_init\n");
#     }
#     
#     U7Array *u7_array_new(void) {
#         U7Array *self = g_object_new(U7_TYPE_ARRAY, NULL);
#         return self;
#     }
#     void u7_array_test(void) {
#     
#         U7Array *array = u7_array_new();
#  
#         U7Release(array);
#         printf("u7_array_test()|array %p\n", array);
#     
#     }
#     


# Output .c file content to standard output
# prefix prefix_upper name_uppercase name_lowercase name_camel parent class

cat <<EOF
#include "${pn}.h"

struct _${ClassName} {
    ${ParentClassName} parent_instance;
};

struct _${ClassNameClass} {
    ${ParentClassName}Class parent_class;
};

G_DEFINE_TYPE(${ClassName}, ${p_n}, ${PP}_TYPE_OBJECT)

static void ${p_n}_dispose(GObject *object) {
    printf("${p_n}_dispose\n");

    G_OBJECT_CLASS(${p_n}_parent_class)->dispose(object);

}

static char *${p_n}_description(U7Object *obj) {
    if (U7Is${name_camel}(obj)) 
        return "${p_n}_description need to implement";
    return "${p_n}_description";
}

static void ${p_n}_class_init(${ClassNameClass} *klass) {
    // Class initialization logic, if needed
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = ${p_n}_dispose;

    ${ParentClassName}Class *u7_object_class = ${PREFIX_PARENT}_CLASS(klass);
    u7_object_class->description = ${p_n}_description;

}

static void ${p_n}_init(${ClassName} *self) {
    u7_object_set_subclass_type(${PREFIX_PARENT}(self), ${ClassName}Type);

    printf("${p_n}_init\n");
}

${ClassName} *${p_n}_new(void) {
    ${ClassName} *self = g_object_new(${PP}_TYPE_${NN}, NULL);
    return self;
}

void ${p_n}_test(void) {

    ${ClassName} *${name} = ${p_n}_new();
    printf("${p_n}_test()|${name} %p\n", ${name});
    U7Release(${name});

}


EOF