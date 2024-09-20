#include "ChunkHandler.h"

int ChunkHandler::getTileIDFromCoord(Vec2 pos_) {

	Vec2 chunkPos = getChunkLocation(pos_);

	Vec2 chunkTilePos = worldspaceToChunkCoordinates(pos_);



	return Region[int(chunkPos.x)][int(chunkPos.y)].getTile(int(chunkTilePos.x), int(chunkTilePos.y));
	//chunkIndexX represents the corner (0,0), relative to the chunk
	//chunkIndexX is then multiplied by 16 to be equivalent to the translation from 0,0 world space to the corner of the chunk
	//the translation is then subtracted from the target position 
}

Vec2 ChunkHandler::worldspaceToChunkCoordinates(Vec2 pos_) {
	Vec2 chunkPos = getChunkLocation(pos_);

	int chunkIndexX = int(chunkPos.x);
	int chunkIndexY = int(chunkPos.y);

	return (Vec2(float(int((pos_.x) - (int(chunkPos.x) * CHUNKSPACING))), float(int((pos_.y) / (int(chunkPos.y) * CHUNKSPACING)))));

}


Vec2 ChunkHandler::getChunkLocation(Vec2 pos_) {
	int chunkIndexX = int(pos_.x / CHUNKSPACING);
	int chunkIndexY = int(pos_.y / CHUNKSPACING);

	return Vec2(float(chunkIndexX), float(chunkIndexY));
}

std::vector<Vec2> ChunkHandler::getFaces(Vec2 entityPos_, Vec2 velVector_) {
	Vec2 entityChunk = getChunkLocation(entityPos_);
	Vec2 maxEndpointChunk = getChunkLocation(velVector_);


	//direction vector of the entity
	Vec2 direction = Vec2(velVector_.x - entityPos_.x, velVector_.y - entityPos_.y);


	float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

	//normalized direction
	Vec2 normalizedDir = Vec2(direction.x / magnitude, direction.y / magnitude);

	// the direction of the faces for the vector
	Vec2 cardinalDirection = Vec2(ceil(normalizedDir.x), ceil(normalizedDir.y));

	
	
}