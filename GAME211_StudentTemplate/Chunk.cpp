#include "Chunk.h"

Chunk::Chunk()
{
}

Chunk::Chunk(std::vector<TileInfo> indexVector_)
{
    for (int i = 0; i <= indexVector_.size(); i++)
    {
        setTile(indexVector_[i]);
    }
}



Chunk::~Chunk() {
}

void Chunk::setTile(TileInfo tileInfo_)
{

    
    if (tileInfo_.x >= 0 && tileInfo_.y >= 0 && tileInfo_.x < MAXSIZE && tileInfo_.y < MAXSIZE) {
        //in chunk bounds

        //set the id to location
        tileSet[(int)tileInfo_.x][(int)tileInfo_.y] = tileInfo_.id;


    }
    else {
        //out of chunk bounds
        std::cout << "Chunk function setTile Error: argument out of bounds (range 0 .. " << MAXSIZE - 1 << ") of chunk size (" << tileInfo_.x << ", " << tileInfo_.y << ") in Chunk " << this << std::endl;
    }
}
