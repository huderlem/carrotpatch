#include "level.h"
#include "log.h"
#include <QPixmap>
#include <QPainter>

Level Level::loadLevel(QString tilesImageFilepath, QString metatilesFilepath, QString mapFilepath, int tilesBaseAddress) {
    Tileset tileset = Tileset::buildTileset(tilesImageFilepath, metatilesFilepath, tilesBaseAddress);
    Map map = Map::loadMap(mapFilepath);
    return Level(tileset, map);
}

QPixmap Level::render(bool ignoreCache) {
    bool changedAny = false;
    int metatileWidth = this->map.getMetatileWidth();
    int metatileHeight = this->map.getMetatileHeight();
    if (this->mapImage.isNull()
            || this->mapImage.width() != metatileWidth * 16
            || this->mapImage.height() != metatileHeight * 16
    ) {
        this->mapImage = QImage(metatileWidth * 16, metatileHeight * 16, QImage::Format_RGBA8888);
        changedAny = true;
    }

    QPainter levelPainter(&this->mapImage);
    for (int j = 0; j < metatileHeight; j++) {
        for (int i = 0; i < metatileWidth; i++) {
            if (!ignoreCache && !this->map.metatileChanged(i, j)) {
                continue;
            }
            Tile *tile = this->map.getTile(i, j);
            if (tile) {
                changedAny = true;
                QImage metatileImage = this->tileset.getMetatileImage(tile->metatileId);
                QPoint origin = QPoint(i * 16, j * 16);
                levelPainter.drawImage(origin, metatileImage);
            }
        }
    }
    levelPainter.end();

    if (changedAny) {
        this->map.cacheMetatiles();
        this->mapPixmap = this->mapPixmap.fromImage(this->mapImage);
    }

    return this->mapPixmap;
}

void Level::save(QString mapFilepath) {
    this->map.save(mapFilepath);
}
