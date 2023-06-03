#include <gtk/gtk.h>

// Функция, выполняющая расчеты.
int calculate(int a, int b, char op) {
    int res;
    switch (op) {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            res = a / b;
            break;
        default:
            res = 0;
            break;
    }
    return res;
}

// Функция-обработчик события нажатия на кнопку.
void on_button_clicked(GtkWidget *widget, gpointer data) {
    // Получаем данные из полей ввода.
    GtkWidget *entry1 = (GtkWidget*)data;
    GtkWidget *entry2 = g_object_get_data(G_OBJECT(widget), "entry2");
    GtkWidget *combo = g_object_get_data(G_OBJECT(widget), "combo");
    const char *s1 = gtk_entry_get_text(GTK_ENTRY(entry1));
    const char *s2 = gtk_entry_get_text(GTK_ENTRY(entry2));
    const char *sop = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
    int a = atoi(s1);
    int b = atoi(s2);
    char op = sop[0];

    // Выполняем расчеты.
    int res = calculate(a, b, op);

    // Отображаем результат.
    GtkWidget *label = g_object_get_data(G_OBJECT(widget), "label");
    char buf[256];
    sprintf(buf, "%d %c %d = %d", a, op, b, res);
    gtk_label_set_text(GTK_LABEL(label), buf);
}

// Главная функция.
int main(int argc, char *argv[]) {
    // Инициализируем GTK.
    gtk_init(&argc, &argv);

    // Создаем графический интерфейс.
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Калькулятор");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *entry1 = gtk_entry_new();
    GtkWidget *entry2 = gtk_entry_new();
    GtkWidget *combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "+");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "-");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "*");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "/");
    GtkWidget *button = gtk_button_new_with_label("=");
    GtkWidget *label = gtk_label_new("");

    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box1), 10);
    gtk_box_pack_start(GTK_BOX(box1), entry1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box1), combo, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box1), entry2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box1), button, TRUE, TRUE, 0);

    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box2), 10);
    gtk_box_pack_start(GTK_BOX(box2), box1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box2), label, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), box2);

    // Разделяем логику и интерфейс.
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_clicked), entry1);
    g_object_set_data(G_OBJECT(button), "entry2", entry2);
    g_object_set_data(G_OBJECT(button), "combo", combo);
    g_object_set_data(G_OBJECT(button), "label", label);

    // Запускаем главный цикл обработки событий.
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}