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

#ifndef DANGEROUSORBIT_ASTEROIDCOMPONENT_HPP
#define DANGEROUSORBIT_ASTEROIDCOMPONENT_HPP

#include "Quasura/ECS.hpp"

class AsteroidComponent : public quasura::ecs::Component
{
public:
  enum class Size {SMALL, BIG};

  explicit AsteroidComponent(const Size& size) : _size(size)
  {
    _border = _size == AsteroidComponent::Size::SMALL ? 16.0f : 32.0f;
  }
  ~AsteroidComponent() override = default;

  Size GetSize() { return _size; }

  float GetBorder()
  {
    return _border;
  }

private:
  Size _size;
  float _border;
};

#endif //DANGEROUSORBIT_ASTEROIDCOMPONENT_HPP
