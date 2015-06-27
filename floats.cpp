#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

void printHex(const char *i, const char *f);
void normalize(char *t, char *n, char s);
void convert(char *n, const char *i, const char *f);
void divide (char *a);
void multiply(char *a);
char toHex(int n);

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

void printHex(const char *in, const char *frac)
{
  char num[1000] = {0}, sign = in[0], number32[33], ieee32[9];//, ieee64[17], number64[65];
  convert(num, in, frac);
  normalize(num, number32, sign);
  //convert(number64, in, frac);
  //normalize(number64, sign);

  //Convert bits to hex representation 
  for (unsigned int i = 0, j = 0, sum = 0; i < strlen(number32); i += 4, sum = 0)
  {
    for (int k = 0, l = 3; k < 4; k++, l--)
      sum += (int)(number32[i + k] - 48) * (int)pow(2, l);
    
    ieee32[j++] = toHex(sum);   
  }
 
  cout << "IEEE 32: " << ieee32 << endl;
} //printHex

void normalize(char *temp, char *num, char sign)
{
  unsigned int pos = 0;
  int shift = -1;
  char exponent[9] = {0}, mantissa[24] = {0}, result[33] = {0};
  
  if (sign == '-')
    result[0] = '1';
  else
    result[0] = '0';
  
  cout << temp << endl; 
  //Get the number of digits needed to shift 
  if (strcmp(temp, "0.0") == 0)
    shift = 0;
  else if (temp[0] == '1')
    for (char *p = temp; *p != '.'; p++)
      shift++;
  else
    for (int i = 2; temp[i] != '1'; i++)
      shift--;
 
  //cout << shift << endl; 
  //Get exponent bits
  for (int i = 0, val = shift + 127; val != 0; val /= 2)
  {
    if (shift == 0)
    {
      strcpy(exponent, "00000000");
      break;
    }

    exponent[i++] = (char) (val % 2 + '0');
  }
 
  if (shift < 0)
    result[1] = '0';
   
  for (char *p = &exponent[strlen(exponent) - 1]; pos < strlen(exponent); pos++)
    strncat(result, p--, 1);
  
  cout << result << endl;
  pos = 0;
  
  //Get mantissa bits
  for (int i = 1; temp[i] != '\0' && pos < 23; i++)
  {
    if (shift >= 0 && temp[i] != '.')
    {
      mantissa[pos++] = temp[i];
    }
    else if (shift < 0 && temp[i] == '1')
    {
      char *p = &temp[i];
      strcat(mantissa, ++p);
      pos = strlen(mantissa);
      break;
    }
  }
  
  //Pad the rest of the bits with 0s 
  while (pos++ < 23)
    strcat(mantissa, "0");
  
  strcat(result, mantissa);
  strcpy(num, result);
  //cout << n << endl;*/
} //normalize

void convert(char *num, const char *in, const char *frac)
{
  char integer[129] = {0}, fraction[256] = {0}, value[256];
  int pos;
  strcpy(value, in);
  
  //Remove negative sign
  if (value[0] == '-')
    for (char *p = value; *p != '\0'; p++)
      *p = *(p+1);
  
  //Convert integer to binary
  for (pos = 0; value[0] != '\0' && pos < 128; divide(value), pos++)
    integer[pos] = ((value[strlen(value) - 1] - '0') % 2) + '0';
  
  for (int i = strlen(integer) - 1, j = 0; i >= 0; i--, j++)
    num[j] = integer[i];
  
  num[strlen(num)] = '.';
  strcpy(value, frac);
  
  //Convert decimal to binary
  for (int i = 0, j, prev = strlen(value), done = 0; !done && i < 255; i++)
  {
    fraction[0] = '0';
    
    if (value[0] == '0' && value[1] == '\0')
      break;
    
    done = 1;
    multiply(value);
    fraction[i] = strlen(value) - prev + '0'; 

    if (fraction[i] == '1')
    {
      for (j = 1; value[j] != '\0'; j++)
      {
        if (value[j] != '0')
          done = 0;
        
        value[j - 1] = value[j];
      }
      
      value[j - 1] = '\0';
    }
    else
      done = 0;
    
    prev = strlen(value);
  }
  
  strcat(num, fraction);
} //convert

void divide(char *val) 
{
  char temp[256];
  
  for (int i = 0, j = 0, borrow = 0; val[i] != '\0'; i++)
  {
    int digit = val[i] - '0';
    
    if (digit >= 2 || borrow != 0)
    {
      temp[j++] = ((borrow * 10 + digit) / 2) + '0';
      borrow = digit % 2;
    }
    else
    {
      borrow = digit;

      if (i != 0)
        temp[j++] = '0';
    }

    temp[j] = '\0';
  }
  
  strcpy(val, temp);
} //divide

void multiply(char *val)
{
  char temp[256];
  temp[0] = '\0';
  
  for (int i = strlen(val) - 1, carry = 0, product = 0; i >= 0 || carry == 1; i--)
  {
    if (i > -1)
      product = carry + (val[i] - '0') * 2;
    else
      product = carry; 
    
    //Shift all digits to one right
    for (int j = strlen(val) - i - 1; j >= 0; j--)
      temp[j + 1] = temp[j];
    
    temp[0] = product % 10 + '0';
    carry = product / 10;
  }

  strcpy(val, temp);
} //multiply

char toHex(int n)
{
  if (n >= 10)
    return n - 10 + 'A';
  else
    return n + '0';
} //toHex
