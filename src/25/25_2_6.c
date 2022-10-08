void user_function(GtkTextView *text_view,
                  GtkDeleteType type,
                  gint count,
                  gpointer user_data);		// 连接delete-from-cursor信号
void user_function(GtkTextView *textview,
                  gchar *arg1,
                  gpointer user_data); 		// 连接insert-at-cursor信号
void user_function(GtkTextView *text_view,
                  GtkMovementStep step,
                  gint count,
                  gboolean extend_selection,
                  gpointer user_data); 		// 连接move-cursor信号
void user_function(GtkTextView *text_view,
                  GtkScrollStep step,
                  gint count,
                  gpointer user_data); 		// 连接move-viewport信号
void user_function(GtkTextView *textview,
                  GtkMenu *arg1,
                  gpointer user_data); 		// 连接populate-popup信号
void user_function(GtkTextView *text_view,
                  gboolean select,
                  gpointer user_data); 		// 连接select-all信号
void user_function(GtkTextView *textview,
                  GtkAdjustment *arg1,
                  GtkAdjustment *arg2,
                  gpointer user_data); 	// 连接set-scroll-adjustments信号
