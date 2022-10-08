﻿#include <string.h>							// 包含字符串函数库
#include <id3tag.h>							// 包含libid3tag函数库
#include "medialib.h"						// 包含媒体库相关函数的头文件
int read_tag_from_file(const char *file,
                     struct _medialib *media)	// 读取MP3文件中的信息
{
   struct id3_file *id3file;			// 用于保存libid3tag库文件对象
   struct id3_tag *tag;						// 用于保存文件信息
   struct id3_frame *frame_title;			// 用于保存标题信息
   struct id3_frame *frame_artist;			// 用于保存艺术家信息
   struct id3_frame *frame_album;			// 用于保存专辑信息
   struct id3_frame *frame_genre;			// 用于保存流派信息
   struct id3_frame *frame_time;			// 用于保存记录长度信息
   id3file = id3_file_open(file, ID3_FILE_MODE_READONLY);
   // 打开文件并创建id3_file结构体
   if (id3file == NULL) {					// 判断文件打开是否失败
      printf("打开文件失败\n");
      return -1;
   }
   tag = id3_file_tag(id3file);				// 创建id3_tag结构体
   frame_title = id3_tag_findframe(tag, ID3_FRAME_TITLE, 0);
   // 创建id3_frame结构体
   if (frame_title->fields)					// 防止指向NULL的地址操作
      strcpy(media->title, (char*) frame_title->fields);
      // 将项目信息复制到媒体库结构中
   frame_artist = id3_tag_findframe(tag, ID3_FRAME_ARTIST, 0);
   if (frame_artist->fields)
      strcpy(media->atrist, (char*) frame_artist->fields);
   frame_album = id3_tag_findframe(tag, ID3_FRAME_ALBUM, 0);
   if (frame_album->fields)
      strcpy(media->album, (char*) frame_album->fields);
   frame_genre = id3_tag_findframe(tag, ID3_FRAME_GENRE, 0);
   if (frame_genre->fields)
      strcpy(media->genre, (char*) frame_genre->fields);
   frame_time = id3_tag_findframe(tag, "TDRC", 0);
   if (frame_time->fields)
      media->record_time = id3_field_getint(frame_time->fields);
      // 将项目信息作为数字类型提取
   strcpy(media->filepath, file);
   id3_file_close(id3file);
   return 0;
}
