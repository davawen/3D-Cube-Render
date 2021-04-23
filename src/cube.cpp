#include "cube.hpp"

Cube::Cube(Vector3 pos, Vector3 size, Vector3 rotation)
{
	this->pos = pos;
	this->size = size;
	this->rotation = rotation;

	this->buildVertices();
}

void Cube::buildVertices()
{
	this->vertices[0] = Vector3(this->pos.x,                this->pos.y,                this->pos.z               );
	this->vertices[1] = Vector3(this->pos.x + this->size.x, this->pos.y,                this->pos.z               );
	this->vertices[2] = Vector3(this->pos.x,                this->pos.y,                this->pos.z + this->size.z);
	this->vertices[3] = Vector3(this->pos.x + this->size.x, this->pos.y,                this->pos.z + this->size.z);
	this->vertices[4] = Vector3(this->pos.x,                this->pos.y + this->size.y, this->pos.z               );
	this->vertices[5] = Vector3(this->pos.x + this->size.x, this->pos.y + this->size.y, this->pos.z               );
	this->vertices[6] = Vector3(this->pos.x,                this->pos.y + this->size.y, this->pos.z + this->size.z);
	this->vertices[7] = Vector3(this->pos.x + this->size.x, this->pos.y + this->size.y, this->pos.z + this->size.z);

	//Center
	this->vertices[8] = Vector3(this->pos.x + this->size.x / 2, this->pos.y + this->size.y / 2, this->pos.z + this->size.z / 2);

	Matrix rotationX =
	{
		{1, 0, 0},
		{0, cosf(this->rotation.x), -sinf(this->rotation.x)},
		{0, sinf(this->rotation.x), cosf(this->rotation.x)}
	};

	Matrix rotationY =
	{
		{cosf(this->rotation.y), 0, -sinf(this->rotation.y)},
		{0, 1, 0},
		{0, sinf(this->rotation.y), cosf(this->rotation.y)}
	};
	
	Matrix rotationZ =
	{
		{cosf(this->rotation.z), -sinf(this->rotation.z), 0},
		{sinf(this->rotation.z), cosf(this->rotation.z), 0},
		{0, 0, 1}
	};

	Matrix rotationMatrix = matrixMultiplication(matrixMultiplication(rotationX, rotationY), rotationZ);

	for (auto &vertice : vertices)
	{
		try
		{
			vertice.rotate(rotationMatrix, this->pos + this->size * .5f);
		}
		catch (std::string error)
		{
			printf("%s\n", error.c_str());
		}
	}
}

void Cube::move(Vector3 amount)
{
	this->pos += amount;

	this->buildVertices();
}

void Cube::rotate(Vector3 amount)
{
	this->rotation += amount;

	this->buildVertices();
}

void Cube::draw(sf::RenderWindow &window, Vector3 cameraPos)
{
	sf::Vector2f vectors[9];
	sf::Color colors[9];

	int i = 0;
	for (auto &vertice : vertices)
	{
		Vector3 cPos = vertice - cameraPos;

		uint32_t fallOff = static_cast<uint32_t>(0xFF * (powf(1.005, -cPos.length())));

		colors[i] = sf::Color(0xFFFFFF00 + fallOff);

		Matrix proj =
			{
				{1, 0, 0},
				{0, 1, 0}};

		std::vector<float> product = matrixVectorMultiplication(proj, &cPos);

		vectors[i] = sf::Vector2f(product[0] + 300.f, product[1] + 300.f);

		// if(i == 0)
		// {
		// 	std::cout << vertices[0].toString() << "\n"
		// 			  << cPos.toString() << "\n"
		// 			  << "  x: " << vectors[0].x << "  y: " << vectors[0].y << "\n";
		// }

		i++;
	}

	sf::CircleShape circles[9];

	for (unsigned int i = 0; i < 9; i++)
	{
		circles[i].setRadius(5.f);
		circles[i].setOrigin(5.f, 5.f);
		circles[i].setPosition(vectors[i]);
		circles[i].setFillColor(colors[i]);
	}

	int lineIndexes[24];

#pragma region Connect vertices
	//Can't figure out how to automate this
	//Probably some sort of triangulation table

	lineIndexes[0] = 0;
	lineIndexes[1] = 1;
	lineIndexes[2] = 0;
	lineIndexes[3] = 2;
	lineIndexes[4] = 1;
	lineIndexes[5] = 3;
	lineIndexes[6] = 2;
	lineIndexes[7] = 3;
	lineIndexes[8] = 0;
	lineIndexes[9] = 4;
	lineIndexes[10] = 2;
	lineIndexes[11] = 6;
	lineIndexes[12] = 1;
	lineIndexes[13] = 5;
	lineIndexes[14] = 3;
	lineIndexes[15] = 7;
	lineIndexes[16] = 4;
	lineIndexes[17] = 5;
	lineIndexes[18] = 4;
	lineIndexes[19] = 6;
	lineIndexes[20] = 5;
	lineIndexes[21] = 7;
	lineIndexes[22] = 6;
	lineIndexes[23] = 7;

#pragma endregion

	sf::VertexArray lines(sf::PrimitiveType::Lines, 24);

	for (unsigned int i = 0; i < 24; i++)
	{
		lines[i].position = vectors[lineIndexes[i]];
		lines[i].color = colors[lineIndexes[i]];
	}

	for (auto &circle : circles)
	{
		window.draw(circle);
	}

	window.draw(lines);
}