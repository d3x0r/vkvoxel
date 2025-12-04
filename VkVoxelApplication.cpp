//#include "glm/trigonometric.hpp"
#include "sack_ucb_filelib.h"
#undef _5
#undef _15
#undef Allocate

#include "json.hpp"
#include "VkVoxelApplication.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

bool firstMouse = true;
float mouseX = WINDOW_WIDTH / 2;
float mouseY = WINDOW_HEIGHT / 2;
bool framebufferResized = false;

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    mouseX = (float)xPos;
    mouseY = (float)yPos;
}

using json = nlohmann::json;

namespace VkVoxel {
    void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<VkVoxelApplication*>(glfwGetWindowUserPointer(window));
        app->resizeFramebuffer();
    }
    
    void VkVoxelApplication::run() {
        init();
        mainLoop();
        cleanup();
    }

    void VkVoxelApplication::resizeFramebuffer() {
        renderer->framebufferResized = true;
    }

    void VkVoxelApplication::mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            
            InputState inputState;

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                inputState.leftSpeed = 1.0f;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                inputState.rightSpeed = 1.0f;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                inputState.forwardSpeed = 1.0f;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                inputState.backwardSpeed = 1.0f;

            if (firstMouse) {
                lastMouseX = mouseX;
                lastMouseY = mouseY;
                firstMouse = false;
            }

            float xOffset = mouseX - lastMouseX;
            float yOffset = lastMouseY - mouseY;

            inputState.yawSpeed = xOffset;
            inputState.pitchSpeed = yOffset;

            lastMouseX = mouseX;
            lastMouseY = mouseY;

            world.update(inputState);
            world.render();
        }
    }
    
    void VkVoxelApplication::init() {
	    glfwInit();
	    glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
	    window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT,
	                               "VkVoxel Application", nullptr, nullptr );
	    glfwSetWindowUserPointer( window, this );
	    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
	    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN );
	    // glfwSetInputMode( window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE );
	    glfwSetCursorPosCallback( window, mouse_callback );

	    renderer = std::make_shared<VkRenderer>();
	    renderer->setWindow( window );

	    camera = std::make_shared<Camera>( WINDOW_WIDTH, WINDOW_HEIGHT );
	    VECTOR tmp = { 0, 2, -8 };
        camera->setPosition( tmp );
        renderer->initializeDevice();

        std::shared_ptr<TextureAtlas> textureAtlas = renderer->createTextureAtlas();
        std::ifstream i("textures/blocks.json");
	     nlohmann::json j;
        i >> j;

        for (auto texture : j["textures"]) {
            textureAtlas->addTexture(texture["name"], texture["file"]);
        }

        for( auto blockTypeJson : j[ "blockTypes" ] ) {
		     BlockType blockType;
		     blockType.frontTexture    = blockTypeJson[ "front" ][ "texture" ];
		     blockType.frontColor[ 0 ] = blockTypeJson[ "front" ][ "color" ][ 0 ];
		     blockType.frontColor[ 1 ] = blockTypeJson[ "front" ][ "color" ][ 1 ];
		     blockType.frontColor[ 2 ] = blockTypeJson[ "front" ][ "color" ][ 2 ];

		     blockType.leftTexture     = blockTypeJson[ "left" ][ "texture" ];
		     blockType.leftColor[ 0 ]  = blockTypeJson[ "left" ][ "color" ][ 0 ];
		     blockType.leftColor[ 1 ]  = blockTypeJson[ "left" ][ "color" ][ 1 ];
		     blockType.leftColor[ 2 ]  = blockTypeJson[ "left" ][ "color" ][ 2 ];

		     blockType.rightTexture    = blockTypeJson[ "right" ][ "texture" ];
		     blockType.rightColor[ 0 ] = blockTypeJson[ "right" ][ "color" ][ 0 ];
		     blockType.rightColor[ 1 ] = blockTypeJson[ "right" ][ "color" ][ 1 ];
		     blockType.rightColor[ 2 ] = blockTypeJson[ "right" ][ "color" ][ 2 ];

		     blockType.backTexture     = blockTypeJson[ "back" ][ "texture" ]; 
		     blockType.backColor[ 0 ]  = blockTypeJson[ "back" ][ "color" ][ 0 ];
		     blockType.backColor[ 1 ]  = blockTypeJson[ "back" ][ "color" ][ 1 ];
		     blockType.backColor[ 2 ]  = blockTypeJson[ "back" ][ "color" ][ 2 ];

		     blockType.topTexture      = blockTypeJson[ "top" ][ "texture" ];
		     blockType.topColor[ 0 ]   = blockTypeJson[ "top" ][ "color" ][ 0 ];
		     blockType.topColor[ 1 ]   = blockTypeJson[ "top" ][ "color" ][ 1 ];
		     blockType.topColor[ 2 ]   = blockTypeJson[ "top" ][ "color" ][ 2 ];

		     blockType.bottomTexture   = blockTypeJson[ "bottom" ][ "texture" ];
		     blockType.bottomColor[ 0 ]
		          = blockTypeJson[ "bottom" ][ "color" ][ 0 ];
		     blockType.bottomColor[ 1 ]
		          = blockTypeJson[ "bottom" ][ "color" ][ 1 ];
		     blockType.bottomColor[ 2 ]
		          = blockTypeJson[ "bottom" ][ "color" ][ 2 ];

		     renderer->addBlockType( blockType );
	     }

        renderer->initialize();
        world.initialize(renderer, camera);
    }

    void VkVoxelApplication::cleanup() {
        renderer->waitIdle();
        renderer->cleanup();

        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

