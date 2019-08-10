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

#ifndef DANGEROUSORBIT_KEYEVENT_HPP
#define DANGEROUSORBIT_KEYEVENT_HPP

#include <SFML/Window/Event.hpp>
#include "Quasura/Events.hpp"

struct KeyEvent : public quasura::events::Event
{
  sf::Event::KeyEvent _keyEvent;
  bool _pressed;

  KeyEvent(const sf::Event::KeyEvent& event, bool pressed) : _keyEvent(event), _pressed(pressed) {}
};

#endif //DANGEROUSORBIT_KEYEVENT_HPP
