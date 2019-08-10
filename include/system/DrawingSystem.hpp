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

#ifndef DANGEROUSORBIT_DRAWINGSYSTEM_HPP
#define DANGEROUSORBIT_DRAWINGSYSTEM_HPP

#include "SFML/Window.hpp"
#include "Quasura/ECS.hpp"
#include "Quasura/Events.hpp"
#include "component/SpriteComponent.hpp"
#include "component/PositionComponent.hpp"
#include "component/AnimationComponent.hpp"

class DrawingSystem : public quasura::ecs::System
{
public:
  explicit DrawingSystem(int priority, sf::RenderWindow& window) : System(priority), _window(window) {}

  void Update(float dt) override
  {
    auto spriteComponents = _componentContainer->GetComponents<SpriteComponent>();
    for(const std::shared_ptr<SpriteComponent>& example : spriteComponents){
      auto entityId = example->GetID();
      auto position = _componentContainer->GetComponent<PositionComponent>(entityId);

      auto sprite = example->GetSprite();

      sprite->setPosition(position->_x, position->_y);
      sprite->setRotation(position->_angle);

      _window.draw(*sprite);
    }

    auto animationComponents = _componentContainer->GetComponents<AnimationComponent>();
    for(const std::shared_ptr<AnimationComponent>& example : animationComponents){
      auto entityId = example->GetID();
      auto position = _componentContainer->GetComponent<PositionComponent>(entityId);

      auto sprite = example->GetSprite();

      sprite->setPosition(position->_x, position->_y);
      sprite->setRotation(position->_angle);
      sf::Time time = sf::seconds(dt);
      sprite->update(time);
      _window.draw(*sprite);

      if(!sprite->isLooped()){
        if(!sprite->isPlaying()){
          auto events = quasura::events::Events::Instance();
          auto remove = std::make_shared<quasura::ecs::RemoveEntityEvent>(entityId);
          events->Emit(remove);
        }
      }
    }
  }

private:
  sf::RenderWindow& _window;
};

#endif //DANGEROUSORBIT_DRAWINGSYSTEM_HPP
