#include "RenderElement.h"

extern DataBase DATABASE;

RenderElement::RenderElement(void) :mSprite(), mTexture(), mTexID(arus::Textures::empty), isVisible(false)
{
}

RenderElement::RenderElement(RenderElement& r){//kopiujacy
	mSprite = r.getSprite();
	setTexture(r.getTextureID());
	isVisible = r.getVisible();
}

RenderElement::RenderElement(arus::Textures t) :mSprite(){
	this->setTexture(t);
}

RenderElement::~RenderElement(){
}

/////////// SETY //////////////

void RenderElement::setTexture(arus::Textures t){
	mTexID = t;
	if (mTexID == arus::Textures::empty){
		this->setVisible(false);
		return;
	}
	this->mTexture = DATABASE.get(t);
	mSprite.setTexture(mTexture);
	isVisible = true;
	setOriginToCenter();
}

void RenderElement::setTextureRect(sf::IntRect& rect){
	mSprite.setTextureRect(rect);
}

void RenderElement::setTextureAndRect(arus::Textures t, sf::IntRect& rect){
	this->setTexture(t);
	this->setTextureRect(rect);
}

void RenderElement::setPosition(float x, float y){
	mSprite.setPosition(x, y);
}

void RenderElement::setScale(float x, float y){
	mSprite.setScale(x, y);
}

void RenderElement::setRotation(float x){
	mSprite.setRotation(x);
}

void RenderElement::setVisible(bool b){
	this->isVisible = b;
}

void RenderElement::setOrigin(float x, float y){
	this->mSprite.setOrigin(x, y);
}

void RenderElement::setOriginToCenter(){
	this->mSprite.setOrigin(mSprite.getLocalBounds().width / 2.f, mSprite.getLocalBounds().height / 2.f);
}

///////////// GETY ///////////////
sf::IntRect RenderElement::getTextureRect(){
	return mSprite.getTextureRect();
}

arus::Textures RenderElement::getTextureID(){
	return this->mTexID;
}

sf::Sprite& RenderElement::getSprite(){
	return mSprite;
}

sf::Vector2f RenderElement::getPosition(){
	return mSprite.getPosition();
}

sf::FloatRect RenderElement::getLocalBounds(){
	return mSprite.getLocalBounds();
}

sf::FloatRect RenderElement::getGlobalBounds(){
	return mSprite.getGlobalBounds();
}

bool RenderElement::getVisible(){
	return isVisible;
}

//////////// INNE ////////////////

void RenderElement::move(float x, float y){
	mSprite.move(x, y);
}

void RenderElement::rotate(float x){
	mSprite.rotate(x);
}

void RenderElement::scale(float x, float y){
	mSprite.scale(x, y);
}

void RenderElement::operator>>(sf::RenderWindow& window){
	if (isVisible) window.draw(this->mSprite);
}
