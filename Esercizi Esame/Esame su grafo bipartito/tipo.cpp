#include "tipo.h"
#include <iostream>
#include <cstring>

using namespace std;

/*******************************/
/* IMPLEMENTAZIONE MODULO "tipo" */
/*******************************/

int compare(tipo t1, tipo t2) {
    // Confronta prima per tipo (carattere)
    if (t1.tipo < t2.tipo) {
        return -1;
    } else if (t1.tipo > t2.tipo) {
        return 1;
    } else {
        // Se il tipo è uguale, confronta per descrizione
        return strcmp(t1.descrizione, t2.descrizione);
    }
}

void copy(tipo& dest, tipo src) {
    // Copia la descrizione
    strcpy(dest.descrizione, src.descrizione);
    // Copia il tipo
    dest.tipo = src.tipo;
}

void print(tipo t) {
    cout << "Descrizione: " << t.descrizione << ", Tipo: " << t.tipo << endl;
}
