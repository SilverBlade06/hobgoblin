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
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLfloat shininess;
public:
    Material();
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shininess);
    const glm::vec3& getAmbient() const;
    void setAmbient(const glm::vec3& ambient);
    const glm::vec3& getDiffuse() const;
    void setDiffuse(const glm::vec3& diffuse);
    float getShininess() const;
    void setShininess(float shininess);
    const glm::vec3& getSpecular() const;
    void setSpecular(const glm::vec3& specular);
    virtual ~Material();
};

#endif /* SRC_GRAPHICS_MATERIAL_H_ */
