

#include <iostream>
using namespace std;

#include <fstream>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"


tipo* creaNodi(int& n) {
    
    //CLASSICA APERTURA DI UN FILE
    ifstream fin("nodi.txt");

    if (!fin) {
        cerr << "Errore apertura nodi.txt" << endl;
        exit(1);
    }


    //ANDIAMO A PRENDERE IL PIRMO NUMERO DEL FILE DI TESTO
    fin >> n;
    fin.ignore(); // salta newline


    tipo* nodi = new tipo[n];

    for (int i = 0; i < n; i++) {                                       //VADO A METTERE OGNI INFORMAZIONE DEL NODO IN UNO SCOMPARTIMENTO APPOSITO FUORI DAL GRAFO
        char buffer[21];
        fin >> buffer;                                               //legge un charattere


        strcpy(nodi[i].descrizione, buffer);                        //COPIA QUESTO SUL TIPO DESCRTIZIONE

        char t;
        fin >> t;
        fin.ignore();
        nodi[i].tipo = t;
    }

    fin.close();
    return nodi;
}

void stampa(graph g, tipo* nodi, int dim) {
    for (int u = 1; u <= dim; u++) {                                    //PARTO DA 1 COSI POSSO FARE DA SUBITO -1 E QUINDI PRENDERE IL PRIMO NODO DEL GRAFO FIN DA SUBITO

        if (nodi[u - 1].tipo == 'U') {                                  //QUI LO VALUTO USANDO L'ALTRO ARRAY STRUTTURA TIPO

            adj_list l = get_adjlist(g, u);                             //METTO SU L LA LISTA DEL SUO NODO IN GRAFO 

            while (l != NULL) {                                         //FINO A CHE NON è NULLA, CLASSICO
                int v = get_adjnode(l);
                float w = get_adjweight(l);

                if (nodi[v - 1].tipo == 'P') {                          //PRENDO IL NODO E LO TRASFORMO NELL'INDICE E VALUTO SE è IL PRODOTTO , SE NON LO è è UN PROBLEMA
                    cout << nodi[u - 1].descrizione
                         << " valuta " << w
                         << " " << nodi[v - 1].descrizione
                         << endl;
                }
                l = get_nextadj(l);                                    // PRENDO IL PROSSIMO NODO SULLA LISTA
            }
        }
    }
}

float media_prod(char* prod, graph g, tipo* nodi, int dim) {           //prende accoutn in input , IL GRAFO , IL TIPO DEL PRODOTTO , E LA DIMENSIONE
    int idProd = -1;

    for (int i = 0; i < dim; i++) {
        if (nodi[i].tipo == 'P' && strcmp(nodi[i].descrizione, prod) == 0) {
            idProd = i + 1; // 1-based per il grafo
            break;
        }
    }
    if (idProd == -1) {
        cerr << "Prodotto non trovato" << endl;
        return -1;
    }

    float somma = 0;
    int count = 0;

    // scorri tutti gli utenti
    for (int u = 1; u <= dim; u++) {
        if (nodi[u - 1].tipo == 'U') {
            adj_list l = get_adjlist(g, u);
            while (l != NULL) {
                if (get_adjnode(l) == idProd) {
                    somma += get_adjweight(l);
                    count++;
                }
                l = get_nextadj(l);
            }
        }
    }

    if (count == 0) return 0;
    return somma / count;
}





/*
    Input: un utente (account) e un prodotto (prod), il grafo in quesitone e le informazioni del tipo, piu la dimensione 

    Trova l’ID dell’utente e l’ID del prodotto.

    Cerca altri utenti che hanno valutato quel prodotto con almeno 3 stelle.

    Per ciascuno di questi utenti, guarda cos’altro hanno valutato con almeno 3 stelle.

    Stampa quei prodotti come “suggerimenti” per l’utente di input.
*/

void suggerisci(char* account, char* prod, graph g, tipo* nodi, int dim) {
    int idUser = -1, idProd = -1;

    // Trovo l'id dell'utente
    for (int i = 0; i < dim; i++) {
        if (nodi[i].tipo == 'U' && strcmp(nodi[i].descrizione, account) == 0) {
            idUser = i + 1; // 1-based
            break;
        }
    }

    // Trovo l'id del prodotto
    for (int i = 0; i < dim; i++) {
        if (nodi[i].tipo == 'P' && strcmp(nodi[i].descrizione, prod) == 0) {
            idProd = i + 1; // 1-based
            break;
        }
    }

    if (idUser == -1 || idProd == -1) {
        cerr << "Account o prodotto non trovato." << endl;
        return;
    }

    cout << "Suggerimenti per " << account << " se ti piace " << prod << ":" << endl;

    // Scorri tutti gli utenti diversi da quello di input
    for (int u = 1; u <= dim; u++) {
        if (u == idUser || nodi[u - 1].tipo != 'U') continue;

        // Controllo se l'utente u ha valutato il prodotto dato con almeno 3
        adj_list l = get_adjlist(g, u);
        bool haValutatoProd = false;
        while (l != NULL) {
            if (get_adjnode(l) == idProd && get_adjweight(l) >= 3) {
                haValutatoProd = true;
                break;
            }
            l = get_nextadj(l);
        }

        if (haValutatoProd) {
            // Ora stampo gli altri prodotti che u ha valutato con >=3
            l = get_adjlist(g, u);
            while (l != NULL) {
                int v = get_adjnode(l);
                float w = get_adjweight(l);

                if (v != idProd && nodi[v - 1].tipo == 'P' && w >= 3) {
                    cout << "Suggerimento: " << nodi[v - 1].descrizione << endl;
                }

                l = get_nextadj(l);
            }
        }
    }
}


int main(){

    int n;
    tipo* nodi = creaNodi(n);                                               //CREANODI FA SI CHE QUESTA N VENGA MODIFICATA, RENDENDO N = AL PRIMO NUMERO DEL FILE , RESTITUISCE L'ARRAY DI INFORMAZIONI PRESE

    graph g = new_graph(n);

    ifstream fin("valutazioni.txt");                                        //QUI FIN INVECE PRENDE LE VALUTAZIONI Paolo Ciabatta 5

    if (!fin) {
        cerr << "Errore apertura valutazioni.txt" << endl;
        exit(1);
    }

    int u, v;
    float stelle;                                                          

    while (fin >> u >> v >> stelle) {                                       //FINO A CHE RIESCE A PRENDERE IN FILA I 3 DATI AGGIUNGE ARCO 
        add_arc(g, u, v, stelle);                                           //METTE L'ARCO TRA U E V CON PESO STELLE, CHE IN QUESTO CASO SONO LE RECENSIONI
    }

    fin.close();

    cout << "Stampa valutazioni:" << endl;
    stampa(g, nodi, n);                                                     //STAMPA LA LISTA

    cout << endl << "Calcolo media di un prodotto." << endl;
    cout << "Inserisci nome prodotto: ";

    char nome[256];
    cin.getline(nome, 256);                                                //chiede all'utente il nome di un prodotto 

    if (strlen(nome) == 0) cin.getline(nome, 256); // fix se rimane vuoto   //LEGGE MEGLIO QUELLO CHE SCRIVE L'UTENTE

    float m = media_prod(nome, g, nodi, n);                                 //RESTITUISCE LA VALUTAZIONE MEDIA DELL'UTENTE CON NOME IN INPUT 
    if (m >= 0)
        cout << "Media valutazioni di " << nome << " = " << m << endl;


    cout << endl << "Inserisci account per suggerimenti: ";
char accountSug[256];
cin.getline(accountSug, 256);

cout << "Inserisci prodotto già valutato: ";
char prodSug[256];
cin.getline(prodSug, 256);

suggerisci(accountSug, prodSug, g, nodi, n);


    delete[] nodi;                                                          //LIBERO LA MEMORIA MOLTO IMPORTANTE
    return 0;


}