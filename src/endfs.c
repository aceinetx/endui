#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long filesize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = (char *)malloc(filesize + 1);
  if (!buffer) {
    fclose(file);
    return NULL;
  }

  size_t bytesRead = fread(buffer, 1, filesize, file);
  if (bytesRead != filesize) {
    free(buffer);
    fclose(file);
    return NULL;
  }

  buffer[filesize] = '\0';
  fclose(file);
  return buffer;
}

void write_file(const char *filename, char *text) {
  FILE *file;

  file = fopen(filename, "w");

  if (file == NULL) {
    return;
  }

  fprintf(file, "%s", text);

  fclose(file);
}