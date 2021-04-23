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

		//uint32_t fallOff = static_cast<uint32_t>(0xFF * (powf(1.005, -cPos.length())));
		
		//Calculate shading
		
		//colors[i] = sf::Color(0xFFFFFF00 + fallOff);
		colors[i] = sf::Color(0xFFFFFF50);

		Matrix proj =
		{
			{1, 0, 0},
			{0, 1, 0}
		};

		std::vector<float> product = matrixVectorMultiplication(proj, &cPos);

		vectors[i] = sf::Vector2f(product[0] + 300.f, product[1] + 300.f);

		i++;
	}

	sf::CircleShape circles[9];

	for (unsigned int i = 0; i < 9; i++)
	{
		circles[i].setRadius(5.f);
		circles[i].setOrigin(5.f, 5.f);
		circles[i].setPosition(vectors[i]);
		// circles[i].setFillColor(colors[i]);
		circles[i].setFillColor(sf::Color(((randSeed(0xA21BEA + i, 0, 0xFF) << 24) + (randSeed(0xFFE89FF + i, 0, 0xFF) << 18) + (randSeed(102 + i, 0, 0xFF) << 8 ) + 0xFF)));
	}
	
	//First level of pain
	int lineIndexes[12][2] = 
	{
		{ 0, 1 },
		{ 0, 2 },
		{ 1, 3 },
		{ 2, 3 },
		{ 0, 4 },
		{ 2, 6 },
		{ 1, 5 },
		{ 3, 7 },
		{ 4, 5 },
		{ 4, 6 },
		{ 5, 7 },
		{ 6, 7 }
	};
	//Can't figure out how to automate this
	//Probably some sort of triangulation table

	//Next level of pain
	int triangleIndexes[12][3] = 
	{
		{ 0, 1, 2 },
		{ 1, 2, 3 },
		{ 0, 2, 4 },
		{ 2, 4, 6 },
		{ 2, 6, 7 },
		{ 2, 3, 7 },
		{ 4, 5, 6 },
		{ 5, 6, 7 },
		{ 3, 5, 7 },
		{ 1, 3, 5 },
		{ 0, 1, 4 },
		{ 1, 4, 5 }
	};
	
	sf::VertexArray lines(sf::PrimitiveType::Lines, 24);
	sf::VertexArray triangles(sf::PrimitiveType::Triangles, 36); //36
	
	for(unsigned int i = 0; i < 12; i++)
	{
		lines[i*2    ].position = vectors[lineIndexes[i][0]];
		lines[i*2 + 1].position = vectors[lineIndexes[i][1]];
		
		lines[i*2    ].color = sf::Color::Red;
		lines[i*2 + 1].color = sf::Color::Red;
		
		triangles[i*3    ].position = vectors[triangleIndexes[i][0]];
		triangles[i*3 + 1].position = vectors[triangleIndexes[i][1]];
		triangles[i*3 + 2].position = vectors[triangleIndexes[i][2]];
		
		triangles[i*3    ].color = circles[triangleIndexes[i][0]].getFillColor();//sf::Color::White;
		triangles[i*3 + 1].color = circles[triangleIndexes[i][1]].getFillColor();//sf::Color::White;
		triangles[i*3 + 2].color = circles[triangleIndexes[i][2]].getFillColor();//sf::Color::White;
	}

	window.draw(triangles);
	window.draw(lines);
	for (auto &circle : circles)
	{
		window.draw(circle);
	}
}