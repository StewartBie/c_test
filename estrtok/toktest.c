#include <string.h>
#include <stdio.h>

int main() {
    char str[] = "This,is a test string.";
    const char delims[] = ", ";
    char *token;

    // Get the first token
    token = strtok(str, delims);
    printf("First token: %s\n", token); // Output: This
    printf("Now str is: %s\n", str + 5); // Output: This

    // Get subsequent tokens
    while ((token = strtok(NULL, delims)) != NULL) {
        printf("Next token: %s\n", token);
    }
    // Output:
    // Next token: is
    // Next token: a
    // Next token: test
    // Next token: string.

    return 0;
}
