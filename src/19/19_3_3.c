#define CUSTOM_USER_DIRECTORY  "/dev/null"					// 定义用户目录
#define CUSTOM_PLUGIN_PATH ""							// 定义插件目录
#define PLUGIN_SAVE_PREF "/purple/nullclient/plugins/saved"		// 定义插件头目录
#define UI_ID "nullclient"										// 定义用户接口ID
#include <purple.h>											// 包含libpurple库
#include <glib.h>											// 包含GLib库
#include <signal.h>
#include <string.h>
#include <unistd.h>
#define PURPLE_GLIB_READ_COND  (G_IO_IN | G_IO_HUP | G_IO_ERR)		// 定义GLib读成员
#define PURPLE_GLIB_WRITE_COND (G_IO_OUT | G_IO_HUP | G_IO_ERR | G_IO_NVAL)
														// 定义GLib写成员
typedef struct _PurpleGLibIOClosure {							// 该结构用于作为回调函数参数
   PurpleInputFunction function;								// 函数名
   guint result;												// 返回结果
   gpointer data;											// 数据参数
} PurpleGLibIOClosure;




static void purple_glib_io_destroy(gpointer data)					// 该函数用于清除数据
{
   g_free(data);											// 释放data所指向的内存空间
}

static gboolean purple_glib_io_invoke(GIOChannel *source,
                                   GIOCondition condition,
                                   gpointer data)				// 调用GLib输入输出接口
{
   PurpleGLibIOClosure *closure = data;							// 创建libpurple输入输出终止符
   PurpleInputCondition purple_cond = 0;							// 创建libpurple输入条件对象
   if (condition & PURPLE_GLIB_READ_COND)					// 判断条件是否为读取
      purple_cond |= PURPLE_INPUT_READ;					// 将libpurple输入条件对象设为读取
   if (condition & PURPLE_GLIB_WRITE_COND)					// 判断条件是否为写入
      purple_cond |= PURPLE_INPUT_WRITE;					// 将libpurple输入条件对象设为写入
   closure->function(closure->data, g_io_channel_unix_get_fd(source),
           purple_cond);										// 调用回调函数执行输入输出操作
   return TRUE;
}

static guint glib_input_add(gint fd,
                         PurpleInputCondition condition,
                         PurpleInputFunction function,
                         gpointer data)						// 加入一个GLib输入接口
{
   PurpleGLibIOClosure *closure = g_new0(PurpleGLibIOClosure, 1);	// 创建libpurple输入输出终止符
   GIOChannel *channel;										// 声明GLib通道对象
   GIOCondition cond = 0;									// 声明GLib输入输出条件
   closure->function = function;								// 定义回调函数
   closure->data = data;										// 定义数据指针
   if (condition & PURPLE_INPUT_READ)						// 判断条件是否为读取
      cond |= PURPLE_GLIB_READ_COND; 					// 将libpurple输入条件对象设为读取
   if (condition & PURPLE_INPUT_WRITE) 						// 判断条件是否为写入
      cond |= PURPLE_GLIB_WRITE_COND; 					// 将libpurple输入条件对象设为写入
   channel = g_io_channel_unix_new(fd);							// 创建GLib通道
   closure->result = g_io_add_watch_full(channel,
                                      G_PRIORITY_DEFAULT,
                                      cond,
                                      purple_glib_io_invoke,
                                      closure,
                                      purple_glib_io_destroy);		// 设置通道中的回调函数
   g_io_channel_unref(channel);								// 将通道对象托管
   return closure->result;
}

static PurpleEventLoopUiOps glib_eventloops = 					// 定义GLib事件循环
{
   g_timeout_add,											// 超时处理
   g_source_remove,										// 源删除
   glib_input_add,											// 添加输入管道
   g_source_remove,										// 源删除
   NULL,
#if GLIB_CHECK_VERSION(2,14,0)								// 判断GLib版本是否为2.14.0
   g_timeout_add_seconds,									// 超时秒数
#else
   NULL,
#endif
   NULL
};

static void null_write_conv(PurpleConversation *conv,				// 会话标识符
                         const char *who,						// 好友ID
                         const char *alias,						// 昵称
                         const char *message,					// 消息
                         PurpleMessageFlags flags,				// 消息类型
                         time_t mtime)							// 发送时间
{
   const char *name;										// 用于保存好友名称
   if (alias && *alias)										// 判断存在好友昵称
      name = alias;											// 将好友名称设为昵称
   else if (who && *who)										// 判断好友ID存在
      name = who;											// 将好友名称设为好友ID
   else
      name = NULL;
   printf("(%s) %s %s: %s\n", purple_conversation_get_name(conv),
         purple_utf8_strftime("(%H:%M:%S)", localtime(&mtime)),
         name, message);									// 输出会话
}

static PurpleConversationUiOps null_conv_uiops = 					// 定义会话UI选项
{
   NULL,													// 创建会话
   NULL,													// 清除会话
   NULL,													// 输入聊天消息
   NULL,													// 输入通信信息
   null_write_conv,											// 写入会话
   NULL,													// 添加联系人
   NULL,													// 修改联系人名
   NULL,													// 删除联系人
   NULL,													// 更新联系人姓名
   NULL,													// 当前时间
   NULL,													// 获得焦点
   NULL,													// 增加表情
   NULL,													// 输入表情
   NULL,													// 关闭表情
   NULL,													// 发送确认
};

static void null_ui_init(void)									// 初始化用户接口
{
   purple_conversations_set_ui_ops(&null_conv_uiops);				// 使用会话UI选项初始化用户接口
}

static PurpleCoreUiOps null_core_uiops = 						// 定义核心用户接口选项
{
   NULL, NULL, null_ui_init, NULL
};

static void init_libpurple(void)									// 初始化libpurple
{
   purple_util_set_user_dir(CUSTOM_USER_DIRECTORY);			// 设置用户目录
   purple_debug_set_enabled(FALSE);							// 不接受调试信息
   purple_core_set_ui_ops(&null_core_uiops);						// 设置核心用户接口选项
   purple_eventloop_set_ui_ops(&glib_eventloops);					// 设置GLib事件循环
   purple_plugins_add_search_path(CUSTOM_PLUGIN_PATH);		// 添加搜索插件路径
   if (!purple_core_init(UI_ID)) {								// 初始化libpurple环境
      fprintf(stderr,
            "libpurple初始化失败!\n");
      abort();
   }
   purple_set_blist(purple_blist_new());							// 读取联系人列表
   purple_blist_load();
   purple_prefs_load();										// 读取用户配置
   purple_plugins_load_saved(PLUGIN_SAVE_PREF);				// 加载插件
   purple_pounces_load();									// 完成初始化
}

static void signed_on(PurpleConnection *gc, gpointer null)			// 接收libpurple信号
{
   PurpleAccount *account = purple_connection_get_account(gc);		// 读取本地账户信息
   printf("Account connected: %s %s\n", account->username, account->protocol_id);
}

static void connect_to_signals_for_demonstration_purposes_only(void)	// 对信号进行过滤
{
   static int handle;											// 用于保存句柄
   purple_signal_connect(purple_connections_get_handle(), "signed-on", &handle,
            PURPLE_CALLBACK(signed_on), NULL);				// 设置过滤器和回调函数
}

int main(int argc, char *argv[])
{
   GList *iter;												// 声明GList链表节点
   int i, num;												// 用户循环控制变量
   GList *names = NULL;										// 声明GList链表
   const char *prpl;
   char name[128];											// 用于保存用户名
   char *password;											// 用于保存密码
   GMainLoop *loop = g_main_loop_new(NULL, FALSE);			// 创建一个主循环
   PurpleAccount *account;									// 定义libpurple账户
   PurpleSavedStatus *status;									// 定义libpurple状态
   char *res;												// 用于用户输入交互
   signal(SIGCHLD, SIG_IGN);								// 设置libpurple信号
   init_libpurple();											// 初始化libpurple库
   printf("libpurple初始化成功。\n");
   iter = purple_plugins_get_protocols();							// 通过插件获得即时通信协议
   for (i = 0; iter; iter = iter->next) {								// 遍历GList链表
      PurplePlugin *plugin = iter->data;							// 取得libpurple插件信息
      PurplePluginInfo *info = plugin->info;
      if (info && info->name) {
         printf("\t%d: %s\n", i++, info->name);						// 输出libpurple插件名
         names = g_list_append(names, info->id);					// 将libpurple插件名加入GList链表
      }
   }
   printf("请选择一个协议 [0-%d]: ", i-1);							// 提示用户选择一个IM协议
   res = fgets(name, sizeof(name), stdin);							// 从终端读取用户输入
   if (!res) {
      fprintf(stderr, "协议选择不正确");
      abort();
   }
   sscanf(name, "%d", &num);									// 输入协议编号
   prpl = g_list_nth_data(names, num);							// 在GList链表中读取相关协议信息
   printf("用户名: ");											// 提述输入用户名
   res = fgets(name, sizeof(name), stdin);							// 从终端读取用户输入
   if (!res) {
      fprintf(stderr, "无法读取用户名");
      abort();
   }
   name[strlen(name) - 1] = 0;
   account = purple_account_new(name, prpl);					// 创建账户
   password = getpass("请输入密码: ");
   purple_account_set_password(account, password);				// 获取用户密码
   purple_account_set_enabled(account, UI_ID, TRUE);				// 激活账户
   status = purple_savedstatus_new(NULL, 
                                  PURPLE_STATUS_AVAILABLE);	// 设置当前状态为可用
   purple_savedstatus_activate(status);							// 设置用户状态为“活动”
   connect_to_signals_for_demonstration_purposes_only();			// 接收IM服务器传来的消息
   g_main_loop_run(loop);									// 启动GLib主循环
   return 0;
}

