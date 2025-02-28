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
name_uppercase=$(echo "$name_camel" | tr '[:lower:]' '[:upper:]')

prefix_name_lowercase=${prefix}_${name}

prefix_upper=$(echo "$prefix" | tr '[:lower:]' '[:upper:]')

#     G_BEGIN_DECLS
#     
#     #define U7_TYPE_ARRAY (u7_array_get_type())
#     
#     G_DECLARE_FINAL_TYPE(U7Array, u7_array, U7, ARRAY, GObject)
#     
#     extern U7Array *u7_array_new(void);
#     extern void u7_array_test(void);
#     G_END_DECLS



# Output the header file content to standard output
cat <<EOF
#pragma once
#include "u7glib.h"

G_BEGIN_DECLS

#define ${prefix_upper}_TYPE_${name_uppercase} (${prefix}_${name}_get_type())

#define ${prefix_upper}Is${name_camel}(n) g_type_check_instance_is_a((GTypeInstance*)n, ${prefix_upper}_TYPE_${name_uppercase})

G_DECLARE_FINAL_TYPE(${prefix_upper}${name_camel}, ${prefix}_${name}, ${prefix_upper}, ${name_uppercase}, ${ParentClassName})

extern ${prefix_upper}${name_camel} *${prefix}_${name}_new(void);
extern void ${prefix}_${name}_test(void);

G_END_DECLS
EOF