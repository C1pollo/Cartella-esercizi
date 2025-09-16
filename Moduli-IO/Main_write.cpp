

#include <stdio.h>
#include <string.h>

int main() {
    int is_closed;
    //char s[]="Buongiorno mondo";
    int vet[10] = {1,2,3,4,5,6,7,8,9,10};

    FILE* f=NULL;
    f = fopen("file scrittura", "wb");          //wb = write binary

    if (f==NULL){
        fprintf(stderr, "impossibile aprire il file\n");            //di norma non me lo stampa, e nel caso lo stampasse andiamo a vederelo in stderr
        return 1;
    }


    //scrivere su un file   
    // size_t fwrite(void* ptr, size_t size, size_t nmemb, FILE* file);

    fwrite(vet, sizeof(int), 10, f);                //scrive i valori interi in formato binario (NON COME TESTO)

    //MOLTO VELOCE E PRECISO    
    //SCRIVE DATI BIANRI GREZZI 

    //puntatore all'array da scrivere
    //sizeof(int): la dimensione dei singoli elementi in byte
    //10 = numero di elementi
    //la funzione scrive sizeof(int) * 10 byte a partire dall'indirizzo vet sullo stream file
    //restituisce il numero di elementi (NON di byte) effettivamente scritti, che possono essere meno di 10



    //PER LEGGERE SSU UN FILE BIANROI, fopen con rb

    //size_t fread(void* ptr, size_t size, size_t nmemb, FILE* file);

    //STESSA COSA PER FWRITE SOLO CHE LEGGE DALLO STREAM FILE E LI SCRIVE IN MEMORIA A PARETIRE DAL PUNTATORE DELL'INDIRIZZO ptr
    //RICHIEDE PRECISIONE ASSOULTA, SE SI VUOLE INDIETRO UNA STRUTTURA DATI QUESTA DEVE ESSERE AL 100 PRECISA, SE NO RESTITUISCE 0

    is_closed= fclose(f);
    if(is_closed == EOF){
        fprintf(stderr, "Erore chiusura file\n");
        return 1;
    }

        return 0;
}