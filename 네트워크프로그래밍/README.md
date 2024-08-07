## 네트워크 프로그래밍
#### 파일 : chat01
### Open Chatting 구현
  
1. 프로그램 목적  

본 프로그램은 파이썬 소켓 통신을 이용하여 오픈채팅방을 구현한 것으로, 기본적으로 각 클라이언트들은 서버를 통해 데이터 브로드캐스트하며 메세지를 주고받을 수 있다.  메세지 포맷은 http 형식을 사용하며 요청메세지, 헤더, 바디 구조로 이루어져 있다. 
요청 메시지를 보낼때는 특정 메세지를 보내며 서버로부터 원하는 동작을 명시할 수 있다. 또한, 헤더는 요청 및 응답에 대한 추가 정보를 포함하고, 바디에는 실제 데이터가 들어간다. 이를 통해 네트워크 통신을 효율적으로 관리할 수 있다. 
프로그램의 구성은 서버와 클라이언트로 나뉘며 클라이언트는 채팅관리자와 유저로 이루어지게 된다.


2. 서비스 및 메세지 포맷

(1) 서버
- 클라이언트 채팅 브로드캐스트
- 상태메세지
  
(2) 채팅관리자 메세지 포맷 및 서비스
- 서비스 : 서버 종료하기, 특정 유저 강제로 내보내기. 이외는 유저 서비스와 동일
  
(3) 유저 메세지 포맷 및 서비스
- 서비스 : 채팅방 나가기, 채팅방 조용히 나가기


3. 흐름도
 <img width="620" alt="image" src="https://github.com/kye09/Projects/assets/136800080/77daa2d1-6f79-4cfd-9822-5bdf26281ac5">

(1) 서버가 먼저 실행된다.  
(2) 클라이언트가 입장하게 되면 클라이언트는 서버로 요청 메세지가 전송하며 [CONNECT] {유저이름}이 출력된다. 해당 유저는 서버의 user_list에 추가된다.  
(3) 클라이언트가 정상적으로 연결되어 채팅에 참여하게 되면 “{유저이름} 접속 완료”라는 메세지를 받게된다.   
(4) 유저가 채팅을 입력하게 되면 해당 메세지는 헤더와 바디가 encode되서 함께 서버로 전달되고, 서버에서 decode하여 서버에 해당 메세지가 출력되게 되고 다시 encode되어 다른 유저들에게 브로드캐스트 된다.   
(5) 채팅에 참여하고있는 유저가 “/종료” 메세지를 보내게되면 해당 클라이언트는 user_list에서 삭제되고 클라이언트 소켓이 닫히며 채팅이 종료된다.  
(6) 유저 이름이 “채팅 관리자”인 유저가 “/서버종료”를 입력하게되면 서버 소켓이 닫히게 되며 더 이상 유저끼리 채팅할 수 없게 되고 채팅이 종료 된다.   


4. 프로젝트 특징 & 장점

(1) 특징
- 채팅에는 5명의 유저가 입장할 수 있다.
- 클라이언트가 채팅을 보내면 메세지를 보낸 날짜와 시간이 유저 이름과 같이 출력된다
- “/종료”를 입력하면 해당 클라이언트는 유저 리스트에서 삭제되며 클라이언트 소켓이 닫히게되며 채팅에서 나갈 수 있다. 또한 채팅에서 나갔다는 메세지가 다른 클라이언트들에게 브로드캐스트 된다.
- “/조용히나가기”를 입력하면 채팅에서 나갈때 다른 클라이언트들에게 나갔다는 메세지가 브로드캐스트되지 않는다
- 클라이언트 이름이 채팅관리자면 “/서버종료”를 입력 시 서버소켓이 닫히며 채팅이 종료되게 된다.
- 클라이언트 이름이 채팅관리자면 “/kick {유저이름}”을 입력 시 해당 클라이언트는 user_list에서 삭제되며 클라이언트 소켓이 닫혀 채팅에서 강제 퇴장되게 된다.
- 클라이언트가 나가게되면 threading.Lock():을 걸고 user_list에서 삭제하고 클라이언트 소켓을 닫는다.
- 만약 서버가 클라이언트 소켓을 발견하지 못하면 "연결이 비 정상적으로 종료된 소켓이 있음”이라고 출력된다
- 만약 클라이언트 소켓이 닫힌 상태에서 해당 클라이언트가 메세지를 보내려고 시도하면 "메세지를 보낼수 없습니다. 다시 연결해주십시오”라는 메세지가 출력된다.

(2) 장점
- 채팅 내에 채팅 관리자가 있어 다른 유저 및 서버를 효율적으로 관리할 수 있다.  
- 여러가지 명령어를 통해 채팅을 통해 다양한 기능을 이용할 수 있다.  
- 클라이언트가 나갈때 threading.Lock():을 걸어 보다 안전하게 유저리스트에서 삭제하고, 소켓을 닫을 수 있다.  

5. 실행 방법  
- 경로설정  
cd /Users/kim-yeeun/Documents/taskpy/chat  
- 실행  
python3 server.py  
python3 client.py채팅관리자  
python3 client.py유저1  
