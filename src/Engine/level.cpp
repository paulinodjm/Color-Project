//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "level.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <jsoncpp/json/json.h>
#include "zipstream.h"
#include "zipstring.h"

LEVEL::LEVEL() : sf::Drawable(),
  paused(false),
  camera(nullptr)
{}

LEVEL::~LEVEL()
{
  DeleteObjects();
}

bool LEVEL::Load(
    const std::string& filename,
    CONTENTMANAGER& contentManager,
    const std::map<std::string, OBJECTFACTORY*>& factories
){ 
  DeleteObjects();
  
  std::cout << "==== Level '" << filename << "' loading ====" << std::endl;
  
  ZIPSTREAM zipstream;
  ZIPSTRING zipstring;
  Json::Value root;
  Json::Reader reader;
  
  if (!zipstream.Open(filename))
  {
    std::cout << "Failed to load level '" << filename << ".";
    return false;
  }
  if (!zipstring.Read(zipstream))
  {
    std::cout << "Failed to load level '" << filename << "' : stream error." << std::endl;
    return false;
  }
  if (!reader.parse(zipstring.Str(), root))
  {
    std::cout << "Failed to load level '" << filename << "' : " << reader.getFormatedErrorMessages();
    return false;
  }
  
  // tilemap loading
  if (root["tilemap"].isNull())
  {
    std::cout << "Failed to load level '" << filename << "' : no tilemap." << std::endl;
    return false;
  }
  else
  {
    tilemap = std::make_shared<TILEMAP>();
    if (!tilemap->Load(root["tilemap"].asString(), contentManager))
    {
      std::cout << "Failed to load level '" << filename << "' : tilemap loading failed." << std::endl;
      tilemap.reset();
      return false;
    }
  }
  
  // objects loading
  Json::Value jobjects = root["objects"];
  for (int i=0; i<jobjects.size(); i++)
  {
    Json::Value jobj = jobjects[i];
    auto itFactory = factories.find(jobj["type"].asString());
    if (itFactory == factories.end())
    {
      std::cout << "Warning : type '" << jobj["type"] << "' unknow!" << std::endl;
      continue;
    }
    OBJECT* obj = itFactory->second->Create();
    if (!obj)
    {
      std::cout << "Warning : an instance of '" << jobj["type"] << "' hasn't been created!" << std::endl;
      continue;
    }
    SOLID* solid = dynamic_cast<SOLID*>(obj);
    if (solid)
    {
      solid->SetPosition(
        jobj.get("x", 0).asDouble(),
        jobj.get("y", 0).asDouble()
      );
    }
    if (
      !AddObject(
        obj,
        jobj.get("name", "").asString(),
        jobj.get("depth", 0).asInt()
      )
    ){
      std::cout << "Warning : an instance of '" << jobj["type"] << "' hasn't been added to the level!" << std::endl;
    }
  }
  
  std::cout << "Level '" << filename << "' loaded." << std::endl;
  return true;
}

bool LEVEL::PerformLoading(CONTENTMANAGER& contentManager)
{
  for (auto it : objects)
  {
    if (!it.second->Load(contentManager))
    {
      std::cout << "An object has returned an error while loading." << std::endl;
      return false;
    }
  }
  return true;
}

bool LEVEL::AddSprite(STATICSPRITE& sprite, int depth)
{
  for (auto it : drawables)
  {
    if (it.second == &sprite)
    {
      return false;
    }
  }
  drawables.insert( std::pair<int, DRAWABLE*>(depth, &sprite) );
  return true;
}

bool LEVEL::AddSprite(ANIMATEDSPRITE& sprite, int depth)
{
  for (auto it : drawables)
  {
    if (it.second == &sprite)
    {
      return false;
    }
  }
  drawables.insert( std::pair<int, DRAWABLE*>(depth, &sprite) );
  actors.push_back(&sprite);

  sprite.Init();
  return true;
}

bool LEVEL::AddObject(OBJECT* obj, const std::string& name, int depth)
{
  if (obj == nullptr) return false;
  
  objects.insert( std::pair<std::string, OBJECT*>(name, obj) );
  
  ACTOR* actor = dynamic_cast<ACTOR*>(obj);
  if (actor)
  {
    actors.push_back(actor);
  }
  
  DRAWABLE* drawable = dynamic_cast<DRAWABLE*>(obj);
  if (drawable)
  {
    drawables.insert(std::pair<int, DRAWABLE*>(depth, drawable) );
  }
  
  SOLID* solid = dynamic_cast<SOLID*>(obj);
  if (solid)
  {
    solids.push_back(solid);
  }
  
  return true;
}

OBJECT* LEVEL::Object(const std::string& name) const
{
  auto it = objects.find(name);
  
  if (it == objects.end())
  {
    return nullptr;
  }
  else
  {
    return it->second;
  }
}

std::vector<OBJECT*> LEVEL::Objects(const std::string& name) const
{
  std::vector<OBJECT*> objs;
  auto range = objects.equal_range(name);
  
  for (auto it = range.first; it != range.second; it++)
  {
    objs.push_back(it->second);
  }
  
  return objs;
}

void LEVEL::DeleteObjects()
{
  for (auto it : objects)
  {
    delete it.second;
  }
  objects.clear();
  actors.clear();
  drawables.clear();
  solids.clear();
  camera = nullptr;
}

void LEVEL::Init()
{
  for (auto it : objects)
  {
    it.second->Init(*this);
  }
}

bool LEVEL::Update()
{
  for (auto it : actors)
  {
    it->Update();
  }
}

void LEVEL::PerformMove()
{
  for (SOLID* solid : solids)
  {
    if (solid->Speed() != sf::Vector2f(0,0))
    {
      sf::Vector2f speed = solid->speed * solid->clock.restart().asSeconds();
      sf::FloatRect bBox;
    
      if (solid->Solid() && tilemap)
      {
        int tileSize = tilemap->TileSize();
      
        // horizontal move
        if (speed.x != 0.f)
        {
          solid->position.x += speed.x;
          bBox = solid->Bbox();
          if ( !tilemap->PlaceFree(bBox) )
          {
            if (speed.x < 0)
            {
              bBox.left = (int)(bBox.left)/tileSize*tileSize + tileSize;
            }
            else
            {
              float right = (int)(bBox.left + bBox.width)/tileSize*tileSize;
              bBox.left = right - bBox.width;
            }
            solid->position.x = bBox.left - solid->bounds.left;
            solid->HitWall();
          }
        }
        
        // vertical move
        if (speed.y != 0.f)
        {
          solid->position.y += speed.y;
          bBox = solid->Bbox();
          if ( !tilemap->PlaceFree(bBox) )
          {
            if (speed.y < 0)
            {
              bBox.top = (int)(bBox.top)/tileSize*tileSize + tileSize;
              solid->position.y = bBox.top - solid->bounds.top;
              solid->HitCeiling();
            }
            else
            {
              float bottom = (int)(bBox.top + bBox.height)/tileSize*tileSize;
              bBox.top = bottom - bBox.height;
              solid->position.y = bBox.top - solid->bounds.top;
              solid->Landed();
            }
          }
        }     
        solid->Moved();
      }
      else
      {
        solid->SetPosition(solid->position + speed);
      }
    }
    else
    {
      solid->clock.restart().asSeconds();
    }
  }// foreach
}//perform move

void LEVEL::PerformCollisions()
{
  // security while using indexes.
  if (solids.size() == 0)
    return;
  
  for (int i=0; i<solids.size()-1; i++)
  {
    if (solids[i]->Solid())
    {
      for (int j=i+1; j<solids.size(); j++)
      {
        if (solids[j]->Solid() 
        && solids[i]->Bbox().intersects(solids[j]->Bbox()))
        {
          solids[i]->CollideWith(*solids[j]);
          solids[j]->CollideWith(*solids[i]);
        }
      }
    }    
    solids[i]->EndCollision();
  }
  solids[solids.size()-1]->EndCollision();
}

void LEVEL::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (camera)
  {
    sf::View view = target.getView();
    camera->CalcView(view);
    target.setView(view);
  }
  
  target.clear(sf::Color::Cyan);
  
  if (tilemap)
    target.draw(*tilemap);
  
  for (auto it : drawables)
  { 
    DRAWABLE* drawable = it.second;
    if (drawable->Visible())
      target.draw(*drawable);
  }
}


void LEVEL::SetPaused(bool paused_)
{
  paused = paused_;
}
  
bool LEVEL::Paused() const
{
  return paused;
}


CAMERA* LEVEL::Camera() const
{
  return camera;
}
  
void LEVEL::SetCamera(CAMERA* camera_)
{
  camera = camera_;
}

const std::shared_ptr<TILEMAP>& LEVEL::Tilemap() const
{
  return tilemap;
}

void LEVEL::SetTilemap(const std::shared_ptr<TILEMAP>& value)
{
  tilemap = value;
}
