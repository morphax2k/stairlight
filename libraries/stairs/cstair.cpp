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
#include "cstair.h"
//
// ################################################################################################
// ################################################################################################

constexpr unsigned long MaxHoldTimeMS         = 300000;                           // ~ 5 min
constexpr unsigned long MaxHoldTimeDivider    = MaxHoldTimeMS / 1023;

constexpr float MaxBrightnessStepWidth        = 10.0f;                            // max step width
constexpr float MaxBrightnessStepWidthDivider = MaxBrightnessStepWidth / 1023.0;


// ################################################################################################
// ################################################################################################

CStair::CStair()
  : m_verbose(false),
    m_startDelay(1000),
    m_brightnessStepWidth(1),
    m_stageHoldTime(10000)
{
}

// ################################################################################################
// ################################################################################################

void CStair::setVerbose(bool verbose)
{
  m_verbose = verbose;
  m_animation.setVerbose(verbose);
}

// ################################################################################################
// ################################################################################################

bool CStair::addStage(int analogPinNumber)
{
  if (analogPinNumber < 0) {
    // unable to process
    if (m_verbose) {
      Serial.println("CStair::addStage(analogPinNumber) (invalid argument)");
    }
    return false;
  }

  // check if this analog pin is already used
  for (int i =  0; i <  m_stage.size(); ++i) {
    if (m_stage.value(i)->pwmPin == analogPinNumber) {
      return false;
    }
  }

  // create an new stage and store it on the stage list (push back to have the correct order)
  CStage stage;
  // the assigned analog pin on this stage
  stage.pwmPin = analogPinNumber;

  pinMode(stage.pwmPin, OUTPUT);
  m_stage.push_back(stage);
}

// ################################################################################################
// ################################################################################################

bool CStair::addHoldTimePotentiometer(int analogPinNumber)
{
  if (analogPinNumber < 0) {
    // unable to process
    if (m_verbose) {
      Serial.println("CStair::addHoldTimePotentiometer(analogPinNumber) (invalid argument)");
    }
    return false;
  }

  m_stageHoldTime.analogPin = analogPinNumber;
  pinMode(analogPinNumber, INPUT);
  return true;
}

// ################################################################################################
// ################################################################################################

bool CStair::addStartDelayPotentiometer(int analogPinNumber)
{
  if (analogPinNumber < 0) {
    // unable to process
    if (m_verbose) {
      Serial.println("CStair::addStartDelayPotentiometer(analogPinNumber) (invalid argument)");
    }
    return false;
  }

  m_startDelay.analogPin = analogPinNumber;
  pinMode(analogPinNumber, INPUT);
  return true;
}

// ################################################################################################
// ################################################################################################

bool CStair::addStepWidthPotentiometer(int analogPinNumber)
{
  if (analogPinNumber < 0) {
    // unable to process
    if (m_verbose) {
      Serial.println("CStair::addStepWidthPotentiometer(analogPinNumber) (invalid argument)");
    }
    return false;
  }

  m_brightnessStepWidth.analogPin = analogPinNumber;
  pinMode(analogPinNumber, INPUT);
  return true;
}

// ################################################################################################
// ################################################################################################

void CStair::adjustPotentiometers()
{
  // adjust the hold time (light period)
  if (m_stageHoldTime.analogPin >= 0) {
    if (!m_stageHoldTime.readResistance()) {
      if (m_verbose) {
        Serial.println("CStair::adjustPotentiometers() (m_stageHoldTime.readResistance() failed)");
      }
    }

    // max possible value is MaxHoldTimeMS ( ~ 300 seconds equivalent to ~ 5 minutes)
    m_stageHoldTime.value = ((m_stageHoldTime.resistance * MaxHoldTimeMS) / MaxHoldTimeDivider);

    if (m_verbose) {

      Serial.print("Adjust HoldTimePotentiometer = ");
      Serial.print(m_stageHoldTime.value);
      Serial.print(" ms resistance(");
      Serial.print(m_stageHoldTime.resistance);
      Serial.println(")");
    }
  }

  // adjust the step width of a lamp (pwm signal takes 0...254),
  // with wich width should the brightness of the lamp increased?
  if (m_brightnessStepWidth.analogPin >= 0) {
    if (!m_brightnessStepWidth.readResistance()) {
      if (m_verbose) {
        Serial.println("CStair::adjustPotentiometers() (m_brightnessStepWidth.readResistance() failed)");
      }
    }

    // max possible value is MaxBrightnessStepWidth ( 10 steps out of 255)
    int integer = (int)((float)m_brightnessStepWidth.resistance * MaxBrightnessStepWidthDivider);
    m_brightnessStepWidth.value = (!integer) ? 1 : integer;

    if (m_verbose) {

      Serial.print("Adjust brightnessStepWidthPotentiometer = ");
      Serial.print(m_brightnessStepWidth.value);
      Serial.print(" step(s) resistance(");
      Serial.print(m_brightnessStepWidth.resistance);
      Serial.println(")");
      Serial.println(MaxBrightnessStepWidthDivider);
    }
  }

  if (m_brightnessStepWidth.analogPin >= 0) {
    if (!m_brightnessStepWidth.readResistance()) {
      if (m_verbose) {
        Serial.println("CStair::adjustPotentiometers() (m_brightnessStepWidth.readResistance() failed)");
      }
    }
  }
}

// ################################################################################################
// ################################################################################################

bool CStair::getAnimation(Direction direction, AnimationStatus * animationStatus) const
{
  if (!animationStatus) {
    if (m_verbose) {
      Serial.println("CStair::getAnimation(..., animationStatus) (invalid argument)");
    }
    return false;
  }

  *animationStatus = m_animation.getStatus(direction);
  return true;
}

// ################################################################################################
// ################################################################################################

bool CStair::setAnimation(Direction direction, AnimationStatus animationStatus)
{
  return m_animation.setStatus(direction, animationStatus);
}

// ################################################################################################
// ################################################################################################

bool CStair::executeAnimation(unsigned long currentTime)
{
  Stage stageStatus;

  auto stageProcessed = [&] ( const int i, const Direction & direction, bool & areAllStagesReady, bool & areAllStagesPerDirectionReady) {

    if (m_stage.value(i)->isReadyForNextAnimation) {
      // skip this stage we have to wait until all stages are done
      return true;
    }

    stageStatus = handleStage(i, direction, currentTime);
    if (stageStatus == StageSkipNext || stageStatus == StageAlreadyInUse) {
      areAllStagesReady = areAllStagesPerDirectionReady = false;

      return false;
    }
    areAllStagesReady = areAllStagesPerDirectionReady = false;

    return true;
  };

  bool areAllStagesPerDirectionReady = true;
  for (int direction = 0; direction < NumberOfDirections; ++direction) {

    if (m_animation.isActive((Direction)direction)) {

      bool areAllStagesReady = true;

      // walking downstairs
      if (direction == DirectionDown) {

        for (int i =  0; i <  m_stage.size(); ++i) {

          if (!stageProcessed(i, DirectionDown, areAllStagesReady, areAllStagesPerDirectionReady)) {
            break;
          }
        }

      } else if (direction == DirectionUp) {

        // walking upstairs
        for (int i = (m_stage.size() - 1); i >= 0  ; --i) {

          if (!stageProcessed(i, DirectionUp, areAllStagesReady, areAllStagesPerDirectionReady)) {
            break;
          }
        }
      }

      // this direction reaches the end, all stages are done with there animation
      // let reset the animation status
      if (areAllStagesReady) {
        m_animation.setStatus((Direction) direction, AnimationStatusOff);
        for (int i =  0; i <  m_stage.size(); ++i) {
          if (m_stage.value(i)->direction == direction) {
            m_stage.value(i)->reset();
          }
        }
      }
    }
  }

  return !areAllStagesPerDirectionReady;
}

// ################################################################################################
// ################################################################################################

CStair::Stage CStair::handleStage(const int i, const Direction direction, const unsigned long currentTime)
{
  if (i < 0 || i > (m_stage.size() - 1)) {
    if (m_verbose) {
      Serial.println("CStair::handleStage() unhandable case, index out of bounds");
    }
    // unhandable case, index out of bounds
    return StageError;
  }

  CStage * stage = m_stage.value(i);

  if (!stage) {
    if (m_verbose) {
      Serial.println("CStair::handleStage() !stage");
    }
    // FIXME: assert?!
    return StageError;
  }

  switch (stage->power) {
    case PowerOff:

      if (stage->direction == DirectionUndefined) {

        stage->power = PowerOn;
        stage->brightness = 0;
        stage->startDelay = m_startDelay.value;


        stage->direction = direction;
        stage->startTime = currentTime;
        stage->dim = DimUp;
        if (m_verbose) {
          Serial.print("Led             = "); Serial.println(stage->pwmPin);
          Serial.print("startDelay      = "); Serial.println(stage->startDelay);
          Serial.println("------------------------- ");
        }

      }
      handleStage(i, direction, currentTime);
      return StageSkipNext;

    case PowerOn:

      // collision detection
      if (stage->direction != direction) {
        if (m_verbose) {
          Serial.println("CStair::handleStage() (stage->direction != direction)");
        }
        return StageAlreadyInUse;
      }

      switch (stage->dim) {

        case DimUp:

          if ((stage->startTime + stage->startDelay) > currentTime) {
            // skip further things it isn't time for this LED to show up any activity
            return StageSkipNext;
          }

          if (stage->brightness != 0xFF) {

            if ((stage->brightness + m_brightnessStepWidth.value) >= 0xFF) {
              // maximum brightness reached, enable hold
              stage->brightness = 0xFF;
              stage->holdTime = currentTime;

            } else {

              stage->brightness += m_brightnessStepWidth.value;
            }

            analogWrite(stage->pwmPin, stage->brightness);

          } else {

            if (stage->holdTime == 0) {
              if (m_verbose) {
                Serial.println("CStair::handleStage() (ASSERT !!! stage->holdTime == 0)");
              }
              return StageError;
            }

            if (m_stageHoldTime.value <= (currentTime - stage->holdTime)) {
              stage->dim = DimDown;
              stage->holdTime = 0;
              // call recursive handleStage to enter one time case DimDown
              handleStage(i, direction, currentTime);
            }
          }

          break;

        case DimDown:

          if (stage->brightness != 0x00) {

            if ((stage->brightness - m_brightnessStepWidth.value) <= 0x00) {
              // minimum brightness reached, disable
              stage->reset( true /* block next animation until all stages ready */);
              if (m_verbose) {
                Serial.print("Led             = "); Serial.print(stage->pwmPin);
                Serial.println(" << block next animation until all stages ready");
              }
            } else {
              stage->brightness -= m_brightnessStepWidth.value;
            }

            analogWrite(stage->pwmPin, stage->brightness);
          }
          break;
      }

      break;
  }

  return StageNext;
}

// ################################################################################################
// ################################################################################################
