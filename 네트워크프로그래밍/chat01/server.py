from socket import *
import threading
import json
from datetime import datetime
import sys

port = 3000 

server_socket = socket(AF_INET, SOCK_STREAM) ## 소켓을 정의
server_socket.bind(('', port))               ## 서버가 정해진 포트번호로 지정된 소켓을 생성
server_socket.listen(5)                      ## 최대로 들어올 수 있는 소켓 갯수를 지정

user_list = {}                               ## 채팅 유저관리를 위한 딕셔너리
def receive(client_socket, addr, user):
    while 1:                      
        try:
            data = client_socket.recv(1024)      ## 클라이언트 소켓에서 데이터를 받아 옴
        except OSError as e:
            if "Bad file descriptor" in str(e):
                print(f"{user}과의 연결이 중단되었습니다.")
                break

        try:
            string = json.loads(data.decode())              ## 받아온 데이터는 비트로 인코딩 되있기 때문에 디코딩을 해줌 
        except:
            print("유저가 퇴장하였습니다.")
            break

        if string['body'] == "/종료" :      # client가 /종료 메세지를 보내면 종료                     
            msg =f'{string["header"]["user"]}가 퇴장하였습니다.'  
            d_user = user
            print(msg) 
            msg_header = {
               'user': d_user,
               'time': datetime.now().strftime("%Y-%m-%d %H:%M:%S"),      
            }
            msg_e={
                'header': msg_header,
                'body': msg
            }
            for con in user_list.values():
              if con != client_socket:             
                try:
                  con.sendall(json.dumps(msg_e).encode()) 
                except:
                  print("사용자가 없습니다")
            break 
            
        
        elif string['header']['user'] == "채팅관리자" and string['body'] == "/서버종료":    ## 채팅관리자가 /서버종료 메세지를 보내면 서버소켓 닫음
            msg = "서버가 종료되었습니다."
            for con in user_list.values():
                msg_header = {
                    'user': '서버',
                    'time': datetime.now().strftime("%Y-%m-%d %H:%M:%S")     
            }
                msg_e={
                    'header': msg_header,
                    'body': msg
            }
            for con in user_list.values():
                try:
                    con.sendall(json.dumps(msg_e).encode()) 
                    con.close()
                except:
                     print("연결이 비 정상적으로 종료된 소켓이 있음")
            print(msg)
            client_socket.close()
            server_socket.close()
            sys.exit() 
        
        elif string['header']['user'] == "채팅관리자" and string['body'].startswith("/kick "):   ## 채팅관리자가 /kick {유저이름}을 하면 강제퇴장
            # '/kick ' 다음에 오는 부분을 추출하여 해당 유저를 강제로 종료
            kicked_user = string['body'][6:]
            if kicked_user in user_list:
                kicked_socket = user_list[kicked_user]

                msg_header = {
               'user': '서버',
               'time': datetime.now().strftime("%Y-%m-%d %H:%M:%S"),      
            }
                msg_k={
                'header': msg_header,
                'body': '더 이상 채팅을 보낼 수 없습니다.'
            }             
                
                msg_o={
                'header': msg_header,
                'body': f"{kicked_user}가 퇴장하였습니다."
            }
                try:
                    for con in user_list.values():
                        if con != client_socket:             
                            try:
                                con.sendall(json.dumps(msg_o).encode()) 
                            except:
                                print("사용자가 없습니다")
                    kicked_socket.sendall(json.dumps(msg_k).encode())
                    kicked_socket.close()
                    
                except:
                    print("연결이 비 정상적으로 종료된 소켓이 있음")

                continue

        elif string['body'] == "/조용히나가기" :             ## client가 /조용히나가기 메세지를 보내면 종료 메세지가 브로드캐스트 X               
            msg =f'{string["header"]["user"]}가 퇴장하였습니다.'  # 오류해결
            print(msg) 
            break

        print(f"({string['header']['time']}) {string['header']['user']} : {string['body']}")

        for con in user_list.values():                    ## 채팅에 참여하고 있는 클라이언트들에게 받아온 메시지 전달
            if con != client_socket: # 보낸 클라이언트 빼고 브로드캐스트
             try:
                con.sendall(json.dumps(string).encode())           
             except:
                print("연결이 비 정상적으로 종료된 소켓이 있음")
    with threading.Lock():   
        del user_list[user]                                   ## 채팅서버를 나간 클라이언트는 딕셔너리에서 제거
        client_socket.close()                                 ## 클라이언트 소켓 제거

while True:
    try:
        client_socket, addr = server_socket.accept()          ## 클라이언트 소켓 정의
    except:
        break
    user_data = client_socket.recv(1024)                       ## 처음 클라이언트 소켓이 정의되고 난 후 처음 받는 데이터
    user_RM=user_data[:9].decode('utf-8')
    user= user_data[9:].decode('utf-8')                        ## 클라이언트는 채팅 유저의 이름을 보냄
    user_list[user] = client_socket                            ## 유저 리스트에 유저 추가
    print(f'{user_RM} {user}') 
       
    msg_header = {
               'user': '서버',
               'time': datetime.now().strftime("%Y-%m-%d %H:%M:%S"),      
            }
    msg_in={
                'header': msg_header,
                'body': f"{user}가 입장하였습니다."
            }             


    for con in user_list.values():                    ## 채팅에 참여하고 있는 클라이언트들에게 받아온 메시지 전달
            if con != client_socket:    # 보낸 클라이언트 빼고 브로드캐스트
             try:
                con.sendall(json.dumps(msg_in).encode())           
             except:
                print("연결이 비 정상적으로 종료된 소켓이 있음")         
              

    receive_thread = threading.Thread(target=receive, args=(client_socket, addr,user))
    ## 각각의 클라이언트 서버가 채팅을 따로 치기 위해 각 클라이언트로 부터 데이터를 받고 보내는 부분은 스레드로 정의
    receive_thread.start()