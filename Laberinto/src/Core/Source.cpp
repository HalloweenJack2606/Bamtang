/*
 * No suelo poner comentarios en mi código porque "el mejor comentario
 * es ningún comentario" creo que el código es legible. En caso se requiera
 * puedo explicar cada parte del código.
 *
 * Estoy separando Maze desde ya en su propia clase. Tengo pensado
 * hacer el 2D y 3D en base a este código de laberinto. Mantengo el
 * "createMaze2D" en su función aparte porque así se pidió.
 *
 * He trabajado con A* anteriormente para resolver laberintos, pero nunca
 * he hecho laberintos así. En este caso usaré BFS en vez de A* por simplicidad.
 * He leido un poco sobre cuales son las mejores soluciones para los
 * requerimientos y estoy leyendo unos articulos y viendo unos videos sobre
 * DFS Backtracking.
 *
 * Los archivos de CMake son porque suelo trabajar en Mac o Linux
 * haré una VM de Windows para compilarlo con VS2019. No mandaré el .SLN
 * pero dejaré un script de premake para generarlo y evitar problemas de
 * directorios
 */

#include "Maze/Maze.h"

Maze createMaze2D(uint32 size)
{
    Maze maze;
    maze.Generate(size);
    return maze;
}

int main()
{
    uint32 size = 11;
    Maze maze = createMaze2D(size);
    maze.Print();
    std::cin.get();
    return 0;
}
