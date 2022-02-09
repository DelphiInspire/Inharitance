#include "Body.h"

int main()
{
	Parallelogram par(coordinates(1.0, 9.0), coordinates(-3.0, 6.0), coordinates(3.0, 9.0), coordinates(-1.0, 6.0));
	const std::vector<const coordinates>* a{ par.getVerteces() };
	return 0;
}