#include "metatileselector.h"
#include <QPainter>

QPoint MetatileSelector::getSelectionDimensions() {
    if (this->externalSelection) {
        return QPoint(this->externalSelectionWidth, this->externalSelectionHeight);
    } else {
        return SelectablePixmapItem::getSelectionDimensions();
    }
}

void MetatileSelector::draw() {
    int length = this->tileset.metatiles.length();
    int height = length / this->numMetatilesWide;
    if (length % this->numMetatilesWide != 0) {
        height++;
    }
    QImage image(this->numMetatilesWide * 16, height * 16, QImage::Format_RGBA8888);
    QPainter painter(&image);
    for (int metatileId = 0; metatileId < length; metatileId++) {
        int x = metatileId % this->numMetatilesWide;
        int y = metatileId / this->numMetatilesWide;
        QImage metatileImage = this->tileset.getMetatileImage(metatileId);
        painter.drawImage(QPoint(x * 16, y * 16), metatileImage );
    }
    painter.end();

    this->setPixmap(QPixmap::fromImage(image));
    if (!this->externalSelection) {
        this->drawSelection();
    }
}

void MetatileSelector::select(uchar metatileId) {
    this->externalSelection = false;
    QPoint coords = this->getMetatileIdCoords(metatileId);
    SelectablePixmapItem::select(coords.x(), coords.y(), 0, 0);
    this->updateSelectedMetatiles();
    emit selectedMetatilesChanged();
}

void MetatileSelector::selectFromMap(uchar metatileId) {
    this->select(metatileId);
}

void MetatileSelector::setTileset(Tileset tileset) {
    this->tileset = tileset;
    this->draw();
}

QList<uchar> MetatileSelector::getSelectedMetatiles() {
    if (this->externalSelection) {
        return this->externalSelectedMetatiles;
    } else {
        return this->selectedMetatiles;
    }
}

void MetatileSelector::setExternalSelection(int width, int height, QList<uchar> metatiles) {
    this->externalSelection = true;
    this->externalSelectionWidth = width;
    this->externalSelectionHeight = height;
    this->externalSelectedMetatiles.clear();
    for (int i = 0; i < metatiles.length(); i++) {
        this->externalSelectedMetatiles.append(metatiles.at(i));
    }

    this->draw();
    emit selectedMetatilesChanged();
}

void MetatileSelector::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    SelectablePixmapItem::mousePressEvent(event);
    this->updateSelectedMetatiles();
    emit selectedMetatilesChanged();
}

void MetatileSelector::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    SelectablePixmapItem::mouseMoveEvent(event);
    this->updateSelectedMetatiles();

    QPoint pos = this->getCellPos(event->pos());
    uchar metatileId = this->getMetatileId(pos.x(), pos.y());
    emit this->hoveredMetatileSelectionChanged(metatileId);
    emit selectedMetatilesChanged();
}

void MetatileSelector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    SelectablePixmapItem::mouseReleaseEvent(event);
    this->updateSelectedMetatiles();
    emit selectedMetatilesChanged();
}

void MetatileSelector::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    QPoint pos = this->getCellPos(event->pos());
    uchar metatileId = this->getMetatileId(pos.x(), pos.y());
    emit this->hoveredMetatileSelectionChanged(metatileId);
}

void MetatileSelector::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
    emit this->hoveredMetatileSelectionCleared();
}

void MetatileSelector::updateSelectedMetatiles() {
    this->externalSelection = false;
    this->selectedMetatiles.clear();
    QPoint origin = this->getSelectionStart();
    QPoint dimensions = this->getSelectionDimensions();
    for (int j = 0; j < dimensions.y(); j++) {
        for (int i = 0; i < dimensions.x(); i++) {
            uchar metatileId = this->getMetatileId(origin.x() + i, origin.y() + j);
            this->selectedMetatiles.append(metatileId);
        }
    }
}

uchar MetatileSelector::getMetatileId(int x, int y) {
    int index = y * this->numMetatilesWide + x;
    return static_cast<uchar>(index);
}

QPoint MetatileSelector::getMetatileIdCoords(uchar metatileId) {
    return QPoint(metatileId % this->numMetatilesWide, metatileId / this->numMetatilesWide);
}

QPoint MetatileSelector::getMetatileIdCoordsOnWidget(uchar metatileId) {
    QPoint pos = getMetatileIdCoords(metatileId);
    pos.rx() = (pos.x() * this->cellWidth) + (this->cellWidth / 2);
    pos.ry() = (pos.y() * this->cellHeight) + (this->cellHeight / 2);
    return pos;
}
