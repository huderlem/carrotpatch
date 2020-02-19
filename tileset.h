#ifndef TILESET_H
#define TILESET_H

#include <QMap>
#include <QImage>

struct Metatile {
    uchar topLeft;
    uchar topRight;
    uchar bottomLeft;
    uchar bottomRight;
};

class Tileset
{
public:
    Tileset() {}
    Tileset(QMap<int, QImage> tiles, QList<QImage> metatiles, QList<Metatile> metatileDefinitions) {
        this->tiles = tiles;
        this->metatiles = metatiles;
        this->metatileDefinitions = metatileDefinitions;
    }
    static Tileset buildTileset(QString tilesImageFilepath, QString metatilesFilepath, int tilesBaseAddress);
    static Tileset buildTilesetGBC(QString tilesImageFilepath, QString metatilesFilepath, int tilesBaseAddress, QString tileAttributesFilepath, int palettesId);
    QImage getMetatileImage(int metatileId);
    QMap<int, QImage> tiles;
    QList<QImage> metatiles;
    QList<Metatile> metatileDefinitions;
};

#endif // TILESET_H
