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

#ifndef DANGEROUSORBIT_ENTITYMAKER_HPP
#define DANGEROUSORBIT_ENTITYMAKER_HPP

#include "Global.hpp"
#include "Quasura/ECS.hpp"
#include "Quasura/Common.hpp"
#include "Quasura/AI.hpp"
#include "ai/Follow.hpp"
#include "ai/Trigger.hpp"
#include "ai/Shoot.hpp"
#include "animation/AnimatedSprite.hpp"
#include "component/AnimationComponent.hpp"
#include "component/AsteroidComponent.hpp"
#include "component/PositionComponent.hpp"
#include "component/ShipComponent.hpp"
#include "component/SpriteComponent.hpp"
#include "component/VelocityComponent.hpp"
#include "component/BulletMovementComponent.hpp"
#include "component/CollisionComponent.hpp"
#include "component/AlienComponent.hpp"
#include "component/AIComponent.hpp"
#include "Resources.hpp"
#include "events/CreateExplosionEvent.hpp"

class EntityMaker
{
public:
  EntityMaker(const quasura::ecs::ECSPtr& ecs, const sf::Vector2u& windowSize);

  quasura::ecs::EntityPtr CreateShip();
  quasura::ecs::EntityPtr CreateBullet(const Owner& owner, float x, float y, float angle, float speed);
  quasura::ecs::EntityPtr CreateAsteroid(const std::shared_ptr<PositionComponent>& position);
  quasura::ecs::EntityPtr CreateAsteroid(const AsteroidComponent::Size& size, float x, float y, float angle);
  quasura::ecs::EntityPtr CreateAlien(const std::shared_ptr<PositionComponent>& shipPosition);
  void CreateExplosion(float x, float y, const CreateExplosionEvent::ExplosionIndex& index);
  void CreateExplosion(const std::shared_ptr<CreateExplosionEvent>& event);

private:
  enum class Sides {LEFT, RIGHT, TOP, BOTTOM};

  quasura::ecs::ECSPtr _ecs;
  sf::Vector2u _windowSize;
  std::vector<std::shared_ptr<Animation>> _smallAsteroidAnimation;
  std::vector<std::shared_ptr<Animation>> _bigAsteroidAnimation;
  std::vector<std::shared_ptr<Animation>> _explosionsAnimation;
  std::vector<std::shared_ptr<Animation>> _alienAnimation;

  float _asteroidVelocity;

  void initializeAnimations();
};

#endif //DANGEROUSORBIT_ENTITYMAKER_HPP
