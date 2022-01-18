#include<cmath>
#include<utility>
#include<vector>
#include<map>
#include<string>
constexpr float PI = 3.141592;

enum class pointPositions { bottomLeftVertice, topLeftVertice, bottomRightVertice, topRightVertice};

class coordinates
{
public:
	coordinates() {};
	coordinates(const float x, const float y, const float z = 0) : x{ x }, y{ y }, z{ z }{};

	coordinates(const coordinates& copyMember)
	{
		*this = copyMember;
	}

	coordinates(coordinates&& moveMember)
	{
		*this = std::forward<coordinates>(moveMember);
	}
	
	coordinates& operator=(coordinates&& moveMember)
	{
		if (this != &moveMember)
		{
			x = moveMember.x;
			y = moveMember.y;
			z = moveMember.z;
			moveMember.x = 0;
			moveMember.y = 0;
			moveMember.z = 0;
		}
		return *this;
	}


	coordinates& operator=(const coordinates& copyMember)
	{
		if (this != &copyMember)
		{
			x = copyMember.x;
			y = copyMember.y;
			z = copyMember.z;
		}
		return *this;
	}

	friend coordinates operator-(const coordinates& firstMember, const coordinates& secondMember)
	{
		return coordinates(firstMember.x - secondMember.x, firstMember.y - secondMember.y, firstMember.z - secondMember.z);
	}

	friend coordinates operator+(const coordinates& firstMember, const coordinates& secondMember)
	{
		return coordinates(firstMember.x + secondMember.x, firstMember.y + secondMember.y, firstMember.z + secondMember.z);
	}

	coordinates operator/(const float divider)
	{
		return coordinates(x / divider, y / divider, z / divider);
	}

	float x;
	float y;
	float z;
	~coordinates() {};
};




class Body2D
{
public:
	Body2D(){};
	virtual float calculate_Perimeter() = 0;
	virtual float calculate_Area() = 0;
	virtual coordinates getCenter() = 0;
	virtual ~Body2D() {};
};

class Body3D : public Body2D
{
public:
	Body3D(){};
	virtual float calculate_Volume() = 0;
	virtual float calculate_SurfaceArea() = 0;
	virtual ~Body3D() {};
};

class Parallelogram : public Body2D
{
public:
	Parallelogram(coordinates&& bottomLeftPos,  coordinates&& topLeftPos,
				  coordinates&& bottomRightPos, coordinates&& topRightPos)			  
	{
		vertices.insert(std::pair<std::string, coordinates>("bottomLeftVertice", bottomLeftPos));
		vertices.insert(std::pair<std::string, coordinates>("topLeftVertice", topLeftPos));
		vertices.insert(std::pair<std::string, coordinates>("bottomRightVertice", bottomRightPos));
		vertices.insert(std::pair<std::string, coordinates>("topRightVertice", topRightPos));
	};

	float calculate_Perimeter() override;
	float calculate_Area() override;
	coordinates getCenter() override;
	std::map<std::string, coordinates> getVertices()  { return vertices; };
	~Parallelogram() {};
private:
	std::map<std::string, coordinates> vertices;
};

class Ellipse : public Body2D
{
public:
	Ellipse(float length, float width) : length{ length }, width{width} {};
	float calculate_Perimeter() override { return 2 * PI * sqrt((pow(length, 2) + pow(width, 2)) / 8.0); };
	float calculate_Area() override { return PI * length * width / 4.0; };
	coordinates getCenter() override { return coordinates(0.0, 0.0); };
	~Ellipse() {};
private:
	float length;
	float width;
};

class Ball : public Body3D
{
public:
	Ball(const float radius) : radius{ radius } {};
	float calculate_Perimeter() override { return 2 * PI * radius; };
	float calculate_Area() override { return 4 * PI * pow(radius, 2); };
	float calculate_Volume() override { return 4.0 * PI * pow(radius, 3.0) / 3.0; };
	float calculate_SurfaceArea() override { return 4.0 * PI * pow(radius, 2.0); };
	coordinates getCenter() override { return coordinates(0.0, 0.0, 0.0); };
	~Ball() {};
private:
	float radius;
};

class Box : public Body3D
{
public:
	Box(coordinates& front_bLeftVertex, coordinates& front_tLeftVertex,
		coordinates& front_bRightVertex,coordinates& front_tRightVertex,
		coordinates& back_bLeftVertex,  coordinates& back_tLeftVertex,
		coordinates& back_bRightVertex, coordinates& back_tRightVertex):
		front_bottomLeftVertex{ front_bLeftVertex }, front_topLeftVertex{ front_tLeftVertex },
		front_bottomRightVertex{ front_bRightVertex }, front_topRightVertex{ front_tRightVertex },
		back_bottomLeftVertex{ back_bLeftVertex }, back_topLeftVertex{ back_tLeftVertex },
		back_bottomRightVertex{ back_bRightVertex }, back_topRightVertex{ back_tRightVertex }
	{
		vertices.push_back(front_bottomLeftVertex);
		vertices.push_back(front_topLeftVertex);
		vertices.push_back(front_bottomRightVertex);
		vertices.push_back(front_topRightVertex);
		vertices.push_back(back_bottomLeftVertex);
		vertices.push_back(back_topLeftVertex);
		vertices.push_back(back_bottomRightVertex);
		vertices.push_back(back_topRightVertex);
		length = getEdgeLength(front_bottomLeftVertex, front_bottomRightVertex);
		width = getEdgeLength(front_bottomLeftVertex, back_bottomLeftVertex);
		height = getEdgeLength(front_bottomLeftVertex, front_topLeftVertex);
	};
	float calculate_Perimeter() override { return 2 * (length + width); };
	float calculate_Area() override { return length * width * height; };
	float calculate_Volume() override { return length * width * height; };
	float calculate_SurfaceArea() override { return 2.0 * (length * width + length * height + width * height); };
	coordinates getCenter() { return coordinates(length / 2.0, width / 2.0, height / 2.0); };
	~Box() {};
private:
	std::vector<coordinates> vertices;
	float getEdgeLength(coordinates& firstVertex, coordinates& secondVertex);
	coordinates front_bottomLeftVertex;
	coordinates front_topLeftVertex;
	coordinates front_bottomRightVertex;
	coordinates front_topRightVertex;
	coordinates back_bottomLeftVertex;
	coordinates back_topLeftVertex;
	coordinates back_bottomRightVertex;
	coordinates back_topRightVertex;
	float length;
	float width;
	float height;
};
