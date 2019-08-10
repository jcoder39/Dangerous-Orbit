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

#ifndef DANGEROUSORBIT_MATH_HPP
#define DANGEROUSORBIT_MATH_HPP

#define _USE_MATH_DEFINES

#include <math.h>
#include "Quasura/Common.hpp"

class Math : public quasura::common::Singleton<Math>
{
  friend class quasura::common::Singleton<Math>;

public:

  bool IntersectCircleRect(float circleOriginX, float circleOriginY, float circleR, float rectX, float rectY, float rectW, float rectH, float rectA)
  {
    auto inRad = (rectA * M_PI) / 180;

    double rectOriginX = rectX + rectW / 2;
    double rectOriginY = rectY + rectH / 2;

    double rotatedCircleX = cos(inRad) * (circleOriginX - rectOriginX) - sin(inRad) * (circleOriginY - rectOriginY) + rectOriginX;
    double rotatedCircleY = sin(inRad) * (circleOriginX - rectOriginX) + cos(inRad) * (circleOriginY - rectOriginY) + rectOriginY;

    double closestX = 0, closestY = 0;
    if (rotatedCircleX  < rectX) {
      closestX = rectX;
    } else if (rotatedCircleX  > rectX + rectW) {
      closestX = rectX + rectW;
    } else {
      closestX = rotatedCircleX;
    }
    if (rotatedCircleY < rectY) {
      closestY = rectY;
    } else if (rotatedCircleY > rectY + rectH) {
      closestY = rectY + rectH;
    } else {
      closestY = rotatedCircleY;
    }

    double distance = this->Distance(rotatedCircleX, rotatedCircleY, closestX, closestY);
    return distance < circleR;
  }

  bool IntersectTwoCircles(float circleOriginX, float circleOriginY, float circleR, float circleOriginX1, float circleOriginY1, float circleR1)
  {
    return std::sqrt((circleOriginX - circleOriginX1) * (circleOriginX - circleOriginX1) + (circleOriginY - circleOriginY1) * (circleOriginY - circleOriginY1)) <= (circleR + circleR1);
  }

  double Distance(double fromX, double fromY, double toX, double toY)
  {
    double a = std::abs(fromX - toX);
    double b = std::abs(fromY - toY);

    return std::sqrt((a * a) + (b * b));
  }
};

#endif //DANGEROUSORBIT_MATH_HPP
