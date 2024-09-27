#include "live2d.h"
#include "file.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

static void live2d_log_function(const char* message) {
  printf("[Live2D] %s\n", message);
}

static void memzero(void* addr, size_t size) {
  memset(addr, 0, size);
}

void live2d_init_log() {
  csmSetLogFunction(&live2d_log_function);
}

Live2DMoc live2d_try_load_from_path(const char* filepath) {
  Live2DMoc moc;
  memzero(&moc, sizeof(Live2DMoc));

  FileBuffer file = file_read(filepath);
  if(!file_is_available(file)) {
    live2d_log_function("Failed to load moc file");
    return moc;
  }

  moc.unalignedBytes = (char*)malloc(file.size + csmAlignofMoc);
  const unsigned long num = (size_t)moc.unalignedBytes & (csmAlignofMoc -1);
  moc.alignedBytes = (num != 0) ? moc.unalignedBytes + csmAlignofMoc - num : moc.unalignedBytes;
  moc.length = file.size;  
  memcpy(moc.alignedBytes, file.bytes, file.size);
  file_free(file);

  if(!csmHasMocConsistency(moc.alignedBytes, moc.length)) {
    live2d_log_function("Failed to read Live2D moc. It isn't consistent");
    live2d_free_moc(&moc);
    return moc;
  }

  moc.ptr = csmReviveMocInPlace(moc.alignedBytes, moc.length);

  return moc;
}

Live2DModel live2d_try_get_model_from_moc(Live2DMoc* moc) {
  assert(moc && live2d_is_moc_alive(moc));

  Live2DModel model;
  memzero(&model, sizeof(Live2DModel));

  const unsigned size = csmGetSizeofModel(moc->ptr);
  model.unalignedBytes = (char*)malloc(size + csmAlignofModel);
  const unsigned long num = (size_t)model.unalignedBytes & (csmAlignofModel - 1);
  model.alignedBytes = (num != 0) ? model.unalignedBytes + csmAlignofModel - num : model.unalignedBytes;
  model.length = size;

  if(!(model.ptr = csmInitializeModelInPlace(moc->ptr, model.alignedBytes, model.length))) {
    live2d_log_function("Failed to get Live2D model");
    live2d_free_model(&model);
    return model;
  }

  return model;
}

void live2d_free_model(Live2DModel* model) {
  assert(model && live2d_is_model_alive(model));
  free(model->unalignedBytes);
  memzero(model, sizeof(Live2DModel));
}

void live2d_free_moc(Live2DMoc* moc) {
  assert(moc && live2d_is_moc_alive(moc));
  free(moc->unalignedBytes);
  memzero(moc, sizeof(Live2DMoc));
}

bool live2d_is_moc_alive(Live2DMoc* moc) {
  assert(moc);
  
  return moc->unalignedBytes != NULL;
}

bool live2d_is_model_alive(Live2DModel *model) {
  assert(model);

  return model->unalignedBytes != NULL;
}