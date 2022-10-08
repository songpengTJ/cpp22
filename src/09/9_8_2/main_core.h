#ifndef MAIN_CORE_H_							// 判断是否已包含该头文件
#define MAIN_CORE_H_							// 定义头文件
#define GENERAL_MEDIALIB_INIT 1000				// 程序控制指令
#define GENERAL_PLAYLIST_INIT 1001

#define REQUEST_STATE 2000						// 程序请求指令

#define MEDIALIB_SHOW 3000						// 媒体库控制指令

#define PLAYLIST_SHOW 3100						// 播放列表控制指令

#define PLAY_START 4000							// 播放控制指令

int general_init(void);							// 定义函数原型
int general_sleep(void);

#endif /* MAIN_CORE_H_ */						// 结束头文件定义
