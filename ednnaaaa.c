#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define rojo "\033[0;31m"
#define reset "\033[0m"

struct datos_direcciones{
	char calle[100];
	int num_exterior;
	char colonia[100];
	char municipio[100];
	char estado[100];		
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
	char telefono[15];
	char correo[100];
	struct datos_direcciones direccion_cliente;
};

struct datos_empleados{
	int clave;
	char nombre[100];
	char puesto[100];
	struct fecha fecha_contratacion;
	char telefono[15];
	char correo[150];
	struct datos_direcciones direccion_empleado;
};



// funciones usadas para clientes
bool validar_sub_menu(char );
bool validar_siono(char *, int);
bool validar_clave(int *);
bool validar_nombre(char *);
void clientes(FILE*);
void agregar_cliente(FILE*);
void consultar(FILE*);
void modificar_ciliente(FILE*);
void espacios_blancos(FILE*,FILE*);
void modificar_menu(FILE *, struct datos_clientes *c);
bool validar_telefono(char *);
void borrar_cliente(FILE*);

main()
{
	
	int opcMain;
	char opc_sub_menu;
	FILE *ptr_clientesdat, *ptr_empleadosdat;
	
	espacios_blancos(ptr_clientesdat, ptr_empleadosdat);
	
	
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
		if((Ptr_fileClient = fopen("clientes1.dat","r+")) == NULL)
			printf("No se abrio el archivo");
		else
		{
			agregar_cliente(Ptr_fileClient);
			fclose(Ptr_fileClient);
		}
		break;	
		
		case 'c' : case'C': 
		if((Ptr_fileClient = fopen("clientes1.dat","r+")) == NULL)
			printf("No se abrio el archivo");
		else
		{
			consultar(Ptr_fileClient);
			fclose(Ptr_fileClient);
		}
		break;
		
		case 'm' : case'M': 
		if((Ptr_fileClient = fopen("clientes1.dat","r+")) == NULL)
			printf("No se abrio el archivo");
		else
		{
			modificar_ciliente(Ptr_fileClient);
			fclose(Ptr_fileClient);
		}
		break;	
		
		case 'd': case'D':
		if((Ptr_fileClient = fopen("clientes1.dat","r+")) == NULL)
			printf("No se abrio el archivo");
		else
		{
			borrar_cliente(Ptr_fileClient);
			fclose(Ptr_fileClient);
		}
				
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

void agregar_cliente(FILE* Ptr_Clientesdatf )
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
			printf("Ingresa el nombre del cliente: \n");
			fflush(stdin);
			gets(cliente.nombre);
		}while(validar_nombre(cliente.nombre));
		
	
		printf("--- Fecha de nacimiento ---\n");
		printf("Ingrese dia: \n");
		scanf("%d",&cliente.fecha_nacimiento.dia);
			
		printf("Ingrese mes: \n");
		scanf("%d",&cliente.fecha_nacimiento.mes);
			
		printf("Ingrese anio: \n");
		scanf("%d",&cliente.fecha_nacimiento.ano);
		
		do
		{
			printf("Ingresa el telefono del cliente: ");
			fflush(stdin);
			gets(cliente.telefono);
		}while(validar_telefono(cliente.telefono));
		
		do
		{
			printf("ingrese correo electronico: \n");
			fflush(stdin);
			gets(cliente.correo);
		}while(false);
		
		printf("--- Direccion ---\n");
		
		printf("Ingrese calle: \n");
		fflush(stdin);
		gets(cliente.direccion_cliente.calle);
		
		printf("Ingrese el numero exterior: \n");
		scanf("%d",&cliente.direccion_cliente.num_exterior);
		
		printf("Ingrese colonia: \n");
		fflush(stdin);
		gets(cliente.direccion_cliente.colonia);
		
		printf("Ingrese municipio: \n");
		fflush(stdin);
		gets(cliente.direccion_cliente.municipio);
		
		printf("Ingrese estado: \n");
		fflush(stdin);
		gets(cliente.direccion_cliente.estado);
		
		fseek(Ptr_Clientesdatf, (cliente.clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
		fwrite(&cliente, sizeof(struct datos_clientes), 1, Ptr_Clientesdatf);
			
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
	
	if(strlen(ftelefono) != 10)
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

void consultar(FILE* Ptr_fileTxt)
{
	struct datos_clientes clientef={0};
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
				
				printf("%s\n",clientef.telefono);
				printf("%s\n",clientef.correo);
				
				if(clientef.clave == clave_ciliente)
				{
					printf("%-20s%-20s%-20s%-20s%-30s\n", "CLAVE", "NOMBRE", "FECHA NACIMIENTO", "TELEFONO", "CORREO");
					printf("%-20d%-20s%-2d/%-1d/%-3d%20s%30s\n", clientef.clave, clientef.nombre, clientef.fecha_nacimiento.dia, clientef.fecha_nacimiento.mes, clientef.fecha_nacimiento.ano, clientef.telefono, clientef.correo);
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
				
				rewind(Ptr_fileTxt);
				
				while(!feof(Ptr_fileTxt))
				{
					fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
					
					if(strcmp(clientef.nombre,nombre_ciliente) == 0 && !feof(Ptr_fileTxt))
					{
						printf("%-20s%-20s%-20s%-20s%-30s\n", "CLAVE", "NOMBRE", "FECHA NACIMIENTO", "TELEFONO", "CORREO");
						printf("%-20d%-20s%-2d/%-1d/%-3d%20s%30s\n", clientef.clave, clientef.nombre, clientef.fecha_nacimiento.dia, clientef.fecha_nacimiento.mes, clientef.fecha_nacimiento.ano, clientef.telefono, clientef.correo);

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
				
				rewind(Ptr_fileTxt);
				
				while(!feof(Ptr_fileTxt))
				{
					fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
					
					if(strcmp(clientef.telefono,telefono_ciliente) == 0 && !feof(Ptr_fileTxt))
					{
						printf("%-20s%-20s%-20s%-20s%-30s\n", "CLAVE", "NOMBRE", "FECHA NACIMIENTO", "TELEFONO", "CORREO");
						printf("%-20d%-20s%-2d/%-1d/%-3d%20s%30s\n", clientef.clave, clientef.nombre, clientef.fecha_nacimiento.dia, clientef.fecha_nacimiento.mes, clientef.fecha_nacimiento.ano, clientef.telefono, clientef.correo);

						encontrado = false;
					}
					
				}
				if(encontrado)
					printf(rojo"El telefono ingresado no existe\n"reset);
				break;
			case 4:
				printf("Regresando al menu clientes...\n");
				break;
		}
		
	}while(opc_consulta != 4);
}

void modificar_ciliente(FILE* Ptr_fileTxt)
{
	struct datos_clientes clientef;
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
					modificar_menu(Ptr_fileTxt, &clientef);
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
				
				rewind(Ptr_fileTxt);
				fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
				
				while(!feof(Ptr_fileTxt))
				{
					if(strcmp(clientef.nombre,nombre_ciliente))
					{
						modificar_menu(Ptr_fileTxt,&clientef);
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
				
				rewind(Ptr_fileTxt);
				fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
				
				while(!feof(Ptr_fileTxt))
				{
					if(strcmp(clientef.telefono,telefono_ciliente))
					{
						modificar_menu(Ptr_fileTxt,&clientef);
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

void modificar_menu(FILE *Ptr_fileTxt, struct datos_clientes *c )
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
	
	switch(opc_consulta)
	{
		case 1:
			fflush(stdin);
			printf("Ingrese el nuevo telefono del cliente\n");
			gets(telefono_nuevo);
			strcpy(c->telefono, telefono_nuevo);
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
			fwrite(c, sizeof(struct datos_clientes),1,Ptr_fileTxt);
			printf("Cliente modificado con exito\n");

			break;
		case 2:
			fflush(stdin);
			printf("Ingrese el nuevo nombre del cliente\n");
			gets(nombre_nuevo);
			strcpy(c->nombre, nombre_nuevo);
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
			fwrite(c, sizeof(struct datos_clientes),1,Ptr_fileTxt);
			printf("Cliente modificado con exito\n");
			
			break;
		case 3:
			printf("Regresando al menu modificar cliente....\n");
			break;
	}
}

void espacios_blancos(FILE*Ptr_ClientesdatF, FILE*Ptr_EmpleadosdatF)
{	
	struct fecha fecha_blanco = {0,0,0};
	struct datos_direcciones direccion_blanco ={" " ,0," "," "," " };
	struct datos_clientes cliente_blanco={0," ",fecha_blanco," "," ", direccion_blanco};
	struct datos_empleados empleados_blanco={0," "," ",fecha_blanco," "," ",direccion_blanco};


	int i;
	
	//erchivo binario clientes
	if((Ptr_ClientesdatF = fopen("clientes1.dat","r+"))== NULL) 
	{
		printf("No se encontro archivo clientes....creando archivo clientes\n");
		Ptr_ClientesdatF = fopen("clientes1.dat","w");
		
		for(i=0; i<100; i++)
			fwrite(&cliente_blanco, sizeof(struct datos_clientes), 1, Ptr_ClientesdatF);
		
		fclose(Ptr_ClientesdatF);
	}
	else
		printf("archivo clientes encontrado\n");
	
	//archivo binario empleados
	if((Ptr_EmpleadosdatF = fopen("empleados.dat","r+"))== NULL) 
	{
		printf("No se encontro archivo empleados....creando archivo empleados\n");
		Ptr_EmpleadosdatF = fopen("empleados.dat","w");
		
		for(i=0; i<100; i++)
			fwrite(&empleados_blanco, sizeof(struct datos_clientes), 1, Ptr_EmpleadosdatF);
		
		fclose(Ptr_EmpleadosdatF);
	}
	else
		printf("archivo empleados encontrado\n");
		
}

void borrar_cliente(FILE*ptr_datfilef)
{
	struct fecha fecha_blanco = {0,0,0};
	struct datos_direcciones direccion_blanco ={" " ,0," "," "," " };
	struct datos_clientes cliente_blanco={0," ",fecha_blanco," "," ", direccion_blanco}, clientef;
	int del_clave;
	
	printf("ingrese la clave del usuario a eliminar: \n");
	scanf("%d",&del_clave);
	
	fseek(ptr_datfilef, (del_clave-1)*sizeof(struct datos_clientes),SEEK_SET);
	fread(&clientef, sizeof(struct datos_clientes),1,ptr_datfilef);
	
	if(clientef.clave == del_clave)
	{
		fseek(ptr_datfilef, (del_clave-1)*sizeof(struct datos_clientes),SEEK_SET);
		fwrite(&cliente_blanco, sizeof(struct datos_clientes),1,ptr_datfilef);
		printf("Usuario eliminado con exito...");	
	}
	else 
		printf("Usuario no encontrado....");
	
}
