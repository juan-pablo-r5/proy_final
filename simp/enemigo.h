#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>
#include "sprite.h"

#define cocodrilo_pixel_x_size 70
#define cocodrilo_pixel_y_size 70
#define cocodrilo_speed 1.5

class enemigo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    enemigo(unsigned int scale);
    ~enemigo();
    void resize_block(int new_width, int new_height);


private:
    QRect set_complete_sprites();
    void set_animations();
    void toggle_direction();

    sprite *pixmap_management;
    QTimer *movement_timer;
    bool moving_right;


private slots:
    void move();

};

#endif // ENEMIGO_H
