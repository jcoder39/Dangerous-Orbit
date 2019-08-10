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

#ifndef DANGEROUSORBIT_VELOCITYCOMPONENT_HPP
#define DANGEROUSORBIT_VELOCITYCOMPONENT_HPP

#define _USE_MATH_DEFINES

#include <math.h>
#include "Quasura/ECS.hpp"

class BulletMovementComponent : public quasura::ecs::Component
{
public:
  float _fromX;
  float _fromY;
  float _x;
  float _y;
  float _speed;

  BulletMovementComponent(float fromX, float fromY, float maxDistance, float speed) : _fromX(fromX), _fromY(fromY), _x(fromX), _y(fromY), _maxDistance(maxDistance), _speed(speed) {}

  bool isArrived()
  {
    float dx = _x - _fromX;
    float dy = _y - _fromY;

    return std::sqrt(dx * dx + dy * dy) >= _maxDistance;
  }

  ~BulletMovementComponent() override = default;

private:
  float _maxDistance;
};

#endif //DANGEROUSORBIT_VELOCITYCOMPONENT_HPP
