#ifndef __VK_CHUNK_H_
#define __VK_CHUNK_H_

#include "sack_ucb_filelib.h"
#undef _5
#undef _15
#undef Allocate

#include "Chunk.h"
#include "VkManager.h"

namespace VkVoxel {
    class VkChunk : public Chunk {
    public:
        VkChunk(int x, int y, std::shared_ptr<VkManager> manager);
        
        virtual void cleanup();

        VkBuffer vertexBuffer;
        VmaAllocation vertexAllocation;

        VkBuffer indexBuffer;
        VmaAllocation indexAllocation;

    protected:
        virtual void prepare(const VertexPool& vertices, const std::vector<uint32_t>& indices);

    private:
        void prepareVertexBuffer(const VertexPool& vertices);
        void prepareIndexBuffer(const std::vector<uint32_t>& indices);

        std::shared_ptr<VkManager> _manager;
        bool _prepared;
    };
}

#endif
