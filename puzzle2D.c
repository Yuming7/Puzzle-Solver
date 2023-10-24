#include "puzzle2D.h"
#include <string.h>
#include <stdio.h>

int search(char *pat, char *txt){
    int SIZE = 256;
    int PRIME = 7079;
    int lenp = strlen(pat);
    int lent = strlen(txt);
    int i, j;
    int hpat = 0; // primwe hash value
    int htxt = 0; // txt hash value txt
    int hash = 1;

    for (i = 0; i < lenp - 1; i++)
        hash = (hash * SIZE) % PRIME;
    for (i = 0; i < lenp; i++) {
        hpat = (SIZE * hpat + pat[i]) % PRIME;
        htxt = (SIZE * htxt + txt[i]) % PRIME;
    }
    for (i = 0; i <= lent - lenp; i++) {
        if (hpat == htxt) {
            for (j = 0; j < lenp; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }
            if (j == lenp)
                return i+1; // pattern was found return the value of where it was + 1
        }
        if (i < lent - lenp) {
            htxt = (SIZE * (htxt - txt[i] * hash) + txt[i + lenp]) % PRIME;
            if (htxt < 0)
                htxt = (htxt + PRIME);
        }
    }
    return 0; 
}


int orientation_check(char *pat, char *txt, int n){
    int size = n-1;
    // orientation 1 horizontal right (→)
    for(int i = 0; i <= size; i++){
        char temp[size + 1];
        for(int j = 0; j <= size; j++){
            temp[j] = pat[i*size + j]; 
        }
        if(search(txt, temp)){
            return 1;
        }
    }
    // orientation 2 horizontal left (←)
    for(int i = size; i >= 0; i--){
        char temp[size + 1];
        for(int j = size; j >= 0; j--){
            temp[j] = pat[i*size + j]; 
        }
        if(search(txt, temp)){
            return 2;
        }
    }
    //orientation 3 vertical down (↓)
    for(int i = 0; i <= size; i++){
        char temp[size + 1];
        for(int j = 0; j <= size; j++){
            temp[j] = pat[j*size + i];
        }
        if(search(txt, temp)){
            return 3;
        }
    }
    //orientation 4 vertical up (↑)
    for(int i = 0; i <= size; i++){
        char temp[size + 1];
        for(int j = size; j >= 0; j--){
            temp[j] = pat[j*size + i];
        }
        if(search(txt, temp)){
            return 4;
        }
    }
    //orientation 5 top left to bottom right diagonal (↘)
    char temp[size + 1];
    for(int i = 0; i <= size; i++){
        temp[i] = pat[i*size + i];
    }
    if(search(temp, txt)){
            return 5;
    }
    //orientation 6 bottom right backwards to top left diagonal (↖)
    for(int i = size; i >= 0; i--){
        temp[i] = pat[i*size + i];
    }
    if(search(txt, temp)){
            return 6;
    }
    //orientation 7 bottom left to top right (↗)
    for(int i = 0; i <= size; i++){
        temp[i] = pat[i*size + (size-i)];
    }
    if(search(txt, temp)){
            return 7;
    }
    //orientation 8 top right backwards to bottom left (↙)
    for(int i = size; i >= 0; i--){
        temp[i] = pat[i*size + (size-i)];
    }
    if(search(txt, temp)){
            return 8;
    }
    return 0;
}

int coordinate_check(char *pat, char *txt, int n){
    int size = n-1;
    // orientation 1 horizontal right (→)
    for(int i = 0; i <= size; i++){
        char temp[size + 1];
        for(int j = 0; j <= size; j++){
            temp[j] = pat[i*size + j]; 
        }
        if(search(txt, temp)){
            return i*size + search(txt, temp)-1;
        }
    }
    // orientation 2 horizontal left (←)
    for(int i = 0; i <= size; i++){
        char temp[size + 1];
        for(int j = size; j >= 0; j--){
            temp[j] = pat[i*size + j]; 
        }
        if(search(txt, temp)){
            return (i)*size - search(txt, temp)+1;
        }
    }
    //orientation 3 vertical down (↓)
    for(int i = 0; i <= size; i++){
        char temp[size + 1];
        for(int j = 0; j <= size; j++){
            temp[j] = pat[j*size + i]; 
        }
        if(search(txt, temp)){
            return (search(txt, temp)-1)*size + i;
        }
    }
    //orientation 4 vertical up (↑)
    for(int i = 0; i <= size; i++){
        char temp[size + 1];
        for(int j = size; j >= 0; j--){
            temp[j] = pat[j*size + i]; 
        }
        if(search(txt, temp)){
            return (size - (search(txt, temp)-1))*size + i;
        }
    }
    //orientation 5 top left to bottom right diagonal (↘)
    char temp[size + 1];
    for(int i = 0; i <= size; i++){
        temp[i] = pat[i*size + i];
    }
    if(search(txt, temp)){
            return (search(txt, temp)-1)*size + (search(txt, temp)-1);
    }
    //orientation 6 bottom right backwards to top left diagonal (↖)
    for(int i = size; i >= 0; i--){
        temp[i] = pat[i*size + i];
    }
    if(search(txt, temp)){
            return (size - (search(txt, temp)-1))*size + (size - (search(txt, temp)-1));
    }
    //orientation 7 bottom left to top right (↗)
    for(int i = 0; i <= size; i++){
        temp[i] = pat[i*size + (size-i)];
    }
    if(search(txt, temp)){
            return (size - (search(txt, temp)-1))*size + (search(txt, temp)-1);
    }
    //orientation 8 top right backwards to bottom left (↙)
    for(int i = size; i >= 0; i--){
        temp[i] = pat[i*size + (size-i)];
    }
    if(search(txt, temp)){
            return (search(txt, temp)-1)*size + (size - (search(txt, temp)-1));
    }
    return 0;
}