#pragma once

#include "HumanSpineElementDrawable.h"


namespace humanSpineSfDraw
{

	class SacroCoccyxDrawable : public HumanSpineElementDrawable<Vector2f>
	{

	private:

		virtual void draw(RenderTarget &target, RenderStates states) const
		{
			states.transform *= getTransform();
			//Vector2f position = getPosition();

			ConvexShape shape;
			shape.setPointCount(3);
			shape.setPoint(0, Vector2f(0, element->y));
			shape.setPoint(1, Vector2f(0, -element->x / 2));
			shape.setPoint(2, Vector2f(0, element->x / 2));
			//shape.setPosition(position);
			shape.setFillColor(Color::White);
			shape.setOutlineColor(Color(60, 60, 60));
			shape.setOutlineThickness(1.0f);
			
			target.draw(shape, states);
		}

	};

}