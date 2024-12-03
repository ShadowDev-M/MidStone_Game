#include <vector>
#include "Chunk.h"
#include "stdio.h"
#include "ProceduralGeneration.h"


namespace  MATH {


	//Named after scott
	struct ScottLinkedNode {
	protected: 
	
	public:
		Vec2 position;
		
		Chunk chunk;

		ScottLinkedNode* next;
		
		ScottLinkedNode* previous;

		ScottLinkedNode(Vec2 position_) : position(position_), next(nullptr), previous(nullptr) {}
		
		int getTilePosNodeInternal(Vec2 pos_) { return chunk.getTile((int)pos_.x, (int)pos_.y); }

		void setTilePosNodeInternal(TileInfo tile_) { 

			chunk.setTile(tile_); 			
			//printf("(Ping) %d) ", getTilePosNodeInternal(Vec2(tile_.x, tile_.y)));

		}

		
	};


	class ScottLinkedList {
	protected:

		ScottLinkedNode* first;
		ScottLinkedNode* last;
		int listSize;

	public:
		static const int MAXSIZE = 50;

		ScottLinkedList() : first(nullptr), last(nullptr), listSize(0) {}

		Chunk* getFirst() {
			return &first->chunk;
		}

		void add(Vec2 position) {
			if (!search(position, listSize)) {

				//	remove(position);

				if (first == nullptr) {
					first = new ScottLinkedNode(position);
					generateNode(first);
					last = first;
				}
				else {
					first->previous= new ScottLinkedNode(position);
					generateNode(first->previous);

					first->previous->next = first;
					first = first->previous;
				}
				//printf("Created: %d", newNode);
				listSize += 1;
				std::cout << listSize << std::endl;
				print();

			}else {
				

				ScottLinkedNode tempNode = *getNodePointer(position);
				remove(position);

				

				if (first == nullptr) {
					first = new ScottLinkedNode(tempNode);
					generateNode(first);

					last = first;
				}
				else {
					first->previous = new ScottLinkedNode(tempNode);
					generateNode(first->previous);

					first->previous->next = first;
					first = first->previous;
				}
				listSize += 1;

				print();

			}
			
		}

		int getChunkTileIDInternal(Vec2 chunkPos_, Vec2 tilePos_) {
			
			//return getChunkPointer(chunkPos_).(tilePos_.x, tilePos_.y);
		
			ScottLinkedNode* tempNode = first;

			for (int i = 0; i < listSize; i++) {
				if (tempNode == nullptr) break;
				if (tempNode->position.x == chunkPos_.x && tempNode->position.y == chunkPos_.y)
					
					return tempNode->getTilePosNodeInternal(tilePos_);

				tempNode = tempNode->next; // Move to the next node
			}
			return NULL;
		}

		void setChunkTileIDInternal(Vec2 chunkPos_, TileInfo tileInfo_) {

			//return getChunkPointer(chunkPos_).(tilePos_.x, tilePos_.y);
			if (!search(chunkPos_, listSize)) {
				add(chunkPos_);
			}

			ScottLinkedNode* tempNode = first;
			printf("internally running setChunk -> ");
			for (int i = 0; i < listSize; i++) {
				if (tempNode == nullptr) break;

				
				if (tempNode->position.x == chunkPos_.x && tempNode->position.y == chunkPos_.y) {

					printf("found chunk in queue -> ");

					tempNode->setTilePosNodeInternal(tileInfo_);
				}
		

				tempNode = tempNode->next;
				// Move to the next node
			}
		}

		int size() { return listSize; }

		bool search(Vec2 position_, int length_) {
			ScottLinkedNode* tempNode = first;

			for (int i = 0; i < length_; i++) {
				if (tempNode == nullptr) break;

				if (tempNode->position.x == position_.x && tempNode->position.y == position_.y)
					return true;

				tempNode = tempNode->next; // Move to the next node
			}
			return false;
		}

		Chunk* getChunkPointer(Vec2 position_) {
			ScottLinkedNode* tempNode = first;

			for (int i = 0; i < listSize; i++) {
				if (tempNode == nullptr) break;

				if (tempNode->position.x == position_.x && tempNode->position.y == position_.y)
					return &tempNode->chunk;

				tempNode = tempNode->next; // Move to the next node
			}
			return nullptr;
		}
		
		ScottLinkedNode* getNodePointer(Vec2 position_) {
			ScottLinkedNode* tempNode = first;

			for (int i = 0; i < listSize; i++) {
				if (tempNode == nullptr) break;

				if (tempNode->position.x == position_.x && tempNode->position.y == position_.y)
					return tempNode;

				tempNode = tempNode->next; // Move to the next node
			}
			return nullptr;
		}

		

		void remove(Vec2 position_) {
			ScottLinkedNode* tempNode = first;

			for (int i = 0; i < listSize; i++) {
				if (tempNode == nullptr) break;

				if (tempNode->position.x == position_.x && tempNode->position.y == position_.y) {
					if (tempNode == first) {
						if (listSize == 1) {
							// Only one element in the list
							first = last = nullptr;
						}
						else {
							first = tempNode->next;
							first->previous = nullptr;
						}
					}
					else if (tempNode == last) {
						last = tempNode->previous;
						last->next = nullptr;
					}
					else {
						tempNode->previous->next = tempNode->next;
						tempNode->next->previous = tempNode->previous;
					}

					delete tempNode;
					tempNode = nullptr; // Avoid dangling pointer
					listSize -= 1;
					break; // Exit after deleting the node
				}

				tempNode = tempNode->next;
			}
		}

		void print() {
			ScottLinkedNode* tempNode = first;
			Vec2 tempPos;
			for (int i = 0; i < listSize; i++) {
				if (tempNode == nullptr) break;
				tempPos = tempNode->position;
				printf("(%d, %d) ", (int)tempPos.x, (int)tempPos.y);
				tempNode = tempNode->next;

			}
			printf("list end");
			std::cout<<std::endl;

		}

		void generateNode(ScottLinkedNode* node) {
			ProceduralGeneration NodeGeneration = ProceduralGeneration(1021430, node->position);
			NodeGeneration.Generate();

			std::vector<TileInfo> tilesProcedural = NodeGeneration.getGenerated();
			
			for (TileInfo tile : tilesProcedural) {
				//printf("(%d, %d) ", tile.x, tile.y);
				node->setTilePosNodeInternal(tile);
			}

		}
	};
}

