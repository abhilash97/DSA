#include<stdio.h>
#include<stdlib.h>
#include "interface.h"
#include<string.h>

int k; char** book;
Hashtable create(){
	Hashtable h1 = (Hashtable)malloc(sizeof(struct hashtable)*best_tab);
	h1->elementCount = 0;
	h1->loadFactor = 0;
	h1->insertionCost = 0;
	h1->queryingCost = 0;
	for(int m=0;m<best_tab;m++){
		h1[m].link = (Node)malloc(sizeof(struct node));	
		h1[m].link->head = (Node)malloc(sizeof(struct node));
		h1[m].link->head->index =0;
	}
	return h1;
}

void Insert(Hashtable h, char** str, int index){

	char* st = str[index];
	int k = hashfunction(st, best_base, best_tab);
	printf("hashed value is: %d\n", k);
	if(h[k].link->head==NULL){
		Node head = (Node)malloc(sizeof(struct node));
		head->index = index;
		head->next = NULL;
		h[k].link->head = head;			
	}
	else{	
	Node temp = h[k].link->head;
	while(1){
		if(temp->next==NULL){
		Node new = (Node)malloc(sizeof(struct node));
		new->index = index;
		new->next = NULL;
		temp->next = new;
		h->insertionCost++;
		break;
		}		
		temp = temp->next;
		h->insertionCost++;
	}
	}
}
int InsertAll(Hashtable h, char** str){
	for(int l=0;l<k;l++){
		printf("The string at index %d is %s\n", l,str[l]);
		Insert(h,str,l);	
	}
	return h->insertionCost;
}
int Lookup(Hashtable h, char* str){
	int ind; 
	int hash = hashfunction(str,best_base,best_tab);
	printf("Hashvalue of lookup string is %d\n",hash);
	for(int x=0;x<k;x++){	
		if(strcmp(book[x],str) == 0){
			ind = x;
			printf("Found at index %d taking the last one\n", ind);	
		}
	}
	if(h[hash].link->head==NULL){
	printf("NULL hai\n");
	return 0;	
	}
	else{
	Node temp = h[hash].link->head;
	while(temp!=NULL){
		if(temp->index == ind){
		h->queryingCost++;
		printf("Found!!!");
		return h->queryingCost;
		}
		else{ h->queryingCost++;
			temp=temp->next;}	
	}	
	}
	return 0;
}
int main(){
	book = inputParser();
	profiler();//updates the best tables size and base value
	Hashtable new = create();
	printf("Done creation\n");
	int total_cost = InsertAll(new,book);
	printf("Total insertion cost is %d\n", total_cost);
	int query = Lookup(new,"email");
	printf("querying cost is %d\n", query);
	return 0;
}

