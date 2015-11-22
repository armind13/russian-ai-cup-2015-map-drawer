#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QImage>

enum TileType
{
    _UNKNOWN_TILE_TYPE_ = -1,
    EMPTY = 0,
    VERTICAL = 1,
    HORIZONTAL = 2,
    LEFT_TOP_CORNER = 3,
    RIGHT_TOP_CORNER = 4,
    LEFT_BOTTOM_CORNER = 5,
    RIGHT_BOTTOM_CORNER = 6,
    LEFT_HEADED_T = 7,
    RIGHT_HEADED_T = 8,
    TOP_HEADED_T = 9,
    BOTTOM_HEADED_T = 10,
    CROSSROADS = 11,
    UNKNOWN = 12,
    _TILE_TYPE_COUNT_ = 13
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void paintEvent(QPaintEvent*);

private:
    Ui::MainWindow *ui;
    QList<QList<TileType> > tiles;
    QImage image_VERTICAL;
    QImage image_HORIZONTAL;
    QImage image_LEFT_TOP_CORNER;
    QImage image_RIGHT_TOP_CORNER;
    QImage image_LEFT_BOTTOM_CORNER;
    QImage image_RIGHT_BOTTOM_CORNER;
    QImage image_LEFT_HEADED_T;
    QImage image_RIGHT_HEADED_T;
    QImage image_TOP_HEADED_T;
    QImage image_BOTTOM_HEADED_T;
    QImage image_CROSSROADS;
    QImage image_EMPTY;
    QList<QPair<int, int> > waypoints;

    void loadTiles();
    void parseFile();
};

#endif // MAINWINDOW_H
