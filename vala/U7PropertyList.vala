public abstract class U7PropertyList : U7Object {


    protected U7PropertyList() {
        base();
    }

    construct {


    }

    public abstract U7PropertyList deep_copy();
    public abstract Json.Node to_json();

    public static U7PropertyList parse_json_string(string json_string) throws U7Error {
        if (json_string == null || json_string.length == 0) {
            throw new U7Error.INVALID_FORMAT("Empty or null JSON string");
        }

        try {
            var parser = new Json.Parser();
            parser.load_from_data(json_string, -1);
            
            var root = parser.get_root();
            if (root == null) {
                throw new U7Error.INVALID_FORMAT("Invalid JSON: could not get root node");
            }
            
            return U7PropertyList.from_json(root);
        } catch (Error e) {
            throw new U7Error.INVALID_FORMAT("Failed to parse JSON: %s", e.message);
        }
    }

    public static U7PropertyList from_json(Json.Node node) throws U7Error {
        switch (node.get_node_type()) {
            case Json.NodeType.VALUE:
                if (node.get_value_type() == typeof(string)) {
                    return new U7String(node.get_string());
                } else if (node.get_value_type() == typeof(int64)) {
                    return new U7Number.from_int((int)node.get_int());
                } else if (node.get_value_type() == typeof(double)) {
                    return new U7Number.from_double(node.get_double());
                } else if (node.get_value_type() == typeof(bool)) {
                    return new U7Number.from_bool(node.get_boolean());
                } else if (node.get_value_type() == typeof(void)) {
                    throw new U7Error.INVALID_FORMAT("Null JSON value not supported");
                }
                break;
            case Json.NodeType.ARRAY:
                var array = new Gee.ArrayList<U7PropertyList>();
                node.get_array().foreach_element((_, __, element) => {
                    try {
                        array.add(from_json(element));
                    } catch (U7Error e) {
                        // Ignore malformed elements for simplicity
                    }
                });
                return new U7Array(array);
            case Json.NodeType.OBJECT:
                var map = new Gee.HashMap<string, U7PropertyList>();
                node.get_object().foreach_member((obj, key, value) => {
                    try {
                        map[key] = from_json(value);
                    } catch (U7Error e) {
                        // Ignore malformed values
                    }
                });
                return new U7Dictionary(map);
            default:
                throw new U7Error.INVALID_FORMAT("Unknown JSON node type");
        }
        throw new U7Error.INVALID_FORMAT("Unsupported JSON value type");
    }

    public string to_json_string() {

        var json_node = this.to_json();
        var generator = new Json.Generator();
        generator.set_pretty(true);
        generator.set_root(json_node);
        return generator.to_data(null);

    }


    public static U7Dictionary test_dictionary() {

        U7Dictionary dict = new U7Dictionary();
        dict.value["array"] = new U7Array();
        ((U7Array)dict.value["array"]).value.add(new U7Number.from_int(1));
        ((U7Array)dict.value["array"]).value.add(new U7Number.from_int(2));

        dict.value["string"] = new U7String("Hello, world!");
        dict.value["number_double"] = new U7Number.from_double(42.5);  // Double
        dict.value["number_int"] = new U7Number.from_int(42);          // Int
        dict.value["number_bool"] = new U7Number.from_bool(true);      // Bool
        dict.value["dictionary"] = new U7Dictionary();
        ((U7Dictionary)dict.value["dictionary"]).value["key"] = new U7String("nested");
        dict.value["date"] = new U7Date(new GLib.DateTime.now_local());
        dict.value["data"] = new U7Data(new GLib.Bytes("binary data".data));

        return dict;

    }
}