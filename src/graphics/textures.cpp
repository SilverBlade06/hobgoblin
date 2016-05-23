#include "textures.h"

GLuint loadTexture(const char* texture_file_path) {

   GLuint texture; // texture ID
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   // Parameters
   // Texture wrap
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // Texture filter
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   // Only for Mipmaps
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   int width, height;
   unsigned char* image = SOIL_load_image(texture_file_path, &width, &height, 0, SOIL_LOAD_RGB);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
   glGenerateMipmap(GL_TEXTURE_2D);
   // Cleanup
   SOIL_free_image_data(image);
   glBindTexture(GL_TEXTURE_2D, 0);

   return texture;
}
