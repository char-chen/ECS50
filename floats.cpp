#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

void printHex(const char *integer, const char *fraction);
void normalize(const char *temp, char *number, char sign, const char *bit_size);
void toBinary(char *number, const char *integer, const char *fraction);
void round(char *number);
void toHexRep(const char *number, char *ieee754);
void divide (char *number);
void multiply(char *number);
char toHex(int number);

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

void printHex(const char *integer, const char *fraction)
{
  char num[2000] = {0}, sign = integer[0], number32[33], ieee32[9] = {0}, ieee64[17] = {0}, number64[65];
  toBinary(num, integer, fraction);
  normalize(num, number32, sign, "32");
  toHexRep(number32, ieee32);
  cout << "IEEE 32:    " << ieee32 << endl;
  normalize(num, number64, sign, "64");
  toHexRep(number64, ieee64); 
  cout << "IEEE 64:    " << ieee64 << endl;
} //printHex

void normalize(const char *temp, char *num, char sign, const char *size)
{
  char exponent[12] = {0}, mantissa[53] = {0}, result[65] = {0}, roundingBit;
  int pos = 0, shift = -1, exp_size, man_size;
  
  if (strcmp(size, "32") == 0)
  {
    exp_size = 8;
    man_size = 23;
  }
  else //64-bit
  {
    exp_size = 11;
    man_size = 52;
  }
  
  int exp_field = pow(2, exp_size - 1);
  
  if (sign == '-')
    result[0] = '1';
  else
    result[0] = '0';
  
  //Get the number of digits needed to shift.
  if (temp[0] == '1')
    for (int i = 0; temp[i] != '.' && shift < exp_field; i++)
      shift++;
  else //Number < 1.
    for (int i = 2; temp[i] != '1' && shift > -(exp_field - 1); i++)
      shift--;
  
  //Get exponent bits.
  for (int i = 0, val = shift + exp_field - 1; i < exp_size; val /= 2)
    exponent[i++] = val % 2 + '0';
 
  for (int i = strlen(exponent) - 1, j = 1; i >= 0; i--, j++)
    result[j] = exponent[i];
  
  //Get mantissa bits.
  for (int i = 1, start = 0; temp[i] != '\0' && pos < man_size; i++)
  {
    if (shift == exp_field || shift == -(exp_field - 1))
      break;  //If number is too small/large to represent.
    
    if (shift >= 0 && temp[i] != '.')
      mantissa[pos++] = temp[i];
    
    if (shift < 0 && start && temp[i] != '\0')
      mantissa[pos++] = temp[i];
    
    if (temp[i] == '1') 
      start = 1;  //For shift < 0. Start copying after first '1' bit.
    
    roundingBit = temp[i + 1];   
  } 
  
  //Pad the rest of the bits with 0.
  while (pos++ < man_size)
    strcat(mantissa, "0");
  
  strcat(result, mantissa);
  
  //Round up if bit to right of LSB is set.
  if (pos >= (man_size) && roundingBit == '1')
    round(result);
  
  strcpy(num, result);
} //normalize

void toBinary(char *num, const char *in, const char *frac)
{
  char integer[1000] = {0}, fraction[1000] = {0}, value[1000] = {0};
  strcpy(value, in);
  
  //Remove negative sign.
  if (value[0] == '-')
    for (char *p = value; *p != '\0'; p++)
      *p = *(p+1);
  
  //Convert integer to binary.
  for (int i = 0; value[0] != '\0'; divide(value), i++)
    integer[i] = ((value[strlen(value) - 1] - '0') % 2) + '0';
  
  for (int i = strlen(integer) - 1, j = 0; i >= 0; i--, j++)
    num[j] = integer[i];
 
  //Add decimal point.
  num[strlen(num)] = '.';
  
  strcpy(value, frac);
  
  //Convert decimal to binary.
  for (int i = 0, j, prev = strlen(value), done = 0; !done && i < 500; i++)
  {
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
} //toBinary

void round(char *number)
{
  //Promulgate bit addition through the whole mantissa and exponent fields.
  for (int i = strlen(number) - 1, done = 0; i >= 1 && !done; i--)
  {
    if (number[i] == '0')
    {
      number[i] = '1';
      done = 1;
    }
    else 
      number[i] = '0';
  }   
} //round

void toHexRep(const char *number, char *ieee754)
{
  //Convert bits to base 16 representation.
  for (int i = 0, j = 0, sum = 0; number[i] != '\0'; i += 4, sum = 0)
  {
    for (int k = 0, l = 3; k < 4; k++, l--)
      sum += (int)(number[i + k] - '0') * pow(2, l);

    ieee754[j++] = toHex(sum);
  }
} //toHexRep

void divide(char *val) 
{
  char temp[256] = {0};
  
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
  }
  
  strcpy(val, temp);
} //divide

void multiply(char *val)
{
  char temp[1000] = {0};
  
  for (int i = strlen(val) - 1, carry = 0, product = 0; i >= 0 || carry == 1; i--)
  {
    if (i >= 0)
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
