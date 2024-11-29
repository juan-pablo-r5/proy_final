#ifndef DONA_H
#define DONA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprite.h"
#include <cmath>
#include <QTimer>


#define dona_pixel_x_size 168
#define dona_pixel_y_size 158

class dona: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    dona(unsigned int scale);
    ~dona();
    void set_initial_conditions(float x, float y, float vx, float amplitude, float frequency);
    void start_motion();
    void stop_motion();

private:
    sprite *pixmap_management;
    QRect set_complete_sprites();
    void set_animations();
    float x, y;
    float vx, vy;
    float ax, ay;
    float amplitude;
    float frequency;
    float friction;
    float time_elapsed;  // Tiempo acumulado para el calculo de la posición
    QTimer *time;
    int time_period;     // Intervalo de tiempo (ms)
    int direction;
    int time_to_reverse;
    float initial_x;
    float initial_y;

private slots:
    void time_step();
};

#endif // DONA_H
