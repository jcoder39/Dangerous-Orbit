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

#ifndef DANGEROUSORBIT_CREATEEXPLOSIONEVENT_HPP
#define DANGEROUSORBIT_CREATEEXPLOSIONEVENT_HPP

#include "Quasura/Events.hpp"

struct CreateExplosionEvent : public quasura::events::Event
{
  enum class ExplosionIndex { FIRST, SECOND, THIRD };

  float _x;
  float _y;
  ExplosionIndex _index;

  CreateExplosionEvent(float x, float y, const ExplosionIndex& index) : _x(x), _y(y), _index(index) {}
};

#endif //DANGEROUSORBIT_CREATEEXPLOSIONEVENT_HPP
