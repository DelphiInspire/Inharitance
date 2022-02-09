#include "Body.h"

Parallelogram::Parallelogram(coordinates &&bottomLeftPos, coordinates &&topLeftPos,
                             coordinates &&bottomRightPos,coordinates &&topRightPos)
{
    verteces.push_back(bottomLeftPos);
    verteces.push_back(topLeftPos);
    verteces.push_back(bottomRightPos);
    verteces.push_back(topRightPos);
};

float Parallelogram::calculate_Perimeter()
{
	coordinates LRsideDifference{ verteces.at((size_t) vertecesID::topLeftVertece) - verteces.at((size_t)vertecesID::bottomLeftVertece) };
	coordinates BTsideDifference{ verteces.at((size_t)vertecesID::topLeftVertece) - verteces.at((size_t)vertecesID::topRightVertece) };
	float LRsideLength =  sqrtf(powf(LRsideDifference.x, 2) + powf(LRsideDifference.y, 2));
	float BTsideLength = sqrtf(powf(BTsideDifference.x, 2) + powf(BTsideDifference.y, 2));
	return 2 * LRsideLength + 2 * BTsideLength;
}

float Parallelogram::calculate_Area()
{
	float height = verteces.at((size_t)vertecesID::topLeftVertece).y - verteces.at((size_t)vertecesID::bottomLeftVertece).y;
	coordinates bottomSideDifference = verteces.at((size_t)vertecesID::bottomLeftVertece) - verteces.at((size_t)vertecesID::bottomRightVertece) ;
	float bottomSideLength = sqrtf(powf(bottomSideDifference.x, 2) + powf(bottomSideDifference.y, 2));
	return bottomSideLength * height;
}

coordinates Parallelogram::getCenter() const
{
	return coordinates((verteces.at((size_t) vertecesID::bottomLeftVertece) + verteces.at((size_t)vertecesID::topRightVertece)) / 2.0);
}

float Ellipse::calculate_Perimeter()
{
    return 2 * PI * sqrtf((powf(length, 2.0) + powf(width, 2.0)) / 8.0); ;
}

float Ellipse::calculate_Area()
{
    return PI * length * width / 4.0;
};

coordinates Ellipse::getCenter() const
{
    return coordinates{0.0, 0.0};
};

float Ball::calculate_Perimeter()
{
    return 2 * PI * radius;
}

float Ball::calculate_Area()
{
    return 4.0 * PI * powf(radius, 2);
}

float Ball::calculate_Volume()
{
     return 4.0 * PI * powf(radius, 3.0) / 3.0;
}

float Ball::calculate_SurfaceArea()
{
    return 4.0 * PI * powf(radius, 2.0);
}

coordinates Ball::getCenter() const
{
    return coordinates{0.0, 0.0, 0.0};
}

Box::Box(coordinates &front_bottomLeftVertex, coordinates &front_topLeftVertex,
         coordinates &front_bottomRightVertex,coordinates &front_topRightVertex,
         coordinates &back_bottomLeftVertex, coordinates &back_topLeftVertex,
         coordinates &back_bottomRightVertex, coordinates &back_topRightVertex)
{
    verteces.push_back(front_bottomLeftVertex);
    verteces.push_back(front_topLeftVertex);
    verteces.push_back(front_bottomRightVertex);
    verteces.push_back(front_topRightVertex);
    verteces.push_back(back_bottomLeftVertex);
    verteces.push_back(back_topLeftVertex);
    verteces.push_back(back_bottomRightVertex);
    verteces.push_back(back_topRightVertex);
    length = getEdgeLength(front_bottomLeftVertex, front_bottomRightVertex);
    width = getEdgeLength(front_bottomLeftVertex, back_bottomLeftVertex);
    height = getEdgeLength(front_bottomLeftVertex, front_topLeftVertex);
};

float Box::calculate_Perimeter()
{
    return 2 * (length + width);
};

float Box::calculate_Area()
{
    return length * width * height;
}

float Box::calculate_Volume()
{
    return length * width * height;
};

float Box::calculate_SurfaceArea()
{
    return 2.0 * (length * width + length * height + width * height);
};

coordinates Box::getCenter() const
{
    return coordinates(length / 2.0, width / 2.0, height / 2.0);
};

float Box::getEdgeLength(coordinates& firstVertex, coordinates& secondVertex) const
{
	return sqrtf(powf((firstVertex.x - secondVertex.x), 2) +
				powf((firstVertex.y - secondVertex.y), 2) +
				powf((firstVertex.z - secondVertex.z), 2));
}
