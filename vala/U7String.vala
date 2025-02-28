public class U7String : U7PropertyList {
    public string value { get; construct; }

    public U7String(string value) {
		
		Object(value: value);

    }

    public override U7PropertyList deep_copy() {
        return new U7String(this.value);
    }

    public override string to_string() {
        return value;
    }

	public override Json.Node to_json() {
        return new Json.Node.alloc().init_string(this.value);
    }


    
}