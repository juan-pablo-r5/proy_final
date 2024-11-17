#include "personaje.h"

personaje::personaje(unsigned int scale) : posX(0), posY(0), velX(homero_speed), velY(0),
    accX(0), accY(0), gravedad(9.81), coefFriccion(0.1)
{
    pixmap_management = new sprite("qrc:/arcade homero.png", scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(homero_pixel_x_size, homero_pixel_y_size);

    set_animations();
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0 /*homero_pixel_x_size, homero_pixel_y_size*/));
}

personaje::~personaje()
{
    delete pixmap_management;
}

QRect personaje::set_complete_sprites()
{
    QRect dim;
    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1 * homero_pixel_y_size);
    dim.setWidth(1 * homero_pixel_x_size);
    return dim;
}

void personaje::set_animations()
{
    QRect dim;
    dim.setX(0);
    dim.setY(4);
    dim.setHeight(1 * homero_pixel_y_size);
    dim.setWidth(7 * homero_pixel_x_size);
    pixmap_management->add_new_animation(dim, 4);

}

void personaje::aplicarFuerzas()
{
    // Aceleración debida a la gravedad
    accY = -gravedad;

    // Fuerza de fricción (proporcional a la velocidad)
    float friccionX = -coefFriccion * velX;
    float friccionY = -coefFriccion * velY;

    // Aceleraciones totales incluyendo fricción
    accX = friccionX;
    accY += friccionY;
}

void personaje::actualizarMovimiento()
{
    // Aplicar fuerzas para actualizar aceleración
    aplicarFuerzas();

    // Actualizar velocidad con la aceleración
    velX += accX;
    velY += accY;

    // Actualizar posición con la velocidad
    posX += velX;
    posY += velY;

    // Ajuste de la posición del gráfico en pantalla
    setPos(posX, posY);

    // Si el personaje llega al "suelo" (posición y = 0), invertir la velocidad en Y para simular rebote
    if (posY < 0) {
        posY = 0;
        velY *= -0.5; // La velocidad se reduce al rebotar
    }
}
