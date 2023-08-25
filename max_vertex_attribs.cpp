#include<glad/glad.h>
#include<iostream>

int main(){

int max_attributes;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attributes);
std::cout<<"maximum vertex attributes " << max_attributes<<std::endl;

}
