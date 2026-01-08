#include <gtk/gtk.h>
#include "engine.c"

static GtkWidget *label_status;
static GtkWidget *progress_bar;

// Callback for the "Optimize Now" button
static void on_optimize_clicked(GtkWidget *widget, gpointer data) {
    gtk_label_set_text(GTK_LABEL(label_status), "Status: Optimizing...");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 0.3);
    
    while (gtk_events_pending()) gtk_main_iteration();
    
    clear_cache();
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 0.6);
    while (gtk_events_pending()) gtk_main_iteration();
    
    optimize_memory();
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 0.8);
    while (gtk_events_pending()) gtk_main_iteration();
    
    clean_temp_files();
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 1.0);
    
    double usage = get_memory_usage();
    char status[100];
    snprintf(status, sizeof(status), "Status: Optimization Complete! (RAM Usage: %.1f%%)", usage);
    gtk_label_set_text(GTK_LABEL(label_status), status);
}

// Custom CSS for Kali-like dark theme
static void apply_css(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    const char *css = 
        "window { background-color: #0f0f0f; color: #ffffff; }"
        "button { background-color: #1a1a1a; color: #00ff00; border: 1px solid #00ff00; border-radius: 0; padding: 10px; font-family: 'Monospace'; }"
        "button:hover { background-color: #00ff00; color: #000000; }"
        "label { color: #00ff00; font-family: 'Monospace'; font-size: 14px; }"
        "progressbar trough { background-color: #1a1a1a; border: 1px solid #00ff00; }"
        "progressbar progress { background-color: #00ff00; }";
    
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    apply_css();

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "BlazeNeuro Optimizer");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *label_title = gtk_label_new("BLAZENEURO SYSTEM OPTIMIZER");
    gtk_label_set_markup(GTK_LABEL(label_title), "<span font='18' weight='bold'>BLAZENEURO OPTIMIZER</span>");
    gtk_box_pack_start(GTK_BOX(vbox), label_title, FALSE, FALSE, 0);

    double usage = get_memory_usage();
    char status[100];
    snprintf(status, sizeof(status), "Status: Ready (RAM Usage: %.1f%%)", usage);
    label_status = gtk_label_new(status);
    gtk_box_pack_start(GTK_BOX(vbox), label_status, FALSE, FALSE, 0);

    progress_bar = gtk_progress_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), progress_bar, FALSE, FALSE, 0);

    GtkWidget *btn_optimize = gtk_button_new_with_label("RUN OPTIMIZATION");
    g_signal_connect(btn_optimize, "clicked", G_CALLBACK(on_optimize_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), btn_optimize, FALSE, FALSE, 0);

    GtkWidget *label_footer = gtk_label_new("v1.0.0 | Built for BlazeNeuro OS");
    gtk_box_pack_end(GTK_BOX(vbox), label_footer, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
