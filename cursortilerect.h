#ifndef CURSORTILERECT_H
#define CURSORTILERECT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRgb>

class CursorTileRect : public QGraphicsItem
{
public:
    CursorTileRect(bool enabled, QRgb color);
    QRectF boundingRect() const override
    {
        int width = this->width;
        int height = this->height;
        if (this->singleTileMode) {
            width = 16;
            height = 16;
        } else if (!this->rightClickSelectionAnchored && this->smartPathMode && this->selectionHeight == 3 && this->selectionWidth == 3) {
            width = 32;
            height = 32;
        }
        qreal penWidth = 4;
        return QRectF(-penWidth,
                      -penWidth,
                      width + penWidth * 2,
                      height + penWidth * 2);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override
    {
        if (!this->enabled) return;
        int width = this->width;
        int height = this->height;
        if (this->singleTileMode) {
            width = 16;
            height = 16;
        } else if (this->smartPathInEffect()) {
            width = 32;
            height = 32;
        }

        painter->setPen(this->color);
        painter->drawRect(-1, -1, width + 2, height + 2);
        painter->setPen(QColor(0, 0, 0));
        painter->drawRect(-2, -2, width + 4, height + 4);
        painter->drawRect(0, 0, width, height);
    }
    void initAnchor(int coordX, int coordY);
    void stopAnchor();
    void initRightClickSelectionAnchor(int coordX, int coordY);
    void stopRightClickSelectionAnchor();
    void setSmartPathMode();
    bool getSmartPathMode() { return this->smartPathMode; }
    void setSingleTileMode();
    void stopSingleTileMode();
    void setNormalPathMode();
    void updateLocation(int x, int y);
    void updateSelectionSize(int width, int height);
    void setVisibility(bool visible);
    bool enabled;
private:
    bool visible;
    int width;
    int height;
    bool anchored;
    bool rightClickSelectionAnchored;
    bool smartPathMode;
    bool singleTileMode;
    int anchorCoordX;
    int anchorCoordY;
    int selectionWidth;
    int selectionHeight;
    QRgb color;
    bool smartPathInEffect();
};


#endif // CURSORTILERECT_H
