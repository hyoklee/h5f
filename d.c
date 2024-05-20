#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define BASE_DIR "."  // Change this to your desired base directory
#define MAX_NAME_LEN 256   // Adjust if directory names need to be longer

int main(int argc, char *argv[]) {
    int num_dirs = 10000;  // Adjust the number of directories to create

    // Check if the base directory exists (optional)
    struct stat st;
    if (stat(BASE_DIR, &st) == -1) {
        printf("Base directory '%s' does not exist.\n", BASE_DIR);
        return 1;
    }

    // Loop to create directories with unique names
    for (int i = 0; i < num_dirs; i++) {
        char dir_name[MAX_NAME_LEN];
        snprintf(dir_name, MAX_NAME_LEN, "%s/dir_%d", BASE_DIR, i);

        // Check if directory already exists (optional)
        if (stat(dir_name, &st) == 0) {
            printf("Directory '%s' already exists, skipping...\n", dir_name);
            continue;
        }

        // Create the directory
        if (mkdir(dir_name, 0755) == -1) {
            perror("mkdir");
            return 1;
        }

        // printf("Created directory: %s\n", dir_name);
    }

    // printf("Successfully created %d directories.\n", num_dirs);
    return 0;
}
