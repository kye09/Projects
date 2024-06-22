# Simple server
# 클라이언트가 연결 요청하면 서버가 클라이언트에게 문자열 전송 후 
# 연결 종료
import socket
BUFSIZE = 1024
HOST = '127.0.0.1'
PORT = 5000
ADDR = (HOST, PORT)

# 소켓 생성 --> 생성한 소켓은 변수 s로 처리
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(ADDR)
#s.bind(('127.0.0.1', 5000))
s.listen(5)
print(f"waiting")

while True:
    clientsocket, address = s.accept()
    print(f"Connection from {address} has been established")
    while True:   #client 와 대화
        data = clientsocket.recv(BUFSIZE)
        msg = data.decode()
        print('received data:', msg)
        if msg == 'exit':
            break
        clientsocket.sendall(data)
    clientsocket.close()


s.close()
print('complete!')