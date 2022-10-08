union id3_field {
   enum id3_field_type type;			// 项目类型
   struct {
     enum id3_field_type type;
     signed long value;
   } number;								// 数字
   struct {
     enum id3_field_type type;
     id3_latin1_t *ptr;
   } latin1;								// 拉丁文
   struct {
     enum id3_field_type type;
     unsigned int nstrings;
     id3_latin1_t **strings;
   } latin1list;						// 拉丁文列表
   struct {
     enum id3_field_type type;
     id3_ucs4_t *ptr;
   } string;								// 字符串
   struct {
     enum id3_field_type type;
     unsigned int nstrings;
     id3_ucs4_t **strings;
   } stringlist;						// 字符串列表
   struct {
     enum id3_field_type type;
     char value[9];
   } immediate;							// 直接数据
   struct {
     enum id3_field_type type;
     id3_byte_t *data;
     id3_length_t length;
   } binary;								// 二进制数据
};
