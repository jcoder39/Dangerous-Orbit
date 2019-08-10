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

#ifndef DANGEROUSORBIT_POSITIONCOMPONENT_HPP
#define DANGEROUSORBIT_POSITIONCOMPONENT_HPP

#define _USE_MATH_DEFINES

#include <math.h>
#include "Quasura/ECS.hpp"

class PositionComponent : public quasura::ecs::Component
{
public:
  float _x;
  float _y;
  float _angle;

  PositionComponent(float x, float y, float angle) : _x(x), _y(y), _angle(angle) {}

  void drag(float d)
  {
    auto rad = (_angle * M_PI) / 180;
    float x1 = static_cast<float>(std::cos(rad));
    float y1 = static_cast<float>(std::sin(rad));

    _x += x1 * d;
    _y += y1 * d;
  }
};

#endif //DANGEROUSORBIT_POSITIONCOMPONENT_HPP
