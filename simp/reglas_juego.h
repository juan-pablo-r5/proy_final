#ifndef REGLAS_JUEGO_H
#define REGLAS_JUEGO_H


#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <cstdlib>
#include <ctime>
#include <QObject>
#include <QTimer>

#include "ecenario.h"
#include "personaje.h"
#include "enemigo.h"

#define bomberman_pixel_x_size 30
#define bomberman_pixel_y_size 30
#define game_scale_factor 3
#define game_map_size_col 30
#define game_map_size_fil 15
#define game_map_rows 12
#define game_map_col 36
class reglas_juego : public QObject
{
    Q_OBJECT
public:
    reglas_juego(QGraphicsView *graph, QVector<QLabel *> game_labels);
    ~reglas_juego();
    void key_event(QKeyEvent *event);
private:
    QGraphicsView *graph;
    QVector<QLabel *> labels;
    QGraphicsScene *scene;
    ecenario *ene;
    personaje *homero;
    enemigo *cocodrilo;

    unsigned int bomberman_keys[4];
    void set_personaje_keys();
    void setup_scene();
    void generate_map();
//private slots:
    //void set_focus(QGraphicsPixmapItem *item, bool is_x_focus, bool is_y_focus);

signals:
    void game_scene_changed();
};

#endif // REGLAS_JUEGO_H
