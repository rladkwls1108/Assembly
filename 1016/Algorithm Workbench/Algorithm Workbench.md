# 4.9.2 Algorithm Workbench

## 1. Write a sequence of MOV instructions that will exchange the upper and lower words in a doubleword variable named three.

**답:**
```asm
mov ax, WORD PTR three        ; 하위 워드를 AX에 저장
mov bx, WORD PTR three+2      ; 상위 워드를 BX에 저장
mov WORD PTR three, bx        ; BX를 하위 워드에 저장
mov WORD PTR three+2, ax      ; AX를 상위 워드에 저장
```

---

## 2. Using the XCHG instruction no more than three times, reorder the values in four 8-bit registers from the order A,B,C,D to B,C,D,A.

**답:**
```asm
; 초기: A,B,C,D
xchg al, bl    ; B,A,C,D
xchg al, cl    ; B,C,A,D
xchg al, dl    ; B,C,D,A
```

---

## 3. Transmitted messages often include a parity bit whose value is combined with a data byte to produce an even number of 1 bits. Suppose a message byte in the AL register contains 01110101. Show how you could use the Parity flag combined with an arithmetic instruction to determine if this message byte has even or odd parity.

**답:**
```asm
mov al, 01110101b
add al, 0          ; 또는 test al, 0FFh
; PF = 1이면 짝수 패리티 (1비트 개수가 짝수)
; PF = 0이면 홀수 패리티 (1비트 개수가 홀수)
```
설명: 01110101b는 1비트가 5개(홀수)이므로 PF = 0

---

## 4. Write code using byte operands that adds two negative integers and causes the Overflow flag to be set.

**답:**
```asm
mov al, -64       ; AL = C0h
add al, -65       ; AL = BFh, -64 + (-65) = -129
; 부호있는 바이트 범위(-128 ~ 127)를 초과하여 OF = 1
```
또는
```asm
mov al, -100      ; AL = 9Ch
add al, -100      ; -100 + (-100) = -200 (범위 초과)
; OF = 1
```

---

## 5. Write a sequence of two instructions that use addition to set the Zero and Carry flags at the same time.

**답:**
```asm
mov al, 0FFh
add al, 1         ; AL = 0 (ZF = 1), 캐리 발생 (CF = 1)
```

---

## 6. Write a sequence of two instructions that set the Carry flag using subtraction.

**답:**
```asm
mov al, 1
sub al, 2         ; 1 - 2는 언더플로우 발생, CF = 1
```

---

## 7. Implement the following arithmetic expression in assembly language: EAX = –val2 + 7 – val3 + val1. Assume that val1, val2, and val3 are 32-bit integer variables.

**답:**
```asm
mov eax, val1      ; EAX = val1
sub eax, val2      ; EAX = val1 - val2
add eax, 7         ; EAX = val1 - val2 + 7
sub eax, val3      ; EAX = val1 - val2 + 7 - val3
```
또는
```asm
mov eax, 7
sub eax, val2      ; EAX = 7 - val2
sub eax, val3      ; EAX = 7 - val2 - val3
add eax, val1      ; EAX = val1 - val2 + 7 - val3
```

---

## 8. Write a loop that iterates through a doubleword array and calculates the sum of its elements using a scale factor with indexed addressing.

**답:**
```asm
.data
array DWORD 10, 20, 30, 40, 50
arraySize = ($ - array) / TYPE array

.code
mov esi, 0              ; 인덱스 초기화
mov eax, 0              ; 합계 초기화
mov ecx, arraySize      ; 루프 카운터

L1:
    add eax, array[esi*4]    ; scale factor 4 사용
    inc esi
    loop L1
```
또는
```asm
mov esi, 0
mov eax, 0
mov ecx, arraySize

L1:
    add eax, [array + esi*TYPE array]
    inc esi
    loop L1
```

---

## 9. Implement the following expression in assembly language: AX = (val2 + BX) – val4. Assume that val2 and val4 are 16-bit integer variables.

**답:**
```asm
mov ax, val2
add ax, bx         ; AX = val2 + BX
sub ax, val4       ; AX = (val2 + BX) - val4
```

---

## 10. Write a sequence of two instructions that set both the Carry and Overflow flags at the same time.

**답:**
```asm
mov al, -128       ; AL = 80h
sub al, 1          ; AL = 7Fh (127)
; CF = 1 (차용 발생), OF = 1 (부호 변경)
```
또는
```asm
mov al, 127        ; AL = 7Fh
add al, 1          ; AL = 80h (-128)
; CF = 0, OF = 1... 이건 CF가 설정 안 됨

mov al, 0
sub al, 1          ; AL = FFh
add al, 127        ; AL = 7Eh, CF = 1, OF = 1
```

더 나은 답:
```asm
mov al, -1         ; AL = FFh
sub al, 127        ; AL = 80h (-128)
; CF = 1, OF = 1
```

---

## 11. Write a sequence of instructions showing how the Zero flag could be used to indicate unsigned overflow after executing INC and DEC instructions.

**답:**
```asm
; INC로 부호없는 오버플로우 감지
mov al, 0FFh       ; 최대값
inc al             ; AL = 0, ZF = 1
; ZF = 1이면 오버플로우 발생

; DEC로 부호없는 언더플로우 감지
mov al, 0          ; 최소값
dec al             ; AL = FFh, ZF = 0
; ZF = 1이 아니면 언더플로우 발생
```
설명: INC/DEC는 CF를 변경하지 않으므로 ZF를 사용하여 0으로의 랩어라운드를 감지

---

## Use the following data definitions for Questions 12–18:
```asm
.data
myBytes BYTE 10h,20h,30h,40h
myWords WORD 3 DUP(?),2000h
myString BYTE "ABCDE"
```

### 12. Insert a directive in the given data that aligns myBytes to an even-numbered address.

**답:**
```asm
.data
ALIGN 2
myBytes BYTE 10h,20h,30h,40h
myWords WORD 3 DUP(?),2000h
myString BYTE "ABCDE"
```

---

### 13. What will be the value of EAX after each of the following instructions execute?
```asm
mov eax,TYPE myBytes        ; a.
mov eax,LENGTHOF myBytes    ; b.
mov eax,SIZEOF myBytes      ; c.
mov eax,TYPE myWords        ; d.
mov eax,LENGTHOF myWords    ; e.
mov eax,SIZEOF myWords      ; f.
mov eax,SIZEOF myString     ; g.
```

**답:**
- **(a)** EAX = 1 (BYTE의 크기는 1바이트)
- **(b)** EAX = 4 (myBytes에 4개 요소)
- **(c)** EAX = 4 (4 * 1 = 4바이트)
- **(d)** EAX = 2 (WORD의 크기는 2바이트)
- **(e)** EAX = 4 (3 DUP(?) + 2000h = 4개 요소)
- **(f)** EAX = 8 (4 * 2 = 8바이트)
- **(g)** EAX = 5 ("ABCDE" = 5바이트)

---

### 14. Write a single instruction that moves the first two bytes in myBytes to the DX register. The resulting value will be 2010h.

**답:**
```asm
mov dx, WORD PTR myBytes
```
설명: 리틀 엔디안이므로 10h, 20h → DX = 2010h

---

### 15. Write an instruction that moves the second byte in myWords to the AL register.

**답:**
```asm
mov al, BYTE PTR myWords+1
```
또는
```asm
mov al, BYTE PTR [myWords+1]
```

---

### 16. Write an instruction that moves all four bytes in myBytes to the EAX register.

**답:**
```asm
mov eax, DWORD PTR myBytes
```
결과: EAX = 40302010h (리틀 엔디안)

---

### 17. Insert a LABEL directive in the given data that permits myWords to be moved directly to a 32-bit register.

**답:**
```asm
.data
myBytes BYTE 10h,20h,30h,40h
myWordsDword LABEL DWORD
myWords WORD 3 DUP(?),2000h
myString BYTE "ABCDE"
```
사용법:
```asm
mov eax, myWordsDword
```

---

### 18. Insert a LABEL directive in the given data that permits myBytes to be moved directly to a 16-bit register.

**답:**
```asm
.data
myBytesWord LABEL WORD
myBytes BYTE 10h,20h,30h,40h
myWords WORD 3 DUP(?),2000h
myString BYTE "ABCDE"
```
사용법:
```asm
mov ax, myBytesWord
```
