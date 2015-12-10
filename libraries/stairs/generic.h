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
//
#include "Arduino.h"
//
// ################################################################################################
// ################################################################################################

/// ###############################################################################################
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

/// ###############################################################################################
/**
  * @brief The Power enum
  */
enum Power {
  PowerOff  = 0,
  PowerOn   = 1
};

/// ###############################################################################################
/**
  * @brief The LedStatus enum
  */
enum Dim {
  DimUndefined = 0,
  DimUp        = 1,
  DimDown      = 2,
};

/// ###############################################################################################
/**
  * @brief The AnimationStatus enum
  */
enum AnimationStatus {
  AnimationStatusOff = 0,
  AnimationStatusOn  = 1,
};
