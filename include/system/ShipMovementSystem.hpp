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

#ifndef DANGEROUSORBIT_MOVEMENTSYSTEM_HPP
#define DANGEROUSORBIT_MOVEMENTSYSTEM_HPP

#define _USE_MATH_DEFINES

#include <math.h>
#include "Quasura/ECS.hpp"
#include "component/ShipComponent.hpp"
#include "component/PositionComponent.hpp"
#include "events/KeyEvent.hpp"
#include "component/VelocityComponent.hpp"

class ShipMovementSystem : public quasura::ecs::System
{
public:
  explicit ShipMovementSystem(int priority, const sf::Vector2u& windowSize) : System(priority), _windowSize(windowSize), _pressed(false) {}

  ~ShipMovementSystem() override
  {
    auto events = quasura::events::Events::Instance();
    events->UnregisterListener(GetID());
  }

  void Init()
  {
    auto events = quasura::events::Events::Instance();
    events->RegisterListener<KeyEvent>(quasura::events::EventListener(GetID(), std::addressof(*this), &ShipMovementSystem::onKeyEvent));
  }

  void Update(float dt) override
  {
    auto ships = _componentContainer->GetComponents<ShipComponent>();
    for(const auto& ship : ships){
      auto entityId = ship->GetID();
      auto position = _componentContainer->GetComponent<PositionComponent>(entityId);
      auto velocity = _componentContainer->GetComponent<VelocityComponent>(entityId);

      auto x = position->_x;
      auto y = position->_y;

      if(_pressed){
        auto rad = (position->_angle * M_PI) / 180;
        velocity->_x = static_cast<float>(std::cos(rad));
        velocity->_y = static_cast<float>(std::sin(rad));

        velocity->_x1 += dt * velocity->_x * velocity->_acceleration;
        velocity->_y1 += dt * velocity->_y * velocity->_acceleration;
      } else {
        velocity->_x1 *= 0.99f;
        velocity->_y1 *= 0.99f;

        if(((int)velocity->_x1) < 1){
          int a = (int)(velocity->_x1 * 1000.0f);
          a %= 1000;

          if(a == 0){
            velocity->_x1 = 0.0f;
            velocity->_y1 = 0.0f;
          }
        }
      }

      x += velocity->_x1;
      y += velocity->_y1;

      if(x >= _windowSize.x + 20.0f){
        x = 0.0f;
      }
      if(x < 0.0f){
        x = _windowSize.x + 20.0f;
      }
      if(y >= _windowSize.y + 20.0f){
        y = 0.0f;
      }
      if(y < 0.0f){
        y = _windowSize.y + 20.0f;
      }

      position->_x = x;
      position->_y = y;
    }
  }

private:
  sf::Vector2u _windowSize;
  bool _pressed;

  void onKeyEvent(const quasura::events::EventPtr& e)
  {
    auto keyEvent = std::static_pointer_cast<KeyEvent>(e);

    if(keyEvent->_keyEvent.code == sf::Keyboard::Key::W){
      _pressed = keyEvent->_pressed;
    }
  }
};

#endif //DANGEROUSORBIT_MOVEMENTSYSTEM_HPP
