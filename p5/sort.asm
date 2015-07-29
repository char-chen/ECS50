section .text
global _sort

_sort:  push eax               
        push ebx              
        push edx               
        push edi            
        push esi           
        mov eax, [ebp + 8] 
        mov esi, 1                
sort1:  cmp esi, [ebp + 12]  
        jz sort9                
        mov edx, [eax + esi * 4]
        mov edi, esi          
        sub edi, 1           
sort2:  cmp edi, 0          
        jl sort3           
        mov ebx, [eax + edi * 4] 
        cmp ebx, edx            
        jle sort3 
        add edi, 1
        mov [eax + edi * 4], ebx  
        sub edi, 2               
        jmp sort2               
sort3:  add edi, 1             
        mov [eax + edi * 4], edx 
        add esi, 1              
        jmp sort1               
sort9:
        pop esi
        pop edi
        pop edx
        pop ebx
        pop eax
        pop ebp
        ret


