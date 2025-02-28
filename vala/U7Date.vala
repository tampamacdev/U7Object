public class U7Date : U7PropertyList {
    public GLib.DateTime value { get; construct; }

    public U7Date(GLib.DateTime value) {
        Object(value: value);
    }

    public override U7PropertyList deep_copy() {
        return new U7Date(new GLib.DateTime.from_unix_utc(this.value.to_unix()));
    }

	public override Json.Node to_json() {
        return new Json.Node.alloc().init_string(this.value.format("%Y-%m-%dT%H:%M:%SZ"));
    }

}

