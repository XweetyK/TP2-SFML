#ifdef _DEBUG
	#include <vld.h>
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;
using namespace sf;
#define C_TAM 50
#define C_DIST 20
#define MIN 0
#define MAX 49

int main()
{
	RenderWindow window(sf::VideoMode(530, 320), "Treasure Hunter");
	window.setKeyRepeatEnabled(false);


	Font font;
	font.loadFromFile("PERTILI.TTF");
	string hintText = "Hint: ";
	Text gameHint;
	gameHint.setPosition(20, 5);
	gameHint.setFont(font);

	ostringstream ss;
	ostringstream ssB;

	int tim = 10;
	Text timeText;
	timeText.setPosition(370, 5);
	timeText.setFont(font);

	int score=0;
	Text scoreText;
	scoreText.setPosition(20, 250);
	scoreText.setFont(font);

	Texture block;
	block.loadFromFile("image.png");
	Texture found;
	found.loadFromFile("image2.png");
	Texture winner;
	winner.loadFromFile("win.png");
	Texture loser;
	loser.loadFromFile("lose.png");
	Texture fondoT;
	fondoT.loadFromFile("fondo.png");

	Sprite boxes[50];
	Sprite win;
	win.setTexture(winner);
	Sprite lose;
	lose.setTexture(loser);
	Sprite fondo;
	fondo.setTexture(fondoT);

	bool timestopper = false;
	bool winA = false;
	bool winB = false;
	bool loseA = false;

	for (int i = 0; i < 50; i++)
	{
		boxes[i].setTexture(block);
	}
	for (int i = 0; i < 11; i++)
	{
		boxes[i].setPosition(Vector2f((i * C_TAM) + C_DIST, C_TAM));
	}
	for (int i = 0; i < 10; i++)
	{
		boxes[i + 10].setPosition(Vector2f((i * C_TAM) + C_DIST, C_TAM + 50));
	}
	for (int i = 0; i < 10; i++)
	{
		boxes[i + 20].setPosition(Vector2f((i * C_TAM) + C_DIST, C_TAM + 100));
	}
	for (int i = 0; i < 10; i++)
	{
		boxes[i + 30].setPosition(Vector2f((i * C_TAM) + C_DIST, C_TAM + 150));
	}
	for (int i = 0; i < 10; i++)
	{
		boxes[i + 40].setPosition(Vector2f((i * C_TAM) + C_DIST, C_TAM + 200));
	}

	srand(time(0));

	int select = 0;
	int goal = (rand() % (MIN - MAX + 1)) + MIN;

	Clock clock;
	bool upDw;

	while (window.isOpen())
	{
		Event event;
		Time elapsed = clock.getElapsedTime();
		upDw = false;

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
			case Keyboard::Up:
				if (select >= 10)
					select -= 10;
				break;
			case Keyboard::Down:
				if (select<40)
					select += 10;
				break;
			case Keyboard::Left:
				if (select>0)
					select--;
				break;
			case Keyboard::Right:
				if (select<49)
					select++;
				break;
			}
			break;
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (goal > select)
			{
				if (select < 10 && goal < 10)
				{
					hintText = "Hint: Right";
					upDw = true;
				}
				if (select < 20 && select > 9 && goal < 20 && goal >9)
				{
					hintText = "Hint: Right";
					upDw = true;
				}
				if (select < 30 && select > 19 && goal < 30 && goal >19)
				{
					hintText = "Hint: Right";
					upDw = true;
				}
				if (select < 40 && select > 29 && goal < 40 && goal >29)
				{
					hintText = "Hint: Right";
					upDw = true;
				}
				if (select < 50 && select > 39 && goal < 50 && goal >39)
				{
					hintText = "Hint: Right";
					upDw = true;
				}
				if (upDw == false)
					hintText = "Hint: Down";
			}
			if (goal < select)
			{
				if (select < 10 && goal < 10)
				{
					hintText = "Hint: Left";
					upDw = true;
				}
				if (select < 20 && select > 9 && goal < 20 && goal >9)
				{
					hintText = "Hint: Left";
					upDw = true;
				}
				if (select < 30 && select > 19 && goal < 30 && goal >19)
				{
					hintText = "Hint: Left";
					upDw = true;
				}
				if (select < 40 && select > 29 && goal < 40 && goal >29)
				{
					hintText = "Hint: Left";
					upDw = true;
				}
				if (select < 50 && select > 39 && goal < 50 && goal >39)
				{
					hintText = "Hint: Left";
					upDw = true;
				}
				if (upDw == false)
					hintText = "Hint: Up";
			}
			if (select == goal)
			{
				hintText = "Hint: You Found It!";
				boxes[select].setTexture(found);
				winA = true;
				score += tim * 10;
				ssB.clear();
				ssB.str("");
				ssB << "Score: " << score;
				scoreText.setString(ssB.str());
			}

		}
		for (int i = 0; i < 50; i++)
		{
			if (i == select)
			{
				boxes[i].setColor(sf::Color(148, 213, 255));
			}
			else
			{
				boxes[i].setColor(sf::Color(255, 255, 255));
			}
		}

		gameHint.setString(hintText);
		if (timestopper == false)
		{
			if (elapsed.asSeconds() > 1.0)
			{
				tim--;
				elapsed = clock.restart();
			}
		}
		if (tim == 0) 
		{
			if(winA==false)
				loseA = true;
			if (winA == true)
				winB = true;
		}

		ss.clear();
		ss.str("");
		ss << "Time: " << tim;
		timeText.setString(ss.str());

		window.clear();
		window.draw(fondo);
		for (int i = 0; i < 50; i++) //draw boxes
		{
			window.draw(boxes[i]);
		}
		window.draw(gameHint);
		window.draw(timeText);
		if (winB)
		{
			window.draw(win);
			window.draw(scoreText);
		}
		if (loseA)
		{
			window.draw(lose);
		}
		window.display();
		sleep(seconds(0.1f));
	}

	return 0;
}