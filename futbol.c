#include <stdio.h>
#include <string.h>

void intercambiarNombres(char nombre1[], char nombre2[]) {
    char temp[50]; 
    strcpy(temp, nombre1);
    strcpy(nombre1, nombre2);
    strcpy(nombre2, temp);
}

int nombreRepetido(char nombre[], char nombres[][50], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(nombre, nombres[i]) == 0) {
            return 1; 
        }
    }
    return 0; 
}

int validarResultadoPartido(char mensaje[], char equipo[]) {
    int goles = -1; 
    char entrada[100]; 
    int n_items_escaneados; 

    do {
        printf(mensaje, equipo); 

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Error al leer la entrada.\n");
            continue;
        }

        n_items_escaneados = sscanf(entrada, "%d", &goles);

        if (n_items_escaneados != 1) {
            printf("Entrada no válida. Debe ingresar un número entero.\n");
            goles = -1; 
        } else if (goles < 0) {
            printf("Los goles no pueden ser negativos. Intente de nuevo.\n");
        }

    } while (n_items_escaneados != 1 || goles < 0);

    return goles;
}

void consumirLineaRestante() {
    int c;
    while ((c = getchar()) != '\n');
}

int main() {
    char equipos[4][50];       
    int puntos[4];             
    int golesFavor[4];          
    int golesContra[4];       
    int golDiferencia[4];     
    int resultado1, resultado2; 
    char opcion;                

    do {
        for(int i=0; i<4; ++i) {
            puntos[i] = 0;
            golesFavor[i] = 0;
            golesContra[i] = 0;
            golDiferencia[i] = 0;
            strcpy(equipos[i], ""); 
        }

        printf("--- Registro de Equipos (Cuadrangular de Futbol) ---\n");

        for (int i = 0; i < 4; i++) {
            printf("\nEquipo #%d\n", i + 1);
            do {
                printf("Nombre del equipo: ");
                if (fgets(equipos[i], sizeof(equipos[i]), stdin) == NULL) {
                    printf("Error al leer el nombre del equipo.\n");
                    return 1; 
                }

                equipos[i][strcspn(equipos[i], "\n")] = '\0';

                if (nombreRepetido(equipos[i], equipos, i)) {
                    printf("Error, el nombre '%s' ya fue ingresado. Use uno diferente.\n", equipos[i]);
                }
            } while (nombreRepetido(equipos[i], equipos, i));
        }

        printf("\n--- Ingreso de Resultados de Partidos ---\n");
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                printf("\n--- Partido: %s vs %s ---\n", equipos[i], equipos[j]);
                resultado1 = validarResultadoPartido("Goles de %s: ", equipos[i]);
                resultado2 = validarResultadoPartido("Goles de %s: ", equipos[j]);

                golesFavor[i] += resultado1;
                golesFavor[j] += resultado2;
                golesContra[i] += resultado2;
                golesContra[j] += resultado1;

                if (resultado1 > resultado2) {
                    puntos[i] += 3; 
                } else if (resultado1 < resultado2) {
                    puntos[j] += 3; 
                } else {
                    puntos[i] += 1; 
                    puntos[j] += 1; 
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            golDiferencia[i] = golesFavor[i] - golesContra[i];
        }

        for (int i = 0; i < 3; i++) { 
            for (int j = i + 1; j < 4; j++) { 

                if (puntos[i] < puntos[j] || (puntos[i] == puntos[j] && golDiferencia[i] < golDiferencia[j])) {

                    int temp_puntos = puntos[i];
                    puntos[i] = puntos[j];
                    puntos[j] = temp_puntos;

                    int temp_gf = golesFavor[i];
                    golesFavor[i] = golesFavor[j];
                    golesFavor[j] = temp_gf;

                    int temp_gc = golesContra[i];
                    golesContra[i] = golesContra[j];
                    golesContra[j] = temp_gc;

                    int temp_gd = golDiferencia[i];
                    golDiferencia[i] = golDiferencia[j];
                    golDiferencia[j] = temp_gd;

                    intercambiarNombres(equipos[i], equipos[j]);
                }
            }
        }

        printf("\n\n--- Tabla de posiciones final ---\n");
        printf("| %-3s | %-20s | %-4s | %-3s | %-3s | %-3s |\n", "Pos", "Equipo", "Pts", "GF", "GC", "GD");
        printf("|-----|----------------------|------|-----|-----|-----|\n"); 
        for (int i = 0; i < 4; i++) {
             printf("| %-3d | %-20s | %4d | %3d | %3d | %3d |\n",
                   i + 1,              
                   equipos[i],         
                   puntos[i],           
                   golesFavor[i],        
                   golesContra[i],      
                   golDiferencia[i]      
                   );
        }
        printf("|-----|----------------------|------|-----|-----|-----|\n"); 
        printf("\n");
        printf("  Pasa en (1er lugar): %s\n", equipos[0]); 
        printf("  Pasa en (2do lugar): %s\n", equipos[1]); 
        printf("\n");

        int valido = 0; 
        do {
            printf("\nDesea registrar otro cuadrangular? (1 para sí, 0 para no): ");
            if (scanf("%d", &opcion) != 1 || (opcion != 0 && opcion != 1)) {
                printf("Opción no válida. Debe ingresar 1 para sí o 0 para no.\n");
                consumirLineaRestante(); 
            } else {
                valido = 1; 
            }
        } while (!valido);

        consumirLineaRestante(); 

    } while (opcion == 1);

    printf("\nGracias por usar el sistema de cuadrangular de futbol. Lindo día\n");

    return 0; 
}
