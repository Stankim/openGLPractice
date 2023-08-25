#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int main(){

int max_attributes;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attributes);
std::cout<<"maximum vertex attributes " << max_attributes<<std.endl;


glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

GLFWwindow* window = glfwCreateWindow(500,500, "Hello stan", NULL, NULL);
if(window==NULL){
std::cout<< "Failed to create GLFW window" << std::endl;
glfwTerminate();
return -1;
}
glfwMakeContextCurrent(window);

if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
std::cout << "Failed to initialize GLAD" << std::endl;
return -1;
}

glViewport(0,0, 500, 500);
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
while(!glfwWindowShouldClose(window)){
processInput(window);
glClearColor(0.1f, 0.5f, 0.8f, 0.5f);
glClear(GL_COLOR_BUFFER_BIT);

glfwSwapBuffers(window);
glfwPollEvents();
}
glfwTerminate();
return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window){
if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
glfwSetWindowShouldClose(window, true);
}

