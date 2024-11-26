#ifndef CHUNK_H
#define CHUNK_H

#include <MMath.h>
#include <VMath.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "TileInfo.h"

using namespace MATH;


class Chunk {
protected:
    
   


    const static int MAXSIZE = 16;
	int tileSet[MAXSIZE][MAXSIZE] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

public:

	Chunk();

    ~Chunk();

	Chunk(Vec2 pos_);
	//constructor for chunk, parametres are a vector for saved tiles and its index, assume both vectors share an index for each information



    /// <returns>id of specific index</returns>
    int getTile(int x, int y) { return tileSet[x][y]; }
    
    /// <summary>
    /// Overwrites a tile in the tileSet with a new ID.
    /// </summary>
    /// <param name="indexVector_"> The list for each tile's index to be changed</param>
    /// <param name="savedIDVector_">The list for each tile's id to be changed</param>
    void setTile(TileInfo tileInfo_);

    void printChunk() {
       
        for (int j = 0; j < MAXSIZE; j++) {
            std::cout << std::endl;

            for (int i = 0; i < MAXSIZE; i++) {
                std::cout << tileSet[j][i] << " ";
            }

        }
        std::cout << std::endl;
        std::cout << std::endl;


        }
    };
#endif