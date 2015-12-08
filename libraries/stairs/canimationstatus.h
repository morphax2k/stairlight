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

#pragma once

// ################################################################################################
// ################################################################################################

#include "Arduino.h"
//
#include "generic.h"
//
// ################################################################################################
// ################################################################################################

class CAnimationStatus
{
  public:

    /// ###########################################################################################
    /**
      * @brief The constructor
      */
    CAnimationStatus();

    /// ###########################################################################################
    /**
      * @brief setStatus
      *
      * @param direction
      * @param animationStatus
      *
      * @return
      */
    bool setStatus(Direction direction, AnimationStatus animationStatus);

    /// ###########################################################################################
    /**
      * @brief getStatus
      * @param direction
      * @return
      */
    AnimationStatus getStatus(Direction direction) const;

    /// ###########################################################################################
    /**
      * @brief isActive
      *
      * @param direction
      *
      * @return
      */
    bool isActive(Direction direction);

  private:

    /// ###########################################################################################
    /// The attributes
    ///
    AnimationStatus m_animationStatus[NumberOfDirections];
    int m_elements[NumberOfDirections];
};
