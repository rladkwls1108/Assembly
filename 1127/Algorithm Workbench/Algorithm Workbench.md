# Algorithm Workbench

## 1. Base-Index Operand 예시 (32비트)

**문제:** Show an example of a base-index operand in 32-bit mode.

**답:**
```asm
mov eax, [ebx + esi]
```

또는
```asm
mov eax, [edi + ecx]
```

베이스 레지스터와 인덱스 레지스터를 더하여 유효 주소를 계산합니다.

---

## 2. Base-Index-Displacement Operand 예시 (32비트)

**문제:** Show an example of a base-index-displacement operand in 32-bit mode.

**답:**
```asm
mov eax, [ebx + esi + 4]
```

또는
```asm
mov eax, myArray[ebx + esi]
```

베이스 레지스터 + 인덱스 레지스터 + 변위(상수 또는 변수 오프셋)를 더하여 유효 주소를 계산합니다.

---

## 3. 2차원 배열 주소 지정 표현식

**문제:** Suppose a two-dimensional array of doublewords has three logical rows and four logical columns. Write an expression using ESI and EDI that addresses the third column in the second row. (Numbering for rows and columns starts at zero.)

**답:**
```asm
; 행 = 1 (두 번째 행), 열 = 2 (세 번째 열)
; 각 행은 4개의 DWORD (16바이트)
; 오프셋 = (행 × 열개수 + 열) × 요소크기

mov esi, 1              ; 행 인덱스
mov edi, 2              ; 열 인덱스

; 방법 1: 계산된 오프셋 사용
mov eax, array[esi * 16 + edi * 4]

; 방법 2: ROWSIZE 상수 사용
ROWSIZE = 4 * TYPE DWORD    ; 16
mov eax, array[esi * ROWSIZE + edi * TYPE DWORD]
```

또는 간단히:
```asm
mov eax, [array + esi * 16 + edi * 4]
```

---

## 4. CMPSW를 사용한 16비트 배열 비교

**문제:** Write instructions using CMPSW that compare two arrays of 16-bit values named sourcew and targetw.

**답:**
```asm
.data
sourcew WORD 1, 2, 3, 4, 5
targetw WORD 1, 2, 3, 4, 5
ARRAY_SIZE = LENGTHOF sourcew

.code
    cld                         ; Direction Flag 클리어 (정방향)
    mov esi, OFFSET sourcew     ; ESI = 소스 배열 주소
    mov edi, OFFSET targetw     ; EDI = 타겟 배열 주소
    mov ecx, ARRAY_SIZE         ; ECX = 비교할 요소 개수
    repe cmpsw                  ; 같은 동안 반복 비교
    ; ZF = 1이면 두 배열이 동일
    ; ZF = 0이면 다른 요소 발견
```

---

## 5. SCASW를 사용한 16비트 값 검색

**문제:** Write instructions that use SCASW to scan for the 16-bit value 0100h in an array named wordArray, and copy the offset of the matching member into the EAX register.

**답:**
```asm
.data
wordArray WORD 50h, 80h, 100h, 200h, 300h

.code
    cld                         ; Direction Flag 클리어 (정방향)
    mov edi, OFFSET wordArray   ; EDI = 배열 시작 주소
    mov ax, 0100h               ; 검색할 값
    mov ecx, LENGTHOF wordArray ; ECX = 배열 요소 개수
    repne scasw                 ; 다른 동안 반복 스캔
    jnz NotFound                ; 찾지 못함
    
    sub edi, 2                  ; SCASW 실행 후 EDI가 2 증가했으므로 보정
    mov eax, edi                ; EAX = 일치하는 요소의 오프셋
    jmp Done
    
NotFound:
    mov eax, -1                 ; 찾지 못한 경우 -1 반환
    
Done:
```

---

## 6. Str_compare를 사용한 문자열 비교 및 출력

**문제:** Write a sequence of instructions that use the Str_compare procedure to determine the larger of two input strings and write it to the console window.

**답:**
```asm
.data
string1 BYTE "Apple", 0
string2 BYTE "Banana", 0

.code
main PROC
    mov esi, OFFSET string1     ; ESI = 첫 번째 문자열
    mov edi, OFFSET string2     ; EDI = 두 번째 문자열
    call Str_compare            ; 문자열 비교
    
    ; Carry Flag와 Zero Flag로 결과 판단
    ja PrintFirst               ; string1 > string2
    jmp PrintSecond             ; string1 <= string2
    
PrintFirst:
    mov edx, OFFSET string1
    jmp PrintResult
    
PrintSecond:
    mov edx, OFFSET string2
    
PrintResult:
    call WriteString            ; 더 큰 문자열 출력
    call Crlf
    
    exit
main ENDP
```

---

## 7. Str_trim으로 후행 "@" 문자 제거

**문제:** Show how to call the Str_trim procedure and remove all trailing "@" characters from a string.

**답:**
```asm
.data
myString BYTE "Hello@@@", 0

.code
    mov esi, OFFSET myString    ; ESI = 문자열 주소
    mov al, '@'                 ; AL = 제거할 문자
    call Str_trim               ; 후행 '@' 문자 제거
```

INVOKE 사용 시:
```asm
INVOKE Str_trim, OFFSET myString, '@'
```

---

## 8. Str_ucase를 소문자 변환으로 수정

**문제:** Show how to modify the Str_ucase procedure from the Irvine32 library so it changes all characters to lower case.

**답:**
```asm
Str_lcase PROC USES eax esi,
    pString:PTR BYTE
    
    mov esi, pString
    
L1:
    mov al, [esi]               ; 현재 문자 로드
    cmp al, 0                   ; 널 종료 문자 확인
    je L3                       ; 널이면 종료
    
    cmp al, 'A'                 ; 'A'보다 작으면 건너뜀
    jb L2
    cmp al, 'Z'                 ; 'Z'보다 크면 건너뜀
    ja L2
    
    add al, 32                  ; 대문자를 소문자로 변환 ('A'-'a' = -32)
    mov [esi], al               ; 변환된 문자 저장
    
L2:
    inc esi                     ; 다음 문자로 이동
    jmp L1
    
L3:
    ret
Str_lcase ENDP
```

---

## 9. 64비트 버전 Str_trim 프로시저

**문제:** Create a 64-bit version of the Str_trim procedure.

**답:**
```asm
;--------------------------------------------------
; Str_trim64
; 문자열 끝에서 지정된 문자를 모두 제거합니다.
; 입력: RCX = 문자열 주소
;       DL = 제거할 문자
; 반환: 없음
;--------------------------------------------------
Str_trim64 PROC USES rax rcx rdi
    mov rdi, rcx                ; RDI = 문자열 주소
    
    ; 문자열 길이 계산 (널 문자 찾기)
    xor al, al                  ; AL = 0 (널 문자)
    mov rcx, -1                 ; 최대 검색 길이
    cld                         ; 정방향
    repne scasb                 ; 널 문자 검색
    
    dec rdi                     ; 널 문자 위치로 이동
    cmp rdi, rcx                ; 빈 문자열 확인
    je L2                       ; 빈 문자열이면 종료
    
    ; 문자열 끝에서 역방향으로 스캔
    std                         ; 역방향 설정
    dec rdi                     ; 널 문자 이전 위치로
    mov al, dl                  ; AL = 제거할 문자
    
L1:
    cmp rdi, rcx                ; 문자열 시작 확인
    jb L2                       ; 시작 이전이면 종료
    cmp [rdi], al               ; 현재 문자와 비교
    jne L2                      ; 다르면 종료
    dec rdi                     ; 이전 문자로 이동
    jmp L1
    
L2:
    mov BYTE PTR [rdi + 1], 0   ; 새로운 널 종료 문자 삽입
    cld                         ; Direction Flag 복원
    ret
Str_trim64 ENDP
```

---

## 10. Base-Index Operand 예시 (64비트)

**문제:** Show an example of a base-index operand in 64-bit mode.

**답:**
```asm
mov rax, [rbx + rsi]
```

또는
```asm
mov rax, [rdi + rcx]
```

64비트 모드에서는 64비트 레지스터(RAX, RBX, RCX, RDX, RSI, RDI, R8-R15)를 사용합니다.

---

## 11. 2차원 배열 요소 접근 (32비트)

**문제:** Assuming that EBX contains a row index into a two-dimensional array of 32-bit integers named myArray and EDI contains the index of a column, write a single statement that moves the content of the given array element into the EAX register.

**답:**
```asm
; myArray가 N개의 열을 가진다고 가정 (COLUMNS = N)
COLUMNS = 4     ; 예: 4개의 열

mov eax, myArray[ebx * (COLUMNS * 4) + edi * 4]
```

또는 ROWSIZE 상수 사용:
```asm
ROWSIZE = COLUMNS * TYPE DWORD

mov eax, myArray[ebx * ROWSIZE + edi * TYPE DWORD]
```

---

## 12. 2차원 배열 요소 접근 (64비트)

**문제:** Assuming that RBX contains a row index into a two-dimensional array of 64-bit integers named myArray and RDI contains the index of a column, write a single statement that moves the content of the given array element into the RAX register.

**답:**
```asm
; myArray가 N개의 열을 가진다고 가정 (COLUMNS = N)
COLUMNS = 4     ; 예: 4개의 열

mov rax, myArray[rbx * (COLUMNS * 8) + rdi * 8]
```

또는 ROWSIZE 상수 사용:
```asm
ROWSIZE = COLUMNS * TYPE QWORD  ; QWORD = 8바이트

mov rax, myArray[rbx * ROWSIZE + rdi * TYPE QWORD]
```

**참고:** 64비트 정수(QWORD)는 8바이트이므로 스케일 팩터가 8이 됩니다.
