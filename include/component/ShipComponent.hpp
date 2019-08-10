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

#ifndef DANGEROUSORBIT_SHIPCOMPONENT_HPP
#define DANGEROUSORBIT_SHIPCOMPONENT_HPP

#include "Quasura/ECS.hpp"

class ShipComponent : public quasura::ecs::Component
{
public:
  ~ShipComponent() override = default;
};

#endif //DANGEROUSORBIT_SHIPCOMPONENT_HPP
