#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>

#include "functions/random.hpp"

#include "math/matrix.hpp"
#include "math/vector.hpp"
#include "cube.hpp"

constexpr float PI = 3.14159265359;

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Cube", sf::Style::Close | sf::Style::Titlebar);

	Cube cube(Vector3(-100.f, -100.f, 100.f), Vector3(200.f, 200.f, 200.f), Vector3());
	
	Vector3 cameraPos(0.f, 0.f, 0.f);
	
	sf::Clock deltaClock;
	sf::Clock timePassed;
	
	float randomRotation = 1.f;
	
	sf::Font font;
	
	if(!font.loadFromFile("arial.ttf"))
	{
		return 0;
	}
	
	sf::Text fpsText;
	
	fpsText.setFont(font);
	fpsText.setCharacterSize(16);
	fpsText.setFillColor(sf::Color::White);
	
	while(window.isOpen())
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
		
		randomRotation += (static_cast<float>(rand() % 100) - 50.f) / 1000.f * dt;

		cube.rotate(Vector3(PI * dt * .4 * randomRotation, PI * dt * .6 * randomRotation, PI * dt * .34 * randomRotation));

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) cube.rotate(Vector3(-PI / 2 * dt));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) cube.rotate(Vector3(PI/2 * dt));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) cube.rotate(Vector3(0.f, -PI/2 * dt));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) cube.rotate(Vector3(0.f, PI/2 * dt));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)) cube.rotate(Vector3(0.f, 0.f, PI/2 * dt));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) cube.rotate(Vector3(0.f, 0.f, -PI/2 * dt));
		
		window.clear();
		
		fpsText.setString("FPS: " + std::to_string(1/dt));
		
		window.draw(fpsText);
		
		cube.draw(
			window,
			cameraPos
		);

		window.display();
	}

	return 0;
}