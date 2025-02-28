public class U7Data : U7PropertyList {
    public GLib.Bytes value { get; construct; }

    public U7Data(GLib.Bytes value) {
        Object(value: value);
    }

    public override U7PropertyList deep_copy() {
        // Use get_data() to get the uint8[] array, then create a new Bytes object
        return new U7Data(new GLib.Bytes(this.value.get_data()));
    }

	public override Json.Node to_json() {
        var base64 = GLib.Base64.encode(this.value.get_data());
        return new Json.Node.alloc().init_string(base64);
    }

}