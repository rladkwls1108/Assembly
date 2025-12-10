# Algorithm Workbench

## 1. Stack Frame 그리기

**문제:** Here is a calling sequence for a procedure named AddThree that adds three doublewords (assume that the STDCALL calling convention is used):
```asm
push 10h
push 20h
push 30h
call AddThree
```
Draw a picture of the procedure's stack frame immediately after EBP has been pushed on the runtime stack.

**답:**
```
+----------------+
|      10h       |  [EBP + 16]  (첫 번째 매개변수)
+----------------+
|      20h       |  [EBP + 12]  (두 번째 매개변수)
+----------------+
|      30h       |  [EBP + 8]   (세 번째 매개변수)
+----------------+
|  Return Addr   |  [EBP + 4]   (반환 주소)
+----------------+
|    Old EBP     |  [EBP]       (이전 EBP 값)
+----------------+  <-- EBP, ESP
```

---

## 2. AddThree 프로시저 작성

**문제:** Create a procedure named AddThree that receives three integer parameters and calculates and returns their sum in the EAX register.

**답:**
```asm
AddThree PROC,
    val1:DWORD,
    val2:DWORD,
    val3:DWORD
    
    mov eax, val1
    add eax, val2
    add eax, val3
    ret
AddThree ENDP
```

---

## 3. pArray 지역 변수 선언

**문제:** Declare a local variable named pArray that is a pointer to an array of doublewords.

**답:**
```asm
LOCAL pArray:PTR DWORD
```

---

## 4. buffer 지역 변수 선언

**문제:** Declare a local variable named buffer that is an array of 20 bytes.

**답:**
```asm
LOCAL buffer[20]:BYTE
```

---

## 5. pwArray 지역 변수 선언

**문제:** Declare a local variable named pwArray that points to a 16-bit unsigned integer.

**답:**
```asm
LOCAL pwArray:PTR WORD
```

---

## 6. myByte 지역 변수 선언

**문제:** Declare a local variable named myByte that holds an 8-bit signed integer.

**답:**
```asm
LOCAL myByte:SBYTE
```

---

## 7. myArray 지역 변수 선언

**문제:** Declare a local variable named myArray that is an array of 20 doublewords.

**답:**
```asm
LOCAL myArray[20]:DWORD
```

---

## 8. SetColor 프로시저 작성

**문제:** Create a procedure named SetColor that receives two stack parameters: forecolor and backcolor, and calls the SetTextColor procedure from the Irvine32 library.

**답:**
```asm
SetColor PROC,
    forecolor:DWORD,
    backcolor:DWORD
    
    mov eax, backcolor
    shl eax, 4              ; 배경색을 상위 4비트로 이동
    or eax, forecolor       ; 전경색과 결합
    call SetTextColor
    ret
SetColor ENDP
```

---

## 9. WriteColorChar 프로시저 작성

**문제:** Create a procedure named WriteColorChar that receives three stack parameters: char, forecolor, and backcolor. It displays a single character, using the color attributes specified in forecolor and backcolor.

**답:**
```asm
WriteColorChar PROC,
    char:BYTE,
    forecolor:DWORD,
    backcolor:DWORD
    
    ; 색상 설정
    mov eax, backcolor
    shl eax, 4
    or eax, forecolor
    call SetTextColor
    
    ; 문자 출력
    movzx eax, char
    call WriteChar
    ret
WriteColorChar ENDP
```

---

## 10. DumpMemory 프로시저 작성

**문제:** Write a procedure named DumpMemory that encapsulates the DumpMem procedure in the Irvine32 library. Use declared parameters and the USES directive. The following is an example of how it should be called: `INVOKE DumpMemory, OFFSET array, LENGTHOF array, TYPE array`.

**답:**
```asm
DumpMemory PROC USES esi ecx ebx,
    pArray:PTR BYTE,
    arrayLength:DWORD,
    arrayType:DWORD
    
    mov esi, pArray         ; ESI = 배열 시작 주소
    mov ecx, arrayLength    ; ECX = 배열 요소 개수
    mov ebx, arrayType      ; EBX = 요소 크기
    call DumpMem
    ret
DumpMemory ENDP
```

---

## 11. MultArray 프로시저 및 PROTO 선언

**문제:** Declare a procedure named MultArray that receives two pointers to arrays of doublewords, and a third parameter indicating the number of array elements. Also, create a PROTO declaration for this procedure.

**답:**
```asm
; PROTO 선언
MultArray PROTO,
    pArray1:PTR DWORD,
    pArray2:PTR DWORD,
    arrayCount:DWORD

; 프로시저 정의
MultArray PROC,
    pArray1:PTR DWORD,
    pArray2:PTR DWORD,
    arrayCount:DWORD
    
    ; 프로시저 구현 코드
    ret
MultArray ENDP
```
