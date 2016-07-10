#pragma once

#include "HumanSpineElementDrawable.h"
#include "Disk.h"


namespace humanSpineSfDraw
{

	class DiskDrawable : public HumanSpineElementDrawable<Disk>
	{

	private:

		virtual void draw(RenderTarget &target, RenderStates states) const
		{
			states.transform *= getTransform();

			ConvexShape leftTriangle;
			leftTriangle.setPointCount(3);
			leftTriangle.setPoint(0, Vector2f(0, 0));
			leftTriangle.setPoint(1, Vector2f(-element->getWidth() / 2, -element->getHeight() / 2));
			leftTriangle.setPoint(2, Vector2f(-element->getWidth() / 2, element->getLeftHeight() - element->getHeight() / 2));

			ConvexShape rightTriangle;
			rightTriangle.setPointCount(3);
			rightTriangle.setPoint(0, Vector2f(0, 0));
			rightTriangle.setPoint(1, Vector2f(element->getWidth() / 2, -element->getHeight() / 2));
			rightTriangle.setPoint(2, Vector2f(element->getWidth() / 2, element->getRightHeight() - element->getHeight() / 2));

			if (selected)
			{
				leftTriangle.setFillColor(sf::Color::Yellow);
				rightTriangle.setFillColor(sf::Color::Yellow);
			}
			else
			{
				leftTriangle.setFillColor(sf::Color::Red);
				rightTriangle.setFillColor(sf::Color::Red);
				leftTriangle.setOutlineColor(sf::Color::Magenta);
				rightTriangle.setOutlineColor(sf::Color::Magenta);
				leftTriangle.setOutlineThickness(1.0f);
				rightTriangle.setOutlineThickness(1.0f);
			}

			target.draw(leftTriangle, states);
			target.draw(rightTriangle, states);
		}

	public:

		bool selected = false;

	};

}