// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "Global.h"
#include <random>
#include <Engine/World.h>
#include "WorldBuilder.h"


class MazeGenerator::MazeImpl {
public:
    MazeImpl() = default;

    ~MazeImpl() = default;

    void init(uint8 InMapSize, UWorld* InWorld)
    {
        PrintInfo();

        _mapSize = InMapSize + 2;
        _world = InWorld;

        _dfs.push_back({ 1, 1 });

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
    }

    void generate()
    {
        std::random_device rd;
        auto rng = std::default_random_engine{ rd() };

        PrintInfo();


        while (!_dfs.empty())
        {
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
        AWorldBuilder* worldBuilder = _world->SpawnActor<AWorldBuilder>(AWorldBuilder::StaticClass());
        worldBuilder->build(_mapNode);
    }

private:
    uint8 _mapSize;
    std::vector<Position> _dfs;
    std::map<Position, MazeNode*> _mapNode;
    UWorld* _world;
};

MazeGenerator::MazeGenerator() : pimpl_(new MazeImpl{}) {};
MazeGenerator::~MazeGenerator() = default;

void MazeGenerator::init(uint8 InMapSize, UWorld* InWorld)
{
    pimpl_->init(InMapSize, InWorld);
}

void MazeGenerator::generate()
{
    pimpl_->generate();
}

void MazeGenerator::build()
{
    pimpl_->build();
}
