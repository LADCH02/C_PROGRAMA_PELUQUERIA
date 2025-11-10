#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define rojo "\033[0;31m"
#define reset "\033[0m"

struct datos_direcciones
{
	char calle[100];
	int num_exterior;
	char colonia[100];
	char municipio[100];
	char estado[100];		
};

struct fecha
{
	int dia;
	int mes;
	int ano;		
};

struct tiempo
{
	int hora;
	int minutos;
};

struct datos_clientes
{
	int clave;
	char nombre[100];
	struct fecha fecha_nacimiento;
	char telefono[15];
	char correo[100];
	struct datos_direcciones direccion_cliente;
};

struct datos_empleados
{
	int clave;
	char nombre[100];
	char puesto[100];
	struct fecha fecha_contratacion;
	char telefono[15];
	char correo[150];
	struct datos_direcciones direccion_empleado;
};

struct datos_servicios
{
	int clave;
	char descripcion[100];
	float precio;
	struct tiempo duracion;
};

struct datos_agenda{
	int clave;
	int clave_cliente;
	int clave_empleado;
	int clave_servicio;
	char estatus[100];
	struct fecha fecha_agendada;
	int hora;		
};




// funciones para validar
bool validar_sub_menu(char );
bool validar_siono(char *, int);
bool validar_clave(int *);
bool validar_nombre(char *);
bool validar_formato_fecha(struct fecha *);
bool validar_fecha_no_futura(struct fecha *);
bool validar_telefono(char *);
bool validar_num_casa(int *);
bool validar_puesto(char *);
bool validar_duracion(struct tiempo *);
bool validar_precio(float *);

// funciones usadas para clientes
void clientes(FILE*);
void agregar_cliente(FILE*);
void consultar(FILE*);
void modificar_ciliente(FILE*);
void modificar_menu_clientes(FILE *, struct datos_clientes *c);
void borrar_cliente(FILE*);
bool validar_existencia_clave_cliente(int *, FILE *, bool);

// Funciones usadas para empleados
void empleados(FILE*);
void agregar_empleado(FILE*);
void consultar_empleado(FILE*);
void modificar_empleado(FILE*);
void modificar_menu_empleado(FILE *Ptr_fileTxt, struct datos_empleados *c);
void borrar_empleado(FILE*);
bool validar_existencia_clave_empleado(int *, FILE *, bool);

// funciones usadas para servicios
void servicios(FILE*);
void agregar_servicios(FILE*);
void consultar_servicio(FILE*);
void modificar_servicio(FILE*);
void modificar_menu_servicio(FILE *Ptr_fileTxt, struct datos_servicios *c);
void borrar_servicio(FILE*);
bool validar_existencia_clave_servicio(int *, FILE *, bool);

// funciones usadas para agenda
void agenda(FILE*, FILE*, FILE*, FILE*);
void agregar_agenda(FILE* , FILE* , FILE*, FILE* );
void consultar_agenda(FILE* );
void modificar_agenda(FILE* , FILE* , FILE*, FILE* );
void borrar_agenda(FILE*);
bool validar_existencia_clave_agenda(int *, FILE *);
bool validar_estatus(char *);
void modificar_menu_agenda(FILE *, FILE *, FILE *, FILE *, struct datos_agenda *);
bool validar_hora(int *);


// Espacios
void espacios_blancos(FILE*,FILE*,FILE*, FILE*);




main()
{
	
	int opcMain;
	char opc_sub_menu;
	FILE *ptr_clientesdat, *ptr_empleadosdat, *ptr_serviciosdat, *ptr_agendadat;
	
	espacios_blancos(ptr_clientesdat, ptr_empleadosdat, ptr_serviciosdat, ptr_agendadat);
	
	
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
			fflush(stdin);
			if(opcMain < 1 || opcMain > 6)
				printf(rojo"ERROR ingrese clave del 1 al 6 \a\n"reset);	
		}while(opcMain < 1 || opcMain > 6);
		
		switch (opcMain)
		{
			case 1:			
				clientes(ptr_clientesdat);
				break;
			case 2:
				empleados(ptr_empleadosdat);
				break;
			case 3:
				servicios(ptr_serviciosdat);
				break;
			case 4:
				agenda(ptr_agendadat, ptr_clientesdat, ptr_empleadosdat,  ptr_serviciosdat);
				break;
				
		}
						
	}while(opcMain != 6);
}

bool validar_sub_menu(char fopc_sub_menu)
{
	bool cambio = false;
	if(!(fopc_sub_menu == 'A' || fopc_sub_menu == 'a' 
	|| fopc_sub_menu == 'M' || fopc_sub_menu == 'm' ||
	 fopc_sub_menu == 'D' || fopc_sub_menu == 'd'|| fopc_sub_menu == 'S' 
	 || fopc_sub_menu == 's' || fopc_sub_menu == 'C'|| fopc_sub_menu == 'c'))
	{	
		cambio = true;
		printf(rojo"ERROR ingrese clave correcta \a\n"reset);
	}	
	return cambio;
}

void clientes(FILE* Ptr_fileClient)
{
	char opc_sub_menu;
	
	do
	{
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
	}while(opc_sub_menu != 'S' && opc_sub_menu != 's');
				
}

void empleados(FILE* Ptr_fileempleado)
{
	char opc_sub_menu;
	
	do
	{
		do
		{
			printf("%20s\n", "Empleados");
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
			if((Ptr_fileempleado = fopen("empleados.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				agregar_empleado(Ptr_fileempleado);
				fclose(Ptr_fileempleado);
			}
			break;	
			
			case 'c' : case'C': 
			if((Ptr_fileempleado = fopen("empleados.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				consultar_empleado(Ptr_fileempleado);
				fclose(Ptr_fileempleado);
			}
			break;
			
			case 'm' : case'M': 
			if((Ptr_fileempleado = fopen("empleados.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				modificar_empleado(Ptr_fileempleado);
				fclose(Ptr_fileempleado);
			}
			break;	
			
			case 'd': case'D':
			if((Ptr_fileempleado = fopen("empleados.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				borrar_empleado(Ptr_fileempleado);
				fclose(Ptr_fileempleado);
			}
					
		}
	}while(opc_sub_menu != 'S' && opc_sub_menu != 's');
				
}

void servicios(FILE* Ptr_fileservicio)
{
	char opc_sub_menu;
	
	do
	{
		do
		{
			printf("%20s\n", "Servicios");
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
			if((Ptr_fileservicio = fopen("servicios.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				agregar_servicios(Ptr_fileservicio);
				fclose(Ptr_fileservicio);
			}
			break;	
			
			case 'c' : case'C': 
			if((Ptr_fileservicio = fopen("servicios.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				consultar_servicio(Ptr_fileservicio);
				fclose(Ptr_fileservicio);
			}
			break;
			
			case 'm' : case'M': 
			if((Ptr_fileservicio = fopen("servicios.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				modificar_servicio(Ptr_fileservicio);
				fclose(Ptr_fileservicio);
			}
			break;	
			
			case 'd': case'D':
			if((Ptr_fileservicio = fopen("servicios.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				borrar_servicio(Ptr_fileservicio);
				fclose(Ptr_fileservicio);
			}
					
		}
	}while(opc_sub_menu != 'S' && opc_sub_menu != 's');
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
	if(*clavef < 1 || *clavef > 100)
	{	
		printf(rojo"ERROR: Ingresa una clave que este entre el 1 - 100 \a\n"reset);
		cambio = true;
	}

	return cambio;
}

bool validar_existencia_clave_cliente(int *clavef, FILE *ptrf, bool debe_existir)
{
	struct datos_clientes clientesf;
    bool cambio = false;
    bool encontrado = false;
    
    rewind(ptrf);
    while(!feof(ptrf))
    {
        fread(&clientesf, sizeof(struct datos_clientes), 1, ptrf);    
        if(*clavef == clientesf.clave)
        {
            encontrado = true;
            break;
        }
    }

    
    if(debe_existir) 
	{
        if(!encontrado) 
		{
            printf(rojo"ERROR: La clave de cliente no existe \a\n"reset);
            cambio = true;
        }
    } 
	else 
	{
        if(encontrado) 
		{
            printf(rojo"ERROR: Ingresa una clave que no este asignada \a\n"reset);
            cambio = true;
        }
    }
    
    return cambio;
}

bool validar_existencia_clave_empleado(int *clavef, FILE *ptrf, bool debe_existir)
{
    struct datos_empleados empleadof;
    bool cambio = false;
    bool encontrado = false;
    
    rewind(ptrf);
    while(!feof(ptrf))
    {
        fread(&empleadof, sizeof(struct datos_empleados), 1, ptrf);    
        if(*clavef == empleadof.clave)
        {
            encontrado = true;
            break;
        }
    }
    rewind(ptrf);
    
    if(debe_existir) 
	{
        if(!encontrado) 
		{
            printf(rojo"ERROR: La clave de empleado no existe \a\n"reset);
            cambio = true;
        }
    } 
	else 
	{
        if(encontrado) 
		{
            printf(rojo"ERROR: Ingresa una clave que no este asignada \a\n"reset);
            cambio = true;
        }
    }
    
    return cambio;
}

bool validar_existencia_clave_servicio(int *clavef, FILE *ptrf, bool debe_existir)
{
    struct datos_servicios serviciof;
    bool cambio = false;
    bool encontrado = false;
    
    rewind(ptrf);
    while(!feof(ptrf))
    {
        fread(&serviciof, sizeof(struct datos_servicios), 1, ptrf);    
        if(*clavef == serviciof.clave)
        {
            encontrado = true;
            break;
        }
    }
    rewind(ptrf);
    
    if(debe_existir) 
	{
        if(!encontrado) 
		{
            printf(rojo"ERROR: La clave de servicio no existe \a\n"reset);
            cambio = true;
        }
    } 
	else 
	{
        if(encontrado) 
		{
            printf(rojo"ERROR: Ingresa una clave que no este asignada \a\n"reset);
            cambio = true;
        }
    }
    
    return cambio;
}

bool validar_existencia_clave_agenda(int *clave_agendaf, FILE *Ptr_agendadatf)
{
	struct datos_agenda agendaf;
	bool	cambio = false;
	
	rewind(Ptr_agendadatf);
	while(!feof(Ptr_agendadatf))
	{
		fread(&agendaf, sizeof(struct datos_agenda), 1, Ptr_agendadatf);	
		if(*clave_agendaf == agendaf.clave && !feof(Ptr_agendadatf))
		{
			printf(rojo"ERROR: Ingresa una clave que no este asignada \a\n"reset);
			cambio = true;
		}
	}
	rewind(Ptr_agendadatf);
	
	return cambio;
}

bool validar_nombre(char *nombref)
{	
	int i=0;
	bool estado_letras = false, estado = false, estado_vacio = false;
	
	if(strlen(nombref) < 1)
    {
        printf(rojo"ERROR: El nombre no puede estar vacio \a\n"reset);
        estado  = true;
    }
	
	while(*(nombref + i) != '\0')
	{			
		
		if(!(*(nombref + i) >= 'A' && *(nombref + i) <= 'Z' || *(nombref + i) >= 'a' && *(nombref + i) <= 'z' || *(nombref + i) == 32))
		
			estado_letras = true;
		
		
		if(*nombref == 32) 
		
			estado_vacio = true;
		
		i++;
		
	}
	if(estado_vacio)
	{
		printf(rojo"ERROR ingresaste un espacio al principio \a\n"reset);
		estado = true;
	}
	
	if(estado_letras)
	{
		printf(rojo"ERROR ingrese solo letras y espacios \a\n"reset);
		estado = true;
	}
		
    return estado;
}

void agregar_cliente(FILE* Ptr_Clientesdatf )
{
	struct datos_clientes cliente;
	int resultado_scanf;
	char siono[3];
	
	do
	{
		do
		{
			fflush(stdin);
			printf("Ingresa la clave del cliente: \n");
			resultado_scanf = scanf("%d", &cliente.clave);
		}while(validar_clave(&cliente.clave) || validar_existencia_clave_cliente(&cliente.clave, Ptr_Clientesdatf, false));
		
		do
		{
			printf("Ingresa el nombre del cliente: \n");
			fflush(stdin);
			gets(cliente.nombre);
		}while(validar_nombre(cliente.nombre));
		
		do
		{
			fflush(stdin);
			printf("--- Fecha de nacimiento ---\n");
			printf("Ingrese dia: \n");
			scanf("%d",&cliente.fecha_nacimiento.dia);
			
			printf("Ingrese mes: \n");
			scanf("%d",&cliente.fecha_nacimiento.mes);
			
			printf("Ingrese anio: \n");
			scanf("%d",&cliente.fecha_nacimiento.ano);			
		}while(validar_formato_fecha(&cliente.fecha_nacimiento) || validar_fecha_no_futura(&cliente.fecha_nacimiento));
		
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
		
		do
		{
			printf("Ingrese calle: \n");
			fflush(stdin);
			gets(cliente.direccion_cliente.calle);
		}while(validar_nombre(cliente.direccion_cliente.calle));
		
		
		do
		{	
			fflush(stdin);
			printf("Ingrese el numero exterior: \n");
			scanf("%d",&cliente.direccion_cliente.num_exterior);
		}while(validar_num_casa(&cliente.direccion_cliente.num_exterior));

		
		do
		{
			printf("Ingrese colonia: \n");
			fflush(stdin);
			gets(cliente.direccion_cliente.colonia);	
		}while(validar_nombre(cliente.direccion_cliente.colonia));

		do
		{
			printf("Ingrese municipio: \n");
			fflush(stdin);
			gets(cliente.direccion_cliente.municipio);
		}while(validar_nombre(cliente.direccion_cliente.municipio));
		
		do
		{
			printf("Ingrese estado: \n");
			fflush(stdin);
			gets(cliente.direccion_cliente.estado);	
		}while(validar_nombre(cliente.direccion_cliente.estado));
		
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

void agregar_empleado(FILE* Ptr_empleadosdatf)
{
	struct datos_empleados empleado;
	char siono[3];
	
	do
	{
		do
		{
			fflush(stdin);
			printf("Ingresa la clave del empleado: \n");
			scanf("%d", &empleado.clave);
		}while(validar_clave(&empleado.clave) || validar_existencia_clave_empleado(&empleado.clave, Ptr_empleadosdatf, false));
		
		do
		{
			printf("Ingresa el nombre del empleado: \n");
			fflush(stdin);
			gets(empleado.nombre);
		}while(validar_nombre(empleado.nombre));
		
		do
		{
			printf("Ingresa el puesto del empleado: \n");
			fflush(stdin);
			gets(empleado.puesto);
		}while(validar_puesto(empleado.puesto));
		
		do
		{
			fflush(stdin);
			printf("--- Fecha de contratacion ---\n");
			printf("Ingrese dia: \n");
			scanf("%d",&empleado.fecha_contratacion.dia);
			
			printf("Ingrese mes: \n");
			scanf("%d",&empleado.fecha_contratacion.mes);
			
			printf("Ingrese anio: \n");
			scanf("%d",&empleado.fecha_contratacion.ano);			
		}while(validar_formato_fecha(&empleado.fecha_contratacion) || validar_fecha_no_futura(&empleado.fecha_contratacion));
		
		do
		{
			printf("Ingresa el telefono del empleado: ");
			fflush(stdin);
			gets(empleado.telefono);
		}while(validar_telefono(empleado.telefono));
		
		do
		{
			printf("Ingrese correo electronico: \n");
			fflush(stdin);
			gets(empleado.correo);
		}while(false);
		
		printf("--- Direccion ---\n");
		
		do
		{
			printf("Ingrese calle: \n");
			fflush(stdin);
			gets(empleado.direccion_empleado.calle);
		}while(validar_nombre(empleado.direccion_empleado.calle));
		
		
		do
		{	
			fflush(stdin);
			printf("Ingrese el numero exterior: \n");
			scanf("%d",&empleado.direccion_empleado.num_exterior);
		}while(validar_num_casa(&empleado.direccion_empleado.num_exterior));

		
		do
		{
			printf("Ingrese colonia: \n");
			fflush(stdin);
			gets(empleado.direccion_empleado.colonia);	
		}while(validar_nombre(empleado.direccion_empleado.colonia));

		do
		{
			printf("Ingrese municipio: \n");
			fflush(stdin);
			gets(empleado.direccion_empleado.municipio);
		}while(validar_nombre(empleado.direccion_empleado.municipio));
		
		do
		{
			printf("Ingrese estado: \n");
			fflush(stdin);
			gets(empleado.direccion_empleado.estado);	
		}while(validar_nombre(empleado.direccion_empleado.estado));
		
		fseek(Ptr_empleadosdatf, (empleado.clave - 1) * sizeof(struct datos_empleados), SEEK_SET);
		fwrite(&empleado, sizeof(struct datos_empleados), 1, Ptr_empleadosdatf);
			
		do
		{
			printf("Desea agregar un nuevo regristro (Si/No): ");
			fflush(stdin);
			gets(siono);	
		}while(validar_siono(siono, 1));
		
	}while(validar_siono(siono, 2));
}

// arreglar impresion
void consultar_empleado(FILE* Ptr_empleadosdatf)
{
	struct datos_empleados empleadof={0};
	int opc_consulta,clave_buscar;
	char nombre_buscar[50],telefono_buscar[50];
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
					fflush(stdin);
					printf("Ingrese la clave del empleado a consultar\n");
					scanf("%d",&clave_buscar);
				}while(validar_clave(&clave_buscar));
				
				fseek(Ptr_empleadosdatf, (clave_buscar - 1) * sizeof(struct datos_empleados), SEEK_SET);
				fread(&empleadof, sizeof(struct datos_empleados),1, Ptr_empleadosdatf);
				
				if(empleadof.clave == clave_buscar)
				{
					printf("%-10s%-20s%-20s%-25s%-20s%-30s%-25s\n","CLAVE", "NOMBRE", "PUESTO", "FECHA DE CONTRATACION","TELEFONO", "CORREO", "DIRECCION");
					
					printf("%-10d%-20s%-20s%02d/%02d/%-04d%25s%18s%15s %-1d, %s, %s, %s\n",
					empleadof.clave,
					empleadof.nombre,
			        empleadof.puesto,
			        empleadof.fecha_contratacion.dia,
				   	empleadof.fecha_contratacion.mes,
					empleadof.fecha_contratacion.ano,
					empleadof.telefono,
			        empleadof.correo,
	  		        empleadof.direccion_empleado.calle,
					empleadof.direccion_empleado.num_exterior,
					empleadof.direccion_empleado.colonia,
					empleadof.direccion_empleado.municipio,
					empleadof.direccion_empleado.estado);

				}
				else
					printf(rojo"La clave ingresada no existe\n"reset);
				break;
			case 3:
				do
				{
					fflush(stdin);
					printf("Ingrese el nombre del cliente a buscar\n");
					gets(nombre_buscar);
				}while(validar_nombre(nombre_buscar));
				
				rewind(Ptr_empleadosdatf);
				
				while(!feof(Ptr_empleadosdatf))
				{
					fread(&empleadof, sizeof(struct datos_empleados),1,Ptr_empleadosdatf);
					
					if(strcmp(empleadof.nombre,nombre_buscar) == 0 && !feof(Ptr_empleadosdatf))
					{
						printf("%-10s%-20s%-20s%-25s%-20s%-30s%-25s\n","CLAVE", "NOMBRE", "PUESTO", "FECHA DE CONTRATACION","TELEFONO", "CORREO", "DIRECCION");
					
						printf("%-10d%-20s%-20s%02d/%02d/%-04d%25s%18s%15s %-1d, %s, %s, %s\n",
						empleadof.clave,
						empleadof.nombre,
				        empleadof.puesto,
				        empleadof.fecha_contratacion.dia,
					   	empleadof.fecha_contratacion.mes,
						empleadof.fecha_contratacion.ano,
						empleadof.telefono,
				        empleadof.correo,
		  		        empleadof.direccion_empleado.calle,
						empleadof.direccion_empleado.num_exterior,
						empleadof.direccion_empleado.colonia,
						empleadof.direccion_empleado.municipio,
						empleadof.direccion_empleado.estado);
						
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
					gets(telefono_buscar);
				}while(validar_telefono(telefono_buscar));
				
				rewind(Ptr_empleadosdatf);
				
				while(!feof(Ptr_empleadosdatf))
				{
					fread(&empleadof, sizeof(struct datos_empleados),1,Ptr_empleadosdatf);
					
					if(strcmp(empleadof.telefono,telefono_buscar) == 0 && !feof(Ptr_empleadosdatf))
					{
						printf("%-10s%-20s%-20s%-25s%-20s%-30s%-25s\n","CLAVE", "NOMBRE", "PUESTO", "FECHA DE CONTRATACION","TELEFONO", "CORREO", "DIRECCION");
					
						printf("%-10d%-20s%-20s%02d/%02d/%-04d%25s%18s%15s %-1d, %s, %s, %s\n",
						empleadof.clave,
						empleadof.nombre,
				        empleadof.puesto,
				        empleadof.fecha_contratacion.dia,
					   	empleadof.fecha_contratacion.mes,
						empleadof.fecha_contratacion.ano,
						empleadof.telefono,
				        empleadof.correo,
		  		        empleadof.direccion_empleado.calle,
						empleadof.direccion_empleado.num_exterior,
						empleadof.direccion_empleado.colonia,
						empleadof.direccion_empleado.municipio,
						empleadof.direccion_empleado.estado);
						
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

//importante empleados
void modificar_empleado(FILE* Ptr_empleadosdatf)
{
	struct datos_empleados empleadof={0};
	int opc_consulta,clave_buscar;
	char nombre_buscar[50],telefono_buscar[50];
	bool encontrado = true;

	do
	{
		do
		{
			printf("%20s\n", "Modificar empleado por: ");
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
					fflush(stdin);
					printf("Ingrese la clave del empleado a consultar\n");
					scanf("%d",&clave_buscar);
				}while(validar_clave(&clave_buscar));
				
				fseek(Ptr_empleadosdatf, (clave_buscar - 1) * sizeof(struct datos_empleados), SEEK_SET);
				fread(&empleadof, sizeof(struct datos_empleados),1, Ptr_empleadosdatf);
				
				if(empleadof.clave == clave_buscar)
				{
					modificar_menu_empleado(Ptr_empleadosdatf,&empleadof);
				}
				else
					printf(rojo"La clave ingresada no existe\n"reset);
				break;
			case 3:
				do
				{
					fflush(stdin);
					printf("Ingrese el nombre del empleado a modificar\n");
					gets(nombre_buscar);
				}while(validar_nombre(nombre_buscar));
				
				rewind(Ptr_empleadosdatf);
				
				
				while(!feof(Ptr_empleadosdatf) && encontrado)
				{
					fread(&empleadof, sizeof(struct datos_empleados),1,Ptr_empleadosdatf);
					if(strcmp(empleadof.nombre,nombre_buscar))
					{
						modificar_menu_empleado(Ptr_empleadosdatf,&empleadof);
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
					printf("Ingrese el telefono del empleado a modificar\n");
					gets(telefono_buscar);
				}while(validar_telefono(telefono_buscar));
				
				rewind(Ptr_empleadosdatf);
				fread(&empleadof, sizeof(struct datos_empleados),1,Ptr_empleadosdatf);
				
				while(!feof(Ptr_empleadosdatf) && && encontrado)
				{
					fread(&empleadof, sizeof(struct datos_empleados),1,Ptr_empleadosdatf);
					if(strcmp(empleadof.telefono,telefono_buscar))
					{
						modificar_menu_empleado(Ptr_empleadosdatf,&empleadof);
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

void modificar_menu_empleado(FILE *Ptr_fileTxt, struct datos_empleados *c )
{
	int opc_consulta;
	do
	{
		printf("%20s\n", "Que desea modificar del empleado: ");
		printf("%-15s\n","1.-Telefono");
		printf("%-15s\n","2.-Nombre");
		printf("%-15s\n","3.-Correo");
		printf("%-15s\n","4.-Fecha de contratacion");
		printf("%-15s\n","5.-dirrecion");
		printf("%-15s\n","6.-puesto");
		printf("%-15s\n","7.-Salir");
		scanf("%d",&opc_consulta);
	}while(opc_consulta < 1 || opc_consulta > 7);
	
	switch(opc_consulta)
	{
		case 1:
			do
			{
				fflush(stdin);
				printf("Ingrese el nuevo telefono del empleado\n");
				gets(c->telefono);
			}while(validar_telefono(c->telefono));
			
			
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_empleados), SEEK_SET);
			fwrite(c, sizeof(struct datos_empleados),1,Ptr_fileTxt);
			printf("Empleado modificado con exito\n");

			break;
			
		case 2:
			do
			{
				fflush(stdin);
				printf("Ingrese el nuevo nombre del empleado\n");
				gets(c->nombre);
			}while(validar_nombre(c->nombre));
			
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_empleados), SEEK_SET);
			fwrite(c, sizeof(struct datos_empleados),1,Ptr_fileTxt);
			
			printf("Empleado modificado con exito\n");			
			break;
			
		case 3:
			do
			{
				fflush(stdin);
				printf("Ingrese el nuevo correo del cliente\n");
				gets(c->correo);
			}while(validar_nombre(c->correo));
			
			
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_empleados), SEEK_SET);
			fwrite(c, sizeof(struct datos_empleados),1,Ptr_fileTxt);
			
			printf("Empleado modificado con exito\n");
			break;
		
		case 4:
			printf("--- Nueva fecha de contratacion ---\n");
			do
			{
				fflush(stdin);
				printf("Ingrese dia: \n");
				scanf("%d",&c->fecha_contratacion.dia);
				
				printf("Ingrese mes: \n");
				scanf("%d",&c->fecha_contratacion.mes);
				
				printf("Ingrese anio: \n");
				scanf("%d",&c->fecha_contratacion.ano);			
			}while(validar_formato_fecha(&c->fecha_contratacion) || validar_fecha_no_futura(&c->fecha_contratacion));
			
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
            fwrite(c, sizeof(struct datos_clientes),1,Ptr_fileTxt);
            printf("Fecha modificada con exito\n");
            break;
            
            
        case 5:
            printf("--- Nueva Direccion ---\n");
            
            do
            {
                fflush(stdin);
                printf("Ingrese calle: ");
                gets(c->direccion_empleado.calle);
            }while(validar_nombre(c->direccion_empleado.calle));
            
            do
            {    
                fflush(stdin);
                printf("Ingrese el numero exterior: ");
                scanf("%d", &c->direccion_empleado.num_exterior);
            }while(validar_num_casa(&c->direccion_empleado.num_exterior));
            
            
            do
            {
                fflush(stdin);
                printf("Ingrese colonia: ");
                gets(c->direccion_empleado.colonia);
            }while(validar_nombre(c->direccion_empleado.colonia));
            
            
            do
            {
                fflush(stdin);
                printf("Ingrese municipio: ");
                gets(c->direccion_empleado.municipio);
            }while(validar_nombre(c->direccion_empleado.municipio));
			
		    
            do
            {
                fflush(stdin);
                printf("Ingrese estado: ");
                gets(c->direccion_empleado.estado);
            }while(validar_nombre(c->direccion_empleado.estado));
            
            
            fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
            fwrite(c, sizeof(struct datos_empleados),1,Ptr_fileTxt);
            printf("Direccion modificada con exito\n");
            break;			
		case 7:
			printf("Regresando al menu modificar empleado....\n");
			break;
	}
}

//falta una funcion
void borrar_empleado(FILE*ptr_datfilef)
{
	struct fecha fecha_blanco = {0,0,0};
	struct datos_direcciones direccion_blanco ={" " ,0," "," "," " };
	struct datos_empleados empleado_blanco={0," ", " ",fecha_blanco," "," ", direccion_blanco}, empleadof;
	int del_clave;
	
	do
	{
		fflush(stdin);
		printf("ingrese la clave del empleado a eliminar: \n");
		scanf("%d",&del_clave);
	}while(validar_clave(&del_clave));
	
	fseek(ptr_datfilef, (del_clave-1)*sizeof(struct datos_empleados),SEEK_SET);
	fread(&empleadof, sizeof(struct datos_empleados),1,ptr_datfilef);
	
	if(empleadof.clave == del_clave)
	{
		fseek(ptr_datfilef, (del_clave-1)*sizeof(struct datos_empleados),SEEK_SET);
		fwrite(&empleado_blanco, sizeof(struct datos_empleados),1,ptr_datfilef);
		printf("Empleado eliminado con exito...");	
	}
	else 
		printf("Empleado no encontrado....");
	
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

bool validar_num_casa(int *numf)
{
	bool cambio= false;
	if(*numf<=0)
	{
		cambio = true;
		printf(rojo"ERROR el numero de casa tiene que ser mayor a 0\a\n"reset);
	}
	
	return cambio;
}

bool validar_formato_fecha(struct fecha *fecha_f) 
{
    int dias_por_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool cambio = false;
    
    if (fecha_f->ano < 1900) 
    {
        printf(rojo"ERROR: El ano debe ser mayor o igual a 1900 \a\n"reset);
        cambio = true;
    }
    
    if (fecha_f->mes < 1 || fecha_f->mes > 12) 
    {
        printf(rojo"ERROR: El mes debe estar entre 1 y 12 \a\n"reset);
        cambio = true;
    }

    if (fecha_f->mes == 2) 
    {
        if ((fecha_f->ano % 4 == 0 && fecha_f->ano % 100 != 0) || (fecha_f->ano % 400 == 0)) 
        {
            dias_por_mes[1] = 29;
        } 
        else 
        {
            dias_por_mes[1] = 28;
        }
    }
    
    if (fecha_f->dia < 1 || fecha_f->dia > dias_por_mes[fecha_f->mes - 1]) 
    {
        printf(rojo"ERROR: El dia %d no es valido para el mes %d del ano %d \a\n"reset, 
               fecha_f->dia, fecha_f->mes, fecha_f->ano);
        cambio = true;
    }
    
    return cambio; 
}

bool validar_fecha_no_futura(struct fecha *fecha_f) 
{
    time_t tiempoSeg = time(NULL);
    struct tm *tm_info = localtime(&tiempoSeg);
    bool cambio = false;
    
    struct fecha fecha_actual = {
        tm_info->tm_mday,
        tm_info->tm_mon + 1, 
        tm_info->tm_year + 1900 
    };
    
    
    if (fecha_f->ano > fecha_actual.ano) 
    {
        printf(rojo"ERROR: No puedes ingresar una fecha futura \a\n"reset);
        cambio = true;
    } 
    else if (fecha_f->ano == fecha_actual.ano) 
    {
        if (fecha_f->mes > fecha_actual.mes) 
        {
            printf(rojo"ERROR: No puedes ingresar una fecha futura \a\n"reset);
            cambio = true;
        } 
        else if (fecha_f->mes == fecha_actual.mes && fecha_f->dia > fecha_actual.dia) 
        {
            printf(rojo"ERROR: No puedes ingresar una fecha futura \a\n"reset);
            cambio = true;
        }
    }
    
    return cambio;
}

bool validar_puesto(char *puestof)
{
	bool estado = false;
	int i=0;
	
	while(*(puestof + i) != '\0')
    {
    	*(puestof + i) = toupper(*(puestof + i));
    	i++;
	}
	
	if(strcmp(puestof, "ESTILISTA") != 0 && strcmp(puestof, "COLORISTA") != 0 && strcmp(puestof, "RECEPCIONISTA") != 0 && strcmp(puestof, "COORDINADOR ") != 0 && strcmp(puestof, "MAQUILLADOR") != 0)
    {
        printf(rojo"ERROR: Ingresa un puesto existente(estilista, colorista, recepcionista, coordinador o maquillad) \a\n"reset);
        estado  = true;
    }
	return estado;
}

bool validar_estatus(char *estatusf)
{
	bool estado = false;
	int i=0;
	
	while(*(estatusf + i) != '\0')
    {
    	*(estatusf + i) = toupper(*(estatusf + i));
    	i++;
	}
	
	if(strcmp(estatusf, "PROGRAMADO") != 0 && strcmp(estatusf, "REALIZADO") != 0 && strcmp(estatusf, "CANCELADO"))
    {
        printf(rojo"ERROR: Ingresa un estatusf existente(programado, realizado o cancelado) \a\n"reset);
        estado  = true;
    }
	return estado;	
}
 // areglar impresion
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
					fflush(stdin);
					printf("Ingrese la clave del cliente a consultar\n");
					scanf("%d",&clave_ciliente);
				}while(validar_clave(&clave_ciliente));
				
				fseek(Ptr_fileTxt, (clave_ciliente - 1) * sizeof(struct datos_clientes), SEEK_SET);
				fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
				
				printf("%s\n",clientef.telefono);
				printf("%s\n",clientef.correo);
				
				if(clientef.clave == clave_ciliente)
				{
					printf("%-10s%-20s%-25s%-20s%-30s%-25s\n","CLAVE", "NOMBRE", "FECHA DE NACIMIENTO","TELEFONO", "CORREO", "DIRECCION");
					
					printf("%-10d%-20s%02d/%02d/%-04d%25s    %18s%15s %-1d, %s, %s, %s\n",
					clientef.clave,
					clientef.nombre,
			        clientef.fecha_nacimiento.dia,
				   	clientef.fecha_nacimiento.mes,
					clientef.fecha_nacimiento.ano,
					clientef.telefono,
			        clientef.correo,
	  		        clientef.direccion_cliente.calle,
					clientef.direccion_cliente.num_exterior,
					clientef.direccion_cliente.colonia,
					clientef.direccion_cliente.municipio,
					clientef.direccion_cliente.estado);
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
						printf("%-10s%-20s%-25s%-20s%-30s%-25s\n","CLAVE", "NOMBRE", "FECHA DE NACIMIENTO","TELEFONO", "CORREO", "DIRECCION");
					
						printf("%-10d%-20s%02d/%02d/%-04d%25s    %18s%15s %-1d, %s, %s, %s\n",
						clientef.clave,
						clientef.nombre,
				        clientef.fecha_nacimiento.dia,
					   	clientef.fecha_nacimiento.mes,
						clientef.fecha_nacimiento.ano,
						clientef.telefono,
				        clientef.correo,
		  		        clientef.direccion_cliente.calle,
						clientef.direccion_cliente.num_exterior,
						clientef.direccion_cliente.colonia,
						clientef.direccion_cliente.municipio,
						clientef.direccion_cliente.estado);
						
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
						printf("%-10s%-20s%-25s%-20s%-30s%-25s\n","CLAVE", "NOMBRE", "FECHA DE NACIMIENTO","TELEFONO", "CORREO", "DIRECCION");
						
						printf("%-10d%-20s%02d/%02d/%-04d%25s    %18s%15s %-1d, %s, %s, %s\n",
						clientef.clave,
						clientef.nombre,
				        clientef.fecha_nacimiento.dia,
					   	clientef.fecha_nacimiento.mes,
						clientef.fecha_nacimiento.ano,
						clientef.telefono,
				        clientef.correo,
		  		        clientef.direccion_cliente.calle,
						clientef.direccion_cliente.num_exterior,
						clientef.direccion_cliente.colonia,
						clientef.direccion_cliente.municipio,
						clientef.direccion_cliente.estado);

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

//importante clientes
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
					modificar_menu_clientes(Ptr_fileTxt, &clientef);
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
				
				while(!feof(Ptr_fileTxt) && encontrado)
				{
					fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);

					if(strcmp(clientef.nombre,nombre_ciliente) && !feof(Ptr_fileTxt))
					{
						modificar_menu_clientes(Ptr_fileTxt,&clientef);
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
					printf("Ingrese el telefono del cliente a modificar\n");
					gets(telefono_ciliente);
				}while(validar_telefono(telefono_ciliente));
				
				rewind(Ptr_fileTxt);				
				while(!feof(Ptr_fileTxt) && encontrado)
				{
					fread(&clientef, sizeof(struct datos_clientes),1,Ptr_fileTxt);
					if(strcmp(clientef.telefono,telefono_ciliente) && !feof(Ptr_fileTxt))
					{
						modificar_menu_clientes(Ptr_fileTxt,&clientef);
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

void modificar_menu_clientes(FILE *Ptr_fileTxt, struct datos_clientes *c )
{
	int opc_consulta;
	
	do
	{
		printf("%20s\n", "Que desea modificar del cliente: ");
		printf("%-15s\n","1.-Telefono");
		printf("%-15s\n","2.-Nombre");
		printf("%-15s\n","3.-Correo");
		printf("%-15s\n","4.-Fecha de nacimiento");
		printf("%-15s\n","5.-dirrecion");
		printf("%-15s\n","6.-Salir");
		scanf("%d",&opc_consulta);
	}while(opc_consulta < 1 || opc_consulta > 6);
	
	switch(opc_consulta)
	{
		case 1:
			do
			{
				fflush(stdin);
				printf("Ingrese el nuevo telefono del cliente\n");
				gets(c->telefono);
			}while(validar_telefono(c->telefono));
			
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
			fwrite(c, sizeof(struct datos_clientes),1,Ptr_fileTxt);
			
			printf("Cliente modificado con exito\n");

			break;
			
		case 2:
			do
			{
				fflush(stdin);
				printf("Ingrese el nuevo nombre del cliente\n");
				gets(c->nombre);
			}while(validar_nombre(c->nombre));
			
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
			fwrite(c, sizeof(struct datos_clientes),1,Ptr_fileTxt);
			
			printf("Cliente modificado con exito\n");			
			break;
			
		case 3:
			do
			{
				fflush(stdin);
				printf("Ingrese el nuevo correo del cliente\n");
				gets(c->correo);
			}while(validar_nombre(c->correo));
		
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
			fwrite(c, sizeof(struct datos_clientes),1,Ptr_fileTxt);
			
			printf("Cliente modificado con exito\n");
			break;
		
		case 4:
			printf("--- Nueva fecha de nacimiento ---\n");
			do
			{
				fflush(stdin);
				printf("Ingrese dia: \n");
				scanf("%d",&c->fecha_nacimiento.dia);
				
				printf("Ingrese mes: \n");
				scanf("%d",&c->fecha_nacimiento.mes);
				
				printf("Ingrese anio: \n");
				scanf("%d",&c->fecha_nacimiento.ano);			
			}while(validar_formato_fecha(&c->fecha_nacimiento) || validar_fecha_no_futura(&c->fecha_nacimiento));
			
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
            fwrite(c, sizeof(struct datos_clientes),1,Ptr_fileTxt);
            printf("Fecha modificada con exito\n");
            break;
            
            
        case 5:
            printf("--- Nueva Direccion ---\n");
            
            do
            {
                fflush(stdin);
                printf("Ingrese calle: ");
                gets(c->direccion_cliente.calle);
            }while(validar_nombre(c->direccion_cliente.calle));
            
            do
            {    
                fflush(stdin);
                printf("Ingrese el numero exterior: ");
                scanf("%d", &c->direccion_cliente.num_exterior);
            }while(validar_num_casa(&c->direccion_cliente.num_exterior));
            
            
            do
            {
                fflush(stdin);
                printf("Ingrese colonia: ");
                gets(c->direccion_cliente.colonia);
            }while(validar_nombre(c->direccion_cliente.colonia));
           
            
            do
            {
                fflush(stdin);
                printf("Ingrese municipio: ");
                gets(c->direccion_cliente.municipio);
            }while(validar_nombre(c->direccion_cliente.municipio));
		     
		    
            do
            {
                fflush(stdin);
                printf("Ingrese estado: ");
                gets(c->direccion_cliente.estado);
            }while(validar_nombre(c->direccion_cliente.estado));
            
            
            fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
            fwrite(c, sizeof(struct datos_clientes),1,Ptr_fileTxt);
            printf("Direccion modificada con exito\n");
            break;
			
						
		case 6:
			printf("Regresando al menu modificar cliente....\n");
			break;
	}
}

// hasta aqui

void espacios_blancos(FILE*Ptr_ClientesdatF, FILE*Ptr_EmpleadosdatF, FILE*Ptr_ServiciosdatF, FILE*ptr_agendadatF)
{	
	struct fecha fecha_blanco = {0,0,0};
	struct tiempo tiempo_blanco = {0,0};
	struct datos_direcciones direccion_blanco ={" " ,0," "," "," " };
	struct datos_clientes cliente_blanco={0," ",fecha_blanco," "," ", direccion_blanco};
	struct datos_empleados empleados_blanco={0," "," ",fecha_blanco," "," ",direccion_blanco};
	struct datos_servicios servicios_blanco={0," ",0.0,tiempo_blanco};
	struct datos_agenda agenda_blanco = {0,0,0,0," ",fecha_blanco,0};



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
			fwrite(&empleados_blanco, sizeof(struct datos_empleados), 1, Ptr_EmpleadosdatF);
		
		fclose(Ptr_EmpleadosdatF);
	}
	else
		printf("archivo empleados encontrado\n");
		
	//archivo binario servicios
	if((Ptr_ServiciosdatF = fopen("servicios.dat","r+"))== NULL) 
	{
		printf("No se encontro archivo servicios....creando archivo servicios\n");
		Ptr_ServiciosdatF = fopen("servicios.dat","w");
		
		for(i=0; i<100; i++)
			fwrite(&servicios_blanco, sizeof(struct datos_servicios), 1, Ptr_ServiciosdatF);
		
		fclose(Ptr_ServiciosdatF);
	}
	else
		printf("archivo servicios encontrado\n");
		
	if((ptr_agendadatF = fopen("agenda.dat","r+"))== NULL) 
	{
		printf("No se encontro archivo agenda....creando archivo agenda\n");
		ptr_agendadatF = fopen("agenda.dat","w");
		
		for(i=0; i<100; i++)
			fwrite(&agenda_blanco, sizeof(struct datos_agenda), 1, ptr_agendadatF);
		
		fclose(ptr_agendadatF);
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
	
	do
	{
		fflush(stdin);
		printf("ingrese la clave del usuario a eliminar: \n");
		scanf("%d",&del_clave);
	}while(validar_clave(&del_clave));
	
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

void agregar_servicios(FILE* Ptr_Serviciosdatf)
{
	struct datos_servicios servicio;
	char siono[3];
	
	do
	{
		do
		{
			printf("Ingresa la clave del servicio: \n");
			fflush(stdin);
			scanf("%d", &servicio.clave);
		}while(validar_clave(&servicio.clave) || validar_existencia_clave_servicio(&servicio.clave, Ptr_Serviciosdatf, false));
		
		do
		{
			printf("Ingresa una descripcion del servicio: \n");
			fflush(stdin);
			gets(servicio.descripcion);
		}while(validar_nombre(servicio.descripcion));
		
		do
		{
			fflush(stdin);
			printf("--- Ingrese la duracion del servicio ---\n");
			printf("Ingrese hora: \n");
			scanf("%d",&servicio.duracion.hora);
			
			printf("Ingrese minutos: \n");
			scanf("%d",&servicio.duracion.minutos);
						
		}while(validar_duracion(&servicio.duracion));
		
		do
		{
			printf("Ingresa el precio del servicio: \n");
			scanf("%f",&servicio.precio);
		}while(validar_precio(&servicio.precio));
		
		fseek(Ptr_Serviciosdatf, (servicio.clave - 1) * sizeof(struct datos_servicios), SEEK_SET);
		fwrite(&servicio ,sizeof(struct datos_servicios), 1, Ptr_Serviciosdatf);
		
		do
		{
			printf("Desea agregar un nuevo regristro (Si/No): \n");
			fflush(stdin);
			gets(siono);	
		}while(validar_siono(siono, 1));
		
	}while(validar_siono(siono, 2));
}

bool validar_duracion(struct tiempo *tiempo_f)
{
	bool salir = false;
    if (tiempo_f->minutos < 0 || tiempo_f->minutos > 59) 
	{
        printf("Error: los minutos deben estar entre 0 y 59.\n");
        salir = true;
    }
    if (tiempo_f->hora < 0) {
        printf("Error: la hora no puede ser negativa.\n");
        salir = true;
    }

    if (tiempo_f->hora == 0 && tiempo_f->minutos == 0) {
        printf("Error: la duracion no puede ser 0 horas con 0 minutos.\n");
        salir = true;
    }
    return salir;
}

bool validar_precio(float *preciof)
{
	bool salir = false;
	
	if (*preciof <= 0) 
	{
        printf("Error: el precio debe ser mayor que 0.\n");
        salir =  true;
    }
    if (*preciof > 1000000) 
	{
        printf("Error: el precio es demasiado alto, verifica.\n");
        salir =  true;
    }
    return salir; 
}

void consultar_servicio(FILE* ptrservicio)
{
	struct datos_servicios serviciof={0};
	int opc_consulta,clave_servicio;
	bool encontrado = true;

	do
	{
		do
		{
			printf("%20s\n", "Consultar por: ");
			printf("%-15s\n","1.-Clave");
			printf("%-15s\n","2.-Salir");
			scanf("%d",&opc_consulta);
		}while(opc_consulta < 1 || opc_consulta > 2);
		
		switch(opc_consulta)
		{
			case 1:
				do
				{
					fflush(stdin);
					printf("Ingrese la clave del cliente a consultar\n");
					scanf("%d",&clave_servicio);
				}while(validar_clave(&clave_servicio));
				
				fseek(ptrservicio, (clave_servicio - 1) * sizeof(struct datos_servicios), SEEK_SET);
				fread(&serviciof, sizeof(struct datos_servicios),1,ptrservicio);
				
				if(serviciof.clave == clave_servicio)
				{
					printf("%-20s%-20s%-20s%-20s\n", "CLAVE", "DESCRIPCION", "DURACION DEL SERV", "PRECIO");
					printf("%-20d%-20s%-20d%-20d%-20f",serviciof.clave,serviciof.descripcion,serviciof.duracion.hora,serviciof.duracion.minutos,serviciof.precio);
				}
				else
					printf(rojo"La clave ingresada no existe\n"reset);
				break;
			case 2:
				printf("Regresando al menu empleados...\n");
				break;
		}
		
	}while(opc_consulta != 2);
}

// importante servicios
void modificar_servicio(FILE* ptrservicio)
{
	struct datos_servicios serviciof;
	int opc_consulta,clave_servicio;
	bool encontrado = true;

	do
	{
		do
		{
			printf("%20s\n", "Modificar cliente por: ");
			printf("%-15s\n","1.-Clave");
			printf("%-15s\n","2.-Salir");
			scanf("%d",&opc_consulta);
		}while(opc_consulta < 1 || opc_consulta > 2);
		
		switch(opc_consulta)
		{
			case 1:
				do
				{
					printf("Ingrese la clave del ciliente a modificar\n");
					scanf("%d",&clave_servicio);
				}while(validar_clave(&clave_servicio));
				
				fseek(ptrservicio, (clave_servicio - 1) * sizeof(struct datos_servicios), SEEK_SET);
				fread(&serviciof, sizeof(struct datos_servicios),1,ptrservicio);
				
				if(serviciof.clave == clave_servicio)
				{
					modificar_menu_servicio(ptrservicio, &serviciof);
				}
				else
					printf(rojo"La clave ingresada no existe\n"reset);
				break;
			case 2:
				printf("Gracias por usar el programa\n");
				break;
		}
		
	}while(opc_consulta != 2);
}

void modificar_menu_servicio(FILE *Ptr_fileTxt, struct datos_servicios *c )
{
	int opc_consulta;

	do
	{
		printf("%20s\n", "Que desea modificar del cliente: ");
		printf("%-15s\n","1.-Descripcion");
		printf("%-15s\n","2.-Precio");
		printf("%-15s\n","3.-Tiempo de duracion");
		printf("%-15s\n","4.-Salir");
		scanf("%d",&opc_consulta);
	}while(opc_consulta < 1 || opc_consulta > 4);
	
	switch(opc_consulta)
	{
		case 1:
			do
			{
				fflush(stdin);
				printf("Ingrese la nueva descripcion del servicio\n");
				gets(c->descripcion);
			}while(validar_nombre(c->descripcion));
			
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_servicios), SEEK_SET);
			fwrite(c, sizeof(struct datos_servicios),1,Ptr_fileTxt);
			
			printf("Servicio modificado con exito\n");
			break;
			
		case 2:
			do
			{
				fflush(stdin);
				printf("Ingrese el nuevo precio del servicio\n");
				scanf("%f",&c->precio);
			}while(validar_precio(&c->precio));
			
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_servicios), SEEK_SET);
			fwrite(c, sizeof(struct datos_servicios),1,Ptr_fileTxt);
			printf("Cliente modificado con exito\n");			
			break;
			
		case 3:
			do
			{
				fflush(stdin);
				printf("--- Ingrese la nueva duracion del servicio ---\n");
				printf("Ingrese hora: \n");
				scanf("%d",&c->duracion.hora);
				printf("Ingrese minutos: \n");
				scanf("%d",&c->duracion.minutos);
			}while(validar_duracion(&c->duracion));
			fseek(Ptr_fileTxt, (c->clave - 1) * sizeof(struct datos_clientes), SEEK_SET);
			fwrite(c, sizeof(struct datos_clientes),1,Ptr_fileTxt);
			printf("servicios modificado con exito\n");
			break;				
		case 4:
			printf("Regresando al menu modificar servicios....\n");
			break;
	}
}

// falta una funcion
void borrar_servicio(FILE* ptr_datfilef)
{
	struct tiempo tiempo_blanco = {0,0};
	struct datos_servicios servicio_blanco={0," ",0.0,tiempo_blanco}, serviciof;
	int del_clave;
	
	do
	{
		fflush(stdin);
		printf("ingrese la clave del servicio a eliminar: \n");
		scanf("%d",&del_clave);
	}while(validar_clave(&del_clave));
	
	fseek(ptr_datfilef, (del_clave-1)*sizeof(struct datos_servicios),SEEK_SET);
	fread(&serviciof, sizeof(struct datos_servicios),1,ptr_datfilef);
	
	if(serviciof.clave == del_clave)
	{
		fseek(ptr_datfilef, (del_clave-1)*sizeof(struct datos_servicios),SEEK_SET);
		fwrite(&servicio_blanco, sizeof(struct datos_servicios),1,ptr_datfilef);
		printf("Servicio eliminado con exito...");	
	}
	else 
		printf("Servicio no encontrado....");
}



bool validar_hora(int *horaf)
{
	
}

void agenda(FILE *Ptr_fileagenda, FILE *Ptr_filecliente, FILE *Ptr_fileempleado, FILE *Ptr_fileservicio)
{
	char opc_sub_menu;
	
	do
	{
		do
		{
			printf("%20s\n", "Agenda");
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
			if((Ptr_fileagenda = fopen("agenda.dat","r+")) == NULL || (Ptr_filecliente = fopen("clientes1.dat","r+")) == NULL || (Ptr_fileempleado = fopen("empleados.dat","r+")) == NULL ||  (Ptr_fileservicio = fopen("servicios.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				agregar_agenda(Ptr_fileagenda, Ptr_filecliente,Ptr_fileempleado, Ptr_fileservicio);
				fclose(Ptr_fileagenda);
				fclose(Ptr_filecliente);
				fclose(Ptr_fileempleado);
				fclose(Ptr_fileservicio);
			}
			break;	
			
			case 'c' : case'C': 
			if((Ptr_fileagenda = fopen("agenda.dat","r+")) == NULL )
				printf("No se abrio el archivo");
			else
			{
				consultar_agenda(Ptr_fileagenda);
				fclose(Ptr_fileagenda);
			}
			break;
			
			case 'm' : case'M': 
			if((Ptr_fileagenda = fopen("agenda.dat","r+")) == NULL || (Ptr_filecliente = fopen("clientes1.dat","r+")) == NULL || (Ptr_fileempleado = fopen("empleados.dat","r+")) == NULL ||  (Ptr_fileservicio = fopen("servicios.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				modificar_agenda(Ptr_fileagenda, Ptr_filecliente,Ptr_fileempleado, Ptr_fileservicio);
				fclose(Ptr_fileagenda);
				fclose(Ptr_filecliente);
				fclose(Ptr_fileempleado);
				fclose(Ptr_fileservicio);
			}
			break;		
			
			case 'd': case'D':
			if((Ptr_fileagenda = fopen("agenda.dat","r+")) == NULL)
				printf("No se abrio el archivo");
			else
			{
				borrar_agenda(Ptr_fileagenda);
				fclose(Ptr_fileagenda);
			}
					
		}
	}while(opc_sub_menu != 'S' && opc_sub_menu != 's');
	
}

void agregar_agenda(FILE* Ptr_agendadatf, FILE* Ptr_Clientesdatf, FILE* Ptr_empleadosdatf, FILE*Ptr_serviciosdatf )
{
	struct datos_agenda agenda;
	char siono[3];
	
	do
	{
		do
		{
			fflush(stdin);
			printf("Ingresa el numero de agenda: \n");
			scanf("%d", &agenda.clave);
		}while(validar_clave(&agenda.clave) || validar_existencia_clave_agenda(&agenda.clave, Ptr_agendadatf));
		
		do
		{
			fflush(stdin);
			printf("Ingresa la clave del empleado: \n");
			scanf("%d", &agenda.clave_empleado);
		}while(validar_clave(&agenda.clave_empleado) || validar_existencia_clave_empleado(&agenda.clave_empleado, Ptr_empleadosdatf, true));
		
		do
		{
			fflush(stdin);
			printf("Ingresa la clave del cliente: \n");
			scanf("%d", &agenda.clave_cliente);
		}while(validar_clave(&agenda.clave_cliente) || validar_existencia_clave_cliente(&agenda.clave_cliente, Ptr_Clientesdatf, true));
		
		do
		{
			printf("Ingresa la clave del servicio: \n");
			fflush(stdin);
			scanf("%d", &agenda.clave_servicio);
		}while(validar_clave(&agenda.clave_servicio) || validar_existencia_clave_servicio(&agenda.clave_servicio, Ptr_serviciosdatf, true));
		
		do
		{
			printf("Ingresa el estatus: \n");
			fflush(stdin);
			gets(agenda.estatus);
		}while(validar_estatus(agenda.estatus));
		
		
		do
		{
			fflush(stdin);
			printf("--- Fecha de contratacion ---\n");
			printf("Ingrese dia: \n");
			scanf("%d",&agenda.fecha_agendada.dia);
			
			printf("Ingrese mes: \n");
			scanf("%d",&agenda.fecha_agendada.mes);
			
			printf("Ingrese anio: \n");
			scanf("%d",&agenda.fecha_agendada.ano);			
		}while(validar_formato_fecha(&agenda.fecha_agendada));
				
		
		fseek(Ptr_agendadatf, (agenda.clave - 1) * sizeof(struct datos_agenda), SEEK_SET);
		fwrite(&agenda, sizeof(struct datos_agenda), 1, Ptr_agendadatf);
			
		do
		{
			printf("Desea agregar un nuevo regristro (Si/No): ");
			fflush(stdin);
			gets(siono);	
		}while(validar_siono(siono, 1));
		
	}while(validar_siono(siono, 2));
}

void consultar_agenda(FILE *Ptr_agenda)
{
	struct datos_agenda agendaf={0};
	int opc_consulta,clave_agenda, clave_serivicio;
	struct fecha fecha_consulta;
	bool encontrado;

	do
	{
		do
		{
			printf("\n%20s\n", "Consultar por: ");
			printf("%-15s\n","1.-Numero de agenda");
			printf("%-15s\n","2.-Clave de servicio");
			printf("%-15s\n","3.-Consultar por fecha");
			printf("%-15s\n","4.-Salir");
			scanf("%d",&opc_consulta);
		}while(opc_consulta < 1 || opc_consulta > 4);
		
		switch(opc_consulta)
		{
			case 1:
				do
				{
					fflush(stdin);
					printf("Ingrese la clave del cliente a consultar\n");
					scanf("%d",&clave_agenda);
				}while(validar_clave(&clave_agenda));
				
				fseek(Ptr_agenda, (clave_agenda - 1) * sizeof(struct datos_agenda), SEEK_SET);
				fread(&agendaf, sizeof(struct datos_agenda),1,Ptr_agenda);
				
				if(agendaf.clave == clave_agenda)
				{
					printf("%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n", "CLAVE", "CLAVE EMPLEADO", "CLAVE CLIENTE", "CLAVE SERVICIO", "ESTATUS", "FECHA AGENDADA","HORA");
					printf("%-20d%-20d%-20d%-20d%-20s%-2d/%-1d/%-3d%20d%\n",agendaf.clave, agendaf.clave_empleado,agendaf.clave_cliente, agendaf.clave_servicio, agendaf.estatus, agendaf.fecha_agendada.dia, agendaf.fecha_agendada.mes, agendaf.fecha_agendada.ano, agendaf.hora);
				}
				else
					printf(rojo"La clave ingresada no existe\n"reset);
				break;
				
			case 2:
			    do
			    {
			        fflush(stdin);
			        printf("Ingrese la clave del servicio a consultar\n");
			        scanf("%d",&clave_serivicio);
			    }while(validar_clave(&clave_serivicio));
			    
			    rewind(Ptr_agenda);
			    encontrado = false;
			    
			    
			    while(!feof(Ptr_agenda))
			    {
			        fread(&agendaf, sizeof(struct datos_agenda),1,Ptr_agenda);
			        if(agendaf.clave_servicio == clave_serivicio && !feof(Ptr_agenda))
			        {
			            encontrado = true;
			        }
			    }
			    
			    if(encontrado)
			    {
			        printf("%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n", "CLAVE", "CLAVE EMPLEADO", "CLAVE CLIENTE", "CLAVE SERVICIO", "ESTATUS", "FECHA AGENDADA","HORA");
			        
			        rewind(Ptr_agenda);
			        while(!feof(Ptr_agenda))
			        {
			            fread(&agendaf, sizeof(struct datos_agenda),1,Ptr_agenda);
			            if(agendaf.clave_servicio == clave_serivicio && !feof(Ptr_agenda))
			            {
			                printf("%-20d%-20d%-20d%-20d%-20s%-2d/%-1d/%-3d%20d\n",agendaf.clave, agendaf.clave_empleado,agendaf.clave_cliente, agendaf.clave_servicio, agendaf.estatus, agendaf.fecha_agendada.dia, agendaf.fecha_agendada.mes, agendaf.fecha_agendada.ano, agendaf.hora);
			            }
			        }
			    }
			    else
			    {
			        printf(rojo"La clave de servicio ingresada no existe\n"reset);
			    }
				break;
				
			case 3: 
				do
				{
				    fflush(stdin);
				    printf("--- Ingrese la fecha a consultar ---\n");
				    printf("Ingrese dia: \n");
				    scanf("%d",&fecha_consulta.dia);
				        
				    printf("Ingrese mes: \n");
				    scanf("%d",&fecha_consulta.mes);
				        
				    printf("Ingrese anio: \n");
				    scanf("%d",&fecha_consulta.ano);			
				}while(validar_formato_fecha(&fecha_consulta));
				    
				rewind(Ptr_agenda); 
				encontrado = false;
				    
				while(!feof(Ptr_agenda))
				{
				    fread(&agendaf, sizeof(struct datos_agenda),1,Ptr_agenda);
				    if(!feof(Ptr_agenda) && agendaf.fecha_agendada.dia == fecha_consulta.dia && agendaf.fecha_agendada.mes == fecha_consulta.mes && agendaf.fecha_agendada.ano == fecha_consulta.ano)
				    {
			           encontrado = true;

				    }
				}
				    
				if(encontrado)
				{
				    printf("%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n", "CLAVE", "CLAVE EMPLEADO", "CLAVE CLIENTE", "CLAVE SERVICIO", "ESTATUS", "FECHA AGENDADA","HORA");
				        
				    rewind(Ptr_agenda); 
				    while(!feof(Ptr_agenda))
				    {
				        fread(&agendaf, sizeof(struct datos_agenda),1,Ptr_agenda);
				        if(!feof(Ptr_agenda) && agendaf.fecha_agendada.dia == fecha_consulta.dia && agendaf.fecha_agendada.mes == fecha_consulta.mes && agendaf.fecha_agendada.ano == fecha_consulta.ano)
				        {
				            printf("%-20d%-20d%-20d%-20d%-20s%-2d/%-1d/%-3d%20d\n", agendaf.clave, agendaf.clave_empleado, agendaf.clave_cliente,  agendaf.clave_servicio, agendaf.estatus, 
				                    agendaf.fecha_agendada.dia, agendaf.fecha_agendada.mes, agendaf.fecha_agendada.ano, agendaf.hora);
				                
				            encontrado = false;
				        }
				    }
				}
				else
				{
				    printf(rojo"No se encontraron citas para la fecha %d/%d/%d\n"reset, fecha_consulta.dia, fecha_consulta.mes, fecha_consulta.ano);
				}
				break;
				
				
				case 4:
					printf("Regresando al menu agenda...\n");
					break;
			}
		
	}while(opc_consulta != 4);
}

void modificar_agenda(FILE* ptragenda, FILE *ptrcliente, FILE*ptrempleado, FILE*ptrservicio)
{
	struct datos_agenda agendaf;
	int opc_consulta,clave_agenda;
	bool encontrado = true;

	do
	{
		do
		{
			printf("%20s\n", "Modificar cliente por: ");
			printf("%-15s\n","1.-Clave");
			printf("%-15s\n","2.-Salir");
			scanf("%d",&opc_consulta);
		}while(opc_consulta < 1 || opc_consulta > 2);
		
		switch(opc_consulta)
		{
			case 1:
				do
				{
					printf("Ingrese la clave del ciliente a modificar\n");
					scanf("%d",&clave_agenda);
				}while(validar_clave(&clave_agenda));
				
				fseek(ptragenda, (clave_agenda - 1) * sizeof(struct datos_agenda), SEEK_SET);
				fread(&agendaf, sizeof(struct datos_agenda),1,ptragenda);
				
				if(agendaf.clave == clave_agenda)
				{
					modificar_menu_agenda(ptragenda, ptrcliente, ptrempleado, ptrservicio, &agendaf);
				}
				else
					printf(rojo"La clave ingresada no existe\n"reset);
				break;
			case 2:
				printf("Gracias por usar el programa\n");
				break;
		}
		
	}while(opc_consulta != 7);
}

void modificar_menu_agenda(FILE *ptragendaf, FILE *ptrclientef, FILE * ptrempleadof,  FILE *ptrserviciof, struct datos_agenda *c)
{
		int opc_consulta;

	do
	{
		printf("%20s\n", "Que desea modificar del cliente: ");
		printf("%-15s\n","1.-Clave del empleado");
		printf("%-15s\n","2.-Clave del cliente");
		printf("%-15s\n","3.-Clave del servicio");
		printf("%-15s\n","4.-Fecha agendada");
		printf("%-15s\n","5.-Estatus");
		printf("%-15s\n","6.-Hora");
		printf("%-15s\n","7.-Salir");
		scanf("%d",&opc_consulta);
	}while(opc_consulta < 1 || opc_consulta > 7);
	
	switch(opc_consulta)
	{
		case 1:
			do
			{
				fflush(stdin);
				printf("Ingresa la nueva clave del empleado: \n");
				scanf("%d", &c->clave_empleado);
			}while(validar_clave(&c->clave_empleado) || validar_existencia_clave_empleado(&c->clave_empleado, ptrempleadof, true));
				
			fseek(ptragendaf, (c->clave - 1) * sizeof(struct datos_agenda), SEEK_SET);
            fwrite(c, sizeof(struct datos_agenda),1,ptragendaf);
			
			printf("Servicio modificado con exito\n");
			break;
			
		case 2:
			do
			{
				fflush(stdin);
				printf("Ingresa la nueva clave del cliente: \n");
				scanf("%d", &c->clave_cliente);
			}while(validar_clave(&c->clave_cliente) || validar_existencia_clave_cliente(&c->clave_cliente, ptrclientef, true));
			
			fseek(ptragendaf, (c->clave - 1) * sizeof(struct datos_agenda), SEEK_SET);
            fwrite(c, sizeof(struct datos_agenda), 1, ptragendaf);
			printf("Cliente modificado con exito\n");			
			break;
			
		case 3:
			do
			{
				fflush(stdin);
				printf("Ingresa la nueva clave del servicio: \n");
				scanf("%d", &c->clave_servicio);
			}while(validar_clave(&c->clave_servicio) || validar_existencia_clave_cliente(&c->clave_servicio, ptrserviciof, true));
			
			fseek(ptragendaf, (c->clave - 1) * sizeof(struct datos_agenda), SEEK_SET);
            fwrite(c, sizeof(struct datos_agenda), 1, ptragendaf);
			printf("Cliente modificado con exito\n");			
			break;
			
			
			
		case 4:
			printf("--- Nueva fecha de la cita ---\n");
			do
			{
				fflush(stdin);
				printf("Ingrese dia: \n");
				scanf("%d",&c->fecha_agendada.dia);
				
				printf("Ingrese mes: \n");
				scanf("%d",&c->fecha_agendada.mes);
				
				printf("Ingrese anio: \n");
				scanf("%d",&c->fecha_agendada.ano);			
			}while(validar_formato_fecha(&c->fecha_agendada) || validar_fecha_no_futura(&c->fecha_agendada));
			
			fseek(ptragendaf, (c->clave - 1) * sizeof(struct datos_agenda), SEEK_SET);
            fwrite(c, sizeof(struct datos_agenda),1,ptragendaf);
            printf("Fecha modificada con exito\n");
            break;
			
		case 5:
			do
			{
				fflush(stdin);
				printf("Ingrese el nuevo estatus de la cita\n");
				gets(c->estatus);
			}while(validar_estatus(c->estatus));
			
			fseek(ptragendaf, (c->clave - 1) * sizeof(struct datos_agenda), SEEK_SET);
            fwrite(c, sizeof(struct datos_agenda), 1, ptragendaf);
			
			printf("Servicio modificado con exito\n");
			break;
			
		case 6:
			do
			{
				fflush(stdin);
				printf("Ingresa la nueva hora  de la cita: \n");
				scanf("%d", &c->hora);
			}while(validar_hora(&c->hora));
			
			fseek(ptragendaf, (c->clave - 1) * sizeof(struct datos_agenda), SEEK_SET);
            fwrite(c, sizeof(struct datos_agenda), 1, ptragendaf);
			printf("Cliente modificado con exito\n");			
			break;
							
		case 7:
			printf("Regresando al menu modificar servicios....\n");
			break;
			

	}
}

void borrar_agenda(FILE*ptr_datfilef)
{
	struct fecha fecha_blanco = {0,0,0};
	struct datos_agenda agenda_blanco={0,0,0,0," ",fecha_blanco,0}, agendaf;
	int del_clave;
	
	do
	{
		fflush(stdin);
		printf("ingrese el numero de agendado a eliminar: \n");
		scanf("%d",&del_clave);
	}while(validar_clave(&del_clave));
	
	fseek(ptr_datfilef, (del_clave-1)*sizeof(struct datos_clientes),SEEK_SET);
	fread(&agendaf, sizeof(struct datos_clientes),1,ptr_datfilef);
	
	if(agendaf.clave == del_clave)
	{
		fseek(ptr_datfilef, (del_clave-1)*sizeof(struct datos_agenda),SEEK_SET);
		fwrite(&agendaf, sizeof(struct datos_agenda),1,ptr_datfilef);
		printf("Usuario eliminado con exito...");	
	}
	else 
		printf("Usuario no encontrado....");
	
}
