#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QList>

class Map
{
public:
    Map() {}
    Map(int metatileWidth, int metatileHeight, QList<uchar> metatiles) {
        this->metatileWidth = metatileWidth;
        this->metatileHeight = metatileHeight;
        this->metatiles = metatiles;
    }
    static Map loadMap(QString mapFilepath);
    void save(QString mapFilepath);
    int getMetatileWidth() { return this->metatileWidth; }
    int getMetatileHeight() { return this->metatileHeight; }
    int getMetatileId(int x, int y);
    void setMetatileId(int x, int y, uchar metatileId);
private:
    void getBlocks(QList<QByteArray> *blockDefinitions, QList<int> *blocks);
    QList<uchar> metatiles;
    int metatileWidth;
    int metatileHeight;
};

#endif // MAP_H
