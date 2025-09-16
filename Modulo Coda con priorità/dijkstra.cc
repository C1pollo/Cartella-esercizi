/********************************************************
 *                                                      *                                  
 * Programma che fornisce la rappresentazione di un grafo    
 * mediante liste di adiacenza.                           
 * Il programma riceve in ingresso due parametri: il nome del 
 * file che contiene la definizione del grafo mediante 
 * lista di archi e un flag che indica se gli archi sono pesati 
 * (flag weighted - 0 se non pesati - 1 se pesati).
 * Il file di input � strutturato come segue:
 * Num di nodi
 * Primo arco
 * Secondo arco
 * ...
 *                                                             
 * La funzione graph, che si occupa della costruzione del grafo,
 * restituisce un intero, che indica il numero n     
 * di nodi nel grafo. Per il programma chiamante, un nodo �    
 * quindi semplicemente costituito da un numero fra 1 ed n. 
 *                                                      *                                     
 *******************************************************/

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

#include "graph.h"
#include "codap.h"
#include <float.h>													//FLT_MAX = ci serve per inizializzare la distanza al massimo 


//************************************************ */
//AGGIUNGE UN ARCO SE IL GRAFO è DIRETTO, SE è INDIRETTO NE AGGIUNGE DUE CON add_edge 

void add(graph &g, int u, int v, float w, bool d) {
	if (d)
		add_arc(g, u, v, w);
	else
		add_edge(g, u, v, w);
}

//************************************************ */


/************************************************ */
// COSTRUISCO IL GRAFO PARTENDO DA UN FILE DI TESTO , USO LA LIBRERIA <fstream> PER AVERE ifstream e prendere i dati con facilità

graph g_build(ifstream &g, bool d, bool w) {
	int n;
	g >> n;
	graph G = new_graph(n);
	int v1, v2;
	if (w) {
		float w;
		while (g >> v1 >> v2 >> w) {
			add(G, v1, v2, w, d);
		}
	} else {
		while (g >> v1 >> v2) {
			add(G, v1, v2, 1.0, d);
		}
	}
	return G;
}
//************************************************ */


//************************************************ */
//USO QUESTA FUNZIONE PER PRENDERE IN INPUT IL GRAFO, IL VERTICE SORGENTE E I DUE ARRAY DIST E PARENT 
void inizialize(graph G, int s, float* dest, int* parent) {
	for (int i = 0; i < G.dim; i++) {
		dest[i] = FLT_MAX;
		parent[i] = NULL;
	}
	dest[s - 1] = 0;
}
//************************************************ */


//************************************************ */
//QUESTA è LA PARTE DENTRO AL WHILE DA RIPETERE PER OGNI NODO PER AGGIORNARGLI LA DISTANZA, DOPO ANDRà AGGIORNATA ANCHE LA CODA CON PRIORITà
void relax(int u, int v, int w,float* dest, int* parent) {
	if (dest[v] > dest[u] + w) {
		dest[v] = dest[u] + w;
		parent[v] = u + 1;
	}
}
//************************************************ */




int main(int argc, char *argv[]) {
	/* Se il numero di parametri con cui e' stato chiamato il client e'
	 inferiore a tre - si ricordi che il primo parametro c'e' sempre, ed e' il
	 nome del file eseguibile - si ricorda all'utente che deve inserire
	 anche il nome del file che descrive il grafo e il flag  weighted*/

	if (argc < 3) {
		cout << "Usage: " << argv[0] << " filename directed weighted\n";
		exit(0);
	};


	//QUESTA PARTE SERVE PER APRIRE IL FILE IN MODALITà LETTURA E PER PRENDERE I VALORI INSERITI DA TASTIERA, CIOè IL NOME FILE ARGV[1], SE è DIRETTO O NO ARGV[2], SE è PESATO CON ARGV[3]

	ifstream g;
	g.open(argv[1]);
	cout << argv[1] << " " << argv[2] << " " << argv[3] << endl;
	int directed = atoi(argv[2]);							//CONVERTE UNA STRINGA IN UN NUMERO INTERO 
	int weighted = atoi(argv[3]);


	/*Chiamata a g_build che costruisce un grafo*/

	graph G = g_build(g, directed, weighted);				//CREO IL GRAFO DAL .TXT


	//SI DILETTA A STAMPARE LA DIMENSIONE DI G (NUEMRO DI VERTICI), POI VA A STAMARE LE LE LISTE DI LISTE CON I CONTENUTI 
	cout << get_dim(G) << endl;

	//Stampa dell'array di liste
	adj_list tmp;
	for (int i = 1; i <= get_dim(G); i++) {
		tmp = get_adjlist(G, i);
		cout << i;
		while (tmp) {
			cout << " --> " << get_adjnode(tmp);
			tmp = get_nextadj(tmp);
		}
		cout << endl;
	}


	/**************************************************/
	// QUI VIENE FATTO IL PROGRAMMA DIJKSTRA
	float* dest = new float[G.dim];
	int* parent = new int[G.dim];

	int s;
	cout << "Da quale nodo vuoi far partire la ricerca? ";
	cin >> s;

	inizialize(G, s, dest, parent);

	codap queue = NULL;

	for (int i = 0; i < G.dim; i++) {												//QUI IMMETTE NLLA CODA I VERTICI DA I=0 A G.DIM CON LA PROPRIA DESTINAZIONE
		queue = enqueue(queue, i, dest[i]);
	}

	while (!isEmpty(queue)) {														
		int u;

		u = dequeue(queue); // Occorre fare conversione tra indici [0,V-1] e [1,V]

		adj_list vicini = get_adjlist(G, u + 1);									//VICINI SARà LA LISTA DEL NODO, U VERRà GIA RESTITUITO COME UN INDICE , OCCORRE QUINDI AUMENTARLO DI 1 PERCHE ACNHE ADJ_LIST PRENDE IN INPUT IL NODO E NON L'INDICE

		while (vicini != NULL) {													//SCORRIAMO ADESSO LA LISTA DEL VERTICE U FINO A CHE è FINITA 

			int v = get_adjnode(vicini);
			float w_u_v = get_adjweight(vicini);									//DA QUA PRENDIAMO IL NODO E IL PESO CORRISPONDENTE PER ARRIVARE DA LUI

			relax(u, v - 1, w_u_v,dest, parent);

			queue = Decrease_Priority(queue, v - 1, dest[v - 1]);					//UGUALE A DIJKSTRA

			vicini = get_nextadj(vicini);											//L=L->NEXT , IN PRATICA SCORRE LA LISTA ESSENDO WHILE 
		}
	}

	cout << "Nodo\t Peso \t Padre" << endl;
	for (int i = 0; i < G.dim; i++) {
		cout << i + 1 << " \t " << dest[i] << " \t " << parent[i] << endl;
	}
}
