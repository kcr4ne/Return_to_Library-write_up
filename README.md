> 오늘은 /PWNABLE2/NX/RTL 경로에 있는 rtl_64를 풀어볼거다

## C 코드 뜯어보기
![](https://velog.velcdn.com/images/k_cr4ne/post/b9b69736-f238-48b2-bd3f-e899d640d643/image.png)

> 코드를 살펴보면 다음의 정보를 알 수 있다
1. 100 바이트 크기의 배열을 선언하였다
2. printf함수로 시스템 주소와 binsh를 출력한다
3. get로 buf에 값을 입력한다 (BoF 발생 가능)
이 정도의 정보만 알아보고 다음으로 넘어가겠다 (아래는 실행 결과)
![](https://velog.velcdn.com/images/k_cr4ne/post/f7ce3661-126d-4bd6-b999-049520321361/image.png)

## 익스플로잇 코드 작성
> ### 시스템 주소와 binsh 받아오기
![](https://velog.velcdn.com/images/k_cr4ne/post/b2bacddd-2b88-45d2-83dd-a01c2bb9766e/image.png)
- rtl_64를 실행하면 출력되는 시스템 주소와 binsh를 받아오기 위해 recvuntil로 "system : "과 "binsh : "를 넘기고 a1과 a2에 recv로 시스템 주소와 binsh를 받아온다.
### 버퍼 크기 찾기
크기를 구하기 위해 만능 이쁜이 gdb를 사용하자
-	bt 사용
![](https://velog.velcdn.com/images/k_cr4ne/post/9ec59550-81b8-4532-9562-7ba33a3081b0/image.png)
-	버퍼 값 찾기
![](https://velog.velcdn.com/images/k_cr4ne/post/c893704f-013d-4a24-968c-1ac4e3f01cb2/image.png)
136만큼 덮어쓰면 될것 같다
![](https://velog.velcdn.com/images/k_cr4ne/post/0ebda1e1-7f3e-492e-95ae-b44f880e1a08/image.png)

이제 이 문제를 풀 당시 배운 가젯을 써야한다
> ### 가젯 사용
![](https://velog.velcdn.com/images/k_cr4ne/post/495b9d6b-1694-4292-84da-2adb27a9e130/image.png)
**중요한 거**
저 가젯만을 사용해서 익스 코드를 작성하면 프로그램이 죽어요
StackAlignment 때문인데 이 친구(새기) 덕분에 스택의 top이 16의 배수로 되어 있어야만 프로그램이 정상작동한다 (효율 때문에 있다는 데 우리의 뇌는 생각해주지 않은 것 같다. 더러운 것들)
근데 오버 플로우를 발생시키면 저게 깨져버린다 (젠장)
그ㅡㅡㅡ래서 저걸 다시 맞추기 위해 가젯을 또 찾아야 한다
### 2차 가젯 탐방
 ROPgadget --binary rtl_64 | grep "ret"을 사용하면 더럽게 긴거가 나오는 데 여기서 순수 ret 귀족 혈통인 친구를 찾으면 된다
 ![](https://velog.velcdn.com/images/k_cr4ne/post/5b677427-4e04-447b-9b0e-7b9f965be703/image.png)
이 가젯들을 사용해 익스 코드를 마저 작성해보자
![](https://velog.velcdn.com/images/k_cr4ne/post/caa4af66-d64c-4757-a95d-abe157de5ff5/image.png)
- 0x0000000000400551와 p640x00000000004007a3을 패킹해서 페이로드에 넣고 binsh와 시스템 주소를 넣고 sendline을 통해서 보내버리자
![](https://velog.velcdn.com/images/k_cr4ne/post/d99fdd6d-7e54-441e-a786-3be34629602f/image.png)
성공적으로 작동했다

## 비하인드
> 브레이크 포인트를 걸기 전 화장실에 가버린 사람 (아래는 신경쓰지 말자)
![](https://velog.velcdn.com/images/k_cr4ne/post/97bb48f3-6818-4353-9a44-3f63a3d9f38e/image.png)

## 간단한 후기
![](https://velog.velcdn.com/images/k_cr4ne/post/73a90027-d3f9-4049-ac3f-de0bdbfc08df/image.png)

