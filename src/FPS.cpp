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

#include "FPS.hpp"

void FPS::SetElapsedTime(float time)
{
  std::string fpsString = std::to_string(static_cast<int>(1.0f / time));
  _fps.setString(fpsString);
}

void FPS::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_label);
  target.draw(_fps);
}

FPS::FPS(const std::string& font, unsigned int fontSize, float positionX, float positionY)
{
  _font.loadFromFile(font);

  _label.setFont(_font);
  _label.setString("FPS:");
  _label.setCharacterSize(fontSize);
  _label.setFillColor(sf::Color(0xaa, 0xaa, 0xaa));
  _label.setPosition(positionX, positionY);

  _fps.setFont(_font);
  _fps.setString("");
  _fps.setCharacterSize(fontSize);
  _fps.setFillColor(sf::Color(0xaa, 0xaa, 0xaa));
  _fps.setPosition(positionX + 60.0f, positionY);
}

FPS::~FPS() = default;