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
#include "dona.h"

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
    dona *donast;

    unsigned int bomberman_keys[4];
    void set_personaje_keys();
    void setup_personaje();
    void setup_enemigo1(int col);
    void setup_enemigo2(int col);
    std::vector<enemigo *> cocodrilos;
    void setup_scene();
    void generate_fondo();
    QTimer *time;
    std::vector<meteor*> active_meteors;
    void setup_meteor();
    void start_game();
    void setup_dona();

    void check_homero_vs_cocodrilos();
    void check_homero_vs_meteoros();
    void check_homero_vs_dona();
    void generate_nivel1();
    void generate_nivel2();


    bool object_right_movement(QGraphicsPixmapItem *item, unsigned int speed);
    bool object_left_movement(QGraphicsPixmapItem *item, unsigned int speed);
    bool object_up_movement(QGraphicsPixmapItem *item, unsigned int speed);
    bool object_down_movement(QGraphicsPixmapItem *item, unsigned int speed);
    int get_level_from_label();
    void update_level_in_label(int lives);
    int get_lives_from_label();
    void update_lives_in_label(int lives);
    int get_points_from_label();
    void update_point_in_label(int lives);
private slots:
    void update_game();
    void set_focus(QGraphicsPixmapItem *item, bool is_x_focus);

signals:
    void game_scene_changed();
};

#endif // REGLAS_JUEGO_H
