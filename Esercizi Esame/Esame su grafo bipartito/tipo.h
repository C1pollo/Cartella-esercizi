/*******************************/
/* HEADER MODULO "tipo" */
/*******************************/



typedef struct{
	char descrizione[20];
	char tipo;
} tipo;

int compare(tipo,tipo);
void copy(tipo&,tipo);
void print(tipo);

/*
	compare(tipo t1, tipo t2): Confronta due strutture tipo prima per il campo tipo (carattere) e, se sono uguali, per la descrizione (stringa).

	copy(tipo& dest, tipo src): Copia il contenuto della struttura src nella struttura dest utilizzando strcpy per la stringa.

	print(tipo t): Stampa a schermo i contenuti della struttura tipo in un formato leggibile.


*/