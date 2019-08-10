/*
 * This file is part of Dangerous Orbit source code.
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "component/BulletMovementComponent.hpp"
#include "GameMaster.hpp"

using namespace std;
USING_EVENTS_NAMESPACE
USING_ECS_NAMESPACE

void GameMaster::Update(const sf::Time& time)
{
  if(_state == State::PAUSE){
    return;
  }

  auto t = time.asSeconds() * 1000.0f;
  if(_state == State::GAME_OVER){
    _delay -= t;
    if(_delay < 0){
      _ecs->Clear();
      NewGame();
    }
  } else if(_state == State::RUN){
    if(_turning){
      if(_pressed == sf::Keyboard::Key::A){
        auto position = _ship->GetComponent<PositionComponent>(_ship->GetID());
        auto angle = position->_angle - 3.0f;
        if(angle < 0){
          angle += 360;
        }
        position->_angle = angle;
      } else if(_pressed == sf::Keyboard::Key::D){
        auto position = _ship->GetComponent<PositionComponent>(_ship->GetID());
        auto angle = position->_angle + 3.0f;
        if(angle >= 360){
          angle -= 360;
        }
        position->_angle = angle;
      }
    }

    _asteroidAppearanceDelay -= t;
    if(_asteroidAppearanceDelay < 0){
      _asteroidAppearanceDelay = ASTEROID_TIMER - _level * 100.0f;
      if(_asteroidAppearanceDelay < 500.0f){
        _asteroidAppearanceDelay = 500.0f;
      }
      auto position = _ship->GetComponent<PositionComponent>(_ship->GetID());
      _entityMaker->CreateAsteroid(position);
    }

    if(_level >= 3){
      _alienAppearanceDelay -= t;
      if(_alienAppearanceDelay < 0){
        _alienAppearanceDelay = ALIEN_TIMER;
        auto position = _ship->GetComponent<PositionComponent>(_ship->GetID());
        _entityMaker->CreateAlien(position);
      }
    }
  }
  _ecs->Update(time.asSeconds());
}

void GameMaster::onKeyEvent(const EventPtr& e)
{
  auto keyEvent = std::static_pointer_cast<KeyEvent>(e);

  auto key = keyEvent->_keyEvent.code;
  if(key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::D){
    _turning = keyEvent->_pressed;
    _pressed = key;
  }

  if(key == sf::Keyboard::Key::Space){
    if(!keyEvent->_pressed && _state == State::RUN){
      shot();
    }
  }
}

void GameMaster::onCreateAsteroidEvent(const EventPtr& e)
{
  auto createAsteroidEvent = std::static_pointer_cast<CreateAsteroidEvent>(e);
  _entityMaker->CreateAsteroid(AsteroidComponent::Size::SMALL, createAsteroidEvent->_x, createAsteroidEvent->_y, createAsteroidEvent->_angle);
}

void GameMaster::onCreateExplosionEvent(const EventPtr& e)
{
  auto createExplosionEvent = std::static_pointer_cast<CreateExplosionEvent>(e);
  _entityMaker->CreateExplosion(createExplosionEvent);
}

void GameMaster::onCreateBulletEvent(const EventPtr& e)
{
  auto createBulletEvent = std::static_pointer_cast<CreateBulletEvent>(e);
  _entityMaker->CreateBullet(createBulletEvent->_owner, createBulletEvent->_x, createBulletEvent->_y, createBulletEvent->_angle, createBulletEvent->_speed);
}

void GameMaster::onRemoveEntityEvent(const EventPtr& e)
{
  auto removeEnityEvent = std::static_pointer_cast<RemoveEntityEvent>(e);
  if(removeEnityEvent->_entityId == _ship->GetID()){
    _state = State::GAME_OVER;
    _delay = 2000.0f;
  }
}

void GameMaster::onAddScoresEvent(const EventPtr& e)
{
  auto addScores = std::static_pointer_cast<AddScoresEvent>(e);
  _currentScore += addScores->_scores;

  if(_currentScore >= LEVEL_UP){
    auto rest = _currentScore - LEVEL_UP;
    _currentScore = rest;
    _level++;

    auto updateLevel = std::make_shared<UpdateLevelEvent>(_level);
    Events::Instance()->Emit(updateLevel);
  }

  _scores += addScores->_scores;

  auto updateScores = std::make_shared<UpdateScoresEvent>(_scores);
  Events::Instance()->Emit(updateScores);
}

void GameMaster::shot()
{
  auto shipPosition = _ship->GetComponent<PositionComponent>(_ship->GetID());
  _entityMaker->CreateBullet(Owner::PLAYER, shipPosition->_x, shipPosition->_y, shipPosition->_angle, 500.0f);
}

void GameMaster::Init()
{
  auto events = Events::Instance();
  events->RegisterListener<KeyEvent>(EventListener("GM", std::addressof(*this), &GameMaster::onKeyEvent));
  events->RegisterListener<CreateAsteroidEvent>(EventListener("GM", std::addressof(*this), &GameMaster::onCreateAsteroidEvent));
  events->RegisterListener<CreateExplosionEvent>(EventListener("GM", std::addressof(*this), &GameMaster::onCreateExplosionEvent));
  events->RegisterListener<RemoveEntityEvent>(EventListener("GM", std::addressof(*this), &GameMaster::onRemoveEntityEvent));
  events->RegisterListener<AddScoresEvent>(EventListener("GM", std::addressof(*this), &GameMaster::onAddScoresEvent));
  events->RegisterListener<CreateBulletEvent>(EventListener("GM", std::addressof(*this), &GameMaster::onCreateBulletEvent));
}

void GameMaster::Pause()
{
  _state = State::PAUSE;
}

void GameMaster::Resume()
{
  _state = State::RUN;
}

void GameMaster::NewGame()
{
  _ship = _entityMaker->CreateShip();
  _state = State::RUN;

  _scores = 0;
  _currentScore = 0;
  _level = 1;
  _asteroidAppearanceDelay = ASTEROID_TIMER;
  _alienAppearanceDelay = ALIEN_TIMER;
  auto updateScores = std::make_shared<UpdateScoresEvent>(_scores);
  Events::Instance()->Emit(updateScores);
  auto updateLevel = std::make_shared<UpdateLevelEvent>(_level);
  Events::Instance()->Emit(updateLevel);
}

GameMaster::GameMaster(sf::RenderWindow& window) : _window(window), _turning(false), _state(State::RUN), _delay(0.0f), _asteroidAppearanceDelay(0.0f),
_alienAppearanceDelay(ALIEN_TIMER), _scores(0), _currentScore(0), _level(1)
{
  _ecs = std::make_shared<ECS>();
  _ecs->Init();

  _entityMaker = std::make_shared<EntityMaker>(_ecs, _window.getSize());

  auto shipMovementSystem = std::make_shared<ShipMovementSystem>(0, _window.getSize());
  shipMovementSystem->Init();
  _ecs->AddSystem(shipMovementSystem);

  auto aiSystem = std::make_shared<AISystem>(1);
  _ecs->AddSystem(aiSystem);

  auto alienMovementSystem = std::make_shared<AlienMovementSystem>(2, _window.getSize());
  _ecs->AddSystem(alienMovementSystem);

  auto asteroidMovementSystem = std::make_shared<AsteroidMovementSystem>(2, _window.getSize());
  _ecs->AddSystem(asteroidMovementSystem);

  auto bulletMovementSystem = std::make_shared<BulletMovementSystem>(2, _window.getSize());
  _ecs->AddSystem(bulletMovementSystem);

  auto collisionSystem = std::make_shared<CollisionSystem>(3);
  _ecs->AddSystem(collisionSystem);

  auto cleanerSystem = make_shared<CleanerSystem>(4);
  _ecs->AddSystem(cleanerSystem);

  auto drawingSystem = std::make_shared<DrawingSystem>(5, _window);
  _ecs->AddSystem(drawingSystem);

  _ship = _entityMaker->CreateShip();
}

GameMaster::~GameMaster()
{
  auto events = Events::Instance();
  events->UnregisterListener("GM");
}
