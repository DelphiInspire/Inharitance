#include "Body.h"


float Parallelogram::calculate_Perimeter()
{
	coordinates LRsideDifference{ vertices["topLeftVertice"] - vertices["bottomLeftVertice"] };
	coordinates BTsideDifference{ vertices["topLeftVertice"] - vertices["topRightVertice"] };
	float LRsideLength =  sqrt(pow(LRsideDifference.x, 2) + pow(LRsideDifference.y, 2));
	float BTsideLength = sqrt(pow(BTsideDifference.x, 2) + pow(BTsideDifference.y, 2));
	return 2 * LRsideLength + 2 * BTsideLength;
}

float Parallelogram::calculate_Area()
{
	float height{ vertices["topLeftVertice"].y - vertices["bottomLeftVertice"].y };
	coordinates bottomSideDifference{ vertices["bottomLeftVertice"] - vertices["bottomRightVertice"] };
	float bottomSideLength = sqrt(pow(bottomSideDifference.x, 2) + pow(bottomSideDifference.y, 2));
	return bottomSideLength * height;
}

coordinates Parallelogram::getCenter()
{
	return coordinates((vertices["bottomLeftVertice"] + vertices["topRightVertice"]) / 2.0);
}

float Box::getEdgeLength(coordinates& firstVertex, coordinates& secondVertex)
{
	return sqrt(pow((firstVertex.x - secondVertex.x), 2) +
				pow((firstVertex.y - secondVertex.y), 2) +
				pow((firstVertex.z - secondVertex.z), 2));
}
