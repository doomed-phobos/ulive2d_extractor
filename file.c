#include "file.h"

#include <stdio.h>
#include <stdlib.h>

FileBuffer file_read(const char *filepath) {
  FILE* file = fopen(filepath, "rb");
  if(!file) return (FileBuffer){NULL, 0};
  fseek(file, 0, SEEK_END);

  FileBuffer res;
  res.size = ftell(file);
  res.bytes = (char*)malloc(res.size);
  fseek(file, 0, SEEK_SET);
  fread(res.bytes, sizeof(*res.bytes), res.size, file);

  fclose(file);

  return res;
}

bool file_is_available(FileBuffer file) {
  return file.bytes != NULL;
}

void file_free(FileBuffer file) {
  free(file.bytes);
}