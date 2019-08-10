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

#include "system/CollisionSystem.hpp"

using namespace std;
USING_COMMON_NAMESPACE
USING_ECS_NAMESPACE

void CollisionSystem::createAsteroids(const std::shared_ptr<PositionComponent>& position)
{
  auto chaos = Chaos::Instance();

  float random = chaos->GetRandom(0.0f, 90.0f);
  float angle = position->_angle - 90 - random;
  if(angle < 0){
    angle += 360;
  }
  if(angle >= 360){
    angle -= 360;
  }

  auto createAsteroid = make_shared<CreateAsteroidEvent>(position->_x, position->_y, angle);
  _events->Emit(createAsteroid);

  random = chaos->GetRandom(0.0f, 90.0f);
  angle = position->_angle + 90 - random;
  if(angle < 0){
    angle += 360;
  }
  if(angle >= 360){
    angle -= 360;
  }

  createAsteroid = make_shared<CreateAsteroidEvent>(position->_x, position->_y, angle);
  _events->Emit(createAsteroid);
}

void CollisionSystem::Update(float dt)
{
  auto objects = _componentContainer->GetComponents<CollisionComponent>();
  for(const auto& first : objects){
    auto firstID = first->GetID();
    auto firstShape = first->GetShape();
    auto firstPosition = _componentContainer->GetComponent<PositionComponent>(firstID);
    if(first->Terminated()){
      continue;
    }

    auto another = _componentContainer->GetComponents<CollisionComponent>();
    for(const auto& second : another){
      if(first == second){
        continue;
      }
      if(first->Terminated()){
        break;
      }
      if(second->Terminated()){
        continue;
      }

      auto secondID = second->GetID();
      auto secondShape = second->GetShape();
      auto secondPosition = _componentContainer->GetComponent<PositionComponent>(secondID);

      if(firstShape->GetType() == Shape::CIRCLE && secondShape->GetType() == Shape::RECT) {
        auto circle = static_pointer_cast<Circle>(firstShape);
        auto rect = static_pointer_cast<Rect>(secondShape);

        if(second->GetObjectType() == CollisionComponent::ObjectType::WEAPON){ // weapon vs asteroid
          if(first->GetObjectType() == CollisionComponent::ObjectType::ASTEROID){
            bool collision = Math::Instance()->IntersectCircleRect(firstPosition->_x, firstPosition->_y, circle->_radius,
                                                                   secondPosition->_x, secondPosition->_y, rect->_width, rect->_height, secondPosition->_angle);
            if(collision){
              auto asteroidComponent = _componentContainer->GetComponent<AsteroidComponent>(firstID);
              if(asteroidComponent->GetSize() == AsteroidComponent::Size::BIG){ // processing collision with big asteroid
                auto explosionEvent = make_shared<CreateExplosionEvent>(secondPosition->_x, secondPosition->_y, CreateExplosionEvent::ExplosionIndex::SECOND);
                _events->Emit(explosionEvent);

                if(second->GetOwner() == Owner::PLAYER){
                  auto addScores = make_shared<AddScoresEvent>(100);
                  _events->Emit(addScores);
                }

                createAsteroids(secondPosition);
              } else {
                auto explosionEvent = make_shared<CreateExplosionEvent>(firstPosition->_x, firstPosition->_y, CreateExplosionEvent::ExplosionIndex::FIRST);
                _events->Emit(explosionEvent);

                if(second->GetOwner() == Owner::PLAYER){
                  auto addScores = make_shared<AddScoresEvent>(50);
                  _events->Emit(addScores);
                }
              }

              first->Terminate();
              second->Terminate();
              break;
            }
          } else if(first->GetObjectType() == CollisionComponent::ObjectType::SHIP){ // weapon vs ship
            if(first->GetOwner() != second->GetOwner()){
              bool collision = Math::Instance()->IntersectCircleRect(firstPosition->_x, firstPosition->_y, circle->_radius,
                                                                     secondPosition->_x, secondPosition->_y, rect->_width, rect->_height, secondPosition->_angle);
              if(collision){
                auto explosionEvent = make_shared<CreateExplosionEvent>(firstPosition->_x, firstPosition->_y, CreateExplosionEvent::ExplosionIndex::THIRD);
                _events->Emit(explosionEvent);

                first->Terminate();
                second->Terminate();

                if(second->GetOwner() == Owner::PLAYER){
                  auto addScores = make_shared<AddScoresEvent>(200);
                  _events->Emit(addScores);
                }

                break;
              }
            }
          }
        }
      } else if(firstShape->GetType() == Shape::CIRCLE && secondShape->GetType() == Shape::CIRCLE){
        auto firstCircle = static_pointer_cast<Circle>(firstShape);
        auto secondCircle = static_pointer_cast<Circle>(secondShape);

        if(second->GetObjectType() == CollisionComponent::ObjectType::SHIP){ // ship vs asteroid
          if(first->GetObjectType() == CollisionComponent::ObjectType::ASTEROID){
            bool collision = Math::Instance()->IntersectTwoCircles(firstPosition->_x, firstPosition->_y, firstCircle->_radius,
                                                                   secondPosition->_x, secondPosition->_y, secondCircle->_radius);
            if(collision){
              auto explosionEvent = make_shared<CreateExplosionEvent>(secondPosition->_x, secondPosition->_y, CreateExplosionEvent::ExplosionIndex::THIRD);
              _events->Emit(explosionEvent);

              first->Terminate();
              second->Terminate();
              break;
            }
          } else if(first->GetObjectType() == CollisionComponent::ObjectType::SHIP){ // ship vs ship
            bool collision = Math::Instance()->IntersectTwoCircles(firstPosition->_x, firstPosition->_y, firstCircle->_radius,
                                                                   secondPosition->_x, secondPosition->_y, secondCircle->_radius);
            if(collision){
              auto explosionEvent = make_shared<CreateExplosionEvent>(firstPosition->_x, firstPosition->_y, CreateExplosionEvent::ExplosionIndex::THIRD);
              _events->Emit(explosionEvent);

              explosionEvent = make_shared<CreateExplosionEvent>(secondPosition->_x, secondPosition->_y, CreateExplosionEvent::ExplosionIndex::THIRD);
              _events->Emit(explosionEvent);

              first->Terminate();
              second->Terminate();
              break;
            }
          }
        }
      }
    }
  }
}

CollisionSystem::~CollisionSystem() = default;

CollisionSystem::CollisionSystem(int priority) : System(priority)
{
  _events = quasura::events::Events::Instance();
}