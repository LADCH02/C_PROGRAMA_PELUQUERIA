#include<stdio.h>

bool validar_sub_menu_reportes(char );


main()
{
	
	char opcRep;
		
	do
	{
		do
		{
			printf("%20s\n", "REPORTE");
			printf("%-15s\n","a.-Listado de empelados por puesto");
			printf("%-15s\n","b.-Listado de listas por estatus");
			printf("%-15s\n","c.-Listado de lista por fecha");
			printf("%-15s\n","d.-Venta por fecha");
			printf("%-15s\n","e.-Generar archivo de clientes");
			printf("%-15s\n","f.-Generar archivo de empleados");
			printf("%-15s\n","g.-Mostrar archivoo");
			printf("%-15s\n","h.-Salir");
			scanf("%d", &opcRep);
			fflush(stdin);
			if(validar_sub_menu_reportes(opcRep))
				printf(rojo"ERROR ingrese un valor correcto\a\n"reset);	
		}while(validar_sub_menu_reportes(opcRep));
		
		switch (opcMain)
		{
			case 'a':			
			
			case 'b':
			
			case 'c':
			
			case 'd':
			
		}
						
	}while(opcRep != 'h');
}


bool validar_sub_menu_reportes(char fopc_sub_menu)
{
	bool cambio = false;
	if(fopc_sub_menu < 'a' || fopc_sub_menu > 'h')
	{	
		cambio = true;
		printf(rojo"ERROR ingrese clave correcta \a\n"reset);
	}	
	return cambio;
}

