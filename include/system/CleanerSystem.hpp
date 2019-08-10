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

#ifndef DANGEROUSORBIT_CLEANERSYSTEM_HPP
#define DANGEROUSORBIT_CLEANERSYSTEM_HPP

#include "Quasura/ECS.hpp"
#include "Quasura/Events.hpp"
#include "component/CollisionComponent.hpp"

class CleanerSystem : public quasura::ecs::System
{
public:
  explicit CleanerSystem(int priority) : System(priority)
  {
    _events = quasura::events::Events::Instance();
  }

  ~CleanerSystem() override = default;

  void Update(float dt) override
  {
    auto objects = _componentContainer->GetComponents<CollisionComponent>();
    for(const auto& object : objects){
      if(object->Terminated()){
        auto entityID = object->GetID();
        auto removeFirst = std::make_shared<quasura::ecs::RemoveEntityEvent>(entityID);
        _events->Emit(removeFirst);
      }
    }
  }

private:
  quasura::events::Events* _events;
};

#endif //DANGEROUSORBIT_CLEANERSYSTEM_HPP
