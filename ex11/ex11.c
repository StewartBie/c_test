#include <stdio.h>

int main(int argc, char *argv[]) {
  int i = 0;
  char *states[] = {"California", "Oregon",  "Texas"};

	// int num_states = 4;

	i = 0;
	while (i < argc) {
		states[i] = argv[i];
		printf("parameter %d: %s\n", i, states[i]);
		i++;
	}
	return 0;
};
