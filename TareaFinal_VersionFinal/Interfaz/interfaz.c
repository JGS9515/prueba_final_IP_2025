#include <Menu/menu.h>
#include <Logica/datos.h>
#include <Logica/logica.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void mensajeBienvenida(){
    printf("\t\t\t===========================================================\n");
    printf("\t\t\t\t\t\tBIENVENIDO\n");
    printf("\t\t\t===========================================================\n");
    printf("\t\t\tEste programa se encarga de manejar los registros de los \n\t\t\tinvestigadores del Polo Cient\241fico\n");
    printf("\t\t\t===========================================================\n\t\t\t");
    system("pause");
    system("cls");
}

// Función para la entrada
int obtenerEntradaNumerica(){
    int resultado;
    int entradaValida = 0; //bandera que controla si la entrada es valida. Inicializo en 0(aun no se ha validado)
    char entrada[100];//array char tam 100 para almacenar temporalmente la entrada como cadena de texto. (99 caract pa que no se parta por si acaso)
    while (!entradaValida) {
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = 0;
        if (esNumero(entrada)) {
            resultado = atoi(entrada);
            entradaValida = 1;
        }else{
            printf("\x1b[31mError. Por favor, ingrese un n\243mero:\x1b[0m ");
        }
    }
    return resultado;
}

// Función para pedir el ID
void pedirID(investigador *inv){
    int valido = 0;
    char codigo[10];

    while (!valido) {
        printf("Ingrese su ID de 4 d\241gitos: ");
        fgets(codigo, sizeof(codigo), stdin);
        codigo[strcspn(codigo, "\n")] = 0;

        if (strlen(codigo) == 4 && esCodigoValido(codigo)) {
            strcpy(inv->id, codigo);  // Almacenar el ID como cadena en la estructura
            printf("\x1b[32mEl ID ha sido introducido correctamente.\x1b[0m\n");
            valido = 1;
        }else{
            printf("\x1b[31mError, el c\242digo debe tener exactamente 4 d\241gitos unidos. Intente nuevamente.\x1b[0m\n");

        }
    }

}

void pedirNombre(investigador *inv){
    int nombreValido = 0;
    int esValido = 1;
    char nombre[100];

    while (!nombreValido) {
        printf("Ingrese el nombre del investigador: ");
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = 0;
        if (validarNombre(nombre)) {
            strcpy(inv->nombre, nombre);  // Copiar el nombre a la estructura
            printf("\x1b[32mEl nombre ha sido introducido exitosamente.\x1b[0m\n");
            nombreValido = 1;
        }
        else if (nombre[0] == '\0'){
            printf("\x1b[31mEl nombre no se puede dejar vac\241o.\x1b[0m\n");
            esValido = 0;
        }
        else
            printf("\x1b[31mError, nombre no v\240lido, intente de nuevo.\x1b[0m\n");
        fflush(stdin);
    }
}

void pedirEdad(investigador *inv) {
    int edadValida = 0;
    char edadStr[10];
    int edad;
    int i;

    while (!edadValida) {
        printf("Ingrese la edad del investigador: ");
        fgets(edadStr, sizeof(edadStr), stdin);
        edadStr[strcspn(edadStr, "\n")] = 0;
        // Verificar si la entrada está vacía
        if (edadStr[0] == '\0') {
            printf("\x1b[31mError, no se puede dejar la edad vac\241a.\x1b[0m\n");
        } else {
            // Variables para verificar combinación de letras y números
            int tieneLetras = 0, tieneNumeros = 0;
            for (i = 0; edadStr[i] != '\0'; i++) {
                if (isdigit(edadStr[i])) {
                    tieneNumeros = 1;
                } else if (isalpha(edadStr[i])) {
                    tieneLetras = 1;
                }
            }
            // Mostrar mensaje de error si hay combinación de letras y números
            if (tieneLetras && tieneNumeros) {
                printf("\x1b[31mError, la edad no puede contener una combinaci\242n de letras y n\243meros.\x1b[0m\n");
            }
            // Validar rango de edad
            else if (atoi(edadStr) < 18) {
                printf("\x1b[31mError, en este centro de trabajo no radican menores de 18 a\244os.\x1b[0m\n");
            } else if (atoi(edadStr) > 100) {
                printf("\x1b[31mEl m\240ximo de edad permitido es 100.\x1b[0m\n");
            }
            // Validar formato general de la edad
            else if (!validarEdad(edadStr, &edad)) {
                printf("\x1b[31mError, la edad ingresada no es v\240lida. Intente nuevamente.\x1b[0m\n");
            }
            // Si pasa todas las validaciones, almacenar la edad
            else {
                inv->edad = edad;
                edadValida = 1;
                printf("\x1b[32mLa edad ha sido introducida exitosamente.\x1b[0m\n");
            }
        }
    }
}

void pedirExperiencia(investigador *inv) {
    int experienciaValida = 0;
    char experienciaStr[10];
    int experiencia;
    int i;

    while (!experienciaValida) {
        printf("Ingrese la experiencia del investigador (a\244os): ");
        fgets(experienciaStr, sizeof(experienciaStr), stdin);
        experienciaStr[strcspn(experienciaStr, "\n")] = 0;

        if (experienciaStr[0] == '\0') {
            printf("\x1b[31mError, no se puede dejar la experiencia vac\241a.\x1b[0m\n");
        } else if (!validarExperiencia(experienciaStr, &experiencia, inv->edad)) {
            // Mostrar mensajes de error específicos basados en la entrada
            int tieneLetras = 0, tieneNumeros = 0;
            for (i = 0; experienciaStr[i] != '\0'; i++) {
                if (isdigit(experienciaStr[i])) {
                    tieneNumeros = 1;
                } else if (isalpha(experienciaStr[i])) {
                    tieneLetras = 1;
                }
            }
            if (tieneLetras && tieneNumeros) {
                printf("\x1b[31mError, la experiencia no puede contener una combinaci\242n de letras y n\243meros.\x1b[0m\n");
            } else if (atoi(experienciaStr) < 0) {
                printf("\x1b[31mError, la experiencia no puede ser menor que 0.\x1b[0m\n");
            } else if (atoi(experienciaStr) > (inv->edad - 18)) {
                printf("\x1b[31mError, la experiencia no puede ser mayor que la diferencia entre la edad y 18 a\244os.\x1b[0m\n");
            } else if (!tieneNumeros) {
                printf("\x1b[31mDigite la experiencia de forma num\202rica.\x1b[0m\n");
            }
        } else {
            // Si la experiencia es válida, la almacenamos y salimos del bucle
            inv->experiencia = experiencia;
            experienciaValida = 1;
            printf("\x1b[32mLa experiencia ha sido introducida exitosamente.\x1b[0m\n");
        }
        fflush(stdin);
    }
}

void pedirProyectos(investigador *inv) {
    int indiceProyecto = 0;
    int proyectosValidos = 0;
    char proyecto[100];

    while (!proyectosValidos) {
        printf("Ingrese el nombre de los proyectos en los que haya trabajado (o escriba 'fin' para terminar): ");
        fgets(proyecto, sizeof(proyecto), stdin);
        proyecto[strcspn(proyecto, "\n")] = 0;

        if (strcmp(proyecto, "fin") == 0) {
            proyectosValidos = 1;
        } else {
            if (proyecto[0] == '\0') {
                printf("\x1b[31mError, no se puede dejar el nombre del proyecto vac\241o.\x1b[0m\n");
            } else if (!validarProyecto(proyecto)) {
                printf("\x1b[31mEl nombre del proyecto no es v\240lido. Aseg\243rese de que no sea solo num\202rico.\x1b[0m\n");
            } else {
                strcpy(inv->proyectos[indiceProyecto], proyecto);
                indiceProyecto++;
                printf("\x1b[32mProyecto registrado: %s\x1b[0m\n", proyecto);
            }
        }

        fflush(stdin);
    }
}

void registrarInvestigadores(investigador investigadores[], int *cantidadInvestigadores) {
    int continuar = 0;
    int registroCompleto = 0;
    int i;

    while (!registroCompleto) {
        investigador nuevoInvestigador;
        strcpy(nuevoInvestigador.id, ""); //Inicializa las cadenas como vacias
        strcpy(nuevoInvestigador.nombre, "");
        nuevoInvestigador.experiencia = 0; // inicializa en 0
        nuevoInvestigador.edad = 0;
        for (i = 0; i < 10; i++) {
            strcpy(nuevoInvestigador.proyectos[i], ""); //inicializa los proyectos como vacio
        }
        do {
            pedirID(&nuevoInvestigador);
            if (!esIdUnico(nuevoInvestigador.id, investigadores, *cantidadInvestigadores)) {
                printf("Este ID ya existe. Intente de nuevo con un ID diferente.\n");
            }
            fflush(stdin);
        } while (!esIdUnico(nuevoInvestigador.id, investigadores, *cantidadInvestigadores));

        pedirNombre(&nuevoInvestigador);
        pedirEdad(&nuevoInvestigador);
        pedirExperiencia(&nuevoInvestigador);
        pedirProyectos(&nuevoInvestigador);

        printf("\x1b[32mINVESTIGADOR REGISTRADO EXITOSAMENTE.\x1b[0m\n");

        investigadores[*cantidadInvestigadores] = nuevoInvestigador;
        (*cantidadInvestigadores)++;
        // Preguntar si quiere registrar otro investigador o volver al menú
        int opcionValida = 0;
        char opcionStr[10];
        while (!opcionValida) {
            printf("Presione 1 para registrar otro investigador, 2 para volver al men\243: ");
            fgets(opcionStr, sizeof(opcionStr), stdin);
            opcionStr[strcspn(opcionStr, "\n")] = 0;
            if (strcmp(opcionStr, "1") == 0 || strcmp(opcionStr, "2") == 0) {
                opcionValida = 1;
            } else {
                printf("\x1b[31mOpci\242n no v\240lida. Intente nuevamente.\x1b[0m\n");
            }
        }
        int opcion = atoi(opcionStr);
        switch (opcion) {
        case 1:
            continuar = 0;
            break;
        case 2:
            printf("Volviendo al men\243 principal...\n");
            registroCompleto = 1;
            break;
        }
    }
}

void mostrarInvestigadoresMayorExperiencia(investigador investigadores[], int cantidad) {
    int continuar = 1;
    int i;

    if (cantidad < 2) {
        printf("No hay suficientes investigadores registrados para mostrar los dos con mayor experiencia.\n");
        system("pause");
        continuar = 0; // Detener el flujo si no hay suficientes investigadores
    }
    if (continuar) {
        // Ordenar los investigadores por experiencia
        ordenarInvestigadoresPorExperiencia(investigadores, cantidad);
        // Mostrar los dos investigadores con mayor experiencia
        printf("\nInvestigadores con mayor experiencia:\n");
        for (i = 0; i < 2; i++) {
            printf("%d. %s con %d a\244os de experiencia\n", i + 1, investigadores[i].nombre, investigadores[i].experiencia);
        }
        system("pause");
    }
}

void mostrarInvestigadorMenosExperiencia(investigador investigadores[], int cantidad) {
    int continuar = 1;

    if (cantidad == 0) {
        printf("No hay investigadores registrados actualmente.\n");
        system("pause");
        continuar = 0;
    }

    if (continuar) {
        int menosExperienciaIndex = obtenerInvestigadorMenosExperiencia(investigadores, cantidad);

        printf("\nInvestigador con menos experiencia:\n");
        printf("Nombre: %s\n", investigadores[menosExperienciaIndex].nombre);
        printf("Experiencia: %d a\244os\n", investigadores[menosExperienciaIndex].experiencia);
        system("pause");
    }
}

void mostrarProyectosPorID(investigador investigadores[], int cantidad) {
    int i, j;
    investigador inv;
    int encontrado = 0;
    int continuar = 1;

    while (continuar) {
        printf("\nListado de ID:\n");
        for (i = 0; i < cantidad; i++) {
            printf("%d. %s\n", i + 1, investigadores[i].id);
        }
        printf("Ingrese el ID del investigador para ver sus proyectos: ");
        pedirID(&inv);  // Llamar a la función pedirID para obtener el ID
        // Buscar el investigador por ID
        encontrado = 0;
        for (i = 0; i < cantidad && !encontrado; i++) {
            if (strcmp(investigadores[i].id, inv.id) == 0) {
                encontrado = 1;
                printf("\nProyectos del investigador %s (ID: %s):\n", investigadores[i].nombre, investigadores[i].id);
                for (j = 0; j < 10 && investigadores[i].proyectos[j][0] != '\0'; j++) {
                    printf("- %s\n", investigadores[i].proyectos[j]);
                }
            }
        }
        if (!encontrado) {
            printf("Investigador con ID %s no encontrado.\n", inv.id);
        }
        // Finalizar el bucle después de mostrar los proyectos o un mensaje de error
        continuar = 0;
    }

    system("pause");
}

void mostrarInvestigadoresPorProyecto(investigador investigadores[], int cantidad){
    char proyectosUnicos[150][100];
    int numProyectos = obtenerProyectosUnicos(investigadores, cantidad, proyectosUnicos);
    int volverMenu = 0;
    int i, j;

    while (!volverMenu) {
        system("cls");
        printf("\nListado de Proyectos:\n");
        for (i = 0; i < numProyectos; i++) { //Recorre todos los proyectos únicos almacenados en proyectosUnicos y los muestra numerados (1, 2, 3, etc.)
            printf("%d. %s\n", i + 1, proyectosUnicos[i]);
        }
        printf("Ingrese el n\243mero del proyecto para ver los investigadores que participan en \202l (o presione '0' para volver al men\243): ");
        int numProyecto = obtenerEntradaNumerica();

        if (numProyecto == 0) {
            printf("Volviendo al men\243...\n");
            volverMenu = 1;
        } else if (numProyecto > 0 && numProyecto <= numProyectos) {
            printf("\nInvestigadores que participan en el proyecto %s:\n", proyectosUnicos[numProyecto - 1]);
            //Se recorre cada investigador y sus proyectos
            //Si el nombre del proyecto coincide con el proyecto seleccionado se imprime el nombre y el ID del investigador.
            for (i = 0; i < cantidad; i++) {
                for (j = 0; j < 10 && investigadores[i].proyectos[j][0] != '\0'; j++) {
                    if (strcmp(investigadores[i].proyectos[j], proyectosUnicos[numProyecto - 1]) == 0) {
                        printf("Investigador: %s (ID: %s)\n", investigadores[i].nombre, investigadores[i].id);
                    }
                }
            }
            system("pause");
            volverMenu = 1;
        } else {
            printf("\x1b[31mOpci\242n no v\240lida. Intente nuevamente.\x1b[0m\n");
            system("pause");
        }
    }
}

void mostrarInvestigadoresVeteranos(investigador investigadores[], int cantidad) {
    int i;
    int encontrado = 0;
    printf("\nInvestigadores con m\240s de 10 a\244os de experiencia:\n");
    for (i = 0; i < cantidad; i++) {
        if (investigadores[i].experiencia > 10) {
            printf("%s (ID: %s) con %d a\244os de experiencia\n", investigadores[i].nombre, investigadores[i].id, investigadores[i].experiencia);
            encontrado = 1;
        }
        if (!encontrado) {
            printf("No hay ning\243n investigador con más de 10 a\244os de experiencia.\n");
        }
    }
    system("pause");
}

void buscarInvestigadorPorNombre(investigador investigadores[], int cantidad) {
    investigador inv;
    int encontrado = 0;
    int i, j;
    pedirNombre(&inv); // Llamar a pedirNombre
    for (i = 0; i < cantidad && !encontrado; i++) {
        if (strcmp(investigadores[i].nombre, inv.nombre) == 0) {
            printf("\nInvestigador encontrado:\n");
            printf("ID: %s\n", investigadores[i].id);
            printf("Nombre: %s\n", investigadores[i].nombre);
            printf("Edad: %d\n", investigadores[i].edad);
            printf("Experiencia: %d a\244os\n", investigadores[i].experiencia);
            printf("Proyectos:\n");

            for (j = 0; j < 10 && investigadores[i].proyectos[j][0] != '\0'; j++) {
                printf("- %s\n", investigadores[i].proyectos[j]);
            }
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontr\243 ning\243n investigador con ese nombre.\n");
    }
    system("pause");
}

void buscarInvestigadorPorID(investigador investigadores[], int cantidad) {
    investigador inv;
    int encontrado = 0;
    int i,j;
    pedirID(&inv);
    for (i = 0; i < cantidad && !encontrado; i++) {
        if (strcmp(investigadores[i].id, inv.id) == 0) {
            printf("\nInvestigador encontrado:\n");
            printf("ID: %s\n", investigadores[i].id);
            printf("Nombre: %s\n", investigadores[i].nombre);
            printf("Edad: %d\n", investigadores[i].edad);
            printf("Experiencia: %d a\244os\n", investigadores[i].experiencia);
            printf("Proyectos:\n");

            for (j = 0; j < 10 && investigadores[i].proyectos[j][0] != '\0'; j++) {
                printf("- %s\n", investigadores[i].proyectos[j]);
            }
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontr\242 ning\243n investigador con ese ID.\n");
    }
    system("pause");
}

void eliminarProyecto(investigador *inv) {
    int i;
    int proyectoSeleccionado;
    int numProyectos = 0;
    int continuar = 1;

    while (continuar) {
        system("cls");
        printf("\nProyectos de %s:\n", inv->nombre);
        for (i = 0; i < 10 && inv->proyectos[i][0] != '\0'; i++) {
            printf("%d. %s\n", i + 1, inv->proyectos[i]);
            numProyectos++;
        }
        printf("%d. Volver al men\243\n", numProyectos + 1);
        printf("Seleccione un proyecto para eliminar (o %d para volver): ", numProyectos + 1);
        proyectoSeleccionado = obtenerEntradaNumerica();

        if (proyectoSeleccionado >= 1 && proyectoSeleccionado <= numProyectos) {
            for (i = proyectoSeleccionado - 1; i < numProyectos - 1; i++) {
                strcpy(inv->proyectos[i], inv->proyectos[i + 1]);
            }
            inv->proyectos[numProyectos - 1][0] = '\0';
            printf("\x1b[32mProyecto eliminado exitosamente.\x1b[0m\n");
            system("pause");
            continuar = 0;
        } else if (proyectoSeleccionado == numProyectos + 1) {
            printf("Volviendo al men\243...\n");
            continuar = 0;
        } else {
            printf("\x1b[31mOpci\242n inv\240lida. Intente nuevamente.\x1b[0m\n");
            system("pause");
        }
    }
}

void eliminarInvestigador(investigador investigadores[], int *cantidadInvestigadores) {
    int seleccion;
    int encontrado = 0;
    int i;
    int continuar = 1;

    while (continuar) {
        system("cls");
        printf("\nLista de Investigadores:\n");
        for (i = 0; i < *cantidadInvestigadores; i++) {
            printf("%d. %s\n", i + 1, investigadores[i].nombre);
        }
        printf("%d. Volver al men\243\n", *cantidadInvestigadores + 1);
        printf("Seleccione un investigador para eliminar (o %d para volver): ", *cantidadInvestigadores + 1);
        seleccion = obtenerEntradaNumerica();

        if (seleccion >= 1 && seleccion <= *cantidadInvestigadores) {
            encontrado = 1;
            for (i = seleccion - 1; i < *cantidadInvestigadores - 1; i++) {
                investigadores[i] = investigadores[i + 1];
            }
            (*cantidadInvestigadores)--;
            printf("\x1b[32mInvestigador eliminado exitosamente.\x1b[0m\n");
            system("pause");
            continuar = 0;
        } else if (seleccion == *cantidadInvestigadores + 1) {
            printf("Volviendo al men\243...\n");
            continuar = 0;
        } else {
            printf("\x1b[31mOpci\242n inv\240lida. Intente nuevamente.\x1b[0m\n");
            system("pause");
        }
    }
}

void mostrarTotalInvestigadores(int cantidadInvestigadores) {
    system("cls");
    if (cantidadInvestigadores > 0) {
        printf("\nTotal de Investigadores Registrados:\n");
        printf("Hay %d investigadores registrados en el sistema.\n", cantidadInvestigadores);
    } else {
        printf("No hay investigadores registrados actualmente.\n");
    }
    system("pause");
}

void mostrarPromedioEdad(investigador investigadores[], int cantidad) {
    float promedioEdad = calcularPromedioEdad(investigadores, cantidad);
    if (promedioEdad == -1) {
        printf("No hay investigadores registrados actualmente.\n");
    } else {
        printf("\nPromedio de edad de los investigadores: %.2f a\244os\n", promedioEdad);
    }
    system("pause");
}

void mostrarPromedioExperiencia(investigador investigadores[], int cantidad) {
    float promedioExperiencia = calcularPromedioExperiencia(investigadores, cantidad);
    if (promedioExperiencia == -1) {
        printf("No hay investigadores registrados actualmente.\n");
    } else {
        printf("\nPromedio de experiencia de los investigadores: %.2f a\244os\n", promedioExperiencia);
    }
    system("pause");
}

void mostrarInvestigadorMasJoven(investigador investigadores[], int cantidad) {
    int continuar = 1;

    if (cantidad == 0) {
        printf("No hay investigadores registrados.\n");
        continuar = 0;
    }

    if (continuar) {
        int masJovenIndex = obtenerInvestigadorMasJoven(investigadores, cantidad);

        printf("\nInvestigador m\240s joven:\n");
        printf("Nombre: %s\n", investigadores[masJovenIndex].nombre);
        printf("Edad: %d a\244os\n", investigadores[masJovenIndex].edad);
    }
    system("pause");
}

void mostrarInvestigadorMasViejo(investigador investigadores[], int cantidad) {
    int continuar = 1;

    if (cantidad == 0) {
        printf("No hay investigadores registrados.\n");
        system("pause");
        continuar = 0;
    }

    if (continuar) {
        int masViejoIndex = obtenerInvestigadorMasViejo(investigadores, cantidad);

        printf("\nEl investigador m\240s viejo es: %s\n", investigadores[masViejoIndex].nombre);
        printf("Edad: %d a\244os\n", investigadores[masViejoIndex].edad);
        system("pause");
    }
}
