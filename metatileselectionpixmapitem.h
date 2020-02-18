#ifndef METATILESELECTIONPIXMAPITEM_H
#define METATILESELECTIONPIXMAPITEM_H

#include "metatileselector.h"
#include <QGraphicsPixmapItem>

class MetatileSelectionPixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    MetatileSelectionPixmapItem(Tileset tileset, MetatileSelector *metatileSelector) {
        this->tileset = tileset;
        this->metatileSelector = metatileSelector;
    }
    Tileset tileset;
    MetatileSelector *metatileSelector;
    void draw();
};

#endif // METATILESELECTIONPIXMAPITEM_H
