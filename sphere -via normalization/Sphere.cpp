#include<math.h>
#include<glm/glm.hpp>
#include<iostream>

class Sphere{
	public:
	glm::vec3 color;
	int smoothness = 0;
	float vertices[1000000];
	float normals[1000000];
	long int number_of_vertices;
	long int sizeof_vertices;
	int vertex_counter = 0;
	int normals_counter = 0;
	Sphere(int smoothness,glm::vec3 color){
		this->color = color;
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
			glm::vec3 normal;
			glm::vec3 vertex1;
			glm::vec3 vertex2;
			glm::vec3 vertex3;
			if(i%2 == 0)//triangle looks upwards
			{
			vertex1 = glm::normalize(glm::vec3(farther_x, nearer_y, farther_z));
			vertex2 = glm::normalize(glm::vec3(nearer_x, farther_y, farther_z));
			vertex3 = glm::normalize(glm::vec3(farther_x, farther_y, nearer_z));
			copyToArray(vertex1);
			copyToArray(vertex2);
			copyToArray(vertex3);
			}
			else //triangle looks downwards
			{
			vertex1 = glm::normalize(glm::vec3(farther_x, nearer_y, nearer_z));
			vertex2 = glm::normalize(glm::vec3(nearer_x, nearer_y, farther_z));
			vertex3 = glm::normalize(glm::vec3(nearer_x, farther_y, nearer_z));
			copyToArray(vertex1);
			copyToArray(vertex2);
			copyToArray(vertex3);
			}
			normal = getNormal(vertex1, vertex2, vertex3);
			copyToNormals(normal);
			copyToNormals(normal);
			copyToNormals(normal);
			}
		}
		copyToQuadrant(-1.0, 1.0, 1.0);
		copyToQuadrant(1.0, -1, 1);
		copyToQuadrant(1, 1, -1);
		copyToQuadrant(-1, -1, 1);
		copyToQuadrant(1, -1, -1);
		copyToQuadrant(-1, 1, -1);
		copyToQuadrant(-1, -1, -1);
		
		copyNormalsToQuadrant(-1.0, 1.0, 1.0);
		copyNormalsToQuadrant(1.0, -1, 1);
		copyNormalsToQuadrant(1, 1, -1);
		copyNormalsToQuadrant(-1, -1, 1);
		copyNormalsToQuadrant(1, -1, -1);
		copyNormalsToQuadrant(-1, 1, -1);
		copyNormalsToQuadrant(-1, -1, -1);
		
	}
	void copyToNormals(glm::vec3 vertex){
		this->normals[this->normals_counter] = vertex.x;		
		normals_counter++;
		this->normals[this->normals_counter] = vertex.y;		
		normals_counter++;
		this->normals[this->normals_counter] = vertex.z;		
		normals_counter++;
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
	
	void copyNormalsToQuadrant(float x, float y, float z){
		for(int i=0;i < 9*pow(4, this->smoothness);){
		this->normals[normals_counter] = this->normals[i] * x;
		i++;
		normals_counter++;
		this->normals[normals_counter] = this->normals[i] * y;
		i++;
		normals_counter++;
		this->normals[normals_counter] = this->normals[i] * z;
		i++;
		normals_counter++;
		}
	}
	
	
	glm::vec3 getNormal(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3){
		return glm::normalize(glm::cross(vertex1 - vertex2, vertex2 - vertex3));
	}

};
