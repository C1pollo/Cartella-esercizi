#include <iostream>

using namespace std;


#include "coda.h"

//#define DEBUG
//extern int dfs_mod(tree);
int main(){
	tree t=NULL;
	char b[5] = "Luca" ;
	t=new_node(b);
	char a [6] = "Paolo";
	node* n=new_node(a);
	insert_child(t,n);

	char c[6] = "Marco";
	n=new_node(c);
	insert_sibling(t->firstChild,n);

	char d[6] = "Lucia";
	n=new_node(d);
	insert_child(t->firstChild->nextSibling,n);

	char e[5] = "Anna";
	node* m=new_node(e);
	insert_sibling(n->parent,m);

	int p = altezza (t);
	cout << p << endl; 
	
    serializzazione(t);				//stampa i nodi dell'alabero tra parentesi 
	bfs(t);

}