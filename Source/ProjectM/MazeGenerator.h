// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <map>
#include "Datas/Structures.h"

enum Direction : uint8
{
    NONE = 0x0,
    EAST = 0x1,
    WEST = 0x2,
    SOUTH = 0x4,
    NORTH = 0x8,
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
        _wall += InWallDir;
    }

    void setVisited()
    {
        bVisited = true;
    }

    bool isVisited()
    {
        return bVisited == true;
    }

    uint8 GetWall()
    {
        return _wall;
    }

public:
    std::vector<Way> nextWay;

private:
    uint8 _wall = 0;
    bool bVisited = false;
};

class PROJECTM_API MazeGenerator
{
public:
	MazeGenerator();
	~MazeGenerator();

	void init(uint8 InMapSize);
	void generate();
	void build();
    std::map<Position, MazeNode*> getMaze();

private:
	class MazeImpl;
	TUniquePtr<MazeImpl> pimpl_;
};

