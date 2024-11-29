#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>
#include "sprite.h"

#define cocodrilo_pixel_x_size 24
#define cocodrilo_pixel_y_size 11
#define cocodrilo_speed 0.5

class enemigo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    enemigo(unsigned int scale);
    ~enemigo();

    void toggle_direction(); // Cambia la dirección del enemigo

private slots:
    void move(); // Controla el movimiento periódico del enemigo

private:
    sprite* pixmap_management;    // Clase para manejar los sprites
    QTimer* movement_timer;       // Timer para el movimiento automático
    bool moving_right;            // Determina si el enemigo se mueve a la derecha
    unsigned int current_animation_index; // Índice de la animación actual

    QRect set_complete_sprites(); // Configura el área completa de sprites
    void set_animations();        // Configura las animaciones
    void animation_right();       // Animación hacia la derecha
    void animation_left();        // Animación hacia la izquierda

};

#endif // ENEMIGO_H
