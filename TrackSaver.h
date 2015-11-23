#pragma once

#include "fstream"

class TrackSaver
{
public:
    TrackSaver();
    void addCoordinates(double x, double y);
    ~TrackSaver();
private:
    bool isFileOpen;
    std::ofstream file;
};

