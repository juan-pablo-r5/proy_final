#include "reglas_juego.h"

reglas_juego::reglas_juego(QGraphicsView *graph, QVector<QLabel *> game_labels)
{
    this->graph = graph;
    labels = game_labels;
    setup_scene();
    start_game();
    labels[0]->setText("vidas: 100");
    labels[1]->setText("puntos: 0");
    if (get_level_from_label()==1) generate_nivel1();
    else if (get_level_from_label()==2) generate_nivel2();
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
            if (col == 0 || col == game_map_col - 1) {
                blocks[fil][col] = new ecenario(game_scale_factor, 1);
            }
            else if (fil == game_map_rows - 1) {
                blocks[fil][col] = new ecenario(game_scale_factor, 1);
            }
            else if (fil == game_map_rows - 2 && col >= (game_map_col / 2 - 2) && col < (game_map_col / 2 + 2)) {
                blocks[fil][col] = new ecenario(game_scale_factor, 1);
            }
            else if (fil == game_map_rows - 3 && col >= (game_map_col / 2 - 2) && col < (game_map_col / 2 + 2)) {
                blocks[fil][col] = new ecenario(game_scale_factor, 2);
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
void reglas_juego::generate_nivel1() {
    labels[2]->setText("nivel: 1");
    generate_fondo();
    setup_personaje();
    for (int i = 0; i < 5; i++) {
        setup_meteor();
        setup_enemigo1(2 + i * 6);
    }
}
void reglas_juego::generate_nivel2() {
    labels[2]->setText("nivel: 2");
    generate_fondo();
    setup_personaje();

    for (int i = 0; i < 10; i++) {
        setup_meteor();
        setup_enemigo2(2 + i * 6);
    }

}
void reglas_juego::setup_meteor() {
    if (active_meteors.size() >= 5) return;// max 5

    int random_col = rand() % game_map_col-1;
    meteor *meteori = new meteor(game_scale_factor);
    meteori->set_initial_conditions(random_col * blocks_pixel_x_size * game_scale_factor, 0, 5);
    scene->addItem(meteori);

    connect(meteori, &meteor::start_explosion, this, [meteori, this]() {
        qDebug() << "¡Explosion del meteorito!";
        active_meteors.erase(
            std::remove(active_meteors.begin(), active_meteors.end(), meteori),
            active_meteors.end()
            );
        scene->removeItem(meteori);
        delete meteori;
        setup_meteor();
    });
    active_meteors.push_back(meteori);
}


void reglas_juego::start_game()
{
    int time_period = 200; // Tiempo en milisegundos
    time = new QTimer(this);
    connect(time, &QTimer::timeout, this, &reglas_juego::update_game);
    time->start(time_period);
}

void reglas_juego::check_homero_vs_cocodrilos()
{
    for (auto it = cocodrilos.begin(); it != cocodrilos.end(); ++it)
    {
        enemigo *cocodrilo = *it;
        float homero_x = homero->x();
        float homero_y = homero->y();
        float homero_width = homero->pixmap().width();
        float homero_height = homero->pixmap().height();

        float cocodrilo_x = cocodrilo->x();
        float cocodrilo_y = cocodrilo->y();
        float cocodrilo_width = cocodrilo->pixmap().width();
        float cocodrilo_height = cocodrilo->pixmap().height();

        // homero rango horizontal del Cocodrilo
        bool in_horizontal_range =
            (homero_x + homero_width > cocodrilo_x) &&
            (homero_x < cocodrilo_x + cocodrilo_width);

        //  Homero aplazta al coco
        if (in_horizontal_range &&
            (homero_y + homero_height <= cocodrilo_y + 5) &&
            (homero_y + homero_height > cocodrilo_y))
        {
            scene->removeItem(cocodrilo);
            delete cocodrilo;
            it = cocodrilos.erase(it);
            // Incrementar puntos
            int current_point = get_points_from_label();
            current_point += 10;
            update_point_in_label(current_point);

            qDebug() << "¡Homero aplasto al Cocodrilo!";
            return;
        }
        // Verificar collicion Lateral
        if (in_horizontal_range &&
            (homero_y + homero_height > cocodrilo_y) &&
            (homero_y < cocodrilo_y + cocodrilo_height) &&
            !(homero_y + homero_height <= cocodrilo_y + 5)) // No pisa desde arriba
        {
            int current_lives = get_lives_from_label();
            current_lives -= 1;
            update_lives_in_label(current_lives);

            if (current_lives <= 0)
            {
                qDebug() << "¡Game Over!";
            }
            qDebug() << "¡devorar homero!";
            return;
        }
    }
}

void reglas_juego::check_homero_vs_meteoros()
{
    for (auto meteori : active_meteors)
    {
        unsigned int speed = 5;
        bool can_move = object_down_movement(meteori, speed);

        if (meteori->collidesWithItem(homero))
        {
            int current_lives = get_lives_from_label();
            current_lives -= 5;
            update_lives_in_label(current_lives);
            if (current_lives <= 0)
            {
                qDebug() << "¡Game Over!";
                return;
            }
            qDebug() << "Homero perdio 5 vidas. Vidas restantes:" << current_lives;
            can_move=false;
        }
        meteori->time_step(can_move);
    }
}
void reglas_juego::check_homero_vs_dona()
{
    if (!homero || !donast)
        return;
    if ( donast->collidesWithItem(homero))
    {
        int decision = rand() % 2;//0: gana vida, 1: pierde 5 vidas
        int current_lives = get_lives_from_label();
        if (decision == 0)
        {
            current_lives++;
            qDebug() << "¡Homero gana una vida!";
        }
        else
        {
            current_lives -= 5;
            qDebug() << "¡Homero pierde 5 vidas!";
        }
        update_lives_in_label(current_lives);

        if (current_lives <= 0)
        {
            qDebug() << "¡Game Over!";
            return;
        }
        scene->removeItem(donast);
        delete donast;
        donast = nullptr;
    }
}

void reglas_juego::update_game()
{
    check_homero_vs_cocodrilos();
    check_homero_vs_meteoros();
    check_homero_vs_dona();
    bool puedeMoverse = object_down_movement(homero, 5);
    homero->actualizarMovimiento(puedeMoverse);

    for (auto cocodrilo : cocodrilos)
    {
        if (cocodrilo->tipo_movimiento == BASE)
        {
            bool can_move = cocodrilo->moving_right
                                ? object_right_movement(cocodrilo, cocodrilo_speed)
                                : object_left_movement(cocodrilo, cocodrilo_speed);
            cocodrilo->move(can_move);
        }
        else if (cocodrilo->tipo_movimiento == ATRACCION)
        {
            cocodrilo->move_towards_target(homero);
        }
    }
}

void reglas_juego::setup_dona()
{
    donast = new dona(game_scale_factor);
    donast->start_motion();
    donast->set_initial_conditions(3*blocks_pixel_x_size*game_scale_factor, 3*blocks_pixel_y_size*game_scale_factor, 170, 50, 0.5); // (x, y, vx, amplitud, frecuencia)
    scene->addItem(donast);
}

void reglas_juego::set_personaje_keys()
{
    bomberman_keys[0] = Qt::Key_A;
    bomberman_keys[1] = Qt::Key_D;
    bomberman_keys[2] = Qt::Key_W;
}

void reglas_juego::key_event(QKeyEvent *event)
{
    bool is_valid = true;
    if(static_cast<unsigned int>(event->key())==bomberman_keys[1]) is_valid = object_right_movement(homero, homero_speed);
    else if(static_cast<unsigned int>(event->key())==bomberman_keys[0]) is_valid = object_left_movement(homero, homero_speed);
    else if(static_cast<unsigned int>(event->key())==bomberman_keys[2]) is_valid =true;
    homero->move(event->key(),is_valid);
}


void reglas_juego::setup_personaje(){
    set_personaje_keys();
    int x =game_scale_factor*16 * blocks_pixel_x_size;
    int y=game_scale_factor* 4 * blocks_pixel_y_size;
    homero = new personaje(game_scale_factor, x, y);
    homero->set_keys(bomberman_keys);
    scene->addItem(homero);
    connect(homero,SIGNAL(is_moving(QGraphicsPixmapItem*,bool)),this,SLOT(set_focus(QGraphicsPixmapItem*,bool)));
}


void reglas_juego::set_focus(QGraphicsPixmapItem *item, bool is_x_focus)
{
    int item_w = item->pixmap().width();
    int xplayer= is_x_focus*((item->x()+item_w/2)-scene->width()/2);
    scene->setSceneRect(xplayer+836,0,scene->width(),scene->height());
}

void reglas_juego::setup_enemigo1(int col){
    enemigo *cocodrilo = new enemigo(game_scale_factor,BASE);
    cocodrilos.push_back(cocodrilo); // Insertar en std::vector
    scene->addItem(cocodrilo);
    cocodrilo->setPos(game_scale_factor* col* blocks_pixel_x_size,game_scale_factor* 5* blocks_pixel_y_size+20);
}
void reglas_juego::setup_enemigo2(int col){
    enemigo *cocodrilo = new enemigo(game_scale_factor,ATRACCION);
    cocodrilos.push_back(cocodrilo); // Insertar en std::vector
    scene->addItem(cocodrilo);
    cocodrilo->setPos(game_scale_factor* col* blocks_pixel_x_size,game_scale_factor* 5* blocks_pixel_y_size+20);
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
    int xf1, xf2, yf1, yf2, width, height;
    bool valid_1, valid_2;

    width = item->pixmap().width();
    height = item->pixmap().height();

    xf1 = item->x();
    xf2 = item->x() + width - 1;
    yf1 = item->y() + height + speed;
    yf2 = item->y() + height + speed;

    valid_1 = blocks[yf1 / (blocks_pixel_y_size * game_scale_factor)]
                    [xf1 / (blocks_pixel_x_size * game_scale_factor)]->get_type() != 1 &&
              blocks[yf1 / (blocks_pixel_y_size * game_scale_factor)]
                    [xf1 / (blocks_pixel_x_size * game_scale_factor)]->get_type() != 2;

    valid_2 = blocks[yf2 / (blocks_pixel_y_size * game_scale_factor)]
                    [xf2 / (blocks_pixel_x_size * game_scale_factor)]->get_type() != 1 &&
              blocks[yf2 / (blocks_pixel_y_size * game_scale_factor)]
                    [xf2 / (blocks_pixel_x_size * game_scale_factor)]->get_type() != 2;

    return valid_1 && valid_2;
}


int reglas_juego::get_level_from_label()
{
    QString text = labels[2]->text();
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
    labels[2]->setText("nivel: " + QString::number(lives));
}

int reglas_juego::get_lives_from_label()
{
    QString text = labels[0]->text();
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
    labels[0]->setText("vidas: " + QString::number(lives));
}

int reglas_juego::get_points_from_label()
{
    QString text = labels[1]->text();
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
    return 0;
}

void reglas_juego::update_point_in_label(int lives)
{
    labels[1]->setText("puntos: " + QString::number(lives));
}
