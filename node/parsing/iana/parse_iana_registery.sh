#!/bin/bash

# Check if node_modules directory exists in the current working directory
if [ ! -d "node_modules" ]; then
    echo "node_modules not found. Installing csv-parse..." >&2
    # Run npm install to fetch csv-parse locally
    npm install csv-parse
    npm install filesize
    
    if [ $? -eq 0 ]; then
        echo "csv-parse installed successfully." >&2
    else
        echo "Error: Failed to install csv-parse. Check npm logs or network."
        exit 1
    fi
else
    echo "node_modules already exists. Skipping npm install." >&2
fi

./csv-to-port-dictionary.js $1