run parse_iana_registery.sh to run node tool "csv-to-port-dictionary.js" to parse iana csv registery files.



For example on macOS:

Download the csv file:
 
    https://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xhtml

Parse the file and output json file "iana.json" with:
    
    ./parse_iana_registery.sh ~/Downloads/service-names-port-numbers.csv > iana.json

Generate a static website for local documentation viewing of a IANA breakdown of port registration with:

    ./iana-breakdown.js

The node tool "iana-breakdown.js" will generate a static website in the directory named "iana_breakdown" in the current working directory. You can use the contents "iana_breakdown" to update the documentation found in the subdirectory docs.




