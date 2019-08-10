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

//#define _HAS_AUTO_PTR_ETC 1 // enable auto_ptr. it should be in AudioDevice.cpp. For MSVC++

#ifdef WINDOWS
#include <windows.h>
#include <synchapi.h>
#endif

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "Quasura/Events.hpp"
#include "FPS.hpp"
#include "TopLayer.hpp"
#include "GameMaster.hpp"
#include "events/KeyEvent.hpp"

using namespace std;
using namespace sf;
USING_EVENTS_NAMESPACE

int main()
{
  sf::ContextSettings contextSettings;
  contextSettings.depthBits = 24;
  contextSettings.antialiasingLevel = 8;

  sf::Vector2f screenSize(1024, 768);
  sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Dangerous Orbit(free version)", sf::Style::Default, contextSettings);
  window.setKeyRepeatEnabled(false);
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  FPS fps("data/fonts/Cosmic.ttf", 24, 20.0f, screenSize.y - 40.0f);
  TopLayer scores(window.getSize(), "data/fonts/Cosmic.ttf", 24);
  scores.Init();

  sf::Texture texture;
  texture.loadFromFile("data/background.png");

  sf::Sprite background;
  background.setTexture(texture);

  GameMaster gm(window);
  gm.Init();

  sf::Clock clock;
  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {

      if(sf::Event::Closed == event.type) {
        window.close();
      }

      if(Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window.close();
      }

      if(sf::Event::LostFocus == event.type){
        gm.Pause();
      }

      if(sf::Event::GainedFocus == event.type){
        gm.Resume();
      }

      if(sf::Event::KeyReleased == event.type){
        auto events = Events::Instance();
        auto keyEvent = make_shared<KeyEvent>(event.key, false);
        events->Emit(keyEvent);
      }

      if(sf::Event::KeyPressed == event.type){
        auto events = Events::Instance();
        auto keyEvent = make_shared<KeyEvent>(event.key, true);
        events->Emit(keyEvent);
      }
    }

    window.clear();

    window.draw(background);

    sf::Time elapsed = clock.restart();
    gm.Update(elapsed);

    float currentTime = elapsed.asSeconds();
    fps.SetElapsedTime(currentTime);
    window.draw(fps);

    window.draw(scores);

    window.display();
  }

  return 0;
}