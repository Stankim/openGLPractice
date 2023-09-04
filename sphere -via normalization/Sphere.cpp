#include<math.h>
#include<glm/glm.hpp>
#include<iostream>
#include "Triangle.cpp"
class Sphere{
	public:
	int smoothness = 0;
	float vertices[1000000];
	long int number_of_vertices;
	long int sizeof_vertices;
	int vertex_counter = 0;
	Sphere(int smoothness){
		this->smoothness = smoothness;
		this->number_of_vertices = 8*9*pow(4, smoothness);
		this->sizeof_vertices = this->number_of_vertices * 4;
		unsigned int largest_n = pow(2, smoothness);
		for(int n=0;n<largest_n;n++){
			for(int i=0;i<(2*n +1);i++){
			float nearer_x = (float)((i/2)+1)/(float)largest_n;
			
			float farther_x = (float)((i/2))/(float) largest_n;
			float nearer_y = (float)(largest_n-n)/(float)largest_n;
			float farther_y = (float)(largest_n-n-1)/(float)largest_n;
			float nearer_z = (float)(((2*n-i)/2)+1)/(float)largest_n;
			float farther_z = (float)(((2*n-i)/2))/(float)largest_n;
			
			//vertices starting from top going clockwise
			if(i%2 == 0)//triangle looks upwards
			{
			
			copyToArray(glm::normalize(glm::vec3(farther_x, nearer_y, farther_z)));
			copyToArray(glm::normalize(glm::vec3(nearer_x, farther_y, farther_z)));
			
			copyToArray(glm::normalize(glm::vec3(farther_x, farther_y, nearer_z)));
			}
			else //triangle looks downwards
			{
			copyToArray(glm::normalize(glm::vec3(farther_x, nearer_y, nearer_z)));
			copyToArray(glm::normalize(glm::vec3(nearer_x, nearer_y, farther_z)));
			copyToArray(glm::normalize(glm::vec3(nearer_x, farther_y, nearer_z)));
			}
			}
		}
		copyToQuadrant(-1.0, 1.0, 1.0);
		copyToQuadrant(1.0, -1, 1);
		copyToQuadrant(1, 1, -1);
		copyToQuadrant(-1, -1, 1);
		copyToQuadrant(1, -1, -1);
		copyToQuadrant(-1, 1, -1);
		copyToQuadrant(-1, -1, -1);
		
	}
	
	void copyToArray(glm::vec3 vertex){
		this->vertices[this->vertex_counter] = vertex.x;		
		vertex_counter++;
		this->vertices[this->vertex_counter] = vertex.y;		
		vertex_counter++;
		this->vertices[this->vertex_counter] = vertex.z;

		vertex_counter++;
	}
	void copyToQuadrant(float x, float y, float z){
		for(int i=0;i < 9*pow(4, this->smoothness);){
		this->vertices[vertex_counter] = this->vertices[i] * x;
		i++;
		vertex_counter++;
		this->vertices[vertex_counter] = this->vertices[i] * y;
		i++;
		vertex_counter++;
		this->vertices[vertex_counter] = this->vertices[i] * z;
		i++;
		vertex_counter++;
		}
	}

};
