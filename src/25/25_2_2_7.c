gboolean user_function(GtkWidget *widget,
                     GdkEventSelection *event,
                      gpointer user_data); 	// 连接drag-begin信号
gboolean user_function(GtkWidget *widget,
                      GdkEventSelection *event,
                      gpointer user_data); 	// 连接drag-data-delete信号
void user_function(GtkWidget *widget,
                  GdkDragContext *drag_context,
                  GtkSelectionData *data,
                  guint info,
                  guint time,
                  gpointer user_data); 		// 连接drag-data-get信号
void user_function(GtkWidget *widget,
                  GdkDragContext *drag_context,
                  gint x,
                  gint y,
                  GtkSelectionData *data,
                  guint info,
                  guint time,
                  gpointer user_data);// 连接drag-data-received21	信号
gboolean user_function(GtkWidget *widget,
                      GdkDragContext *drag_context,
                      gint x,
                      gint y,
                      guint time,
                      gpointer user_data); 	// 连接drag-drop信号
void user_function(GtkWidget *widget,
                  GdkDragContext *drag_context,
                  gpointer user_data); 		// 连接drag-end信号
gboolean user_function(GtkWidget *widget,
                      GdkDragContext *drag_context,
                      GtkDragResult result,
                      gpointer user_data); 	// 连接drag-failed信号
void user_function(GtkWidget *widget,
                  GdkDragContext *drag_context,
                  guint time,
                  gpointer user_data); 		// 连接drag-leave信号
gboolean user_function(GtkWidget *widget,
                      GdkDragContext *drag_context,
                      gint x,
                      gint y,
                      guint time,
                      gpointer user_data); 	// 连接drag-motion信号
