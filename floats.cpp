#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

void printHex(char *i, char *f);
void normalize(char *n, char s);
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

void printHex(char *in, char *frac)
{
  char sign = in[0], number32[33], ieee32[9];//, ieee64[17], number64[65];
  convert(number32, in, frac);
  normalize(number32, sign);
  //convert(number64, in, frac);
  //normalize(number64, sign);
  //cout << number32 << endl;

  //Convert bits to hex representation 
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
  unsigned int pos = 0;
  int shift = -1;
  char exponent[9], mantissa[24], result[33];
  
  //Get the number of digits needed to shift 
  if (n[0] == '1')
  {
    for (char *p = n; *p != '.'; p++)
      shift++;
  }
  else
  {
    for (char *p = &n[strlen(n) - 1]; *p != '.'; p--)
      shift--;

    shift++;
  }
  
  //Get mantissa bits
  for (int i = 1; n[i] != '\0'; i++)
  {
    if (shift >= 0 && n[i] != '.')
    {
      mantissa[pos++] = n[i];
      mantissa[pos] = '\0';
    }
    else if (shift < 0 && n[i] == '1')
    {
      char *p = &n[i];
      mantissa[0] = '\0';
      strcat(mantissa, ++p);
      pos = strlen(mantissa);
      break;
    }
  }
  
  //Pad the rest of the bits with 0s 
  while (pos++ < 23)
    strcat(mantissa, "0");
 
  //Get exponent bits
  for (int i = 0, val = shift + 127; val != 0; val /= 2)
  {
    exponent[i++] = (char) (val % 2 + '0');
    exponent[i] = '\0'; //Needed due to mysterious extra bits appear
  }
  
  if (sign == '-')
    result[0] = '1';
  else
    result[0] = '0';
  
  pos = 0;
  
  if (shift < 0)
  {
    result[1] = '0';
    result[2] = '\0';
  }
  else
    result[1] = '\0';
  
  for (char *p = &exponent[strlen(exponent) - 1]; pos < strlen(exponent); pos++)
    strncat(result, p--, 1);
  
  strcat(result, mantissa);
  strcpy(n, result);
  //cout << n << endl;
} //normalize

void convert(char *num, const char *in, const char *frac)
{
  char integer[9], fraction[24], value[256];
  fraction[0] = integer[0] = '0'; 
  strcpy(value, in);
  
  //Remove negative sign
  if (value[0] == '-')
    for (char *p = value; *p != '\0'; p++)
      *p = *(p+1);
  
  value[strlen(value)] = '\0';  //Make sure that the null terminator is there.
  
  //Convert integer to binary
  for (int i = 0; value[0] != '\0'; divide(value), i++)
    integer[i] = ((value[strlen(value) - 1] - '0') % 2) + '0';
  
  for (int i = strlen(integer) - 1, j = 0; i >= 0; i--, j++)
    num[j] = integer[i];
  
  num[strlen(num)] = '.';
  strcpy(value, frac);
   
  //Convert decimal to binary
  for (int i = 0, j, prev = strlen(value), done = 0; !done; i++)
  {
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

    if (i == 23)
      break;
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
