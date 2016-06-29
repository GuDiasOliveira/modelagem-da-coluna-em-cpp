#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "SpineDrawable.h"

using namespace std;
using namespace sf;
using namespace humanSpineSfDraw;


int main(int argc, char** argv)
{
	RenderWindow window(VideoMode(1280, 720), "Visualização em 2D da Coluna Vertebral", Style::Default);

	Spine spine;
	double angles[SPINE_COUNT_ALL_DISKS];
	for (int i = 0; i < SPINE_COUNT_ALL_DISKS; i++)
	{
		angles[i] = (PI / 2) / (SPINE_COUNT_ALL_DISKS - i);
	}
	spine.setAngles(angles);
	spine.setHeadInclination(PI / 4);

	SpineDrawable spineDrw;
	spineDrw.element = &spine;
	spineDrw.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y - 30));

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

		DiskDrawable test;
		test.setPosition(Vector2f(150, 200));
		test.element = new Disk;
		test.element->setHeight(100);
		test.element->setWidth(200);
		test.element->setDeltaHeight(-50);
		//test.setRotation(30);

		window.clear();
		window.draw(spineDrw);
		//window.draw(test);
		window.display();

		delete test.element;
	}

	return EXIT_SUCCESS;
}