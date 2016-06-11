/*
 * Material.h
 *
 *  Created on: 2016. jún. 7.
 *      Author: SilverBlade
 */

#ifndef SRC_GRAPHICS_MATERIAL_H_
#define SRC_GRAPHICS_MATERIAL_H_

// OpenGL/Graphic libraries
// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW)
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>

class Material {
private:
    GLint diffuse;
    GLint specular;
    GLfloat shininess;
public:
    Material(GLint diffuse, GLint specular, GLfloat shininess);
    GLint getDiffuse() const;
    void setDiffuse(GLint diffuse);
    GLint getSpecular() const;
    void setSpecular(GLint specular);
    float getShininess() const;
    void setShininess(float shininess);
    virtual ~Material();
};

#endif /* SRC_GRAPHICS_MATERIAL_H_ */
