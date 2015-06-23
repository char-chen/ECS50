#include <iostream>
#include <cstring>
using namespace std;

void printHex(char *i, char *f);

int main()
{
  char input[256];
  cout << "Number: ";
  cin >> input;
  char *tok = strtok(input , ".");
  char integer[strlen(tok) + 1];
  strcpy(integer, tok);
  tok = strtok(NULL, "");
  char fraction[strlen(tok) + 1];
  strcpy(fraction, tok);
  printHex(integer, fraction);  
} //main

void printHex(char *in, char *frac)
{
  
}
