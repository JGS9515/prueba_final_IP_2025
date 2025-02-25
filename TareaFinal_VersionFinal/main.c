#include <Menu/menu.h>
#include <Interfaz/interfaz.h>
#include <Logica/datos.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    investigador investigadores[1000];
    int cantidadInvestigadores = 0;
    mensajeBienvenida();
    mostrarMenuPrincipal(investigadores, &cantidadInvestigadores);

    return 0;
}
