//=======================================================
//Include guard
#ifndef CUBE_H
#define CUBE_H
//=======================================================

#include <SFML/Graphics.hpp>
#include <vector>

#include "math/vector.hpp"
#include "math/matrix.hpp"
#include "functions/random.hpp"

class Cube
{
	Vector3 vertices[9];
	Vector3 pos;
	Vector3 size;
	Vector3 rotation;

	void buildVertices();

public:
	Cube(Vector3 pos, Vector3 size, Vector3 rotation);

	void move(Vector3 amount);

	void rotate(Vector3 amount);

	void draw(sf::RenderWindow &window, Vector3 cameraPos);
};

#endif