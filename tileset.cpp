#include "tileset.h"
#include "log.h"

#include <QFile>
#include <QPainter>

Tileset Tileset::buildTileset(QString tilesImageFilepath, QString metatilesFilepath, int tilesBaseAddress) {
    QImage blank = QImage(8, 8, QImage::Format_RGBA8888);
    QImage tilesImage;
    if (QFile::exists(tilesImageFilepath)) {
        tilesImage = QImage(tilesImageFilepath);
    } else {
        tilesImage = blank;
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
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            QImage tile = tilesImage.copy(x * 8, y * 8, 8, 8);
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

QImage Tileset::getMetatileImage(int metatileId) {
    if (metatileId >= this->metatiles.size()) {
        logError(QString("Invalid metatile id %1. Max metatile id is %1").arg(metatileId).arg(this->metatiles.size() - 1));
        return QImage();
    }
    return this->metatiles.at(metatileId);
}
