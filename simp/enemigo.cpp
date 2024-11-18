#include "enemigo.h"

enemigo::enemigo(unsigned int scale)
    : moving_right(true) // Inicialmente se mueve a la derecha
{
    pixmap_management = new sprite("qrc:/../../OneDrive/Imagens/caiman2.png", scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(cocodrilo_pixel_x_size, cocodrilo_pixel_y_size);

    set_animations();
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0));

    // Configuración del temporizador
    movement_timer = new QTimer(this);
    connect(movement_timer, &QTimer::timeout, this, &enemigo::move);
    movement_timer->start(30); // Movimiento cada 30 ms
}

enemigo::~enemigo()
{
    delete pixmap_management;
    delete movement_timer;
}

QRect enemigo::set_complete_sprites()
{
    QRect dim;
    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1 * cocodrilo_pixel_y_size);
    dim.setWidth(1 * cocodrilo_pixel_x_size);
    return dim;
}

void enemigo::set_animations()
{
    QRect dim;
    dim.setX(0);
    dim.setY(4);
    dim.setHeight(1 * cocodrilo_pixel_y_size);
    dim.setWidth(7 * cocodrilo_pixel_x_size);
    pixmap_management->add_new_animation(dim, 4);
}

void enemigo::toggle_direction()
{
    moving_right = !moving_right;
}

void enemigo::move()
{
    // Movimiento en una dirección
    if (moving_right)
    {
        setX(x() + cocodrilo_speed); // Mover a la derecha
    }
    else
    {
        setX(x() - cocodrilo_speed); // Mover a la izquierda
    }

    // Cambiar dirección cada 2 segundos
    static int elapsed_time = 0;
    elapsed_time += 30; // Incremento en milisegundos
    if (elapsed_time >= 2000) // 2 segundos
    {
        toggle_direction();
        elapsed_time = 0; // Reiniciar el tiempo
    }
}
