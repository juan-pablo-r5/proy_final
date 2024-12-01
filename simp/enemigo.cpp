#include "enemigo.h"

enemigo::enemigo(unsigned int scale,Movimiento tipo_movimiento) : moving_right(true),tipo_movimiento(tipo_movimiento),
    velocidad_x(0), velocidad_y(0)

{
    pixmap_management = new sprite(":/caiman completo.jpeg", scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(cocodrilo_pixel_x_size, cocodrilo_pixel_y_size);

    set_animations();

    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0));

}

enemigo::~enemigo()
{
    delete pixmap_management;  
}

QRect enemigo::set_complete_sprites()
{
    QRect dim;
    dim.setX(0);
    dim.setY(0);
    dim.setHeight(2 * cocodrilo_pixel_y_size);
    dim.setWidth(16 * cocodrilo_pixel_x_size);
    return dim;
}

void enemigo::set_animations()
{
    animation_right();
    animation_left();
}

void enemigo::animation_right()
{
    QRect dim;
    dim.setX(0);
    dim.setY(8 * cocodrilo_pixel_y_size);
    dim.setHeight(1 * cocodrilo_pixel_y_size);
    dim.setWidth(7 * cocodrilo_pixel_x_size);
    pixmap_management->add_new_animation(dim, 7);
}

void enemigo::animation_left()
{
    QRect dim;
    dim.setX(8* cocodrilo_pixel_x_size);
    dim.setY(0);
    dim.setHeight(1 * cocodrilo_pixel_y_size);
    dim.setWidth(8 * cocodrilo_pixel_x_size);
    pixmap_management->add_new_animation(dim, 8);
}



void enemigo::move(bool can_move)
{
    if (tipo_movimiento == BASE)
    {
        if (can_move)
        {
            if (moving_right)
            {
                setX(x() + cocodrilo_speed);
                setPixmap(pixmap_management->get_current_pixmap(0));
            }
            else
            {
                setX(x() - cocodrilo_speed);
                setPixmap(pixmap_management->get_current_pixmap(1));
            }
        }
        else
        {
            moving_right = !moving_right;
        }
    }
}

void enemigo::move_towards_target(QGraphicsPixmapItem *target)
{
    if (tipo_movimiento == ATRACCION && target)
    {
        float current_x = x();
        float current_y = y();

        float target_x = target->x();
        float target_y = target->y();

        float dx = target_x - current_x;
        float dy = target_y - current_y;

        // Calcular la fuerza de atracción (aceleración)
        float distancia = sqrt(dx * dx + dy * dy);
        if (distancia > 1) // Evitar divisiones por 0
        {
            float ax = fuerza_atraccion * (dx / distancia);
            float ay = fuerza_atraccion * (dy / distancia);

            velocidad_x += ax;
            velocidad_y += ay;

            velocidad_x *= 0.98;
            velocidad_y *= 0.98;

            //nuevas posiciones
            float new_x = current_x + velocidad_x;
            float new_y = current_y + velocidad_y;
            setX(new_x);
            setY(new_y);

            if (velocidad_x > 0)
            {
                setPixmap(pixmap_management->get_current_pixmap(0));
            }
            else if (velocidad_x < 0)
            {
                setPixmap(pixmap_management->get_current_pixmap(1));
            }
        }
    }
}
