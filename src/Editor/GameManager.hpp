//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "AbstractLogic.hpp"

class GameManager
{
public:

  GameManager();
  
  /////////////////////////
  // Game logic
  
  void setLogic(AbstractLogic *logic);
  
  AbstractLogic* getLogic() const;
  
protected:

  void init();

  void update();
  
  void draw();
  
  void finalize();
  
private:

  bool loadResources();
  

  AbstractLogic *m_logic;
};
