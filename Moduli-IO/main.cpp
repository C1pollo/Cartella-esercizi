
#include <stdio.h>

#include <string.h>

int main() {

    char s[] = "Hello World";
    int a[5] = {1, 2, 3, 4, 5};
    unsigned i;
    int fcheck;
    int is_closed;



    FILE* f=NULL;               //importante per il file 


    //Aprire il file 

    f = fopen("ilmiofile", "w");                    //apre ilmiofile in funzione di w, cioè scrittura
                                                    //se successo restituisce un puntatore alla struttura file che rappresenta il file aperto
    if (f==NULL)
    {
        fprintf(stderr, "impossibile aprire il file\n");            //di norma non me lo stampa, e nel caso lo stampasse andiamo a vederelo in stderr
        return 1;
    }


    fcheck = fprintf(f, "%d", a[0]);                        //scrive in un file puntato un carattere con un tipo, e alla fine restituisce il numero di caratteri scritti all'inerno del file 
                                                              //se vogliamo andare a capo ogni volta posso usare \n
                                                              //in teoria deve analizzare la stringa di formato 
                                                              //convertire i valori nei tipio specificati
                                                              //formatta l'uotput secondo le specifiche 


     for(i=1 ; i < 5 && fcheck > 0 ; i++) 
        {                      //struttura classica O(n) per scrivere nel file tutti gli elementi di un array fino a quando dentro non c'è niente oppure arriviamo alla fine
            fcheck = fprintf(f, " %d", a[i]);
        }

        if(fcheck <= 0)
        {
            fprintf(stderr, "Impossibile aprire il file\n");
            }


    /*Alcuni esempi
                   int numero = 42;
        float decimale = 3.14;
        char carattere = 'A';
        char stringa[] = "Ciao";
        int array[] = {1, 2, 3};

        // Scritture valide:
        fprintf(f, "%d", numero);          // int
        fprintf(f, "%.2f", decimale);      // float
        fprintf(f, "%c", carattere);       // char  
        fprintf(f, "%s", stringa);         // stringa
        fprintf(f, "%d %d", array[0], array[1]); // elementi array
        */
    
        fcheck = fputs(s, f);                                   //scrive nel file f la stringa s senza aggiungere automaticamnete la newline \n   
                                                                //in caso di errore restituisce EOF (End Of File), tipicamente -1
                                                                //in caso di successo restituisce un numero non negativo

                                                                //lo usiamo per scrivere in un file una stringa gia formattata
                                                                //prende la stringa e la scrive senza controlli



            if(fcheck==EOF){
                fprintf(stderr, "Errore di scrittura!\n");
                } else {
            printf("Stringa scritta con successo\n");
            } 
    
   

        //char * fgets(char *s, int n, FILE *f);

    //Chiudere il file 

    is_closed = fclose(f);                  //se ha successo restituisce un int=0, altrimenti restituisce una costante simbolica EOF definita in stdio.h
    if(is_closed == EOF){
        fprintf(stderr, "Erore chiusura file\n");
        return 1;
    }
    return 0;
}