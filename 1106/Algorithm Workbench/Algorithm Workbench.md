# 6.10.2 Algorithm Workbench

## 1. Write a single instruction that converts an ASCII digit in AL to its corresponding binary value. If AL already contains a binary value (00h to 09h), leave it unchanged.

**답:**
```assembly
and al, 0Fh
```

**설명:** ASCII 숫자 '0'-'9'는 30h-39h입니다. 하위 4비트만 남기면 0-9의 이진값이 됩니다. 이미 00h-09h인 경우에도 값이 변하지 않습니다.

## 2. Write instructions that calculate the parity of a 32-bit memory operand. Hint: Use the formula presented earlier in this section: B0 XOR B1 XOR B2 XOR B3.

**답:**
```assembly
mov eax, [operand]    ; 32비트 메모리 피연산자 로드
mov ebx, eax          ; 복사본 생성
shr ebx, 16           ; 상위 16비트를 하위로 이동
xor eax, ebx          ; B0 XOR B2, B1 XOR B3
mov ebx, eax          ; 결과 복사
shr ebx, 8            ; 상위 8비트를 하위로 이동
xor al, bl            ; 최종 XOR
; AL의 비트 0에 패리티 결과가 저장됨
```

**설명:** 32비트를 4개의 바이트로 나누어 XOR 연산을 수행하여 패리티를 계산합니다.

## 3. Given two bit-mapped sets named SetX and SetY, write a sequence of instructions that generate a bit string in EAX that represents members in SetX that are not members of SetY.

**답:**
```assembly
mov eax, SetX         ; SetX 로드
not SetY              ; SetY의 보수 계산
and eax, SetY         ; SetX AND (NOT SetY)
not SetY              ; SetY를 원래 값으로 복원
```

**또는:**

```assembly
mov eax, SetX         ; SetX 로드
mov ebx, SetY         ; SetY 로드
not ebx               ; SetY의 보수
and eax, ebx          ; SetX AND (NOT SetY)
```

**설명:** SetX에는 있지만 SetY에는 없는 멤버는 SetX AND (NOT SetY)로 구할 수 있습니다.

## 4. Write instructions that jump to label L1 when the unsigned integer in DX is less than or equal to the integer in CX.

**답:**
```assembly
cmp dx, cx
jbe L1                ; Jump if Below or Equal (부호 없는 비교)
```

**설명:** JBE는 CF=1 또는 ZF=1일 때 점프합니다 (DX ≤ CX, 부호 없는 비교).

## 5. Write instructions that jump to label L2 when the signed integer in AX is greater than the integer in CX.

**답:**
```assembly
cmp ax, cx
jg L2                 ; Jump if Greater (부호 있는 비교)
```

**설명:** JG는 ZF=0이고 SF=OF일 때 점프합니다 (AX > CX, 부호 있는 비교).

## 6. Write instructions that first clear bits 0 and 1 in AL. Then, if the destination operand is equal to zero, the code should jump to label L3. Otherwise, it should jump to label L4.

**답:**
```assembly
and al, 11111100b     ; 비트 0과 1을 클리어 (0FCh)
jz L3                 ; AL이 0이면 L3로 점프
jmp L4                ; 그렇지 않으면 L4로 점프
```

**설명:** AND 연산으로 비트 0, 1을 클리어하고, 결과가 0인지 확인하여 분기합니다.

## 7. Implement the following pseudocode in assembly language. Use short-circuit evaluation and assume that val1 and X are 32-bit variables.

```c
if( val1 > ecx ) AND ( ecx > edx )
    X = 1
else
    X = 2;
```

**답:**
```assembly
        mov eax, val1
        cmp eax, ecx
        jbe else_part        ; val1 <= ecx이면 else로
        cmp ecx, edx
        jbe else_part        ; ecx <= edx이면 else로
        mov X, 1             ; 두 조건 모두 참
        jmp end_if
else_part:
        mov X, 2
end_if:
```

**설명:** Short-circuit 평가를 사용하여 첫 번째 조건이 거짓이면 두 번째 조건을 평가하지 않고 else로 분기합니다.

## 8. Implement the following pseudocode in assembly language. Use short-circuit evaluation and assume that X is a 32-bit variable.

```c
if( ebx > ecx ) OR ( ebx > val1 )
    X = 1
else
    X = 2
```

**답:**
```assembly
        cmp ebx, ecx
        ja then_part         ; ebx > ecx이면 then으로
        cmp ebx, val1
        jbe else_part        ; ebx <= val1이면 else로
then_part:
        mov X, 1
        jmp end_if
else_part:
        mov X, 2
end_if:
```

**설명:** OR 연산에서는 첫 번째 조건이 참이면 즉시 then 블록으로 이동합니다.

## 9. Implement the following pseudocode in assembly language. Use short-circuit evaluation and assume that X is a 32-bit variable.

```c
if( ebx > ecx AND ebx > edx) OR ( edx > eax )
    X = 1
else
    X = 2
```

**답:**
```assembly
        cmp ebx, ecx
        jbe check_second     ; ebx <= ecx이면 두 번째 OR 조건 확인
        cmp ebx, edx
        jbe check_second     ; ebx <= edx이면 두 번째 OR 조건 확인
        jmp then_part        ; 첫 번째 AND 조건 참
check_second:
        cmp edx, eax
        jbe else_part        ; edx <= eax이면 else로
then_part:
        mov X, 1
        jmp end_if
else_part:
        mov X, 2
end_if:
```

**설명:** (ebx > ecx AND ebx > edx) OR (edx > eax)를 short-circuit으로 평가합니다.

## 10. Implement the following pseudocode in assembly language. Use short-circuit evaluation and assume that A, B, and N are 32-bit signed integers.

```c
while N > 0
    if N != 3 AND (N < A OR N > B)
        N = N – 2
    else
        N = N – 1
end while
```

**답:**
```assembly
while_start:
        cmp N, 0
        jle while_end        ; N <= 0이면 루프 종료
        
        cmp N, 3
        je else_part         ; N == 3이면 else로
        
        cmp N, A
        jl then_part         ; N < A이면 N = N - 2
        cmp N, B
        jg then_part         ; N > B이면 N = N - 2
        jmp else_part        ; 조건 불만족
        
then_part:
        sub N, 2             ; N = N - 2
        jmp while_start
        
else_part:
        dec N                ; N = N - 1
        jmp while_start
        
while_end:
```

**설명:** while 루프와 중첩된 if 문을 short-circuit 평가로 구현합니다. N != 3이 거짓이면 즉시 else로, (N < A OR N > B) 조건 중 하나라도 참이면 then으로 분기합니다.
