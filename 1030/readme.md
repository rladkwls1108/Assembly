# 🧩 Assembly Programming — Chapter 5: Procedures 요약

## 📘 개요

이 장에서는 어셈블리 언어에서의 프로시저(Procedure) 개념과
스택(Stack) 사용, 레지스터 보존, 인자 전달,
그리고 Irvine32 라이브러리의 주요 함수 사용법을 다룹니다.

---

## 1. Stack Operations (스택 동작 원리)

### 기본 개념

* 스택(Stack)은 LIFO(Last In, First Out) 구조의 메모리 영역이다.
* ESP(Extended Stack Pointer) 레지스터가 스택의 최상단을 가리킨다.
* 스택을 그릴 때는 위쪽이 낮은 주소, 아래쪽이 높은 주소이다.

### PUSH / POP 동작

* PUSH reg : ESP를 4 감소시키고 값을 스택에 저장
* POP reg : 스택의 값을 레지스터로 복사하고 ESP를 4 증가

예시:

```
push eax
pop  ebx
```

### PUSHFD / POPFD

* PUSHFD : 32비트 EFLAGS를 스택에 저장
* POPFD : 스택 값을 EFLAGS에 복원

### PUSHAD / POPAD

* PUSHAD : 모든 32비트 범용 레지스터(EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI)를 순서대로 저장
* POPAD : 반대 순서로 복원

---

## 2. Defining and Using Procedures

### 기본 개념

* PROC ~ ENDP 사이에 서브루틴(프로시저)을 정의한다.
* RET 명령은 스택의 반환 주소를 꺼내 호출 위치로 복귀한다.
* C, Java 등의 함수 개념과 동일하다.

### 인자 전달 방식

* 인자는 범용 레지스터(EAX, EBX, ECX 등)에 넣고 전달할 수 있다.

예시:

```
mov eax,10000h
mov ebx,20000h
mov ecx,30000h
call SumOf
```

---

## 3. ArraySum 예제

```
; ArraySum: 32비트 정수 배열의 합을 계산
; 입력: ESI = 배열 주소, ECX = 배열 크기
; 반환: EAX = 합계
ArraySum PROC
    push esi
    push ecx
    mov  eax,0
L1:
    add eax,[esi]
    add esi,TYPE DWORD
    loop L1
    pop ecx
    pop esi
    ret
ArraySum ENDP
```

테스트 코드:

```
mov esi,OFFSET array
mov ecx,LENGTHOF array
call ArraySum
mov theSum,eax
```

---

## 4. USES 지시어 (Register Preservation)

* USES는 프로시저 내에서 변경되는 레지스터를 명시하여 자동으로 PUSH/POP을 생성한다.

예시:

```
ArraySum PROC USES esi ecx
    mov eax,0
L1:
    add eax,[esi]
    add esi,TYPE DWORD
    loop L1
    ret
ArraySum ENDP
```

※ 단, 반환값을 담는 EAX는 PUSH/POP하지 않는다.

---

## 5. Linking to an External Library

* 라이브러리(LIB)는 미리 컴파일된 서브루틴 집합이다.
* kernel32.lib / kernel32.dll은 Windows의 핵심 시스템 함수 집합이다.
* 어셈블리에서도 이러한 DLL 내부 함수를 호출할 수 있다.

---

## 6. The Irvine32 Library

### 개요

* Windows용 어셈블리 학습을 위한 입출력 지원 라이브러리
* Irvine32.inc를 include 후 다양한 I/O 함수를 호출 가능
* WriteString, ReadInt, DumpRegs 등 제공

### 주요 함수

Clrscr – 콘솔 화면 초기화
Crlf – 줄바꿈
Delay – 지정 시간(ms) 지연
DumpRegs – 레지스터 상태 표시
DumpMem – 메모리 블록 출력
RandomRange – 난수 생성 (0~n-1)
WriteDec / WriteInt – 정수 출력
ReadInt / ReadString – 사용자 입력
SetTextColor – 콘솔 색상 설정
MsgBox, MsgBoxAsk – 팝업 메시지
WriteStackFrame – 현재 스택 프레임 출력

---

## 7. Irvine32 활용 예제

화면 지우고 500ms 대기 후 레지스터 상태 표시:

```
call Clrscr
mov eax,500
call Delay
call DumpRegs
```

문자열 출력:

```
.data
str1 BYTE "Assembly language is easy!",0
.code
mov edx,OFFSET str1
call WriteString
call Crlf
```

난수 출력:

```
mov ecx,10
L1:
    mov eax,100
    call RandomRange
    call WriteInt
    call Crlf
    loop L1
```

---

## 8. 콘솔 색상 출력 예시

```
.data
str1 BYTE "Color output is easy!",0
.code
mov eax,yellow + (blue * 16)
call SetTextColor
mov edx,OFFSET str1
call WriteString
call Crlf
```

→ 노란색 글자, 파란색 배경 출력

---

## 9. Integer I/O 종합 예제

```
mov edx,OFFSET prompt
call WriteString
call ReadInt
call WriteInt
call WriteHex
call WriteBin
```

---

## 10. 성능 측정 예제

```
call GetMSeconds
mov startTime,eax
; --- 루프 실행 ---
call GetMSeconds
sub eax,startTime
call WriteDec
```

GetMSeconds는 시스템 시작 후 경과한 시간을 밀리초 단위로 반환한다.

---

## Chapter Summary

* Stack: LIFO 구조, PUSH/POP 명령으로 데이터 저장/복원
* Procedure: PROC–ENDP로 정의, RET로 복귀
* Argument Passing: 레지스터를 이용한 인자 전달
* USES: 자동 PUSH/POP으로 레지스터 보존
* External Linking: kernel32.dll, Irvine32.lib 등 외부 호출
* Irvine32 Library: 초보자용 입출력 및 시스템 제어 함수 모음

