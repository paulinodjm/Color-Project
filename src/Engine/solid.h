//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <set>

class LEVEL;

class SOLID
{
public:

  SOLID();
  SOLID(const sf::FloatRect& bounds, const sf::Vector2f& position = sf::Vector2f(0,0));
  
  /** Bounds of the object, in relative coordinates */
  const sf::FloatRect& Bounds() const;
  void SetBounds(const sf::FloatRect& value);
  
  /** Bounding box of the object, in world coordinates */
  sf::FloatRect Bbox() const;
  sf::FloatRect Bbox(float xOffset, float yOffset) const;
  sf::FloatRect Bbox(const sf::Vector2f& offset) const;
  
  /** Position */
  const sf::Vector2f& Position() const;
  void SetPosition(float x, float y);
  void SetPosition(const sf::Vector2f& position);  
  
  /** Speed */
  const sf::Vector2f& Speed() const;
  void SetSpeed(float x, float y);
  void SetSpeed(const sf::Vector2f& speed);
  
  bool Solid() const;
  void SetSolid(bool enable);
  
  const std::set<SOLID*>& TouchingSolids() const;
  
protected:
  /// EVENTS ///
  virtual void Moved() {}
  virtual void Touch(const SOLID& other) {}
  virtual void Untouch(const SOLID& other) {}
  virtual void Landed() {}
  virtual void Fall() {}
  virtual void HitWall() {}
  virtual void HitCeiling() {}

private:

  void CollideWith(SOLID& other);
  void EndCollision();
  void InvertCollisionBuffers();
  
  
  bool              isSolid;
  sf::Vector2f      position;
  sf::Vector2f      speed;
  sf::FloatRect     bounds;
  std::set<SOLID*>* touching;
  std::set<SOLID*>* lastTouching;
  sf::Clock					clock;
  
friend class LEVEL;
};
