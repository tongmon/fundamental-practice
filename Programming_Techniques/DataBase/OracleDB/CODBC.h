#include <windows.h>
#include <iostream>
#include <sqlext.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <atlconv.h>

using namespace std;

// 201663021 이경준 

struct DB_Table // 데이터베이스 결과는 테이블이기에 테이블 자료형을 따로 선언
{
    int index = 0;
    vector<wstring> Attribute; // 속성
    vector<vector<wstring>> Tuples; // 레코드

    void PrintTable(vector<wstring> &ptitle) // 테이블 출력
    {
        for (int i = 0; i < 5 && index + i < Tuples.size(); i++) {
            PrintRecord(ptitle, index + i);
            wcout << L"\n";
        }
    }

    void NextPage() // 레코드 5개 앞으로
    {
        if (Tuples.size() <= 5)
            return;
        index = min(index + 5, Tuples.size() - 5);
    }

    void PrevPage() // 레코드 5개 뒤로
    {
        index = max(0, index - 5);
    }

    void PrintRecord(vector<wstring>& ptitle, int n) // 레코드 하나 출력
    {
        for (int i = 0; i < ptitle.size(); i++) {
            wcout << ptitle[i] << L": " << Tuples[n][i] << L"\n";
        }
    }
};

static wstring wstrconv(const string& src)
{
    USES_CONVERSION;
    return wstring(A2W(src.c_str()));
};

class CODBC // ODBC와 C++ 연동 클래스
{

    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    SQLRETURN retcode;

    // 특정 에러 처리
    SQLSMALLINT length;
    SQLINTEGER rec = 0, native;
    SQLWCHAR state[7], message[256];

    // 버퍼 크기
    SQLLEN mMaxBufferSize;

public:
    CODBC();
    ~CODBC();
    void AllocateHandles(); // 핸들 변수 초기화
    int ConnectDataSource(SQLWCHAR* DSN_name, SQLWCHAR* User_name, SQLWCHAR* Passwd); // 연결할 DBMS에 접속
    int ExecuteStatementDirect(SQLWCHAR* sql); // 쿼리문 바로 실행
    int PrepareStatement(SQLWCHAR* sql); // 쿼리문 준비
    int ExecuteStatement(); // 준비된 쿼리문 실행
    void DisconnectDataSource(); // 핸들 모두 해제
    int PrintTable(int Degree, wstring title = L"Table Data Below"); // 속성 개수 넣어주면 테이블 반환
    int GetTableData(DB_Table& tableData); // 테이블 데이터 획득 함수
};