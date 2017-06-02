GLOBAL getMin
GLOBAL getHour
GLOBAL getDay
GLOBAL getMonth
GLOBAL getYear
GLOBAL binaryTime
%include "./asm/macros.m"

section .text

binaryTime:
			pushStack
            mov rax,0
            mov al,0Bh
            out 70h,al
            in al,71h
            or al,4
            out 71h,al
            leave
            ret


getMin:
            pushStack
            mov al,2
            out 70h,al
           	leave
            ret

getHour:
            pushStack
            mov al,4
            out 70h,al
            in al,71h
           	leave
            ret

getDay:
            pushStack
            mov al,7
            out 70h,al
            in al,71h
           	leave
            ret

getMonth:
            pushStack
            mov al,8
            out 70h,al
            in al,71h
           	leave
            ret

getYear:
            pushStack
            mov al,9
            out 70h,al
            in al,71h
           	leave
            ret