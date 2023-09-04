#include<math.h>
#include <glm/glm.hpp>
class Polygon{
	public:
	glm::vec3 center;
	float radius;
	int sides;
	float vertices[10000];
	long int number_of_vertices;
	long int sizeof_vertices;
	Polygon(int sides){
		this->sides = sides;
		this->number_of_vertices = sides * 3;
		this->sizeof_vertices = sides * 36;
		float center_angle = glm::radians(360.0 / (float)sides);
		for(int i = 0;i<sides; i++)
		{
			int tri_index=i*9;
			vertices[tri_index] = 0;
			vertices[tri_index+1] = 0;
			vertices[tri_index+2] = 0;
			vertices[tri_index+3] = cos(i*center_angle);
			vertices[tri_index+4] = sin(i*center_angle);
			vertices[tri_index+5] = 0;
			vertices[tri_index+6] = cos((i+1)*center_angle);
			vertices[tri_index+7] = sin((i+1)*center_angle);
			vertices[tri_index+8] = 0;
			
		}
		
		
	}
		
};
