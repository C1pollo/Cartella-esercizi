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
#include <fstream>                                      //per avere ifstream
#include <stdlib.h>                                     //exit(0)

using namespace std;

#include "coda_bfs.h"
#include "graph.h"






void add(graph& g, int u, int v, float w, bool d) {           //il bool starebbere per l'oreintazione del grafo , se diretto o non diretto
                                                              // si lavora direttamente sull'indirizzo di graph, andandolo a modificare
	if (d)
		add_arc(g,u,v,w);
	else
		add_edge(g,u,v,w);
}

graph g_build(ifstream& g, bool d, bool w) {
  int n;
  g >> n;                                                     //con ifstream, legge il primo numero 
                                                              // >> si chiamano operatori di estrazione 
                                                              //salta gli spazi bianchi, legge il valore fino al prossimo spazio bianco, converte il valore nel tipo della variabile destinazione , si sposta alla posizione successiva


                                                              //per ifstream un dato non è MISURATO IN BYTE, MA IN TOKEN (PEZZI SEPARATI DA SPAZI BIANCHI)
                                                              //UTILIZZA L'INSTINTO, CIOè VEDE LA VIARIBLE DI DESTINAZIONE E PENSA POI AL DATO DA LEGGERE
                                                              //dopo averlo letto si ferma dopo il dato appena letto
  graph G = new_graph(n);

  int v1,v2;

  if (w) {
    float w;
    while (g >> v1 >> v2 >> w) {                                  //legge ma mano i valori e li mette nelle variabili , intanto controlla se ci siano tutte
                                                                  //se non ci sono il while finisce
      add(G,v1,v2,w,d);
     }
  } else {
    while (g >> v1 >> v2) {                                       //finche riesco a leggere due valori consecutivi non esco dal ciclo
      add(G,v1,v2,1.0,d);
    }
  }
  return G;
}

/*
**************************
****FUNZIONE CONNECTED****
**************************
*/

bool connected(graph G, int v){
	bool* raggiunto = new bool[get_dim(G)];
  int* padre = new int[get_dim(G)];


	for(int i=0; i<get_dim(G); i++){
		raggiunto[i]= false;
    padre[i]=-1;
  }

  raggiunto[v-1]=true;
	codaBFS C=newQueue();
	C=enqueue(C,v);



	while(!isEmpty(C)){
		int w=dequeue(C);

		for(adj_list n=get_adjlist(G,w);    n!=NULL;     n=get_nextadj(n)){        //PRENDIAMO IN PRATICA LA LISTA DEL NODO DOPO IL DEQUEUE E ANALIZZIAMO I NODI DELLA LISTA
			
      int i = get_adjnode(n);

			if(raggiunto[i-1] == false)
      {
        padre[i-1]=w-1;
				raggiunto[i-1]=true;
				C=enqueue(C,i);}
		}
	}

  //QUESTO è IL PEZZO PER VEDERE SE TUTTI I NODI SONO RAGGIUNTI DOPO AVER FATTO LA BFS, QUINDI VEDIAMO SE ABBIAMO RAGGIUNTO TUTTI I NODI 

/*
	for(int i=0;i<get_dim(G);i++)
		if(!raggiunto[i])
			return false;
	return true;
  */
  
  for(int i=0;i<get_dim(G);i++)
		if(!raggiunto[i])
			return false;
	cout<<"Spanning tree del nodo "<<v<<endl;
	for(int i=0;i<get_dim(G);i++)
		if (padre[i]!=-1)
			cout<<"il padre del nodo "<<i+1<<" e' il nodo "<<padre[i]+1<<endl;
	return true;

}



int main(int argc,char *argv[]) {       //tratto la funzione main come funzione che riceve in ingresso argomenti

  //In questa funzione gli devo passare argoemnti quando richiamo il .exe, che argomenti gli devo passare?
  // devo passargli stringhe di dati per char* argv[], le stringhe potrebbero essere "file.txt", "0", "1"

   /* Se il numero di parametri con cui e' stato chiamato il client e' inferiore a tre - si ricordi che il primo parametro c'e' sempre, ed e' il
     nome del file eseguibile - si ricorda all'utente che deve inserire anche il nome del file che descrive il grafo e il flag  weighted*/
  int nodo;

  if (argc<3) {                                           //vuole per forza almeno 3 argomenti
    cout << "Usage: " << argv[0] << " filename directed weighted\n";
    exit(0);
  };
                                                                          //argv[0] = nomde del programma
                                                                          //argv[1] = nome del file da aprire
                                                                          //argv[2] = 0 o 1, se 0 è indiretto se è 1 è diretto
                                                                          //argv[3] = 0 o 1, se 1 vuol dire che il grafo è pesato
   ifstream g;

  g.open(argv[1]);                                                        //essendo ifstream il file viene aperto in modalità lettura
                                                                          //fosse stato ofstream avrebbe aperto il file in scrittura
                                                                          //fosse stato fstream lo avrebbe aperto in entrambe le modalità
      cout <<   argv[1] << " " << argv[2] << " " << argv[3]<<endl;
  int directed = atoi(argv[2]);
  int weighted = atoi(argv[3]);

  /*Chiamata a g_build che costruisce un grafo*/

 graph G=g_build(g, directed, weighted);

cout<<get_dim(G)<<endl;

  //Stampa dell'array di liste
  adj_list tmp;
    for (int i=1; i<=get_dim(G); i++) {
       tmp=get_adjlist(G,i);
       cout << i;
       while (tmp) {
	  cout << " --> " << get_adjnode(tmp);
	  tmp=get_nextadj(tmp);
       }
       cout << endl;
  }

  cout<<"Da quale nodo vuoi partire?"<<endl;
    cin>>nodo;
   if(connected(G,nodo))
	   cout<<"Grafo connesso!!"<<endl;
   else
	   cout<<"Grafo non connesso!!"<<endl;
  
}
