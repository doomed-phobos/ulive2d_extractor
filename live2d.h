#pragma once
#include "file.h"
#include <Live2DCubismCore.h>

typedef struct {
  char* unalignedBytes;
  char* alignedBytes;
  unsigned long length;
  csmMoc* ptr;
} Live2DMoc;

typedef struct {
  char* unalignedBytes;
  char* alignedBytes;
  unsigned long length;
  csmModel* ptr;
} Live2DModel;

void live2d_init_log();
Live2DMoc live2d_try_load_from_path(const char* filepath);
Live2DModel live2d_try_get_model_from_moc(Live2DMoc* moc);
bool live2d_is_moc_alive(Live2DMoc* moc);
bool live2d_is_model_alive(Live2DModel* model);
void live2d_free_model(Live2DModel* model);
void live2d_free_moc(Live2DMoc* moc);