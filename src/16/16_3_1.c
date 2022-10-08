#include <glib.h>									// 包含glib库
#include <dbus/dbus-glib.h>							// 包含glib库中D-BUS管理库
int link_dbus()
{
   GMainLoop *loop;								// 定一个事件循环对象的指针
   DBusConnection *bus;								// 定义总线连接对象的指针
   DBusError error;									// 定义D-BUS错误消息对象
   loop = g_main_loop_new(NULL, FALSE);				// 创建新事件循环对象
   dbus_error_init(&error);							// 将错误消息对象连接到D-BUS错误消息对象
   bus = dbus_bus_get(DBUS_BUS_SYSTEM, &error);		// 连接到系统总线
   if (!bus) {										// 判断是否连接错误
      g_warning("连接到D-BUS失败: %s", error.message); 	// 使用GLib输出错误警告信息
      dbus_error_free(&error);							// 清除错误消息
      return 1;
  }
   dbus_connection_setup_with_g_main(bus, NULL);		// 将总线设为接收GLib事件循环
   dbus_bus_add_match(bus, "type='signal',interface='com.system.dbus.Signal'");	// 定义匹配器
   dbus_connection_add_filter(bus, general_exit, loop, NULL);	// 调用函数接收消息
   g_main_loop_run(loop);							// 启动事件循环
   return 0;
}





static DBusHandlerResult							// 定义接收消息函数的细节
general_exit (DBusConnection *connection, DBusMessage *message, void *user_data)
{
   GMainLoop *loop = user_data;					// 定义事件循环对象的指针，并与主函数中的同步
   if (dbus_message_is_signal 					// 接收连接成功消息，判断是否连接失败
        (message, DBUS_INTERFACE_ORG_FREEDESKTOP_LOCAL, "Disconnected")) {
      g_main_loop_quit (loop);					// 退出主循环
      return DBUS_HANDLER_RESULT_HANDLED;
   }
   if (dbus_message_is_signal(message, "com.burtonini.dbus.Signal", "Ping")) {
											// 指定消息对象路径，判断是否成功
      DBusError error;							// 定义错误对象
      char *s;
      dbus_error_init(&error);						// 将错误消息对象连接到D-BUS错误消息对象
      if (dbus_message_get_args 					// 接收消息，并判断是否有错误
         (message, &error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID)) {
         if (!strcmp(s, "SHUTDOWN")) {				// 判断收到的消息是否为系统关闭信息
            main_core(GENERAL_EXIT, NULL);		// 调用核心控制模块
            dbus_free (s);						// 清除该消息
         }
      } 
      else {									// 有错误时执行下列语句
         g_print("消息已收到，但有错误提示: %s\n", error.message);
         dbus_error_free (&error);
      }
      return DBUS_HANDLER_RESULT_HANDLED;
   }
   return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}
