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

#include "TopLayer.hpp"

using namespace std;
USING_EVENTS_NAMESPACE

void TopLayer::Init()
{
  auto events = Events::Instance();
  events->RegisterListener<UpdateScoresEvent>(EventListener("TopLayer", std::addressof(*this), &TopLayer::onUpdateScoresEvent));
  events->RegisterListener<UpdateLevelEvent>(EventListener("TopLayer", std::addressof(*this), &TopLayer::onUpdateLevelEvent));
}

void TopLayer::onUpdateScoresEvent(const EventPtr& e)
{
  auto updateScoresEvent = std::static_pointer_cast<UpdateScoresEvent>(e);
  std::string scores = std::to_string(updateScoresEvent->_scores);
  _scores.setString(scores);

  if(updateScoresEvent->_scores > _high){
    _high = updateScoresEvent->_scores;
    string high = to_string(_high);
    _highScores.setString(high);
  }
}

void TopLayer::onUpdateLevelEvent(const EventPtr& e)
{
  auto updateLevelEvent = static_pointer_cast<UpdateLevelEvent>(e);
  string level = to_string(updateLevelEvent->_level);
  _level.setString(level);
}

void TopLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_scoresLabel);
  target.draw(_scores);
  target.draw(_levelLabel);
  target.draw(_level);
  target.draw(_highScoresLabel);
  target.draw(_highScores);
}

TopLayer::TopLayer(const sf::Vector2u& windowSize, const std::string& font, unsigned int fontSize) : _windowSize(windowSize), _high(0)
{
  _font.loadFromFile(font);

  float positionX = 20.0f;
  float positionY = 20.0f;

  _scoresLabel.setFont(_font);
  _scoresLabel.setString("Scores:");
  _scoresLabel.setCharacterSize(fontSize);
  _scoresLabel.setFillColor(sf::Color::White);
  _scoresLabel.setPosition(positionX, positionY);

  _scores.setFont(_font);
  _scores.setString("0");
  _scores.setCharacterSize(fontSize);
  _scores.setFillColor(sf::Color::White);
  _scores.setPosition(positionX + 90.0f, positionY);

  _levelLabel.setFont(_font);
  _levelLabel.setString("Level:");
  _levelLabel.setCharacterSize(fontSize);
  _levelLabel.setFillColor(sf::Color::White);
  _levelLabel.setPosition(_windowSize.x / 2.0f - _levelLabel.getLocalBounds().width / 2.0f, positionY);

  _level.setFont(_font);
  _level.setString("1");
  _level.setCharacterSize(fontSize);
  _level.setFillColor(sf::Color::White);
  _level.setPosition(_windowSize.x / 2.0f - _levelLabel.getLocalBounds().width / 2.0f + 70.0f, positionY);

  _highScoresLabel.setFont(_font);
  _highScoresLabel.setString("High scores:");
  _highScoresLabel.setCharacterSize(fontSize);
  _highScoresLabel.setFillColor(sf::Color::White);
  _highScoresLabel.setPosition(_windowSize.x - 250.0f, positionY);

  _highScores.setFont(_font);
  _highScores.setString("0");
  _highScores.setCharacterSize(fontSize);
  _highScores.setFillColor(sf::Color::White);
  _highScores.setPosition(_windowSize.x - 110.0f, positionY);
}

TopLayer::~TopLayer()
{
  auto events = Events::Instance();
  events->UnregisterListener("TopLayer");
}