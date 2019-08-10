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

#ifndef DANGEROUSORBIT_RESOURCES_HPP
#define DANGEROUSORBIT_RESOURCES_HPP

#include <memory>
#include <map>
#include <string>
#include "SFML/Graphics.hpp"
#include "Quasura/Common.hpp"

class Resources : public quasura::common::Singleton<Resources>
{
  friend class quasura::common::Singleton<Resources>;
  using TexturePtr = std::shared_ptr<sf::Texture>;

public:
  TexturePtr GetTexture(const std::string& path)
  {
    if(_textures.find(path) == _textures.end()){
      TexturePtr texture = std::make_shared<sf::Texture>();
      texture->loadFromFile(path);
      _textures.insert({path, texture});

      return texture;
    }

    return _textures.at(path);
  }

private:
  std::map<std::string, TexturePtr> _textures;
};

#endif //DANGEROUSORBIT_RESOURCES_HPP
