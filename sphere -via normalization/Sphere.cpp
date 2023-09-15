#include<math.h>
#include<glm/glm.hpp>
#include<iostream>
#include<vector>

struct Vertex{
	glm::vec3 position;
	glm::vec3 normal;
	};
class Sphere{
	public:
	glm::vec3 color;
	int smoothness = 0;
	std::vector<Vertex> vertices;

	Sphere(int smoothness,glm::vec3 color, float breakage, float bulgence){
		this->color = color;
		this->smoothness = smoothness;
		unsigned int largest_n = pow(2, smoothness);
		float unbreakage = 1 - breakage;
		for(int n=0;n<largest_n;n++){
			for(int i=0;i<(2*n +1);i++){
			float nearer_x = ((unbreakage*(float)((i/2)+1))+(breakage*(float)(largest_n - (i/2)-1)))/(float)largest_n;
			float farther_x = ((unbreakage*(float)((i/2)))+(breakage*(float)(largest_n - (i/2))))/(float) largest_n;
			float nearer_y = ((unbreakage*(float)(largest_n-n))+(breakage*(float)(n+1)))/(float)largest_n;
			float farther_y = ((unbreakage*(float)(largest_n-n-1))+(breakage*(float)(n+1)))/(float)largest_n;
			float nearer_z = ((unbreakage*(float)(((2*n-i)/2)+1))+(breakage*(float)(largest_n -((2*n-i)/2)-1)))/(float)largest_n;
			float farther_z = ((unbreakage*(float)(((2*n-i)/2)))+(breakage*(float)(largest_n-((2*n-i)/2))))/(float)largest_n;
			
			//vertices starting from top going clockwise		

			Vertex vertex1;
			Vertex vertex2;
			Vertex vertex3;
			
			
			if(i%2 == 0)//triangle looks upwards
			{
			vertex1.position = normalize_bulging(glm::vec3(farther_x, nearer_y, farther_z), bulgence);
			vertex2.position = normalize_bulging(glm::vec3(nearer_x, farther_y, farther_z), bulgence);
			vertex3.position = normalize_bulging(glm::vec3(farther_x, farther_y, nearer_z), bulgence);
			
			}
			else //triangle looks downwards
			{
			vertex1.position = normalize_bulging(glm::vec3(farther_x, nearer_y, nearer_z), bulgence);
			vertex2.position = normalize_bulging(glm::vec3(nearer_x, nearer_y, farther_z), bulgence);
			vertex3.position = normalize_bulging(glm::vec3(nearer_x, farther_y, nearer_z), bulgence);
			}
			glm::vec3 normal = getNormal(vertex1.position, vertex2.position, vertex3.position);
			vertex1.normal = normal;
			vertex2.normal = normal;
			vertex3.normal = normal;
			this->vertices.push_back(vertex1);
			this->vertices.push_back(vertex2);
			this->vertices.push_back(vertex3);
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

	glm::vec3 normalize_bulging(glm::vec3 raw_vec, float bulgence){
		glm::vec3 vec_x = glm::normalize(raw_vec);
		vec_x.x = raw_vec.x + (vec_x.x - raw_vec.x)*bulgence;
		vec_x.y = raw_vec.y + (vec_x.y - raw_vec.y)*bulgence;
		vec_x.z = raw_vec.z + (vec_x.z - raw_vec.z)*bulgence;
		return vec_x;
	}
	
	void copyToQuadrant(float x, float y, float z){
		for(int i=0;i < 3*pow(4, this->smoothness);i++){		Vertex vertex;
		vertex.position.x = this->vertices[i].position.x * x;
		vertex.normal.x = this->vertices[i].normal.x * x;
		vertex.position.y = this->vertices[i].position.y * y;
		vertex.normal.y = this->vertices[i].normal.y * y;
		vertex.position.z = this->vertices[i].position.z * z;
		vertex.normal.z = this->vertices[i].normal.z * z;
		
		this->vertices.push_back(vertex);

		}
	}
	Sphere(int smoothness,glm::vec3 color, float breakage){
		this->color = color;
		this->smoothness = smoothness;
		unsigned int largest_n = pow(2, smoothness);
		breakage = breakage * 10.0;
		for(int n=0;n<largest_n;n++){
			for(int i=0;i<(2*n +1);i++){
			float nearer_x = (((1.0-breakage)*(float)((i/2)+1))+(breakage*(float)(largest_n - (i/2)-1)))/(float)largest_n;
			float farther_x = (float)((i/2))/(float) largest_n;
			float nearer_y = (float)(largest_n-n)/(float)largest_n;
			float farther_y = (float)(largest_n-n-1)/(float)largest_n;
			float nearer_z = (float)(((2*n-i)/2)+1)/(float)largest_n;
			float farther_z = (float)(((2*n-i)/2))/(float)largest_n;
			
			//vertices starting from top going clockwise		

			Vertex vertex1;
			Vertex vertex2;
			Vertex vertex3;
			
			
			if(i%2 == 0)//triangle looks upwards
			{
			vertex1.position = glm::normalize(glm::vec3(farther_x, nearer_y, farther_z));
			vertex2.position = glm::normalize(glm::vec3(nearer_x, farther_y, farther_z));
			vertex3.position = glm::normalize(glm::vec3(farther_x, farther_y, nearer_z));
			
			}
			else //triangle looks downwards
			{
			vertex1.position = glm::normalize(glm::vec3(farther_x, nearer_y, nearer_z));
			vertex2.position = glm::normalize(glm::vec3(nearer_x, nearer_y, farther_z));
			vertex3.position = glm::normalize(glm::vec3(nearer_x, farther_y, nearer_z));
			}
			glm::vec3 normal = getNormal(vertex1.position, vertex2.position, vertex3.position);
			vertex1.normal = normal;
			vertex2.normal = normal;
			vertex3.normal = normal;
			this->vertices.push_back(vertex1);
			this->vertices.push_back(vertex2);
			this->vertices.push_back(vertex3);
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
	
	
	glm::vec3 getNormal(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3){
	glm::vec3 normal = glm::cross(vertex1 - vertex2, vertex1 - vertex3);
	
	normal.x *= -1;
	normal.y *= -1;
	normal.z *= -1;
		return normal;
	}

};
