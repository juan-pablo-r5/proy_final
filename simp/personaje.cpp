#include "personaje.h"

personaje::personaje(unsigned int scale)
    : posX(0), posY(300), velX(0), velY(0), accX(0), accY(0),
    gravedad(0.5), enElAire(false), fuerzaSalto(-10.0), escala(scale)
{
    pixmap_management = new sprite(":/homero prueba.png", scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(homero_pixel_x_size, homero_pixel_y_size);

    set_animations();
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0));

    // Aplicar la escala inicial
    setScale(escala);

    // Establecer posición inicial
    setPos(posX, posY);
}

personaje::~personaje()
{
    delete pixmap_management;
}

void personaje::setScaleFactor(float factor)
{
    escala = factor;
    setScale(escala); // Cambiar la escala del QGraphicsPixmapItem
}

void personaje::set_keys(unsigned int *keys)
{
    for (unsigned int i = 0; i < 4; i++) this->keys[i] = keys[i];
}

void personaje::move(unsigned int key, bool is_valid)
{
    if (key == keys[0] && is_valid) { // Movimiento a la izquierda
        setPixmap(pixmap_management->get_current_pixmap(0));
        posX -= homero_speed;
    }
    else if (key == keys[1] && is_valid) { // Movimiento a la derecha
        setPixmap(pixmap_management->get_current_pixmap(1));
        posX += homero_speed;
    }
    else if (key == keys[2] && is_valid) { // Salto (tecla W)
        if (!enElAire) { // Solo si está en el suelo
            enElAire = true;      // Cambiar el estado a "en el aire"
            velY = fuerzaSalto;   // Velocidad inicial hacia arriba
            setPixmap(pixmap_management->get_current_pixmap(2)); // Sprite de salto
        }
    }

    // Actualizar posición en pantalla
    setPos(posX, posY);
}

void personaje::actualizarMovimiento()
{
    if (enElAire) { // Solo actualizar física cuando está en el aire
        // Actualizar velocidad vertical con la gravedad
        velY += gravedad;

        // Actualizar posición vertical con la velocidad
        posY += velY;

        // Verificar si llega al suelo
        if (posY >= 300) { // Nivel del suelo
            posY = 300;       // Fijar la posición al nivel del suelo
            velY = 0;         // Detener movimiento vertical
            enElAire = false; // Permitir nuevos saltos
            setPixmap(pixmap_management->get_current_pixmap(0)); // Cambiar al sprite de pie
        }

        // Ajustar la posición del personaje en pantalla
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
    animation_jump(); // Configurar la animación de salto
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
    dim.setX(0); // Cambia según el sprite de salto
    dim.setY(homero_pixel_y_size); // Supongamos que el sprite de salto está en una fila diferente
    dim.setHeight(1 * homero_pixel_y_size);
    dim.setWidth(1 * homero_pixel_x_size); // Solo un cuadro para el salto
    pixmap_management->add_new_animation(dim, 1);
}
