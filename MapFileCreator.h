#pragma once

#include "model\World.h"
#include <fstream>

class MapFileCreator
{
public:
    static void createMapFile(const model::World& world)
    {
        if (1 == world.getTick())
        {
            std::ofstream mapFile;
            mapFile.open("map.txt");
            auto mapTiles = world.getTilesXY();
            for (auto vec : mapTiles)
            {
                for (auto vec1 : vec)
                {
                    mapFile << vec1 << " ";
                }
                mapFile << std::endl;
            }
            mapFile << "***" << std::endl;

            auto waypoints = world.getWaypoints();
            for (auto waypoint : waypoints)
            {
                mapFile << waypoint.at(0) << " " << waypoint.at(1) << std::endl;
            }
            mapFile.close();
        }
    }
private:
    MapFileCreator();
};

