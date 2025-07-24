#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
  char *name;
  int age;
  int height;
  int weight;
};


void print_person(struct Person px){
  printf("Name: %s\n",px.name);
  printf("\tAge: %d\n",px.age);
  printf("\tHeight: %d\n",px.height);
  printf("\tWeight: %d\n",px.weight);
}

struct Person change_name (struct Person px){
	px.name = "new name";
	return px;
}
int main(int argc, char *argv[]){
  struct Person joe = {
    .name = "joe",
    .age = 32,
    .height = 140,
    .weight = 100
  };
  print_person(joe);
	printf("change ----\n");
	joe = change_name(joe);
	print_person(joe);
  return 0;
}
