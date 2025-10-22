#include <regex.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *str;
  scanf("%s", str);

	// 结构体 regx_t 用来编译 保存格式
  regex_t find_num;
  char *pattern = "[123]";
  if (regcomp(&find_num, pattern, 1)) {
    fprintf(stderr, "Couldn't compile regex\n");
    return 1;
  }

  return 0;
}
