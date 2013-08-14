//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "GameManager.hpp"

GameManager::GameManager() : m_logic(nullptr)
{}

void GameManager::setLogic(AbstractLogic *logic)
{
  m_logic = logic;
}
  
AbstractLogic* GameManager::getLogic() const
{
  return m_logic;
}

void GameManager::init()
{
  if (m_logic) 
    m_logic->init();
}

void GameManager::update()
{
  if (m_logic)
    m_logic->update();
}

void GameManager::draw()
{
  if (m_logic)
    m_logic->draw();
}

void GameManager::finalize()
{
  if (m_logic)
    m_logic->finalize();
}

bool GameManager::loadResources()
{
  return true;
}
