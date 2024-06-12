#include "Stdafx.h"
#include "RouteFind.h"
#include <unordered_set>

HRESULT RouteFind::init()
{
	_selected.x = 0;
	_selected.y = 0;
	_mapSize.x = 0;
	_mapSize.y = 0;
	_playerCoord.x = 0;
	_playerCoord.y = 0;
	_moveTile.x = 0;
	_moveTile.y = 0;

	_isMove = false;

	return S_OK;
}

void RouteFind::release(void)
{
}

void RouteFind::update(Point2D camera)
{
	_selected.x = TILEMANAGER->getSelectedTile().x;
	_selected.y = TILEMANAGER->getSelectedTile().y;

	if (_vRoute.size() != 0)
	{
		if (_vRoute.size() == 1)
		{
			MoveToPoint(_movePoint);
		}
		else
			MoveToTile(_vRoute[0]);
	}
}

void RouteFind::render(HDC hdc)
{
	char temp[128];
	wsprintf(temp, "%d, %d", _objectLocation.x, _objectLocation.y);
	TextOut(hdc, 10, 110, temp, strlen(temp));
}

void RouteFind::WayPoint(Point2D objectCoord, Point2D targetTile)
{
	routeTile = objectCoord;
	_vRoute.clear();
	while (routeTile != targetTile)
	{
		_vNeighborTile.clear();
		_vNeighborTile.push_back(routeTile + Point2D(1, 0));
		_vNeighborTile.push_back(routeTile + Point2D(-1, 0));
		_vNeighborTile.push_back(routeTile + Point2D(0, -1));
		_vNeighborTile.push_back(routeTile + Point2D(0, 1));
		_vNeighborTile.push_back(routeTile + Point2D(1, 1));
		_vNeighborTile.push_back(routeTile + Point2D(1, -1));
		_vNeighborTile.push_back(routeTile + Point2D(-1, 1));
		_vNeighborTile.push_back(routeTile + Point2D(-1, -1));

		vector<Point2D>::iterator iter;
		iter = _vNeighborTile.begin();

		for (; iter != _vNeighborTile.end();)
		{
			if (targetTile == iter)
			{
				_vRoute.push_back(*iter);
				return;
			}
			else if (iter->x < 0 || iter->y <0 || iter->x > TILEMANAGER->getWorldSize().x || iter->y > TILEMANAGER->getWorldSize().y)
			{
				iter = _vNeighborTile.erase(iter);
			}
			else if (TILEMANAGER->getWall()[iter->x + (iter->y * TILEMANAGER->getWorldSize().x)] != 1)
			{
				iter = _vNeighborTile.erase(iter);
			}
			else
				++iter;
		}

		Point2D next = distanceBetweenTile(targetTile);
		_vRoute.push_back(next);
		routeTile = next;
	}
}

void RouteFind::FindPath(Point2D objectCoord, Point2D targetTile)
{
	_vRoute.clear();
	if (objectCoord == targetTile)
	{
		_vRoute.push_back(targetTile);
		return;
	}

	vector<Node>& nodes = TILEMANAGER->getNode();
	Node* startNode = &nodes[objectCoord.x + (objectCoord.y * TILEMANAGER->getWorldSize().x)];
	Node* targetNode = &nodes[targetTile.x + (targetTile.y * TILEMANAGER->getWorldSize().x)];

	vector<Node*> openSet;
	unordered_set<Node*> closedSet;

	openSet.push_back(startNode);
	openSet[0]->gCost = 0;
	openSet[0]->hCost = TILEMANAGER->GetDistance(openSet[0], targetNode);

 	while (!openSet.empty())
	{
		Node* currentNode = openSet[0];

		for (int i = 0; i < openSet.size(); ++i)
		{
			if (openSet[i]->fCost() < currentNode->fCost() || 
				openSet[i]->fCost() == currentNode->fCost() && openSet[i]->hCost < currentNode->hCost)
				currentNode = openSet[i];
		}

		auto it = find(openSet.begin(), openSet.end(), currentNode);
		openSet.erase(it);
		closedSet.insert(currentNode);
		
		if (currentNode->num == targetNode->num)
		{
			RetracePath(*startNode, *currentNode);
			return;
		}
		
		vector<Node*> neighbour = TILEMANAGER->GetNeighbours(currentNode);
		for (int k = 0; k < neighbour.size(); ++k)
		{
			Node* target = neighbour[k];
			if (TILEMANAGER->getWall()[target->num] != 1 || closedSet.find(target) != closedSet.end())
				continue;
		
			int newCostToNeightbour = currentNode->gCost + TILEMANAGER->GetDistance(currentNode, target);
			bool isIncluded = find(openSet.begin(), openSet.end(), target) == openSet.end();
			if (newCostToNeightbour < target->gCost || isIncluded)
			{
				target->gCost = newCostToNeightbour;
				target->hCost = TILEMANAGER->GetDistance(target, targetNode);
				target->parentNum = currentNode->num;

				if (isIncluded)
					openSet.push_back(target);
			}
		}
	}
}


void RouteFind::RetracePath(Node start, Node end)
{
	vector<Node> path;
	Node currentNode = end;

	while (currentNode.num != start.num)
	{
		path.push_back(currentNode);
		currentNode = TILEMANAGER->getNode()[currentNode.parentNum];
	}

	reverse(path.begin(), path.end());

	int worldX = TILEMANAGER->getWorldSize().x;
	for (int i = 0; i < path.size(); ++i)
	{
		int x = path[i].num % worldX;
		int y = path[i].num / worldX;
		_vRoute.push_back(Point2D(x, y));
	}
}

//타일간 거리 계산
Point2D RouteFind::distanceBetweenTile(Point2D targetTile)
{
	Point2D nextTile;
	float tempMin = 0;
	for (Point2D& neighbor : _vNeighborTile)
	{
		if (neighbor == targetTile)
		{
			nextTile = neighbor;
			break;
		}
		else if (tempMin > neighbor.distance(targetTile) || tempMin == 0)
		{
			tempMin = neighbor.distance(targetTile);
			nextTile = neighbor;
		}
	}

	return nextTile;
}

//타일로 이동
void RouteFind::MoveToTile(Point2D tile)
{
	Point2D tempPt;
	Vector2D directionVec;

	tempPt = TileCenterLocation(tile) - _objectLocation;
	directionVec = tempPt * _speed / tempPt.magnitude();


	if (_objectLocation.approximate(TileCenterLocation(tile), 5))
		_objectLocation = TileCenterLocation(tile);
	else
	{
		_objectLocation.x += directionVec.x;
		_objectLocation.y += directionVec.y;
	}


	if (_objectLocation == TileCenterLocation(tile) && _vRoute.size() > 0)
	{
		_vRoute.erase(_vRoute.begin());
	}
	else
	{
		destAngle = getAngle(_objectLocation.x, _objectLocation.y, TileCenterLocation(tile).x, TileCenterLocation(tile).y);
	}

}

//타일 좌표로 이동
void RouteFind::MoveToPoint(Point2D point)
{
	Point2D tempPt;
	Vector2D directionVec;

	tempPt = point - _objectLocation;
	directionVec = tempPt * _speed / tempPt.magnitude();

	if (_objectLocation.approximate(point, 5))
		_objectLocation = point;
	else
	{
		_objectLocation.x += directionVec.x;
		_objectLocation.y += directionVec.y;
	}


	if (_objectLocation == point && _vRoute.size() > 0)
	{
		_vRoute.erase(_vRoute.begin());
	}
	else
	{
		destAngle = getAngle(_objectLocation.x, _objectLocation.y, point.x, point.y);
	}
}

//타일 좌표를 픽셀좌표로 치환
Point2D RouteFind::TileCenterLocation(Point2D Location)
{
	return Point2D(((TILEMANAGER->getOrigin().x * TILE_WIDTH) + ((Location.x - Location.y) * (TILE_WIDTH / 2))) + TILE_WIDTH / 2,
		((TILEMANAGER->getOrigin().y * TILE_HEIGHT) + ((Location.x + Location.y) * (TILE_HEIGHT / 2))) + TILE_HEIGHT / 2);
}

//타일좌표 계산 
Point2D RouteFind::CoordCheck(Point2D Location)
{
	Point2D coord;
	Point2D _pCell = Point2D(Location.x / TILE_WIDTH, Location.y / TILE_HEIGHT);

	coord = Point2D(
		(_pCell.y - TILEMANAGER->getOrigin().y) + (_pCell.x - TILEMANAGER->getOrigin().x),
		(_pCell.y - TILEMANAGER->getOrigin().y) - (_pCell.x - TILEMANAGER->getOrigin().x));

	COLORREF color = GetPixel(IMAGEMANAGER->findImage("TestTile")->getMemDC(), Location.x % TILE_WIDTH, Location.y % TILE_HEIGHT);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	if (r == 255 && g == 0 && b == 0)
	{
		coord += Point2D(-1, 0);
	}
	else if (r == 0 && g == 0 && b == 255)
	{
		coord += Point2D(0, -1);
	}
	else if (r == 0 && g == 255 && b == 0)
	{
		coord += Point2D(0, 1);
	}
	else if (r == 255 && g == 255 && b == 0)
	{
		coord += Point2D(1, 0);
	}

	return coord;
}

class Coord
{
	public: 
		int gCost;
		int hCost;
};