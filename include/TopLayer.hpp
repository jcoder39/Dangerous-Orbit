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

#ifndef DANGEROUSORBIT_SCORES_HPP
#define DANGEROUSORBIT_SCORES_HPP

#include "SFML/Graphics.hpp"
#include "Quasura/Events.hpp"
#include "events/UpdateScoresEvent.hpp"
#include "events/UpdateLevelEvent.hpp"

class TopLayer final : public sf::Drawable
{
public:
  TopLayer(const sf::Vector2u& windowSize, const std::string& font, unsigned int fontSize);
  ~TopLayer() override;

  void Init();
private:
  sf::Vector2u _windowSize;
  sf::Font _font;
  sf::Text _scoresLabel;
  sf::Text _scores;
  sf::Text _levelLabel;
  sf::Text _level;
  sf::Text _highScoresLabel;
  sf::Text _highScores;
  long _high;

  void onUpdateScoresEvent(const quasura::events::EventPtr& e);
  void onUpdateLevelEvent(const quasura::events::EventPtr& e);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif //DANGEROUSORBIT_SCORES_HPP
