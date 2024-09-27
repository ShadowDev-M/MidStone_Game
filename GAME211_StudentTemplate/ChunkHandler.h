#pragma once

#include <MMath.h>
#include <VMath.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Chunk.h"

using namespace MATH;

class ChunkHandler {
	const float CHUNKSPACING = 16;
	Chunk Region[10][10];

	//
protected:


public:
	int getTileIDFromCoord(Vec2 pos_) {

<<<<<<< Updated upstream
		Vec2 chunkPos = getChunkLocation(pos_);
		
		Vec2 chunkTilePos = worldspaceToChunkCoordinates(pos_);
		
		
		
		return Region[int(chunkPos.x)][int(chunkPos.y)].getTile(int(chunkTilePos.x), int(chunkTilePos.y));
		//chunkIndexX represents the corner (0,0), relative to the chunk
		//chunkIndexX is then multiplied by 16 to be equivalent to the translation from 0,0 world space to the corner of the chunk
		//the translation is then subtracted from the target position 
	}
=======
	/// <summary>
	/// gets the id of the tile corresponding to a set of worldspace coordinates
	/// </summary>
	/// <param name="pos_">worldspace coordinate</param>
	/// <returns>tile id</returns> 
	int getTileIDFromCoord(Vec2 pos_); //render with this
>>>>>>> Stashed changes

	Vec2 worldspaceToChunkCoordinates(Vec2 pos_) {
		Vec2 chunkPos = getChunkLocation(pos_);

		int chunkIndexX = int(chunkPos.x);
		int chunkIndexY = int(chunkPos.y);

		return (Vec2(float(int((pos_.x) - (int(chunkPos.x) * CHUNKSPACING))), float(int((pos_.y) / (int(chunkPos.y) * CHUNKSPACING)))));

	}

	Vec2 getChunkLocation(Vec2 pos_) {
		int chunkIndexX = int(pos_.x / CHUNKSPACING);
		int chunkIndexY = int(pos_.y / CHUNKSPACING);
		
		return Vec2(float(chunkIndexX), float(chunkIndexY));
	}
};
