/******************************************************************************
**
** Anyone is free to copy, modify, publish, use, compile, sell, or
** distribute this software, either in source code form or as a compiled
** binary, for any purpose, commercial or non-commercial, and by any
** means.
**
** In jurisdictions that recognize copyright laws, the author or authors
** of this software dedicate any and all copyright interest in the
** software to the public domain. We make this dedication for the benefit
** of the public at large and to the detriment of our heirs and
** successors. We intend this dedication to be an overt act of
** relinquishment in perpetuity of all present and future rights to this
** software under copyright law.
**
** DISCLAIMER
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
** OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
** ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
** OTHER DEALINGS IN THE SOFTWARE.
**
******************************************************************************/

/**
*** @autor Sven Stadler <sven.stadler@web.de>
**/

// ################################################################################################
// ################################################################################################
//
#include "Arduino.h"
//
#include "canimationstatus.h"
//
// ################################################################################################
// ################################################################################################

CAnimationStatus::CAnimationStatus()
  : m_animationStatus({AnimationStatusOff, AnimationStatusOff}),
    m_elements({0,0})
{
}

// ################################################################################################
// ################################################################################################

AnimationStatus CAnimationStatus::getStatus(Direction direction) const
{
  // safty check
  if (direction >= NumberOfDirections){
    Serial.println("CAnimationStatus::getStatus() (direction >= NumberOfDirections)");
    return  AnimationStatusOff;
  }
  return m_animationStatus[direction];
}

// ################################################################################################
// ################################################################################################

bool CAnimationStatus::setStatus(Direction direction, AnimationStatus animationStatus)
{
  // safty check
  if (direction >= NumberOfDirections){
    Serial.println("CAnimationStatus::getStatus() (direction >= NumberOfDirections)");
    return  false;
  }

  if (m_animationStatus[direction] != animationStatus) {
    m_animationStatus[direction] = animationStatus;
  }

  return true;
}

// ################################################################################################
// ################################################################################################

bool CAnimationStatus::isActive(Direction direction)
{
  return (m_animationStatus[direction] == AnimationStatusOn) ? true : false;
}
