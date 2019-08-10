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

#include "EntityMaker.hpp"

using namespace std;
USING_COMMON_NAMESPACE
USING_ECS_NAMESPACE
using namespace quasura::ai::bt;

EntityPtr EntityMaker::CreateShip()
{
  auto ship = _ecs->CreateEntity();

  auto positionComponent = std::make_shared<PositionComponent>(_windowSize.x / 2, _windowSize.y / 2, 0);
  positionComponent->SetID(ship->GetID());
  ship->AddComponent(positionComponent);

  auto shipComponent = std::make_shared<ShipComponent>();
  shipComponent->SetID(ship->GetID());
  ship->AddComponent(shipComponent);

  auto velocityComponent = std::make_shared<VelocityComponent>(3);
  velocityComponent->SetID(ship->GetID());
  ship->AddComponent(velocityComponent);

  auto resources = Resources::Instance();
  auto texture = resources->GetTexture("data/ship.png");
  auto sprite = std::make_shared<sf::Sprite>();
  sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
  sprite->setTexture(*texture);
  auto spriteComponent = std::make_shared<SpriteComponent>(sprite);
  spriteComponent->SetID(ship->GetID());
  ship->AddComponent(spriteComponent);

  auto circle = std::make_shared<Circle>(32.0f);
  auto collisionComponent = std::make_shared<CollisionComponent>(Owner::PLAYER, CollisionComponent::ObjectType::SHIP, circle);
  collisionComponent->SetID(ship->GetID());
  ship->AddComponent(collisionComponent);

  return ship;
}

EntityPtr EntityMaker::CreateBullet(const Owner& owner, float x, float y, float angle, float speed)
{
  auto bullet = _ecs->CreateEntity();

  auto resources = Resources::Instance();
  auto texture = resources->GetTexture("data/laser.png");
  texture->setSmooth(true);
  auto sprite = std::make_shared<sf::Sprite>();
  sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
  sprite->setTexture(*texture);
  auto spriteComponent = std::make_shared<SpriteComponent>(sprite);
  spriteComponent->SetID(bullet->GetID());

  auto positionComponent = std::make_shared<PositionComponent>(x, y, angle);
  positionComponent->SetID(bullet->GetID());
  positionComponent->drag(30.0f);
  auto bulletMovementComponent = std::make_shared<BulletMovementComponent>(positionComponent->_x, positionComponent->_y, 250, speed);
  bulletMovementComponent->SetID(bullet->GetID());

  auto rect = std::make_shared<Rect>(16.0f, 6.0f);
  auto collisionComponent = std::make_shared<CollisionComponent>(owner, CollisionComponent::ObjectType::WEAPON, rect);
  collisionComponent->SetID(bullet->GetID());

  bullet->AddComponent(collisionComponent);
  bullet->AddComponent(positionComponent);
  bullet->AddComponent(spriteComponent);
  bullet->AddComponent(bulletMovementComponent);

  return bullet;
}

EntityPtr EntityMaker::CreateAsteroid(const std::shared_ptr<PositionComponent>& position)
{
  auto asteroid = _ecs->CreateEntity();

  Bag<int> bag;
  bag.Add({0,0,0,0,1,1,1,1,1,1});

  auto size = static_cast<AsteroidComponent::Size>(bag.Get());

  auto asteroidComponent = std::make_shared<AsteroidComponent>(size);
  asteroidComponent->SetID(asteroid->GetID());
  std::shared_ptr<Animation> animation;

  auto animationType = Chaos::Instance()->GetRandom(0, 5);
  auto rotationSpeed = Chaos::Instance()->GetRandom(0.08f, 0.13f);
  auto velocity = _asteroidVelocity;
  if(size == AsteroidComponent::Size::BIG){
    animation = _bigAsteroidAnimation[animationType];
    rotationSpeed = Chaos::Instance()->GetRandom(0.15f, 0.2f);
    velocity = _asteroidVelocity / 2;
  } else {
    animation = _smallAsteroidAnimation[animationType];
  }

  auto sprite = std::make_shared<AnimatedSprite>(sf::seconds(rotationSpeed), false, true);
  sprite->setOrigin(asteroidComponent->GetBorder(), asteroidComponent->GetBorder());
  auto animationComponent = std::make_shared<AnimationComponent>(sprite, animation);
  animationComponent->SetID(asteroid->GetID());
  animationComponent->PlayAnimation();

  auto side = static_cast<Sides>(Chaos::Instance()->GetRandom(0, 3));
  float x = 0.0f, y = 0.0f;

  if(side == Sides::LEFT){
    x = -asteroidComponent->GetBorder();
    y = Chaos::Instance()->GetRandom(0.0f, _windowSize.y);
  } else if(side == Sides::RIGHT) {
    x = _windowSize.x + asteroidComponent->GetBorder();
    y = Chaos::Instance()->GetRandom(0.0f, _windowSize.y);
  } else if(side == Sides::TOP) {
    x = Chaos::Instance()->GetRandom(0.0f, _windowSize.x);
    y = -asteroidComponent->GetBorder();
  } else if(side == Sides::BOTTOM) {
    x = Chaos::Instance()->GetRandom(0.0f, _windowSize.x);
    y = _windowSize.y + asteroidComponent->GetBorder();
  }

  float dx = position->_x - x;
  float dy = position->_y - y;

  auto length = std::sqrt((dx * dx + dy * dy));
  length = 1.0f / length;
  dx = dx * length;
  dy = dy * length;

  double angle = std::atan2(dy, dx);
  angle = angle * 180.0f / M_PI;

  if(angle < 0){
    angle += 360;
  }
  if(angle >= 360){
    angle -= 360;
  }

  auto positionComponent = std::make_shared<PositionComponent>(x, y, angle);
  positionComponent->SetID(asteroid->GetID());
  auto velocityComponent = std::make_shared<VelocityComponent>(velocity);
  velocityComponent->SetID(asteroid->GetID());

  auto circle = std::make_shared<Circle>(asteroidComponent->GetBorder());
  auto collisionComponent = std::make_shared<CollisionComponent>(Owner::NATURE, CollisionComponent::ObjectType::ASTEROID, circle);
  collisionComponent->SetID(asteroid->GetID());

  asteroid->AddComponent(asteroidComponent);
  asteroid->AddComponent(collisionComponent);
  asteroid->AddComponent(positionComponent);
  asteroid->AddComponent(animationComponent);
  asteroid->AddComponent(velocityComponent);

  return asteroid;
}

EntityPtr EntityMaker::CreateAsteroid(const AsteroidComponent::Size& size, float x, float y, float angle)
{
  auto asteroid = _ecs->CreateEntity();

  auto asteroidComponent = std::make_shared<AsteroidComponent>(size);
  asteroidComponent->SetID(asteroid->GetID());
  std::shared_ptr<Animation> animation;

  auto animationType = Chaos::Instance()->GetRandom(0, 5);
  auto rotationSpeed = Chaos::Instance()->GetRandom(0.08f, 0.13f);
  auto velocity = _asteroidVelocity;
  if(size == AsteroidComponent::Size::BIG){
    animation = _bigAsteroidAnimation[animationType];
    rotationSpeed = Chaos::Instance()->GetRandom(0.15f, 0.2f);
    velocity = _asteroidVelocity / 2;
  } else {
    animation = _smallAsteroidAnimation[animationType];
  }

  auto sprite = std::make_shared<AnimatedSprite>(sf::seconds(rotationSpeed), false, true);
  sprite->setOrigin(asteroidComponent->GetBorder(), asteroidComponent->GetBorder());
  auto animationComponent = std::make_shared<AnimationComponent>(sprite, animation);
  animationComponent->SetID(asteroid->GetID());
  animationComponent->PlayAnimation();

  auto positionComponent = std::make_shared<PositionComponent>(x, y, angle);
  positionComponent->SetID(asteroid->GetID());
  auto velocityComponent = std::make_shared<VelocityComponent>(velocity);
  velocityComponent->SetID(asteroid->GetID());

  auto circle = std::make_shared<Circle>(asteroidComponent->GetBorder());
  auto collisionComponent = std::make_shared<CollisionComponent>(Owner::NATURE, CollisionComponent::ObjectType::ASTEROID, circle);
  collisionComponent->SetID(asteroid->GetID());

  asteroid->AddComponent(asteroidComponent);
  asteroid->AddComponent(collisionComponent);
  asteroid->AddComponent(positionComponent);
  asteroid->AddComponent(animationComponent);
  asteroid->AddComponent(velocityComponent);

  return asteroid;
}

EntityPtr EntityMaker::CreateAlien(const std::shared_ptr<PositionComponent>& shipPosition)
{
  auto alien = _ecs->CreateEntity();

  auto velocityComponent = std::make_shared<VelocityComponent>(100.0f);
  velocityComponent->SetID(alien->GetID());
  alien->AddComponent(velocityComponent);

  auto alienComponent = std::make_shared<AlienComponent>();
  alienComponent->SetID(alien->GetID());
  alien->AddComponent(alienComponent);

  auto sprite = std::make_shared<AnimatedSprite>(sf::seconds(0.15f), false, true);
  sprite->setOrigin(32, 32);
  auto animationComponent = std::make_shared<AnimationComponent>(sprite, _alienAnimation[0]);
  animationComponent->SetID(alien->GetID());
  animationComponent->PlayAnimation();
  alien->AddComponent(animationComponent);

  auto circle = std::make_shared<Circle>(32.0f);
  auto collisionComponent = std::make_shared<CollisionComponent>(Owner::ALIEN, CollisionComponent::ObjectType::SHIP, circle);
  collisionComponent->SetID(alien->GetID());
  alien->AddComponent(collisionComponent);

  auto side = static_cast<Sides>(Chaos::Instance()->GetRandom(0, 3));
  float x = 0.0f, y = 0.0f;

  if(side == Sides::LEFT){
    x = -circle->_radius;
    y = Chaos::Instance()->GetRandom(0.0f, _windowSize.y);
  } else if(side == Sides::RIGHT) {
    x = _windowSize.x + circle->_radius;
    y = Chaos::Instance()->GetRandom(0.0f, _windowSize.y);
  } else if(side == Sides::TOP) {
    x = Chaos::Instance()->GetRandom(0.0f, _windowSize.x);
    y = -circle->_radius;
  } else if(side == Sides::BOTTOM) {
    x = Chaos::Instance()->GetRandom(0.0f, _windowSize.x);
    y = _windowSize.y + circle->_radius;
  }

  auto positionComponent = std::make_shared<PositionComponent>(x, y, 0);
  positionComponent->SetID(alien->GetID());
  alien->AddComponent(positionComponent);

  auto bt = make_shared<BT>();
  auto follow = make_shared<Follow>(positionComponent, shipPosition);
  auto trigger = make_shared<Trigger>(2000.0f);
  auto parallel = make_shared<Parallel>(0, 2);
  parallel->AddChildren(follow);
  auto sequence = make_shared<Sequence>();
  sequence->AddChildren(trigger);
  auto shoot = make_shared<Shoot>(positionComponent);
  sequence->AddChildren(shoot);
  parallel->AddChildren(sequence);
  bt->SetRoot(parallel);
  auto aiComponent = make_shared<AIComponent>(bt);
  aiComponent->SetID(alien->GetID());
  alien->AddComponent(aiComponent);

  return alien;
}

void EntityMaker::CreateExplosion(float x, float y, const CreateExplosionEvent::ExplosionIndex& index)
{
  auto explosion = _ecs->CreateEntity();

  auto positionComponent = std::make_shared<PositionComponent>(x, y, 0);
  positionComponent->SetID(explosion->GetID());
  std::shared_ptr<Animation> animation = _explosionsAnimation[(int)index];

  auto sprite = std::make_shared<AnimatedSprite>(sf::seconds(0.06f), false, false);
  sprite->setOrigin(48, 48);
  auto animationComponent = std::make_shared<AnimationComponent>(sprite, animation);
  animationComponent->SetID(explosion->GetID());
  animationComponent->PlayAnimation();

  explosion->AddComponent(positionComponent);
  explosion->AddComponent(animationComponent);
}

void EntityMaker::CreateExplosion(const std::shared_ptr<CreateExplosionEvent>& event)
{
  this->CreateExplosion(event->_x, event->_y, event->_index);
}

void EntityMaker::initializeAnimations()
{
  auto resources = Resources::Instance();
  auto smallAsteroidTexture = resources->GetTexture("data/asteroids_small.png");
  smallAsteroidTexture->setSmooth(true);

  int left = 0, top = 0, width = 0, height = 0;
  width = height = 33;

  for(int i = 0; i < 6; i++){
    auto animation = std::make_shared<Animation>();
    animation->setSpriteSheet(*smallAsteroidTexture);
    top = i * 33;
    for(int l = 0; l < 16; l++){
      left = l * 33;
      animation->addFrame(sf::IntRect(left, top, width, height));
    }
    _smallAsteroidAnimation.emplace_back(animation);
  }

  auto bigAsteroidTexture = resources->GetTexture("data/asteroids_big.png");
  bigAsteroidTexture->setSmooth(true);
  width = height = 64;

  for(int i = 0; i < 6; i++){
    auto animation = std::make_shared<Animation>();
    animation->setSpriteSheet(*bigAsteroidTexture);
    top = i * 64;
    for(int l = 0; l < 16; l++){
      left = l * 64;
      animation->addFrame(sf::IntRect(left, top, width, height));
    }
    _bigAsteroidAnimation.emplace_back(animation);
  }

  auto explosionTexture = resources->GetTexture("data/explosions.png");
  explosionTexture->setSmooth(true);
  width = height = 96;

  for(int i = 0; i < 3; i++){
    auto animation = std::make_shared<Animation>();
    animation->setSpriteSheet(*explosionTexture);
    top = i * 96;
    for(int l = 0; l < 17; l++){
      left = l * 96;
      animation->addFrame(sf::IntRect(left, top, width, height));
    }
    _explosionsAnimation.emplace_back(animation);
  }

  auto alienTexture = resources->GetTexture("data/alien.png");
  alienTexture->setSmooth(true);
  width = height = 64;

  for(int i = 0; i < 1; i++){
    auto animation = std::make_shared<Animation>();
    animation->setSpriteSheet(*alienTexture);
    top = i * 64;
    for(int l = 0; l < 15; l++){
      left = l * 64;
      animation->addFrame(sf::IntRect(left, top, width, height));
    }
    _alienAnimation.emplace_back(animation);
  }
}

EntityMaker::EntityMaker(const ECSPtr& ecs, const sf::Vector2u& windowSize) : _ecs(ecs), _windowSize(windowSize), _asteroidVelocity(150.0f)
{
  initializeAnimations();
}