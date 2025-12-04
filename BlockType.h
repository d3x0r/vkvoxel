#ifndef __BLOCK_TYPE_H_
#define __BLOCK_TYPE_H_

#include <vector>
#include "glm/vec3.hpp"
#include "Vertex.h"

namespace VkVoxel {

    class BlockType {
    public:
        BlockType();

        uint32_t frontTexture = 0;
        VECTOR frontColor = { 1.0f, 1.0f, 1.0f };
	     glm::vec3 g_frontColor      = { 1.0f, 1.0f, 1.0f };

        uint32_t leftTexture = 0;
	     VECTOR leftColor       = { 1.0f, 1.0f, 1.0f };

        uint32_t rightTexture = 0;
	     VECTOR rightColor      = { 1.0f, 1.0f, 1.0f };

        uint32_t backTexture = 0;
	     VECTOR backColor       = { 1.0f, 1.0f, 1.0f };

        uint32_t topTexture = 0;
	     VECTOR topColor        = { 1.0f, 1.0f, 1.0f };

        uint32_t bottomTexture = 0;
	     VECTOR bottomColor     = { 1.0f, 1.0f, 1.0f };

    };
};

#endif