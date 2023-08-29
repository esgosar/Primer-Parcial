// Programa para un profesor que quiere llevar un registro de las notas de sus estudiantes.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Dado que no se especifica el número de materias, arbitrareamente se estabelcen 5.
#define MATERIAS 5

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
    FILE *archivo;
    char estudiante[50]; // Ejemmplo:  José Estuardo González Sarceño
    char materias[MATERIAS][50]; 
    float notas[MATERIAS];       

    // El programa deberá desplegar un menú para seleccionar la opción a realiazar.
    while (1)
    {
        int option;
        
        interface("REGISTRO DE NOTAS", "1) Registrar nuevo estudiante y sus notas\n2) Ver historial de notas.\n3) Borrar historial de notas.\n4) Salir");
        scanf("%i", &option);
        clean(1);
         
        switch (option)
        {
            case 1:
            {
                // El programa debe solicitar el nombre del estudiante
                interface("REGISTRO DE NOTAS", "Ingrese el nombre del estudiante");

                // La función scanf() causa problemas al leer espacios en este caso específico. Usar getchar()
                scanf("%s", estudiante); 
                //fgets(estudiante, 49, stdin);
                archivo = fopen("salida.txt", "a"); // Abrir archivo en modo "append"
                if (archivo == NULL)
                {
                    printf("No se pudo abrir el archivo para escribir.\n");
                    return 1; // Salir del programa con código de error
                }
                fprintf(archivo, "\n\nAlumno: %s\n\nMATERIA\t\t\t\tNOTA\n---------------------------------------\n", estudiante);

                // ...el nombre de las materias
                interface("REGISTRO DE NOTAS", "Ingrese el nombre de las materias");

                for (int i = 0; i < MATERIAS; i++)
                {
                    printf("%d: ", i + 1);
                    scanf("%s", materias[i]);
                }
                

                // ... y la nota correspondiente a cada materia
                for (int i = 0; i < MATERIAS; i++)
                {
                    while (1)
                    {
                        interface("REGISTRO DE NOTAS", "Ingrese la nota de cada materia");
                        for (int j = 0; j < i; j++) printf("%s: %.2f\n", materias[j], notas[j]);

                        printf("%s: ", materias[i]);
                        scanf("%f", &notas[i]);

                        if (notas[i] < 0 || notas[i] > 100)
                        {
                            printf("\nError: Introduzca una cantidad en el rango de 0 a 100.\n");
                            clean(3);

                        } else break;
                    }
                }

                // Posteriormente se calculará el promedio de las notas
                float sumatoria;
                float promedio;

                for (int i = 0; i < MATERIAS; i++) sumatoria += notas[i];
                promedio = sumatoria / MATERIAS;
                printf("Promedio = %.2f\n", promedio);
                clean(2);

                // Las notas se guardarán en un archivo de texto
                for (int i = 0; i < MATERIAS; i++) fprintf(archivo, "%s\t\t\t\t\t%.2f\n", materias[i], notas[i]);
                fclose(archivo);
            }
            break;
            case 2:
            {
                int c;
                archivo = fopen("salida.txt", "r");

                if (archivo == NULL)
                {
                    printf("No se pudo abrir el archivo para escribir.\n");
                    return 1; // Salir del programa con código de error
                }
                while (1)
                {
                    c = fgetc(archivo); // asignar caracteres a la variable
                    if (feof(archivo)) break; // Al encontrar fin de archivo se sale
                    printf("%c", c);
                }
                fclose(archivo);
                sleep(4);
            }
            break;
            case 3:
            {
                archivo  = fopen("salida.txt", "w");
                fclose(archivo);
            }
            break;
            case 4:
            {
                exit(0);
                break;
            }
            default:
            {
                printf("Introduzca una opcion del 1 al 4.");
                break;
            }
        }
    }

    return 0;
}