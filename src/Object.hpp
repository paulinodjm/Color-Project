//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"

/**
* Base class for each object in the game.
*/
class Object
{
protected:

	virtual void init() {}
	
	virtual void update(float deltaTime) {}
	
friend class Game;
};

/**
* Base class for each visible object.
*/
class Drawable : public sf::Drawable
{
public:

	Drawable() : sf::Drawable(), m_visible(true) {}

	void setVisible(bool visible)
	{
		m_visible = visible;
	}
	
	bool isVisible() const
	{
		return m_visible;
	}
	
protected:

	bool m_visible;
};

/**
* Base class for each object that can collide with others and with
* the map.
*/
class Solid
{
public:

	Solid() : m_solid(true) {}

private:

	bool m_solid;
};
