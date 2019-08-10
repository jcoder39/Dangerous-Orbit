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

#ifndef DANGEROUSORBIT_COLLISIONCOMPONENT_HPP
#define DANGEROUSORBIT_COLLISIONCOMPONENT_HPP

#include <memory>
#include "Quasura/ECS.hpp"
#include "Global.hpp"

class Shape
{
public:
  enum Type { CIRCLE, RECT };

  explicit Shape(const Type& type) : _type(type) {}
  virtual ~Shape() = 0;

  Type GetType()
  {
    return _type;
  }

protected:
  Type _type;
};

inline Shape::~Shape() = default;

class Circle : public Shape
{
public:
  explicit Circle(float radius) : Shape(Type::CIRCLE), _radius(radius) {}
  ~Circle() override = default;

  float _radius;
};

class Rect : public Shape
{
public:
  explicit Rect(float width, float height) : Shape(Type::RECT), _width(width), _height(height) {}
  ~Rect() override = default;

  float _width;
  float _height;
};

class CollisionComponent : public quasura::ecs::Component
{
public:
  enum class ObjectType { SHIP, ASTEROID, WEAPON };
  enum class Condition { ENABLED, DISABLED };

  explicit CollisionComponent(const Owner& owner, const ObjectType& type, const std::shared_ptr<Shape>& shape) : _type(type), _owner(owner),
  _condition(Condition::ENABLED), _shape(shape) {}
  ~CollisionComponent() override = default;

  const std::shared_ptr<Shape>& GetShape()
  {
    return _shape;
  }

  void Terminate()
  {
    _condition = Condition::DISABLED;
  }

  bool Terminated()
  {
    return _condition == Condition::DISABLED;
  }

  ObjectType GetObjectType()
  {
    return _type;
  }

  Owner GetOwner()
  {
    return _owner;
  }

  Condition GetCondition()
  {
    return _condition;
  }

private:
  std::shared_ptr<Shape> _shape;
  ObjectType _type;
  Owner _owner;
  Condition _condition;
};

#endif //DANGEROUSORBIT_COLLISIONCOMPONENT_HPP
