#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


int main(int argc, char** argv)
{
	RenderWindow window(VideoMode(640, 480), "Visualiza��o em 2D da Coluna Vertebral", Style::Default);

	// TODO

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
			// TODO
		}

		// TODO
	}

	return EXIT_SUCCESS;
}