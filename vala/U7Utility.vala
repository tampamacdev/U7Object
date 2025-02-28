public class U7Utility {
    public static string? getStringFromDictionaryForKey(U7Object? obj, string? key) {
        if (obj == null || key == null) {
            return null;
        }
        var dict = obj as U7Dictionary;
        if ((dict != null) && dict.value.has_key(key)) {
            var value = dict.value[key];
            var strValue = value as U7String;
            if (strValue != null) {
                return strValue.value;
            }
        }
        return null;
    }

    public static string get_type_name<T>(T instance) {
        return typeof(T).name();
    }
    
    
    // Add more convenience methods here as needed
}