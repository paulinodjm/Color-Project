//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>
#include <set>

class Object;
class Drawable;

class Game
{
public:

	int mainLoop();
	
	//--------------------------------------------
	// temporary functions; will be deleted later
	void addObject(Object& obj)
	{m_objects.insert(&obj);}
	//
	void deleteObject(Object& obj)
	{m_objects.erase(&obj);}
	//
	void addDrawable(Drawable& drawable)
	{m_drawables.insert(&drawable);}
	//
	void deleteDrawable(Drawable& drawable)
	{m_drawables.insert(&drawable);}
	//--------------------------------------------
	
protected:

	virtual bool loadRessources() {return true;}
	
	virtual void init() {}
	
	virtual bool update(float deltaTime) {return true;}
	
	virtual void finalize() {}
	
private:

	sf::RenderWindow 			m_rendow;
	
	std::set<Object*> 		m_objects;
	
	std::set<Drawable*> 	m_drawables;
};
