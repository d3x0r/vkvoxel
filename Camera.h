#ifndef __CAMERA_H_
#define __CAMERA_H_
#define NEED_VECTLIB_ALIASES
#define VECTOR_LIBRARY_IS_EXTERNAL
#include "sack_ucb_filelib.h"
#undef _5
#undef _15

#include "Frustum.h"

namespace VkVoxel {
    class Camera {
    public:
        Camera(uint32_t resWidth, uint32_t resHeight);
        
        void rebuildProjection(uint32_t resWidth, uint32_t resHeight);
        PMatrix getProjection();
	     PMatrix getView();
	     
        void setPosition(const PCVECTOR position);
	     PVECTOR getPosition();
	     PVECTOR getFront();

        void setRotation(float pitch, float yaw);
        float getPitch();
        float getYaw();

        void move(PCVECTOR direction, float amount);

        Frustum getFrustum();
	     void updateCamera();

	   private:

        // Our view and projection matrix
        MATRIX _projection;
	   MATRIX _view;

        // Our FPS camera state.
        VECTOR _position;
	   VECTOR _front;

       VECTOR4 rotation = { 0, 1, 0, 0 };
	     VECTOR4 orientation = { 0, 1, 0, 0 };
	     ;
	     float _pitch;
        float _yaw;

        // Our cameras frustum
        Frustum _frustum;

    };
};

#endif
