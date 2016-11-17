//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Gelo123321 - 2016. +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "GameEngine.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class GameState
{
public:
	virtual void init(GameEngine* game) = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents(GameEngine* game) = 0;
	virtual void update(GameEngine* game) = 0;
	virtual void draw(GameEngine* game) = 0;

	void ChangeState(GameEngine* game, GameState* state) {
		game->changeState(state);
	}

protected:
	GameState() { }
};
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++