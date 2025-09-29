# 📘 x86 Processor Architecture

## 1. General Concepts
- Intel이 개발한 **x86 아키텍처**는 CISC(Complex Instruction Set Computer) 구조를 기반으로 발전.
- 16비트 → 32비트 → 64비트로 확장되며 성능과 메모리 접근 범위가 증가.
- CPU는 **레지스터, 메모리, 입출력 장치**를 중심으로 동작.

---

## 2. 32-Bit x86 Processors
- **범용 레지스터 (32-bit)**
  - EAX, EBX, ECX, EDX, ESI, EDI, EBP, ESP
- **세그먼트 레지스터**
  - CS, DS, ES, FS, GS, SS
- **명령어 포인터**
  - EIP (현재 실행 중인 명령어 주소 저장)
- **플래그 레지스터**
  - EFLAGS → 조건 분기, 상태 플래그, 연산 결과 확인

---

## 3. 64-Bit x86-64 Processors
- **확장된 레지스터**
  - RAX, RBX, RCX, RDX, RSI, RDI, RBP, RSP  
  - 추가: R8 ~ R15
- **주소 공간**
  - 64비트 메모리 주소로 대용량 메모리 접근 가능
- **호환성**
  - 16비트/32비트 프로그램 실행 지원
- 보안 및 성능 향상을 위한 새로운 명령어 포함

---

## 4. Components of a Typical x86 Computer
- **Motherboard**: 모든 부품을 연결하는 중심
- **CPU & GPU**: 연산 및 그래픽 처리 담당
- **Main Memory (RAM)**: 실행 중인 데이터 저장
- **Storage (SSD/HDD)**: 영구적 데이터 저장 장치
- **I/O Devices**: 키보드, 마우스, 모니터 등 사용자 인터페이스 장치

---

## 5. Input-Output System
- **I/O 시스템**은 CPU ↔ 외부 장치 간 데이터 전송 담당
- **I/O 방식**
  - Memory-mapped I/O: 메모리 주소 일부를 장치 제어용으로 사용
  - Isolated I/O: 별도의 I/O 주소 공간 사용
- **인터럽트(Interrupt)**
  - 장치가 CPU에 서비스 요청 → 빠른 응답 가능

---

## 6. Chapter Summary
- x86 구조는 세대를 거쳐 발전하여 현재는 64비트 환경이 주류
- CPU, 메모리, I/O 장치가 컴퓨터 아키텍처의 핵심 요소
- 어셈블리 프로그래밍 학습에 있어 구조 이해가 필수

---

## 7. Review Questions & Exercises
### 발표/과제 주제 예시
- Motherboard
- CPU & GPU
- Main memory & SSD
- Keyboard, Mouse, Monitor
- PC building

---


