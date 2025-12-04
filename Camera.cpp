
#include "Camera.h"
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
namespace VkVoxel {

#define pm( n, tmp )                                                           \
	printf( n ":\n" );                                                          \
	printf( "%.5g %.5g %.5g %.5g\n", tmp[ 0 ][ 0 ], tmp[ 0 ][ 1 ],              \
	        tmp[ 0 ][ 2 ], tmp[ 0 ][ 3 ] );                                     \
	printf( "%.5g %.5g %.5g %.5g\n", tmp[ 1 ][ 0 ], tmp[ 1 ][ 1 ],              \
	        tmp[ 1 ][ 2 ], tmp[ 1 ][ 3 ] );                                     \
	printf( "%.5g %.5g %.5g %.5g\n", tmp[ 2 ][ 0 ], tmp[ 2 ][ 1 ],              \
	        tmp[ 2 ][ 2 ], tmp[ 2 ][ 3 ] );                                     \
	printf( "%.5g %.5g %.5g %.5g\n", tmp[ 3 ][ 0 ], tmp[ 3 ][ 1 ],              \
	        tmp[ 3 ][ 2 ], tmp[ 3 ][ 3 ] );

#define to_radians( degrees ) ( ( degrees ) * M_PI / 180.0f )

void MygluPerspective(
     PMatrix mat, float fovy, float aspect, float zNear, float zFar ) {
#define m ( *mat )
	// #define m l.fProjection
	float sine, cotangent, deltaZ;
	float radians                   = (float)( fovy / 2.0f * M_PI / 180.0f );

	/*m[0][0] = 1.0f;*/ m[ 0 ][ 1 ] = 0.0f;
	m[ 0 ][ 2 ]                     = 0.0f;
	m[ 0 ][ 3 ]                     = 0.0f;
	m[ 1 ][ 0 ]                     = 0.0f; /*m[1][1] = 1.0f;*/
	m[ 1 ][ 2 ]                     = 0.0f;
	m[ 1 ][ 3 ]                     = 0.0f;
	m[ 2 ][ 0 ]                     = 0.0f;
	m[ 2 ][ 1 ]                     = 0.0f; /*m[2][2] = 1.0f; m[2][3] = 0.0f;*/
	m[ 3 ][ 0 ]                     = 0.0f;
	m[ 3 ][ 1 ]                     = 0.0f; /*m[3][2] = 0.0f; m[3][3] = 1.0f;*/

	deltaZ                          = zFar - zNear;
	sine                            = (float)sin( radians );
	if( ( deltaZ == 0.0f ) || ( sine == 0.0f ) || ( aspect == 0.0f ) ) {
		return;
	}
	cotangent   = (float)( cos( radians ) / sine );
	if( aspect < 1 ) {
		m[ 0 ][ 0 ] = cotangent;
		m[ 1 ][ 1 ] = -cotangent * aspect;
	} else {
		m[ 0 ][ 0 ] = cotangent / aspect;
		m[ 1 ][ 1 ] = -cotangent;
	}
	m[ 2 ][ 2 ] = -( zFar + zNear ) / deltaZ;
	m[ 2 ][ 3 ] = -1.0f;
	m[ 3 ][ 2 ] = -1.0f /*2.0f / *Normally 2.0 is here, but vulkan is a smaller space? * / */ 
	            * zNear * zFar / deltaZ;
	m[ 3 ][ 3 ] = 0;
#undef m
}


Camera::Camera( uint32_t resWidth, uint32_t resHeight ) {

	MygluPerspective( &_projection, 45.0f, resWidth / (float)resHeight, 0.1f,
	                  1000.0f );

	// look at works, it doesn't use position+front like other lookat
	// ... but this doesn't matter to start.
	//LookAt( &_view, _position, _front, _Y );

	_yaw   = 0.0f;
	_pitch = 0.0f;

	// Update our camera frustum
	_frustum.fromCamera( &_projection, &_view );
	// _frustum.fromCamera( g_projection, g_view );
}

void Camera::rebuildProjection( uint32_t resWidth, uint32_t resHeight ) {
	MygluPerspective( &_projection, 45.0f,
	                  resWidth / (float)resHeight,
	                  0.1f,
	                  1000.0f );
	//_projection = glm::perspective(glm::radians(45.0f), resWidth /
	//(float)resHeight, 0.1f, 1000.0f);
}

PMatrix Camera::getProjection() { return &_projection; }

PMatrix Camera::getView() { return &_view; }

void Camera::setPosition( PCVECTOR position ) {
	SetPoint( _position, position );

	// updateCamera();
}

PVECTOR Camera::getPosition() { return _position; }

void Camera::move( PCVECTOR direction, float amount ) {
	addscaled( _position, _position, direction, amount );
	//_position = _position + (direction * amount);

	// updateCamera();
}

float Camera::getPitch() { return _pitch; }

float Camera::getYaw() { return _yaw; }

void Camera::setRotation( float pitch, float yaw ) {
	_pitch = pitch;
	_yaw   = yaw;

	// updateCamera();
}

PVECTOR Camera::getFront() { return _front; }

Frustum Camera::getFrustum() { return _frustum; }

void Camera::updateCamera() {
	lq_level_look( orientation, orientation, -_pitch, _yaw, 0.016 );

	// get view matrix, with position translated appropriately
	lq_matrix( &_view, orientation, _position );

	_front[ 0 ] = _view[ 0 ][ 2 ];
	_front[ 1 ] = _view[ 1 ][ 2 ];
	_front[ 2 ] = _view[ 2 ][ 2 ];
	_pitch = 0;
	_yaw   = 0;
	_frustum.fromCamera( &_projection, &_view );
	return;
}
} // namespace VkVoxel
