/*
 * diagnostics.cpp
 *
 *  Created on: 2016. máj. 19.
 *      Author: SilverBlade
 */
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>

void printDiagnosticInfo() {
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
    // Experimenting
    GLint numberOfMaxAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfMaxAttributes);
    std::cout << "Maximum number of vertex attributes supported: "
            << numberOfMaxAttributes << std::endl;
}


