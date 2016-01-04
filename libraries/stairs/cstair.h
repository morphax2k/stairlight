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
#include "cstage.h"
#include "clist.h"
#include "generic.h"
#include "cpotentiometer.h"
#include "canimationstatus.h"
//
// ################################################################################################
// ################################################################################################

class CStair
{
  public:

    /// ###########################################################################################
    /**
      * @brief The constructor
      */
    CStair();

    /// ###########################################################################################
    /**
      * @brief Set the verbose level
      *
      * @param verbose  enable or disable verbose level of this class instance
      */
    void setVerbose(bool verbose);

    /// ###########################################################################################
    /**
      * @brief Add a stage to this stair instance
      *
      * @param analogPinNumber    an analog pin with PWM support
      *
      * @return true if new stage was added other wise false (duplicate key entry)
      */
    bool addStage(int analogPinNumber);

    /// ###########################################################################################
    /**
      * @brief addHoldTimePotentiometer
      *
      * @param analogPinNumber  an analog pin
      *
      * @return
      */
    bool addHoldTimePotentiometer(int analogPinNumber);

    /// ###########################################################################################
    /**
      * @brief addStartDelayPotentiometer
      *
      * @param analogPinNumber  an analog pin
      *
      * @return
      */
    bool addStartDelayPotentiometer(int analogPinNumber);

    /// ###########################################################################################
    /**
      * @brief addStepWidthPotentiometer
      *
      * @param analogPinNumber
      *
      * @return
      */
    bool addStepWidthPotentiometer(int analogPinNumber);

    /// ###########################################################################################
    /**
      * @brief adjustPotentiometers
      * @param currentTime
      */
    void adjustPotentiometers(const unsigned long currentTime = 0);

    /// ###########################################################################################
    /**
      * @brief getAnimation
      *
      * @param direction
      * @param animationStatus
      *
      * @return true on success otherwise false
      */
    bool getAnimation(Direction direction, AnimationStatus * animationStatus) const;

    /// ###########################################################################################
    /**
      * @brief setAnimation
      * @param direction
      * @param animationStatus
      */
    bool setAnimation(Direction direction, AnimationStatus animationStatus = AnimationStatusOn);

    /// ###########################################################################################
    /**
      * @brief executeAnimation
      * @param currentTime
      *
      * @return true if animation is ongoing on one or all stairs otherwise false and ready for next
      *         activation
      */
    bool executeAnimation(const unsigned long currentTime);

  private:

    /// ###########################################################################################
    /**
      * @brief The Stage enum
      */
    enum Stage {
      StageError        = 0,
      StageNext,
      StageSkipNext,
      StageAlreadyInUse,
    };

    /// ###########################################################################################
    /**
      * @brief handleStage
      * @param i
      * @return
      */
    Stage handleStage(const int i, const Direction direction, const unsigned long currentTime) ;

    /// ###########################################################################################
    /// The attributes
    ///
    CList<CStage> m_stage;
    CAnimationStatus m_animation;

    CPotentiometer<unsigned int> m_stageHoldTime;
    CPotentiometer<unsigned short> m_startDelay;
    CPotentiometer<unsigned char> m_brightnessStepWidth;

    unsigned long m_lastPotentiometerAdjustment;
    bool m_verbose;
    bool m_isAnimationRunning;

};
