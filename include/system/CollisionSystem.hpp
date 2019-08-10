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

#ifndef DANGEROUSORBIT_COLLISIONSYSTEM_HPP
#define DANGEROUSORBIT_COLLISIONSYSTEM_HPP

#include "Quasura/ECS.hpp"
#include "Quasura/Events.hpp"
#include "Math.hpp"
#include "component/AsteroidComponent.hpp"
#include "component/PositionComponent.hpp"
#include "component/ShipComponent.hpp"
#include "component/CollisionComponent.hpp"
#include "events/CreateExplosionEvent.hpp"
#include "events/CreateAsteroidEvent.hpp"
#include "events/AddScoresEvent.hpp"

class CollisionSystem : public quasura::ecs::System
{
public:
  explicit CollisionSystem(int priority);

  ~CollisionSystem() override;

  void Update(float dt) override;

private:
  quasura::events::Events* _events;

  void createAsteroids(const std::shared_ptr<PositionComponent>& position);
};

#endif //DANGEROUSORBIT_COLLISIONSYSTEM_HPP
