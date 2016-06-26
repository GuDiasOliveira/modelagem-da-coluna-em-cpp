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
		angles[i] = PI / 2;
	}
	spine.setAngles(angles);
	spine.setHeadInclination(PI / 4);

	SpineDrawable spineDrw;
	spineDrw.element = &spine;
	spineDrw.position = Vector2f(window.getSize().x / 2, window.getSize().y - 30);

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