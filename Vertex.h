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

	#define IntegersPerSet 4096 	
	struct IntSet {
	    struct VertexSet *next, *prior;
	    uint32_t nUsed;
	    uint32_t nBias;
	    uint32_t bUsed[ ( IntegersPerSet + 31 ) / 32 ];
	    uint32_t p[ IntegersPerSet ];
	};

	#define VerticesPerSet 4096
    typedef struct VertexSet {
	    struct VertexSet *next, *prior;
	    uint32_t nUsed;
	    uint32_t nBias;
	    uint32_t bUsed[ ( VerticesPerSet + 31 ) / 32 ];
	    struct Vertex p[ VerticesPerSet ];
			/*
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
			*/
    } VertexSet, *PVertexSet;

	template <typename T>
	struct GenericPool {
		GENERICSET *root = NULL;
		size_t setsz;
		size_t sz;
		size_t count;

		GenericPool( size_t setsize, size_t unitsize, size_t maxcount )
	       : setsz( setsize )
	       , sz( unitsize )
	       , count( maxcount ) {
		}

	    T get() {
		    return (T)GetFromSetEx( &this->root, (int)setsz, (int)sz, (int)count DBG_SRC );
	    }

	    T push_back( T v ) {
			T pv = this->get();
			if( pv ) {
				pv[ 0 ] = v[ 0 ];
				return pv;
			}
			return NULL;
		}

	    // Vertex *push_back( struct Vertex *v ) { return VertexSet::push_back(
	    // &this, v ); }
	    void reserve( size_t n ) {
		    void *p = GetSetMemberEx( &this->root, n, (int)setsz, (int)sz,
		                              (int)count DBG_SRC );
		    DeleteSetMemberEx( this->root, (int)n, (int)sz, (int)count );
	    }

	    size_t size() const {
		    return CountUsedInSetEx( this->root, (int)count );
	    }

	    void storeInto( T data ) const {
		    StoreSetIntoEx( this->root, (void *)data, (int)sz, (int)count );
	    }

	};

    typedef struct IntPool : GenericPool<uint32_t *> {

		IntPool()
	        : GenericPool( sizeof( struct IntSet ),
	                       sizeof( uint32_t ),
	                       IntegersPerSet ) {
		}

		uint32_t push_back( uint32_t v ) {
		   uint32_t* pv = this->get();
		   if( pv ) {
			   pv[ 0 ] = v;
			   return v;
		   }
		   return NULL;
	   }

	} IntPool, *PIntPool;

    typedef struct VertexPool : GenericPool<Vertex *> {

		VertexPool() : GenericPool( sizeof( struct VertexSet ), sizeof( struct Vertex ), VerticesPerSet ) {
		}
	} VertexPool, *PVertexPool;

    }



#endif