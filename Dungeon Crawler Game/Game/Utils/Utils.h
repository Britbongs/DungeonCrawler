#ifndef UTILS_H
#define UTILS_H

#define PI 3.14159

#include "..\Entities\Entity.h"

struct SATProjection
{
	SATProjection(double min, double max)
		: min(min), max(max)
	{

	}
	double min;
	double max;
};

bool overlaps(SATProjection proj1, SATProjection proj2);

bool collides(Entity* const entityOne, Entity* const entityTwo); 

SATProjection getProjection(sf::Vector2f normal, Entity* const entity); 

float random(float a, float b);

float radians(float a); 

float degrees(float a);

float lerp(float v1, float v2, float mod);

#endif