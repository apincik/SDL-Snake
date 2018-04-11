#include "Map.h"

Map::~Map()
{
	for (int i = 0; i < RowCount; i++) {

		for (int j = 0; j < ColCount; j++) {

			int pos = i * ColCount + j;
			for (auto &item : MapEntities[pos]) {
				delete item;
			}
		}
	}

	ClearMap();
}

void Map::ClearMap()
{
	MapEntities.clear();
}

/*
* Update map - mainly entities positions, @TODO game update logic
*/
void Map::Update()
{
	//all entities list
	forward_list<IEntity*> entities = GetAllEntities();

	//refresh map variable
	ClearMap();

	//reinsert entites by their position
	for (auto it = entities.begin(); it != entities.end(); it++) {

		SDL_Point currentPosition = (*it)->GetPosition();
		Insert(
			currentPosition.x / Map::ColCount,
			currentPosition.y / Map::RowCount,
			(*it)
			//(*(IEntity*)(&it))
		);
	}

}

Map::Map()
{

}

Map::Map(int rCount, int cCount)
{
	RowCount = rCount;
	ColCount = cCount;

	for (int i = 0; i < RowCount; i++) {

		for (int j = 0; j < ColCount; j++) {

			int pos = i * ColCount+ j;
			forward_list<IEntity*> *list = new forward_list<IEntity*>;
			MapEntities.insert(pair<int, forward_list<IEntity*>>(pos, *list));
		}
	}
}

forward_list<IEntity*> Map::GetAllEntities()
{
	forward_list<IEntity*> entities;

	for (int i = 0; i < RowCount; i++) {

		for (int j = 0; j < ColCount; j++) {

			int pos = i * ColCount + j;
			for (auto &item : MapEntities[pos]) {
				entities.push_front(item);
			}
		}
	}

	return entities;
}

bool Map::Insert(int x, int y, IEntity *entity)
{
	if (x > ColCount || y > RowCount) {
		return false;
	}

	MapEntities[x * ColCount + y].push_front(entity);

	return true;
}
