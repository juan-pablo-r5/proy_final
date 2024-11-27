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
    dim.setHeight(7*blocks_pixel_y_size);
    dim.setWidth(7*blocks_pixel_x_size);

    return dim;
}

QRect ecenario::set_stone()
{
    QRect dim;

    dim.setX(1*blocks_pixel_x_size+2);
    dim.setY(1*blocks_pixel_y_size+2);
    dim.setHeight(1*blocks_pixel_y_size);
    dim.setWidth(1*blocks_pixel_x_size);

    return dim;
}

QRect ecenario::set_stone_plan()
{
    QRect dim;

    dim.setX(1*blocks_pixel_x_size+2);
    dim.setY(1);
    dim.setHeight(1*blocks_pixel_y_size);
    dim.setWidth(1*blocks_pixel_x_size);

    return dim;
}

QRect ecenario::set_roca()
{
    QRect dim;

    dim.setX(5*blocks_pixel_x_size+6);
    dim.setY(2*blocks_pixel_y_size+3);
    dim.setHeight(1*blocks_pixel_y_size);
    dim.setWidth(1*blocks_pixel_x_size);

    return dim;
}


void ecenario::set_type_block()
{
    if(type == 1) setPixmap(pixmap->get_fixed_image(set_stone()));
    else if(type == 2) setPixmap(pixmap->get_fixed_image(set_stone_plan()));
    else if(type == 3)setPixmap(pixmap->get_fixed_image(set_roca()));

}
