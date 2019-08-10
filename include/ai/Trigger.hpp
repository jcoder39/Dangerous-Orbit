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

#ifndef DANGEROUSORBIT_WAIT_HPP
#define DANGEROUSORBIT_WAIT_HPP

#include "Quasura/AI.hpp"
#include "Quasura/Common.hpp"

class Trigger : public quasura::ai::bt::Leaf
{
public:
  explicit Trigger(float delay) : _delay(delay), _current(delay) {}

  Node::State Update(float dt) override
  {
    auto step = dt * 1000.0f;
    _current -= step;
    if(_current < 0.0f){
      _current = _delay;
      return Node::State::Success;
    }

    return Node::State::InProgress;
  }

private:
  float _current;
  float _delay;
};

#endif //DANGEROUSORBIT_WAIT_HPP
