#pragma once

#include<SFML/Graphics.hpp>

#include "Vertebra.h"

using namespace sf;
using namespace humanSpine;


namespace humanSpineSfDraw
{

	template<class T>
	class HumanSpineElementDrawable : public Drawable
	{

	public:

		T& element;
		Vector2f position;

		virtual ~HumanSpineElementDrawable()
		{
		}

	};

}