#include "Body.h"
#include <iostream>

int main()
{
	Parallelogram par(coordinates(1.0, 9.0), coordinates(-3.0, 6.0), coordinates(3.0, 9.0), coordinates(-1.0, 6.0));
	std::map<std::string, coordinates> a{ par.getVertices() };
	std::cout << a["bottomLeftVertice"].x;
	return 0;
}