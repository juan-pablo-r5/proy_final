#ifndef ECENARIO_H
#define ECENARIO_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprite.h"

#define blocks_pixel_x_size 74
#define blocks_pixel_y_size 32

class ecenario: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ecenario(unsigned int scale, unsigned int type);
    ~ecenario();
    unsigned int get_type();

private:
    sprite *pixmap;
    unsigned int scale, type;
    QRect set_complete_sprites();
    QRect set_borde();
    QRect set_fondo();
    void set_type_block();
};


#endif // ECENARIO_H
