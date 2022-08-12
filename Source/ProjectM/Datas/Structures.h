#pragma once

#include "CoreMinimal.h"

struct Position
{
    uint8 Col;
    uint8 Row;

    Position() {};

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