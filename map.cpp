#include "map.h"
#include "log.h"
#include <QFile>
#include <QMap>
#include <QDebug>

Map Map::loadMap(QString mapFilepath) {
    QFile mapFile(mapFilepath);
    if (mapFile.open(QIODevice::ReadOnly)) {
        QByteArray data = mapFile.readAll();
        int blockWidth  = ((static_cast<uchar>(data.at(1)) << 8) | static_cast<uchar>(data.at(0))) / 64;
        int blockHeight = (((static_cast<uchar>(data.at(3)) << 8) | static_cast<uchar>(data.at(2))) - 64 ) / 64;

        QList<int> blockMap;
        QMap<int, QList<uchar>> blockDefinitions;
        data.remove(0, 6);
        for (int i = 0; i < blockWidth * (blockHeight + 1); i++) {
            int addr = (static_cast<uchar>(data.at(i*2 + 1)) << 8) | static_cast<uchar>(data.at(i*2));
            blockMap.append(addr);
            if (!blockDefinitions.contains(addr)) {
                int blockOffset = addr - 0xc600 - 6;
                QList<uchar> blockMetatiles;
                for (int j = 0; j < 16; j++) {
                    blockMetatiles.append(static_cast<uchar>(data.at(blockOffset+j)));
                }
                blockDefinitions.insert(addr, blockMetatiles);
            }
        }

        int metatileWidth = blockWidth * 4;
        int metatileHeight = blockHeight * 4;
        QList<uchar> metatiles;
        for (int i = 0; i < metatileWidth * metatileHeight; i++) {
            metatiles.append(0);
        }

        for (int j = 0; j < blockHeight; j++) {
            for (int i = 0; i < blockWidth; i++) {
                int blockIndex = j * blockWidth + i;
                int blockAddr = blockMap.value(blockIndex);
                QList<uchar> blockDefinition = blockDefinitions.value(blockAddr);
                for (int k = 0; k < 4; k++) {
                    int metatileIndex = (j * metatileWidth * 4) + (i * 4) + k * metatileWidth;
                    metatiles[metatileIndex] = blockDefinition[k * 4];
                    metatiles[metatileIndex + 1] = blockDefinition[k * 4 + 1];
                    metatiles[metatileIndex + 2] = blockDefinition[k * 4 + 2];
                    metatiles[metatileIndex + 3] = blockDefinition[k * 4 + 3];
                }
            }
        }

        return Map(metatileWidth, metatileHeight, metatiles);
    } else {
        return Map();
    }
}

void Map::save(QString mapFilepath) {
    QByteArray data;

    // First, write the three header values.
    int pixelWidth = this->metatileWidth * 16;
    int pixelHeight = (this->metatileHeight + 4) * 16;
    int rowSize = pixelWidth / 32;
    data.append(static_cast<char>(pixelWidth & 0xff));
    data.append(static_cast<char>((pixelWidth >> 8) & 0xff));
    data.append(static_cast<char>(pixelHeight & 0xff));
    data.append(static_cast<char>((pixelHeight >> 8) & 0xff));
    data.append(static_cast<char>(rowSize & 0xff));
    data.append(static_cast<char>((rowSize >> 8) & 0xff));

    QList<QByteArray> blockDefinitions;
    QList<int> blocks;
    this->getBlocks(&blockDefinitions, &blocks);

    // Write the block addresses.
    int baseAddress = 0xc606 + (2 * blocks.size());
    int padding = 0x10 - (baseAddress % 0x10);
    baseAddress += padding;
    for (int i = 0; i < blocks.size(); i++) {
        int blockId = blocks[i];
        int blockAddress = baseAddress + (blockId * 0x10);
        data.append(static_cast<char>(blockAddress & 0xff));
        data.append(static_cast<char>((blockAddress >> 8) & 0xff));
    }
    for (int i = 0; i < padding; i++) {
        data.append(char(0));
    }

    // Write the block definitions.
    for (QByteArray blockDefinition : blockDefinitions) {
        for (int i = 0; i < 16; i++) {
            data.append(blockDefinition[i]);
        }
    }

    QFile file(mapFilepath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(data);
    } else {
        logError(QString("Failed to open map file for writing: '%1'").arg(mapFilepath));
    }
}

void Map::getBlocks(QList<QByteArray> *blockDefinitions, QList<int> *blocks) {
    QMap<QByteArray, int> blockMap;
    int blockWidth = this->metatileWidth / 4;
    int blockHeight = this->metatileHeight / 4;
    for (int j = 0; j < blockHeight; j++) {
        for (int i = 0; i < blockWidth; i++) {
            QByteArray blockDefinition;
            for (int k = 0; k < 4; k++) {
                int index = (j * this->metatileWidth * 4) + (i * 4) + k * this->metatileWidth;
                blockDefinition.append(static_cast<char>(this->tiles[index]->metatileId));
                blockDefinition.append(static_cast<char>(this->tiles[index + 1]->metatileId));
                blockDefinition.append(static_cast<char>(this->tiles[index + 2]->metatileId));
                blockDefinition.append(static_cast<char>(this->tiles[index + 3]->metatileId));
            }
            if (!blockMap.contains(blockDefinition)) {
                blockMap.insert(blockDefinition, blockMap.size());
                blockDefinitions->append(blockDefinition);
            }
            blocks->append(blockMap[blockDefinition]);
        }
    }
}

Tile *Map::getTile(int x, int y) {
    if (!this->isInBounds(x, y)) {
        return nullptr;
    }
    int index = y * this->metatileWidth + x;
    return this->tiles[index];
}

void Map::setMetatileId(int x, int y, uchar metatileId) {
    if (!this->isInBounds(x, y)) {
        logError(QString("Invalid map coordinates (%1, %2). Map dimensions are %3x%4").arg(x).arg(y).arg(this->metatileWidth).arg(this->metatileHeight));
        return;
    }
    int index = y * this->metatileWidth + x;
    this->tiles[index]->metatileId = metatileId;
}

bool Map::isInBounds(int x, int y) {
    return x >= 0 && x < this->metatileWidth && y >= 0 && y < this->metatileHeight;
}

void Map::cacheMetatiles() {
    this->cachedMetatiles.clear();
    for (Tile *tile : this->tiles) {
        this->cachedMetatiles.append(tile->metatileId);
    }
}

bool Map::metatileChanged(int x, int y) {
    int index = y * this->metatileWidth + x;
    return this->tiles[index]->metatileId != this->cachedMetatiles[index];
}
