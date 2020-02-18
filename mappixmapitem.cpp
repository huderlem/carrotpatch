#include "mappixmapitem.h"
#include "log.h"

#define SWAP(a, b) do { if (a != b) { a ^= b; b ^= a; a ^= b; } } while (0)

void MapPixmapItem::paint(QGraphicsSceneMouseEvent *event) {
    if (this->level) {
        if (event->type() == QEvent::GraphicsSceneMouseRelease) {
            // map->commit();
        } else {
            QPointF pos = event->pos();
            int x = static_cast<int>(pos.x()) / 16;
            int y = static_cast<int>(pos.y()) / 16;
            paintNormal(x, y);
        }
        draw();
    }
}

void MapPixmapItem::paintNormal(int x, int y) {
    QPoint selectionDimensions = this->metatileSelector->getSelectionDimensions();
    QList<uchar> selectedMetatiles = this->metatileSelector->getSelectedMetatiles();

    // Snap the selected position to the top-left of the block boundary.
    // This allows painting via dragging the mouse to tile the painted region.
    int xDiff = x - this->paint_tile_initial_x;
    int yDiff = y - this->paint_tile_initial_y;
    if (xDiff < 0 && xDiff % selectionDimensions.x() != 0) xDiff -= selectionDimensions.x();
    if (yDiff < 0 && yDiff % selectionDimensions.y() != 0) yDiff -= selectionDimensions.y();

    x = this->paint_tile_initial_x + (xDiff / selectionDimensions.x()) * selectionDimensions.x();
    y = this->paint_tile_initial_y + (yDiff / selectionDimensions.y()) * selectionDimensions.y();
    for (int i = 0; i < selectionDimensions.x() && i + x < this->level->map.getMetatileWidth(); i++) {
        for (int j = 0; j < selectionDimensions.y() && j + y < this->level->map.getMetatileHeight(); j++) {
            int actualX = i + x;
            int actualY = j + y;
            int index = j * selectionDimensions.x() + i;
            this->level->map.setMetatileId(actualX, actualY, selectedMetatiles[index]);
        }
    }
}

void MapPixmapItem::updateMetatileSelection(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->pos();
    int x = static_cast<int>(pos.x()) / 16;
    int y = static_cast<int>(pos.y()) / 16;

    // Snap point to within map bounds.
    if (x < 0) x = 0;
    if (x >= this->level->map.getMetatileWidth()) x = this->level->map.getMetatileWidth() - 1;
    if (y < 0) y = 0;
    if (y >= this->level->map.getMetatileHeight()) y = this->level->map.getMetatileHeight() - 1;

    // Update/apply copied metatiles.
    if (event->type() == QEvent::GraphicsSceneMousePress) {
        this->selectionOrigin = QPoint(x, y);
        this->selection.clear();
        this->selection.append(QPoint(x, y));
        Tile *tile = this->level->map.getTile(x, y);
        if (tile) {
            this->metatileSelector->selectFromMap(tile->metatileId);
        }
    } else if (event->type() == QEvent::GraphicsSceneMouseMove) {
        int x1 = this->selectionOrigin.x();
        int y1 = this->selectionOrigin.y();
        int x2 = x;
        int y2 = y;
        if (x1 > x2) SWAP(x1, x2);
        if (y1 > y2) SWAP(y1, y2);
        this->selection.clear();
        for (int y = y1; y <= y2; y++) {
            for (int x = x1; x <= x2; x++) {
                this->selection.append(QPoint(x, y));
            }
        }

        QList<uchar> metatiles;
        for (QPoint point : this->selection) {
            int x = point.x();
            int y = point.y();
            Tile *tile = this->level->map.getTile(x, y);
            if (tile) {
                metatiles.append(tile->metatileId);
            }
        }

        this->metatileSelector->setExternalSelection(x2 - x1 + 1, y2 - y1 + 1, metatiles);
    }
}

void MapPixmapItem::floodFill(QGraphicsSceneMouseEvent *event) {
    if (this->level) {
        if (event->type() == QEvent::GraphicsSceneMouseRelease) {
            // map->commit();
        } else {
            QPointF pos = event->pos();
            int x = static_cast<int>(pos.x()) / 16;
            int y = static_cast<int>(pos.y()) / 16;
            Tile *tile = this->level->map.getTile(x, y);
            QList<uchar> selectedMetatiles = this->metatileSelector->getSelectedMetatiles();
            uchar firstMetatileId = selectedMetatiles.first();
            if (selectedMetatiles.size() > 1 || (tile && tile->metatileId != firstMetatileId)) {
               this->_floodFill(x, y);
            }
        }
        draw();
    }
}

void MapPixmapItem::magicFill(QGraphicsSceneMouseEvent *event) {
    if (this->level) {
        if (event->type() == QEvent::GraphicsSceneMouseRelease) {
            // map->commit();
        } else {
            QPointF pos = event->pos();
            int initialX = static_cast<int>(pos.x()) / 16;
            int initialY = static_cast<int>(pos.y()) / 16;
            Tile *tile = this->level->map.getTile(initialX, initialY);
            if (tile) {
                uchar originalMetatileId = tile->metatileId;
                QList<uchar> selectedMetatiles = this->metatileSelector->getSelectedMetatiles();
                QPoint selectionDimensions = this->metatileSelector->getSelectionDimensions();
                for (int y = 0; y < this->level->map.getMetatileHeight(); y++) {
                    for (int x = 0; x < this->level->map.getMetatileWidth(); x++) {
                        tile = this->level->map.getTile(x, y);
                        if (tile && tile->metatileId == originalMetatileId) {
                            int xDiff = x - initialX;
                            int yDiff = y - initialY;
                            int i = xDiff % selectionDimensions.x();
                            int j = yDiff % selectionDimensions.y();
                            if (i < 0) i = selectionDimensions.x() + i;
                            if (j < 0) j = selectionDimensions.y() + j;
                            int index = j * selectionDimensions.x() + i;
                            this->level->map.setMetatileId(x, y, selectedMetatiles[index]);
                        }
                    }
                }
            }
        }
        draw();
    }
}

void MapPixmapItem::_floodFill(int initialX, int initialY) {
//    QPoint selectionDimensions = this->metatileSelector->getSelectionDimensions();
//    QList<uchar> selectedMetatiles = this->metatileSelector->getSelectedMetatiles();
//    QList<QPair<uint16_t, uint16_t>> *selectedCollisions = this->metatileSelector->getSelectedCollisions();
//    bool setCollisions = selectedCollisions && selectedCollisions->length() == selectedMetatiles->length();

//    int numMetatiles = map->getWidth() * map->getHeight();
//    bool *visited = new bool[numMetatiles];
//    for (int i = 0; i < numMetatiles; i++)
//        visited[i] = false;

//    QList<QPoint> todo;
//    todo.append(QPoint(initialX, initialY));
//    while (todo.length()) {
//        QPoint point = todo.takeAt(0);
//        int x = point.x();
//        int y = point.y();
//        visited[x + y * map->getWidth()] = true;

//        Block *block = map->getBlock(x, y);
//        if (!block) {
//            continue;
//        }

//        int xDiff = x - initialX;
//        int yDiff = y - initialY;
//        int i = xDiff % selectionDimensions.x();
//        int j = yDiff % selectionDimensions.y();
//        if (i < 0) i = selectionDimensions.x() + i;
//        if (j < 0) j = selectionDimensions.y() + j;
//        int index = j * selectionDimensions.x() + i;
//        uint16_t tile = selectedMetatiles->at(index);
//        uint16_t old_tile = block->tile;
//        if (selectedMetatiles->count() != 1 || old_tile != tile) {
//            block->tile = tile;
//            if (setCollisions) {
//                block->collision = selectedCollisions->at(index).first;
//                block->elevation = selectedCollisions->at(index).second;
//            }
//            map->_setBlock(x, y, *block);
//        }
//        if (!visited[x + 1 + y * map->getWidth()] && (block = map->getBlock(x + 1, y)) && block->tile == old_tile) {
//            todo.append(QPoint(x + 1, y));
//            visited[x + 1 + y * map->getWidth()] = true;
//        }
//        if (!visited[x - 1 + y * map->getWidth()] && (block = map->getBlock(x - 1, y)) && block->tile == old_tile) {
//            todo.append(QPoint(x - 1, y));
//            visited[x - 1 + y * map->getWidth()] = true;
//        }
//        if (!visited[x + (y + 1) * map->getWidth()] && (block = map->getBlock(x, y + 1)) && block->tile == old_tile) {
//            todo.append(QPoint(x, y + 1));
//            visited[x + (y + 1) * map->getWidth()] = true;
//        }
//        if (!visited[x + (y - 1) * map->getWidth()] && (block = map->getBlock(x, y - 1)) && block->tile == old_tile) {
//            todo.append(QPoint(x, y - 1));
//            visited[x + (y - 1) * map->getWidth()] = true;
//        }
//    }

//    delete[] visited;
}

void MapPixmapItem::pick(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->pos();
    int x = static_cast<int>(pos.x()) / 16;
    int y = static_cast<int>(pos.y()) / 16;
    Tile *tile = this->level->map.getTile(x, y);
    if (tile) {
        this->metatileSelector->selectFromMap(tile->metatileId);
    }
}

void MapPixmapItem::select(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->pos();
    int x = static_cast<int>(pos.x()) / 16;
    int y = static_cast<int>(pos.y()) / 16;
    if (event->type() == QEvent::GraphicsSceneMousePress) {
        this->selectionOrigin = QPoint(x, y);
        this->selection.clear();
    } else if (event->type() == QEvent::GraphicsSceneMouseMove) {
        if (event->buttons() & Qt::LeftButton) {
            this->selection.clear();
            this->selection.append(QPoint(x, y));
        }
    } else if (event->type() == QEvent::GraphicsSceneMouseRelease) {
        if (!this->selection.isEmpty()) {
            QPoint pos = selection.last();
            int x1 = this->selectionOrigin.x();
            int y1 = this->selectionOrigin.y();
            int x2 = pos.x();
            int y2 = pos.y();
            if (x1 > x2) SWAP(x1, x2);
            if (y1 > y2) SWAP(y1, y2);
            this->selection.clear();
            for (int y = y1; y <= y2; y++) {
                for (int x = x1; x <= x2; x++) {
                    this->selection.append(QPoint(x, y));
                }
            }
        }
    }
}

void MapPixmapItem::draw(bool ignoreCache) {
    if (this->level) {
        setPixmap(this->level->render(ignoreCache));
    }
}

void MapPixmapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    int x = static_cast<int>(event->pos().x()) / 16;
    int y = static_cast<int>(event->pos().y()) / 16;
    emit this->hoveredMapMetatileChanged(x, y);
}
void MapPixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    emit this->hoveredMapMetatileCleared();
}
void MapPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->pos();
    int x = static_cast<int>(pos.x()) / 16;
    int y = static_cast<int>(pos.y()) / 16;
    this->paint_tile_initial_x = x;
    this->paint_tile_initial_y = y;
    emit startPaint(event, this);
    emit mouseEvent(event, this);
}
void MapPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    int x = static_cast<int>(event->pos().x()) / 16;
    int y = static_cast<int>(event->pos().y()) / 16;
    emit this->hoveredMapMetatileChanged(x, y);
    emit mouseEvent(event, this);
}
void MapPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    emit endPaint(event, this);
    emit mouseEvent(event, this);
}
