#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QList>

struct Tile {
    uchar metatileId;
};

class Map
{
public:
    Map() {}
    Map(int metatileWidth, int metatileHeight, QList<uchar> metatiles) {
        this->metatileWidth = metatileWidth;
        this->metatileHeight = metatileHeight;
        for (uchar metatileId : metatiles) {
            Tile *tile = new Tile;
            tile->metatileId = metatileId;
            this->tiles.append(tile);
        }
        this->cacheMetatiles();
    }
    static Map loadMap(QString mapFilepath);
    void save(QString mapFilepath);
    int getMetatileWidth() { return this->metatileWidth; }
    int getMetatileHeight() { return this->metatileHeight; }
    Tile *getTile(int x, int y);
    void setMetatileId(int x, int y, uchar metatileId);
    bool isInBounds(int x, int y);
    void cacheMetatiles();
    bool metatileChanged(int x, int y);
private:
    void getBlocks(QList<QByteArray> *blockDefinitions, QList<int> *blocks);
    QList<Tile*> tiles;
    QList<uchar> cachedMetatiles;
    int metatileWidth;
    int metatileHeight;
};

#endif // MAP_H
