#include <stdio.h>
int main(int argc, char *argv[]) {
  int ages[] = {23, 43, 12, 89, 2};
  char *names[] = {"Alan", "Frank", "Marry", "John", "Lisa"};

  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  for (i = 0; i < count; i++) {
    printf("%s has %d years alive.\n", names[i], ages[i]);
  }
  printf("---\n");

  int *cur_age = ages;
  char **cur_name = names;

  for (i = 0; i < count; i++) {
    printf("%s is %d yeard old again.\n", cur_name[i], *(cur_age + i));
  }

  for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_age++) {
    printf("%s lived %d years so far.\n", *cur_name, *cur_age);
  }

  for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++) {
    printf("name:%s points to %p \nyears:%d points to %p.\n", *cur_name, cur_name, *cur_age, cur_age);
  }
  return 0;
}
