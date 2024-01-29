/***********************************************************************
*
* @Propòsit: Crear un programa que ajudi a gestionar aquestes 
*             noves millores en el parc de bombers de Prog City.
* @Autor:                        David Susagna Holgado
* @Data de creació:              16/12/2022
* @Data de l'última modificació: 18/12/2022
*
***********************************************************************/
// Llibreries del sistema
#include <stdio.h>
#include <string.h>

// Constants
#define MAX_TEAM 8				// Nombre màxim d'equips.
#define MAX_NAME 30				// Núm. màxim de caràcter del nom dels bombers.
#define MAX_FIREFIGHTERS 9		// Núm. màxim de bombers per equip.
#define MAX_OPERATIONS 100		// Núm. màxim d'operacions d'un bomber.
#define MAX_CHAR 1000			// Núm. màxim de caràcter d'una cadena. 
#define HOUR_MAX 23             // Màximes hores d'un dia.
#define MIN_MAX 59              // Màxims minuts d'una hora
#define MIN_HOUR 60				// Minuts en una hora.
#define MAX_MIN_DAY 1440		// Minuts en un dia.

// Tipus propis
typedef struct {
	char name[MAX_NAME];
	int n_operations;
	int minutes_op[MAX_OPERATIONS];
	int total_min;
} FireFighter;

typedef struct {
	char team_id;
	int n_firefighters;
	FireFighter firefighters[MAX_FIREFIGHTERS];
} Team;


// Procediments i funcions
/***********************************************************************
*
* nº: 1
* @Finalitat:	Modifica un caràcter en el seu equivalent de tipus int.
* @Paràmetres: 	in: a = Caràcter a modificar.
* @Retorn:		Retorna el seu equivalent en format "int".
*
***********************************************************************/
int charToInt(char a){
	int exit = 0;
	
	exit = exit + a - '0';
	return(exit);
}

/***********************************************************************
*
* nº: 2
* @Finalitat:   Modifica dos valors continus com a màxim, del format "char" a "int".
* @Paràmetres:  in: arr[] = cadena de caràcters la qual es vol recorre.
*			    in: i = indicador de la posició de la cadena en la qual començar els dos caràcters anteriors.
* 				in: end = caràcter el qual indica que a cavat la cadena de dos caràcters.
* @Retorn:    	Retorna el valor trobat en el format "int". 
*
***********************************************************************/
int getTimeNum(char arr[], int i, char end){
	int num = 0;
	int num_1 = 0;
	int num_2 = 0;

	while(end != arr[i]){
		num_1 = num_2;
		num_2 = charToInt(arr[i]);
		i++;
	}

	num = num_1*10 + num_2;

	return(num);
}
/***********************************************************************
*
* nº: 3
* @Finalitat:  	Recorre una cadena una sèrie de posicions en fusió d'un caràcter específic.
* @Paràmetres: 	in: i = indicador de la posició de la cadena en la qual començar els dos caràcters anteriors.
*				in: end = caràcter el qual indica que a cavat la cadena de dos caràcters.
*				in: arr[] = cadena de caràcters la qual es vol recorre.
* @Retorn:		Retorna la posició en la qual es troba la cadena, per poder continuar recorrent-la.    
*
***********************************************************************/
int newStringPosition(char arr[], int i, char end){	

	while(end != arr[i]){
		i++;
	}

	return(i);
}
/***********************************************************************
*
* nº: 4
* @Finalitat:	Comprovar si el format d'una hora determinada és correcte o no.
* @Paràmetres: 	in: hour = hora a analitzar.
*				in: min = minuts a analitzar.
* @Retorn:     	Retorna el valor de l'hora en minuts, en el cas que el format sigui incorrecte retorna un -1.
*
***********************************************************************/
int checkTime(int hour, int min){

	int time = -1;
	int format_is_ok = 1;

	if ( ((hour <= HOUR_MAX) && (0 <= hour)) && ((min <= MIN_MAX) && (0 <= min)) ){
		format_is_ok = 0;
		time = ((hour * MIN_HOUR) + min);
    }

    if (format_is_ok){
		printf("(ERROR) Wrong time format\n");
	}

	return(time);
}
/***********************************************************************
*
* nº: 5
* @Finalitat:	Extreu una sèrie de caràcter d'una cadena i la guarda en una altra.
* @Paràmetres:  in: end = caràcter el qual indica que a cavat la cadena de dos caràcters.
*				in: origen[] = cadena de caràcters la qual es vol recorre.
*				in: destino[] = cadena de caràcters la qual es vol guardar la informació extreta.
*				in: i = indicador de la posició de la cadena en la qual començar i acaba.
* @Retorn:     	Retorna la posició en la qual es troba la cadena, per poder continuar recorrent-la.   
*
***********************************************************************/
int cpString(char origen[], char destino[], int i, char end){

	int n = 0;
	char null[MAX_CHAR];

	strcpy(destino, null);
	n = 0;
	while(end != origen[i]){
		destino[n] = origen[i];
		i++;
		n++;
	}
	destino[n] = '\0';

	return (i);
}
/***********************************************************************
*
* nº: 6
* @Finalitat:	Mostra la informació relacionada amb les operacions dels bombers.
* @Paràmetres:  in: all_teams[] array on es troba tota la informació guardada.
				in: k = Indicador del bomber el qual es vol imprimir la informació.
* @Retorn:     	----.
*
***********************************************************************/	
void showOperations(Team all_teams[], int k){
	int j = 0, o = 0;

	printf("Team %c\n", all_teams[k].team_id);
	for(j=0; j<all_teams[k].n_firefighters; j++){
		// Print firefighters name
		printf("\t%s: %d operations\n", all_teams[k].firefighters[j].name, all_teams[k].firefighters[j].n_operations);
		printf("\t[");
		// Print firefighters minutes_op
		for(o=0; o<all_teams[k].firefighters[j].n_operations; o++){
			if (0 < all_teams[k].firefighters[j].minutes_op[o]){
				if(o < (all_teams[k].firefighters[j].n_operations -1)){
					printf("%d ", all_teams[k].firefighters[j].minutes_op[o]);
				}
				else{
					printf("%d", all_teams[k].firefighters[j].minutes_op[o]);
				}
			}
		}
		printf("]\n");
	}
}
/***********************************************************************
*
* nº: 7
* @Finalitat:  	Escaneja la informació escrita per l'usuari i elimina el salt de línia del final.
* @Paràmetres:	in: arr[] = cadena de caràcters on es guardarà la informació.
* @Retorn:     	----.     
*
***********************************************************************/
void scanInformation(char arr[]){

	fgets(arr, MAX_CHAR, stdin);
	arr[strlen(arr)-1] = '\0';  	// Eliminar '\n'.

}
/***********************************************************************
*
* nº: 8
* @Finalitat:	Identificar si l'equip intruït per l'usuari existeix.
* @Paràmetres:	in: all_teams[] = array on es troba tota la informació guardada.
*				in: team =  equip anomenat per l'usuari.
*				in: n_team = el nombre màxim d'equips.
* @Retorn:     	Retorna "1" si l'equip no existeix i "0" en el cas que si que existeixi.
*
***********************************************************************/
int isNotTeam(Team all_teams[], char team, int n_team){
	int team_id_is_ok = 1;
	int k = 0;

	for(k=0; k<n_team; k++){
		if(all_teams[k].team_id == team){
			team_id_is_ok = 0;
		}
	}

	return(team_id_is_ok);
}




int main(){

	// Declaració de variables locals
	int i = 0, k = 0, n = 0, j = 0;						// Variables auxiliar de tipus índex.
	char input[MAX_CHAR];								// Cadena de caràcters es guarda la informació relacionada amb els equips.
	int start = 0;										// Variable per indiciar o no la segona part del programa.
	int n_team = 0;										// Indica el nombre d'equips introduïts.
	Team all_teams[MAX_TEAM];							// Array on es guardarà tora la informació per analitzar.
	int error_1 = 0, error_2 = 0, end = 0, exit = 0;	// Variables auxiliar per finalitzar el programa.
	char opt_p1[MAX_CHAR], opt_p2[MAX_CHAR]; 			// Cadena de caràcters per guarda cada una de les opcions de l'usuari.
	char opt_p3[MAX_CHAR], option[MAX_CHAR]; 			// Cadena de caràcters per guarda cada una de les opcions de l'usuari.
	int select = 0;										// Indica quina és l'opció relaciona per l'usuari.
	int team_id_is_ok = 0;								// Indica si l'equp existeix o no.
	int time_format = 0;								// Indica l'estat correcte o incorrecte del format hora i minut.
	int hour = 0, min = 0, time_in = 0, time_out = 0;	// Variables relacionades amb els tems d'una operació.
	int minut_op = 0;									// Minuts totals d'una operació.
	int lower = 0, lower_firefighters_position = 0;		// Variables relacionades amb el nombre menor de minuts d'una operació.
	int operations_position = 0;						// En quina possessió es guarden els minuts de l'operació.

		
	/*** CODE ***/

	// Output.1 Donar la benvinguda i iniciar el programa.
	printf("Welcome to Prog City! \n");

	// Output.2 Sol·licitar la informació del parc de bombers
	printf("\nInitial info: ");
	// Input.1 Escanejar informació escrita per l'usuari.
	scanInformation(input);

	
	// Bucle per segmentar i guarda la informació escrita per l'usuari.
	n_team = 0;
	i = 0;
	while('.' != input[i]){
		start = 1;

		// Bucle per identificar i guarda l'identificador de l'equip.
		while('/' != input[i]){
			if (('Z' >= input[i]) &&  ('A' <= input[i])){
				all_teams[n_team].team_id = input[i];
	       	 	error_1 = 0;
	    	} 
	    	else{
	    		// Output.3 Mostrar missatge d'error relacionat amb el format de l'identificador de l'equip.
	    		printf("(ERROR) Wrong team id \n");
	    		error_1 = 1;
	    	} 
			i++;
		}

		// Bucle per identificar i guarda el nombre de bombers de l'equip.
		i++;
		while('/' != input[i]){
			// char to int
			all_teams[n_team].n_firefighters = charToInt(input[i]);	
			if((9 >= all_teams[n_team].n_firefighters) && (1 <= all_teams[n_team].n_firefighters)){
    			error_2 = 0;
	    	} 
	    	else{
	    		// Output.3 Mostrar missatge d'error relacionat amb el nombre de bombers de l'equip.
	    		printf("(ERROR) Wrong firefighters number \n");
	    		error_2 = 1;
	    	}
			i++;
		}

		// Bucle per identificar i guarda el nom dels bombers.
		for(j=0; j<all_teams[n_team].n_firefighters; j++){
			i++;
			n = 0;
			while('/' != input[i]){
				if('.' != input[i]){
					all_teams[n_team].firefighters[j].name[n] = input[i];
					i++;
					n++;
					end = 0;
				}
				else{
					input[i] = '/';
					end = 1;

				}
			}
			all_teams[n_team].firefighters[j].name[n] = '\0';
			all_teams[n_team].firefighters[j].n_operations = 0;
		}


		n_team++;
		i++;
		// Condicional per tancar el bucle de forma sobtada.
		if( (1 == error_1) || (1 == error_2) || (1 == end) ){
			input[i] = '.';
		}
	}



	// Condicional per iniciar la segona part del problema en cas que tota la informació sigui correcta.
	if( (0 == error_1) && (0 == error_2) && (1 == start) ){
		exit = 0;

		// Bucle per dedicar al menú "Prog City > ".
		while(1 != exit){

			select = 0;
			// Output.4 Sol·licitar la informació relacionada amb el menú "Prog City >".
			printf("\nProg City > ");
			// Input.2 Escanejar informació escrita per l'usuari.
			scanInformation(option);
			
			// Classificació de la informació, en 3 grups.
			i = 0;
			i = cpString(option, opt_p1, i, ' ');
			i++;
			i = cpString(option, opt_p2, i, ' ');
			i++;
			i = cpString(option, opt_p3, i, '\0');
			
			
			// Identificar quina és l'opció escollida per l'usuari.
			if(0 == strcmp(opt_p1, "show")){
				if (0 == strcmp(opt_p2, "operations")){
					select = 5;
				}
				else {
					select = 2;
				}
			}

			if(0 == strcmp(opt_p1, "add")){
				select = 3;
			}

			if(0 == strcmp(opt_p1, "operation")){
				select = 4;
			}

			if(0 == strcmp(opt_p1, "exit")){
				select = 6;
			}

			// Condicional per oferir a l'usuari la informació reclamada entarimant en l'input 2,
			switch(select){

				// 2.2 Comanda “show”
				case 2:
					for(k = 0; k<(n_team); k++){
						// Output.5 Mostra la informació de tots els equips.
						printf("Team %c\n", all_teams[k].team_id);
						for(j = 0; j < all_teams[k].n_firefighters; j++){
							printf("\t%s\n",all_teams[k].firefighters[j].name);
						}
					}
					break;

				// 2.3 Comanda “add”
				case 3:
					team_id_is_ok = isNotTeam(all_teams, opt_p2[0], n_team);

					if(team_id_is_ok){
						// Output.6 L'equip indicat no existeix.
						printf("(ERROR) Team %c does not exist \n", opt_p2[0]);
					}
					else{
						for(k=0; k<n_team; k++){
							// Condicional per idèntica quin és l'equip seleccionat per l'usuari.
							if(all_teams[k].team_id == opt_p2[0]){
								if(all_teams[k].n_firefighters < MAX_FIREFIGHTERS){
									// Ampliar el nombre de bombers dins l'equip.
							        all_teams[k].n_firefighters++;

							        // Guardar el nom del bomber.
							        i = 0;
									i = cpString(opt_p3, all_teams[k].firefighters[(all_teams[k].n_firefighters - 1)].name, i, '\0');
								}
								else{
									// Output.7 L'equip no pot enregistrar més bomber esta ple.
									printf("(ERROR) Team %c is full \n", all_teams[k].team_id);
								}
							}
						}	
					}
					break;

				// 2.4 Comanda “operation”
				case 4:
					team_id_is_ok = isNotTeam(all_teams, opt_p2[0], n_team);

					if(team_id_is_ok){
						// Output.6 L'equip indicat no existeix.
					    printf("(ERROR) Team %c does not exist \n", opt_p2[0]);
					}
					else{
						time_format = 1;
						for(k=0; k<n_team; k++){
							if(all_teams[k].team_id == opt_p2[0]){

								// Enregistra hores del temps d'inici de l'operació.
						    	i = 0;
						    	hour = getTimeNum(opt_p3,i, ':');
						    	i = newStringPosition(opt_p3,i, ':');

						    	// Enregistra minuts del temps d'inici de l'operació.
					    		i++;
						    	min = getTimeNum(opt_p3,i, '-');
						    	i = newStringPosition(opt_p3,i, '-');
						    	time_in = checkTime(hour, min);

						    	// Condicional per indicar que el format del temps d'inici és correcte.
								if(-1 != time_in){
						    		// Enregistra hores del temps final de l'operació.
								    i++;
							    	hour = getTimeNum(opt_p3,i, ':');
							    	i = newStringPosition(opt_p3,i, ':');

							    	// Enregistra minuts del temps final de l'operació. 
						    		i++;
							    	min = getTimeNum(opt_p3,i, '\0');
							    	time_out = checkTime(hour, min);
							    	if(-1 != time_out){
							    		time_format = 0;
							    	}
						    	}

						    	// Condicional per indicar que el format del temps d'inici i final és correcte.
						    	if(!time_format){

						    		// Calcular minuts totals de l'operació.
						    		minut_op = 0;
						    		// Calcular minuts totals de l'operació.
									if (time_in < time_out) {
										minut_op = time_out - time_in;
									}
									else{
										minut_op = minut_op + ((MAX_MIN_DAY - time_in) + time_out);
									}

									// Buscar el bomber amb el menor nombre de minuts treballs.
									lower = all_teams[k].firefighters[0].total_min;
									lower_firefighters_position = 0;
									for(j=1; j<all_teams[k].n_firefighters; j++){

										if((all_teams[k].firefighters[j].total_min < lower) && (all_teams[k].firefighters[j].n_operations <= MAX_OPERATIONS) ){
											lower = all_teams[k].firefighters[j].total_min;
											lower_firefighters_position = j;
										}
									}

									// Guarda minuts de l'operació en el bomber corresponent.
									all_teams[k].firefighters[lower_firefighters_position].n_operations++;
									operations_position = all_teams[k].firefighters[lower_firefighters_position].n_operations - 1;
									all_teams[k].firefighters[lower_firefighters_position].minutes_op[operations_position] = minut_op;

									// Actualitzar el temps màxim treballat del bomber.
									all_teams[k].firefighters[lower_firefighters_position].total_min  = all_teams[k].firefighters[lower_firefighters_position].total_min + minut_op;
						    	}
							}
						}
					}
					break;

				// 2.5 Comanda “show operations” 
				case 5:	
					team_id_is_ok = isNotTeam(all_teams, opt_p3[0], n_team);

					if (('Z' >= opt_p3[0]) &&  ('A' <= opt_p3[0])){
				        if(team_id_is_ok){
				        	// Output.6 L'equip indicat no existeix.
						    printf("(ERROR) Team %c does not exist \n", opt_p3[0]);
						}
						else{
							for(k=0; k<n_team; k++){
								if(all_teams[k].team_id == opt_p3[0]){
									// Output.9 Mostrar per pantalla la informació de les operacions relacionades amb l'equip sol·licitat.
									showOperations(all_teams, k);
								}
							}
						}
				    }
				    else{
				    	if (0 == strcmp(opt_p3, "all")){
							for(k=0; k<n_team; k++){
								// Output.8 Mostrar per pantalla la informació de tots els equips i les seves operacions.
								showOperations(all_teams, k);
							}
						}
				    }
					break;


				// 2.6 Comanda “exit” 
				case 6:
					exit = 1;
					break;
			}
		}
	}		
	// Output. L'opció “Quit” finalitza l'execució del programa.
    printf("\nSee you later!\n");

	return 0;
}			