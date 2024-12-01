#include "personaje.h"

personaje::personaje(unsigned int scale, int x, int y): progresoSalto(0)

{
    pixmap_management = new sprite(":/homero prueba.jpeg", scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(homero_pixel_x_size, homero_pixel_y_size);


    set_animations();
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmaps(0, homero_pixel_x_size, homero_pixel_y_size));
    posX=x;
    posY=y;
    setPos(posX,posY);

}

personaje::~personaje()
{
    delete pixmap_management;
}

void personaje::set_keys(unsigned int *keys)
{
    for (unsigned int i = 0; i < 4; i++) this->keys[i] = keys[i];
}

void personaje::move(unsigned int key, bool is_valid)
{
    if (key == keys[0]) {
        setPixmap(pixmap_management->get_current_pixmaps(0, homero_pixel_x_size, homero_pixel_y_size)); // Sprite izquierda
        if (is_valid)posX -= homero_speed;
        emit is_moving(this, true);

    }
    else if (key == keys[1]) {
        setPixmap(pixmap_management->get_current_pixmaps(1, homero_pixel_x_size, homero_pixel_y_size)); // Sprite derecha
        if (is_valid)posX += homero_speed;
        emit is_moving(this, true);
    }
    else if (key == keys[2]) {
        if (!enElAire) {
            enElAire = true;
            progresoSalto=0;
            setPixmap(pixmap_management->get_current_pixmaps(2, homero_pixel_x_size, homero_pixel_y_size));
            qDebug() << "salto";

        }
    }

    setPos(posX, posY);
}


void personaje::actualizarMovimiento(bool puedeMoverse)
{
    if (enElAire) {
        // Fase de subida
        if (progresoSalto < alturaSalto ) {
            qDebug() << "realidad salto";
            posY -= 5;
            progresoSalto += 5;
        }
        // Fase de bajada
        else if (progresoSalto >= alturaSalto) {
            posY += 5;
        }
        // Verificar si ha tocado el suelo
        if (!puedeMoverse && progresoSalto >= alturaSalto) {
            enElAire = false;
            progresoSalto = 0;
            setPixmap(pixmap_management->get_current_pixmaps(0,homero_pixel_x_size,homero_pixel_y_size));
        }
        setPos(posX, posY);
    }
}

QRect personaje::set_complete_sprites()
{
    QRect dim;
    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1 * homero_pixel_y_size);
    dim.setWidth(16 * homero_pixel_x_size);
    return dim;
}

void personaje::set_animations()
{
    animation_right();
    animation_left();
    animation_jump();
}

void personaje::animation_right()
{
    QRect dim;
    dim.setX(8 * homero_pixel_x_size);
    dim.setY(0);
    dim.setHeight(1 * homero_pixel_y_size);
    dim.setWidth(8 * homero_pixel_x_size);
    pixmap_management->add_new_animation(dim, 8);
}

void personaje::animation_left()
{
    QRect dim;
    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1 * homero_pixel_y_size);
    dim.setWidth(8 * homero_pixel_x_size);
    pixmap_management->add_new_animation(dim, 8);
}

void personaje::animation_jump()
{
    QRect dim;
    dim.setX(0);
    dim.setY(homero_pixel_y_size);
    dim.setHeight(1 * homero_pixel_y_size);
    dim.setWidth(1 * homero_pixel_x_size);
    pixmap_management->add_new_animation(dim, 1);
}
