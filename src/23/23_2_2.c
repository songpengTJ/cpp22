#include <gtk-2.0/gtk/gtk.h>
static GtkWidget *window = NULL;
static GdkPixmap *pixmap = NULL;

static gboolean scribble_configure_event(GtkWidget *widget,
		GdkEventConfigure *event, gpointer data) {
	if (pixmap)
		g_object_unref(pixmap);

	pixmap = gdk_pixmap_new(widget->window, widget->allocation.width,
			widget->allocation.height, -1);

	gdk_draw_rectangle(pixmap, widget->style->white_gc, TRUE, 0, 0,
			widget->allocation.width, widget->allocation.height);

	return TRUE;
}

static gboolean scribble_expose_event(GtkWidget *widget, GdkEventExpose *event,
		gpointer data) {

	gdk_draw_drawable(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(
			widget)], pixmap,

	event->area.x, event->area.y, event->area.x, event->area.y,
			event->area.width, event->area.height);

	return FALSE;
}

static void draw_brush(GtkWidget *widget, gdouble x, gdouble y) {
	GdkRectangle update_rect;

	update_rect.x = x - 3;
	update_rect.y = y - 3;
	update_rect.width = 6;
	update_rect.height = 6;

	gdk_draw_rectangle(pixmap, widget->style->black_gc, TRUE, update_rect.x,
			update_rect.y, update_rect.width, update_rect.height);

	gdk_window_invalidate_rect(widget->window, &update_rect, FALSE);
}

static gboolean scribble_button_press_event(GtkWidget *widget,
		GdkEventButton *event, gpointer data) {
	if (pixmap == NULL)
		return FALSE;

	if (event->button == 1)
		draw_brush(widget, event->x, event->y);

	return TRUE;
}

static gboolean scribble_motion_notify_event(GtkWidget *widget,
		GdkEventMotion *event, gpointer data) {
	int x, y;
	GdkModifierType state;

	if (pixmap == NULL)
		return FALSE;

	gdk_window_get_pointer(event->window, &x, &y, &state);

	if (state & GDK_BUTTON1_MASK)
		draw_brush(widget, x, y);

	return TRUE;
}

static gboolean checkerboard_expose(GtkWidget *da, GdkEventExpose *event,
		gpointer data) {
	gint i, j, xcount, ycount;
	GdkGC *gc1, *gc2;
	GdkColor color;

#define CHECK_SIZE 10
#define SPACING 2

	gc1 = gdk_gc_new(da->window);
	color.red = 30000;
	color.green = 0;
	color.blue = 30000;
	gdk_gc_set_rgb_fg_color(gc1, &color);

	gc2 = gdk_gc_new(da->window);
	color.red = 65535;
	color.green = 65535;
	color.blue = 65535;
	gdk_gc_set_rgb_fg_color(gc2, &color);

	xcount = 0;
	i = SPACING;
	while (i < da->allocation.width) {
		j = SPACING;
		ycount = xcount % 2;
		while (j < da->allocation.height) {
			GdkGC *gc;

			if (ycount % 2)
				gc = gc1;
			else
				gc = gc2;

			gdk_draw_rectangle(da->window, gc, TRUE, i, j, CHECK_SIZE,
			CHECK_SIZE);

			j += CHECK_SIZE + SPACING;
			++ycount;
		}

		i += CHECK_SIZE + SPACING;
		++xcount;
	}

	g_object_unref(gc1);
	g_object_unref(gc2);

	return TRUE;
}

static void close_window(void) {
	window = NULL;

	if (pixmap)
		g_object_unref(pixmap);
	pixmap = NULL;
}


int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWidget *frame;
	GtkWidget *vbox;
	GtkWidget *da;
	GtkWidget *label;

	if (!window) {
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

		gtk_window_set_title(GTK_WINDOW(window), "绘图区测试");

		g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);

		gtk_container_set_border_width(GTK_CONTAINER(window), 8);

		vbox = gtk_vbox_new(FALSE, 8);
		gtk_container_set_border_width(GTK_CONTAINER(vbox), 8);
		gtk_container_add(GTK_CONTAINER(window), vbox);

		label = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label), "<u>方格图案</u>");
		gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

		frame = gtk_frame_new(NULL);
		gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
		gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 0);

		da = gtk_drawing_area_new();

		gtk_widget_set_size_request(da, 100, 100);

		gtk_container_add(GTK_CONTAINER(frame), da);

		g_signal_connect(da, "expose-event", G_CALLBACK(checkerboard_expose),
				NULL);

		label = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(label), "<u>手绘区</u>");
		gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

		frame = gtk_frame_new(NULL);
		gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
		gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 0);

		da = gtk_drawing_area_new();

		gtk_widget_set_size_request(da, 100, 100);

		gtk_container_add(GTK_CONTAINER(frame), da);

		g_signal_connect(da, "expose-event", G_CALLBACK(scribble_expose_event),
				NULL);
		g_signal_connect(da, "configure-event", G_CALLBACK(
				scribble_configure_event), NULL);

		g_signal_connect(da, "motion-notify-event", G_CALLBACK(
				scribble_motion_notify_event), NULL);
		g_signal_connect(da, "button-press-event", G_CALLBACK(
				scribble_button_press_event), NULL);

		gtk_widget_set_events(da, gtk_widget_get_events(da)
				| GDK_LEAVE_NOTIFY_MASK | GDK_BUTTON_PRESS_MASK
				| GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);
	}

	if (!GTK_WIDGET_VISIBLE(window))
		gtk_widget_show_all(window);
	else
		gtk_widget_destroy(window);
	gtk_main();
	return 0;
}
