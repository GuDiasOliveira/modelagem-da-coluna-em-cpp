#pragma once

#include "HumanSpineElementDrawable.h"
#include "Head.h"


namespace humanSpineSfDraw
{

	class HeadDrawable : public HumanSpineElementDrawable<Head>
	{

	private:

		virtual void draw(RenderTarget &target, RenderStates states) const
		{
			CircleShape shape;
			shape.setRadius(element->getRadius());
			shape.setFillColor(Color::White);
			shape.setOutlineColor(Color(50, 50, 50));
			shape.setOutlineThickness(3.5f);
			
			ConvexShape eye;
			eye.setPointCount(3);
			eye.setPoint(0, Vector2f(0, 0));
			eye.setPoint(1, Vector2f(element->getRadius(), -element->getRadius() / 8));
			eye.setPoint(2, Vector2f(element->getRadius(), element->getRadius() / 8));
			eye.setFillColor(Color::Blue);
			eye.setRotation(element->getAngle());

			target.draw(shape, states);
			target.draw(eye, states);
		}

	};

}