#pragma once
#include "renderelement.h"
#include<ctime>
class PowerUp :
	public RenderElement
{
public:
	PowerUp(void);

	void create();
	void take();

	arus::PowerUp getType();
	float getTime();
protected:
	arus::PowerUp type;
	float time;
};
