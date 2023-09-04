#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "Polygon.cpp"

void framebuffer_size_callback(GLFWwindow *window, int width,int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 700;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
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

unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);

int success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if(!success){
glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
std::cout << "ERROR: vertex shader compilation failed\n"<< infoLog<< std::endl;
}

unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);

glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
if(!success)
{
glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
std::cout<< "ERROR: Fragment shader compilation failed\n" << infoLog << std::endl;
}

unsigned int shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);

glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if(!success) {
glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
std::cout << "ERROR:: Shader program linkage failed\n" << infoLog << std::endl;
}
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);

Polygon polygon(1000);

polygon.vertices;

unsigned int VBO, VAO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, polygon.sizeof_vertices, polygon.vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

while(!glfwWindowShouldClose(window)){
processInput(window);
glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, polygon.number_of_vertices);
glfwSwapBuffers(window);
glfwPollEvents();
}

glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);
glDeleteProgram(shaderProgram);

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