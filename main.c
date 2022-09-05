#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE  1
#define FALSE 2

typedef struct Directorio
{
	int id;
	int estado; 
	char *nombres;
	char *apellidos;
	char *numero;
	char *RFC;
	int cont_empleos;
	char **empleos;
}Directorio;

void _fflush(void); // Versión personalizada del fflush(stdin);
void delay(int); // Versión personalizada de Sleep(int); / sleep(int);
void crearDirectorio(Directorio*);
void mostrarDirectorio(Directorio*);
void modificarDirectorio(Directorio*);
void eliminarDirectorio(Directorio*);
void liberarMemoria(Directorio*);

void main(void)
{
	Directorio dir;
	dir.estado = FALSE;
	int opc, ciclo = TRUE;
	
	do{
		system("clear");

		printf("\n\t..::DIRECTORIO::..\n\n");
		printf("1) Crear directorio.\n");
		printf("2) Mostrar directorio.\n");
		printf("3) Modificar directorio.\n");
		printf("4) Eliminar directorio.\n");
		printf("0) Salir.\n");
		printf(">>> ");
		scanf("%d", &opc);
		_fflush();

		switch(opc)
		{
			case 1:
				delay(1000);
				crearDirectorio(&dir);
				_fflush();
				break;
			case 2:
				delay(1000);
				mostrarDirectorio(&dir);
				_fflush();
				break;
			case 3:
				delay(1000);
				modificarDirectorio(&dir);
				_fflush();
				break;
			case 4:
				delay(1000);
				eliminarDirectorio(&dir);
				_fflush();
				break;
			case 0:
				liberarMemoria(&dir);
				delay(1000);
				printf("Saliendo\n");
				ciclo = FALSE;
				break;
			default:
				printf("Opcion inglresada no valida. (MENU)\n");
				break;
		}
	}while(ciclo != FALSE);
}

void _fflush(void)
{
    int c;
    
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void delay(int seconds)
{
	// Convirtiendolo en milisegundos
    int milli_seconds = 1000 * seconds;
    // Guardando el tiempo de inicio
    clock_t start_time = clock();
    // Ciclo hasta que no se alcance el tiempo requerido
    while (clock() < start_time + milli_seconds)
       	;
}

void crearDirectorio(Directorio *directorio)
{
	int i;

	directorio->nombres = (char*)malloc(sizeof(char)); 
	directorio->apellidos = (char*)malloc(sizeof(char)); 
	directorio->numero = (char*)malloc(sizeof(char)); 
	directorio->RFC = (char*)malloc(sizeof(char)); 

	system("clear");
	printf("\n\t..::CREAR::..\n\n");	
	printf("ID: ");
	scanf("%d", &directorio->id);
	printf("Nombre: ");
	scanf("%s", directorio->nombres);
	printf("Apellido: ");
	scanf("%s", directorio->apellidos);
	printf("Numero: ");
	scanf("%s", directorio->numero);
	printf("RFC: ");
	scanf("%s", directorio->RFC);
	printf("Cantidad de empleos: ");
	scanf("%d", &directorio->cont_empleos);

	directorio->empleos = (char**)malloc(sizeof(char*));
	for(i = 0; i < directorio->cont_empleos; i++)
	{
		*(directorio->empleos + i) = (char*)malloc(sizeof(char));
		printf("Empleo No.%d: ", i);
		scanf("%s", *(directorio->empleos + i));	
	}

	directorio->estado = TRUE;
}

void mostrarDirectorio(Directorio *directorio)
{
	// dir.empleos = (char *[]){"uno", "dos"};
	// printf ("%s", &(*dir.empleos)[0]); 
	system("clear");
	
	if(directorio->estado == FALSE)
	{
		printf("\n\tNo existe el directorio. (MOSTRAR)\n\n");
	}
	else
	{
		printf("\n\t..::MOSTRAR::..\n\n");
		printf("ID: %d\n", directorio->id);
		printf("Nombre: %s\n", directorio->nombres);
		printf("Apellido: %s\n", directorio->apellidos);
		printf("Numero: %s\n", directorio->numero);
		printf("RFC: %s\n", directorio->RFC);
		
		printf("Empleos:\n");
		for(int i = 0; i < directorio->cont_empleos; i++) 
			printf("[%i]: %s\n", i, *(directorio->empleos + i));
	}
}

void modificarDirectorio(Directorio *directorio)
{
	int opc, opc_empleos;

	system("clear");
	printf("\n\t..::MODIFICAR::..\n\n");
	printf("1) Nombres.\n");
	printf("2) Apellidos.\n");
	printf("3) Numero.\n");
	printf("4) RFC.\n");
	printf("5) Modificar Empleos.\n");
	printf(">>> ");
	scanf("%d", &opc);
	_fflush();

	switch(opc)
	{
		case 1:
			printf("Nuevo nombre: ");
			scanf("%s", directorio->nombres);
			break;
		case 2:
			printf("Nuevo apellido: ");
			scanf("%s", directorio->apellidos);
			break;
		case 3:
			printf("Nuevo numero: ");
			scanf("%s", directorio->numero);
			break;
		case 4:
			printf("Nuevo RFC: ");
			scanf("%s", directorio->RFC);
			break;
		case 5:
		{
			system("clear");
			printf("\n\t____----SUBMENU EMPLEOS----____\n\n");
			printf("1) Modificar un empleo.\n");
			printf("2) Modificar todos los empleos.\n");
			printf(">>> ");
			scanf("%d", &opc_empleos);
			_fflush();

			switch(opc_empleos)
			{
				case 1:

					break;
				case 2:
				{
					int i;

					printf("Nueva cantidad de empleos: ");
					scanf("%d", &directorio->cont_empleos);

					directorio->empleos = (char**)realloc(directorio->empleos, directorio->cont_empleos);
					for(i = 0; i < directorio->cont_empleos; i++)
					{
						*(directorio->empleos + i) = (char*)malloc(sizeof(char));
						printf("Empleo No.%d: ", i);
						scanf("%s", *(directorio->empleos + i));
					}
				}
					break;
				default:
					printf("Opcion inglresada no valida. (SUBMENU EMPLEOS)\n");
					break;
			}
		}
			break;
		default:
			printf("Opcion inglresada no valida. (MODIFICAR)\n");
			break;
	}
}

void eliminarDirectorio(Directorio *directorio)
{
	system("clear");
	printf("\n\t..::ELIMINAR::..\n\n");

	if(directorio->estado == FALSE)
	{
		printf("\n\tNo existe el directorio. (ELIMINAR)\n\n");
	}
	else
	{
		printf("Datos eliminados con exito...\n");

		directorio->id = 0;
		directorio->nombres = '\0';
		directorio->apellidos = '\0';
		directorio->numero = '\0';
		directorio->RFC = '\0';
		directorio->estado = FALSE;

		liberarMemoria(directorio);
	}
}

void liberarMemoria(Directorio *directorio)
{
	int i;

	// Liberando memoria de **empleos en Directorio
	for(i = 0; i < directorio->cont_empleos; i++)
	{
		free(*(directorio->empleos + i));
		*(directorio->empleos + i) = '\0';
	}
}
