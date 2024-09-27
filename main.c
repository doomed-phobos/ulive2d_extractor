#include "live2d.h"

#include <stdio.h>

#define PATH "/home/phobos/IVAV/Assets/Moc/Model009.moc3"

int main(void) {
  live2d_init_log();
  Live2DMoc moc = live2d_try_load_from_path(PATH);
  if(!live2d_is_moc_alive(&moc)) {
    fprintf(stderr, "Failed to read moc in '%s'\n", PATH);
    return 1;
  }

  Live2DModel model = live2d_try_get_model_from_moc(&moc);
  if(!live2d_is_model_alive(&model)) {
    fprintf(stderr, "Failed to get model in '%s'\n", PATH);
    live2d_free_moc(&moc);
    return 1;
  }

  {
  puts("---- PARAMETERS ----- ");
  const int count = csmGetParameterCount(model.ptr);
  const char** parameterIds = csmGetParameterIds(model.ptr);
  for(int i = 0; i < count; ++i) puts(parameterIds[i]);                                                       
  }

  {
  puts("---- PARTS -----");
  const int count = csmGetPartCount(model.ptr);
  const char** partIds = csmGetPartIds(model.ptr);
  for(int i = 0; i < count; ++i) puts(partIds[i]);
  }

  live2d_free_model(&model);
  live2d_free_moc(&moc);

  return 0;
}