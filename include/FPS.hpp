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

#ifndef DANGEROUSORBIT_FPS_HPP
#define DANGEROUSORBIT_FPS_HPP

#include "SFML/Graphics.hpp"

class FPS final : public sf::Drawable
{
public:
  FPS(const std::string& font, unsigned int fontSize, float positionX, float positionY);
  ~FPS() override;

  void SetElapsedTime(float);
private:
  sf::Font _font;
  sf::Text _label;
  sf::Text _fps;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif //DANGEROUSORBIT_FPS_HPP
