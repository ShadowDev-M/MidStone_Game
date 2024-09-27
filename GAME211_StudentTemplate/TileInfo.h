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

}