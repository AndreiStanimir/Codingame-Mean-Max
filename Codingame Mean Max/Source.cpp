#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#define NUMBER_CARS 1
#define INFINITY 1<<20
#define NULL_ENTITIY Entity(-1, 0, 0, 0, 0, 0, 0, 0, 0, 0)
using namespace std;

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/
string outputHarvester = "";
string outputDestroyer = "";
class Point
{
public:
	int x, y;

	Point(int x, int y);
	Point();
private:
};
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}
Point::Point()
{
	this->x = 0;
	this->y = 0;
}
class Entity
{
public:
	int unitId;
	int player;
	float mass;
	int radius;
	Point position;
	Point vector;
	int extra; // The quantity of water for Tankers and Wrecks, -1 otherwise
	int extra2; // the water capacity for a Tanker, -1 otherwise
	Entity(int unitId, int player, float mass, int radius, int x, int y, int vx, int vy, int extra, int extra2);
private:

};

Entity::Entity(int unitId, int player, float mass, int radius, int x, int y, int vx, int vy, int extra, int extra2)
{
	this->unitId = unitId;
	this->player = player;
	this->mass = mass;
	this->radius = radius;
	this->position = *new Point(x, y);
	this->vector = *new Point(vx, vy);
	this->extra = extra;
	this->extra2; //
}

inline double distance(Point a, Point b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}
inline double distance(Entity* a, Entity* b)
{
	return sqrt(pow((a->position.x - b->position.x), 2) + pow((a->position.y - b->position.y), 2));
}
inline double distance(Entity* a, Point b)
{
	return sqrt(pow((a->position.x - b.x), 2) + pow((a->position.y - b.y), 2));
}

void ThinkNextMove();
Entity* SearchClosestWaterTank(Entity*);
bool isNullEntity(Entity*);
string GiveCommand(Point, int);

vector<Entity*> myCars;
vector<Entity*> enemyCars;
vector<Entity*> waterSources;
vector<Entity*> tanks;
Entity harvester(NULL_ENTITIY);
Entity destroyer(NULL_ENTITIY);
Entity* ClosestEnitity(Point car, vector<Entity*> entities)
{
	Entity* e = entities[0];
	//if (entities.size() == 0)
	//	return Point(-9999, -9999);
	for (int i = 1; i < entities.size(); i++)
	{
		e = entities[0];
	}
	return e;
}
Point ClosestWell(Entity* car)
{
	Point p;
	double minD = INFINITY;
	if (waterSources.size() == 0)
		return Point(-9999, -9999);
	for (int i = 0; i < waterSources.size(); i++)
	{
		Entity* w = waterSources[i];
		if (minD > distance(w->position, car->position))
			minD = distance(w->position, car->position),
			p = w->position;
	}
	return p;
}

string GoToMiddle(Entity* e)
{
	string output = "";
	if (distance(e->position, Point(0, 0)) < 5000)
		output = "WAIT";
	else
		output = "0 0 300";
	return output;
}

void ReadInput(Entity &harvester, Entity &destroyer);

int main()
{

	// game loop

	cerr << 1;
	const Entity tempE(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);


	while (1) {
		ReadInput(harvester, destroyer);
		ThinkNextMove();

		cout << outputHarvester << endl;
		cout << outputDestroyer << endl;
		cout << "WAIT" << endl;

		enemyCars.clear();
		waterSources.clear();
		tanks.clear();
	}
}

void SendHarvesterToWaterSource(Point &closestWell);

void ThinkNextMove()
{
	Point closestWell = ClosestWell(&harvester);
	if (closestWell.x == -9999)
		outputHarvester = GoToMiddle(&harvester);
	else
		SendHarvesterToWaterSource(closestWell);

	//Destroyer
	Entity* closestWaterTank = SearchClosestWaterTank(&destroyer);
	if (isNullEntity(closestWaterTank))
		outputDestroyer = GoToMiddle(&destroyer);
	else
	{
		outputDestroyer = GiveCommand(closestWaterTank->position, 300);
		if (distance(&harvester, closestWell) > distance(closestWaterTank, &harvester))
			outputHarvester = GiveCommand(closestWaterTank->position, 300);
	}
}

void SendHarvesterToWaterSource(Point &closestWell)
{
	if (distance(&harvester,closestWell) < 200)
		outputHarvester = "WAIT";
	else
	{
		outputHarvester = GiveCommand(closestWell, 300);
			//outputHarvester = to_string(closestWell.x) + " " + to_string(closestWell.y);
			//outputHarvester += " 150";
	}
}

Entity* SearchClosestWaterTank(Entity* car)
{
	Entity* e = new NULL_ENTITIY;
	int minD = INFINITY;
	for (int i = 0; i < tanks.size(); i++)
	{
		Entity *t = tanks[i];
		if (t->extra > 2)
			if (minD > distance(t->position, car->position))
				minD = distance(t->position, car->position),
				e = t;
	}
	if (minD == INFINITY)
		e = new NULL_ENTITIY;
	return e;
}

void RamDestroyer(Point p)
{
	outputDestroyer = GiveCommand(p, 300);
}

inline string GiveCommand(Point p, int thrust)
{
	return to_string(p.x) + " " + to_string(p.y) + " " + to_string(thrust);
}
inline string GiveCommand(Entity* p, int thrust)
{
	return to_string(p->position.x) + " " + to_string(p->position.y) + " " + to_string(thrust);
}

void ReadInput(Entity &harvester, Entity &destroyer)
{
	int myScore;
	cin >> myScore; cin.ignore();
	int enemyScore1;
	cin >> enemyScore1; cin.ignore();
	int enemyScore2;
	cin >> enemyScore2; cin.ignore();
	int myRage;
	cin >> myRage; cin.ignore();
	int enemyRage1;
	cin >> enemyRage1; cin.ignore();
	int enemyRage2;
	cin >> enemyRage2; cin.ignore();
	int unitCount;
	cin >> unitCount; cin.ignore();
	for (int i = 0; i < unitCount; i++) {
		int unitId;
		int unitType;
		int player;
		float mass;
		int radius;
		int x;
		int y;
		int vx;
		int vy;
		int extra;
		int extra2;
		cin >> unitId >> unitType >> player >> mass >> radius >> x >> y >> vx >> vy >> extra >> extra2; cin.ignore();


		Entity* e = new Entity(unitId, player, mass, radius, x, y, vx, vy, extra, extra2);
		//cerr << e->mass << ":" << e->radius << "z  " << " " << e->position.x;
		if (player == 0) {
			if (unitType == 0)
				harvester = *e;
			else if (unitType == 1)
				destroyer = *e;
		}
		else if (unitType == 0)
			enemyCars.push_back(e);
		else if (unitType == 1)
			enemyCars.push_back(e);
		else if (unitType == 3)
			tanks.push_back(e);
		else if (unitType == 4)
			waterSources.push_back(e);
	}
}

inline bool isNullEntity(Entity* e)
{
	return e->unitId == -1;
}