

//Per spostarsi all'interno di un file


//int fseek(FILE* file, long offset, int origin);

/*
    sposta la testina di offset byte a partire dalla posizione origin, che puo valere 0 1 o 2
    se ha successo fornisce 0 , altrimenti un numero diverso da esso

    origin:
        0 inizio file SEEK_SET
        1 posizione attuale nel file SEEK_CUR
        2 fine file SEEK_END


        PRIMITVE PER SPOSTAMENTO

        SPOSTARSI ALL'INIOZIO DEL FILE 
        void rewind(FILE* file);

        SAPERE LA POSIZIONE DELLA TESTINA IN UN FILE
        long ftell(FILE* file);

        Cosa restituisce?
        Restituisce la posizione del byte su cui è posizionata la testina al momento della chiamata, restituisce –1 in caso di errore.

        RESTITUISCE IL BYTE SU CUI E POSIZIONATA, UTILE PER VEDERE LA DIMENSIONE DEL FILE 
*/