//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Gelo123321 - 2016. +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "SDL.h"
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Enemy : public SDLGameObject
{
public:
	Enemy();

	void load(const LoaderParams *pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
private:

};

// for the factory
class EnemyCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Enemy();
	}
};
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++