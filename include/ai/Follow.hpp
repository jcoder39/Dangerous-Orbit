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

#ifndef DANGEROUSORBIT_FOLLOW_HPP
#define DANGEROUSORBIT_FOLLOW_HPP

#include <memory>
#include "Quasura/AI.hpp"
#include "component/PositionComponent.hpp"

class Follow : public quasura::ai::bt::Leaf
{
public:
  Follow(const std::shared_ptr<PositionComponent>& src, const std::shared_ptr<PositionComponent>& dst) : _src(src), _dst(dst) {}

  Node::State Update(float dt) override
  {
    float dx = _dst->_x - _src->_x;
    float dy = _dst->_y - _src->_y;

    auto length = std::sqrt((dx * dx + dy * dy));
    length = 1.0f / length;
    dx = dx * length;
    dy = dy * length;

    double angle = std::atan2(dy, dx);
    angle = angle * 180.0f / M_PI;

    if(angle < 0){
      angle += 360;
    }
    if(angle >= 360){
      angle -= 360;
    }

    _src->_angle = static_cast<float>(angle);

    return Node::State::InProgress;
  }

private:
  std::shared_ptr<PositionComponent> _src;
  std::shared_ptr<PositionComponent> _dst;
};

#endif //DANGEROUSORBIT_FOLLOW_HPP
