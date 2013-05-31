//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <cstdlib>
#include "Game.hpp"
#include "Object.hpp"

int Game::mainLoop()
{
	m_rendow.create(sf::VideoMode(640,480), "Colour Project");
	m_rendow.setFramerateLimit(60);
	
	sf::Event event;
	while (m_rendow.isOpen())
	{
		while (m_rendow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_rendow.close();
		}
		
		// update
		for (Object* obj : m_objects)
		{
			obj->update(1.f); // < TODO true deltaTime
		}
		
		// display
		m_rendow.clear(sf::Color::White);
		for (Drawable* drawable : m_drawables)
		{
			if (drawable->isVisible())
				m_rendow.draw(*drawable);
		}
		m_rendow.display();
	}
	
	return EXIT_SUCCESS;
}
