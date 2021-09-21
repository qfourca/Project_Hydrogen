#define DEFAULT 0
#define FILENAMESIZE 128   // 파일 이름버퍼의 크기
#define PORT 80            //서버 포트
#define READTHREADSIZE 4   //입력 쓰레드 개수
#define SENDTHREADSIZE 1   //전송 쓰레드 개수
#define SENDFOLDER "send/" //전송 데이터들이 들어있는 폴더 이름
#define FOLDERLONG strlen(SENDFOLDER)

#define ERROR -1

#define LOGFOLDER "logs/"

#define STDERR 2
#define STDOUT 1
//연결 요청 메소드 매크로
#define UNKNOWN 0
#define GET 1
#define CONNECT 2
#define DELETE 3
#define POST 4
#define HEAD 5
#define OPCTIONS 6
#define PATCH 7
#define PUT 8
#define TRACE 9
#define CONNECTTION_REQUEST_MACOR_COUNT 10
//--------------------//
#define LOCALHOST 1
//printlog flags
#define THISTIME 0b00010000
#define NEXTLINETIME 0b00100000
#define BEFLINETIME 0b00110000
#define PRINTSTDOUT 0b00000001
#define PRINTSTDERR 0b00000010
