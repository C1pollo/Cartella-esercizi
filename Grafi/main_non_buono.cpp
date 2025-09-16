
#include <iostream>
using namespace std;
#include <stdio.h>
#include <string.h>

#include "graph.h"


graph* leggi_grafo(char* filename, int orientato, int pesato)
{
    int is_closed;
    int vertici;
    char s[10];
    FILE* f= fopen(filename, "r");
    if (f==NULL){
        fprintf(stderr, "ERRORE CON APERTURA FILE");
        return NULL;                                //POSSIAMO USARLO PERCHE DI NORMA RESTITUIAMO UN PUNTATORE
    }
    
    
    //fread(&vertici, sizeof(int),1, f);                    fread è per file BINARI

    fgets(s,sizeof(s) ,f);
    printf("numero di vertici del grafo=%s", s);



    graph g = new_graph(vertici);


    int u,v;
    while(fscanf(f, "%d %d" , &u, &v) == 2)
    {
        printf(" arco da %d -> %d\n", u, v);


        add_arc(g,u, v, 0);
        
        if (orientato == 1){
            add_arc(g,v, u, 0);
        }

    }






    is_closed= fclose(f);
    if (is_closed == EOF){
        fprintf(stderr, "ERRORE CON CHIUSURA FILE");
        return NULL;
    }

    graph* l= &g;
    return l;
}



int main (){

    char s[]="graph1";
    graph* g = leggi_grafo(s, 0, 0);

    printf("\n%d\n", g->dim);
    stampa_grafo(g);


    
    return 0;
}