#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <cglm/cglm.h>
#include "include/common.h"
#include "include/res.h"
#include "include/shaders.h"

#include <stdbool.h>
#define CODE(...) #__VA_ARGS__

int main(int argc, char *argv[]) {
    int windowWidth, windowHeight;

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    resInit();

    if(!initGlWindow(&windowWidth, &windowHeight)) return terminate();
    if(!initGlew()) return terminate();

    glViewport(0, 0, windowWidth, windowHeight);
    
    float size = 0.5f;
    float vertices[] = {
        -size, -size, -size,
        -size, size, -size,
        size, size, -size,
        size, size, -size,
        size, -size, -size,
        -size, -size, -size,

        -size, 0, size,
        -size, size, size,
        size, size, size,
        size, size, size,
        size, -size, size,
        -size, -size, size,
    };
    
    // create a vertex array object
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create a vertex buffer object
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // add the vertex data to the vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), NULL);
    glEnableVertexAttribArray(0);

/*
glm_translate(m, pivot);
glm_rotate(m, angle, axis);
glm_translate(m, pivotInv); /* pivotInv = -pivot */

/*
vec4 vec = {1.0f, 0.0f, 0.0f, 1.0f};
mat4 trans = GLM_MAT4_IDENTITY_INIT;
trans = glm_translate(trans, (vec3){1.0f, 1.0f, 0.0f});
vec = trans * vec;
std::cout << vec.x << vec.y << vec.z << std::endl;
*/

    // Compile Shaders and set Gl pipeline
    const GLchar* vertexShaderCode = "#version 330 core\n" CODE(
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    );
    const GLchar* fragmentShaderCode = "#version 330 core\n" CODE(
        out vec4 color;
        void main() {
            color = vec4(0.4f, 0.4f, 0.4f, 0.3f);
        } 
    );
    unsigned int program = createGlProgram(vertexShaderCode, fragmentShaderCode);
    if (program == false) return terminate();

    // enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // start render loop
    bool quit = false;
    while(!quit){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)) quit = true;
            if(event.type == SDL_QUIT) quit = true;
        }
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 12);
        SDL_GL_SwapWindow(mainWindow);
    }
    glDeleteProgram(program);
    return terminate();
}
