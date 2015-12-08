
/**
*** @autor Sven Stadler <sven.stadler@web.de>
**/

#pragma once

// ################################################################################################
// ################################################################################################
//
#include "Arduino.h"
//
// ################################################################################################
// ################################################################################################

/**
  * @brief The Direction enum
  */
enum Direction
{
  DirectionUp        = 0,
  DirectionDown      = 1,
  NumberOfDirections = 2,
  DirectionUndefined = 3
};

enum Power {
  PowerOff  = 0,
  PowerOn   = 1
};

/**
  * @brief The LedStatus enum
  */
enum Dim {
  DimUndefined = 0,
  DimUp        = 1,
  DimDown      = 2,
};

/**
  * @brief The AnimationStatus enum
  */
enum AnimationStatus {
  AnimationStatusOff = 0,
  AnimationStatusOn  = 1,
};
