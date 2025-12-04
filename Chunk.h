#ifndef __CHUNK_H_
#define __CHUNK_H_

#include <cstdint>
#include <vector>
#define NEED_VECTLIB_ALIASES
#include "sack_ucb_filelib.h"
#include "BlockType.h"
#include "Vertex.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 128

namespace VkVoxel {
    class Chunk {
    public:
        int xPos, zPos;
        uint32_t blocks[CHUNK_HEIGHT][CHUNK_SIZE][CHUNK_SIZE];

        Chunk(int x, int y);
        void build(const std::vector<BlockType>& blockTypes);
	     PMatrix getTransform( PMatrix out,
	                           PMatrix proj,
	                           PMatrix view);
        uint32_t getVertexCount();
        uint32_t getIndexCount();

        virtual void cleanup() = 0;

    protected:
        virtual void prepare(const VertexPool& vertices, const std::vector<uint32_t>& indices) = 0;

    private:
	     TRANSFORM *_model = EXTERNAL_NAME(CreateNamedTransform)( NULL );

        uint32_t _xPos;
        uint32_t _yPos;
        size_t _lastSize;
        uint32_t _vertexCount;
        uint32_t _indexCount;
    };
}

#endif
