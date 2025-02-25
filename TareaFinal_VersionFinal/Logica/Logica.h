#include <Logica/datos.h>
void inicializarInvestigadoresAutomaticamente(investigador investigadores[], int *cantidadInvestigadores);
int esNumero(const char *str);
int esCodigoValido(const char *codigo);
int esIdUnico(const char *codigo, investigador *investigadores, int cantidadInvestigadores);
int validarNombre(const char *nombre);
int validarEdad(const char *edadStr, int *edad);
int validarExperiencia(const char *experienciaStr, int *experiencia, int edad);
int validarProyecto(const char *proyecto);
int obtenerProyectosUnicos(investigador investigadores[], int cantidad, char proyectosUnicos[][100]);
void ordenarInvestigadoresPorExperiencia(investigador investigadores[], int cantidad);
int obtenerInvestigadorMenosExperiencia(investigador investigadores[], int cantidad);
float calcularPromedioEdad(investigador investigadores[], int cantidad);
float calcularPromedioExperiencia(investigador investigadores[], int cantidad);
int obtenerInvestigadorMasJoven(investigador investigadores[], int cantidad);
int obtenerInvestigadorMasViejo(investigador investigadores[], int cantidad);
