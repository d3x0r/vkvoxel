#include <vector>
//#include "glm/mat4x4.hpp"
//#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Block.h"
#include "Chunk.h"

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


	Chunk::Chunk(int x, int z) {
        xPos = x;
        zPos = z;
	     //ClearTransformd( _model );

	     ClearTransformf( _model );
		 Translate( _model, (RCOORD)( x * CHUNK_SIZE ), 0.0f,
	                (RCOORD)( z * CHUNK_SIZE ) );
        // Zero out the blocks
        for (int yBlock = 0; yBlock < CHUNK_HEIGHT; yBlock++) {
            for (int xBlock = 0; xBlock < CHUNK_SIZE; xBlock++) {
                for (int zBlock = 0; zBlock < CHUNK_SIZE; zBlock++) {
                    blocks[yBlock][xBlock][zBlock] = 0;
                }
            }
        }
        _lastSize = 0;
    }

    void Chunk::build(const std::vector<BlockType>& blockTypes) {
	    struct VertexPool vertices;

        std::vector<Vertex> g_vertices;
        std::vector<uint32_t> indices;
        vertices.reserve(_lastSize);
        indices.reserve(_lastSize);

        _vertexCount = 0;
        _indexCount = 0;
        for (int yBlock = 0; yBlock < CHUNK_HEIGHT; yBlock++) {
            for (int xBlock = 0; xBlock < CHUNK_SIZE; xBlock++) {
                for (int zBlock = 0; zBlock < CHUNK_SIZE; zBlock++) {
                    uint32_t blockIndex = blocks[yBlock][xBlock][zBlock];
				        if( blockIndex > 0 ) {
					        BlockType blockType     = blockTypes[ blockIndex ];

					        VECTOR blockTranslation = { (RCOORD)xBlock, (RCOORD)yBlock, (RCOORD)zBlock };
					        glm::vec3 g_blockTranslation = { (RCOORD)xBlock, (RCOORD)yBlock, (RCOORD)zBlock };

							Vertex tmp;
                        // Front face neighbor test: if we're at the front or if the block in front of us is air, we add the front vertices
					     if( zBlock == 0 || blocks[ yBlock ][ xBlock ][ zBlock - 1 ] == 0 ) {

                            SetPoint( tmp.color, blockType.frontColor );
						     tmp.texCoord[ 2 ] = blockType.frontTexture;
						     add( tmp.pos, FRONT_FACE[ 0 ], blockTranslation );
						     tmp.texCoord[ 0 ] = 0.0f;
						     tmp.texCoord[ 1 ] = 1.0f;
						     vertices.push_back( &tmp );
						     tmp.texCoord[ 0 ] = 1.0f;
						     tmp.texCoord[ 1 ] = 1.0f;
						     add( tmp.pos, FRONT_FACE[ 1 ], blockTranslation );
						     vertices.push_back( &tmp );
						     tmp.texCoord[ 0 ] = 1.0f;
						     tmp.texCoord[ 1 ] = 0.0f;
						     add( tmp.pos, FRONT_FACE[ 2 ], blockTranslation );
						     vertices.push_back( &tmp );
						     tmp.texCoord[ 0 ] = 0.0f;
						     tmp.texCoord[ 1 ] = 0.0f;
						     add( tmp.pos, FRONT_FACE[ 3 ], blockTranslation );
						     vertices.push_back( &tmp );

						     indices.push_back( _vertexCount );
						     indices.push_back( _vertexCount + 1 );
						     indices.push_back( _vertexCount + 2 );
						     indices.push_back( _vertexCount + 2 );
						     indices.push_back( _vertexCount + 3 );
						     indices.push_back( _vertexCount );

						     _vertexCount += 4;
						     _indexCount += 6;
					     }

                        // Left face neighbor test
                        if (xBlock == 0 || blocks[yBlock][xBlock - 1][zBlock] == 0) {

                            SetPoint( tmp.color, blockType.leftColor );
						     tmp.texCoord[ 2 ] = blockType.leftTexture;

						     add( tmp.pos, LEFT_FACE[ 0 ], blockTranslation );
						     tmp.texCoord[ 0 ] = 0.0f;
						     tmp.texCoord[ 1 ] = 1.0f;
						     vertices.push_back( &tmp );
						     add( tmp.pos, LEFT_FACE[ 1 ], blockTranslation );
						     tmp.texCoord[ 0 ] = 1.0f;
						     tmp.texCoord[ 1 ] = 1.0f;
						     vertices.push_back( &tmp );
						     add( tmp.pos, LEFT_FACE[ 2 ], blockTranslation );
						     tmp.texCoord[ 0 ] = 1.0f;
						     tmp.texCoord[ 1 ] = 0.0f;
						     vertices.push_back( &tmp );
						     add( tmp.pos, LEFT_FACE[ 3 ], blockTranslation );
						     tmp.texCoord[ 0 ] = 0.0f;
						     tmp.texCoord[ 1 ] = 0.0f;
						     vertices.push_back( &tmp );

                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }

                        // Right face neighbor test
                        if (xBlock == (CHUNK_SIZE - 1) || blocks[yBlock][xBlock + 1][zBlock] == 0) {

                            SetPoint( tmp.color, blockType.rightColor );
						         tmp.texCoord[ 2 ] = blockType.rightTexture;

						         add( tmp.pos, RIGHT_FACE[ 0 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 0.0f;
						         tmp.texCoord[ 1 ] = 1.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, RIGHT_FACE[ 1 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 1.0f;
						         tmp.texCoord[ 1 ] = 1.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, RIGHT_FACE[ 2 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 1.0f;
						         tmp.texCoord[ 1 ] = 0.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, RIGHT_FACE[ 3 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 0.0f;
						         tmp.texCoord[ 1 ] = 0.0f;
						         vertices.push_back( &tmp );


                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }

                        // Back face neighbor test
                        if (zBlock == (CHUNK_SIZE - 1) || blocks[yBlock][xBlock][zBlock + 1] == 0) {

                            SetPoint( tmp.color, blockType.backColor );
						         tmp.texCoord[ 2 ] = blockType.backTexture;

						         add( tmp.pos, BACK_FACE[ 0 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 0.0f;
						         tmp.texCoord[ 1 ] = 1.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, BACK_FACE[ 1 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 1.0f;
						         tmp.texCoord[ 1 ] = 1.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, BACK_FACE[ 2 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 1.0f;
						         tmp.texCoord[ 1 ] = 0.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, BACK_FACE[ 3 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 0.0f;
						         tmp.texCoord[ 1 ] = 0.0f;
						         vertices.push_back( &tmp );



                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }

                        // Top face neighbor test
                        if (yBlock == (CHUNK_HEIGHT - 1) || blocks[yBlock + 1][xBlock][zBlock] == 0) {

                            SetPoint( tmp.color, blockType.topColor );
						         tmp.texCoord[ 2 ] = blockType.topTexture;

						         add( tmp.pos, TOP_FACE[ 0 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 0.0f;
						         tmp.texCoord[ 1 ] = 1.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, TOP_FACE[ 1 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 1.0f;
						         tmp.texCoord[ 1 ] = 1.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, TOP_FACE[ 2 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 1.0f;
						         tmp.texCoord[ 1 ] = 0.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, TOP_FACE[ 3 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 0.0f;
						         tmp.texCoord[ 1 ] = 0.0f;
						         vertices.push_back( &tmp );


                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }

                        // Bottom face neighbor test
                        if (yBlock == 0 || blocks[yBlock - 1][xBlock][zBlock] == 0) {


                            SetPoint( tmp.color, blockType.bottomColor );
						         tmp.texCoord[ 2 ] = blockType.bottomTexture;

						         add( tmp.pos, BOTTOM_FACE[ 0 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 0.0f;
						         tmp.texCoord[ 1 ] = 1.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, BOTTOM_FACE[ 1 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 1.0f;
						         tmp.texCoord[ 1 ] = 1.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, BOTTOM_FACE[ 2 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 1.0f;
						         tmp.texCoord[ 1 ] = 0.0f;
						         vertices.push_back( &tmp );
						         add( tmp.pos, BOTTOM_FACE[ 3 ], blockTranslation );
						         tmp.texCoord[ 0 ] = 0.0f;
						         tmp.texCoord[ 1 ] = 0.0f;
						         vertices.push_back( &tmp );


                            indices.push_back(_vertexCount);
                            indices.push_back(_vertexCount + 1);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 2);
                            indices.push_back(_vertexCount + 3);
                            indices.push_back(_vertexCount);

                            _vertexCount += 4;
                            _indexCount += 6;
                        }
                    }
                }
            }
        }

        // We'll cache the size so we know how much memory to reserve for the next build
        _lastSize = vertices.size();

        // Now call the implementation of the build buffers method.
        prepare(vertices, indices);
    }

    PMatrix Chunk::getTransform( PMatrix out,
                                 PMatrix proj,
                                 PMatrix view ) {
	    MATRIX tmp;
	    ApplyM( view, &tmp, (PMatrix)_model );
	   ApplyM( proj, out, (PMatrix)tmp  );
        return out;
    }


    uint32_t Chunk::getVertexCount() {
        return _vertexCount;
    }

    uint32_t Chunk::getIndexCount() {
        return _indexCount;
    }
}
