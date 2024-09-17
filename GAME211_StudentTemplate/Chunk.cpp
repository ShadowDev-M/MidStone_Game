#include "Chunk.h"

Chunk::Chunk()
{
}

Chunk::Chunk(std::vector<Vec2> indexVector_, std::vector<int> savedIDVector_)
{
    setTile(indexVector_, savedIDVector_);
}



Chunk::~Chunk() {
}

void Chunk::setTile(std::vector<Vec2> indexVector_, std::vector<int> savedIDVector_)
{

    if (savedIDVector_.size() > indexVector_.size()) {
        //extra id arguments with no location
        std::cout << "Chunk function setTile Error: " << savedIDVector_.size() - indexVector_.size() << " ID change arguments found with no location saved in indexVector in Chunk " << this << std::endl;
    }
    
    for (int i = 0; i < indexVector_.size(); i++) {

        if (i < savedIDVector_.size()) {
            //found a corresponding id for location
            
            if(indexVector_[i].x >= 0 && indexVector_[i].y >= 0 && indexVector_[i].x < MAXSIZE && indexVector_[i].y < MAXSIZE) {
                //in chunk bounds
              
                //set the id to location
                tileSet[(int)indexVector_[i].x][(int)indexVector_[i].y] = savedIDVector_[i];
            

            }
            else {
                //out of chunk bounds
                std::cout << "Chunk function setTile Error: argument out of bounds (range 0 .. " << MAXSIZE-1 << ") of chunk size (" << indexVector_[i].x << ", " << indexVector_[i].y << ") in Chunk " << this << std::endl;
            }
        }
        else {
            //no id change info - extra ids
            std::cout << "Chunk function setTile Error: No ID argument found for (" << indexVector_[i].x << ", " << indexVector_[i].y << ") in Chunk " << this << std::endl;
        }
        
    }
}
