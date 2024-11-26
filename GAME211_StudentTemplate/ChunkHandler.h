#pragma once

#include <MMath.h>
#include <VMath.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Chunk.h"
#include "Body.h"
#include "ScottyLinkedList.h"
using namespace MATH;

class ChunkHandler {
	const float CHUNKSPACING = 16;
	//std::vector<Chunk> gameMap;
	

	std::vector<Body*> entitiesThatLoadChunks;
	Chunk* currentChunk;
	Chunk* lastChunk;
	ScottLinkedList chunkList;

	//
protected:
	
	Body* newBody;
public:
	std::vector<TileFaces> renderLines;

	void OnCreate();


	void Update();

	void addLoadingEntity(Body* entity);

	Chunk* getChunkPointer(Vec2 pos_);



	void LoadChunk(Vec2 pos_);

	Chunk* getNthNext(int numberOfNexts);

	int searchForChunkPos(Vec2 pos_);

	int getChunkTileID(Vec2 chunkPos_, Vec2 tilePos_);
	/// <summary>
	/// gets the id of the tile corresponding to a set of worldspace coordinates
	/// </summary>
	/// <param name="pos_">worldspace coordinate</param>
	/// <returns>tile id</returns>
	int getTileIDFromCoord(Vec2 pos_);

	/// <summary>
	/// converts worldspace coordinates into chunkspace coordinates
	/// </summary>
	/// <param name="pos_">worldspace coordinate</param>
	/// <returns>position of tile within its own chunk</returns>
	Vec2 worldspaceToChunkCoordinates(Vec2 pos_);

	/// <summary>
	/// gets the chunk index position which a set of coordinates would be located in
	/// </summary>
	/// <param name="pos_">worldspace coordinates</param>
	/// <returns>Region index of the chunk</returns>
	Vec2 getChunkLocation(Vec2 pos_);

	void setTile(std::vector<TileInfo> indexVector_);

	bool isSolid(Vec2 pos_);

	/// <summary>
	/// gets a list of exposed faces that the vector would encounter based on location
	/// </summary>
	/// <param name="entityPos_">position of the entity</param>
	/// <param name="velVector_">the farthest location the entity would move in the current frame</param>
	/// <returns>list of lines for collision</returns>
	TileFaces getFaces(Vec2 entityPos_, Vec2 velVector_);
	
};
