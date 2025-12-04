#include <glm/geometric.hpp>
#include "Frustum.h"

namespace VkVoxel {
    Frustum::Frustum() { }

    Frustum::Frustum( PMatrix projection, PMatrix view ) {
        fromCamera(projection, view);
    }

    void Frustum::fromCamera( PMatrix projection, PMatrix view ) {
	    MATRIX clipMatrix;
        ApplyM( projection, &clipMatrix, view );
        

        right.position[0] = clipMatrix[3][0] - clipMatrix[0][0];
        right.position[1] = clipMatrix[3][1] - clipMatrix[0][1];
        right.position[2] = clipMatrix[3][2] - clipMatrix[0][2];
        right.position[3] = clipMatrix[3][3] - clipMatrix[0][3];
        normalize4(right.position);

        left.position[0] = clipMatrix[3][0] + clipMatrix[0][0];
        left.position[1] = clipMatrix[3][1] + clipMatrix[0][1];
        left.position[2] = clipMatrix[3][2] + clipMatrix[0][2];
        left.position[3] = clipMatrix[3][3] + clipMatrix[0][3];
        normalize4(left.position);

        bottom.position[0] = clipMatrix[3][0] + clipMatrix[1][0];
        bottom.position[1] = clipMatrix[3][1] + clipMatrix[1][1];
        bottom.position[2] = clipMatrix[3][2] + clipMatrix[1][2];
        bottom.position[3] = clipMatrix[3][3] + clipMatrix[1][3];
        normalize4(bottom.position);

        top.position[0] = clipMatrix[3][0] - clipMatrix[1][0];
        top.position[1] = clipMatrix[3][1] - clipMatrix[1][1];
        top.position[2] = clipMatrix[3][2] - clipMatrix[1][2];
        top.position[3] = clipMatrix[3][3] - clipMatrix[1][3];
        normalize4(top.position);

        nearPlan.position[0] = clipMatrix[3][0] - clipMatrix[2][0];
        nearPlan.position[1] = clipMatrix[3][1] - clipMatrix[2][1];
        nearPlan.position[2] = clipMatrix[3][2] - clipMatrix[2][2];
        nearPlan.position[3] = clipMatrix[3][3] - clipMatrix[2][2];
        normalize4(nearPlan.position);

        farPlane.position[0] = clipMatrix[3][0] + clipMatrix[2][0];
        farPlane.position[1] = clipMatrix[3][1] + clipMatrix[2][1];
        farPlane.position[2] = clipMatrix[3][2] + clipMatrix[2][2];
        farPlane.position[3] = clipMatrix[3][3] + clipMatrix[2][3];
        normalize4(farPlane.position);
    }

    #undef normalize

     void Frustum::fromCamera( const glm::mat4x4 &projection,
                              const glm::mat4x4 &view ) {
	    glm::mat4x4 clipMatrix = projection * view;

	    right.gPosition.x       = clipMatrix[ 3 ][ 0 ] - clipMatrix[ 0 ][ 0 ];
	    right.gPosition.y       = clipMatrix[ 3 ][ 1 ] - clipMatrix[ 0 ][ 1 ];
	    right.gPosition.z       = clipMatrix[ 3 ][ 2 ] - clipMatrix[ 0 ][ 2 ];
	    right.gPosition.w       = clipMatrix[ 3 ][ 3 ] - clipMatrix[ 0 ][ 3 ];
	    right.gPosition         = glm::normalize( right.gPosition );

	    left.gPosition.x        = clipMatrix[ 3 ][ 0 ] + clipMatrix[ 0 ][ 0 ];
	    left.gPosition.y        = clipMatrix[ 3 ][ 1 ] + clipMatrix[ 0 ][ 1 ];
	    left.gPosition.z        = clipMatrix[ 3 ][ 2 ] + clipMatrix[ 0 ][ 2 ];
	    left.gPosition.w        = clipMatrix[ 3 ][ 3 ] + clipMatrix[ 0 ][ 3 ];
	    left.gPosition          = glm::normalize( left.gPosition );

	    bottom.gPosition.x      = clipMatrix[ 3 ][ 0 ] + clipMatrix[ 1 ][ 0 ];
	    bottom.gPosition.y      = clipMatrix[ 3 ][ 1 ] + clipMatrix[ 1 ][ 1 ];
	    bottom.gPosition.z      = clipMatrix[ 3 ][ 2 ] + clipMatrix[ 1 ][ 2 ];
	    bottom.gPosition.w      = clipMatrix[ 3 ][ 3 ] + clipMatrix[ 1 ][ 3 ];
	    bottom.gPosition        = glm::normalize( bottom.gPosition );

	    top.gPosition.x         = clipMatrix[ 3 ][ 0 ] - clipMatrix[ 1 ][ 0 ];
	    top.gPosition.y         = clipMatrix[ 3 ][ 1 ] - clipMatrix[ 1 ][ 1 ];
	    top.gPosition.z         = clipMatrix[ 3 ][ 2 ] - clipMatrix[ 1 ][ 2 ];
	    top.gPosition.w         = clipMatrix[ 3 ][ 3 ] - clipMatrix[ 1 ][ 3 ];
	    top.gPosition           = glm::normalize( top.gPosition );

	    nearPlan.gPosition.x    = clipMatrix[ 3 ][ 0 ] - clipMatrix[ 2 ][ 0 ];
	    nearPlan.gPosition.y    = clipMatrix[ 3 ][ 1 ] - clipMatrix[ 2 ][ 1 ];
	    nearPlan.gPosition.z    = clipMatrix[ 3 ][ 2 ] - clipMatrix[ 2 ][ 2 ];
	    nearPlan.gPosition.w    = clipMatrix[ 3 ][ 3 ] - clipMatrix[ 2 ][ 2 ];
	    nearPlan.gPosition      = glm::normalize( nearPlan.gPosition );

	    farPlane.gPosition.x    = clipMatrix[ 3 ][ 0 ] + clipMatrix[ 2 ][ 0 ];
	    farPlane.gPosition.y    = clipMatrix[ 3 ][ 1 ] + clipMatrix[ 2 ][ 1 ];
	    farPlane.gPosition.z    = clipMatrix[ 3 ][ 2 ] + clipMatrix[ 2 ][ 2 ];
	    farPlane.gPosition.w    = clipMatrix[ 3 ][ 3 ] + clipMatrix[ 2 ][ 3 ];
	    farPlane.gPosition      = glm::normalize( farPlane.gPosition );
    }


    }
