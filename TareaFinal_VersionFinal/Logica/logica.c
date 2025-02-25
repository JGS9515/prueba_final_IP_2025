#include <Logica/datos.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// con array de la struct que almacenará los investigadores que se inicialicen automáticamente
void inicializarInvestigadoresAutomaticamente(investigador investigadores[], int *cantidadInvestigadores){//puntero para actualizar la cantidad de inv registrados
    int inicializado = 0;
    if (inicializado = 1){

        investigador investigador1 = {
            .id = "1111",
            .nombre = "Diego Gonzalez",
            .edad = 38,
            .experiencia = 13,
            .proyectos = {  //array de cadenas con los proyectos del investig El último proyecto está vacío ("") para indicar el final de la lista.
                "Desarrollo de Materiales Fotovoltaicos Eficientes",
                "Estudio del Uso de Drones para Monitoreo Ambiental",
                "Desarrollo de Sistemas de Control Automatizado para Cultivos"
                ""
            }
        };

        investigador investigador2 = {
            .id = "0000",
            .nombre = "Felipe Valverde",
            .edad = 45,
            .experiencia = 20,
            .proyectos = {
                "Desarrollo de Sistemas de Control Automatizado para Cultivos",
                ""
            }
        };

        investigador investigador3 = {
            .id = "0003",
            .nombre = "Eduardo Garc\241a",
            .edad = 28,
            .experiencia = 5,
            .proyectos = {
                "Desarrollo de Materiales Fotovoltaicos Eficientes",
                "Desarrollo de Modelos Predictivos para el Riesgo de Incendios Forestales",
                ""
            }
        };

        investigador investigador4 = {
            .id = "1554",
            .nombre = "Lionel Hern\240ndez",
            .edad = 50,
            .experiencia = 25,
            .proyectos = {
                "Estudio del Uso de Drones para Monitoreo Ambiental",
                "Desarrollo de Sistemas de Control Automatizado para Cultivos",
                "Estudio de la Metabolismo de Microorganismos",
                ""
            }
        };

        investigador investigador5 = {
            .id = "0005",
            .nombre = "Mariano Le\242n",
            .edad = 35,
            .experiencia = 15,
            .proyectos = {
                "Desarrollo de Sistemas de Control Automatizado para Cultivos",
                "Estudio de la Metabolismo de Microorganismos",
                ""
            }
        };

        investigadores[0] = investigador1;
        investigadores[1] = investigador2;
        investigadores[2] = investigador3;
        investigadores[3] = investigador4;
        investigadores[4] = investigador5;

        *cantidadInvestigadores = 5;
    }
}

// Función para verificar si una cadena es un número
int esNumero(const char *str) {
    int i;
    int esNumero = 1;
    for (i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            esNumero = 0;
        }
    }
    return esNumero;
}

int esCodigoValido(const char *codigo) {
    int esValido = 1;
    int i;

    if (strlen(codigo) != 4) {
        esValido = 0;
    }
    // Chequear que sean dígitos
    for (i = 0; i < 4 && esValido; i++) {
        if (!isdigit(codigo[i])) {
            esValido = 0;
        }
    }
    return esValido;
}

int esIdUnico(const char *codigo, investigador *investigadores, int cantidadInvestigadores) {
    int esUnico = 1;
    int i;
    for (i = 0; i < cantidadInvestigadores; i++) {
        if (strcmp(investigadores[i].id, codigo) == 0) {
            esUnico = 0;
        }
    }
    return esUnico;
}

int validarNombre(const char *nombre) {
    int esValido = 1;
    int continuar = 1;
    int i;
    int tieneLetras = 0;
    // Verificar si el nombre está vacío
    for (i = 0; nombre[i] != '\0' && continuar; i++) {
        if (isdigit(nombre[i])) {
            esValido = 0;
            continuar = 0;
        } else if (isalpha(nombre[i])) {
            tieneLetras = 1;
        }
    }
    // Si no hay letras, el nombre no es válido
    if (!tieneLetras) {
        esValido = 0;
    }

    return esValido;
}

int validarEdad(const char *edadStr, int *edad) {
    int esValido = 1;
    int tieneLetras = 0, tieneNumeros = 0;
    int i;

    // Verificar cada carácter de la cadena
    for (i = 0; edadStr[i] != '\0'; i++) {
        if (isdigit(edadStr[i])) {
            tieneNumeros = 1;
        } else if (isalpha(edadStr[i])) {
            tieneLetras = 1;
        } else {
            // Si hay algún carácter que no es ni letra ni número, es inválido
            esValido = 0;
        }
    }
    // Si hay una combinación de letras y números, es inválido
    if (tieneLetras && tieneNumeros) {
        esValido = 0;
    }
    // Si no hay números, es inválido
    if (!tieneNumeros) {
        esValido = 0;
    }
    // Si es válido hasta ahora, convertir a entero y verificar el rango
    if (esValido) {
        *edad = atoi(edadStr);
        if (*edad < 18 || *edad > 100) {
            esValido = 0;
        }
    }

    return esValido;
}

int validarExperiencia(const char *experienciaStr, int *experiencia, int edad) {
    int tieneLetras = 0, tieneNumeros = 0;
    int esValido = 1;
    int i;
    // Verificar si hay combinaciones de letras y números
    for (i = 0; experienciaStr[i] != '\0'; i++) {
        if (isdigit(experienciaStr[i])) {
            tieneNumeros = 1;
        } else if (isalpha(experienciaStr[i])) {
            tieneLetras = 1;
        }
    }
    // Si hay una combinación de letras y números, no es válido
    if (tieneLetras && tieneNumeros) {
        esValido = 0;
    } else if (!tieneNumeros) {
        // Si no hay números, no es válido
        esValido = 0;
    } else {
        // Convertir a entero y verificar rangos
        *experiencia = atoi(experienciaStr);
        if (*experiencia < 0) {
            esValido = 0;
        } else if (*experiencia > (edad - 18)) {
            esValido = 0;
        }
    }
    return esValido;
}

int validarProyecto(const char *proyecto) { //Asumo que el proyecto puede contener combinacion de letras y números, pero no solo números.
                                            // (Por ejemplo: Objetivos de Desarrollo Sostenible 2030 (qué se yo), proyecto reactor nuclear 3.
    int tieneLetras = 0;
    int tieneNumeros = 0;
    int esValido = 1;
    int continuar = 1;
    int i;

    // Verificar si el proyecto contiene al menos una letra y opcionalmente números
    for (i = 0; proyecto[i] != '\0' && continuar; i++) {
        if (isalpha(proyecto[i])) {
            tieneLetras = 1;
        } else if (isdigit(proyecto[i])) {
            tieneNumeros = 1;
        } else if (!isspace(proyecto[i])) {
            // Si hay caracteres que no son letras, números o espacios, es inválido
            esValido = 0;
            continuar = 0;
        }
    }
    // El proyecto es válido si contiene al menos una letra (puede incluir números)
    if (tieneLetras) {
        esValido = 1;
    } else {
        esValido = 0;
    }
    return esValido;
}

void ordenarInvestigadoresPorExperiencia(investigador investigadores[], int cantidad) { //metodo burbuja
    int i, j;
    for (i = 0; i < cantidad; i++) {
        for (j = i + 1; j < cantidad; j++) {
            if (investigadores[j].experiencia > investigadores[i].experiencia) {
                investigador temp = investigadores[i];
                investigadores[i] = investigadores[j];
                investigadores[j] = temp;
            }
        }
    }
}

int obtenerInvestigadorMenosExperiencia(investigador investigadores[], int cantidad) {
    int menosExperienciaIndex = 0;
    int i;

    for (i = 1; i < cantidad; i++) {
        if (investigadores[i].experiencia < investigadores[menosExperienciaIndex].experiencia) {
            menosExperienciaIndex = i;
        }
    }

    return menosExperienciaIndex;
}

float calcularPromedioEdad(investigador investigadores[], int cantidad) {
    int sumaEdades = 0;
    float promedioEdad = -1;

    if (cantidad > 0) {
        int i;
        for (i = 0; i < cantidad; i++) {
            sumaEdades += investigadores[i].edad;
        }
        promedioEdad = (float)sumaEdades / cantidad;
    }

    return promedioEdad;
}

int obtenerProyectosUnicos(investigador investigadores[], int cantidad, char proyectosUnicos[][100]){
    int numProyectos = 0;
    int i, j, k;
    // Inicializar proyectosUnicos con cadenas vacías
    for (i = 0; i < 150; i++) {
        strcpy(proyectosUnicos[i], "");
    }
    // Recopilar proyectos únicos
    for (i = 0; i < cantidad; i++) { //utilizadas para iterar sobre los investigadores, sus proyectos y la lista de proyectos únicos.
        for (j = 0; j < 10 && investigadores[i].proyectos[j][0] != '\0'; j++) {
            int existe = 0;
            int continuar = 1;
            for (k = 0; k < numProyectos && continuar; k++) {
                if (strcmp(proyectosUnicos[k], investigadores[i].proyectos[j]) == 0) {
                    existe = 1;
                    continuar = 0;
                }
            }
            if (!existe) {
                strcpy(proyectosUnicos[numProyectos], investigadores[i].proyectos[j]);
                numProyectos++;
            }
        }
    }
    return numProyectos;
}

float calcularPromedioExperiencia(investigador investigadores[], int cantidad) {
    int sumaExperiencia = 0;
    float promedioExperiencia = -1;

    if (cantidad > 0) {
        int i;
        for (i = 0; i < cantidad; i++) {
            sumaExperiencia += investigadores[i].experiencia;
        }
        promedioExperiencia = (float)sumaExperiencia / cantidad;
    }

    return promedioExperiencia;
}

int obtenerInvestigadorMasJoven(investigador investigadores[], int cantidad) {
    int indiceMasJoven = 0;
    int i;

    for (i = 1; i < cantidad; i++) {
        if (investigadores[i].edad < investigadores[indiceMasJoven].edad) {
            indiceMasJoven = i;
        }
    }

    return indiceMasJoven;
}

int obtenerInvestigadorMasViejo(investigador investigadores[], int cantidad) {
    int indiceMasViejo = 0;
    int i;

    for (i = 1; i < cantidad; i++) {
        if (investigadores[i].edad > investigadores[indiceMasViejo].edad) {
            indiceMasViejo = i;
        }
    }

    return indiceMasViejo;
}
