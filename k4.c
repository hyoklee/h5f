#include <stdio.h>

#define CHUNK_SIZE 1024
#define NUM_CHUNKS 1000

int main(void) {
  
  FILE* file_id = NULL;
  int data[CHUNK_SIZE];
  char fname[8];
  
  for (int i = 0; i < CHUNK_SIZE; i++) {
    data[i] = i;
  }

  for (int i = 0; i < NUM_CHUNKS; i++) {
    sprintf(fname, "%d.bin", i);
    file_id = fopen(fname, "w");
    if (file_id == NULL) {
      printf("Error creating file\n");
      return -1;
    }
    fwrite(data, 1024, 1, file_id);
    fclose(file_id);    
  }
  return 0;
}
