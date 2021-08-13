#include "DataClass.h"
std::vector<Error> Data::errors;

int Data::processRequestMethod()
{
    char method[20];
    for (working_idx = 0; _recived_data[working_idx] != '/' && _recived_data[working_idx] != ' '; working_idx++)
    {
    }
    if (!strncmp(method, "GET", working_idx))
        return GET;
    else if (!strncmp(method, "CONNECT", working_idx))
        return CONNECT;
    else if (!strncmp(method, "DELETE", working_idx))
        return DELETE;
    else if (!strncmp(method, "POST", working_idx))
        return POST;
    else if (!strncmp(method, "HEAD", working_idx))
        return HEAD;
    else if (!strncmp(method, "OPCTIONS", working_idx))
        return OPCTIONS;
    else if (!strncmp(method, "PATCH", working_idx))
        return PATCH;
    else if (!strncmp(method, "PUT", working_idx))
        return PUT;
    else if (!strncmp(method, "TRACE", working_idx))
        return TRACE;
    else //알 수 없는 데이터 일시
    {
        Error error;
        error._codeName = UNKNOWM_METHOD;
        int error_long = strlen(method);
        if (error_long > ERROR_BUF)
        {
            for (int i = ERROR_BUF - 1; i > ERROR_BUF - 4; i--)
                error._contents[i] = '.';
            error_long = ERROR_BUF - 3;
        } //에러가 너무 긴 경우
        strncpy(error._contents, method, error_long);
        error.inputTimes();
        errors.push_back(error);
        return UNKNOWN;
    }
}
int Data::processFileName()
{
    for (; _recived_data[working_idx] != '/'; working_idx++)
    {
    }              // /를 건너뛰기
    working_idx++; //그 다음 인덱스
    if (_recived_data[working_idx] == ' ')
    {
        _request_file[0] = 0;
        return -1;
    } //아무것도 요청한 파일이 없을 시
    else
    {
        strcpy(_request_file, SENDFOLDER); //앞에 폴더의 경로 붙이기
        int i;
        for (i = strlen(SENDFOLDER); _recived_data[working_idx] != ' '; working_idx++)
        {
            _request_file[i] = _recived_data[working_idx];
            i++;
        }
        return i - strlen(SENDFOLDER); //파일 이름의 길이 반환
    }
}
void Error::inputTimes()
{
    time_t curTime = time(NULL);
    struct tm *thistime = localtime(&curTime);
    hour = thistime->tm_hour;
    min = thistime->tm_min;
}

int Data::processData()
{
    _request_method = processRequestMethod();
    processFileName();
    return 0;
}