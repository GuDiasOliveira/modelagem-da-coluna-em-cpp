#pragma once

#include<SFML/Graphics.hpp>

#include "Vertebra.h"

using namespace sf;
using namespace humanSpine;


namespace humanSpineSfDraw
{

	class VertebraDrawer : public Drawable
	{

	private:

		virtual void draw(RenderTarget &target, RenderStates states) const
		{
			RectangleShape shape;
			
			shape.setPosition(position);
			shape.setOrigin(Vector2f(vertebra.getWidth / 2, vertebra.getHeight / 2));
			shape.setSize(Vector2f(vertebra.getWidth, vertebra.getHeight));
			shape.setRotation(vertebra.getAngle * 180 / PI);

			shape.setFillColor(Color::White);
			shape.setOutlineColor(Color(50, 50, 50));
			shape.setOutlineThickness(3.5f);

			target.draw(shape, states);
		}

	public:

		Vertebra vertebra;
		Vector2f position;

		VertebraDrawer()
		{
		}

		VertebraDrawer(Vertebra vertebra, Vector2f position = Vector2f())
		{
			this->vertebra = vertebra;
			this->position = position;
		}

		virtual ~VertebraDrawer()
		{
		}

	};

}