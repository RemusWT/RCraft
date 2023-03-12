#include "chunk_manager.h"


void Chunk::add_block(Block &block) {
    Blocks.push_back(block);
}

void ChunkManager::load_chunk(Chunk &chunk) {
    loaded_chunks.push_back(chunk);
}
