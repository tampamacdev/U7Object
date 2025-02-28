public class U7Array : U7PropertyList {
    public Gee.ArrayList<U7PropertyList> value { get; construct; }

    public U7Array(Gee.ArrayList<U7PropertyList>? value = null) {
        var list = value ?? new Gee.ArrayList<U7PropertyList>();
        Object(value: list); 
    }

    public override U7PropertyList deep_copy() {
        var copy = new Gee.ArrayList<U7PropertyList>();
        foreach (var item in this.value) {
            copy.add(item.deep_copy());
        }
        return new U7Array(copy);
    }

	public override Json.Node to_json() {
        var builder = new Json.Builder();
        builder.begin_array();
        foreach (var item in this.value) {
            builder.add_value(item.to_json());
        }
        builder.end_array();
        return builder.get_root();
    }

}