# 5.8.2 Algorithm Workbench

---

### 1. Write a sequence of statements that use only PUSH and POP instructions to exchange the
values in the EAX and EBX registers (or RAX and RBX in 64-bit mode).

**정답 (PUSH/POP만 사용한 교환):**
```asm
; 32-bit
push eax
push ebx
pop  eax        ; eax ← (old ebx)
pop  ebx        ; ebx ← (old eax)

; 64-bit
push rax
push rbx
pop  rax        ; rax ← (old rbx)
pop  rbx        ; rbx ← (old rax)
````

---

### 2. Suppose you wanted a subroutine to return to an address that was 3 bytes higher in memory

than the return address currently on the stack. Write a sequence of instructions that would be
inserted just before the subroutine’s RET instruction that accomplish this task.

**정답 (스택의 반환 주소를 +3 증가):**

```asm
; 32-bit: [esp]에 있는 반환 주소를 직접 수정
add dword ptr [esp], 3
ret

; 64-bit: [rsp]의 반환 주소 수정
add qword ptr [rsp], 3
ret
```

---

### 3. Functions in high-level languages often declare local variables just below the return address

on the stack. Write an instruction that you could put at the beginning of an assembly language
subroutine that would reserve space for two integer doubleword variables. Then, assign the
values 1000h and 2000h to the two local variables.

**정답 (두 개의 로컬 DWORD 확보 및 초기화):**

```asm
; 32-bit: 서브루틴 시작부
sub  esp, 8                 ; 두 개의 DWORD 로컬 변수 확보
mov  dword ptr [esp],  1000h
mov  dword ptr [esp+4],2000h

; 64-bit: 동일 개념(필요시 16바이트 정렬 고려)
sub  rsp, 8                 ; 두 개의 DWORD 로컬 변수 확보
mov  dword ptr [rsp],  1000h
mov  dword ptr [rsp+4],2000h
; (호출 규약에 따라 추가 정렬이 필요하면 sub rsp,16 등으로 조정)
```

---

### 4. Write a sequence of statements using indexed addressing that copies an element in a double

word array to the previous position in the same array.

**정답 (더블워드 배열의 i번째 요소를 i-1번째로 복사):**

* **인덱스가 바이트 오프셋(= 요소 크기 반영됨)인 경우:**

```asm
; ESI = 바이트 오프셋, array는 DWORD 배열
mov eax, [array + esi]      ; eax ← array[i]
mov [array + esi - 4], eax  ; array[i-1] ← eax
```

* **인덱스가 요소 인덱스(0,1,2,...)인 경우:**

```asm
; ESI = 요소 인덱스, 각 요소 크기 4바이트
mov   eax, [array + esi*4]  ; eax ← array[i]
lea   edx, [esi-1]
mov   [array + edx*4], eax  ; array[i-1] ← eax
```

(64비트도 동일 개념으로 `rsi`, `rdx` 사용 가능)

---

### 5. Write a sequence of statements that display a subroutine’s return address. Be sure that what

ever modifications you make to the stack do not prevent the subroutine from returning to its
caller.

**정답 (스택을 보존하며 반환 주소를 표시):**

* **스택을 전혀 변형하지 않고 읽기만 하는 방법(표시 루틴이 레지스터로 받는 경우):**

```asm
; 32-bit
mov eax, [esp]      ; eax ← 반환 주소
; 여기서 eax를 화면 출력 루틴에 전달(구현 의존)

; 64-bit
mov rax, [rsp]      ; rax ← 반환 주소
; rax를 출력 루틴에 전달(구현 의존)
```

* **출력 함수가 인자를 스택으로 받는 경우(반환에 영향 없도록 원본을 복제해 전달):**

```asm
; 32-bit (예: WriteHex 같은 출력 함수가 있다고 가정)
push dword ptr [esp]    ; 반환 주소를 복제하여 인자로 푸시
call WriteHex           ; 주소 표시
add  esp, 4             ; 인자 정리 (원본 반환 주소는 그대로 보존됨)
; ...
ret

; 64-bit (시演용: 가변 규약/ABI에 맞춰 인자 전달 방식 조정)
push qword ptr [rsp]    ; 반환 주소 복제
call PrintAddr          ; 주소 표시
add  rsp, 8             ; 정리
; ...
ret
```
---
