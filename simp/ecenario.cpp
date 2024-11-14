#include "ecenario.h"

ecenario::ecenario(unsigned int scale, unsigned int type)
{
    this->scale = scale;
    pixmap = new sprite(":/blocks.png",scale);
    pixmap->cut_character_pixmap(set_complete_sprites());
    pixmap->set_design_size(blocks_pixel_x_size,
                            blocks_pixel_y_size);

    this->type = type;
    set_type_block();
    setZValue(0);
}

ecenario::~ecenario()
{
    delete pixmap;

}

unsigned int ecenario::get_type()
{
    return type;
}

QRect ecenario::set_complete_sprites()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*blocks_pixel_y_size);
    dim.setWidth(9*blocks_pixel_x_size);

    return dim;
}

QRect ecenario::set_borde()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*blocks_pixel_y_size);
    dim.setWidth(1*blocks_pixel_x_size);

    return dim;
}

QRect ecenario::set_fondo()
{
    QRect dim;

    dim.setX(1*blocks_pixel_x_size);
    dim.setY(1*blocks_pixel_y_size);
    dim.setHeight(1*blocks_pixel_y_size);
    dim.setWidth(1*blocks_pixel_x_size);

    return dim;
}



void ecenario::set_type_block()
{
    if(type == 1) setPixmap(pixmap->get_fixed_image(set_borde()));
    else if(type == 2) setPixmap(pixmap->get_fixed_image(set_fondo()));

}
