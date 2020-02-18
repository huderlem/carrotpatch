#ifndef LEVEL_H
#define LEVEL_H

#include "map.h"
#include "tileset.h"
#include <QPixmap>

class Level
{
public:
    Level() {}
    Level(Tileset tileset, Map map) {
        this->tileset = tileset;
        this->map = map;
    }
    static Level loadLevel(QString tilesImageFilepath, QString metatilesFilepath, QString mapFilepath, int tilesBaseAddress);
    QPixmap render(bool ignoreCache);
    void save(QString mapFilepath);
    Map map;
    Tileset tileset;
private:
    void saveMap(QString mapFilepath);
    QImage mapImage;
    QPixmap mapPixmap;
};

#endif // LEVEL_H
