#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders.cpp"
#include "rel_img_loader.cpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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




Shader ownShader("./lighting.vs", "./lighting.fs");
Shader lightShader("./light_cube.vs", "./light_cube.fs");


float vertices[] = {
 -0.5f, 0.5f, 0.5f, 
0.5f, 0.5f, 0.5f,
0.5f, -0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,
0.5f, -0.5f, -0.5f,
0.5f, 0.5f, -0.5f,
-0.5f, 0.5f, -0.5f,
-0.5f, -0.5f, -0.5f
};

unsigned int indices[]= {
 0, 1, 2,
 0, 2, 3,
1, 2, 4,
1, 4, 5,
0, 1, 5,
0, 1, 6,
 0, 3, 7,
 0, 6, 7,
 2, 3, 7,
 2, 4, 7,
 4, 5, 6,
 4, 6, 7
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
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);



unsigned int lightVAO;
glGenVertexArrays(1, &lightVAO);
glBindVertexArray(lightVAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
glEnableVertexAttribArray(0);


	

glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);








glm::mat4 view = glm::mat4(1.0f);
view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

glm::mat4 projection;
projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.0f, 100.0f);  










while(!glfwWindowShouldClose(window)){
processInput(window);
glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);


glm::mat4 model = glm::mat4(1.0f);
model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));
ownShader.use();
ownShader.setMat4("model", model);
ownShader.setMat4("view", view);
ownShader.setMat4("projection", projection);

ownShader.setVec3("objectColor",1.0f, 0.5f, 0.31f);
ownShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


glm::vec3 lightPos(0.6f, 0.7f, 0.5f);
glm::mat4 model2 = glm::mat4(1.0f);
model2 = glm::mat4(1.0f);
model2 = glm::translate(model2, lightPos);
model2 = glm::scale(model2, glm::vec3(0.2f));
lightShader.use();
lightShader.setMat4("model", model2);
lightShader.setMat4("view", view);
lightShader.setMat4("projection", projection);

glBindVertexArray(lightVAO);
glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


glfwSwapBuffers(window);
glfwPollEvents();
}

glDeleteVertexArrays(1, &VAO);
//glDeleteVertexArrays(1, &lightVAO);
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
