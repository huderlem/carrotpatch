#include "level.h"
#include "log.h"
#include <QPixmap>
#include <QPainter>

Level Level::loadLevel(QString tilesImageFilepath, QString metatilesFilepath, QString mapFilepath, int tilesBaseAddress) {
    Tileset tileset = Tileset::buildTileset(tilesImageFilepath, metatilesFilepath, tilesBaseAddress);
    Map map = Map::loadMap(mapFilepath);
    return Level(tileset, map);
}

QPixmap Level::render() {
    int metatileWidth = this->map.getMetatileWidth();
    int metatileHeight = this->map.getMetatileHeight();
    QImage levelImage = QImage(metatileWidth * 16, metatileHeight * 16, QImage::Format_RGBA8888);
    QPainter levelPainter(&levelImage);
    for (int j = 0; j < metatileHeight; j++) {
        for (int i = 0; i < metatileWidth; i++) {
            int metatileId = this->map.getMetatileId(i, j);
            QImage metatileImage = this->tileset.getMetatileImage(metatileId);
            QPoint origin = QPoint(i * 16, j * 16);
            levelPainter.drawImage(origin, metatileImage);
        }
    }

    levelPainter.drawImage(QPoint(0, 0), this->tileset.getMetatileImage(0x0));
    levelPainter.drawImage(QPoint(16, 0), this->tileset.getMetatileImage(0x0));
    levelPainter.drawImage(QPoint(32, 0), this->tileset.getMetatileImage(0x0));
    levelPainter.drawImage(QPoint(48, 0), this->tileset.getMetatileImage(0x0));
    levelPainter.drawImage(QPoint(64, 0), this->tileset.getMetatileImage(0x0));
    levelPainter.drawImage(QPoint(80, 0), this->tileset.getMetatileImage(0x0));

    levelPainter.end();

    QPixmap pixmap;
    return pixmap.fromImage(levelImage);
}

void Level::save(QString mapFilepath) {
    this->map.save(mapFilepath);
}
