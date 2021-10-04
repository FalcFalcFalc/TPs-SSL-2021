#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct 
{
	char especie[6];
	float compra, venta, apertura, min, max, variacion;

} Cotizacion;

void corregirPuntuacion(char * string){
	int i;
	char retorno[20];
	for(i = 0;i<sizeof(string)/sizeof(string[0]);i++){
		if(string[i] == '.'){ //en caso de que haya un punto,
			char * pDest = string; //guardamos el string original.
			while(*string){ //mientras la direccion a la que apunta sea valida,
				if(*string != '.'){ //y siempre que la direccion apuntada no sea un punto,
					*pDest++ = *string; //guardamos la direccion
				} //si la direccion apuntada fuese un punto, no guardamos la direccion, por ende se borra en el resultado final
				string++;
			}
		}
		if(string[i] == ','){ //simplemente sobreescribimos las comas por puntos
			string[i] = '.';
		}
	}
}

avanzarHastaMayor(char **p){ 	//no logré hacer que funcione, es un algoritmo
	while(**p != '>')		 	//tan simple que me dió verguenza rendirme...
		*p++;				 
	*p++;
}

void displayInput(){
	printf("Ingrese 1 o A para ver por pantalla las especies cuyas variaciones sean negativas\n");
	printf("Ingrese 2 o B para generar una planilla CSV de todas las especies\n");
	printf("Ingrese 3 o C para generar una planilla en HTML de las especies cuyas variaciones sean negativas\n");
	printf("\nIngrese 0 para salir\n");

}

int main()
{
    FILE *a = popen("wget -q - https://bolsar.info/lideres.php -O html.html", "r");
    pclose(a); // me hubiera encantado usar el pipeline para hacer el scrapping, pero esta es la mejor solución que encontré.
    FILE *f = fopen("html.html","rt");
    char *pchar;
    char buffer[2048];
    char especie[6];
	int fila = 0;
	int i;
	bool tablaEncontrada = false;
	
	Cotizacion tabla[100];
	
    if (f != NULL)
    {
        while (fgets(buffer,sizeof(buffer),f))
        {
        	if(!tablaEncontrada){
        		if(strstr(buffer, "<table ")){ 	//como en la pagina unicamente hay una tabla,
        			tablaEncontrada = true;		//pregunto si en el buffer se encuentra la tabla
				}								//eso nos adelanta mucho texto del html que no necesitamos
			}									//incluso si el 'onclick' que buscamos no esta en el mismo buffer que '<table ', nos sirve igual porque estará en los siguientes
			if ((pchar = strstr(buffer, "onclick=")) && tablaEncontrada) //en caso de haberlo encontrado, nos ponemos a trabajar con el scrapping
            {
				
                /* ESPECIE */
                
                i = 0;
                
                while (*pchar != '>')
                    pchar++;
                pchar++;
                //avanzarHastaMayor(pchar);
                
                while(*pchar != '<'){
                    tabla[fila].especie[i] = *pchar;
                    i++;
                    pchar++;
                }
    
                tabla[fila].especie[i] = '\0';
                
                /* COMPRA */
                
                i = 0;
                for(i; i<3; i++){ //hace falta saltarse tres casillas para ir a compras
	               pchar = strstr(pchar, "<td");
	               pchar++;
				}
				
            	char recoleccion[20]; //recoleccion lo uso para convertir char[]s en floats con atof()
            	
				i = 0;
				
                while (*pchar != '>')
                    pchar++;
                pchar++;
                //avanzarHastaMayor(pchar);
				                
                while(*pchar != '<'){
                    recoleccion[i] = *pchar;
                    i++;
                    pchar++;
                }
                recoleccion[i] = '\0';
                corregirPuntuacion(recoleccion);
                
				tabla[fila].compra = atof(recoleccion);
				
				/* VENTA */
				
				pchar = strstr(pchar, "<td");
	            
                i = 0;
                
                while (*pchar != '>')
                    pchar++;
                pchar++;
                //avanzarHastaMayor(pchar);
                
				while(*pchar != '<'){
                    recoleccion[i] = *pchar;
                    i++;
                    pchar++;
                }
                recoleccion[i] = '\0';				
				corregirPuntuacion(recoleccion);
                
				tabla[fila].venta = atof(recoleccion);
				
                /* VARIACION */
                
                pchar = strstr(buffer, "<span");
                
                i = 0;
                
				while (*pchar != '>')
                    pchar++;
                pchar++;
                //avanzarHastaMayor(pchar);
                
				while(*pchar != '%'){
                    recoleccion[i] = *pchar;
                    i++;
                    pchar++;
                }
                recoleccion[i] = '\0';
                corregirPuntuacion(recoleccion);

				tabla[fila].variacion = atof(recoleccion);
                
               	/* VENTA */
				
				pchar = strstr(pchar, "<td");
	            
                i = 0;
                
                while (*pchar != '>')
                    pchar++;
                pchar++;
                //avanzarHastaMayor(pchar);
                
				while(*pchar != '<'){
                    recoleccion[i] = *pchar;
                    i++;
                    pchar++;
                }
                recoleccion[i] = '\0';				
				corregirPuntuacion(recoleccion);
                
				tabla[fila].apertura = atof(recoleccion);
                
                /* MIN */
				
				pchar = strstr(pchar, "<td");
	            
                i = 0;
                
                while (*pchar != '>')
                    pchar++;
                pchar++;
                //avanzarHastaMayor(pchar);
                
				while(*pchar != '<'){
                    recoleccion[i] = *pchar;
                    i++;
                    pchar++;
                }
                recoleccion[i] = '\0';				
				corregirPuntuacion(recoleccion);
                
				tabla[fila].min = atof(recoleccion);
                
            	/* MAX */
				
				pchar = strstr(pchar, "<td");
	            
                i = 0;
                
                while (*pchar != '>')
                    pchar++;
                pchar++;
                //avanzarHastaMayor(pchar);
                
				while(*pchar != '<'){
                    recoleccion[i] = *pchar;
                    i++;
                    pchar++;
                }
                recoleccion[i] = '\0';				
				corregirPuntuacion(recoleccion);
                
				tabla[fila].max = atof(recoleccion);
                
                fila++;
            }
        }
        pclose(f);
	}
	char input;
	FILE *html, *csv;

	displayInput();

	while((input = getchar())!= '0'){
		switch(input){
			case '1':
			case 'A':
			case 'a':
				
				printf("\nMOSTRANDO ESPECIES CUYAS VARIACIONES SON NEGATIVAS\nN.| Nombre	| Variacion 	\n==================================================\n");
				
			    for(i = 0; i<fila;i++){
			
					if(tabla[i].variacion < 0){
						if(i < 9) printf(" %d",i+1);
						else printf("%d",i+1);
					
			    		printf("| %s  	  %.2f%c %c\n", tabla[i].especie, tabla[i].variacion, '%', 25);
					}
				}
				
			    printf("==================================================\n\n");
				
				break;
				
			case '2':
			case 'B':
			case 'b':
				
				printf("\nGENERANDO PLANILLA CSV DE COTIZACIONES\n======================================\n");
				
				csv = fopen("listadoDeCotizaciones.csv","wt");
			
				fprintf(csv,"Especie; Precio de compra; Precio de venta; Apertura; Precio Máximo; Precio Mínimo\n");
				for(i=0;i<fila;i++){
					fprintf(csv,"%s; %.2f; %.2f; %.2f; %.2f; %.2f;\n", tabla[i].especie, tabla[i].compra, tabla[i].venta, tabla[i].apertura, tabla[i].max, tabla[i].min);
				}
				
				fclose(csv);
				
				printf("listadoDeCotizaciones.csv CREADO CORRECTAMENTE\n==============================================\n\n");
				
				break;
			case '3':
			case 'C':
			case 'c':
								
				printf("\nGENERANDO LISTADO HTML DE VARIACIONES\n=====================================\n");


				html = fopen("reporteVariaciones.html","wt");
				
				fprintf(html,"<html><head><title>Listado de Variaciones</title></head><body><h1>Reporte de Variaciones</h1><table border=\"1px\">\n");
				
				for(i = 0; i<fila;i++){
			    	if(tabla[i].variacion < 0){
			    		if(tabla[i].compra < tabla[i].apertura && tabla[i].venta < tabla[i].apertura){
							fprintf(html,"<tr style=\"background-color:#336633; color:#00ff00;\">");
				    	}
				    	else{
				    		fprintf(html,"<tr>");
						}
						fprintf(html,"<td>%i</td><td>%s</td><td>%.2f%\%</td></tr>\n", i+1, tabla[i].especie, tabla[i].variacion);
					}
				}
				
				fprintf(html,"</table></body></html>");
				
				fclose(html);
				
				printf("reporteVariaciones.html CREADO CORRECTAMENTE\n============================================\n\n");
				
				break;
			case '\n': //al ingresar un input, el while corría dos veces, y era porque tomaba el enter como otro input adicional, y entraba en el caso Default
				break;
			default:
				printf("\n=========================\nNo se reconocio el input.\n=========================\n\n");
				break;
		}
		
		if(input != '\n') displayInput();

	}
	
    return 0;
}
