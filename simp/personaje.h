#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>
#include "sprite.h"

#define homero_pixel_x_size 70
#define homero_pixel_y_size 70
#define homero_speed 1.5

class personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    personaje(unsigned int scale);
    ~personaje();

    void actualizarMovimiento(); // Método para actualizar el movimiento del personaje

private:
    QRect set_complete_sprites();
    void set_animations();
    sprite *pixmap_management;

    // Variables de física
    float posX, posY;         // Posición en el eje X e Y
    float velX, velY;         // Velocidad en el eje X e Y
    float accX, accY;         // Aceleración en el eje X e Y
    float gravedad;           // Aceleración debida a la gravedad
    float coefFriccion;       // Coeficiente de fricción del aire

    void aplicarFuerzas();    // Método para calcular fuerzas como la gravedad y fricción
};

#endif // PERSONAJE_H
