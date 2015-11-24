#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QRect>

#include "Constants.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTiles();
    parseMapFile();
    parseCoordinatesFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    if (tiles.count() < 1)
    {
        return;
    }
    QPainter painter(this);
    QPen pen(Qt::red, 2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    for (int i = 0; i < tiles.count(); ++i)
    {
        for (int j = 0; j < tiles.at(i).count(); ++j)
        {          
            QImage tile;
            switch (tiles.at(i).at(j))
            {
                case VERTICAL:
                    tile = image_VERTICAL;
                    break;
                case HORIZONTAL:
                    tile = image_HORIZONTAL;
                    break;
                case LEFT_TOP_CORNER:
                    tile = image_LEFT_TOP_CORNER;
                    break;
                case RIGHT_TOP_CORNER:
                    tile = image_RIGHT_TOP_CORNER;
                    break;
                case LEFT_BOTTOM_CORNER:
                    tile = image_LEFT_BOTTOM_CORNER;
                    break;
                case RIGHT_BOTTOM_CORNER:
                    tile = image_RIGHT_BOTTOM_CORNER;
                    break;
                case LEFT_HEADED_T:
                    tile = image_LEFT_HEADED_T;
                    break;
                case RIGHT_HEADED_T:
                    tile = image_RIGHT_HEADED_T;
                    break;
                case TOP_HEADED_T:
                    tile = image_TOP_HEADED_T;
                    break;
                case BOTTOM_HEADED_T:
                    tile = image_BOTTOM_HEADED_T;
                    break;
                case CROSSROADS:
                    tile = image_CROSSROADS;
                    break;
                default:
                    tile = image_EMPTY;
                    break;
            }
            painter.drawImage(i * TileSize, j * TileSize, tile);
        }
    }

    int size = tiles.count();
    if (size < tiles.at(0).count())
    {
        size = tiles.at(0).count();
    }
    int lenghtOfWindow = size * TileSize;
    QPoint leftTop = geometry().topLeft();
    setGeometry(QRect(leftTop, QSize(lenghtOfWindow, lenghtOfWindow)));

    painter.setFont(QFont("Arial", 15));
    painter.setBrush(Qt::black);
    for (int i = 0; i < waypoints.count(); ++i)
    {
        QRect rect(QPoint(waypoints.at(i).first.x() * TileSize, waypoints.at(i).first.y() * TileSize),
                   QSize(TileSize, TileSize));
        painter.drawText(rect, Qt::AlignCenter, waypoints.at(i).second);
    }

    for (int i = 0; i < coordinates.count(); ++i)
    {
        painter.drawPoint(coordinates.at(i));
    }
}

void MainWindow::loadTiles()
{
    image_VERTICAL.load(":/TilesImages/tiles/VERTICAL.png");
    image_HORIZONTAL.load(":/TilesImages/tiles/HORIZONTAL.png");
    image_LEFT_TOP_CORNER.load(":/TilesImages/tiles/LEFT_TOP_CORNER.png");
    image_RIGHT_TOP_CORNER.load(":/TilesImages/tiles/RIGHT_TOP_CORNER.png");
    image_LEFT_BOTTOM_CORNER.load(":/TilesImages/tiles/LEFT_BOTTOM_CORNER.png");
    image_RIGHT_BOTTOM_CORNER.load(":/TilesImages/tiles/RIGHT_BOTTOM_CORNER.png");
    image_LEFT_HEADED_T.load(":/TilesImages/tiles/LEFT_HEADED_T.png");
    image_RIGHT_HEADED_T.load(":/TilesImages/tiles/RIGHT_HEADED_T.png");
    image_TOP_HEADED_T.load(":/TilesImages/tiles/TOP_HEADED_T.png");
    image_BOTTOM_HEADED_T.load(":/TilesImages/tiles/BOTTOM_HEADED_T.png");
    image_CROSSROADS.load(":/TilesImages/tiles/CROSSROADS.png");
    image_EMPTY.load(":/TilesImages/tiles/EMPTY.png");
}

void MainWindow::parseMapFile()
{
    QFile mapFile(PathToMap);
    bool parseTiles = true;
    if (mapFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&mapFile);
        int numberOfTile = 0;
        while ( ! in.atEnd())
        {
            QString line(in.readLine(150));
            if (line == "***")
            {
                parseTiles = false;
                continue;
            }
            QStringList stringValues = line.split(" ");
            if (parseTiles)
            {
                QList<TileType> column;
                for (int i = 0; i < stringValues.count(); ++i)
                {
                    bool ok = false;
                    int tileType = stringValues.at(i).toInt(&ok);
                    if (ok)
                    {
                        column.push_back(static_cast<TileType>(tileType));
                    }
                }
                tiles.push_back(column);
            }
            else
            {                
                if (stringValues.count() != 2)
                {
                    continue;
                }
                QPoint point;
                point.setX(stringValues.at(0).toInt());
                point.setY(stringValues.at(1).toInt());
                bool found(false);
                for (int j = 0; j < waypoints.count(); ++j)
                {
                    if (waypoints.at(j).first == point)
                    {
                        QString newValue = waypoints.at(j).second + "_" + QString::number(numberOfTile);
                        waypoints.removeAt(j);
                        waypoints.push_back(qMakePair<QPoint, QString>(point, newValue));
                        found = true;
                        break;
                    }
                }
                if ( ! found)
                {
                    waypoints.push_back(qMakePair<QPoint, QString>(point, QString::number(numberOfTile)));
                }
                ++numberOfTile;
            }
        }
        mapFile.close();
    }
}

void MainWindow::parseCoordinatesFile()
{
    QFile coordinatesFile(PathToCoordinates);
    if (coordinatesFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&coordinatesFile);
        while ( ! in.atEnd())
        {
            QString line(in.readLine(50));
            QStringList stringValues = line.split(" ");
            if (stringValues.count() == 2)
            {
                QPair<double, double> pair;
                bool xOk(false);
                pair.first = stringValues.at(0).toDouble(&xOk);
                bool yOk(false);
                pair.second = stringValues.at(1).toDouble(&yOk);
                if (xOk && yOk)
                {
                    QPointF point(pair.first / 10.0, pair.second / 10.0);
                    coordinates.push_back(point);
                }
            }
        }
    }
}
