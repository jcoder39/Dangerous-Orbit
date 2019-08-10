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

#ifndef DANGEROUSORBIT_BULLETMOVEMENTSYSTEM_HPP
#define DANGEROUSORBIT_BULLETMOVEMENTSYSTEM_HPP

#define _USE_MATH_DEFINES

#include <math.h>
#include "Quasura/ECS.hpp"
#include "component/BulletMovementComponent.hpp"
#include "component/PositionComponent.hpp"

class BulletMovementSystem : public quasura::ecs::System
{
public:
  explicit BulletMovementSystem(int priority, const sf::Vector2u& windowSize) : System(priority), _windowSize(windowSize) {}

  ~BulletMovementSystem() override = default;

  void Update(float dt) override
  {
    auto movementComponents = _componentContainer->GetComponents<BulletMovementComponent>();
    for(const std::shared_ptr<BulletMovementComponent>& movement : movementComponents){
      auto entityId = movement->GetID();
      auto position = _componentContainer->GetComponent<PositionComponent>(entityId);

      auto rad = (position->_angle * M_PI) / 180;
      float x1 = static_cast<float>(std::cos(rad));
      float y1 = static_cast<float>(std::sin(rad));

      auto x = position->_x + movement->_speed * dt * x1;
      auto y = position->_y + movement->_speed * dt * y1;

      if(x >= _windowSize.x + 5.0f){
        x = 0.0f;
      }
      if(x < 0.0f){
        x = _windowSize.x + 5.0f;
      }
      if(y >= _windowSize.y + 5.0f){
        y = 0.0f;
      }
      if(y < 0.0f){
        y = _windowSize.y + 5.0f;
      }

      position->_x = x;
      position->_y = y;

      movement->_x = x;
      movement->_y = y;

      if(movement->isArrived()){
        auto events = quasura::events::Events::Instance();
        auto remove = std::make_shared<quasura::ecs::RemoveEntityEvent>(entityId);
        events->Emit(remove);
      }
    }
  }

private:
  sf::Vector2u _windowSize;
};

#endif //DANGEROUSORBIT_BULLETMOVEMENTSYSTEM_HPP
