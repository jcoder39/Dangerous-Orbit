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

#ifndef DANGEROUSORBIT_SHOOT_HPP
#define DANGEROUSORBIT_SHOOT_HPP

#include <memory>
#include "Global.hpp"
#include "Quasura/AI.hpp"
#include "Quasura/Common.hpp"
#include "Quasura/Events.hpp"
#include "events/CreateBulletEvent.hpp"
#include "component/PositionComponent.hpp"

class Shoot : public quasura::ai::bt::Leaf
{
public:
  Shoot(const std::shared_ptr<PositionComponent>& position) : _position(position)
  {
    _events = quasura::events::Events::Instance();
  }

  Node::State Update(float dt) override
  {
    auto createBulletEvent = std::make_shared<CreateBulletEvent>(Owner::ALIEN, _position->_x, _position->_y, _position->_angle, 300);
    _events->Emit(createBulletEvent);
    return Node::State::Success;
  }

private:
  std::shared_ptr<PositionComponent> _position;
  quasura::events::Events* _events;
};

#endif //DANGEROUSORBIT_SHOOT_HPP
