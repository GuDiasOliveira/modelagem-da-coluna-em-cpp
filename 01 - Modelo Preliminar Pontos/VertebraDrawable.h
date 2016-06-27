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

			//Vector2f position = getPosition();
			RectangleShape shape;
			
			//shape.setPosition(position);
			shape.setOrigin(Vector2f(element->getWidth() / 2, element->getHeight() / 2));
			shape.setSize(Vector2f(element->getWidth(), element->getHeight()));
			//shape.setRotation(element->getAngle() * 180 / PI);

			shape.setFillColor(Color::White);
			shape.setOutlineColor(Color(50, 50, 50));
			shape.setOutlineThickness(3.5f);

			target.draw(shape, states);
		}

	};

}