#pragma once

typedef struct {
  char* bytes;
  unsigned long size;
} FileBuffer;

FileBuffer file_read(const char* filepath);
bool file_is_available(FileBuffer file);
void file_free(FileBuffer file);