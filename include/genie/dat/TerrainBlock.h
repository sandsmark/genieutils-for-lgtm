/*
    geniedat - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2014 - 2015  Mikko "Tapsa" P

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GENIE_TERRAINBLOCK_H
#define GENIE_TERRAINBLOCK_H
#include "genie/file/ISerializable.h"
#include "genie/dat/TerrainCommon.h"
#include "genie/dat/Terrain.h"
#include "genie/dat/TerrainBorder.h"

namespace genie {

class TileSize : public ISerializable
{
public:
    void setGameVersion(GameVersion gv) override;

    int16_t Width;
    int16_t Height;
    int16_t DeltaY;

    bool compareTo(const TileSize &other) const;

private:
    void serializeObject(void) override;
};

class TerrainBlock : public ISerializable
{
public:
    void setGameVersion(GameVersion gv) override;

    int32_t VirtualFunctionPtr;
    int32_t MapPointer;
    int32_t MapWidth;
    int32_t MapHeight;
    int32_t WorldWidth;
    int32_t WorldHeight;
    int16_t PaddingTS;

    std::array<TileSize, SharedTerrain::TILE_TYPE_COUNT> TileSizes;
    std::vector<Terrain> Terrains;

    std::vector<int16_t> AoEAlphaUnknown; // These are very similar to borders
    std::array<TerrainBorder, 16> TerrainBorders;

    int32_t MapRowOffset;
    float MapMinX = 0.f;
    float MapMinY = 0.f;
    float MapMaxX = 0.f;
    float MapMaxY = 0.f;
    float MapMaxXplus1 = 0.f;
    float MapMaxYplus1 = 0.f;

    uint16_t TerrainsUsed2;
    uint16_t RemovedBlocksUsed = 0;
    uint16_t BordersUsed;
    int16_t MaxTerrain;
    int16_t TileWidth;
    int16_t TileHeight;
    int16_t TileHalfHeight;
    int16_t TileHalfWidth;
    int16_t ElevHeight;
    int16_t CurRow;
    int16_t CurCol;
    int16_t BlockBegRow;
    int16_t BlockEndRow;
    int16_t BlockBegCol;
    int16_t BlockEndCol;

    int32_t SearchMapPtr;
    int32_t SearchMapRowsPtr;
    int8_t AnyFrameChange;

    int8_t MapVisibleFlag;
    int8_t FogFlag;

    unsigned short getBytesSize(void);
    std::vector<int8_t> SomeBytes;
    unsigned short getSomethingSize(void);
    std::vector<int32_t> SomeInt32;

    bool compareTo(const TerrainBlock &other) const;

private:
    void serializeObject(void) override;
};
} // namespace genie

#endif // GENIE_DATFILE_H
