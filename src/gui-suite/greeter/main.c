#include <gtk/gtk.h>

static void on_login_clicked(GtkWidget *widget, gpointer data) {
    // In a real greeter, this would interface with PAM
    g_print("Login attempt for BlazeNeuro...\n");
}

static void apply_greeter_css(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    const char *css = 
        "window { background-image: url('/usr/share/backgrounds/blazeneuro/wallpaper.png'); background-size: cover; }"
        ".login-box { background-color: rgba(15, 15, 15, 0.85); border: 2px solid #00ff00; padding: 40px; border-radius: 0; }"
        "entry { background-color: #1a1a1a; color: #00ff00; border: 1px solid #00ff00; caret-color: #00ff00; padding: 10px; font-family: 'Monospace'; }"
        "button { background-color: #00ff00; color: #000000; border: none; padding: 12px; font-weight: bold; font-family: 'Monospace'; }"
        "button:hover { background-color: #00cc00; }"
        "label { color: #00ff00; font-family: 'Monospace'; }";
    
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    apply_greeter_css();

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "BlazeNeuro Login");
    gtk_window_fullscreen(GTK_WINDOW(window));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *overlay = gtk_overlay_new();
    gtk_container_add(GTK_CONTAINER(window), overlay);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);
    gtk_style_context_add_class(gtk_widget_get_style_context(vbox), "login-box");
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), vbox);

    GtkWidget *label_title = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_title), "<span font='24' weight='bold'>BLAZENEURO OS</span>");
    gtk_box_pack_start(GTK_BOX(vbox), label_title, FALSE, FALSE, 0);

    GtkWidget *entry_user = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_user), "Username");
    gtk_box_pack_start(GTK_BOX(vbox), entry_user, FALSE, FALSE, 0);

    GtkWidget *entry_pass = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_pass), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(entry_pass), FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), entry_pass, FALSE, FALSE, 0);

    GtkWidget *btn_login = gtk_button_new_with_label("ACCESS SYSTEM");
    g_signal_connect(btn_login, "clicked", G_CALLBACK(on_login_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), btn_login, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
