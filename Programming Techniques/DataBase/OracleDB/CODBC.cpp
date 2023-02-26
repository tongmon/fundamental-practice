#include "CODBC.h"

CODBC::CODBC()
{
    mMaxBufferSize = 5000;
}

CODBC::~CODBC()
{

}

void CODBC::AllocateHandles() 
{
    wostringstream outs;
    outs.precision(6);

    // 환경 핸들러 할당
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        // ODBC 드라이버 버전 명시
        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            // 연결 핸들러 할당
            retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                outs << L"핸들 할당 성공...\n";
            }
            else {
                SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);
                outs << state << " : " << rec << " : " << native << " : " << message << "\n";
            }
        }
        else {
            SQLGetDiagRec(SQL_HANDLE_ENV, henv, ++rec, state, &native, message, sizeof(message), &length);
            outs << state << " : " << rec << " : " << native << " : " << message << "\n";
        }
    }
    else {
        SQLGetDiagRec(SQL_HANDLE_ENV, henv, rec, state, &native, message, sizeof(message), &length);
        outs << state << " : " << rec << " : " << native << " : " << message << "\n";
    }
    wcout << outs.str();
}

int CODBC::ConnectDataSource(SQLWCHAR* DSN_name, SQLWCHAR* User_name, SQLWCHAR* Passwd) 
{
    retcode = SQLConnect(hdbc, DSN_name, SQL_NTS, User_name, SQL_NTS, Passwd, SQL_NTS);
    if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) // 연결 실패시
    {
        wcout << L"데이터베이스 연결 실패...\n";
        return !SQL_SUCCESS;
    }
    wcout << L"데이터베이스 연결 성공...\n";
    return SQL_SUCCESS;
}

int CODBC::ExecuteStatementDirect(SQLWCHAR* sql) 
{
    wostringstream outs;
    outs.precision(6);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    }
    else {
        SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);
        outs << state << " : " << rec << " : " << native << " : " << message << "\n";
    }
    retcode = SQLExecDirect(hstmt, sql, SQL_NTS);
    if (retcode == SQL_SUCCESS) {
        return retcode;
    }
    SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, ++rec, state, &native, message, sizeof(message), &length);
    outs << state << " : " << rec << " : " << native << " : " << message << "\n";
    wcout << outs.str();
    return retcode;
}

int CODBC::PrepareStatement(SQLWCHAR* sql) 
{
    wostringstream outs;
    outs.precision(6);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    }
    else {
        SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);
    }
    retcode = SQLPrepare(hstmt, sql, SQL_NTS);
    if (retcode == SQL_SUCCESS) {
        return retcode;
    }
    SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, ++rec, state, &native, message, sizeof(message), &length);
    return retcode;
}

int CODBC::ExecuteStatement() 
{
    wostringstream outs;
    outs.precision(6);

    retcode = SQLExecute(hstmt);
    if (retcode == SQL_SUCCESS) {
        return retcode;
    }
    SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, ++rec, state, &native, message, sizeof(message), &length);
    return retcode;
}

int CODBC::PrintTable(int Degree, wstring title)
{
    wostringstream outs;
    outs.precision(6);

    vector<string> Attribute(Degree);
    SQLLEN Len = 0;

    for (int i = 0; i < Degree; i++) {
        SQLBindCol(hstmt, i + 1, SQL_C_CHAR, &Attribute[i][0], mMaxBufferSize, &Len);
    }

    outs << title << "\n";

    while (true) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_NO_DATA)
            break;
        for (int i = 0; i < Degree; i++) {
            if (Attribute[i][0] == '\0') {
                outs << L"null\t\t";
            }
            else {
                outs << Attribute[i].c_str() << "\t\t";
            }
        }
        outs << "\n";
    }
    if (!outs.str().length()) {
        SQLFreeStmt(hstmt, SQL_UNBIND);
        return -1;
    }
    wcout << outs.str();
    SQLFreeStmt(hstmt, SQL_UNBIND);
    return 1;
}

int CODBC::GetTableData(DB_Table& tableData)
{
    vector<wstring> Zero;
    SQLWCHAR colName[256];
    SQLLEN Len = 0, displaySize = 0;
    SQLULEN colLen = 0;
    SQLSMALLINT Degree = 0, colnameLen = 0, colType = 0, decimalDigits = 0, nullAble = 0;
    retcode = SQLNumResultCols(hstmt, &Degree);

    tableData.Attribute.clear();
    tableData.Tuples.clear();
    SQLCHAR Data[128][512];
    tableData.Attribute.clear();
    tableData.Attribute.resize(Degree);

    for (int i = 0; i < Degree; i++) {
        SQLDescribeCol(hstmt, i + 1, colName, sizeof(colName), &colnameLen, &colType, &colLen, &decimalDigits, &nullAble);
        SQLColAttribute(hstmt, i + 1, SQL_COLUMN_DISPLAY_SIZE, NULL, 0, NULL, &displaySize);
        colLen = colLen > displaySize ? displaySize + 1 : colLen + 1;
        
        tableData.Attribute[i].resize(colLen);
        for (int j = 0; j < colLen; j++) {
            tableData.Attribute[i][j] = colName[j];
        }

        SQLBindCol(hstmt, i + 1, SQL_C_CHAR, Data[i], mMaxBufferSize, &Len);
    }

    while (true) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_NO_DATA)
            break;
        tableData.Tuples.push_back(Zero); // 튜플 초기화
        for (int i = 0; i < Degree; i++) {
            string buf;
            int k = 0;
            while (Data[i][k] != '\0') {
                buf += Data[i][k];
                k++;
            }
            tableData.Tuples.back().push_back(wstrconv(buf)); // 튜플에 데이터 추가
        }
    }
    if (tableData.Tuples.empty()) {
        SQLFreeStmt(hstmt, SQL_UNBIND);
        return -1;
    }
    SQLFreeStmt(hstmt, SQL_UNBIND);
    return 1;
}

void CODBC::DisconnectDataSource() 
{
    if (hstmt) {
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        hstmt = NULL;
    }
    SQLDisconnect(hdbc);
    if (hdbc) {
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
        hdbc = NULL;
    }
    if (henv) {
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
        henv = NULL;
    }
    wcout << L"데이터베이스 연결 해제...\n" << endl;
}
