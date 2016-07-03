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
	double angles[SPINE_COUNT_ALL_DISKS + 1];
	angles[0] = PI / 2;
	for (int i = 1; i < SPINE_COUNT_ALL_DISKS; i++)
	{
		double deltaAngleMax = spine.getMaxDeltaAngle(i - 1);
		double deltaAngle = random(-deltaAngleMax, deltaAngleMax);
		//double deltaAngle = deltaAngleMax;
		angles[i] = angles[i - 1] + deltaAngle;
		//angles[i] = PI / 4;
		if (angles[i] > 2 * PI)
			angles[i] -= 2 * PI;
	}
	int set = spine.setAngles(angles);
	cout << "De " << SPINE_COUNT_ALL_DISKS << " ângulos, " << set << " foram setados" << endl;
	spine.setHeadInclination(angles[SPINE_COUNT_ALL_DISKS]);

	SpineDrawable spineDrw;
	spineDrw.element = &spine;
	spineDrw.setPosition(Vector2f(window.getSize().x / 2, 100));

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