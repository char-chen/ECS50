#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

void printHex(char *i, char *f);
void normalize(char *n, char s);
void convert(char *n, const char *i, const char *f);
char toHex(int n);
int ctoi(const char *a);
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
  char ieee32[9], ieee64[17], number32[33], number64[65], sign = in[0];
  convert(number32, in, frac);
  normalize(number32, sign);
  convert(number64, in, frac);
  normalize(number64, sign);
  
  for (unsigned int i = 0, j = 0, sum = 0; i < strlen(number32); i += 4, sum = 0)
  {
    for (int k = 0, l = 3; k < 4; k++, l--)
      sum += (int)(number32[i + k] - 48) * (int)pow(2, l);
    
    ieee32[j++] = toHex(sum);   
  }
       
  cout << "IEEE 32: " << ieee32 << endl;   
} //printHex

void normalize(char *n, char sign)
{
  int pos = 0, shift = -1;
  char exponent[9], mantissa[24], result[33];
  
  if (n[0] == '1')
    for (char *p = n; *p != '.'; p++)
      shift++;
  else
    ;
  
  if (shift >= 0)
  {
    for (int i = 1; n[i] != '\0'; i++)
      if (n[i] != '.')
        mantissa[pos++] = n[i];
    
    while (pos++ < 23)
      strcat(mantissa, "0");   
  }
  
  for (int val = shift + 127, i = 0; val != 0; val /= 2, i++)
    exponent[i] = val % 2 + 48;

  if (sign == '-')
    result[0] = '1';
  else
    result[0] = '0';
 
  for (int i = strlen(exponent) - 1, j = 1; i >= 0; i--, j++)
    result[j] = exponent[i];
  
  strcat(result, mantissa);
  strcpy(n, result);
} //normalize

void convert(char *num, const char *in, const char *frac)
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

int ctoi(const char *s)
{
  char str[strlen(s) + 1];
  strcpy(str, s);
  
  if (str[0] == '-')
    for (char *ps = str; *ps != '\0'; ps++)
      *ps = *(ps+1);

  str[strlen(str)] = '\0';
  int i, num=0;
  
  for(i = 0; str[i] >= '0' && str[i] <= '9'; i++)
    num = (str[i] - '0') + 10 * num;
  
  return num;
} //ctoi

char toHex(int n)
{
  if (n == 10)
    return 'A';
  else if (n == 11)
    return 'B';
  else if (n == 12)
    return 'C';
  else if (n == 13)
    return 'D';
  else if (n == 14)
    return 'E';
  else if (n == 15)
    return 'F';
  else
    return n + 48; 
} //toHex
