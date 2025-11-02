#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define rojo "\033[0;31m"
#define reset "\033[0m"

struct datos_dirrecciones{
	char calle[50];
	int num_exterior;
	char colonia[50];
	char municipio[50];
	char estado[50];		
};

struct fecha{
	int dia;
	int mes;
	int ano;		
};

struct datos_clientes{
	int clave;
	char nombre[100];
	struct fecha fecha_nacimiento;
	char telefono[10];
	char correo[50];
	struct datos_dirrecciones direccion_cliente;
};



bool validar_sub_menu(char );
bool validar_siono(char *, int);
bool validar_clave(int *);
bool validar_nombre(char *);
void clientes(FILE*);
void agregar_cliente(FILE*);
void consultar(FILE*);
void modificar_ciliente(FILE*);
void espacios_blancos(FILE*);
void modificar_menu(FILE *, struct datos_clientes, int);
bool validar_telefono(char *);

main()
{
	
	int opcMain;
	char opc_sub_menu;
	FILE *ptr_clientesdat;
	
	espacios_blancos(ptr_clientesdat);
	
	
	do
	{
		do
		{
			printf("%20s\n", "Menu");
			printf("%-15s\n","1.-Cliente");
			printf("%-15s\n","2.-Empleados");
			printf("%-15s\n","3.-Servicios");
			printf("%-15s\n","4.-Agenda");
			printf("%-15s\n","5.-Reporte");
			printf("%-15s\n","6.-Salir");
			scanf("%d", &opcMain);
		
			if(opcMain < 1 || opcMain > 6)
				printf(rojo"ERROR ingrese clave del 1 al 6 \a\n"reset);	
		}while(opcMain < 1 || opcMain > 6);
		
		switch (opcMain)
		{
			case 1:			
				clientes(ptr_clientesdat);
				break;
			case 2:
				break;
				
		}
						
	}while(opcMain != 6);
}

bool validar_sub_menu(char fopc_sub_menu)
{
	if((fopc_sub_menu == 'A' || fopc_sub_menu == 'a' 
	|| fopc_sub_menu == 'M' || fopc_sub_menu == 'm' ||
	 fopc_sub_menu == 'D' || fopc_sub_menu == 'd'|| fopc_sub_menu == 'S' 
	 || fopc_sub_menu == 's' || fopc_sub_menu == 'C'|| fopc_sub_menu == 'c'))
	{	
		return false;
	}
		printf(rojo"ERROR ingrese clave correcta \a\n"reset);	
	return true;
}

void clientes(FILE* Ptr_fileClient)
{
	char opc_sub_menu;
	
	
	do
	{
		printf("%20s\n", "Clientes");
		printf("%-15s\n","A.-Agregar");
		printf("%-15s\n","C.-Consultar");
		printf("%-15s\n","M.-Modificar");
		printf("%-15s\n","D.-Borrar");
		printf("%-15s\n","S.-Salir");
		fflush(stdin);
		scanf("%c", &opc_sub_menu);
					

	}while((validar_sub_menu(opc_sub_menu)));
	
	switch (opc_sub_menu)
	{
		case 'a' : case 'A':
		if((Ptr_fileClient = fopen("clientes1.dat","a+")) == NULL)
			printf("No se abrio el archivo");
		else
		{
			agregar_cliente(Ptr_fileClient);
			fclose(Ptr_fileClient);
		}
		break;		
			
	}
			
				
}

bool validar_siono(char *sionof, int opcf)
{
	int i=0;
	
    while(*(sionof + i) != '\0')
    {
    	*(sionof + i) = toupper(*(sionof + i));
    	i++;
	}
        
	switch(opcf)
	{
		case 1:
			if(strcmp(sionof, "SI") != 0 && strcmp(sionof, "NO") != 0)
			{
				printf(rojo"ERROR ingrese Si o No \a\n"reset);
				return true;		
			}
			else
				return false;
		break;
		
		case 2:
			if(strcmp(sionof, "SI") == 0)
				return true;		
			else
				return false;
		break;
		
	}
}

bool validar_clave(int *clavef)
{
	bool cambio = false;
	getchar();
	if(*clavef < 1 || *clavef > 100)
	{	
		return cambio = true;
		getchar();
	}
	return cambio;
}


bool validar_nombre(char *nombref)
{
	int i=0;
	bool estado = false;
	while(*(nombref + i) != '\0')
	{

		
		if(!(*(nombref + i) >= 'A' && *(nombref + i) <= 'Z' || *(nombref + i) >= 'a' && *(nombref + i) <= 'z' || *(nombref + i) == 32))
		{
			printf(rojo"ERROR ingrese solo letras y espacios \a\n"reset);
			estado = true;
		}
		
		if(!(*(nombref + i) >= 'A' && *(nombref + i) <= 'Z' || *(nombref + i) >= 'a' && *(nombref + i) <= 'z'))
		{
			printf(rojo"ERROR ingresaste solo espacios \a\n"reset);
			estado = true;
		}
		i++;
	}
	
    
    return estado;

}

void agregar_cliente(FILE* Ptr_fileTxt )
{
	struct datos_clientes cliente; 
	char siono[3];
	
	
	do
	{
		do
		{
			printf("Ingresa la clave del cliente: \n");
			scanf("%d", &cliente.clave);
		}while(validar_clave(&cliente.clave));
		
		do
		{
			printf("Ingresa el nombre del cliente: ");
			fflush(stdin);
			gets(cliente.nombre);
		}while(validar_nombre(cliente.nombre));
		
		do
		{
			printf("Ingresa el telefono del cliente: ");
			fflush(stdin);
			gets(cliente.telefono);
		}while(validar_telefono(cliente.telefono));
			
		do
		{
			printf("Desea agregar un nuevo regristro (Si/No): ");
			fflush(stdin);
			gets(siono);	
		}while(validar_siono(siono, 1));
		
	}while(validar_siono(siono, 2));
}
bool validar_telefono(char *ftelefono)
{
	int i;
	
	if(strlen(ftelefono) > 10 || strlen(ftelefono) < 10)
	{
		printf(rojo"ERROR solo 10 caracteres\a\n"reset);
		return true;
	}
	
	
	for(i=0; i<10; i++)
	{
		if(*(ftelefono + i) < '0' || *(ftelefono + i) > '9')
		{
			printf(rojo"ERROR solo numeros, no letras \a\n"reset);
			return true;
		}
	}
	
	
	return false;
}

void consultar(FILE* Ptr_fileTxt  )
{
	struct datos_clientes clientef;
	int opc_consulta,clave_ciliente;
	char nombre_ciliente[50],telefono_ciliente[50];
	bool encontrado = true;

	do
	{
		do
		{
			printf("%20s\n", "Consultar por: ");
			printf("%-15s\n","1.-Clave");
			printf("%-15s\n","2.-Telefono");
			printf("%-15s\n","3.-Nombre");
			printf("%-15s\n","4.-Salir");
			scanf("%d",&opc_consulta);
		}while(opc_consulta < 1 || opc_consulta > 4);
		
		switch(opc_consulta)
		{
			case 1:
				do
				{
					printf("Ingrese la clave del ciliente a consultar\n");
					scanf("%d",&clave_ciliente);
				}while(validar_clave(&clave_ciliente));
				
				fseek(Ptr_fileTxt, (clave_ciliente - 1) * sizeof(struct datos_clientes), SEEK_SET);
				fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
				
				if(clientef.clave == clave_ciliente)
				{
					imprimir_cliente(&clientef);
				}
				else
					printf(rojo"La clave ingresada no existe\n"reset);
				break;
			case 3:
				do
				{
					fflush(stdin);
					printf("Ingrese el nombre del cliente a buscar\n");
					gets(nombre_ciliente);
				}while(validar_nombre(nombre_ciliente));
				
				rewind(clientef);
				
				fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
				while(!feof(clientef))
				{
					if(strcmp(clientef.nombre,nombre_ciliente))
					{
						imprimir_cliente(&clientef);
						encontrado = false;
					}
						
				}
				if(encontrado)
					printf(rojo"El nombre ingresado no existe\n"reset);
				
				break;
			case 2:
				do
				{
					fflush(stdin);
					printf("Ingrese el telefono del cliente a buscar\n");
					gets(telefono_ciliente);
				}while(validar_telefono(telefono_ciliente));
				
				rewind(clientef);
				fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
				
				while(!feof(clientef))
				{
					if(strcmp(clientef.telefono,telefono_ciliente))
					{
						imprimir_cliente(&clientef);
						encontrado = false;
					}
					
				}
				if(encontrado)
					printf(rojo"El telefono ingresado no existe\n"reset);
				break;
			case 4:
				printf("Gracias por usar el programa\n");
				break;
		}
		
	}while(opc_consulta != 4);
}

void modificar_ciliente(FILE* Ptr_fileTxt)
{
	struct datos_clientes cliente;
	int opc_consulta,clave_ciliente;
	char nombre_ciliente[50],telefono_ciliente[50];
	bool encontrado = true;

	do
	{
		do
		{
			printf("%20s\n", "Modificar cliente por: ");
			printf("%-15s\n","1.-Clave");
			printf("%-15s\n","2.-Telefono");
			printf("%-15s\n","3.-Nombre");
			printf("%-15s\n","4.-Salir");
			scanf("%d",&opc_consulta);
		}while(opc_consulta < 1 || opc_consulta > 4);
		
		switch(opc_consulta)
		{
			case 1:
				do
				{
					printf("Ingrese la clave del ciliente a modificar\n");
					scanf("%d",&clave_ciliente);
				}while(validar_clave(&clave_ciliente));
				
				fseek(Ptr_fileTxt, (clave_ciliente - 1) * sizeof(struct datos_clientes), SEEK_SET);
				fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
				
				if(clientef.clave == clave_ciliente)
				{
					modificar_menu(Ptr_fileTxt,&clientef,1);
				}
				else
					printf(rojo"La clave ingresada no existe\n"reset);
				break;
			case 3:
				do
				{
					fflush(stdin);
					printf("Ingrese el nombre del cliente a modificar\n");
					gets(nombre_ciliente);
				}while(validar_nombre(nombre_ciliente));
				
				rewind(clientef);
				fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
				
				while(!feof(clientef))
				{
					if(strcmp(clientef.nombre,nombre_ciliente))
					{
						modificar_menu(Ptr_fileTxt,&clientef,3);
						encontrado = false;
					}
				}
				if(encontrado)
					printf(rojo"El nombre ingresado no existe\n"reset);
				
				break;
			case 2:
				do
				{
					fflush(stdin);
					printf("Ingrese el telefono del cliente a modficar\n");
					gets(telefono_ciliente);
				}while(validar_telefono(telefono_ciliente));
				
				rewind(clientef);
				fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
				
				while(!feof(clientef))
				{
					if(strcmp(clientef.telefono,telefono_ciliente))
					{
						modificar_menu(Ptr_fileTxt,&clientef,2);
						encontrado = false;
					}
				}
				if(encontrado)
					printf(rojo"El telefono ingresado no existe\n"reset);
				break;
			case 4:
				printf("Gracias por usar el programa\n");
				break;
		}
		
	}while(opc_consulta != 4);
	
}

void modificar_menu(FILE *Ptr_fileTxt, struct datos_clientes *c, int n)
{
	char telefono_nuevo[10],nombre_nuevo[100];
	int opc_consulta;
	do
	{
		printf("%20s\n", "Que desea modficar del cliente: ");
		printf("%-15s\n","1.-Telefono");
		printf("%-15s\n","2.-Nombre");
		printf("%-15s\n","3.-Salir");
		scanf("%d",&opc_consulta);
	}while(opc_consulta < 1 || opc_consulta > 3);
	
	switch(n)
	{
		case 1:
			fflush(stdin);
			printf("Ingrese el nuevo telefono del cliente\n");
			gets(telefono_nuevo);
			c.telefono = telefono_nuevo;
			break;
		case 2:
			fflush(stdin);
			printf("Ingrese el nuevo nombre del cliente\n");
			gets(nombre_nuevo);
			c.nombre = nombre_nuevo;
			break;
		case 3:
			printf("Gracias por usar el programa\n");
			break;
	}
}

void espacios_blancos(FILE*Ptr_ClientesdatF)
{	
	struct fecha fecha_blanco = {0,0,0};
	struct datos_dirrecciones direccion_blanco ={" " ,0," "," "," " };
	struct datos_clientes cliente_blanco={0," ",fecha_blanco," "," ", direccion_blanco};
	int i;
	
	if((Ptr_ClientesdatF = fopen("clientes1.dat","r+"))== NULL) 
	{
		printf("No se encontro archivo....creando\n");
		Ptr_ClientesdatF = fopen("clientes1.dat","w");
		
		for(i=0; i<100; i++)
			fwrite(&cliente_blanco, sizeof(struct datos_clientes), 1, Ptr_ClientesdatF);
		
		fclose(Ptr_ClientesdatF);
	}
	else
		printf("archivo encontrado\n");
}
