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

#ifndef DANGEROUSORBIT_GAMEMASTER_HPP
#define DANGEROUSORBIT_GAMEMASTER_HPP

#include <vector>
#include <memory>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Global.hpp"
#include "Resources.hpp"
#include "Quasura/ECS.hpp"
#include "system/ShipMovementSystem.hpp"
#include "system/AlienMovementSystem.hpp"
#include "system/AISystem.hpp"
#include "component/ShipComponent.hpp"
#include "system/BulletMovementSystem.hpp"
#include "system/AsteroidMovementSystem.hpp"
#include "system/CollisionSystem.hpp"
#include "system/CleanerSystem.hpp"
#include "component/BulletMovementComponent.hpp"
#include "system/DrawingSystem.hpp"
#include "Quasura/events/Events.hpp"
#include "events/KeyEvent.hpp"
#include "events/CreateAsteroidEvent.hpp"
#include "events/CreateExplosionEvent.hpp"
#include "events/AddScoresEvent.hpp"
#include "events/UpdateScoresEvent.hpp"
#include "events/CreateBulletEvent.hpp"
#include "events/UpdateLevelEvent.hpp"
#include "component/VelocityComponent.hpp"
#include "animation/AnimatedSprite.hpp"
#include "EntityMaker.hpp"

class GameMaster
{
public:
  enum class State { RUN, PAUSE, GAME_OVER };
  GameMaster(sf::RenderWindow& window);
  ~GameMaster();

  void Init();
  void Update(const sf::Time& time);
  void Pause();
  void Resume();
  void NewGame();

private:
  sf::RenderWindow& _window;
  quasura::ecs::ECSPtr _ecs;
  std::shared_ptr<EntityMaker> _entityMaker;
  quasura::ecs::EntityPtr _ship;
  bool _turning;
  sf::Keyboard::Key _pressed;
  State _state;
  float _delay;
  float _asteroidAppearanceDelay;
  float _alienAppearanceDelay;
  long _scores;
  long _currentScore;
  unsigned int _level;

  void onKeyEvent(const quasura::events::EventPtr& e);
  void onCreateAsteroidEvent(const quasura::events::EventPtr& e);
  void onCreateExplosionEvent(const quasura::events::EventPtr& e);
  void onCreateBulletEvent(const quasura::events::EventPtr& e);
  void onRemoveEntityEvent(const quasura::events::EventPtr& e);
  void onAddScoresEvent(const quasura::events::EventPtr& e);
  void shot();
};

#endif //DANGEROUSORBIT_GAMEMASTER_HPP
