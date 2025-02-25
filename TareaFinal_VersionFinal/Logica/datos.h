#ifndef DATOS_H
#define DATOS_H

struct investigador {
    char id[5]; //array de caracteres para el ID (almacena 4 char más el nulo \0)
    char nombre[50]; //array de caracteres para el nombre(almacena 49 char más el nulo)
    int edad;
    int experiencia;
    char proyectos[10][100]; //matriz de caracteres. Almacena 20 proyectos, cada proyecto puede tener 99 char + nulo
};

typedef struct investigador investigador; //alias oara en vez de tener que escribir struct investigador, solo poner investigador

#endif // DATOS_H
