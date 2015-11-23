#include "TrackSaver.h"

TrackSaver::TrackSaver() :
    isFileOpen(false)
{
}

void TrackSaver::addCoordinates(double x, double y)
{
    if ( ! isFileOpen)
    {
        file.open("coordinates.txt");
        isFileOpen = true;
    }
    file << x << " " << y << std::endl;
}

TrackSaver::~TrackSaver()
{
    if (isFileOpen)
    {
        file.close();
    }
}
