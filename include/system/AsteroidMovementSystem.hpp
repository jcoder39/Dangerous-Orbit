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

#ifndef DANGEROUSORBIT_ASTEROIDMOVEMENTSYSTEM_HPP
#define DANGEROUSORBIT_ASTEROIDMOVEMENTSYSTEM_HPP

#define _USE_MATH_DEFINES

#include <math.h>
#include "SFML/Graphics.hpp"
#include "Quasura/ECS.hpp"
#include "component/AsteroidComponent.hpp"
#include "component/PositionComponent.hpp"
#include "component/VelocityComponent.hpp"

class AsteroidMovementSystem : public quasura::ecs::System
{
public:
  explicit AsteroidMovementSystem(int priority, const sf::Vector2u& windowSize) : System(priority), _windowSize(windowSize) {}

  ~AsteroidMovementSystem() override
  {
    auto events = quasura::events::Events::Instance();
    events->UnregisterListener(GetID());
  }

  void Update(float dt) override
  {
    auto asteroids = _componentContainer->GetComponents<AsteroidComponent>();
    for(const auto& asteroid : asteroids){
      auto entityId = asteroid->GetID();
      auto position = _componentContainer->GetComponent<PositionComponent>(entityId);
      auto velocity = _componentContainer->GetComponent<VelocityComponent>(entityId);

      auto x = position->_x;
      auto y = position->_y;

      auto rad = (position->_angle * M_PI) / 180;
      velocity->_x = static_cast<float>(std::cos(rad));
      velocity->_y = static_cast<float>(std::sin(rad));

      velocity->_x1 = dt * velocity->_x * velocity->_acceleration;
      velocity->_y1 = dt * velocity->_y * velocity->_acceleration;

      x += velocity->_x1;
      y += velocity->_y1;

      bool outOfScreen = false;
      if(x >= _windowSize.x + asteroid->GetBorder()){
        outOfScreen = true;
      }
      if(x < -asteroid->GetBorder()){
        outOfScreen = true;
      }
      if(y >= _windowSize.y + asteroid->GetBorder()){
        outOfScreen = true;
      }
      if(y < -asteroid->GetBorder()){
        outOfScreen = true;
      }

      position->_x = x;
      position->_y = y;

      if(outOfScreen){
        auto events = quasura::events::Events::Instance();
        auto remove = std::make_shared<quasura::ecs::RemoveEntityEvent>(entityId);
        events->Emit(remove);
      }
    }
  }

private:
  sf::Vector2u _windowSize;
};

#endif //DANGEROUSORBIT_ASTEROIDMOVEMENTSYSTEM_HPP
