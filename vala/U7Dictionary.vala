public class U7Dictionary : U7PropertyList {
    public Gee.HashMap<string, U7PropertyList> value { get; construct; }

    public U7Dictionary(Gee.HashMap<string, U7PropertyList>? value = null) {
        var map = value ?? new Gee.HashMap<string, U7PropertyList>();
        Object(value: map);
    }

    public override U7PropertyList deep_copy() {
        var copy = new Gee.HashMap<string, U7PropertyList>();
        foreach (var key in this.value.keys) {
            copy[key] = this.value[key].deep_copy();
        }
        return new U7Dictionary(copy);
    }

	public override Json.Node to_json() {
        var builder = new Json.Builder();
        builder.begin_object();
        foreach (var key in this.value.keys) {
            builder.set_member_name(key);
            builder.add_value(this.value[key].to_json());
        }
        builder.end_object();
        return builder.get_root();
    }

    public void add_pairs(string first_key, U7PropertyList first_value, ...) {
        // Add the first pair explicitly
        this.value.set(first_key, first_value);

        // Process the remaining pairs from the va_list
        va_list args = va_list();
        while (true) {
            // Get the next key (string)
            string? key = args.arg<string?>();
            if (key == null) {
                break; // Null sentinel ends the list
            }

            // Get the next value (U7PropertyList)
            U7PropertyList? value = args.arg<U7PropertyList?>();
            if (value == null) {
                GLib.warning("Missing value for key '%s' in add_pairs", key);
                break;
            }

            // Add the pair to the dictionary
            this.value.set(key, value);
        }
    }

    public static U7Dictionary with_pairs(string first_key, U7PropertyList first_value, ...) {
        var map = new Gee.HashMap<string, U7PropertyList>();
        map.set(first_key, first_value); // Add the first pair

        va_list args = va_list();
        while (true) {
            string? key = args.arg<string?>();
            if (key == null) {
                break; // Null sentinel ends the list
            }
            U7PropertyList? value = args.arg<U7PropertyList?>();
            if (value == null) {
                GLib.warning("Missing value for key '%s' in with_pairs", key);
                break;
            }
            map.set(key, value);
        }

        return new U7Dictionary(map);
    }


}