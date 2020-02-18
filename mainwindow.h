#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "metatileselector.h"
#include "metatileselectionpixmapitem.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void displayMetatileSelector(Tileset tileset);
    void displayMetatileSelection(Tileset tileset);
    Ui::MainWindow *ui;
    MetatileSelector *metatileSelector = nullptr;
    QGraphicsScene *metatileSelectorScene = nullptr;
    MetatileSelectionPixmapItem *metatileSelection = nullptr;
    QGraphicsScene *metatileSelectionScene = nullptr;
private slots:
    void onHoveredMetatileSelectionChanged(uchar metatileId);
    void onHoveredMetatileSelectionCleared();
    void onSelectedMetatilesChanged();
};

#endif // MAINWINDOW_H
