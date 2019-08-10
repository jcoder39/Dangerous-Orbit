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

#ifndef DANGEROUSORBIT_ANIMATIONCOMPONENT_HPP
#define DANGEROUSORBIT_ANIMATIONCOMPONENT_HPP

#include <memory>
#include "Quasura/ECS.hpp"
#include "animation/AnimatedSprite.hpp"

class AnimationComponent : public quasura::ecs::Component
{
public:
  AnimationComponent(const std::shared_ptr<AnimatedSprite>& sprite, const std::shared_ptr<Animation>& animation) : _sprite(sprite), _animation(animation) {}
  ~AnimationComponent() override = default;

  std::shared_ptr<AnimatedSprite> GetSprite() const
  {
    return _sprite;
  }

  std::shared_ptr<Animation> GetAnimation() const
  {
    return _animation;
  }

  void PlayAnimation()
  {
    _sprite->play(*_animation);
  }

private:
  std::shared_ptr<AnimatedSprite> _sprite;
  std::shared_ptr<Animation> _animation;
};

#endif //DANGEROUSORBIT_ANIMATIONCOMPONENT_HPP
