#ifndef __FRUSTUM_H_
#define __FRUSTUM_H_

#define NEED_VECTLIB_ALIASES
#include "sack_ucb_filelib.h"
#undef _5
#undef _15
#include <glm/matrix.hpp>
//#include <glm/ve
#include "Plane.h"

namespace VkVoxel {
    class Frustum {
    public:
        Frustum();
	   Frustum( const PMatrix projection, const PMatrix view );

        void fromCamera( const PMatrix projection, const PMatrix view );
	   void Frustum::fromCamera( const glm::mat4x4 &projection,
	                             const glm::mat4x4 &view );

        Plane nearPlan;
        Plane farPlane;
        Plane left;
        Plane right;
        Plane top;
        Plane bottom;
    };
}

#endif
