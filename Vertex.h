#ifndef __VERTEX_H_
#define __VERTEX_H_

#include <array>
#define NEED_VECTLIB_ALIASES
#include "sack_ucb_filelib.h"
#undef _5
#undef _15
#include "glm/vec2.hpp"
#include <array>
#include "glm/vec3.hpp"
#include "VkUtil.h"


namespace VkVoxel {
    struct Vertex {
    public:
	    union {
		    struct {
			    VECTOR pos;
			    VECTOR color;
			    VECTOR texCoord;
		    };
	    };

        static VkVertexInputBindingDescription getBindingDescription();
        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
	     void set( PCVECTOR p, PCVECTOR c, PCVECTOR t ) {
		     SetPoint( pos, p );
		     SetPoint( color, c );
		     SetPoint( texCoord, t );
	     }
	     Vertex() {
		     SetPoint( pos, _0 );
		     SetPoint( color, _0 );
		     SetPoint( texCoord, _0 );
	     }
	     Vertex( PCVECTOR p, PCVECTOR c, PCVECTOR t ) {
		     SetPoint( pos, p );
		     SetPoint( color, c );
		     SetPoint( texCoord, t );
		 }
    };

	#define VerticesPerSet 4096
    typedef struct VertexSet {
	    struct VertexSet *next, *prior;
	    uint32_t nUsed;
	    uint32_t nBias;
	    uint32_t bUsed[ ( VerticesPerSet + 31 ) / 32 ];
	    struct Vertex p[ VerticesPerSet ];

	    static Vertex *get(struct VertexSet **pset) {
		    return (Vertex *)GetFromSeta(
		         (GENERICSET **)( pset ), sizeof( struct VertexSet ),
		         sizeof( struct Vertex ), VerticesPerSet );
	    }
	    Vertex *Get( struct VertexSet **set ) { return VertexSet::get( set ); }

	    static Vertex *push_back( struct VertexSet **set, struct Vertex *v ) {
		    struct Vertex *pv = VertexSet::get( set );
			if ( pv ) {
					pv[ 0 ]      = v[0];
					return pv;
				}
			return NULL;
		}
	    //Vertex *push_back( struct Vertex *v ) { return VertexSet::push_back( &this, v ); }
	   void Reserve( uint32_t n ) {
	   }
    } VertexSet, *PVertexSet;

    typedef struct VertexPool {
	    struct VertexSet *root = NULL;

	    Vertex *get( ) {
		    return (Vertex *)GetFromSetEx(
		         (GENERICSET **)( &this->root ), sizeof( struct VertexSet ),
		         sizeof( struct Vertex ), VerticesPerSet DBG_SRC );
	    }

	    Vertex *push_back( struct Vertex *v ) {
		    struct Vertex *pv = this->get();
		    if( pv ) {
			    pv[ 0 ] = v[ 0 ];
			    return pv;
		    }
		    return NULL;
	    }
	    // Vertex *push_back( struct Vertex *v ) { return VertexSet::push_back(
	    // &this, v ); }
	    void reserve( size_t n ) { 
			void *p = GetSetMemberEx( (GENERICSET **)( &this->root ), n, sizeof( struct VertexSet ), sizeof( struct Vertex ),
		                    VerticesPerSet DBG_SRC );
		    DeleteSetMemberEx( (GENERICSET*)this->root, n, sizeof( struct Vertex ),
		                       VerticesPerSet );
		}

		size_t size() const {
		   return CountUsedInSetEx( (GENERICSET *)this->root, VerticesPerSet );
	   }
	   
	   void storeInto( void *data ) const {
		   StoreSetIntoEx( (GENERICSET *)this->root, data, sizeof( Vertex ), VerticesPerSet );
	   }
	} VertexPool, *PVertexPool;

    }



#endif