#ifndef SERVER_MODEL_ENTITY_GAME
#define SERVER_MODEL_ENTITY_GAME

enum class ResourceType { Wood, Stone, Iron, Gold };

struct GameTeamEntity
{
	vector<int> Members;
	pair<int, int> WoodSlot = { -1, -1 };
	pair<int, int> RockSlot = { -1, -1 };
	pair<int, int> IronSlot = { -1, -1 };
};

struct SpotEntity
{
	int WoodSlot = -1;
	int RockSlot = -1;
	int IronSlot = -1;
};

struct MapEntity
{
	array<SpotEntity, 6> Spots;
};


#endif