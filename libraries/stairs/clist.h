/*****************************************************************************
**
** Copyright (c) 2015 Blackhack
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
** https://github.com/blackhack/ArduLibraries/blob/master/Releases/SimpleList.rar?raw=true
**
******************************************************************************/

#pragma once

// ################################################################################################
// ################################################################################################
//
#include "Arduino.h"
//
// ################################################################################################
// ################################################################################################

#ifndef NULL
#define NULL 0
#endif

template<typename T>
class CList
{
  public:

    typedef T* iterator;

    /// ###########################################################################################
    /**
      * The constructor
      */
    CList()
    {
      internalArray = NULL;
      endPosition = 0;
      allocBlocks = 0;
      preAllocBlocks = 0;
    }

    /// ###########################################################################################
    /**
      * The destructor
      */
    ~CList()
    {
      delete[] internalArray;
      internalArray = NULL;
      endPosition = 0;
      allocBlocks = 0;
      preAllocBlocks = 0;
    }

    /// ###########################################################################################
    /**
      * @brief push_back
      * @param item
      */
    void push_back(T item)
    {
      if (endPosition == allocBlocks)
        allocOneBlock(false);

      internalArray[endPosition] = item;
      ++endPosition;
    }

    /// ###########################################################################################
    /**
      * @brief push_front
      * @param item
      */
    void push_front(T item)
    {
      if (endPosition == allocBlocks)
        allocOneBlock(true);
      else
      {
        for (int i = endPosition; i > 0; --i)
          internalArray[i] = internalArray[i - 1];
      }

      internalArray[0] = item;
      ++endPosition;
    }

    /// ###########################################################################################
    /**
      * @brief pop_back
      */
    void pop_back()
    {
      if (endPosition == 0)
        return;

      --endPosition;

      if (allocBlocks > preAllocBlocks)
        deallocOneBlock(false);
    }

    /// ###########################################################################################
    /**
      * @brief pop_front
      */
    void pop_front()
    {
      if (endPosition == 0)
        return;

      --endPosition;

      if (allocBlocks > preAllocBlocks)
        deallocOneBlock(true);
      else
      {
        for (int i = 0; i < endPosition; ++i)
          internalArray[i] = internalArray[i + 1];
      }
    }

    /// ###########################################################################################
    /**
      * @brief erase
      * @param position
      * @return
      */
    iterator erase(iterator position)
    {
      int offSet = int(position - internalArray);

      if (offSet == endPosition - 1) // Last item.
      {
        pop_back();
        return end();
      }

      --endPosition;

      if (allocBlocks > preAllocBlocks)
      {
        --allocBlocks;
        T* newArray = new T[allocBlocks];

        for (int i = 0; i < endPosition; ++i)
        {
          if (i >= offSet)
            newArray[i] = internalArray[i + 1];
          else
            newArray[i] = internalArray[i];
        }

        delete[] internalArray;
        internalArray = newArray;
      }
      else
      {
        for (int i = offSet; i < endPosition; ++i)
          internalArray[i] = internalArray[i + 1];
      }

      return internalArray + offSet;
    }

    /// ###########################################################################################
    /**
      * @brief reserve
      * @param size
      */
    void reserve(int size)
    {
      if (size == 0 || size < allocBlocks)
        return;

      allocBlocks = size;
      preAllocBlocks = size;

      T* newArray = new T[allocBlocks];

      for (int i = 0; i < endPosition; ++i)
        newArray[i] = internalArray[i];

      delete[] internalArray;
      internalArray = newArray;
    }

    /// ###########################################################################################
    /**
      * @brief clear
      */
    void clear()
    {
      if (allocBlocks > preAllocBlocks)
      {
        allocBlocks = preAllocBlocks;

        T* newArray = NULL;

        if (allocBlocks > 0)
          newArray = new T[allocBlocks];

        delete[] internalArray;
        internalArray = newArray;
      }

      endPosition = 0;
    }

    /// ###########################################################################################
    /**
      * @brief value
      * @param position
      * @return
      */
    inline iterator value(int position)
    {
      if (position < 0 || position >= endPosition)  {
        return NULL;
      }

      return (internalArray + position);
    }


    /// ###########################################################################################
    /**
      * @brief begin
      * @return
      */
    inline iterator begin()
    {
      return internalArray;
    }

    /// ###########################################################################################
    /**
      * @brief end
      * @return
      */
    inline iterator end()
    {
      return (internalArray + endPosition);
    }

    /// ###########################################################################################
    /**
      * @brief empty
      * @return
      */
    inline bool empty()
    {
      return (endPosition == 0);
    }

    /// ###########################################################################################
    /**
      * @brief size
      * @return
      */
    inline unsigned int size()
    {
      return endPosition;
    }

    /// ###########################################################################################
    /**
      * @brief capacity
      * @return
      */
    inline unsigned int capacity()
    {
      return allocBlocks;
    }

  private:

    /// ###########################################################################################
    /**
      * @brief AllocOneBlock
      * @param shiftItems
      */
    void allocOneBlock(bool shiftItems)
    {
      ++allocBlocks;
      T* newArray = new T[allocBlocks];

      for (int i = 0; i < endPosition; ++i)
        newArray[shiftItems ? (i + 1) : i] = internalArray[i];

      delete[] internalArray;
      internalArray = newArray;
    }

    /// ###########################################################################################
    /**
      * @brief DeAllocOneBlock
      * @param shiftItems
      */
    void deallocOneBlock(bool shiftItems)
    {
      --allocBlocks;

      if (allocBlocks == 0)
      {
        delete[] internalArray;
        internalArray = NULL;
        return;
      }

      T* newArray = new T[allocBlocks];

      for (int i = 0; i < endPosition; ++i)
        newArray[i] = internalArray[shiftItems ? (i + 1) : i];

      delete[] internalArray;
      internalArray = newArray;
    }

  private:

    /// ###########################################################################################
    /// The attributes
    T* internalArray;
    int endPosition;
    int allocBlocks;
    int preAllocBlocks;
};

