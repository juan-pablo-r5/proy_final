#include "enemigo.h"

enemigo::enemigo(unsigned int scale)
    : moving_right(true), // Inicialmente se mueve a la derecha
    current_animation_index(0) // Por defecto, comienza con la animación de la derecha
{
    // Inicialización del sprite
    pixmap_management = new sprite(":/caiman completo.png", scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(cocodrilo_pixel_x_size, cocodrilo_pixel_y_size);

    // Configurar animaciones
    set_animations();

    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0)); // Inicialmente usa el primer cuadro

    // Configuración del temporizador
    movement_timer = new QTimer(this);
    connect(movement_timer, &QTimer::timeout, this, &enemigo::move);
    movement_timer->start(50); // Movimiento cada 30 ms

    // Establecer posición inicial
    setPos(150, 342); // Cambia estos valores por la posición inicial deseada
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
    dim.setHeight(2 * cocodrilo_pixel_y_size); // Dos filas de sprites
    dim.setWidth(16 * cocodrilo_pixel_x_size); // Ocho columnas de sprites
    return dim;
}

void enemigo::set_animations()
{
    animation_right(); // Configurar animación hacia la derecha
    animation_left();  // Configurar animación hacia la izquierda
}

void enemigo::animation_right()
{
    QRect dim;
    dim.setX(0);
    dim.setY(8 * cocodrilo_pixel_y_size); // Fila 1: Animación hacia la derecha
    dim.setHeight(1 * cocodrilo_pixel_y_size);
    dim.setWidth(7 * cocodrilo_pixel_x_size); // 7 cuadros
    pixmap_management->add_new_animation(dim, 7);
}

void enemigo::animation_left()
{
    QRect dim;
    dim.setX(8* cocodrilo_pixel_x_size);
    dim.setY(0); // Fila 0: Animación hacia la izquierda
    dim.setHeight(1 * cocodrilo_pixel_y_size);
    dim.setWidth(8 * cocodrilo_pixel_x_size); // 8 cuadros
    pixmap_management->add_new_animation(dim, 8);
}

void enemigo::toggle_direction()
{
    moving_right = !moving_right; // Cambiar la dirección

    // Cambiar el índice de animación según la dirección
    if (moving_right)
    {
        current_animation_index = 0; // Índice para la animación hacia la derecha
    }
    else
    {
        current_animation_index = 1; // Índice para la animación hacia la izquierda
    }
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

    // Actualizar el sprite actual
    setPixmap(pixmap_management->get_current_pixmap(current_animation_index));

    // Cambiar dirección cada 2 segundos
    static int elapsed_time = 0;
    elapsed_time += 30; // Incremento en milisegundos
    if (elapsed_time >= 2000) // 2 segundos
    {
        toggle_direction(); // Cambiar dirección
        elapsed_time = 0;   // Reiniciar el tiempo
    }
}
