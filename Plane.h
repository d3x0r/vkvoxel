#ifndef __PLANE_H_
#define __PLANE_H_

#include "sack_ucb_filelib.h"
#undef _5
#undef _15
#include "glm/vec4.hpp"


namespace VkVoxel {
    class Plane {
    public:
	    VECTOR4 normal;
        VECTOR4 position;
	    glm::vec4 gNormal;
	     glm::vec4 gPosition;
    };
    }

#endif