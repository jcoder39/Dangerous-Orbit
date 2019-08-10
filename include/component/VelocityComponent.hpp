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

#ifndef DANGEROUSORBIT_MOTIONCOMPONENT_HPP
#define DANGEROUSORBIT_MOTIONCOMPONENT_HPP

#include "Quasura/ECS.hpp"

class VelocityComponent : public quasura::ecs::Component
{
public:
  float _x;
  float _y;

  float _x1;
  float _y1;

  float _acceleration;

  VelocityComponent(float acceleration) : _x(0.0f), _y(0.0f), _x1(0.0f), _y1(0.0f), _acceleration(acceleration) {}
};

#endif //DANGEROUSORBIT_MOTIONCOMPONENT_HPP
