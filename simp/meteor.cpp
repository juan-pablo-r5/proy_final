#include "meteor.h"

meteor::meteor(unsigned int scale)
{
    pixmap_management = new sprite(":/asteroid.png",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites1());
    pixmap_management->set_design_size(meteor_pixel_x_size,meteor_pixel_y_size);

    explosion_management = new sprite(":/explotion.png", scale);
    explosion_management->cut_character_pixmap(set_complete_sprites2());
    explosion_management->set_design_size(explo_pixel_x_size,explo_pixel_y_size);

    //setPixmap();
    set_animations();
    setPixmap(pixmap_management->get_current_pixmap(0));
    y_dimension = 4; // Escala vertical
    this->vy = 0;    // Velocidad inicial en el eje Y
}

meteor::~meteor()
{
    delete pixmap_management;
    delete explosion_management;
}
float meteor::get_vy()
{
    return vy;
}

void meteor::set_initial_conditions(float x, float y, float vy)
{
    this->x = x;   // Posición inicial en X (fija)
    this->y = y;   // Posición inicial en Y
    this->vy = vy; // Velocidad inicial en Y
    setPos(x, y);  // Establece la posición gráfica inicial
}


void meteor::time_step(bool can_move)
{
    if (can_move)
    {
        // Actualiza la velocidad debido a la gravedad
        vy += acc * time_period / 1000.0;
        y += vy * time_period / 1000.0;
        setPos(x, y);
    }
    else
    {
        // Si no puede moverse, manejar intentos o explotar
        attempt_count++;
        if (attempt_count < max_attempts)
        {
            setPixmap(explosion_management->get_current_pixmaps(0,explo_pixel_x_size,explo_pixel_y_size));
            setPos(x, y);
        }
        else
        {
            emit start_explosion();
        }
    }
}



QRect meteor::set_complete_sprites1()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(6*meteor_pixel_y_size);
    dim.setWidth(3*meteor_pixel_x_size);

    return dim;
}

void meteor::set_animations()
{
    set_down_animation();
    set_explo_animation1();
}

void meteor::set_down_animation()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*meteor_pixel_y_size);
    dim.setWidth(1*meteor_pixel_x_size);

    pixmap_management->add_new_animation(dim,1);
}
QRect meteor::set_complete_sprites2()
{
    QRect dime;

    dime.setX(0);
    dime.setY(0);
    dime.setHeight(2*explo_pixel_y_size);
    dime.setWidth(5*explo_pixel_x_size);

    return dime;
}

void meteor::set_explo_animation1()
{
    QRect dime;

    dime.setX(0);
    dime.setY(0);
    dime.setHeight(1*explo_pixel_y_size);
    dime.setWidth(5*explo_pixel_x_size);


   explosion_management->add_new_animation(dime,5);
}



