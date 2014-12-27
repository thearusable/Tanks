#include "AnimateElement.h"


AnimateElement::AnimateElement(arus::Textures t, sf::Vector2f pos, sf::Vector2f size, bool r, float timestep)
	:repeated(r)
	, timeStep(0.5f)
	, timeToChange(timestep)
	, whichFrame(0)
	, colldown(timeToChange)
	, sliceSize(size)
{
	this->setVisible(true);
	this->setTexture(t);
	textureSize = mTexture.getSize();
	this->setTextureRect(sf::IntRect(0, 0, sliceSize.x, sliceSize.y));
	this->setPosition(pos.x - sliceSize.x / 2.f, pos.y - sliceSize.y / 2.f);
}

bool AnimateElement::update(){
	if (colldown <= 0){
		colldown = timeToChange;
		whichFrame++;
		if (whichFrame * sliceSize.x >= textureSize.x){
			if (repeated){
				whichFrame = 0;
				this->setTextureRect(sf::IntRect(0, 0, sliceSize.x, sliceSize.y));
				return false;
			}
			else return true;
		}
		else{
			this->setTextureRect(sf::IntRect(whichFrame * sliceSize.x, 0, sliceSize.x, sliceSize.y));
		}
	}
	colldown -= timeStep;
	return false;
}
