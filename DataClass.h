#include "Defines/Defines.h"
#include "Defines/ErrorDefines.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>
class Error
{
public:
    void inputTimes();
    char _contents[ERROR_BUF];
    int _codeName;
    int min;
    int hour;
};
struct History
{
    long long int _method_history[CONNECTTION_REQUEST_MACOR_COUNT];
};

class Data
{
private:
    int working_idx = 0;        //현재 작업중인 인덱스
    int processRequestMethod(); //연결 요청 메소드를 분석해 정수형으로 반환해주는 함수
    int processFileName();      //파일 이름을 분석해 _request_file에 넣어주는 함수 반환값:파일 이름의 길이
    void inputTimes();
    int processData();
    int processHeader();

    int _request_method;

public:
    char _recived_data[BUFSIZ];
    char _send_hearder[BUFSIZ];
    char _request_file[FILENAMESIZE];
    bool _isFilename_folder = true;

    int process();

    static std::vector<Error> errors;
};
