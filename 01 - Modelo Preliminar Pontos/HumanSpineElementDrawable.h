#pragma once

#include<SFML/Graphics.hpp>

#include "Vertebra.h"

using namespace sf;
using namespace humanSpine;


namespace humanSpineSfDraw
{

	template<class T>
	class HumanSpineElementDrawable : public Drawable, public Transformable
	{

	public:

		T *element = NULL;

		virtual ~HumanSpineElementDrawable()
		{
		}

	};

}