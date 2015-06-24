#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

void printHex(char *i, char *f);
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
  short sign = 0; 
  char integer[9], fraction[24];
  fraction[0] = integer[0] = '0';
  
  if (in[0] == '-')
    sign = 1;
   
  for (int val = ctoi(in), i = 0; val != 0; val /= 2, i++)
    integer[i] = val % 2 + 48;
  
  for (int val = ctoi(frac), i = 0; val != 0; i++)
  {
    int digit = numOfDigits(val);
    val *= 2;
    fraction[i] = val / pow(10, digit) + 48;
    
    if (fraction[i] == '1')
      val = val % (int) pow(10, digit); 
  } 
  
  cout << fraction << endl;
  //cout << "IEEE 32: " << endl;   
} //printHex

int numOfDigits(int num)
{
  int i = 0;
  
  for (i = 0; num != 0; i++)
    num /= 10;
  
  return i;
}

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
