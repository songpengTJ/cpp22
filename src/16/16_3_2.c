#include <ioctl.h>								// 提供IO操作相关控制函数
#include <unistd.h>								// 标准函数库
#include <fcntl.h>								// 提供文件操作相关控制函数
#include <sys/soundcard.h>						// 提供声卡配置相关系统调用
#include <oss.h>								// OSS函数库

int general_volume(*((int*) data))					// 设置音量
{
   int mixer_fd;									// 用于调音器标识符
   mixer_fd = oss_get_mixer();						// 获得调音器的标识符
   if (*data < 0 || *data > 100) {						// 判断输入的数值是否有误
      printf("输入的音量调节值有误\n");
      return 0;
   }
   if (ioctl(mixer_fd, SOUND_MIXER_WRITE(SOUND_MIXER_WAV), data) == -1) {
											// 打开声卡设备文件，设置音量
      printf("无法打开指定声卡\n");
      return 0;
   }
   return 1;
}

int request_volume(void) 										// 查询音量函数
{
   int mixer_fd;												// 用于设备文件的标识符
   int data;												// 用于保存音量的数值
   mixer_fd = oss_get_mixer();									// 打开设备文件
   if (ioctl(mixer_fd, SOUND_MIXER_READ(SOUND_MIXER_WAV), &data) == -1) {
														// 读取混音器中音量数值
      printf("无法打开指定声卡\n");
      return -1;
   }
   return data;												// 返回音量的数值
}
