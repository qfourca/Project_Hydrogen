#include "Defines/Defines.h"
#include "Defines/ErrorDefines.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>

class Data
{
private:
    char filename[128];
    void inputTimes();

public:
    int requestMethod(); //연결 요청 메소드를 분석해 정수형으로 반환해주는 함수
    char *fileName();    //파일 이름을 분석해 _request_file에 넣어주는 함수 반환값:파일 이름의 길이
    char _recived_data[BUFSIZ];
    char _send_hearder[BUFSIZ];
};
