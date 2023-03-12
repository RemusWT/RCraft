#include "chunk_manager.h"


Chunk::add_block(Block &block) {
    Blocks.push_back(block);
}

ChunkManager::load_chunk(Chunk &chunk) {
    loaded_chunk.push_back(chunk);
}
