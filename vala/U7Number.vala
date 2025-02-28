public class U7Number : U7PropertyList {
    public enum NumberType {
        INT,
        DOUBLE,
        BOOL
    }

    private NumberType num_type;
    private int int_value;
    private double double_value;
    private bool bool_value;

    // Constructors for each type
    public U7Number.from_int(int value) {
        Object();
        this.num_type = NumberType.INT;
        this.int_value = value;
    }

    public U7Number.from_double(double value) {
        Object();
        this.num_type = NumberType.DOUBLE;
        this.double_value = value;
    }

    public U7Number.from_bool(bool value) {
        Object();
        this.num_type = NumberType.BOOL;
        this.bool_value = value;
    }

    // Getter for the type (renamed from 'type' to 'number_type')
    public NumberType number_type {
        get { return num_type; }
    }

    // Getters with casting based on stored type
    public int as_int() {
        switch (num_type) {
            case NumberType.INT:
                return int_value;
            case NumberType.DOUBLE:
                return (int)double_value;  // Cast double to int (truncates)
            case NumberType.BOOL:
                return bool_value ? 1 : 0;  // Convert bool to int (true=1, false=0)
            default:
                assert_not_reached();
        }
    }

    public double as_double() {
        switch (num_type) {
            case NumberType.INT:
                return (double)int_value;  // Cast int to double
            case NumberType.DOUBLE:
                return double_value;
            case NumberType.BOOL:
                return bool_value ? 1.0 : 0.0;  // Convert bool to double
            default:
                assert_not_reached();
        }
    }

    public bool as_bool() {
        switch (num_type) {
            case NumberType.INT:
                return int_value != 0;  // Non-zero int is true
            case NumberType.DOUBLE:
                return double_value != 0.0;  // Non-zero double is true
            case NumberType.BOOL:
                return bool_value;
            default:
                assert_not_reached();
        }
    }

    public override U7PropertyList deep_copy() {
        switch (num_type) {
            case NumberType.INT:
                return new U7Number.from_int(this.int_value);
            case NumberType.DOUBLE:
                return new U7Number.from_double(this.double_value);
            case NumberType.BOOL:
                return new U7Number.from_bool(this.bool_value);
            default:
                assert_not_reached();
        }
    }


	public override Json.Node to_json() {
        switch (num_type) {
            case NumberType.INT: return new Json.Node.alloc().init_int(this.int_value);
            case NumberType.DOUBLE: return new Json.Node.alloc().init_double(this.double_value);
            case NumberType.BOOL: return new Json.Node.alloc().init_boolean(this.bool_value);
            default: assert_not_reached();
        }
    }

}