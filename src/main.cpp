#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>

#include "matrix.hpp"
#include "vector.hpp"

constexpr float PI = 3.14159265359;

class Cube
{
	Vector3 vertices[9];
	Vector3 pos;
	Vector3 size;
	Vector3 rotation;

	void buildVertices()
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
		this->vertices[8] = Vector3(this->pos.x + this->size.x/2, this->pos.y + this->size.y/2, this->pos.z + this->size.z/2);

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

		for(auto &vertice : vertices)
		{
			try
			{
				vertice.rotate(rotationMatrix, this->pos + this->size * .5f);
			}
			catch(std::string error)
			{
				printf("%s\n", error.c_str());
			}
		}
	}
	
public:
	Cube(Vector3 pos, Vector3 size, Vector3 rotation)
	{
		this->pos = pos;
		this->size = size;
		this->rotation = rotation;
		
		this->buildVertices();
	}
	
	void move(Vector3 amount)
	{
		this->pos += amount;
		
		this->buildVertices();
	}
	
	void rotate(Vector3 amount)
	{
		this->rotation += amount;
		
		this->buildVertices();
	}
	
	void draw(sf::RenderWindow &window, Vector3 cameraPos)
	{
		sf::Vector2f vectors[9];
		sf::Color distances[9];
		
		int i = 0;
		for(auto &vertice : vertices)
		{
			Vector3 cPos = vertice - cameraPos;

			uint32_t fallOff = static_cast<uint32_t>(0xFF * (powf(1.005, -cPos.length())));

			distances[i] = sf::Color(0xFFFFFF00 + fallOff);

			Matrix proj =
			{
				{1, 0, 0},
				{0, 1, 0}
			};

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
		
		for(unsigned int i = 0; i < 9; i++)
		{
			circles[i].setRadius(5.f);
			circles[i].setOrigin(5.f, 5.f);
			circles[i].setPosition(vectors[i]);
			circles[i].setFillColor(distances[i]);
		}
		
		int lineIndexes[24];
		
		
		
		sf::VertexArray lines(sf::PrimitiveType::Lines, 24);

		lines[0].position = vectors[0];
		lines[0].color = sf::Color::Red;
		lines[1].position = vectors[1];
		lines[1].color = distances[1];

		lines[2].position = vectors[0];
		lines[2].color = sf::Color::Red;
		lines[3].position = vectors[2];
		lines[3].color = distances[2];

		lines[4].position = vectors[1];
		lines[4].color = distances[1];
		lines[5].position = vectors[3];
		lines[5].color = distances[3];

		lines[6].position = vectors[2];
		lines[6].color = distances[2];
		lines[7].position = vectors[3];
		lines[7].color = distances[3];

		lines[8].position = vectors[0];
		lines[8].color = sf::Color::Red;
		lines[9].position = vectors[4];
		lines[9].color = distances[4];
		
		lines[10].position = vectors[2];
		lines[10].color = distances[2];
		lines[11].position = vectors[6];
		lines[11].color = distances[6];
		
		lines[12].position = vectors[1];
		lines[12].color = distances[1];
		lines[13].position = vectors[5];
		lines[13].color = distances[5];
		
		lines[14].position = vectors[3];
		lines[14].color = distances[3];
		lines[15].position = vectors[7];
		lines[15].color = distances[7];
		
		lines[16].position = vectors[4];
		lines[16].color = distances[4];
		lines[17].position = vectors[5];
		lines[17].color = distances[5];
		
		lines[18].position = vectors[4];
		lines[18].color = distances[4];
		lines[19].position = vectors[6];
		lines[19].color = distances[6];
		
		lines[20].position = vectors[5];
		lines[20].color = distances[5];
		lines[21].position = vectors[7];
		lines[21].color = distances[7];
		
		lines[22].position = vectors[6];
		lines[22].color = distances[6];
		lines[23].position = vectors[7];
		lines[23].color = distances[7];

		for (auto &circle : circles)
		{
			window.draw(circle);
		}
		
		window.draw(lines);
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Cube", sf::Style::Close | sf::Style::Titlebar);

	Cube cube(Vector3(-100.f, -100.f, 100.f), Vector3(200.f, 200.f, 200.f), Vector3());
	
	Vector3 cameraPos(0.f, 0.f, 0.f);
	Vector3 cameraAngle(0.f, 0.f, 0.f);
	
	sf::Clock deltaClock;
	sf::Clock timePassed;
	
	float randomRotation = 1.f;
	
	while (window.isOpen())
	{
		float dt = deltaClock.restart().asSeconds();
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) cameraPos += Vector3(50.f*dt);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  cameraPos -= Vector3(50.f*dt);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  cameraPos += Vector3(0.f, 50.f*dt);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    cameraPos -= Vector3(0.f, 50.f*dt);
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))     cameraPos += Vector3(0.f, 0.f, 50.f*dt);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))     cameraPos -= Vector3(0.f, 0.f, 50.f*dt);
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))     cameraAngle.y -= PI/2 * dt;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))     cameraAngle.y += PI/2 * dt;
		
		randomRotation += (static_cast<float>(rand() % 100) - 50.f) / 1000.f * dt;

		cube.rotate(Vector3(PI * dt * .4 * randomRotation, PI * dt * .6 * randomRotation, PI * dt * .34 * randomRotation));

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) cube.rotate(Vector3(-PI / 2 * dt));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) cube.rotate(Vector3(PI/2 * dt));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) cube.rotate(Vector3(0.f, -PI/2 * dt));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) cube.rotate(Vector3(0.f, PI/2 * dt));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)) cube.rotate(Vector3(0.f, 0.f, PI/2 * dt));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) cube.rotate(Vector3(0.f, 0.f, -PI/2 * dt));
		
		window.clear();

		cube.draw(
			window,
			cameraPos
		);

		window.display();
	}

	return 0;
}