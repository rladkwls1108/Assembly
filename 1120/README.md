# Chapter 8: Advanced Procedures 요약

## 8.1 Stack Frames (스택 프레임)

### 스택 프레임이란?
스택에 할당된 영역으로 다음을 포함:
- 전달된 인수
- 반환 주소
- 지역 변수
- 저장된 레지스터

### 스택 프레임 생성 과정
```
1. Push Arguments    → 인수를 스택에 배치
2. Call Subroutine   → 반환 주소 push
3. Push EBP          → 이전 EBP 저장
4. Set EBP = ESP     → 새 베이스 포인터 설정
5. Allocate Locals   → 지역 변수 공간 예약
6. Save Registers    → 사용할 레지스터 저장
```

### 값 전달 vs 참조 전달

| 방식 | 설명 | 예시 |
|------|------|------|
| **값 전달** | 값의 복사본 전달 | `push val1` |
| **참조 전달** | 주소(오프셋) 전달 | `push OFFSET val1` |

### 스택 매개변수 접근
```asm
AddTwo PROC
    push ebp
    mov  ebp, esp
    mov  eax, [ebp + 12]    ; 두 번째 매개변수
    add  eax, [ebp + 8]     ; 첫 번째 매개변수
    pop  ebp
    ret
AddTwo ENDP
```

**스택 구조:**
```
[EBP + 12]  → 두 번째 매개변수
[EBP + 8]   → 첫 번째 매개변수
[EBP + 4]   → 반환 주소
[EBP]       → 저장된 EBP  ← EBP
```

---

## 8.2 Calling Conventions (호출 규약)

| 규약 | 스택 정리 | 특징 |
|------|----------|------|
| **C** | 호출자 (caller) | `add esp, n` 사용, 가변 인자 지원 |
| **STDCALL** | 피호출자 (callee) | `ret n` 사용, Windows API 표준 |

**STDCALL 예시:**
```asm
AddTwo PROC
    push ebp
    mov  ebp, esp
    mov  eax, [ebp + 8]
    add  eax, [ebp + 12]
    pop  ebp
    ret  8              ; 8바이트 정리 (매개변수 2개 × 4바이트)
AddTwo ENDP
```

---

## 8.3 Local Variables (지역 변수)

지역 변수는 **EBP 아래**에 할당됩니다.
```asm
MySub PROC
    push ebp
    mov  ebp, esp
    sub  esp, 8             ; 지역 변수 8바이트 할당
    mov  DWORD PTR [ebp-4], 10  ; 첫 번째 지역 변수
    mov  DWORD PTR [ebp-8], 20  ; 두 번째 지역 변수
    mov  esp, ebp           ; 지역 변수 해제
    pop  ebp
    ret
MySub ENDP
```

---

## 8.4 ENTER / LEAVE Instructions

| 명령어 | 동작 | 등가 코드 |
|--------|------|----------|
| `ENTER n, 0` | 스택 프레임 생성 | `push ebp` / `mov ebp,esp` / `sub esp,n` |
| `LEAVE` | 스택 프레임 해제 | `mov esp,ebp` / `pop ebp` |
```asm
MySub PROC
    enter 8, 0          ; 8바이트 지역 변수 공간
    ...
    leave
    ret
MySub ENDP
```

---

## 8.5 LEA Instruction

`LEA`는 실행 시간에 주소를 계산합니다 (OFFSET은 컴파일 시간 상수만 가능).
```asm
lea  esi, [ebp-30]      ; 지역 변수의 주소 로드
```

---

## 8.6 LOCAL Directive
```asm
MySub PROC
    LOCAL temp:DWORD, flag:BYTE
    LOCAL pArray:PTR DWORD
    LOCAL buffer[20]:BYTE
```

---

## 8.7 Recursion (재귀)

### 팩토리얼 예시
```asm
Factorial PROC
    push ebp
    mov  ebp, esp
    mov  eax, [ebp+8]       ; n 가져오기
    cmp  eax, 0
    ja   L1
    mov  eax, 1             ; 0! = 1 (기저 조건)
    jmp  L2
L1: dec  eax
    push eax
    call Factorial          ; Factorial(n-1)
    mov  ebx, [ebp+8]
    mul  ebx                ; n * Factorial(n-1)
L2: pop  ebp
    ret  4
Factorial ENDP
```

---

## 8.8 INVOKE, ADDR, PROC, PROTO

### INVOKE (32비트 전용)
```asm
; 기존 방식
push OFFSET array
push LENGTHOF array
call MyProc

; INVOKE 사용
INVOKE MyProc, OFFSET array, LENGTHOF array
```

### ADDR Operator
```asm
INVOKE Swap, ADDR val1, ADDR val2
```
- INVOKE와 함께만 사용 가능
- 어셈블리 시간 상수만 가능

### PROC with Parameters
```asm
AddTwo PROC,
    val1:DWORD,
    val2:DWORD
    mov  eax, val1
    add  eax, val2
    ret
AddTwo ENDP
```

### PROTO Directive
```asm
; 프로토타입 선언 (INVOKE 전에 필요)
AddTwo PROTO, val1:DWORD, val2:DWORD

; 사용
INVOKE AddTwo, 5, 6
```

---

## 8.9 Multimodule Programs (멀티모듈 프로그램)

### 프로시저 내보내기/숨기기
```asm
mySub PROC PRIVATE          ; 현재 모듈에서만 접근 가능
mySub PROC PUBLIC           ; 다른 모듈에서 접근 가능 (기본값)
```

### EXTERN Directive
```asm
EXTERN AddTwo@8:PROC        ; 외부 프로시저 선언 (@8 = 매개변수 8바이트)
```

### EXTERNDEF (PUBLIC + EXTERN)
```asm
; vars.inc
EXTERNDEF count:DWORD, SYM1:ABS

; 두 모듈 모두에서 INCLUDE vars.inc
```

---

## 핵심 요약

| 개념 | 설명 |
|------|------|
| **스택 프레임** | 프로시저의 매개변수, 반환주소, 지역변수, 저장 레지스터 영역 |
| **[EBP+n]** | 스택 매개변수 접근 (n ≥ 8) |
| **[EBP-n]** | 지역 변수 접근 |
| **STDCALL** | 피호출자가 `ret n`으로 스택 정리 |
| **C Convention** | 호출자가 `add esp,n`으로 스택 정리 |
| **INVOKE** | 자동으로 인수 push 및 호출 |
| **PROTO** | 프로시저 프로토타입 선언 |
| **LOCAL** | 지역 변수 선언 |
| **ENTER/LEAVE** | 스택 프레임 자동 생성/해제 |
