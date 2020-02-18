#include "metatileselectionpixmapitem.h"
#include <QPainter>

void MetatileSelectionPixmapItem::draw() {
    QList<uchar> selectedMetatiles = this->metatileSelector->getSelectedMetatiles();
    QPoint selectionDimensions = this->metatileSelector->getSelectionDimensions();
    int width = selectionDimensions.x() * 16;
    int height = selectionDimensions.y() * 16;
    QImage image(width, height, QImage::Format_RGBA8888);
    QPainter painter(&image);
    for (int i = 0; i < selectionDimensions.x(); i++) {
        for (int j = 0; j < selectionDimensions.y(); j++) {
            int x = i * 16;
            int y = j * 16;
            int index = j * selectionDimensions.x() + i;
            QImage metatileImage = this->tileset.getMetatileImage(selectedMetatiles[index]);
            painter.drawImage(QPoint(x, y), metatileImage);
        }
    }
    painter.end();
    setPixmap(QPixmap::fromImage(image));
}
