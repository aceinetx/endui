#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename) {
  FILE *file;
  char *buffer;
  size_t bytesRead;
  size_t filesize;

  file = fopen(filename, "rb");
  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  filesize = ftell(file);
  fseek(file, 0, SEEK_SET);

  buffer = (char *)malloc(filesize + 1);
  if (!buffer) {
    fclose(file);
    return NULL;
  }

  bytesRead = fread(buffer, 1, filesize, file);
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
