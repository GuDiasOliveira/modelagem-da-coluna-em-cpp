#pragma once

#include "HumanSpineElementDrawable.h"
#include "Vertebra.h"


namespace humanSpineSfDraw
{

	class VertebraDrawable : public HumanSpineElementDrawable<Vertebra>
	{

	private:

		virtual void draw(RenderTarget &target, RenderStates states) const
		{
			states.transform *= getTransform();

			RectangleShape shape;
			
			shape.setOrigin(Vector2f(element->getWidth() / 2, element->getHeight() / 2));
			shape.setSize(Vector2f(element->getWidth(), element->getHeight()));

			shape.setFillColor(sf::Color::White);
			shape.setOutlineColor(sf::Color(50, 50, 50));
			shape.setOutlineThickness(1.0f);

			target.draw(shape, states);
		}

	};

}