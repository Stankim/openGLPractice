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




Shader ownShader("./ex_vshader.vs", "./ex_fshader.fs");

int width, height, nrChannels;
unsigned char *data = stbi_load("image.jpg", &width, &height, &nrChannels, 0);

if(!data){
std::cout << "Failed to load image." << std::endl;
return -1;
}

unsigned int texture1;
glGenTextures(1, &texture1);
glBindTexture(GL_TEXTURE_2D, texture1);



	
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(data);



data = stbi_load("image2.jpg", &width, &height, &nrChannels, 0);
if(!data){
	std::cout << "Failed to load 2nd image." <<std::endl;
	return -1;
}
unsigned int texture2;
glGenTextures(1, &texture2);
glBindTexture(GL_TEXTURE_2D, texture2);


glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(data);




float vertices[] = {
 0.5f, 0.5f, 0.0f, 	1.0f, 0.0f, 0.0f, 	1.0f, 1.0f,
0.8f, 0.0f, 0.0f, 	0.0f, 1.0f, 0.0f, 	1.0f, 0.0f,
0.0f, -0.5f, 0.0f, 	0.0f, 0.0f, 1.0f, 	0.0f, 0.0f,
-0.8f, 0.0f, 0.0f, 	0.0f, 0.0f, 1.0f, 	0.0f, 0.5f,
-0.3f, 0.5f, 0.0f,	1.0f,0.0f, 0.0f,	 0.0f, 1.0f
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
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 *sizeof(float), (void *)(3 * sizeof(float)));
glEnableVertexAttribArray(1);


glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 *sizeof(float)));
glEnableVertexAttribArray(2);

	

glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


ownShader.use();
ownShader.setInt("ourTexture1", 0);
ownShader.setInt("ourTexture2", 1);





while(!glfwWindowShouldClose(window)){
processInput(window);
glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);

glm::mat4 trans = glm::mat4(1.0f);
trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
trans = glm::rotate(trans, (float)glfwGetTime(),glm::vec3(0.0f, 0.0f, 1.0f));
unsigned int transformLoc = glGetUniformLocation(ownShader.ID, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


ownShader.use();
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, texture2);
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
