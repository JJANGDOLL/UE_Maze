// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <map>

struct Position
{
	uint8 Col;
	uint8 Row;

	Position(uint8 InCol, uint8 InRow)
	{
		Col = InCol;
		Row = InRow;
	}

    bool operator==(const Position& rhs) const {
        return Col == rhs.Col && Row == rhs.Row;
    }

	bool operator<(const Position& rhs) const {
		return Col < rhs.Col || (Col == rhs.Col && Row < rhs.Row);
	}
};

enum class Direction : uint8
{
	EAST	= 0x1,
	WEST	= 0x2,
	SOUTH	= 0x4,
	NORTH	= 0x8,
};

struct Way
{
	Position Pos;
	Direction Dir;
	char Compass;

	Way(Position InPos, Direction InDir, char InCompass)
		: Pos(InPos), Dir(InDir), Compass(InCompass)
	{

	}
};

class MazeNode
{
public:
	MazeNode() 
		: bVisited(false)
	{
		Way northWay({ uint8(-1), uint8(0) }, Direction::NORTH, 'N');
		nextWay.push_back(northWay);

        Way southWay({ uint8(1), uint8(0) }, Direction::SOUTH, 'S');
        nextWay.push_back(southWay);

        Way westWay({ uint8(0), uint8(-1) }, Direction::WEST, 'W');
        nextWay.push_back(westWay);

        Way eastWay({ uint8(0), uint8(1) }, Direction::EAST, 'E');
        nextWay.push_back(eastWay);
	}

	~MazeNode()
	{

	}

	void prevRoute(Direction InPrevDir)
	{
		switch (InPrevDir)
		{
		case Direction::EAST:
			nextWay.erase(nextWay.begin() + 2);
			break;
		case Direction::WEST:
			nextWay.erase(nextWay.begin() + 3);
			break;
		case Direction::SOUTH:
			nextWay.erase(nextWay.begin() + 0);
			break;
		case Direction::NORTH:
			nextWay.erase(nextWay.begin() + 1);
			break;
		default:
			break;
		}
	}

	void addWall(Direction InWallDir)
	{
		_wall.push_back(InWallDir);
	}

	void setVisited()
	{
		bVisited = true;
	}

	bool isVisited()
	{
		return bVisited == true;
	}

public:
	std::vector<Way> nextWay;

private:
	std::vector<Direction> _wall;
	bool bVisited = false;
};

class MazeImpl;

class PROJECTM_API MazeGenerator
{
public:
	MazeGenerator();
	~MazeGenerator();

	void init(uint8 InMapSize);
	void generate();

private:
	TUniquePtr<MazeImpl> pImpl_;
};

class PROJECTM_API MazeImpl
{
public:
	void init(uint8 InMapSize);
    void generate();

private:
    uint8 _mapSize;
	std::vector<Position> _dfs;
	std::map<Position, MazeNode*> _mapNode;
};