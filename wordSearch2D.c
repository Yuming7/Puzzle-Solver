#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "puzzle2D.h"


int main(int argc, char *argv[]) {
    int wrdlen; 
    FILE *pzlfile;
    FILE *wrdfile;
    FILE *solfile;
    int error;
    int mode;
    if(argc == 7 || argv[1][0] != '-' || argv[3][0] != '-' || argv[5][0] != '-' ){
        mode = 1;
    }
    else if(argc == 9 || argv[1][0] != '-' || argv[3][0] != '-' || argv[5][0] != '-' || argv[7][0] != '-'){
        mode = 2;
    }
    else{
        fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file>[-o <solution_file>]\n");
        exit(6);
    }
    
    for(int i=1; i < argc ; i+=2){
        int size = strlen(argv[i+1]) - 1;
        error = 1;
        if(argv[i][1] == 'p'){
            error = 0;
            if(argv[i+1][size] == 't' && argv[i+1][size-1] == 'x' && argv[i+1][size-2] == 't' && argv[i+1][size-3] == '.'){
                 pzlfile = fopen(argv[i+1], "r");
                 if(pzlfile == NULL){
                     fprintf(stderr, "Error: Puzzle file <name-of-input-file> does not exist\n");
                     exit(5);
                 }
            }
            else{
                 fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file>[-o <solution_file>]\n");
                 exit(7);
            }
        }
        if(argv[i][1] == 'w'){
            error = 0;
            if(argv[i+1][size] == 't' && argv[i+1][size-1] == 'x' && argv[i+1][size-2] == 't' && argv[i+1][size-3] == '.'){
                wrdfile = fopen(argv[i+1], "r");
                if(wrdfile == NULL){
                    fprintf(stderr, "Error: Wordlist file <name-of-input-file> does not exist\n");
                    exit(3);
                }
            }
            else{
                fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file>[-o <solution_file>]\n");
                exit(7);
            }
        }
        if(argv[i][1] == 'l'){
            error = 0;
            wrdlen = atoi(argv[i+1]); 
            if(wrdlen < 1 || wrdlen > 100){
                fprintf(stderr, "Encountered error");
                exit(7);
            }
        }
        if(mode == 2){
            if(argv[i][1] == 'o'){
            error = 0;
            if(argv[i+1][size] == 't' && argv[i+1][size-1] == 'x' && argv[i+1][size-2] == 't' && argv[i+1][size-3] == '.'){
                solfile = fopen(argv[i+1], "w");
            }
            else{
                fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file>[-o <solution_file>]\n");
                exit(7);
            }
        }
        }
    }
    if(error == 1){
    	fprintf(stderr, "Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>\n");
        exit(7);
    }
    char words[101][wrdlen+2];
    char word[wrdlen+2];
    int num_words = 0;
    while (fgets(word, wrdlen+2, wrdfile) != NULL && num_words < 100) {
        word[strcspn(word, "\n")] = 0;
        strcpy(words[num_words], word);
        num_words++;
    }
    
    char lines[1000];
    int size = 0; 
    int index = 0;
    char ch;
    while (ch!= EOF){
        ch = fgetc(pzlfile);
        if(ch != '\n' && ch != '\0'){
            lines[index] = ch;
            index += 1;
        }
        else{
            size ++;
        }
    }
    printf("%s", lines);
    if(mode == 1){
        FILE *output_fp = fopen("output.txt", "w");
        for (int i = 0; i < num_words; i++) {
            int orientation = orientation_check(lines, words[i], size);
            int coord = coordinate_check(lines, words[i], size);
            int row = coord / size;
            int column = coord % size;
            fprintf(output_fp, "%s;(%d,%d);%d\n", words[i], row, column, orientation);
        }
    fclose(output_fp);
    }
    if(mode == 2){
        for (int i = 0; i < num_words; i++) {
            int orientation = orientation_check(lines, words[i], size);
            int coord = coordinate_check(lines, words[i], size);
            int row = coord / size;
            int column = coord % size;
            fprintf(solfile, "%s;(%d,%d);%d\n", words[i], row, column, orientation);
        }
        fclose(solfile);
    }
    fclose(pzlfile);
    fclose(wrdfile);
}