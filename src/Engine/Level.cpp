//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "Level.hpp"

using namespace e;

Level::Level() : Drawable(),
  m_paused(false),
  m_camera(nullptr)
{}

Level::~Level()
{
  deleteObjects();
}


void Level::addObject(Object* object)
{
  if (object == nullptr) return;
  
  m_objects.insert( std::pair<std::string, Object*>(object->getName(), object) );
  
  Drawable* drawable = dynamic_cast<Drawable*>(object);
  if (drawable)
  {
    m_drawables.insert(std::pair<int, Drawable*>(drawable->getDepth(), drawable) );
  }
  
  Solid* solid = dynamic_cast<Solid*>(object);
  if (solid)
  {
    m_solids.push_back(solid);
  }
}

Object* Level::getObject(const std::string& name)
{
  auto it = m_objects.find(name);
  
  if (it == m_objects.end())
  {
    return nullptr;
  }
  else
  {
    return it->second;
  }
}

std::vector<Object*> Level::getObjects(const std::string& name)
{
  std::vector<Object*> objects;
  auto range = m_objects.equal_range(name);
  
  for (auto it = range.first; it != range.second; it++)
  {
    objects.push_back(it->second);
  }
  
  return objects;
}

void Level::deleteObjects()
{
  for (auto it : m_objects)
  {
    delete it.second;
  }
  m_objects.clear();
  m_drawables.clear();
  m_solids.clear();
}

void Level::init()
{
  for (auto it : m_objects)
  {
    it.second->init(*this);
  }
}

void Level::update()
{
  for (auto it : m_objects)
  {
    it.second->update(1.f);
  }
}

void Level::performCollisions()
{
  // security while using indexes.
  if (m_solids.size() == 0)
    return;
  
  for (int i=0; i<m_solids.size()-1; i++)
  {
    if (m_solids[i]->isSolid())
    {
      for (int j=i+1; j<m_solids.size(); j++)
      {
        if (m_solids[j]->isSolid() 
        && m_solids[i]->getBbox().intersects(m_solids[j]->getBbox()))
        {
          m_solids[i]->collideWith(*m_solids[j]);
          m_solids[j]->collideWith(*m_solids[i]);
        }
      }
    }    
    m_solids[i]->endCollision();
  }
  m_solids[m_solids.size()-1]->endCollision();
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (m_camera)
  {
    sf::View view = target.getView();
    m_camera->calcView(view);
    target.setView(view);
  }
    
  for (auto it : m_drawables)
  { 
    Drawable* drawable = it.second;
    if (drawable->isVisible())
      target.draw(*drawable);
  }
}


void Level::setPaused(bool paused)
{
  m_paused = paused;
}
  
bool Level::isPaused() const
{
  return m_paused;
}


Camera* Level::getCamera() const
{
  return m_camera;
}
  
void Level::setCamera(Camera* camera)
{
  m_camera = camera;
}
