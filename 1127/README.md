# Chapter 9: Strings and Arrays 요약

---

## 9.1 String Primitive Instructions

### 문자열 명령어 개요

| 명령어 | 설명 |
|--------|------|
| **MOVSB/W/D** | [ESI] → [EDI] 복사 |
| **CMPSB/W/D** | [ESI]와 [EDI] 비교 |
| **SCASB/W/D** | AL/AX/EAX와 [EDI] 비교 |
| **STOSB/W/D** | AL/AX/EAX → [EDI] 저장 |
| **LODSB/W/D** | [ESI] → AL/AX/EAX 로드 |

### Repeat Prefix

| 접두사 | 조건 |
|--------|------|
| **REP** | ECX > 0 |
| **REPE/REPZ** | ZF=1 AND ECX > 0 |
| **REPNE/REPNZ** | ZF=0 AND ECX > 0 |

### Direction Flag

| 명령 | 동작 |
|------|------|
| **CLD** | ESI/EDI 증가 (순방향) |
| **STD** | ESI/EDI 감소 (역방향) |

### 예제: 문자열 복사

```asm
cld                         ; 순방향
mov esi, OFFSET source
mov edi, OFFSET target
mov ecx, 10
rep movsb                   ; 10바이트 복사
```

### 예제: 문자 검색 (SCASB)

```asm
mov edi, OFFSET alpha
mov al, 'F'
mov ecx, LENGTHOF alpha
cld
repne scasb                 ; 다를 동안 반복
jnz not_found
dec edi                     ; 찾은 위치
```

---

## 9.2 Irvine32 String Procedures

| 프로시저 | 기능 |
|----------|------|
| **Str_compare** | 두 문자열 비교 (CF, ZF 설정) |
| **Str_length** | 문자열 길이 → EAX |
| **Str_copy** | source → target 복사 |
| **Str_trim** | 후행 문자 제거 |
| **Str_ucase** | 대문자 변환 |

```asm
INVOKE Str_length, ADDR myString    ; EAX = 길이
INVOKE Str_copy, ADDR src, ADDR dst
INVOKE Str_trim, ADDR str, '#'      ; '#' 제거
```

---

## 9.3 Two-Dimensional Arrays

### 메모리 배치

- **Row-Major**: 행 단위로 저장 (C, C++, Java)
- **Column-Major**: 열 단위로 저장 (Fortran)

### Base-Index Operand

```asm
mov ebx, OFFSET tableB
add ebx, RowSize * row_index
mov esi, column_index
mov al, [ebx + esi]
```

### Scale Factor (WORD/DWORD 배열)

```asm
mov ax, [ebx + esi*2]       ; WORD 배열
mov eax, [ebx + esi*4]      ; DWORD 배열
```

### Base-Index-Displacement

```asm
mov eax, tableD[ebx + esi*TYPE tableD]
```

---

## 9.4 Searching and Sorting

### Bubble Sort

```asm
BubbleSort PROC USES eax ecx esi,
    pArray:PTR DWORD, Count:DWORD
    
    mov ecx, Count
    dec ecx
L1: push ecx
    mov esi, pArray
L2: mov eax, [esi]
    cmp [esi+4], eax
    jg L3
    xchg eax, [esi+4]       ; 교환
    mov [esi], eax
L3: add esi, 4
    loop L2
    pop ecx
    loop L1
    ret
BubbleSort ENDP
```

### Binary Search

```asm
; first=0, last=count-1
; mid = (first + last) / 2
; values[mid] < searchVal → first = mid + 1
; values[mid] > searchVal → last = mid - 1
; values[mid] = searchVal → 찾음!
```

---

## 핵심 정리

| 개념 | 설명 |
|------|------|
| **ESI** | Source Index (소스 포인터) |
| **EDI** | Destination Index (대상 포인터) |
| **CLD/STD** | 방향 플래그 제어 |
| **REP** | ECX 기반 반복 |
| **[base+index*scale+disp]** | 2차원 배열 주소 계산 |
