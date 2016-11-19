//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Gelo123321 - 2016. +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "StateManager.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StateManager::pushState(GameState * pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void StateManager::changeState(GameState * pState)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			return; // do nothing
		}
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}

	m_gameStates.push_back(pState);

	m_gameStates.back()->onEnter();
}

void StateManager::popState()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
}

void StateManager::update()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}
}

void StateManager::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++