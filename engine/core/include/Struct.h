#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__

#include "BaseObject.h"

namespace engine
{
      #define PI 3.1415926

      struct Struct
      {
      public:
            
      protected:
            Struct(void){}
            ~Struct(void){}
      };

      extern const bool equal(const float & param_left, const float & param_right);
}

#endif //__STRUCT_H__