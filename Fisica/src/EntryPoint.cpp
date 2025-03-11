/*
 * Este es el laberinto en 2D, usa el mismo algoritmo de Maze.
 * Cuando hago juegos uso mi motor y editor que he ido desarrollando
 * a lo largo de los años, en caso ayude para el puesto me
 * gustaría hacer una demo.
 *
 * Por el mismo motivo hace mucho que no levanto una ventana y un render en
 * GLFW y OpenGL. Pero no me dió mucho problema uso GLSL4.1 porque programo
 * en MacOS y es la máxima versión permitida acá, pero estoy al tanto
 * de las funcionalidades de nuevas versiones.
 *
 * Intenté hacer un 2D y 3D en la misma App, pero no me pareció la mejor
 * idea, así que empezaré el proyecto 3D en otra rama. Igualmente dejé
 * los cambios. El movimiento de cámara no es el mejor (suelo trabajar
 * principalmente en 2D) pero intentaré hacer una mejor verisón en el
 * otro proyecto.
 *
 * He tratado de hacer el proyecto lo más limpio posible y es una
 * estructura similar a la que suelo trabajar en mis juegos
 */

#include "Core/Launch/Application.h"

int main(int argc, char** argv)
{
    auto app = new Application({argc, argv});
    app->Run();
    delete app;
    return 0;
}
