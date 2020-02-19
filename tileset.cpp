#include "tileset.h"
#include "log.h"

#include <QFile>
#include <QPainter>

QList<QList<QRgb>> getPalettes(int paletteId) {
    switch (paletteId) {
    case 0:
    {
        QList<QRgb> pal0 = QList<QRgb>({qRgb(0x7 * 8, 0x14 * 8, 0x12 * 8), qRgb(0x1b * 8, 0x12 * 8, 0xe * 8), qRgb(0xf * 8, 0x4 * 8, 0x3 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal1 = QList<QRgb>({qRgb(0x7 * 8, 0x16 * 8, 0x1f * 8), qRgb(0x1b * 8, 0x12 * 8, 0xe * 8), qRgb(0xf * 8, 0x4 * 8, 0x3 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal2 = QList<QRgb>({qRgb(0x7 * 8, 0x16 * 8, 0x1f * 8), qRgb(0xe * 8, 0x1c * 8, 0x5 * 8), qRgb(0x5 * 8, 0xf * 8, 0x0 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal3 = QList<QRgb>({qRgb(0x1f * 8, 0x19 * 8, 0xe * 8), qRgb(0x14 * 8, 0xd * 8, 0x3 * 8), qRgb(0xc * 8, 0x5 * 8, 0x0 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal4 = QList<QRgb>({qRgb(0x8 * 8, 0x15 * 8, 0x1f * 8), qRgb(0x1d * 8, 0x17 * 8, 0xc * 8), qRgb(0x10 * 8, 0x9 * 8, 0x0 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal5 = QList<QRgb>({qRgb(0x1f * 8, 0x1f * 8, 0x1f * 8), qRgb(0x12 * 8, 0x1f * 8, 0x1f * 8), qRgb(0x7 * 8, 0x16 * 8, 0x1f * 8), qRgb(0x0 * 8, 0xc * 8, 0x1d * 8)});
        QList<QRgb> pal6 = QList<QRgb>({qRgb(0x7 * 8, 0x16 * 8, 0x1f * 8), qRgb(0x1f * 8, 0x1f * 8, 0x0 * 8), qRgb(0x18 * 8, 0x15 * 8, 0x0 * 8), qRgb(0x12 * 8, 0xe * 8, 0x0 * 8)});
        QList<QRgb> pal7 = QList<QRgb>({qRgb(0x1d * 8, 0x14 * 8, 0x10 * 8), qRgb(0x16 * 8, 0x9 * 8, 0x8 * 8), qRgb(0xf * 8, 0x4 * 8, 0x3 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        return QList<QList<QRgb>>({pal0, pal1, pal2, pal3, pal4, pal5, pal6, pal7});
    }
    case 1:
    {
        QList<QRgb> pal0 = QList<QRgb>({qRgb(0x1e * 8, 0x1b * 8, 0x11 * 8), qRgb(0x11 * 8, 0xe * 8, 0x4 * 8), qRgb(0xa * 8, 0x8 * 8, 0x1 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal1 = QList<QRgb>({qRgb(0xa * 8, 0x12 * 8, 0x1f * 8), qRgb(0xf * 8, 0x17 * 8, 0x1f * 8), qRgb(0x19 * 8, 0x1b * 8, 0x1f * 8), qRgb(0x1f * 8, 0x1f * 8, 0x1f * 8)});
        QList<QRgb> pal2 = QList<QRgb>({qRgb(0x13 * 8, 0x1f * 8, 0x17 * 8), qRgb(0xc * 8, 0x16 * 8, 0x11 * 8), qRgb(0x6 * 8, 0x10 * 8, 0xb * 8), qRgb(0x0 * 8, 0x4 * 8, 0x3 * 8)});
        QList<QRgb> pal3 = QList<QRgb>({qRgb(0xa * 8, 0x12 * 8, 0x1f * 8), qRgb(0x1b * 8, 0xe * 8, 0x7 * 8), qRgb(0x12 * 8, 0x5 * 8, 0x0 * 8), qRgb(0x6 * 8, 0x1 * 8, 0x0 * 8)});
        QList<QRgb> pal4 = QList<QRgb>({qRgb(0x15 * 8, 0x18 * 8, 0x1a * 8), qRgb(0xa * 8, 0xf * 8, 0x14 * 8), qRgb(0x5 * 8, 0x8 * 8, 0xb * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal5 = QList<QRgb>({qRgb(0x11 * 8, 0xe * 8, 0x4 * 8), qRgb(0x1b * 8, 0xe * 8, 0x7 * 8), qRgb(0x12 * 8, 0x5 * 8, 0x0 * 8), qRgb(0x6 * 8, 0x1 * 8, 0x0 * 8)});
        QList<QRgb> pal6 = QList<QRgb>({qRgb(0x11 * 8, 0xe * 8, 0x4 * 8), qRgb(0x17 * 8, 0x15 * 8, 0x15 * 8), qRgb(0xa * 8, 0x9 * 8, 0x9 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal7 = QList<QRgb>({qRgb(0x11 * 8, 0xe * 8, 0x4 * 8), qRgb(0x1f * 8, 0xb * 8, 0x13 * 8), qRgb(0xe * 8, 0x3 * 8, 0x6 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        return QList<QList<QRgb>>({pal0, pal1, pal2, pal3, pal4, pal5, pal6, pal7});
    }
    case 2:
    {
        QList<QRgb> pal0 = QList<QRgb>({qRgb(0x1f * 8, 0x1a * 8, 0x1d * 8), qRgb(0x15 * 8, 0x11 * 8, 0x13 * 8), qRgb(0xb * 8, 0x8 * 8, 0x6 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal1 = QList<QRgb>({qRgb(0xb * 8, 0x14 * 8, 0x1f * 8), qRgb(0x12 * 8, 0x1c * 8, 0xa * 8), qRgb(0x8 * 8, 0x17 * 8, 0x2 * 8), qRgb(0x1 * 8, 0xa * 8, 0x0 * 8)});
        QList<QRgb> pal2 = QList<QRgb>({qRgb(0x1f * 8, 0x1f * 8, 0x1f * 8), qRgb(0x14 * 8, 0x1b * 8, 0x1f * 8), qRgb(0xb * 8, 0x14 * 8, 0x1f * 8), qRgb(0x6 * 8, 0xc * 8, 0x17 * 8)});
        QList<QRgb> pal3 = QList<QRgb>({qRgb(0xb * 8, 0x14 * 8, 0x1f * 8), qRgb(0x1f * 8, 0x19 * 8, 0x14 * 8), qRgb(0x17 * 8, 0xb * 8, 0x9 * 8), qRgb(0xd * 8, 0x3 * 8, 0x3 * 8)});
        QList<QRgb> pal4 = QList<QRgb>({qRgb(0x1f * 8, 0x19 * 8, 0x14 * 8), qRgb(0x17 * 8, 0xb * 8, 0x9 * 8), qRgb(0x8 * 8, 0x17 * 8, 0x2 * 8), qRgb(0x1 * 8, 0xa * 8, 0x0 * 8)});
        QList<QRgb> pal5 = QList<QRgb>({qRgb(0x1d * 8, 0x19 * 8, 0xa * 8), qRgb(0x14 * 8, 0xf * 8, 0x2 * 8), qRgb(0x9 * 8, 0x6 * 8, 0x0 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal6 = QList<QRgb>({qRgb(0x1d * 8, 0x19 * 8, 0xa * 8), qRgb(0x14 * 8, 0xf * 8, 0x2 * 8), qRgb(0x9 * 8, 0x6 * 8, 0x0 * 8), qRgb(0x8 * 8, 0x17 * 8, 0x2 * 8)});
        QList<QRgb> pal7 = QList<QRgb>({qRgb(0x1d * 8, 0xc * 8, 0xa * 8), qRgb(0x16 * 8, 0x8 * 8, 0x1 * 8), qRgb(0xd * 8, 0x0 * 8, 0x0 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        return QList<QList<QRgb>>({pal0, pal1, pal2, pal3, pal4, pal5, pal6, pal7});
    }
    case 3:
    {
        QList<QRgb> pal0 = QList<QRgb>({qRgb(0x17 * 8, 0xa * 8, 0x17 * 8), qRgb(0xf * 8, 0x2 * 8, 0xf * 8), qRgb(0x8 * 8, 0x0 * 8, 0x8 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal1 = QList<QRgb>({qRgb(0x15 * 8, 0x1f * 8, 0xa * 8), qRgb(0xb * 8, 0x17 * 8, 0x2 * 8), qRgb(0x3 * 8, 0xd * 8, 0x0 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal2 = QList<QRgb>({qRgb(0x1a * 8, 0x17 * 8, 0x14 * 8), qRgb(0x11 * 8, 0x10 * 8, 0xd * 8), qRgb(0x9 * 8, 0x8 * 8, 0x7 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal3 = QList<QRgb>({qRgb(0x1f * 8, 0x1f * 8, 0x1f * 8), qRgb(0x1f * 8, 0x1f * 8, 0x0 * 8), qRgb(0xf * 8, 0x2 * 8, 0xf * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal4 = QList<QRgb>({qRgb(0x1f * 8, 0x19 * 8, 0x12 * 8), qRgb(0x1b * 8, 0x11 * 8, 0x5 * 8), qRgb(0x11 * 8, 0x9 * 8, 0x0 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal5 = QList<QRgb>({qRgb(0xf * 8, 0x2 * 8, 0xf * 8), qRgb(0x17 * 8, 0x5 * 8, 0x4 * 8), qRgb(0xe * 8, 0x1 * 8, 0x1 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal6 = QList<QRgb>({qRgb(0x1f * 8, 0x1f * 8, 0x0 * 8), qRgb(0x1c * 8, 0xf * 8, 0x4 * 8), qRgb(0x16 * 8, 0x4 * 8, 0xe * 8), qRgb(0xf * 8, 0x2 * 8, 0xf * 8)});
        QList<QRgb> pal7 = QList<QRgb>({qRgb(0x11 * 8, 0x10 * 8, 0x1f * 8), qRgb(0xa * 8, 0x8 * 8, 0x18 * 8), qRgb(0x5 * 8, 0x3 * 8, 0x11 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        return QList<QList<QRgb>>({pal0, pal1, pal2, pal3, pal4, pal5, pal6, pal7});
    }
    default:
    {
        QList<QRgb> pal0 = QList<QRgb>({qRgb(0x1f * 8, 0x15 * 8, 0x13 * 8), qRgb(0x16 * 8, 0xa * 8, 0x6 * 8), qRgb(0xd * 8, 0x4 * 8, 0x2 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal1 = QList<QRgb>({qRgb(0xf * 8, 0x12 * 8, 0x1f * 8), qRgb(0xc * 8, 0x19 * 8, 0x3 * 8), qRgb(0x5 * 8, 0xd * 8, 0x1 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal2 = QList<QRgb>({qRgb(0xf * 8, 0x12 * 8, 0x1f * 8), qRgb(0x12 * 8, 0x1a * 8, 0xb * 8), qRgb(0xb * 8, 0xa * 8, 0x1 * 8), qRgb(0x1c * 8, 0x14 * 8, 0xe * 8)});
        QList<QRgb> pal3 = QList<QRgb>({qRgb(0x1f * 8, 0x17 * 8, 0xe * 8), qRgb(0x16 * 8, 0xd * 8, 0x2 * 8), qRgb(0xc * 8, 0x6 * 8, 0x0 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal4 = QList<QRgb>({qRgb(0xc * 8, 0x19 * 8, 0x3 * 8), qRgb(0x5 * 8, 0xd * 8, 0x1 * 8), qRgb(0x12 * 8, 0x1a * 8, 0xb * 8), qRgb(0x1c * 8, 0x14 * 8, 0xe * 8)});
        QList<QRgb> pal5 = QList<QRgb>({qRgb(0x1f * 8, 0x1c * 8, 0x4 * 8), qRgb(0x11 * 8, 0x10 * 8, 0x0 * 8), qRgb(0x9 * 8, 0x8 * 8, 0x0 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal6 = QList<QRgb>({qRgb(0xf * 8, 0x12 * 8, 0x1f * 8), qRgb(0x16 * 8, 0x14 * 8, 0x11 * 8), qRgb(0xc * 8, 0x9 * 8, 0x8 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        QList<QRgb> pal7 = QList<QRgb>({qRgb(0xc * 8, 0x19 * 8, 0x3 * 8), qRgb(0x5 * 8, 0xd * 8, 0x1 * 8), qRgb(0x11 * 8, 0x10 * 8, 0x0 * 8), qRgb(0x0 * 8, 0x0 * 8, 0x0 * 8)});
        return QList<QList<QRgb>>({pal0, pal1, pal2, pal3, pal4, pal5, pal6, pal7});
    }
    }
}

QMap<int, QImage> readTiles(QString tilesImageFilepath, int tilesBaseAddress, QString tileAttributesFilepath, int palettesId) {
    QImage blank = QImage(8, 8, QImage::Format_RGBA8888);
    QImage tilesImage;
    if (QFile::exists(tilesImageFilepath)) {
        tilesImage = QImage(tilesImageFilepath);
    } else {
        tilesImage = blank;
    }

    QList<QList<QRgb>> palettes;
    QByteArray tileAttributes;
    if (!tileAttributesFilepath.isEmpty()) {
        QFile attrsFile(tileAttributesFilepath);
        if (attrsFile.open(QIODevice::ReadOnly)) {
            tileAttributes = attrsFile.readAll();
            palettes = getPalettes(palettesId);
        }
    }

    int w = tilesImage.width() / 8;
    int h = tilesImage.height() / 8;
    int firstTile = (tilesBaseAddress - 0x8000) >> 4;
    QMap<int, QImage> tiles;

    // Insert the blank tiles that come before the base tiles.
    for (int i = 0; i < firstTile - 0x80; i++) {
        tiles.insert(i, blank);
    }

    // Populate every tile from the tiles image.
    int tileId = firstTile;
    int attrIndex = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            QImage tile = tilesImage.copy(x * 8, y * 8, 8, 8);
            if (attrIndex < tileAttributes.size()) {
                char palId = tileAttributes[attrIndex];
                attrIndex++;
                if (palId < palettes.size()) {
                    for (int i = 0; i < 4; i++) {
                        tile.setColor(i, palettes[palId][i]);
                    }
                }
            }
            tiles.insert(tileId, tile);
            tileId++;
            if (tileId == 0x100) {
                tileId = 0x0;
            }
        }
    }

    // Insert blank tiles for any missing tiles.
    for (int i = 0; i < 0x100; i++) {
        if (!tiles.contains(i)) {
            tiles.insert(i, blank);
        }
    }

    return tiles;
}

Tileset buildTilesetCommon(QString metatilesFilepath, QMap<int, QImage> tiles) {
    QList<Metatile> metatileDefinitions;
    QFile metatilesFile(metatilesFilepath);
    if (metatilesFile.open(QIODevice::ReadOnly)) {
        QByteArray data = metatilesFile.readAll();
        int numMetatiles = data.length() / 4;
        for (int i = 0; i < numMetatiles; i++) {
            int index = i * 4;
            Metatile metatile;
            metatile.topLeft     = static_cast<uchar>(data.at(index));
            metatile.topRight    = static_cast<uchar>(data.at(index + 1));
            metatile.bottomLeft  = static_cast<uchar>(data.at(index + 2));
            metatile.bottomRight = static_cast<uchar>(data.at(index + 3));
            metatileDefinitions.append(metatile);
        }
    }

    QList<QImage> metatiles;
    for (Metatile m : metatileDefinitions) {
        QImage image = QImage(16, 16, QImage::Format_RGBA8888);
        QPainter painter(&image);
        painter.drawImage(0, 0, tiles.value(m.topLeft));
        painter.drawImage(8, 0, tiles.value(m.topRight));
        painter.drawImage(0, 8, tiles.value(m.bottomLeft));
        painter.drawImage(8, 8, tiles.value(m.bottomRight));
        metatiles.append(image);
    }

    return Tileset(tiles, metatiles, metatileDefinitions);
}

Tileset Tileset::buildTilesetGBC(QString tilesImageFilepath, QString metatilesFilepath, int tilesBaseAddress, QString tileAttributesFilepath, int palettesId) {
    QMap<int, QImage> tiles = readTiles(tilesImageFilepath, tilesBaseAddress, tileAttributesFilepath, palettesId);
    return buildTilesetCommon(metatilesFilepath, tiles);
}

Tileset Tileset::buildTileset(QString tilesImageFilepath, QString metatilesFilepath, int tilesBaseAddress) {
    QMap<int, QImage> tiles = readTiles(tilesImageFilepath, tilesBaseAddress, "", 0);
    return buildTilesetCommon(metatilesFilepath, tiles);
}

QImage Tileset::getMetatileImage(int metatileId) {
    if (metatileId >= this->metatiles.size()) {
        logError(QString("Invalid metatile id %1. Max metatile id is %1").arg(metatileId).arg(this->metatiles.size() - 1));
        return QImage();
    }
    return this->metatiles.at(metatileId);
}
