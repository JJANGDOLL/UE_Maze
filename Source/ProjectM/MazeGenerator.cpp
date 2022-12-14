// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include <random>
#include <Engine/World.h>
#include "Global.h"
#include "WorldBuilder.h"


class MazeGenerator::MazeImpl {
public:
    MazeImpl() = default;

    ~MazeImpl() = default;

    void init(uint8 InMapSize)
    {
        PrintLine();

        _mapSize = InMapSize + 2;

        _dfs.push_back({ 1, 1 });

        _startPos = Position(0, 0);
        _endPos = Position(0, 0);
    }

    void generate()
    {
        PrintLine();

        std::random_device rd;
        auto rng = std::default_random_engine{ rd() };

        _mapNode.clear();

        for (uint8 c = 0; c < _mapSize; c++)
        {
            for (uint8 r = 0; r < _mapSize; r++)
            {
                Position pos{ c, r };
                MazeNode* mn = new MazeNode();
                if (r == 0 || r == _mapSize - 1 || c == 0 || c == _mapSize - 1)
                {
                    mn->setVisited();
                }
                _mapNode[pos] = mn;
            }
        }

        uint16 goalDepth = 0;

        while (!_dfs.empty())
        {
            if (goalDepth < _dfs.size())
            {
                goalDepth = _dfs.size();
                _endPos = _dfs.back();
            }


            if (_mapNode[_dfs.back()]->nextWay.empty())
            {
                _dfs.pop_back();
                continue;
            }

            _mapNode[_dfs.back()]->setVisited();
            //int random = rand() % _mapNode[_dfs.back()]->nextWay.size();
            //Way sel_elem = _mapNode[_dfs.back()]->nextWay[random];
            //_mapNode[_dfs.back()]->nextWay.erase(_mapNode[_dfs.back()]->nextWay.begin() + random);
            std::shuffle(_mapNode[_dfs.back()]->nextWay.begin(), _mapNode[_dfs.back()]->nextWay.end(), rng);

            while (!_mapNode[_dfs.back()]->nextWay.empty())
            {
                Way nw = _mapNode[_dfs.back()]->nextWay.back();
                _mapNode[_dfs.back()]->nextWay.pop_back();

                Position npos{ uint8(_dfs.back().Col + nw.Pos.Col), uint8(_dfs.back().Row + nw.Pos.Row) };
                if (_mapNode[npos]->isVisited())
                {
                    _mapNode[_dfs.back()]->addWall(nw.Dir);
                }
                else
                {
                    _dfs.push_back(npos);
                    _mapNode[_dfs.back()]->prevRoute(nw.Dir);
                    break;
                }
            }
        }
    }

    void build()
    {
//         AWorldBuilder* worldBuilder = _world->SpawnActor<AWorldBuilder>(AWorldBuilder::StaticClass());
//         worldBuilder->build(_mapNode);
    }

    std::map<Position, MazeNode*> getMaze()
    {
        return _mapNode;
    }

    Position getGoalPos()
    {
        return _endPos;
    }

private:
    uint8 _mapSize;
    std::vector<Position> _dfs;
    std::map<Position, MazeNode*> _mapNode;
    Position _startPos;
    Position _endPos;
};

MazeGenerator::MazeGenerator() : pimpl_(new MazeImpl) {};
MazeGenerator::~MazeGenerator() = default;

void MazeGenerator::init(uint8 InMapSize)
{
    pimpl_->init(InMapSize);
}

void MazeGenerator::generate()
{
    pimpl_->generate();
}

void MazeGenerator::build()
{
    pimpl_->build();
}

Position MazeGenerator::getGoalPos()
{
    return pimpl_->getGoalPos();
}

std::map<Position, MazeNode*> MazeGenerator::getMaze()
{
    return pimpl_->getMaze();
}

