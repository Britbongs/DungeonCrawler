#include "Utils.h"

bool overlaps(SATProjection proj1, SATProjection proj2)
{//Checks if two values overlap for SAT collision detection
	return(proj1.max >= proj2.min && proj1.min < proj2.max);
}

bool collides(Entity* const entityOne, Entity* const entityTwo)
{//Function which  uses the separating axis theorem to detect for collisions between two entities
	//Projection getProjection(const sf::Vector2f&, const Square&);
	std::vector<sf::Vector2f> axes1(entityOne->getVertexCount());
	std::vector<sf::Vector2f> axes2(entityTwo->getVertexCount());

	for (int i(0); i < entityOne->getVertexCount(); ++i)
	{//Loop through the first shape and get all normals to each side
		int index(0);
		(i + 1) == entityOne->getVertexCount() ? index = 0 : index = i + 1;

		axes1[i] = entityOne->getNormal(i, index);
	}

	for (int i(0); i < entityTwo->getVertexCount(); ++i)
	{//Loop through the second shape and get all normals to each side
		int index(0);
		(i + 1) == entityTwo->getVertexCount() ? index = 0 : index = i + 1;

		axes2[i] = entityTwo->getNormal(i, index);
	}

	for (int i(0); i < axes1.size(); ++i)
	{//Project shape2 onto shape1's axis and determine if there's a gap
		sf::Vector2f normal(axes1[i]);

		SATProjection proj1(getProjection(normal, entityOne)); //max and minimum values of the first shape projection
		SATProjection proj2(getProjection(normal, entityTwo)); //max and minimum values of the second shape projection


		if (!overlaps(proj1, proj2))
			return false;
	}

	for (int i(0); i < axes2.size(); ++i)
	{
		sf::Vector2f normal(axes2[i]);

		SATProjection proj1(getProjection(normal, entityOne)); //max and minimum values of the first shape projection
		SATProjection proj2(getProjection(normal, entityTwo)); //max and minimum values of the second shape projection


		if (!overlaps(proj1, proj2))
			return false;
	}

	return(true);
}

SATProjection getProjection(sf::Vector2f normal, Entity* const entity)
{
	double min = dotProduct(normal, entity->getVertexGlobalPosition(0));
	double max = min;

	for (int i(1); i < entity->getVertexCount(); ++i)
	{//project each vertex of the shape onto the normal
		//then calculate the maximum and minimum values in the array and return those
		//as a projection
		double dp = dotProduct(normal, entity->getVertexGlobalPosition(i));

		if (dp < min)
			min = dp;
		else if (dp > max)
			max = dp;

	}
	return(SATProjection(min, max));
}

float random(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

float radians(float a)
{
	return((PI / 180.f) *a);
}

float degrees(float a)
{
	return((180.f / PI) * a);
}

float lerp(float v1, float v2, float mod)	
{
	return(v1 + ((v2 - v1) * mod));
}