#ifndef LEVEL_H
#define LEVEL_H

#include "map.h"
#include "tileset.h"

class Level
{
public:
    Level(Tileset tileset, Map map) {
        this->tileset = tileset;
        this->map = map;
    }
    static Level loadLevel(QString tilesImageFilepath, QString metatilesFilepath, QString mapFilepath, int tilesBaseAddress);
    QPixmap render();
    void save(QString mapFilepath);
    Map map;
    Tileset tileset;
private:
    void saveMap(QString mapFilepath);
};

#endif // LEVEL_H
