#pragma once
#include "IEntity.h"
#include<map>
#include<forward_list>

using namespace std;

class Map
{
public:
	Map();
	Map(int rows, int cols);
	~Map();
	bool Insert(int x, int y, IEntity *entity);
	forward_list<IEntity*> GetAllEntities();
	void Update();
	void ClearMap();
private:
	int RowCount = 0, ColCount = 0;
	map<int, forward_list<IEntity*>> MapEntities;

};