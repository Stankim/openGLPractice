#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "Sphere.cpp"
#include "./../shaders.cpp"

void framebuffer_size_callback(GLFWwindow *window, int width,int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
float fov=45.0f;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 700;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float yaw=-90.0f, pitch;
bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f , lastY= SCR_HEIGHT / 2.0f;

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
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
glfwSetCursorPosCallback(window, mouse_callback);

glfwSetScrollCallback(window, scroll_callback);



if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
std::cout << "Failed to initialize GLAD" << std::endl;
return -1;
}
//glEnable(GL_DEPTH_TEST);

Shader sphereShader = Shader("sphere.vs", "sphere.fs");

Sphere sphere(8);


unsigned int VBO, VAO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sphere.sizeof_vertices, sphere.vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

while(!glfwWindowShouldClose(window)){
float currentFrame = static_cast<float>(glfwGetTime());
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;


processInput(window);
glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);

glm::mat4 projection;
projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 100.0f); 

glm::mat4 view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);

glm::mat4 model = glm::mat4(1.0f);
model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

sphereShader.use();

sphereShader.setMat4("model", model);
sphereShader.setMat4("view", view);	
sphereShader.setMat4("projection", projection);

glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, sphere.number_of_vertices);
glfwSwapBuffers(window);
glfwPollEvents();
}

glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);
glDeleteProgram(sphereShader.ID);

glfwTerminate();
return 0;
}


void processInput(GLFWwindow *window){
if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
glfwSetWindowShouldClose(window, true);
const float cameraSpeed = 2.5f * deltaTime;
if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	cameraPos += cameraSpeed * cameraFront;
if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	cameraPos -= cameraSpeed * cameraFront;
if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
glViewport(0,0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    cameraFront = glm::normalize(direction);
    
} 

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
fov -= (float) yoffset;
if(fov<1.0f)
	fov = 1.0f;
if(fov > 45.0f)
	fov = 45.0f;
}
