#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GraphicsEngine {
    GLFWwindow* window;
    GLuint shaderProgram, VAO, VBO;
    glm::mat4 projection;

public:
    GraphicsEngine(int width, int height) {
        glfwInit();
        window = glfwCreateWindow(width, height, "3D Engine", NULL, NULL);
        glfwMakeContextCurrent(window);
        glewInit();

        // Shader setup
        const char* vertexShaderSource = "#version 330 core\n...";
        const char* fragmentShaderSource = "#version 330 core\n...";
        
        // Compile shaders, create program...
        
        // Cube data
        float vertices[] = {...};
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // Buffer setup...

        projection = glm::perspective(glm::radians(45.0f), 
                                    (float)width/height, 
                                    0.1f, 100.0f);
    }

    void render() {
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glm::mat4 view = glm::lookAt(...);
            glm::mat4 model = glm::rotate(glm::mat4(1.0f), 
                                         (float)glfwGetTime(), 
                                         glm::vec3(0.5f, 1.0f, 0.0f));
            glm::mat4 mvp = projection * view * model;
            
            glUseProgram(shaderProgram);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 
                              1, GL_FALSE, &mvp[0][0]);
            
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    ~GraphicsEngine() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glfwTerminate();
    }
};

int main() {
    GraphicsEngine engine(800, 600);
    engine.render();
    return 0;
}
