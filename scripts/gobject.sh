#!/bin/bash

# Check if the correct number of arguments are provided
if [ "$#" -ne 3 ]; then
    #               $1     $2           $3                
    echo "Usage: $0 prefix parent_camel name_camel"
    exit 1
fi

# Full path to the executing script
SCRIPT_PATH=$(readlink -f "$0")
# Directory where the script resides
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")


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

pn="$prefix$name"

header_filename="${pn}.h"
source_filename="${pn}.c"

echo "<<<<<<<<<<<<<<<<gobject build>>>>>>>>>>>>>>"
echo "prefix=$prefix"
echo "name=$name"
echo "name_camel=$name_camel"
echo "parent_camel=$parent_camel"
echo "parent_lowercase=$parent_lowercase"
echo "prefix_parent=$prefix_parent"
echo "PREFIX_PARENT=$PREFIX_PARENT"
echo "ClassName=$ClassName"
echo "ParentClassName=$ParentClassName"
echo "header_filename=$header_filename"
echo "source_filename=$source_filename"



if [ -f $header_filename ]; then
    echo "header already exists!!!"
    exit 1
fi

if [ -f $source_filename ]; then
    echo "source already exists!!!"
    exit 1
fi



$SCRIPT_DIR/gobject_header.sh $1 $2 $3
$SCRIPT_DIR/gobject_source.sh $1 $2 $3


$SCRIPT_DIR/gobject_header.sh $1 $2 $3 > $header_filename
$SCRIPT_DIR/gobject_source.sh $1 $2 $3 > $source_filename



echo "Don't forget to add ${ClassName}Type to U7ObjectSubclassType enum in u7object.h"