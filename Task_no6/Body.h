#include<cmath>
#include<vector>

constexpr float PI = 3.141592;

enum class pointPositions { bottomLeftVertice, topLeftVertice, bottomRightVertice, topRightVertice};

class coordinates
{
public:
	coordinates() noexcept : x{0.0},   y{0.0}, z{0.0}{};
	coordinates(const float x, const float y, const float z = 0) : x{ x }, y{ y }, z{ z } {};

	friend coordinates operator-(const coordinates& firstMember, const coordinates& secondMember)
	{
		return coordinates{firstMember.x - secondMember.x, firstMember.y - secondMember.y, firstMember.z - secondMember.z};
	}

	friend coordinates operator+(const coordinates& firstMember, const coordinates& secondMember)
	{
		return coordinates{firstMember.x + secondMember.x, firstMember.y + secondMember.y, firstMember.z + secondMember.z};
	}

	coordinates operator/(const float divider) const
	{
		return coordinates{x / divider, y / divider, z / divider};
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
	virtual coordinates getCenter() const = 0;
	virtual ~Body2D() {};
protected:
    coordinates centerCoordinates;
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
				  coordinates&& bottomRightPos, coordinates&& topRightPos);
	float calculate_Perimeter() override;
	float calculate_Area() override;
	coordinates getCenter() const override;
    const std::vector<const coordinates>* getVerteces() const {return &verteces;};
	~Parallelogram() {};
private:
    std::vector<const coordinates> verteces;
    enum class vertecesID{bottomLeftVertece = 0, topLeftVertece, bottomRightVertece, topRightVertece};
};

class Ellipse : public Body2D
{
public:
	Ellipse(float length, float width) : length{ length }, width{width} {};
	float calculate_Perimeter() override;
	float calculate_Area() override;
	coordinates getCenter()  const  override;
	~Ellipse() {};
private:
	float length;
	float width;
};

class Ball : public Body3D
{
public:
	explicit Ball(const float radius) : radius{ radius } {};
	float calculate_Perimeter() override;
	float calculate_Area() override;
	float calculate_Volume() override;
	float calculate_SurfaceArea() override;
	coordinates getCenter() const override;
	~Ball() {};
private:
	float radius;
};

class Box : public Body3D
{
public:
	Box(coordinates& front_bottomLeftVertex, coordinates& front_topLeftVertex,
		coordinates& front_bottomRightVertex,coordinates& front_topRightVertex,
		coordinates& back_bottomLeftVertex,  coordinates& back_topLeftVertex,
		coordinates& back_bottomRightVertex, coordinates& back_topRightVertex);

	float calculate_Perimeter() override;
	float calculate_Area() override;
	float calculate_Volume() override;
	float calculate_SurfaceArea() override;
    const std::vector<const coordinates>* getVerteces() const {return &verteces;};
	coordinates getCenter() const override;
	~Box() {};
private:
	std::vector<const coordinates> verteces;
    enum class vertecesID {front_bottomLeftVertex = 0, front_topLeftVertex, front_bottomRightVertex, front_topRightVertex,
                            back_bottomLeftVertex, back_topLeftVertex, back_bottomRightVertex, back_topRightVertex};
	float length;
	float width;
	float height;
private:
    float getEdgeLength(coordinates& firstVertex, coordinates& secondVertex) const;
};
