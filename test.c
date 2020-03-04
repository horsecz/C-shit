/*
 * double-linked list => priority queue
 * by horse
 * fixed by the_leteron
 */

#include <stdio.h>
#include <stdlib.h>

struct Prvek_Seznamu {
    int data;
    struct Prvek_Seznamu* dalsi;
    struct Prvek_Seznamu* predchozi;
};

struct Prvek_Seznamu* koren;

// vytvori novy prvek (nezarazen do seznamu!)
struct Prvek_Seznamu* vytvorPrvek (int data) {
    struct Prvek_Seznamu* novy_prvek = (struct Prvek_Seznamu*) malloc(sizeof(struct Prvek_Seznamu));
    novy_prvek->data = data;
    novy_prvek->dalsi = NULL;
    novy_prvek->predchozi = NULL;
    
    return novy_prvek;
}

// vlozi novy prvek do seznamu (na konec)
void vlozPrvekMezi(int data) {
    struct Prvek_Seznamu* temp = koren;
    struct Prvek_Seznamu* novy_prvek = vytvorPrvek(data);
    
    if (koren == NULL) {
        koren = novy_prvek;
        return;
    }

    // find value where data is lower than new data
    while ((temp->dalsi != NULL && (temp->data < data))) {
        temp = temp->dalsi;
    }

    // insert node
    if (temp->data >= data) {

        if (temp->predchozi == NULL) {
            temp->predchozi = novy_prvek;
            novy_prvek->dalsi = temp;
            koren = novy_prvek;
        } else {
        novy_prvek->predchozi = temp->predchozi;
        temp->predchozi = novy_prvek;
        novy_prvek->dalsi = temp;
        novy_prvek->predchozi->dalsi = novy_prvek;
        return;
        }
    }

    // end of list, insert after last node, equal data
    else if (temp->dalsi == NULL) {

        temp->dalsi = novy_prvek;
        novy_prvek->predchozi = temp;
        return;

    }
}   


int hodnotaDatPrvku(int poradi_v_seznamu, int od_korene) {
    struct Prvek_Seznamu* temp = koren;
    
    if (od_korene) { // prochazim od korene
        for(int i = 0; i != poradi_v_seznamu; i++) {
            if (temp == NULL || temp->dalsi == NULL)
                return -1;
            temp = temp->dalsi;
        }
    }
    else { // prochazim od konce
        while (temp->dalsi != NULL) {
            temp = temp->dalsi;
        }
        
        for(int i = 0; i != poradi_v_seznamu; i++) {
            if (temp->predchozi == NULL)
                return -1;
            temp = temp->predchozi;
        }
    }
    return temp->data;
}

// znici/vymaze cely seznam
void destroySeznam() {
    struct Prvek_Seznamu* temp = koren;
    struct Prvek_Seznamu* to_be_deleted;
    
    printf("\nDestroying:\nNULL ");
    while (temp != NULL) {
        printf("x> %d <", temp->data);
        to_be_deleted = temp;
        temp = temp->dalsi;
        free(to_be_deleted);
    }
    printf("x NULL\nCompleted\n");
}

void destroyElement(int data) {
    struct Prvek_Seznamu* temp = koren;
    struct Prvek_Seznamu* to_be_deleted;
    
    //printf("\nnicim\n");
    while (temp->dalsi != NULL && temp != NULL && temp->data != data) {
      //  printf("jdu na dalsi :\n");
        temp = temp->dalsi;
    }
    
    if (temp == NULL) {
        printf("takova picovina tu neni\n");
        return;
    
    }
    
    to_be_deleted = temp;
    if (temp->data != data) {
        printf("sorryjako\n");
        return;
    }
    
    if (temp->dalsi == NULL && temp->predchozi == NULL) {
        koren = NULL;
        free(to_be_deleted);
        return;
    }
    
    if (temp->dalsi == NULL) {
        temp->predchozi->dalsi = NULL;
        free(to_be_deleted);
        return;
    }
    
    if (temp->predchozi == NULL) {
        temp->dalsi->predchozi = NULL;
        koren = temp->dalsi;
        free (to_be_deleted);
        return;
    }
    
        
    //printf("jde se na to smug\n");
    temp->predchozi->dalsi = temp->dalsi;
    temp->dalsi->predchozi = temp->predchozi;
    free(to_be_deleted);
}

int main() {
    int data;
    
    koren = NULL;
    
    // vlozi koren s hodnotou 0 a 5 prvku do seznamu
    for(int i = 1; i <= 5; i++) {
        if (i != 3 || i != 0)
            vlozPrvekMezi(i);
    }
    
    // vytiskne seznam
    struct Prvek_Seznamu* temp = koren;
    printf("SEZNAM\nNULL ");
    while(temp != NULL) {
        printf("-> %d <", temp->data);
        temp = temp->dalsi;
    }
    printf(" NULL");
    
    destroyElement(5);
    destroyElement(3);
    destroyElement(2);
    destroyElement(1);
    destroyElement(10);
    
        // vytiskne seznam
    temp = koren;
    printf("\nSEZNAM\nNULL ");
    while(temp != NULL) {
        printf("-> %d <", temp->data);
        temp = temp->dalsi;
    }
    printf(" NULL");
    
    destroyElement(4);
    
    /*
    vlozPrvekMezi(3);
    vlozPrvekMezi(6);
    vlozPrvekMezi(10);
    vlozPrvekMezi(7);
    vlozPrvekMezi(9);
    vlozPrvekMezi(8);
    vlozPrvekMezi(6);
    vlozPrvekMezi(6);
    vlozPrvekMezi(2);
    vlozPrvekMezi(2);
    vlozPrvekMezi(2);
    vlozPrvekMezi(2);
    vlozPrvekMezi(2);
    vlozPrvekMezi(10);
    vlozPrvekMezi(0);
    vlozPrvekMezi(0);*/
        
    return 0;
}
