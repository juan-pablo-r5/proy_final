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
#include "meteor.h"

#define bomberman_pixel_x_size 16
#define bomberman_pixel_y_size 16
#define game_scale_factor 4
#define game_map_rows 8
#define game_map_col 30

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
    ecenario *blocks[game_map_rows][game_map_col];
    personaje *homero;
    enemigo *cocodrilo;
    meteor *meteori;

    unsigned int bomberman_keys[4];
    void set_personaje_keys();
    void setup_personaje();
    void setup_enemigo();
    void setup_scene();
    void generate_fondo();
    QTimer *time;
    std::vector<meteor*> active_meteors;
    void setup_meteor();
    void start_game();




    bool object_right_movement(QGraphicsPixmapItem *item, unsigned int speed);
    bool object_left_movement(QGraphicsPixmapItem *item, unsigned int speed);
    bool object_up_movement(QGraphicsPixmapItem *item, unsigned int speed);
    bool object_down_movement(QGraphicsPixmapItem *item, unsigned int speed);

private slots:
    void update_game();
    //void set_focus(QGraphicsPixmapItem *item, bool is_x_focus, bool is_y_focus);

signals:
    void game_scene_changed();
};

#endif // REGLAS_JUEGO_H
