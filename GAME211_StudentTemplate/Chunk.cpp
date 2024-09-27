#include "Chunk.h"

Chunk::Chunk()
{
}

Chunk::Chunk(std::vector<TileInfo> indexVector_)
{
    setTile(indexVector_);
}



Chunk::~Chunk() {
}

void Chunk::setTile(std::vector<TileInfo> indexVector_)
{

    
    for (int i = 0; i < indexVector_.size(); i++) {
            
            if(indexVector_[i].x >= 0 && indexVector_[i].y >= 0 && indexVector_[i].x < MAXSIZE && indexVector_[i].y < MAXSIZE) {
                //in chunk bounds
              
                //set the id to location
                tileSet[(int)indexVector_[i].x][(int)indexVector_[i].y] = indexVector_[i].id;
            

            }
            else {
                //out of chunk bounds
                std::cout << "Chunk function setTile Error: argument out of bounds (range 0 .. " << MAXSIZE-1 << ") of chunk size (" << indexVector_[i].x << ", " << indexVector_[i].y << ") in Chunk " << this << std::endl;
            }        
    }
}
