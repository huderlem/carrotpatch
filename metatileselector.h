#ifndef METATILESELECTOR_H
#define METATILESELECTOR_H

#include <QPair>
#include "selectablepixmapitem.h"
#include "tileset.h"

class MetatileSelector: public SelectablePixmapItem {
    Q_OBJECT
public:
    MetatileSelector(int numMetatilesWide, Tileset tileset): SelectablePixmapItem(16, 16) {
        this->externalSelection = false;
        this->numMetatilesWide = numMetatilesWide;
        this->tileset = tileset;
        setAcceptHoverEvents(true);
    }
    QPoint getSelectionDimensions();
    void draw();
    void select(uchar metatile);
    void selectFromMap(uchar metatileId);
    QList<uchar> getSelectedMetatiles();
    void setExternalSelection(int, int, QList<uchar>);
    QPoint getMetatileIdCoordsOnWidget(uchar);
    void setTileset(Tileset tileset);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void hoverMoveEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
private:
    bool externalSelection;
    int numMetatilesWide;
    Tileset tileset;
    QList<uchar> selectedMetatiles;
    int externalSelectionWidth;
    int externalSelectionHeight;
    QList<uchar> externalSelectedMetatiles;

    void updateSelectedMetatiles();
    uchar getMetatileId(int x, int y);
    QPoint getMetatileIdCoords(uchar);

signals:
    void hoveredMetatileSelectionChanged(uchar);
    void hoveredMetatileSelectionCleared();
    void selectedMetatilesChanged();
};

#endif // METATILESELECTOR_H
