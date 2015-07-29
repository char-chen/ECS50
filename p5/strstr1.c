#include <stdio.h>

char* mystrstr(char *string, char *pattern);

int main()
{
  char *ptr, s[] = "People respond to people who respond.", sub1[] = "Pe",
    sub2[] = " peo", sub3[] = "respond to People", sub4[] = "";
  
  ptr = mystrstr(s, sub1);
  puts(ptr);
  ptr = mystrstr(s, sub2);
  puts(ptr);
  ptr = mystrstr(s, sub3);
  
  if(!ptr)
    puts("OK");
  else
    puts("Not OK");
  
  ptr = mystrstr(s, sub4);
  puts(ptr);
    
  return 0;
} // main


char* strstr(char *string, char *substring)
{
  int i;
 
  if (*substring == 0) 
    return string;
  
  for(; *string != 0; string++) 
  {
    if (*string != *substring) 
      continue;
	
    i = 1;

    while (1) 
    {
      if (substring[i] == 0) 
        return string;
	
      if (string[i] != substring[i])
        break;
     
      i++;
    }  // while
  }  // for

  return (char*) 0;
}

