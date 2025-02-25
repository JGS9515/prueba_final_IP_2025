#include <Logica/datos.h>

void mensajeBienvenida();
int obtenerEntradaNumerica();
void pedirID(investigador *inv, int *continuara);
void pedirNombre(investigador *inv);
void mostrarDatosInvestigadores(investigador *investigadores, int cantidad);
void pedirEdad(investigador *inv);
void pedirExperiencia(investigador *inv);
void pedirProyectos(investigador *inv);
void registrarInvestigadores();
void mostrarDatosInvestigadores(investigador *investigadores, int cantidad);
void mostrarInvestigadoresPorProyecto(investigador investigadores[], int cantidad);
void mostrarProyectosPorID(investigador investigadores[], int cantidad);
void mostrarInvestigadoresVeteranos(investigador investigadores[], int cantidad);
void buscarInvestigadorPorNombre(investigador investigadores[], int cantidad);
void buscarInvestigadorPorID(investigador investigadores[], int cantidad);
void eliminarProyecto(investigador *inv);
void eliminarInvestigador(investigador investigadores[], int *cantidadInvestigadores);
void mostrarTotalInvestigadores(int cantidadInvestigadores);
void mostrarPromedioEdad(investigador investigadores[], int cantidad);
void mostrarPromedioExperiencia(investigador investigadores[], int cantidad);
void mostrarInvestigadorMasJoven(investigador investigadores[], int cantidad);
