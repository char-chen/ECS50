section .text
global mystrstr

mystrstr:
  push ebp
  mov ebp, esp
  mov edi, [ebp+8]  ;edi is string
  mov esi, [ebp+12] ;esi is substring
  mov ecx, 0
  

  mov al, [esi]
  cmp al, 0
  je  done

  
loop:
   
  mov ah, [edi]
  cmp ah, 0
  je  done2

  mov al, [esi]
  cmp al, ah
  jne increment

  mov ecx, 1
; substring: al, string: ah
loop2:
  mov al, [esi + ecx]
  cmp al, 0
  je  done
  
  mov ah, [edi+ecx]
  cmp ah, al
  jne increment

  inc ecx
  jmp loop2

increment:
  inc edi
  jmp loop

done2:
  mov eax, 0
  leave
  ret

done: 
  mov eax, edi
  leave
  ret
