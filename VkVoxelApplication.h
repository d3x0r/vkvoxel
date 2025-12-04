#ifndef __VK_VOXEL_APPLICATION_
#define __VK_VOXEL_APPLICATION_

#include "sack_ucb_filelib.h"
#undef _5
#undef _15

#include "VkRenderer.h"
#include "World.h"

namespace VkVoxel {
    class VkVoxelApplication {
    public:
        void run();

        void resizeFramebuffer();

    private:
        void init();
        void mainLoop();
        void cleanup();
        
        bool firstMouse = true;
        float lastMouseX;
        float lastMouseY;

        std::shared_ptr<VkRenderer> renderer;
        std::shared_ptr<Camera> camera;
        World world;
        GLFWwindow* window;
    };
}

#endif
