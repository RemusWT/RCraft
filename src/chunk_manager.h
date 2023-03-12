#ifndef chunk_manager_h

#define chunk_manager_h
#include "utils/basic_types.h"
#include "render/opengl_basic_wrapper.h"


// Pointer to custome information about the block. For an example the metadata for a chest will point to struct
// for the chest inventory. Functions for metadata corespond to the block type.
typedef void* BlockMetadata;

typedef struct Block {
    int type;
    glm::vec3 position; // Relative to chunk
    BlockMetadata meta;
} Block;

typedef struct Chunk {
    glm::vec2 position; // all chunks have the same y coordinate
    std::vector<Block> Blocks;

    Block* get_block_by_position();
} Chunk;


typedef struct ChunkManager {
    std::vector<Chunk> loaded_chunks;
    void load_chunk(Chunk &chunk);
    void unload_chunk(int chunk_index);
} ChunkManager;


#endif
