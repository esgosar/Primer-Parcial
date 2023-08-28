// Juego simulado del Gran 8

#include <stdio.h> // Input/Output
#include <stdlib.h> // system()
#include <unistd.h> // File Management
#include <stdbool.h> // Bool values
#include <math.h>


// Almacenar los datos en un archivo de texto con nombre: "salida.txt"
// Agregar la opción de poder visualizar los datos.

void clean(int seconds)
{
    sleep(seconds);
    system("clear");
}

void interface(char *title, char *instruction)
{
    clean(0);
    printf("\n%s\n", title);
    printf("%s\n", instruction);
    printf("\n------------------------------------------------------------\n");
}

int main()
{
    int primero;
    int segundo;
    int option;
    FILE *archivo = fopen("salida.txt", "a");

    while(1)
    {
        //Debes lanzar un par de dados.
        interface("GRAN 8 SIMULADOR", "Introduzca el número de cada dado");
        printf("Primer dado: ");
        scanf("%i", &primero);
        printf("Segundo dado: ");
        scanf("%i", &segundo);
        
        if ((primero + segundo) == 8)
        {
            printf("Ganas! Fin del juego\n"); //Si la suma de las caras es un 8, ganas
            // Almacenar los datos en el archivo automáticamente
            fprintf(archivo, "Primer dado: %i, Segundo dado: %i, Resultado: Gana\n", primero, segundo);
            while(option != 1 && option != 2)
            {
                interface("Fin del Juego", "¿Qué desea hacer?\n1) Visualizar mis datos\n2) Salir del juego");
                scanf("%i", &option);

                if (option == 1)
                {
                    printf("Resultados:\n");
                    fseek(archivo, 0, SEEK_SET); // Regresar al inicio del archivo antes de leer
                    char linea[240]; // Variable para almacenar una línea del archivo
                    while (fgets(linea, sizeof(linea), archivo) && getchar() != '\n')
                    {
                        printf("%s", linea);
                    } // Imprimir la línea leída
                    fclose(archivo); // Cerrar archivo después de leer
                    clean(5);
                }
                else if (option == 2)
                {
                    break;
                }
            }
            break;
        }
        else if ((primero + segundo) == 7)
        {
            printf("Pierdes Fin del juego\n"); // Si sale 7, pierdes.
            // Almacenar los datos en el archivo automáticamente
            fprintf(archivo, "Primer dado: %i, Segundo dado: %i, Resultado: Pierde\n", primero, segundo);

            while(1)
            {
                interface("Fin del Juego", "¿Qué desea hacer?\n1) Visualizar mis datos\n2) Salir del juego");
                scanf("%i", &option);

                if (option != 1 && option != 2)
                {
                    printf("Resultados:\n");
                    fseek(archivo, 0, SEEK_SET); // Regresar al inicio del archivo antes de leer
                    char linea[240]; // Variable para almacenar una línea del archivo
                    while (fgets(linea, sizeof(linea), archivo) && getchar() != '\n')
                    {
                        printf("%s", linea);  // Imprimir la línea leída
                    }
                    fclose(archivo); // Cerrar archivo después de leer
                    clean(5);
                }
                else if (option == 2)
                {
                    break;
                }
            }
            break;
        }
        
        printf("Pierdes Fin del juego\n"); // Si sale 7, pierdes.
        // Almacenar los datos en el archivo automáticamente
        fprintf(archivo, "Primer dado: %i, Segundo dado: %i, Resultado: Vulve a jugar\n", primero, segundo);        
        clean(0);
        printf("Vuelve a tirar");
    }

    return 0;
}

