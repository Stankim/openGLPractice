#include<glm/glm.hpp>




class Triangle{
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
	Triangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3){
	this->vertex1 = vertex1;
	this->vertex2 = vertex2;
	this->vertex3 = vertex3;
}
	glm::vec3 getNormal(){
		return glm::normalize(glm::cross(this->vertex2 - this->vertex1, this->vertex3 - this->vertex2));
	}
