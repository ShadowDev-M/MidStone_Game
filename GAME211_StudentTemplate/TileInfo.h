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
	struct TileFaces {
		Vec2 PointShared, FaceLength;

		void set(Vec2 PointShared_, Vec2 FaceLength_) {
			PointShared = PointShared_; FaceLength = FaceLength_;
		}
		/// Here's a set of constructors
		inline TileFaces() {
			set(Vec2(), Vec2());
		}

		inline TileFaces(Vec2 PointShared_, Vec2 FaceLength_) {
			set(PointShared_, FaceLength_);
		}

		/// A copy constructor
		inline TileFaces(const TileFaces& newFaces) {
			set(newFaces.PointShared, newFaces.FaceLength);
		}

		inline Vec2 LineY() {
			
			return (Vec2(PointShared.x, PointShared.y + FaceLength.y));
		}

		inline Vec2 LineX() {

			return (Vec2(PointShared.x + FaceLength.x, PointShared.y));
		}

	};
}