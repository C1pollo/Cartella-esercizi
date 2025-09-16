

#include <stdio.h>
#include <string.h>

    struct persona {
        char cognome[31];
        char nome[31];
        char sesso;
        int anno;
    };
    typedef struct persona* people;


int main (){

    int is_closed;
    FILE* f = fopen("people.dat", "wb+");

    if(f== NULL){
        fprintf(stderr, "Errore apertura file\n");
        return 1;
    }

    struct persona p;

    strncpy(p.cognome,"Rossi", 30);
    strncpy(p.nome, "Mario", 30);
    p.sesso = 'M';
    p.anno = 1990;


    //DEVO SCRIVERE L'ìINTERA STRUTTURA DEL FILE

    fwrite(&p, sizeof(struct persona), 1, f );

    fseek(f,0,SEEK_SET);

    int count=0;
    struct persona c;
    //PER LEGGERE ESSENDO CHE è UN FILE BINARIO .DAT
while (fread(&c, sizeof(struct persona), 1, f) == 1) {
        count++;
        printf("Persona %d:\n", count);
        printf("  Cognome: %s\n", c.cognome);
        printf("  Nome:    %s\n", c.nome);
        printf("  Sesso:   %c\n", c.sesso);
        printf("  Anno:    %d\n", c.anno);
        printf("\n");
    };
    
    is_closed = fclose(f);
    if (is_closed == EOF){
        fprintf(stderr, "Erore chiusura file\n");
        return 1;
    }




    return 0;
}


