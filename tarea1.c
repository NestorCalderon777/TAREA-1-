#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"TDA/list.c"
#include"TDA/queue.h"
#include"TDA/stack.h"
#include"TDA/list.h"
#include <ctype.h>

// DEFINICION DE LAS PRIORIDADES
#define ALTO 1
#define MEDIO 2
#define BAJO 3

// ESTRUCTURA DEL TICKET
typedef struct{
    int ID; // ID DEL TICKET
    char descripcion[1001]; // DESCRIPCION DEL PROBLEMA
    int prioridad; // PRIORIDAD DEL PROBLEMAS
    char horaDelRgistro[9]; // HORA DEL REGISTRO EN EL FORMATO HH:MM:SS
} Ticket;

// FUNCION QUE OBTIENE LA HORA DEL REGISTRO EN EL FORMATO HH:MM:SS
void obtenerHora(char *horaDelRegistro){
    time_t tiempo;
    struct tm *tm_info;

    time(&tiempo); // OBTIENE EL TIEMPO ACTUAL
    tm_info = localtime(&tiempo);

    // FORMATO HH:MM:SS
    strftime(horaDelRegistro, 9, "%H:%M:%S", tm_info);
}

// FUNCION QUE BUSCA Y ELIMINA UN TICKET CON SU ID
Ticket *buscarYEliminarPorID(Queue *cola, int id){

    //SI LA COLA NO EXISTE
    if(!cola) return NULL;

    //PRIMER TICKET DE LA COLA
    Ticket *ticket = list_first(cola);

    //RECORRO LA COLA HASTA EL FINAL
    while(ticket != NULL){
        if(ticket->ID == id){
            Ticket *buscado = ticket;
            list_popCurrent(cola);
            return buscado;
        }

        //SI NO ERA EL TICKET PASO AL SIGUIENTE
        ticket = list_next(cola);
    }

    //SI NO LO ENCUENTRA 
    return NULL;
}

// FUNCION QUE ACTUALIZA LA PRIORIDAD DE UN TICKET 
void asignarPriori(Queue *alta, Queue *media, Queue *baja){

    //GUARDO EL ID
    int id;
    printf("Ingrese el ID del ticket al que desea cambiar la prioridad: ");
    scanf("%d", &id);
    getchar();

    //BUSQUEDA DEL TICKET
    Ticket *ticket = buscarYEliminarPorID(alta, id);
    //SI NO ENCONTRO EL TICEKT AUN 
    if(!ticket) ticket = buscarYEliminarPorID(media, id);
    if(!ticket) ticket = buscarYEliminarPorID(baja, id);

    //MENSAJE SI NO ENCUENTRA EL ID EN LAS COLAS
    if(!ticket){
        printf("\nNO SE LOGRO ENCONTRAR EL TICKET. intente nuevamente\n");
        return;

    }

    //GUARDAMOS LA NUEVA PRIORIDAD EN EL OTRO CASO
    int newPrioridad;
    printf("\nIngrese la nueva prioridad (1--> AltO, 2--> Medio, 3--> Bajo):");
    scanf("%d", &newPrioridad);
    getchar();

    //ACTUALIZAMOS DICHA PRIORIDAD
    ticket->prioridad = newPrioridad;

    //GUARDAMOS EL TICKET EN SU COLA CORRESPONDIENTE
    switch (newPrioridad){
        case ALTO: queue_insert(alta, ticket); break;
        case MEDIO: queue_insert(media, ticket); break;
        case BAJO: queue_insert(baja, ticket); break;
        default:
            printf("LA PRIORIDAD NO ES VALIDA. mantiene su actual prioridad\n");
            break;
    }

    printf("TU NUEVA PRIORIDAD YA ESTA LISTA!\n");
}

void mostrarPendientes(Queue *alta, Queue *media, Queue *baja){

    //AGRUPO LAS COLAS EN UN ARREGLO
    Queue *colas[] = {alta, media, baja};

    //LOS MISMO PARA LOS NOMBRES DE LAS PRIORIDADES
    char *prioridades[] = {"ALTA", "MEDIA", "BAJA"};

    //RECORRO LAS 3 PRIORIDADES
    for(int k = 0 ; k < 3 ; k++){
        printf("\n---- Tickets con prioridad %s ----\n", prioridades[k]);

        //VERIFICO SI LA COLA ESTA VACIA
        if(list_size(colas[k]) == 0){
            printf("NO HAY TICKETS CON ESTA PRIORIDAD.\n");
            printf("------------------------------------\n");
            continue;
        }

        //GUARDA EL PRIMER TICKET 
        Ticket *ticket = list_first(colas[k]);

        //RECORRO TODOS LOS TICKETS
        while(ticket!= NULL){
            printf("ID: %d\n", ticket->ID);
            printf("Descripcion: %s\n", ticket->descripcion);
            printf("Hora de registro: %s\n", ticket->horaDelRgistro);
            printf("------------------------------------\n");

            ticket = list_next(colas[k]);
        }
    }
}

// FUNCION QUE BUSCA UN ID EN LA COLAS
Ticket *buscarPorID(Queue *cola, int id){

    //SI LA COLA NO EXISTE
    if(!cola) return NULL;

    //PRIMER TICKET DE LA COLA
    Ticket *firstTicket = list_first(cola);

    //BUSCO EL ID EN LA COLA
    while(firstTicket){
        if(firstTicket->ID == id){
            return firstTicket;
        }
        //SI NO ES IGUAL SIGO BUSCANDO
        firstTicket = list_next(cola);

    }
    //NO ENCRONTRO EL ID
    return NULL;
}

//FUNCION QUE PROCESA EL SIGUEINTE TICKET EN BASE A SU PRIORIDAD
void procesarSiguiente(Queue *alta, Queue *media, Queue *baja){

    Ticket *ticket = NULL;
    
    //PROCESAMOS POR LA PRIORIDAD EN ORDEN ALTA, MEDIA Y BAJA
    if(list_size(alta) > 0){
        ticket = list_first(alta);
        list_popCurrent(alta); 
        printf("\nProcesando ticket de PRIORIDAD ALTA...\n");
    }
    else if(list_size(media) > 0){
        ticket = list_first(media);
        list_popCurrent(media);
        printf("\nProcesando ticket de PRIORIDAD MEDIA...\n");

    }
    else if(list_size(baja) > 0){
        ticket = list_first(baja);
        list_popCurrent(baja);
        printf("\nProcesando ticket de PRIORIDAD BAJA...\n");

    } else {
        printf("\nNo hay tickets pendientes en ninguna cola.\n");
        return;
    }

    //MOSTRAR EL TICKET PROCESADO
    printf("ID: %d\n", ticket->ID);
    printf("Descripción: %s\n", ticket->descripcion);
    printf("Hora de registro: %s\n", ticket->horaDelRgistro);
    printf("Procesamiento completado.\n");

    //LIBER MEMORIA DEL TICKET
    free(ticket);
}


//FUNCION QUE BUSCA UN TICKET POR SU ID
void buscarID(Queue *alta, Queue *media, Queue *baja){

    //GUARDO EL ID 
    int id;
    printf("Ingrese el ID del ticket que desea buscar: ");
    scanf("%d", &id);
    getchar(); //SALTO DE LINEA

    //RECORRO LAS COLAS BUSCANDO EL ID
    Ticket *ticket = buscarPorID(alta, id);
    if(!ticket) ticket = buscarPorID(media, id);
    if(!ticket) ticket = buscarPorID(baja, id);

    //SI LOGRO ENCONTRAR EL TICKET MUESTRO EL TICKET, SI NO UN MENSAJE DE QUE NO FUE ENCONTRADO
    if(ticket){
        printf("\nSu ticket fue encontrado con exito:\n");
        printf("ID: %d\n", ticket->ID);
        printf("Descripción: %s\n", ticket->descripcion);
        printf("Hora de registro: %s\n", ticket->horaDelRgistro);
        printf("Prioridad: ");
        
        switch(ticket->prioridad){
            case ALTO: printf("Alto\n"); break;
            case MEDIO: printf("Medio\n"); break;
            case BAJO: printf("Bajo\n"); break;
            default: printf("Desconocida\n"); break;
        }
    } else {
        printf("\nEL TICKET NO FUE ENCONTRADO :(\n");
    }
}


// FUNCION QUE REGISTRA EL TICKET
void registrarTicket(Queue *baja){

    //ASIGNAMOS MEMORIA AL NUEVO TICKET SI NO MUESTRA UN MENSAJE DE ERROR
    Ticket *nuevoTicket = malloc(sizeof(Ticket));
    if(nuevoTicket == NULL){
        printf("###ERROR###\n");
        return;
    }

    //ENTRADA DEL CLIENTE OBTENER SU ID Y DESCRIPCION
    printf("ingrese el ID del ticket: ");
    scanf("%d", &nuevoTicket->ID);
    getchar(); // SALTO DE LINEA 
    printf("ingrese la descripcion del problema: ");
    fgets(nuevoTicket->descripcion, sizeof(nuevoTicket->descripcion), stdin); // DECLARA EL TAMAÑO QUE TENDRA MI DESCRIPCION INGRESADA POR EL TECLADO
    nuevoTicket->descripcion[strcspn(nuevoTicket->descripcion, "\n")] = '\0'; // ELIMINA EL SALTO DE LINEA REMPLAZANDOLO CON UN CARACTER NULO
    //ASIGNAR LA PRIORIDAD POR DEFECTO
    nuevoTicket->prioridad = BAJO;

    //OBTENER LA HORA DEL REGISTRO
    obtenerHora(nuevoTicket->horaDelRgistro);

    //INSERTAR EL TICKET EN LA COLA DE PRIORIDAD BAJA
    queue_insert(baja, (void*)nuevoTicket);

    //MOSTRAR RESULTADO
    printf("\nTicket registrado con exito!\n");
    printf("----------------------------\n");
    printf("ID: %d\n", nuevoTicket->ID);
    printf("Descripcion: %s\n", nuevoTicket->descripcion);
    printf("Prioridad: Bajo\n");
    printf("Hora de registro: %s\n", nuevoTicket->horaDelRgistro);
}

void menu(){
    //MOSTRAR MENU DE OPCIONES
    printf("\n--- SISTEMA DE TICKETS ---\n");
    printf("1. Registrar ticket\n");
    printf("2. Asignar prioridad\n");
    printf("3. Mostrar tickets pendientes\n");
    printf("4. Procesar siguiente ticket\n");
    printf("5. Buscar ticket por ID\n");
    printf("6. Salir\n");
    printf("Seleccione opcion: ");
}

int main(){

    //CREA LAS COLAS CON PRIORIDAD
    Queue *alta = queue_create(NULL);
    Queue *media = queue_create(NULL);
    Queue *baja = queue_create(NULL);

    //NUMERO INGRESADO
    char opcion;

    do {
        //MUESTRO EL MENU Y GUARDO LA OPCION
        menu();
        scanf(" %c", &opcion);
        getchar();

        switch (opcion){
            case '1': registrarTicket(baja); break;
            case '2': asignarPriori(alta, media, baja); break;
            case '3': mostrarPendientes(alta, media, baja); break;
            case '4': procesarSiguiente(alta, media, baja); break;
            case '5': buscarID(alta, media, baja); break;
            case '6': printf("--------> SALIENDO DEL PROGRAMA...."); break;
            default:
                printf("\nLA OPCION NO ES VALIDA!\n"); 
                printf("POR FAVOR INTENTE NUEVAMENTE.\n");
                break;
        }
    } while(opcion != '6');

    // LIBERAR LA MEMORIA DE LAS COLAS
    queue_clean(alta);
    queue_clean(media);
    queue_clean(baja);

    return 0;
}