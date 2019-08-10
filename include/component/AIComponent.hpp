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

#ifndef DANGEROUSORBIT_AICOMPONENT_HPP
#define DANGEROUSORBIT_AICOMPONENT_HPP

#include <memory>
#include "Quasura/ECS.hpp"
#include "Quasura/AI.hpp"

class AIComponent : public quasura::ecs::Component
{
public:
  explicit AIComponent(std::shared_ptr<quasura::ai::bt::BT>& bt) : _bt(std::move(bt)) {}
  ~AIComponent() override = default;

  void Tick(float dt)
  {
    _bt->Tick(dt);
  }

private:
  std::shared_ptr<quasura::ai::bt::BT> _bt;
};

#endif //DANGEROUSORBIT_AICOMPONENT_HPP
