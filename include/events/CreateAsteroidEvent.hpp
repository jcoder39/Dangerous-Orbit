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

#ifndef DANGEROUSORBIT_CREATEASTEROIDEVENT_HPP
#define DANGEROUSORBIT_CREATEASTEROIDEVENT_HPP

#include "Quasura/Events.hpp"

struct CreateAsteroidEvent : public quasura::events::Event
{
  float _x;
  float _y;
  float _angle;

  CreateAsteroidEvent(float x, float y, float angle) : _x(x), _y(y), _angle(angle) {}
};

#endif //DANGEROUSORBIT_CREATEASTEROIDEVENT_HPP
