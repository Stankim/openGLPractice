#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders.cpp"
#include <iostream>
void framebuffer_size_callback(GLFWwindow *window, int width,int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 700;

int main(){
glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

GLFWwindow* window= glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My own copy, openGL example", NULL, NULL);
if(window==NULL)
{
std::cout<<"Failed to create GLFW window"<< std::endl;
glfwTerminate();
return -1;
}
glfwMakeContextCurrent(window);
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
std::cout << "Failed to initialize GLAD" << std::endl;
return -1;
}

Shader ownShader("./ex_vshader.vs", "./ex_fshader.fs");


float vertices[] = {
 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
0.8f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.8f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.3f, 0.5f, 0.0f, 1.0f,0.0f, 0.0f
};

unsigned int indices[]= {
0, 1, 2,
0, 2, 4,
2, 3, 4
};


unsigned int VBO, VAO, EBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// position attribute
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// color attribute
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
glEnableVertexAttribArray(1);
	

glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

while(!glfwWindowShouldClose(window)){
processInput(window);
glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);

ownShader.use();

float timeValue = glfwGetTime();
float greenValue = (sin(timeValue)/2.0f) + 0.5f;


int vertexColorLocation = glGetUniformLocation(shaderProgram, "alterColor");
glUniform4f(vertexColorLocation, 0.2f, greenValue, 0.3f, 1.0f);


glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
glfwSwapBuffers(window);
glfwPollEvents();
}

glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);


glfwTerminate();
return 0;
}

void processInput(GLFWwindow *window){
if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
glViewport(0,0, width, height);
}
