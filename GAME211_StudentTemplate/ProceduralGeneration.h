#ifndef PROCEDURALGENERATION_H
#define PROCEDURALGENERATION_H


#include <MMath.h>
#include <VMath.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "TileInfo.h"
#include <random>

using namespace MATH;

class ProceduralGeneration {
protected:
	int seed;
	int x; 
	int y;
	static const int SEGMENTSIZE = 20;
	static const int CHUNKSIZE = 16;  


	std::vector<TileInfo> tileChanges;
	
	

public:

	ProceduralGeneration() : seed(1000000), x(0), y(0) {}

	~ProceduralGeneration() {}

	ProceduralGeneration(int seed_, Vec2 index_) {
		seed = seed_;
		x = index_.x;
		y = index_.y;
	};

	std::vector<TileInfo> getGenerated() { return tileChanges; };

	void Generate() {


			tileChanges.clear();

			// Create a pseudo-random generator using the seed
			std::mt19937 rng(seed);
			std::uniform_int_distribution<int> distribution(0, 1); // 0 = ground, 1 = wall

			// Define segment boundaries
			bool isSegmentBoundary = (std::abs(x) % SEGMENTSIZE == 0 || std::abs(y) % SEGMENTSIZE == 0);
			
			
			for (int i = 0; i <= 15; i++) {
				for (int j = 0; j <= 15; j++) {
					TileInfo tile;

					// Tile's coordinates in the chunk
					tile.x = i;
					tile.y = j;


					int combined = i * 100 + j;
					switch (combined) {
					case 0: 
					case 15:
					case 1500: 
					case 1515:
						tile.id = 0;



					}

						

					if (i == 0 || i == 15 || j == 0 || j == 15) {
						// If it's on a segment boundary, make a wall
						//tile.id = 1;
					}
					else {
						// Randomly generate ground or wall
						//tile.id = distribution(rng);
					}

					// Add the tile to tileChanges
					if (tile.id == 1) tileChanges.push_back(tile);
				}
			}
			


	}


};

#endif