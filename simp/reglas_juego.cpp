#include "reglas_juego.h"

reglas_juego::reglas_juego(QGraphicsView *graph, QVector<QLabel *> game_labels)
{
    srand(time(NULL));
    this->graph = graph;
    labels = game_labels;
    setup_scene();
    //generate_map();
}

reglas_juego::~reglas_juego()
{
    delete scene;
}

void reglas_juego::setup_scene(){
    // Configurar la geometría de graphicsView
    graph->setGeometry(0, 0,
                       game_scale_factor * game_map_col * game_map_size_col,
                       game_scale_factor * game_map_rows * game_map_size_fil);
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, graph->width() - 2, graph->height() - 2);
    graph->setScene(scene);
    emit game_scene_changed();
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
    //pac->move(event->key(),is_valid);

}


void reglas_juego::generate_fondo() {
    for (unsigned int fil = 0; fil < game_map_rows; fil++) {
        for (unsigned int col = 0; col < game_map_col; col++) {
            // Penúltima fila: bloques tipo 2
            if (fil == game_map_rows - 2) {
                blocks[fil][col] = new ecenario(game_scale_factor, 2);
                blocks[fil][col]->setX(game_scale_factor * blocks_pixel_x_size * col);
                blocks[fil][col]->setY(game_scale_factor * blocks_pixel_y_size * fil);
                scene->addItem(blocks[fil][col]);
            }
            // Última fila: bloques tipo 3
            if (fil == game_map_rows - 1) {
                blocks[fil][col] = new ecenario(game_scale_factor, 1);
                blocks[fil][col]->setX(game_scale_factor * blocks_pixel_x_size * col);
                blocks[fil][col]->setY(game_scale_factor * blocks_pixel_y_size * fil);
                scene->addItem(blocks[fil][col]);
            }
            // En el resto de la escena no agregar bloques
        }
    }
}




