# 7.9.2 Algorithm Workbench

## 1. Sign-Extend AX into EAX without CWD

**Question:** Write a sequence of shift instructions that cause AX to be sign-extended into EAX. In other words, the sign bit of AX is copied into the upper 16 bits of EAX. Do not use the CWD instruction.

**Answer:**

```assembly
movsx eax, ax    ; 방법 1: movsx 사용 (가장 간단)

; 또는 shift 명령어만 사용:
shl eax, 16      ; 방법 2: EAX의 상위 16비트로 AX 이동
sar eax, 16      ; 산술 우측 시프트로 부호 확장
```

**설명:**
- `movsx`는 부호 확장을 직접 수행
- shift 방법: AX를 상위로 이동 후 SAR로 부호 비트를 복사하며 원위치

---

## 2. Rotate Right without ROT instruction

**Question:** Suppose the instruction set contained no rotate instructions. Show how you would use SHR and a conditional jump instruction to rotate the contents of the AL register 1 bit to the right.

**Answer:**

```assembly
shr al, 1          ; AL을 1비트 우측 시프트 (최하위 비트는 CF로)
jnc skip           ; Carry가 0이면 skip
or al, 80h         ; Carry가 1이면 최상위 비트를 1로 설정
skip:
```

**설명:**
- SHR은 최하위 비트를 Carry 플래그로 이동
- Carry가 1이면 최상위 비트에 1을 설정하여 회전 효과 구현

---

## 3. Multiply EAX by 16

**Question:** Write a logical shift instruction that multiplies the contents of EAX by 16.

**Answer:**

```assembly
shl eax, 4         ; EAX * 16 (2^4 = 16)
```

**설명:**
- 좌측 시프트 4비트 = 16배 곱셈

---

## 4. Divide EBX by 4

**Question:** Write a logical shift instruction that divides EBX by 4.

**Answer:**

```assembly
shr ebx, 2         ; EBX / 4 (2^2 = 4)
```

**설명:**
- 우측 시프트 2비트 = 4로 나눗셈

---

## 5. Exchange High and Low Halves of DL

**Question:** Write a single rotate instruction that exchanges the high and low halves of the DL register.

**Answer:**

```assembly
rol dl, 4          ; 또는 ror dl, 4
```

**설명:**
- 4비트 회전으로 상위 4비트와 하위 4비트 교환
- 예: 10110011b → 00111011b

---

## 6. SHLD Instruction

**Question:** Write a single SHLD instruction that shifts the highest bit of the AX register into the lowest bit position of DX and shifts DX one bit to the left.

**Answer:**

```assembly
shld dx, ax, 1
```

**설명:**
- SHLD는 DX를 좌측으로 시프트하면서 AX의 최상위 비트를 DX의 최하위로 이동

---

## 7. Shift 3 Bytes Right by 1 bit

**Question:** Write a sequence of instructions that shift three memory bytes to the right by 1 bit position. Use the following test data:

```assembly
byteArray BYTE 81h,20h,33h
```

**Answer:**

```assembly
clc                          ; Carry 플래그 클리어
mov esi, 0                   ; 인덱스 초기화
rcr byteArray[esi], 1        ; 첫 번째 바이트 시프트
inc esi
rcr byteArray[esi], 1        ; 두 번째 바이트 시프트 (Carry 포함)
inc esi
rcr byteArray[esi], 1        ; 세 번째 바이트 시프트 (Carry 포함)

; 결과: 81h,20h,33h → 40h,90h,19h
```

**설명:**
- RCR을 사용하여 Carry를 통해 비트를 전달하며 우측 시프트

---

## 8. Shift 3 Words Left by 1 bit

**Question:** Write a sequence of instructions that shift three memory words to the left by 1 bit position. Use the following test data:

```assembly
wordArray WORD 810Dh, 0C064h, 93ABh
```

**Answer:**

```assembly
clc                          ; Carry 플래그 클리어
mov esi, 4                   ; 마지막 워드의 인덱스 (역순 처리)
rcl wordArray[esi], 1        ; 세 번째 워드 시프트
sub esi, 2
rcl wordArray[esi], 1        ; 두 번째 워드 시프트 (Carry 포함)
sub esi, 2
rcl wordArray[esi], 1        ; 첫 번째 워드 시프트 (Carry 포함)

; 결과: 810Dh,0C064h,93ABh → 021Ah,80C8h,2756h
```

**설명:**
- RCL을 사용하여 역순으로 처리하여 Carry를 올바르게 전파

---

## 9. Multiply 5 by 3

**Question:** Write instructions that multiply 5 by 3 and store the result in a 16-bit variable val1.

**Answer:**

```assembly
.data
val1 WORD ?

.code
mov ax, 5
mov bx, 3
mul bx              ; AX = 5 * 3 = 15
mov val1, ax
```

**설명:**
- MUL 명령어로 부호 없는 곱셈 수행

---

## 10. Divide 276 by 10

**Question:** Write instructions that divide 276 by 10 and store the result in a 16-bit variable val1.

**Answer:**

```assembly
.data
val1 WORD ?

.code
mov ax, 276
mov bl, 10
div bl              ; AL = 27 (몫), AH = 6 (나머지)
movzx ax, al        ; AX = 27
mov val1, ax
```

**설명:**
- DIV로 나눗셈 수행, 몫만 저장

---

## 11. Implement: val1 = (val2 * val3) / (val4 - 3)

**Question:** Implement the following C++ expression in assembly language, using 32-bit unsigned operands:

```cpp
val1 = (val2 * val3) / (val4 - 3)
```

**Answer:**

```assembly
.data
val1 DWORD ?
val2 DWORD ?
val3 DWORD ?
val4 DWORD ?

.code
mov eax, val2
mul val3            ; EDX:EAX = val2 * val3
mov ebx, val4
sub ebx, 3          ; EBX = val4 - 3
div ebx             ; EAX = (val2 * val3) / (val4 - 3)
mov val1, eax
```

**설명:**
- 곱셈 후 나눗셈을 순서대로 수행
- 32비트 부호 없는 연산 사용

---

## 12. Implement: val1 = (val2 / val3) * (val1 + val2)

**Question:** Implement the following C++ expression in assembly language, using 32-bit signed operands:

```cpp
val1 = (val2 / val3) * (val1 + val2)
```

**Answer:**

```assembly
.data
val1 SDWORD ?
val2 SDWORD ?
val3 SDWORD ?

.code
; 먼저 (val1 + val2) 계산
mov ebx, val1
add ebx, val2       ; EBX = val1 + val2

; (val2 / val3) 계산
mov eax, val2
cdq                 ; 부호 확장 EAX → EDX:EAX
idiv val3           ; EAX = val2 / val3

; 곱셈
imul eax, ebx       ; EAX = (val2 / val3) * (val1 + val2)
mov val1, eax
```

**설명:**
- 부호 있는 나눗셈 전 CDQ로 부호 확장 필수
- IMUL로 부호 있는 곱셈 수행

---

## 13. Display 8-bit Binary in Decimal (0-99)

**Question:** Write a procedure that displays an unsigned 8-bit binary value in decimal format. Pass the binary value in AL. The input range is limited to 0 to 99, decimal.

**Answer:**

```assembly
showDecimal8 PROC
    push eax
    push edx
    
    mov ah, 0           ; AX = AL (확장)
    mov dl, 10
    div dl              ; AL = 십의 자리, AH = 일의 자리
    
    add al, '0'         ; ASCII 변환
    call WriteChar      ; 십의 자리 출력
    
    mov al, ah
    add al, '0'         ; ASCII 변환
    call WriteChar      ; 일의 자리 출력
    
    pop edx
    pop eax
    ret
showDecimal8 ENDP
```

**설명:**
- 10으로 나누어 십의 자리와 일의 자리 분리
- ASCII 코드로 변환 후 출력

---

## 14. AAA Instruction Analysis

**Question:** Challenge: Suppose AX contains 0072h and the Auxiliary Carry flag is set as a result of adding two unknown ASCII decimal digits. Use the Intel manual to determine what output the AAA instruction would produce.

**Answer:**

**AX = 0108h, CF = 1**

**설명:**
- 초기값: AX = 0072h, AF = 1
- AAA 실행 조건: AF = 1 또는 (AL의 하위 4비트 > 9)
- AF가 1이므로:
  1. AL = AL + 6 = 72h + 6 = 78h
  2. AH = AH + 1 = 00h + 1 = 01h
  3. AL의 하위 4비트만 유지: AL = 08h
  4. CF = 1, AF = 1 설정
- 최종 결과: AX = 0108h

---

## 15. Calculate x = n mod y (y is power of 2)

**Question:** Challenge: Using only SUB, MOV, and AND instructions, show how to calculate x = n mod y, assuming that you are given the values of n and y. You can assume that n is any 32-bit unsigned integer, and y is a power of 2.

**Answer:**

```assembly
; n mod y (y는 2의 거듭제곱)
; 예: n mod 8 (y = 8 = 2^3)

.data
n DWORD ?
y DWORD 8      ; 2의 거듭제곱
x DWORD ?

.code
mov eax, n
mov ebx, y
sub ebx, 1     ; y - 1 (마스크 생성: 8-1 = 7 = 00000111b)
and eax, ebx   ; n AND (y-1) = n mod y
mov x, eax
```

**설명:**
- y가 2의 거듭제곱일 때: n mod y = n AND (y-1)
- 예: 23 mod 8 = 23 AND 7 = 10111b AND 00111b = 00111b = 7

---

## 16. Absolute Value using SAR, ADD, XOR

**Question:** Challenge: Using only SAR, ADD, and XOR instructions (but no conditional jumps), write code that calculates the absolute value of the signed integer in the EAX register.

**Answer:**

```assembly
; EAX의 절댓값 계산 (조건 점프 없이)
mov ebx, eax       ; 원본 저장
sar ebx, 31        ; 부호 비트를 모든 비트로 확장 (음수면 FFFFFFFFh, 양수면 00000000h)
xor eax, ebx       ; 음수면 1의 보수, 양수면 변화 없음
sub eax, ebx       ; 음수면 +1 (2의 보수), 양수면 -0
```

**설명:**
- **원리:**
  - 양수: EBX = 0, EAX XOR 0 = EAX, EAX - 0 = EAX (변화 없음)
  - 음수: EBX = -1 (FFFFFFFFh), EAX XOR -1 = ~EAX (1의 보수), ~EAX - (-1) = ~EAX + 1 (2의 보수)
- **예시:**
  - EAX = 5: EBX = 0 → 5 XOR 0 = 5 → 5 - 0 = 5
  - EAX = -5: EBX = -1 → -5 XOR -1 = 4 → 4 - (-1) = 5
 
