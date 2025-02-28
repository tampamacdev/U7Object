[CCode (cheader_filename = "u7_notification_center.h")]
public class U7NotificationCenter : GLib.Object {
    [CCode (cname = "u7_notification_center_new")]
    public U7NotificationCenter();

    [CCode (cname = "u7_notification_center_subscribe")]
    public void subscribe(string name, U7Object observer);

    [CCode (cname = "u7_notification_center_publish")]
    public void publish(string name, U7Dictionary item);

    [CCode (cname = "u7_notification_center_default")]
    public static unowned U7NotificationCenter default();

    [CCode (cname = "u7_notification_center_registerThreadDispatcher")]
    public static void registerThreadDispatcher(U7Object dispatcher);


}

