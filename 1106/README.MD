# 6. Conditional Processing

## 6.1 Boolean and Comparison Instructions

### CPU Status Flags
- **Zero Flag (ZF)**: 연산 결과가 0일 때 설정
- **Carry Flag (CF)**: 캐리 아웃 발생 시 설정
- **Sign Flag (SF)**: 피연산자의 최상위 비트 복사
- **Overflow Flag (OF)**: 부호 있는 범위 초과 시 설정
- **Parity Flag (PF)**: 1비트의 개수가 짝수일 때 설정

### 주요 명령어

#### AND 명령어
- 비트 마스킹에 사용
- 특정 비트를 클리어하면서 다른 비트는 유지
- OF와 CF를 항상 클리어, SF, ZF, PF 수정
- 예: 소문자를 대문자로 변환 (`and al, 11011111b`)

#### OR 명령어
- 특정 비트를 세트
- OF와 CF를 항상 클리어, SF, ZF, PF 수정

#### XOR 명령어
- 비트 토글 및 암호화에 사용
- 패리티 체크: `xor al, 0`
- OF와 CF를 항상 클리어, SF, ZF, PF 수정

#### NOT 명령어
- 모든 비트 반전 (1의 보수)
- 플래그에 영향 없음

#### TEST 명령어
- AND 연산 수행하지만 목적지 피연산자를 수정하지 않음
- 비트 테스팅에 사용
- OF와 CF를 항상 클리어, SF, ZF, PF 수정

#### CMP 명령어
- 묵시적 뺄셈 수행, 피연산자 수정 없음
- **부호 없는 비교**: ZF와 CF 사용
  - destination < source: ZF=0, CF=1
  - destination > source: ZF=0, CF=0
  - destination = source: ZF=1, CF=0
- **부호 있는 비교**: SF와 OF 사용
  - destination < source: SF ≠ OF
  - destination > source: SF = OF
  - destination = source: ZF=1

## 6.2 Conditional Jumps

### 조건부 점프의 종류

#### 1. Flag 값 기반 점프
- `JZ` (Jump if Zero): ZF=1
- `JNZ` (Jump if Not Zero): ZF=0
- `JC` (Jump if Carry): CF=1
- `JNC` (Jump if Not Carry): CF=0
- `JO` (Jump if Overflow): OF=1
- `JS` (Jump if Signed): SF=1
- `JP` (Jump if Parity): PF=1

#### 2. 동등성 비교 점프
- `JE` (Jump if Equal): ZF=1
- `JNE` (Jump if Not Equal): ZF=0
- `JCXZ`, `JECXZ`, `JRCXZ`: CX/ECX/RCX가 0일 때

#### 3. 부호 없는 비교 점프
- `JA` / `JNBE` (Jump if Above): CF=0 and ZF=0
- `JAE` / `JNB` (Jump if Above or Equal): CF=0
- `JB` / `JNAE` (Jump if Below): CF=1
- `JBE` / `JNA` (Jump if Below or Equal): CF=1 or ZF=1

#### 4. 부호 있는 비교 점프
- `JG` / `JNLE` (Jump if Greater): ZF=0 and SF=OF
- `JGE` / `JNL` (Jump if Greater or Equal): SF=OF
- `JL` / `JNGE` (Jump if Less): SF≠OF
- `JLE` / `JNG` (Jump if Less or Equal): ZF=1 or SF≠OF

## 6.3 Conditional Loop Instructions

### LOOPZ / LOOPE
- ECX를 감소시키고 ECX>0 **AND** ZF=1일 때 점프

### LOOPNZ / LOOPNE
- ECX를 감소시키고 ECX>0 **AND** ZF=0일 때 점프

## 6.4 Conditional Structures

### Block-Structured IF Statements
```assembly
; if (op1 == op2) { X=1; Y=2; }
    mov eax, op1
    cmp eax, op2
    jne L1          ; op1 ≠ op2이면 건너뜀
    mov X, 1
    mov Y, 2
L1:
```

### Compound Expressions

#### Logical AND
```assembly
; if (al > bl) AND (bl > cl) X=1
    cmp al, bl
    ja L1
    jmp next
L1: cmp bl, cl
    ja L2
    jmp next
L2: mov X, 1
next:
```

#### Logical OR (Short-circuit)
```assembly
; if (al > bl) OR (bl > cl) X=1
    cmp al, bl
    ja L1           ; 첫 조건이 참이면 바로 실행
    cmp bl, cl
    jbe next        ; 두 조건 모두 거짓
L1: mov X, 1
next:
```

### WHILE Loops
```assembly
; while (val1 < val2) { val1++; val2--; }
    mov eax, val1
beginwhile:
    cmp eax, val2
    jnl endwhile
    inc eax
    dec val2
    jmp beginwhile
endwhile:
    mov val1, eax
```

### Table-Driven Selection
- 다중 분기 구조를 테이블 룩업으로 대체
- 룩업 값과 프로시저 오프셋을 포함하는 테이블 생성
- 간접 프로시저 호출 사용

## 6.5 Conditional Control Flow Directives (32-bit 전용)

### High-Level Directives
- `.IF condition ... .ENDIF`
- `.IF ... .ELSE ... .ENDIF`
- `.IF ... .ELSEIF ... .ELSE ... .ENDIF`
- `.WHILE condition ... .ENDW`
- `.REPEAT ... .UNTIL condition`

### 관계 연산자
- `==`, `!=`, `>`, `>=`, `<`, `<=`
- `&&` (logical AND), `||` (logical OR)
- `&` (bitwise AND)
- `CARRY?`, `OVERFLOW?`, `PARITY?`, `SIGN?`, `ZERO?`

### 예제
```assembly
.data
val1 DWORD 5
result DWORD ?
.code
mov eax, 6
.IF eax > val1
    mov result, 1
.ENDIF
```

이 코드는 다음과 같이 변환됨:
```assembly
mov eax, 6
cmp eax, val1
jbe @C0001
mov result, 1
@C0001:
```

## 주요 응용

### 1. 배열 검색
- 첫 번째 0이 아닌 값 찾기
- 조건 루프와 점프 조합 사용

### 2. 문자열 암호화
- XOR 연산으로 간단한 암호화/복호화 구현
- 동일한 키로 두 번 XOR하면 원래 값 복원

### 3. 상태 비트 테스팅
- TEST 명령어로 특정 비트 확인
- 여러 비트를 AND로 마스킹하여 동시 테스트
                 
