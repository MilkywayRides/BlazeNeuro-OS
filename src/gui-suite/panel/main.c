#include <gtk/gtk.h>
#include <time.h>

static GtkWidget *label_clock;

static gboolean update_clock(gpointer data) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s, sizeof(s), "%H:%M:%S", tm);
    gtk_label_set_text(GTK_LABEL(label_clock), s);
    return TRUE;
}

static void apply_panel_css(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    const char *css = 
        "window { background-color: #0f0f0f; border-bottom: 1px solid #00ff00; }"
        "label { color: #00ff00; font-family: 'Monospace'; font-weight: bold; padding: 0 10px; }"
        "button { background: none; border: none; color: #00ff00; font-family: 'Monospace'; }"
        "button:hover { background-color: #1a1a1a; }";
    
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    apply_panel_css();

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DOCK);
    gtk_window_set_title(GTK_WINDOW(window), "BlazeNeuro Panel");
    
    // Position at top
    GdkDisplay *display = gdk_display_get_default();
    GdkMonitor *monitor = gdk_display_get_primary_monitor(display);
    GdkRectangle geometry;
    gdk_monitor_get_geometry(monitor, &geometry);
    gtk_window_set_default_size(GTK_WINDOW(window), geometry.width, 30);
    gtk_window_move(GTK_WINDOW(window), 0, 0);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    GtkWidget *btn_menu = gtk_button_new_with_label(" [ BLAZENEURO ] ");
    gtk_box_pack_start(GTK_BOX(hbox), btn_menu, FALSE, FALSE, 0);

    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox), spacer, TRUE, TRUE, 0);

    label_clock = gtk_label_new("");
    gtk_box_pack_end(GTK_BOX(hbox), label_clock, FALSE, FALSE, 0);
    g_timeout_add_seconds(1, update_clock, NULL);
    update_clock(NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
