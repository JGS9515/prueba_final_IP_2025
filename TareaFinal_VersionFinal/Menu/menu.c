#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <Menu/menu.h>
#include <Interfaz/interfaz.h>
#include <stdlib.h>
#include <Logica/datos.h>
#include <Logica/logica.h>

void mostrarMenuPrincipal(investigador investigadores[], int *cantidadInvestigadores) {
    int opcion;
    int datos = 0;
    int continuar = 1;
    while (continuar) {
        system("cls");
        printf("=======================SISTEMA DE CONTROL DEL PERSONAL=======================\n");
        printf("Men\243 Principal:\n");
        printf("1. Registro de Investigadores\n");
        printf("2. Mostrar datos de los investigadores\n");
        printf("3. Men\243 de reportes de los investigadores\n");
        printf("4. B\243squeda de investigadores\n");
        printf("5. Actualizar Registro de Investigadores\n");
        printf("6. Mostrar total de investigadores\n");
        printf("7. Salir del programa\n");
        printf("Seleccione una opci\242n: ");
        opcion = obtenerEntradaNumerica();

        switch (opcion) {
        case 1:
            mostrarMenuRegistro(investigadores, cantidadInvestigadores);
            datos = 1;
            break;
        case 2:
            if (datos) {
                mostrarMenuMostrarDatos(investigadores, *cantidadInvestigadores);
            } else {
                printf("Los datos no han sido inicializados.\n");
                system("pause");
            }
            break;
        case 3:
            if (datos) {
                mostrarMenuReportes(investigadores, *cantidadInvestigadores);
            } else {
                printf("Los datos no han sido inicializados.\n");
                system("pause");
            }
            break;
        case 4:
            if (datos) {
                mostrarMenuBusqueda(investigadores, *cantidadInvestigadores);
            } else {
                printf("Los datos no han sido inicializados.\n");
                system("pause");
            }
            break;
        case 5:
            if (datos) {
                mostrarMenuActualizarRegistro(investigadores, cantidadInvestigadores);
            } else {
                printf("Los datos no han sido inicializados.\n");
                system("pause");
            }
            break;
        case 6:
            mostrarTotalInvestigadores(*cantidadInvestigadores);
            break;
        case 7:
            printf("Saliendo del programa...\n");
            continuar = 0;  // Salir del bucle
            break;
        default:
            printf("\x1b[31mOpci\242n inv\240lida. Intente nuevamente.\x1b[0m \n");
            system("pause");
            break;
        }
    }
}

void mostrarMenuRegistro(investigador investigadores[], int *cantidadInvestigadores) {
    int opcion;
    int inicializado;
    bool datos = false;
    do {
        system("cls");
        printf("\nRegistro de Investigadores:\n");
        printf("1. Registrar manualmente\n");
        printf("2. Inicializar autom\240ticamente\n");
        printf("3. Volver al men\243 principal\n");
        printf("Seleccione una opci\242n: ");
        opcion = obtenerEntradaNumerica();
        switch (opcion) {
        case 1:
            registrarInvestigadores(investigadores, cantidadInvestigadores);
            break;
        case 2:
            if(*cantidadInvestigadores == 0){
                inicializarInvestigadoresAutomaticamente(investigadores, cantidadInvestigadores);
                printf("\x1b[32mLos datos han sido inicializados con \202xito\x1b[0m\n");
                system("pause");
            }
            else if (*cantidadInvestigadores > 0){
                printf("Ya hay investigadores registrados.\n");
                system("pause");
                inicializado = 1;
            }
            datos = true;
            break;
        case 3:
            printf("Volviendo al men\243...\n");
            break;
        default:
            printf("\x1b[31mOpci\242n inv\240lida. Intente nuevamente.\x1b[0m \n");
            system("pause");
        }
    } while (opcion != 3);
}

void mostrarMenuMostrarDatos(investigador investigadores[], int cantidad) {
    int opcion, i, j;
    int salir = 0;  // Variable de control para salir del bucle

    if (cantidad == 0) {
        printf("Debe registrar a los investigadores primero.\n");
        system("pause");
        salir = 1;  // Establecer la variable de control para salir
    }
    while (!salir) {
        system("cls");
        printf("\nMostrar datos de los investigadores:\n");
        printf("1. Datos de cada investigador\n");
        printf("2. Listado de nombres\n");
        printf("3. Listado de ID\n");
        printf("4. Listado de proyectos\n");
        printf("5. Volver al men\243 principal\n");
        printf("Seleccione una opci\242n: ");
        opcion = obtenerEntradaNumerica();
        switch (opcion) {
        case 1:
            printf("\nDatos de cada Investigador:\n");
            for (i = 0; i < cantidad; i++) {
                printf("\nInvestigador %d:\n", i + 1);
                printf("ID: %s\n", investigadores[i].id);
                printf("Nombre: %s\n", investigadores[i].nombre);
                printf("Edad: %d\n", investigadores[i].edad);
                printf("Experiencia: %d a\244os\n", investigadores[i].experiencia);
                printf("Proyectos:\n");
                for (j = 0; j < 10 && investigadores[i].proyectos[j][0] != '\0'; j++) {
                    printf("- %s\n", investigadores[i].proyectos[j]);
                }
            }
            system("pause");
            break;
        case 2:
            printf("\nListado de nombres:\n");
            for (i = 0; i < cantidad; i++) {
                printf("%d. %s\n", i + 1, investigadores[i].nombre);
            }
            system("pause");
            break;
        case 3:
            printf("\nListado de ID:\n");
            for (i = 0; i < cantidad; i++) {
                printf("%d. %s\n", i + 1, investigadores[i].id);
            }
            system("pause");
            break;
        case 4:
            printf("\nListado de proyectos con sus investigadores:\n");
            for (i = 0; i < cantidad; i++) {
                printf("INVESTIGADOR: %s \n", investigadores[i].nombre);
                printf("PROYECTOS: \n");
                for (j = 0; j < 10 && investigadores[i].proyectos[j][0] != '\0'; j++) {
                    printf("- %s\n", investigadores[i].proyectos[j]);
                }
                printf("\n");
            }
            system("pause");
            break;
        case 5:
            printf("Volviendo al men\243...\n");
            salir = 1;  // Establecer la variable de control para salir
            system("pause");
            break;
        default:
            printf("\x1b[31mOpci\242n inv\240lida. Intente nuevamente.\x1b[0m \n");
            system("pause");
        }
    }
}

void mostrarMenuReportes(investigador investigadores[], int cantidad) {
    int opcion;
    do {
        system("cls");
        printf("\nReportes de los investigadores:\n");
        printf("1. Investigadores con mayor experiencia\n");
        printf("2. Proyectos de cada investigador a partir del ID\n");
        printf("3. Listado de nombres de investigadores que participan en cada proyecto\n");
        printf("4. Investigadores con m\240s de 10 a\244os de experiencia\n");
        printf("5. Investigador con menos experiencia\n");
        printf("6. Promedio de edad de los investigadores\n");
        printf("7. Promedio de experiencia de los investigadores\n");
        printf("8. Investigador m\240s joven\n");
        printf("9. Investigador m\240s viejo\n");
        printf("0. Volver al men\243\n");
        printf("Seleccione una opci\242n: ");
        opcion = obtenerEntradaNumerica();
        if (cantidad == 0 && opcion != 0) {
            printf("Primero debe inicializar los datos.\n");
            system("pause");
        } else {
            switch (opcion) {
            case 1:
                mostrarInvestigadoresMayorExperiencia(investigadores, cantidad);
                break;
            case 2:
                mostrarProyectosPorID(investigadores, cantidad);
                break;
            case 3:
                mostrarInvestigadoresPorProyecto(investigadores, cantidad);
                break;
            case 4:
                mostrarInvestigadoresVeteranos(investigadores, cantidad);
                break;
            case 5:
                mostrarInvestigadorMenosExperiencia(investigadores, cantidad);
                break;
            case 6:
                mostrarPromedioEdad(investigadores, cantidad);
                break;
            case 7:
                mostrarPromedioExperiencia(investigadores, cantidad);
                break;
            case 8:
                mostrarInvestigadorMasJoven(investigadores, cantidad);
                break;
            case 9:
                mostrarInvestigadorMasViejo(investigadores, cantidad);
                break;
            case 0:
                printf("Volviendo al men\243...\n");
                system("pause");
                break;
            default:
                printf("\x1b[31mOpci\242n inv\240lida. Intente nuevamente.\x1b[0m \n");
                system("pause");
            }
        }
    } while (opcion != 0);
}

void mostrarMenuBusqueda(investigador investigadores[], int cantidadInvestigadores) {
    int opcion;
    int continuar = 1;
    while (continuar) {
        system("cls");
        printf("\nB\243squeda de Investigadores:\n");
        printf("1. Buscar por nombre\n");
        printf("2. Buscar por ID\n");
        printf("3. Volver al men\243 principal\n");
        printf("Seleccione una opci\242n: ");
        opcion = obtenerEntradaNumerica();
        if (opcion == 1) {
            buscarInvestigadorPorNombre(investigadores, cantidadInvestigadores);
        } else if (opcion == 2) {
            buscarInvestigadorPorID(investigadores, cantidadInvestigadores);
        } else if (opcion == 3) {
            printf("Volviendo al men\243 principal...\n");
            continuar = 0;
        } else {
            printf("\x1b[31mOpci\242n inv\240lida. Intente nuevamente.\x1b[0m\n");
            system("pause");
        }
    }
}

void mostrarMenuActualizarRegistro(investigador investigadores[], int *cantidadInvestigadores) {
    int opcion;
    int continuar = 1;

    while (continuar) {
        system("cls");
        printf("\nActualizar Registro de Investigadores:\n");
        printf("1. Actualizar Datos de Investigador\n");
        printf("2. Eliminar Investigador\n");
        printf("3. Volver al men\243 principal\n");
        printf("Seleccione una opci\242n: ");
        opcion = obtenerEntradaNumerica();

        switch (opcion) {
        case 1:
            actualizarDatosInvestigador(investigadores, *cantidadInvestigadores);
            break;
        case 2:
            eliminarInvestigador(investigadores, cantidadInvestigadores);
            break;
        case 3:
            printf("Volviendo al men\243 principal...\n");
            continuar = 0;
            break;
        default:
            printf("\x1b[31mOpci\242n inv\240lida. Intente nuevamente.\x1b[0m\n");
            system("pause");
        }
    }
}

void actualizarDatosInvestigador(investigador investigadores[], int cantidadInvestigadores) {
    int seleccion;
    int encontrado = 0;
    int i;
    int continuar = 1;

    while (continuar) {
        system("cls");
        printf("\nLista de Investigadores:\n");
        for (i = 0; i < cantidadInvestigadores; i++) {
            printf("%d. %s\n", i + 1, investigadores[i].nombre);
        }
        printf("%d. Volver al men\243\n", cantidadInvestigadores + 1);
        printf("Seleccione un investigador para actualizar (o %d para volver): ", cantidadInvestigadores + 1);
        seleccion = obtenerEntradaNumerica();

        if (seleccion >= 1 && seleccion <= cantidadInvestigadores) {
            encontrado = 1;
            investigador *inv = &investigadores[seleccion - 1];

            int subOpcion;
            int subContinuar = 1;
            while (subContinuar) {
                system("cls");
                printf("\nActualizar Datos de %s:\n", inv->nombre);
                printf("1. Actualizar Edad\n");
                printf("2. Actualizar Experiencia\n");
                printf("3. A\244adir Proyecto\n");
                printf("4. Eliminar Proyecto\n");
                printf("5. Volver al men\243\n");
                printf("Seleccione una opci\242n: ");
                subOpcion = obtenerEntradaNumerica();

                switch (subOpcion) {
                case 1:
                    pedirEdad(inv);
                    system("pause");
                    system("cls");
                    break;
                case 2:
                    pedirExperiencia(inv);
                    system("pause");
                    system("cls");
                    break;
                case 3:
                    pedirProyectos(inv);
                    printf("\x1b[32mProyectos actualizados con \202xito\x1b[0m\n");
                    system("pause");
                    system("cls");
                    break;
                case 4:
                    eliminarProyecto(inv);
                    break;
                case 5:
                    printf("Volviendo al men\243...\n");
                    subContinuar = 0;
                    system("pause");
                    system("cls");
                    break;
                default:
                    printf("\x1b[31mOpci\242n inv\240lida. Intente nuevamente.\x1b[0m\n");
                    system("pause");
                    system("cls");
                }
            }
        } else if (seleccion == cantidadInvestigadores + 1) {
            printf("Volviendo al men\243...\n");
            continuar = 0;
        } else {
            printf("\x1b[31mOpci\242n inv\240lida. Intente nuevamente.\x1b[0m\n");
            system("pause");
        }
    }
}
