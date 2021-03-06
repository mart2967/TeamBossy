#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_disemvowel.h"

#define BUF_SIZE 1024

int is_vowel(char c) {
  /* Returns true if c is a vowel (upper or lower case), and false otherwise. */
  char vowels[11] = "aeiouAEIOU";
  if (strchr(vowels, c) != NULL) {
    return 1;
  }
  return 0;
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
  /*
   * Copy all the non-vowels from in_buf to out_buf. num_chars indicates how many
   * characters are in in_buf, and this should return the number of non-vowels that
   * that were copied over.
   */
  int i, a;
  int totalNonVowels = 0;
  int charTypes[num_chars]; // vowels 1, all else 0
  for (i = 0; i < num_chars; ++i) {
    int result = is_vowel(in_buf[i]);
    if (result == 0) {
      ++totalNonVowels;
    }
    charTypes[i] = result;
  }
  
  for (i = 0, a = 0; i < num_chars-1; ++i) {
    if (charTypes[i] == 0 && in_buf[i] > 0) {
      out_buf[a] = in_buf[i];
      //printf("setting out_buf[%d] to '%c' \n", a, in_buf[i]);
      ++a;
    }
  }
  //fwrite(out_buf, 1, a, stdout);
  return totalNonVowels;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
  /* 
   * Copy all the non-vowels from inputFile to outputFile.
   * Create input and output buffers, and use fread() to repeatedly read
   * in a buffer of data, copy the non-vowels to the output buffer, and
   * use fwrite to write that out.
   */
  char bufferIn[BUF_SIZE];
  char bufferOut[BUF_SIZE];
  fread(bufferIn, BUF_SIZE, 1, inputFile);
  int newLength = copy_non_vowels(strlen(bufferIn), bufferIn, bufferOut);
  fwrite(bufferOut, 1, newLength, outputFile);
}

int main(int argc, char *argv[]) {
  FILE *inputFile;
  FILE *outputFile;
  if(argc == 1) {
    disemvowel(stdin, stdout);
  } else if (argc == 2){
    inputFile = fopen( argv[1], "r");
    disemvowel(inputFile, stdout);
  }
  else if (argc == 3) {
    inputFile = fopen( argv[1], "r");
    outputFile = fopen( argv[2], "w");
    disemvowel(inputFile, outputFile);
  }

  return 0;
}
