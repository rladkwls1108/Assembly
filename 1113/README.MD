# 7. Integer Arithmetic

## 1. Shift and Rotate Instructions (시프트 및 회전 명령어)

### 1.1 주요 명령어 종류
- **SHL** (Shift Left): 논리적 좌측 시프트, 최하위 비트에 0 삽입
- **SHR** (Shift Right): 논리적 우측 시프트, 최상위 비트에 0 삽입
- **SAL** (Shift Arithmetic Left): SHL과 동일
- **SAR** (Shift Arithmetic Right): 산술 우측 시프트, 부호 비트 유지
- **ROL** (Rotate Left): 좌측 회전, 비트 손실 없음
- **ROR** (Rotate Right): 우측 회전, 비트 손실 없음
- **RCL** (Rotate Carry Left): Carry 플래그 포함 좌측 회전
- **RCR** (Rotate Carry Right): Carry 플래그 포함 우측 회전
- **SHLD/SHRD** (Double Precision Shift): 이중 정밀도 시프트

### 1.2 활용 예시
- **비트 곱셈**: SHL을 사용한 2의 거듭제곱 곱셈
- **비트 나눗셈**: SHR을 사용한 2의 거듭제곱 나눗셈
- **비트 추출**: 파일 날짜 필드 추출 등
- **다중 바이트 시프트**: 배열의 비트를 한 번에 시프트

## 2. Multiplication and Division Instructions (곱셈 및 나눗셈 명령어)

### 2.1 MUL (Unsigned Multiply)
- 부호 없는 정수 곱셈
- 피승수와 승수는 같은 크기, 결과는 두 배 크기
- Carry 플래그로 상위 비트 오버플로우 확인

| 피승수 | 승수 | 결과 |
|--------|------|------|
| AL | reg/mem8 | AX |
| AX | reg/mem16 | DX:AX |
| EAX | reg/mem32 | EDX:EAX |

### 2.2 IMUL (Signed Multiply)
- 부호 있는 정수 곱셈
- 3가지 형식: 단일, 이중, 삼중 피연산자
- Overflow 플래그 확인 필수

### 2.3 DIV (Unsigned Divide)
- 부호 없는 정수 나눗셈
- 나눗셈 오버플로우 방지 중요 (제수가 0인지 확인)

| 피제수 | 제수 | 몫 | 나머지 |
|--------|------|-----|--------|
| AX | reg/mem8 | AL | AH |
| DX:AX | reg/mem16 | AX | DX |
| EDX:EAX | reg/mem32 | EAX | EDX |

### 2.4 IDIV (Signed Divide)
- 부호 있는 정수 나눗셈
- 부호 확장 명령어 필요: CBW, CWD, CDQ

### 2.5 부호 확장 명령어
- **CBW**: 바이트를 워드로 변환 (AL → AX)
- **CWD**: 워드를 더블워드로 변환 (AX → DX:AX)
- **CDQ**: 더블워드를 쿼드워드로 변환 (EAX → EDX:EAX)

## 3. Extended Addition and Subtraction (확장 덧셈 및 뺄셈)

### 3.1 ADC (Add with Carry)
- Carry 플래그를 포함한 덧셈
- 다중 바이트/워드 덧셈에 사용

### 3.2 SBB (Subtract with Borrow)
- Carry 플래그(빌림)를 포함한 뺄셈
- 다중 바이트/워드 뺄셈에 사용

## 4. ASCII and Unpacked Decimal Arithmetic (ASCII 및 언팩 십진 연산)

### 4.1 ASCII vs Unpacked Decimal
- **ASCII 형식**: 상위 4비트 = 0011b
- **Unpacked 형식**: 상위 4비트 = 0000b

### 4.2 조정 명령어
- **AAA** (ASCII Adjust After Addition): 덧셈 후 조정
- **AAS** (ASCII Adjust After Subtraction): 뺄셈 후 조정
- **AAM** (ASCII Adjust After Multiplication): 곱셈 후 조정
- **AAD** (ASCII Adjust Before Division): 나눗셈 전 조정

## 5. Packed Decimal Arithmetic (팩 십진 연산)

### 5.1 조정 명령어
- **DAA** (Decimal Adjust After Addition): 팩 십진 덧셈 후 조정
- **DAS** (Decimal Adjust After Subtraction): 팩 십진 뺄셈 후 조정

### 5.2 예시
```assembly
mov al, 35h
add al, 48h    ; AL = 7Dh
daa            ; AL = 83h (조정된 결과)
```

## 6. 주요 활용 예시

### 6.1 이진 곱셈 (비트 시프트 사용)
```assembly
EAX * 36 = EAX * (2^5 + 2^2)
         = (EAX * 32) + (EAX * 4)
```

### 6.2 산술 표현식 구현
```assembly
var4 = (var1 + var2) * var3;

mov eax, var1
add eax, var2
mul var3
jc tooBig         ; 오버플로우 검사
mov var4, eax
```

## 7. 중요 주의사항

1. **Carry/Overflow 플래그 확인**: MUL, IMUL 후 항상 확인
2. **나눗셈 오버플로우 방지**: 제수 0 검사, 64비트 피제수 사용 권장
3. **부호 확장**: IDIV 전 반드시 수행
4. **메모리 보호**: 코드 수정 시 VirtualProtect 사용
5. **Position-Independent Code**: 쉘코드 개발 시 필수


