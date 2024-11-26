
#pragma once

#include "Vector.h"

namespace  MATH {

	struct TileInfo {

		int x, y, id;

		void set(int x_, int y_, int id_) {
			x = x_; y = y_; id = id_;
		}
		/// Here's a set of constructors
		inline TileInfo() {
			set(0, 0, 0);
		}

		inline TileInfo(int x, int y, int id) {
			set(x, y, id);
		}

		/// A copy constructor
		inline TileInfo(const TileInfo& tile) {
			set(tile.x, tile.y, tile.id);
		}


	};
	/// <summary>
	/// Struct for storing the info of a tile's faces facing a player's direction vector, both are connected to PointShared
	/// </summary>
	/// 
	
	enum ObjectTag
	{
		none = 0,
		wall = 1,
		enemy = 2,
		loot = 3
	};
	
	struct TileFaces {
		Vec2 PointOne, PointTwo;
		ObjectTag objectTag;


		void set(Vec2 PointOne_, Vec2 PointTwo_, ObjectTag _collisionType) {
			PointOne = PointOne_; PointTwo = PointTwo_; objectTag = _collisionType;
		}
		/// Here's a set of constructors
		inline TileFaces() {
			set(Vec2(), Vec2(),none);
		}

		inline TileFaces(Vec2 PointOne_, Vec2 PointTwo_, ObjectTag _collisionType) {
			set(PointOne_, PointTwo_,_collisionType);
		}

		/// A copy constructor
		inline TileFaces(const TileFaces& newFaces) {
			set(newFaces.PointOne, newFaces.PointTwo,newFaces.objectTag);
		}


	}; 
	

}

	