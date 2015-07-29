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


char* mystrstr(char *string, char *substring)
{
  asm(".intel_syntax noprefix\n");
  asm(
  "mov edi, [ebp+8] \n" 
  "mov esi, [ebp+12] \n"
  "mov ecx, 0\n"
  

  "mov al, [esi]\n"
  "cmp al, 0\n"
  "je  done\n"

  
"loop:\n"
   
  "mov ah, [edi]\n"
  "cmp ah, 0\n"
  "je  done2\n"

  "mov al, [esi]\n"
  "cmp al, ah\n"
  "jne increment\n"

  "mov ecx, 1\n"

"loop2:\n"
  "mov al, [esi + ecx]\n"
  "cmp al, 0\n"
  "je  done\n"
  
  "mov ah, [edi+ecx]\n"
  "cmp ah, al\n"
  "jne increment\n"

  "inc ecx\n"
  "jmp loop2\n"

"increment:\n"
  "inc edi\n"
  "jmp loop\n"

"done2:\n"
  "mov eax, 0\n"
  "leave\n"
  "ret\n"

"done: \n"
  "mov eax, edi\n"
  "leave\n"
  "ret\n"
  ); 
}
