# 10. Structures and Macros

## 개요

**구조체(Structure)**는 논리적으로 관련된 변수들의 그룹에 주어지는 템플릿 또는 패턴이다.
- 구조체 내의 변수들을 **필드(fields)**라고 한다
- 프로그램에서 구조체를 단일 엔티티로 접근하거나, 개별 필드에 접근할 수 있다
- 구조체는 종종 서로 다른 타입의 필드들을 포함한다

**유니온(Union)**도 여러 식별자를 그룹화하지만, 식별자들이 메모리의 **같은 영역을 공유**한다.

---

## 10.1.1 구조체 정의 (Defining Structures)

구조체는 `STRUCT`와 `ENDS` 지시어를 사용하여 정의한다.

```asm
name STRUCT
    field-declarations
name ENDS
```

### COORD 구조체 예제

Windows API에 정의된 COORD 구조체는 X, Y 화면 좌표를 나타낸다.

```asm
COORD STRUCT
    X WORD ?        ; offset 00
    Y WORD ?        ; offset 02
COORD ENDS
```

---

## 필드 초기화 (Field Initializers)

| 초기화 방식 | 설명 |
|------------|------|
| **Undefined (?)** | `?` 연산자는 필드 내용을 미정의 상태로 둔다 |
| **String literals** | 따옴표로 묶인 문자열 |
| **Integers** | 정수 상수와 정수 표현식 |
| **Arrays** | `DUP` 연산자로 배열 요소를 초기화 |

### Employee 구조체 예제

```asm
Employee STRUCT
    IdNum        BYTE "000000000"
    LastName     BYTE 30 DUP(0)
    Years        WORD 0
    SalaryHistory DWORD 0,0,0,0
Employee ENDS
```

**메모리 레이아웃:**

| IdNum | LastName | Years | SalaryHistory |
|-------|----------|-------|---------------|
| "000000000" | (null) | 0 | 0, 0, 0, 0 |

---

## 구조체 필드 정렬 (Aligning Structure Fields)

최적의 메모리 I/O 성능을 위해 구조체 멤버는 해당 데이터 타입에 맞는 주소로 정렬되어야 한다. 그렇지 않으면 CPU가 멤버에 접근하는 데 더 많은 시간이 필요하다.

### ALIGN 지시어 사용

```asm
ALIGN datatype

Employee STRUCT
    IdNum        BYTE "000000000"    ; 9 bytes
    LastName     BYTE 30 DUP(0)      ; 30 bytes
    ALIGN        WORD                ; 1 byte added (패딩)
    Years        WORD 0              ; 2 bytes
    ALIGN        DWORD               ; 2 bytes added (패딩)
    SalaryHistory DWORD 0,0,0,0      ; 16 bytes
Employee ENDS                        ; 60 total
```

### 정렬 규칙 (Table 10-1)

| Member Type | Alignment |
|-------------|-----------|
| BYTE, SBYTE | 8-bit (byte) boundary |
| WORD, SWORD | 16-bit (word) boundary |
| DWORD, SDWORD | 32-bit (doubleword) boundary |
| QWORD | 64-bit (quadword) boundary |
| REAL4 | 32-bit (doubleword) boundary |
| REAL8 | 64-bit (quadword) boundary |
| structure | Largest alignment requirement of any member |
| union | Alignment requirement of the first member |

---

## 10.1.2 구조체 변수 선언 (Declaring Structure Variables)

구조체 변수는 선언과 동시에 특정 값으로 초기화할 수 있다.

### 문법

```asm
identifier structureType < initializer-list >
                         initializer [, initializer] . . .
```

빈 꺾쇠 괄호 `< >`를 사용하면 구조체 정의의 기본 필드 값을 사용한다.

### 예제

```asm
.data
point1 COORD <5,10>              ; X = 5, Y = 10
point2 COORD <20>                ; X = 20, Y = ?
point3 COORD <>                  ; X = ?, Y = ? (기본값)
worker Employee <>               ; (default initializers)
```

### 선택적 필드 초기화

특정 필드만 오버라이드하는 것이 가능하다.

```asm
person1 Employee <"555223333">           ; IdNum만 초기화
person2 Employee {"555223333"}           ; 중괄호도 사용 가능
person3 Employee <,"dJones">             ; LastName만 초기화
person4 Employee <,,,2 DUP(20000)>       ; SalaryHistory만 초기화
```

---

## 요약

| 항목 | 설명 |
|------|------|
| 구조체 정의 | `STRUCT` ... `ENDS` |
| 필드 초기화 | `?`, 문자열, 정수, `DUP()` |
| 정렬 | `ALIGN` 지시어로 성능 최적화 |
| 변수 선언 | `< >` 또는 `{ }`로 초기화 |
| 선택적 초기화 | 콤마로 필드 건너뛰기 가능 |
