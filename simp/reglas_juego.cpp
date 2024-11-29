#include "reglas_juego.h"

reglas_juego::reglas_juego(QGraphicsView *graph, QVector<QLabel *> game_labels)
{
    this->graph = graph;
    labels = game_labels;
    setup_scene();
    setup_personaje();
    setup_enemigo();
    generate_fondo();
    setup_meteor();
    start_game();
    setup_dona();
    labels[0]->setText("vidas: 7");
    labels[1]->setText("puntos: 0");
    labels[2]->setText("nivel: xd");
}

reglas_juego::~reglas_juego()
{
    delete scene;
    delete time;
}

void reglas_juego::setup_scene(){
    // Configurar la geometría de graphicsView
    graph->setGeometry(0, 0,
                       game_scale_factor * game_map_col * blocks_pixel_x_size,
                       game_scale_factor * game_map_rows * blocks_pixel_y_size);
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, graph->width(), graph->height());
    graph->setScene(scene);
    emit game_scene_changed();
}

void reglas_juego::generate_fondo() {
    for (unsigned int fil = 0; fil < game_map_rows; fil++) {
        for (unsigned int col = 0; col < game_map_col; col++) {
            if (fil == game_map_rows - 1) {
                blocks[fil][col] = new ecenario(game_scale_factor, 1);
            }
            else if (fil == game_map_rows - 2) {
                blocks[fil][col] = new ecenario(game_scale_factor, 2);
            }
            else {
                blocks[fil][col] = new ecenario(game_scale_factor, 3);
            }
            blocks[fil][col]->setX(game_scale_factor * blocks_pixel_x_size * col);
            blocks[fil][col]->setY(game_scale_factor * blocks_pixel_y_size * fil);
            scene->addItem(blocks[fil][col]);
        }
    }
}

void reglas_juego::setup_meteor()
{
    meteor *meteori = new meteor(game_scale_factor);
    meteori->set_initial_conditions(0, 0, 5);      // Establecer condiciones iniciales
    scene->addItem(meteori);

    // Conecta la senal de explosion al manejador
    connect(meteori, &meteor::start_explosion, this, [meteori, this]() {
        qDebug() << "¡Explosion del meteorito!";
        active_meteors.erase(
            std::remove(active_meteors.begin(), active_meteors.end(), meteori),
            active_meteors.end()
            );
        scene->removeItem(meteori);
        delete meteori;
    });
    active_meteors.push_back(meteori);
}

void reglas_juego::start_game()
{
    int time_period = 100; // Tiempo en milisegundos
    time = new QTimer(this);
    connect(time, &QTimer::timeout, this, &reglas_juego::update_game);
    time->start(time_period);
}

void reglas_juego::update_game()
{
    for (auto meteori : active_meteors)
    {
        unsigned int speed = 5;
        bool can_move = object_down_movement(meteori, speed);
        meteori->time_step(can_move);
    }
}

void reglas_juego::setup_dona()
{
    dona *donas = new dona(game_scale_factor);
    donas->set_initial_conditions(3, 3, 0, 50, 0.5); // (x, y, vx, amplitud, frecuencia)
    scene->addItem(donas);
    donas->start_motion();

}
void reglas_juego::set_personaje_keys()
{
    bomberman_keys[0] = Qt::Key_A;
    bomberman_keys[1] = Qt::Key_D;
    bomberman_keys[2] = Qt::Key_W;
    bomberman_keys[3] = Qt::Key_S;
}

void reglas_juego::key_event(QKeyEvent *event)
{
    bool is_valid = true;
    if(static_cast<unsigned int>(event->key())==bomberman_keys[1]) is_valid = true;//object_right_movement(bomberman,bomberman_speed);
    else if(static_cast<unsigned int>(event->key())==bomberman_keys[0]) is_valid = true; // object_left_movement(bomberman,bomberman_speed);
    else if(static_cast<unsigned int>(event->key())==bomberman_keys[2]) is_valid =true; //object_up_movement(bomberman,bomberman_speed);
    else if(static_cast<unsigned int>(event->key())== bomberman_keys[3]) is_valid = true; //object_down_movement(bomberman,bomberman_speed);
    homero->move(event->key(),is_valid);

}


void reglas_juego::setup_personaje(){
    set_personaje_keys();

    homero = new personaje(game_scale_factor);
    homero->setScaleFactor(0.3);
    homero->set_keys(bomberman_keys);
    scene->addItem(homero);
}


void reglas_juego::setup_enemigo(){

    cocodrilo= new enemigo(game_scale_factor);
    scene->addItem(cocodrilo);
}


bool reglas_juego::object_right_movement(QGraphicsPixmapItem *item, unsigned int speed)
{
    int xf1,xf2,yf1,yf2, width, height;
    bool valid_1, valid_2;


    width = item->pixmap().width();
    height = item->pixmap().height();

    xf1 = item->x() + width -1 + speed;
    yf1 = item->y();
    xf2 = item->x() + width -1 + speed;
    yf2 = item->y() + height -1;

    valid_1 = blocks[yf1/(blocks_pixel_y_size*game_scale_factor)][xf1/(blocks_pixel_x_size*game_scale_factor)]->get_type()!=1;
    valid_2 = blocks[yf2/(blocks_pixel_y_size*game_scale_factor)][xf2/(blocks_pixel_x_size*game_scale_factor)]->get_type()!=2;

    return valid_1 && valid_2;

}

bool reglas_juego::object_left_movement(QGraphicsPixmapItem *item, unsigned int speed)
{
    int xf1,xf2,yf1,yf2, height;
    bool valid_1, valid_2;

    height = item->pixmap().height();

    xf1 = item->x() - speed;
    yf1 = item->y();
    xf2 = item->x() - speed;
    yf2 = item->y() + height -1;

    valid_1 = blocks[yf1/(blocks_pixel_y_size*game_scale_factor)][xf1/(blocks_pixel_x_size*game_scale_factor)]->get_type() != 1;
    valid_2 = blocks[yf2/(blocks_pixel_y_size*game_scale_factor)][xf2/(blocks_pixel_x_size*game_scale_factor)]->get_type() != 2;
    return valid_1 && valid_2;
}

bool reglas_juego::object_up_movement(QGraphicsPixmapItem *item, unsigned int speed)
{
    int xf1,xf2,yf1,yf2, width;
    bool valid_1, valid_2;

    width = item->pixmap().width();

    xf1 = item->x();
    yf1 = item->y() - speed;
    xf2 = item->x() + width -1;
    yf2 = item->y() - speed;

    valid_1 = blocks[yf1/(blocks_pixel_y_size*game_scale_factor)][xf1/(blocks_pixel_x_size*game_scale_factor)]->get_type() != 1;
    valid_2 = blocks[yf2/(blocks_pixel_y_size*game_scale_factor)][xf2/(blocks_pixel_x_size*game_scale_factor)]->get_type() != 2;
    return valid_1 && valid_2;
}


bool reglas_juego::object_down_movement(QGraphicsPixmapItem *item, unsigned int speed)
{
    int xf1,xf2,yf1,yf2, width, height;
    bool valid_1, valid_2;

    width = item->pixmap().width();
    height = item->pixmap().height();

    xf1 = item->x();
    xf2 = item->x() + width - 1;
    yf1 = item->y() + height + speed;
    yf2 = item->y() + height + speed;

    valid_1 = blocks[yf1 / (blocks_pixel_y_size * game_scale_factor)]
                    [xf1 / (blocks_pixel_x_size * game_scale_factor)]->get_type() != 1;

    valid_2 = blocks[yf2 / (blocks_pixel_y_size * game_scale_factor)]
                    [xf2 / (blocks_pixel_x_size * game_scale_factor)]->get_type() != 2;
    return valid_1 && valid_2;
}

int reglas_juego::get_level_from_label()
{
    QString text = labels[0]->text();
    QStringList parts = text.split(": ");
    if (parts.size() == 2)
    {
        bool ok;
        int level = parts[1].toInt(&ok);
        if (ok)
        {
            return level;
        }
    }
    return 0;
}
void reglas_juego::update_level_in_label(int lives)
{
    labels[0]->setText("nivel: " + QString::number(lives));
}

int reglas_juego::get_lives_from_label()
{
    QString text = labels[1]->text();
    QStringList parts = text.split(": ");
    if (parts.size() == 2)
    {
        bool ok;
        int lives = parts[1].toInt(&ok);
        if (ok)
        {
            return lives;
        }
    }
    return 0;
}

void reglas_juego::update_lives_in_label(int lives)
{
    labels[1]->setText("vidas: " + QString::number(lives));
}

int reglas_juego::get_points_from_label()
{
    QString text = labels[2]->text();
    QStringList parts = text.split(": ");
    if (parts.size() == 2)
    {
        bool ok;
        int point = parts[1].toInt(&ok);
        if (ok)
        {
            return point;
        }
    }
    return 0; // Default en caso de error
}

void reglas_juego::update_point_in_label(int lives)
{
    labels[2]->setText("puntos: " + QString::number(lives));
}
