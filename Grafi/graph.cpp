

#include <iostream>
using namespace std;

#include "graph.h"



graph new_graph(int n){
	graph G;
	G.dim=n;
	G.nodes= new adj_list[n];                  //alloca mamoria per un array di n puntatori con struttura quella di adj_list
	  for (int i=0; i<n; i++) {
	    G.nodes[i] = NULL;  //indicazione di lista vuota
	  }
	return G;
}

void add_arc(graph& G, int u, int v, float w) {			//prenderà l'ndirizzo di memoria delk grafo, vertice u, s e il peso w, 
  adj_node* t = new adj_node;
  t->node = v-1;                        				//faccio -1 per andare in contro alla lista creata da 0 , essendo un array 
  t->weight = w;
  t->next = G.nodes[u-1];								//farlo andare in testa o in coda non conta, quindi lo facciamo andare in testa
  G.nodes[u-1] = t;										// metto che il nodo punta al prossimo prendendolo dalla lista di liste g.nodes al valore u-1 e il puntatore alla stessa verrà cambiata per lui così fa farlo andare al primo posto 
}


/* Funzione che aggiunge l'arco non orientato (u,v) alle liste
 * di adiacenza di u e v. L'arco ha peso w. */
void add_edge(graph& g, int u, int v, float w) {		//questo lo si usa per l'arco orientato
  add_arc(g,u,v,w);
  add_arc(g,v,u,w);
}


int get_dim(graph g){									//la dimensione del grafo è nota nella struttura di base
	return g.dim;
}

adj_list get_adjlist(graph g,int u){					//per restituire la testa della lista usata per un determinato nodo sfruttiamo la proprietà dell'array di liste con velocità O(1) per restituire il valore 
	return g.nodes[u-1];
}

int get_adjnode(adj_node* l){							//Restituisce il nodod vero e proprio contenuto nel nodo
	return (l->node+1);
}

adj_list get_nextadj(adj_list l){						
	return l->next;
}

float get_adjweight(adj_node* l){
	return (l->weight);
}

void stampa_grafo(graph* g){

	printf("=== LISTA di ADIACENZA ===\n");
    
    for (int i = 0; i < g->dim; i++) {
        printf("\n%d -> ", i + 1);  // Vertice corrente
    
		adj_list L=g->nodes[i];
        while (L != NULL)
		{
			printf ("%d-", L->node + 1);
			L=L->next;
		}

		

        
    }
}