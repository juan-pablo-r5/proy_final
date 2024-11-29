#include "dona.h"

dona::dona(unsigned int scale) {
    pixmap_management = new sprite(":/dona.png",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(dona_pixel_x_size,dona_pixel_y_size);

    set_animations();
    setPixmap(pixmap_management->get_current_pixmaps(0,dona_pixel_x_size,dona_pixel_y_size));

    vx = 0;
    vy = 0;
    ax = 0;
    ay = 0;
    amplitude = 50;
    frequency = 1;
    friction = 0.01;
    time_elapsed = 0;
    time_to_reverse = 50000; // Tiempo antes de devolverse (ms)


    time_period = 16; // ~60 FPS (16 ms por frame)
    time = new QTimer(this);
    connect(time, &QTimer::timeout, this, &dona::time_step);

}

dona::~dona()
{
    delete pixmap_management;
    delete time;
}

QRect dona::set_complete_sprites()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*dona_pixel_y_size);
    dim.setWidth(1*dona_pixel_x_size);

    return dim;
}

void dona::set_animations()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*dona_pixel_y_size);
    dim.setWidth(1*dona_pixel_x_size);
    pixmap_management->add_new_animation(dim,1);
}


void dona::set_initial_conditions(float x, float y, float vx, float amplitude, float frequency) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->amplitude = amplitude;
    this->frequency = frequency;
    this->initial_x = x;
    this->initial_y = y;

    setPos(x, y);

}

void dona::start_motion() {
    time->start(time_period);
}

void dona::stop_motion() {
    time->stop();
}

void dona::time_step() {
    // Incrementar el tiempo acumulado
    time_elapsed += time_period / 1000.0; // Convertir milisegundos a segundos

    // **Movimiento Oscilatorio Vertical (Senoidal):**
    y = initial_y + amplitude * sin(2 * M_PI * frequency * time_elapsed);

    // **Aceleración y Fricción del Aire (Eje X):**
    // Actualizar velocidad en X con aceleración (opcional) y fricción
    vx += ax * (time_period / 1000.0);    // Aceleración en X
    vx *= (1.0 - friction);           // Aplicar fricción en X

    // Actualizar la posición en X
    x += direction * vx * (time_period / 1000.0);

    // **Aceleración y Fricción del Aire (Eje Y):**
    vy += ay * (time_period / 1000.0);    // Aceleración en Y (si aplica)
    vy *= (1.0 - friction);           // Aplicar fricción en Y

    // Modificar la posición en Y con velocidad (si fuera necesario además de la senoidal)
    // y += vy * (time_period / 1000.0);

    // **Actualizar posición gráfica:**
    setPos(x, y);
    // Si ha regresado a la posición inicial, detener el movimiento
    if (direction == -1 && x <= initial_x) {
        stop_motion();
        setPos(initial_x, initial_y); // Asegurar que vuelva exactamente a la posición inicial
    }
}

