#pragma once
#include "renderelement.h"
class AnimateElement :
	public RenderElement
{
public:
	AnimateElement(arus::Textures t, sf::Vector2f pos, sf::Vector2f size, bool r = true, float timestep = 0.75f);

	bool update();
protected:

	float timeToChange, colldown, timeStep;

	sf::Vector2u textureSize;
	sf::Vector2u sliceSize;

	int whichFrame;

	bool repeated;
};
