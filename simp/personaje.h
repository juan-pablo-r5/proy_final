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
    personaje(unsigned int scale);
    ~personaje();

    void set_keys(unsigned int *keys);
    void move(unsigned int key, bool is_valid);
    void setScaleFactor(float factor);

private:
    QRect set_complete_sprites();
    void set_animations();
    void animation_right();
    void animation_left();
    void animation_jump(); // Nueva animación para el salto

    // Métodos para la física
    void aplicarFuerzas();
    void actualizarMovimiento();

    // Variables para la física
    float posX, posY;         // Posición del personaje
    float velX, velY;         // Velocidades
    float accX, accY;         // Aceleraciones
    float gravedad;           // Constante de gravedad
    float fuerzaSalto;        // Velocidad inicial del salto
    bool enElAire;            // Bandera para indicar si está saltando

    // Gestión del pixmap y animaciones
    sprite *pixmap_management;
    unsigned int keys[4];     // Teclas de movimiento
    float escala;             // Factor de escala
};

#endif // PERSONAJE_H
