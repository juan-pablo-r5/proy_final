#ifndef METEOR_H
#define METEOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprite.h"
#include <QTimer>

#define meteor_pixel_x_size 19
#define meteor_pixel_y_size 18

#define explo_pixel_x_size 190
#define explo_pixel_y_size 200

class meteor : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    meteor(unsigned int scale);
    ~meteor();
    void set_initial_conditions(float x, float y, float vy);
    float get_vy();
signals:
    void start_explosion();

public slots:
    void time_step(bool can_move);

private:
    QRect set_complete_sprites1();
    void set_animations();
    void set_down_animation();

    QRect set_complete_sprites2();
    void set_explo_animation1();
    void set_explo_animation2();
    // Atributos para manejar la simulacion de caida libre
    float x, y;
    float vy;
    const float acc = 9.8;
    QTimer *time;
    int time_period=100;     // (en ms)
    float y_dimension;   // Escala para la posición vertical
    sprite *pixmap_management;
    sprite *explosion_management;
    int attempt_count = 0;
    const int max_attempts = 5;

};


#endif // METEOR_H
