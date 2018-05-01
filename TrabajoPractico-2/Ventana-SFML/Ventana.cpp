#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(450, 450), "SFML works!");
	sf::Texture texture;
	texture.loadFromFile("image.png");

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(0, 255, 200));

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		sf::Time elapsed = clock.restart();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		switch (event.type) 
		{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Up:
						sprite.move(0, -100*elapsed.asSeconds());
						break;
					case sf::Keyboard::Down:
						sprite.move(0, 100 * elapsed.asSeconds());
						break;
					case sf::Keyboard::Left:
						sprite.move(-100 * elapsed.asSeconds(), 0);
						break;
					case sf::Keyboard::Right:
						sprite.move(100 * elapsed.asSeconds(), 0);
						break;
				}
				break;
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}