/*
    geniedat - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2011 - 2017  Mikko "Tapsa" P

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

#ifndef GENIE_UNKNOWN_H
#define GENIE_UNKNOWN_H
#include "genie/file/ISerializable.h"

namespace genie {

// Not read by game
class MapElevation : public ISerializable
{
public:
    void setGameVersion(GameVersion gv) override;

    int32_t Proportion = 0;
    int32_t Terrain = -1;
    int32_t ClumpCount = 0;
    int32_t BaseTerrain = -1;
    int32_t BaseElevation = 0;
    int32_t TileSpacing = 0;

    bool compareTo(const MapElevation &other) const;

private:
    void serializeObject(void) override;
};

class MapUnit : public ISerializable
{
public:
    void setGameVersion(GameVersion gv) override;

    int32_t Unit = -1;
    int32_t HostTerrain = -1;
    int8_t GroupPlacing = 0;
    int8_t ScaleFlag = 0;
    int16_t Padding1 = 0;
    int32_t ObjectsPerGroup = 1;
    int32_t Fluctuation = 0;
    int32_t GroupsPerPlayer = 1;
    int32_t GroupArea = 1;
    int32_t PlayerID = 0;
    int32_t SetPlaceForAllPlayers = 1;
    int32_t MinDistanceToPlayers = 2;
    int32_t MaxDistanceToPlayers = 6;

    bool compareTo(const MapUnit &other) const;

private:
    void serializeObject(void) override;
};

class MapTerrain : public ISerializable
{
public:
    void setGameVersion(GameVersion gv) override;

    int32_t Proportion = 0;
    int32_t Terrain = -1;
    int32_t ClumpCount = 0;
    int32_t EdgeSpacing = 0;
    int32_t PlacementTerrain = -1;
    int32_t Clumpiness = 0;

    bool compareTo(const MapTerrain &other) const;

private:
    void serializeObject(void) override;
};

class MapLand : public ISerializable
{
public:
    void setGameVersion(GameVersion gv) override;

    int32_t LandID = 1;
    int32_t Terrain = -1;
    int32_t LandSpacing = 2;
    int32_t BaseSize = 7;
    int8_t Zone = 0;
    int8_t PlacementType = 1;
    int16_t Padding1 = 0;
    int32_t BaseX = 0;
    int32_t BaseY = 0;
    int8_t LandProportion = 100;
    int8_t ByPlayerFlag = 1;
    int16_t Padding2 = 0;
    int32_t StartAreaRadius = 10;
    int32_t TerrainEdgeFade = 25;
    int32_t Clumpiness = 8;

    bool compareTo(const MapLand &other) const;

private:
    void serializeObject(void) override;
};

class MapInfo : public ISerializable
{
public:
    void setGameVersion(GameVersion gv) override;

    int32_t MapID = -1;

    int32_t BorderSouthWest = 0;
    int32_t BorderNorthWest = 0;
    int32_t BorderNorthEast = 0;
    int32_t BorderSouthEast = 0;
    int32_t BorderUsage = 0;
    int32_t WaterShape = 10;
    int32_t BaseTerrain = -1;
    int32_t LandCoverage = 80;
    int32_t UnusedID = 0;

    // These pointers are overwritten
    int32_t MapLandsPtr = 0;
    int32_t MapTerrainsPtr = 0;
    int32_t MapUnitsPtr = 0;
    int32_t MapElevationsPtr = 0;

    std::vector<MapLand> MapLands;
    std::vector<MapTerrain> MapTerrains;
    std::vector<MapUnit> MapUnits;
    std::vector<MapElevation> MapElevations;

    bool compareTo(const MapInfo &other) const;

private:
    bool io_all_ = false;

    void serializeObject(void) override;
};

class RandomMaps : public ISerializable
{
public:
    void setGameVersion(GameVersion gv) override;

    // Overwritten
    int32_t RandomMapsPtr = 0;

    std::vector<MapInfo> Maps;

    bool compareTo(const RandomMaps &other) const;

private:
    std::vector<std::array<int32_t, 852>> OldMaps;

    void serializeObject(void) override;
};
} // namespace genie

#endif // GENIE_UNKNOWN_H
