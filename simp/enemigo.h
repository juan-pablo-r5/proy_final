#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>
#include "sprite.h"

#define cocodrilo_pixel_x_size 24
#define cocodrilo_pixel_y_size 11
#define cocodrilo_speed 4

enum Movimiento {
    BASE,
    ATRACCION
};

class enemigo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    enemigo(unsigned int scale, Movimiento tipo_movimiento);
    ~enemigo();
    bool moving_right;            // Determina si el enemigo se mueve
    Movimiento tipo_movimiento;  // Tipo de movimiento seleccionado
    void move(bool can_move);
    void move_towards_target(QGraphicsPixmapItem *target);
private:
    sprite* pixmap_management;
    QRect set_complete_sprites();
    void set_animations();
    void animation_right();
    void animation_left();

    float velocidad_x, velocidad_y; // Velocidades para movimiento por atracción
    const float fuerza_atraccion = 0.1; // Intensidad de la atracción
};

#endif // ENEMIGO_H
