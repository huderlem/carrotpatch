#ifndef MAPPIXMAPITEM_H
#define MAPPIXMAPITEM_H

#include "level.h"
#include "metatileselector.h"
#include <QGraphicsPixmapItem>

class MapPixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

private:
    using QGraphicsPixmapItem::paint;

public:
    MapPixmapItem(Level *level, MetatileSelector *metatileSelector) {
        this->level = level;
        this->metatileSelector = metatileSelector;
        this->paintingEnabled = true;
        setAcceptHoverEvents(true);
    }
    bool paintingEnabled;
    Level *level;
    MetatileSelector *metatileSelector;
    bool active;
    bool right_click;
    int paint_tile_initial_x;
    int paint_tile_initial_y;
    QPoint selectionOrigin;
    QList<QPoint> selection;
    virtual void paint(QGraphicsSceneMouseEvent*);
    virtual void floodFill(QGraphicsSceneMouseEvent*);
    virtual void magicFill(QGraphicsSceneMouseEvent*);
    void _floodFill(int x, int y);
    virtual void pick(QGraphicsSceneMouseEvent*);
    virtual void select(QGraphicsSceneMouseEvent*);
    virtual void draw(bool ignoreCache = false);
    void updateMetatileSelection(QGraphicsSceneMouseEvent *event);

private:
    void paintNormal(int x, int y);

signals:
    void startPaint(QGraphicsSceneMouseEvent *, MapPixmapItem *);
    void endPaint(QGraphicsSceneMouseEvent *, MapPixmapItem *);
    void mouseEvent(QGraphicsSceneMouseEvent *, MapPixmapItem *);
    void hoveredMapMetatileChanged(int x, int y);
    void hoveredMapMetatileCleared();

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
};

#endif // MAPPIXMAPITEM_H
