#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    float precio;
    int option;
    FILE *archivo;

    archivo = fopen("salida.txt", "a"); // Abrir archivo en modo "append"
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return 1; // Salir del programa con código de error
    }
    fprintf(archivo, "\n\nPrecio Original\tPrecio sin IVA\tIVA\n");

    while (1) {
        interface("CALCULADOR IVA GT", "1) Añadir nuevo calculo \n2) Ver historial de datos\n3) Salir");
        scanf("%d", &option);
        clean(1);

        if (option == 1)
        {
            // Ingrese un precio en quetzales
            interface("CALCULADOR IVA GT", "Ingrese el precio en quetzales");
            scanf("%f", &precio);
            clean(0);
            printf("Del total Q %.2f GTQ son de IVA\nEl precio sin IVA es de : Q %2.f GTQ\n", precio * .12, precio * .88);
            clean(2);
            fprintf(archivo, "%f\t%f\t%f\n", precio, precio * .88, precio * .12);
            fclose(archivo); // Close the file after writing
        }
        else if (option == 2)
        {
            int c;
            archivo = fopen("salida.txt", "r");

            if (archivo == NULL)
            {
                printf("No se pudo abrir el archivo para leer.\n");
                return 1; // Salir del programa con código de error
            }

            while (1)
            {
                c = fgetc(archivo);
                if (feof(archivo)) break;
                printf("%c", c);
            }
            fclose(archivo);
            sleep(4);
        }
        else if (option == 3)
        {
            exit(0);
        }
    }
    return 0;
}
