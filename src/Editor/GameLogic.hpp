class GameLogic : public AbstractLogic
{
public:

  GameLogic() : m_rendow(nullptr) {}

  void init()
  {
    std::cout << "init" << std::endl;
  }
  
  void update()
  {

  }
  
  virtual void draw()
  {
    if (!m_rendow) return;
    
    m_rendow->clear(sf::Color::Red);
  }
  
  void finalize()
  {
    std::cout << "finalize" << std::endl;
  }
  
  void setRendow(sf::RenderWindow* rendow)
  {
    m_rendow = rendow;
  }
  
  sf::RenderWindow* getRendow() const
  {
    return m_rendow;
  }
  
private:

  sf::RenderWindow* m_rendow;
};

