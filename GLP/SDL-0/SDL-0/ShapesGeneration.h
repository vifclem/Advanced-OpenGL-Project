#pragma once
#include <vector>
#include "Vector2F.h"

using namespace std;

inline void CreateRectangle(vector<float>& vertices, Vector2F center, Vector2F dimensions) {

	vertices.push_back(center.x - dimensions.x/2);
	vertices.push_back(center.y - dimensions.y/2);

	vertices.push_back(center.x - dimensions.x / 2);
	vertices.push_back(center.y + dimensions.y / 2);

	vertices.push_back(center.x + dimensions.x / 2);
	vertices.push_back(center.y + dimensions.y / 2);

	vertices.push_back(center.x + dimensions.x / 2);
	vertices.push_back(center.y - dimensions.y / 2);
}

inline void CreateEllipse(vector<float>& vertices, Vector2F center, Vector2F dimensions, int pointsCount)
{
	float theta = 2 * 3.1415926 / pointsCount;
	float cosine = cosf(theta);
	float sine = sinf(theta);


	float x = 1;//we start at angle = 0 
	float y = 0;
	float t = x;

	for (int vert = 0; vert < pointsCount; vert++)
	{
		//apply radius and offset
		vertices.push_back(x * dimensions.x + center.x);
		vertices.push_back(y * dimensions.y + center.y);

		//apply the rotation matrix
		t = x;
		x = cosine * x - sine * y;
		y = sine * t + cosine * y;
	}
}


inline void CreateCircle(vector<float>& vertices, Vector2F center, float radius, int pointsCount) {
	CreateEllipse(vertices, center, Vector2F(radius, radius), pointsCount);
}
