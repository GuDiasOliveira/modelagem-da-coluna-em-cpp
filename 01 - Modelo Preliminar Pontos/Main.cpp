#pragma once

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

#include "SpineDrawable.h"

using namespace std;
using namespace sf;
using namespace humanSpineSfDraw;


double random(double min, double max)
{
	static random_device rand;
	double num = rand();
	num -= rand.min();
	num /= rand.max() - rand.min();
	num *= max - min;
	num += min;
	return num;
}


int main(int argc, char** argv)
{
	RenderWindow window(VideoMode(1280, 720), "Visualização em 2D da Coluna Vertebral", Style::Default);

	Spine spine;
	double angles[SPINE_COUNT_ALL_DISKS];
	angles[0] = PI / 2;
	for (int i = 1; i < SPINE_COUNT_ALL_DISKS; i++)
	{
		double deltaAngleMax = atan(2 * spine.getDisk(i - 1).getHeight() / SPINE_WIDTH);
		double deltaAngle = random(-deltaAngleMax, deltaAngleMax);
		angles[i] = angles[i - 1] + deltaAngle / 2.8;
		//angles[i] = PI / 4;
	}
	spine.setAngles(angles);
	spine.setHeadInclination(angles[SPINE_COUNT_ALL_DISKS - 1] - PI / 2);

	SpineDrawable spineDrw;
	spineDrw.element = &spine;
	spineDrw.setPosition(Vector2f(window.getSize().x / 2, 30));

	window.setVisible(true);
	while (window.isOpen())
	{
		Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.draw(spineDrw);
		window.display();
	}

	return EXIT_SUCCESS;
}