#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "sprite.h"

#define homero_pixel_x_size 47
#define homero_pixel_y_size 73
#define homero_speed 5.0

class personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    personaje(unsigned int scale, int x, int y);
    ~personaje();

    void set_keys(unsigned int *keys);
    void move(unsigned int key, bool is_valid);
    void actualizarMovimiento(bool puedeMoverse);


private:
    QRect set_complete_sprites();
    void set_animations();
    void animation_right();
    void animation_left();
    void animation_jump();

    float posX, posY;
    bool enElAire;
    float saltoAltura = 50;
    float saltoVelocidad = 10;
    float alturaSalto = 80;
    float progresoSalto = 0;


    sprite *pixmap_management;
     unsigned int keys[3];

signals:
    void is_moving(QGraphicsPixmapItem *, bool);
};

#endif // PERSONAJE_H
