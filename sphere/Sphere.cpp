#include<math.h>
#include<glm/glm.hpp>
#include<iostream>
class Sphere{
	public:
	int smoothness = 0;
	float vertices[1000000];
	long int number_of_vertices;
	long int sizeof_vertices;
	int vertex_counter = 0;
	Sphere(int smoothness){
		this->number_of_vertices = 9*pow(4, smoothness);
		this->sizeof_vertices = this->number_of_vertices * 4;
		
		float center_angle = glm::radians(90.0 / ((float)smoothness +1.0));

		for(int n=0;n<pow(2, smoothness);n++){
			for(int i=0;i<(2*n +1);i++){
			float right_theta = glm::radians(90.0) - (float)((2*n-i)/2) * center_angle;
			float left_theta = right_theta + center_angle;
			float right_phi;
			float left_phi;
			left_phi = glm::radians(90.0) - (float)(i/2) * center_angle;
			right_phi = left_phi  - center_angle;
			if(i%2 == 0)//triangle looks upwards
			{
			copyToArray(calculateVertex(left_theta, left_phi)); //lower left vertex
			copyToArray(calculateVertex(right_theta, left_phi)); //the only upper vertex
			copyToArray(calculateVertex(right_theta, right_phi));//the right vertex
			}
			else //triangle looks downwards
			{
			copyToArray(calculateVertex(left_theta, left_phi)); //the left upper vertex
			copyToArray(calculateVertex(right_theta, right_phi));//the right upper vertex
			copyToArray(calculateVertex(left_theta, right_phi)); //the only lower vertex
			}
			}
		}
	}
	
	glm::vec3 calculateVertex(float theta, float phi){
		glm::vec3 vertex=glm::vec3();
		vertex.x = sin(theta)* cos(phi);
		vertex.y = sin(theta) * sin(phi);
		vertex.z = cos(theta);
		return vertex;
	}
	void copyToArray(glm::vec3 vertex){
		this->vertices[this->vertex_counter] = vertex.x;
		vertex_counter++;
		this->vertices[this->vertex_counter] = vertex.y;
		vertex_counter++;
		this->vertices[this->vertex_counter] = vertex.z;
		vertex_counter++;
	}

};
