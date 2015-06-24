#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

void printHex(char *i, char *f);
void normalize(char *n);
void convert(char *n, char *i, char *f);
int ctoi(char *a);
int numOfDigits(int n);

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
  char number[33];
  convert(number, in, frac);
  normalize(number);
  cout << number << endl;
  //cout << "IEEE 32: " << endl;   
} //printHex

void normalize(char *n)
{
    
} //normalize

void convert(char *num, char *in, char *frac)
{
  char integer[9], fraction[24];
  fraction[0] = integer[0] = '0';
  
  for (int val = ctoi(in), i = 0; val != 0; val /= 2, i++)
    integer[i] = val % 2 + 48;
  
  for (int i = strlen(integer) - 1, j = 0; i >= 0; i--, j++)
    num[j] = integer[i];

  num[strlen(num)] = '.';
   
  for (int val = ctoi(frac), i = 0; val != 0; i++)
  {
    int digit = numOfDigits(val);
    val *= 2;
    fraction[i] = val / pow(10, digit) + 48;
    
    if (fraction[i] == '1')
      val = val % (int) pow(10, digit); 
  } 
 
  for (unsigned int i = 0, j = strlen(num); i < strlen(fraction); i++, j++)
    num[j] = fraction[i];
} //convert

int numOfDigits(int num)
{
  int i = 0;
  
  for (i = 0; num != 0; i++)
    num /= 10;
  
  return i;
} //numOfDigits

int ctoi(char *str)
{
  if (str[0] == '-')
    for (char *ps = str; *ps != '\0'; ps++)
      *ps = *(ps+1);

  str[strlen(str)] = '\0';
  int i, num=0;
  
  for(i = 0; str[i] >= '0' && str[i] <= '9'; i++)
    num = (str[i] - '0') + 10 * num;
  
  return num;
} //ctoi
