#ifndef __BLOCK_H_
#define __BLOCK_H_

#include <vector>
#include "Vertex.h"

namespace VkVoxel {
const static VECTOR FRONT_FACE[4]                  = {
        { -0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }
    };
const static glm::vec3 G_FRONT_FACE[4]                  = {
        { -0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }
    };
    const static VECTOR LEFT_FACE[4] = {
        { -0.5f, -0.5f,  0.5f }, { -0.5f, -0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f,  0.5f }
    };
const static VECTOR RIGHT_FACE[ 4 ] = {
        {  0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f,  0.5f }, { 0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, -0.5f }
    };
    const static VECTOR BACK_FACE[ 4 ]  = {
        {  0.5f, -0.5f,  0.5f }, { -0.5f, -0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }
    };
const static VECTOR TOP_FACE[ 4 ]  = {
        { -0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }
    };
    const static VECTOR BOTTOM_FACE[ 4 ] = {
        { -0.5f, -0.5f,  0.5f }, {  0.5f, -0.5f,  0.5f }, {  0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f }
    };
};

#endif
