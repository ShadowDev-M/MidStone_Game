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

void ChunkHandler::setTile(std::vector<TileInfo> indexVector_) {
    Vec2 chunkLoc;
    for (int i = 0; i < indexVector_.size(); i++)
    {
        chunkLoc = getChunkLocation(Vec2((float)indexVector_[i].x, (float)indexVector_[i].y));
        Region[(int)chunkLoc.x][(int)chunkLoc.y].setTile(indexVector_[i]);

    }

}

bool ChunkHandler::isSolid(Vec2 pos_) {
    if (getTileIDFromCoord(pos_) == 1) {
        return true;
    }
    return false;
}

TileFaces ChunkHandler::getFaces(Vec2 entityPos_, Vec2 velVector_) {
	
    // adding the velocity to the position to find the end point of the line
	Vec2 endPos_ = Vec2(entityPos_.x + velVector_.x, entityPos_.y + velVector_.y);


    //std::vector<Vec2> tiles;

    // distance vector for the line
    Vec2 d = Vec2(endPos_.x - entityPos_.x, endPos_.y - entityPos_.y);
 

    // simplified cardinal direction
    int dirX = (d.x > 0) ? 1 : -1;
    int dirY = (d.y > 0) ? 1 : -1;
   // std::cout << dirX << std::endl;
    
   

    // values to represent a scale for how fast the line reaches the next grid line in each axis
    Vec2 tDelta;

    // represents the distance of the starting position the next grid line
    Vec2 tMax;

    // calculate 
    if (d.x != 0) {
        tDelta.x = fabs(1.0f / d.x);
    }
    else {
        tDelta.x = std::numeric_limits<float>::max(); // I dont like dividing by 0
    }

    if (d.y != 0) { 
        tDelta.y = fabs(1.0f / d.y); 
    }
    else {
        tDelta.y = std::numeric_limits<float>::max();
    }



    // Starting tile
    int tileX = (int)floor(entityPos_.x);
    int tileY = (int)floor(entityPos_.y);

    // tiles.emplace_back(tileX, tileY); // Start tile

    // distance to the next tile scaled (multiplied) by how fast the line travels in that axis (tDelta)
    // Setting different values depending on direction
    tMax.x = (dirX > 0) ? 
        /*east->*/((tileX + 1) - entityPos_.x) * tDelta.x /*west->*/ : (entityPos_.x - tileX) * tDelta.x;
    
    tMax.y = (dirY > 0) ? 
        /*north->*/((tileY + 1) - entityPos_.y) * tDelta.y : /*south->*/(entityPos_.y - tileY) * tDelta.y;
    std::cout << "(next tile pos) " << tileX + 1 << " - (position of entity) " << entityPos_.x << " = (distance to next tile)\n";
    std::cout << " distance * (fast the line travels in that axis) " << tDelta.x << "\n\n";
    
    // (adjacentTilePos.axis - entityPos.axis) = (nextTileDistance) :::::: (nextTileDistance) * (lineScaling.axis) = tMax.axis

    // will loop until the tile is the end point's tile
    while ((int)floor(endPos_.x) != tileX || (int)floor(endPos_.y) != tileY) {
        
        //check which tMax axis is closer to the next wall on its axis
        if (tMax.x < tMax.y) {
            std::cout << "tMax.x is closer to its line than tMax.y: move tMax.x down the line and then check again" << "\n";


            std::cout << "(tMax.x) ";
            //tMax.x is closer to the next wall: new tile position
            tileX += dirX;

            // Adding tDelta moves tMax further down the line
            tMax.x += tDelta.x;


            std::cout << tMax.x << " += (tDelta.x)" << tDelta.x << "\n";

            if (isSolid(Vec2((float)tileX, (float)tileY))) {
                std::cout << tileX << ", " << tileY << " is solid!\n";
                return TileFaces(Vec2(tileX + fabs(dirX - 1.0) / 2.0, tileY), Vec2(tileX + fabs(dirX - 1.0) / 2.0, tileY + 1));

            }
        }
        else {

            //tMax.y is closer to the next wall therefore it collides with the tile above it
            tileY += dirY;

            // increase tMax.y by the amount it would have needed to reach the tile
            tMax.y += tDelta.y;
            
            if (isSolid(Vec2((float)tileX, (float)tileY))) {
                std::cout << tileX << ", " << tileY << " is solid!\n";
                return (TileFaces(Vec2(tileX, tileY + fabs(dirY - 1.0) / 2.0), Vec2(tileX+1, tileY + fabs(dirY - 1.0) / 2.0)));
            }
        }
        
        
        // Add the tile to the list
        //tiles.emplace_back(tileX, tileY);
    }

    return (TileFaces(Vec2(), Vec2()));
}