#include "CODBC.h"
#include <conio.h>
#include <ctime>
using namespace std;

#pragma warning( disable : 4996 )

// 201663021 이경준 
// 농수산물 이력제 데이터베이스 C++ 연동
// x64 비트에서 작동합니다.

#define DNS_name L"trace_DB" // ODBC와 연동할 데이터베이스
#define User_name L"lee" // 데이터베이스 컨트롤할 계정
#define Password L"1213" // 데이터베이스 컨트롤할 계정 비밀번호

wstring GetCurTime(bool keytime = false) // 현재 시각을 획득하는 함수
{
    wstring result;
    time_t timer;
    struct tm* t;
    timer = time(NULL);
    t = localtime(&timer);
    // keytime 체크 유무에 따라 다른 형식 반환하게 구현
    if (keytime)
    {
        result += to_wstring(t->tm_year + 1900);
        wstring buf = to_wstring(t->tm_mon + 1);
        if (buf.length() == 1) buf.insert(buf.begin(), L'0');
        result += buf;
        buf = to_wstring(t->tm_mday);
        if (buf.length() == 1) buf.insert(buf.begin(), L'0');
        result += buf;
        return result;
    }
    result += to_wstring(t->tm_year + 1900); result += L"-";
    result += to_wstring(t->tm_mon + 1); result += L"-";
    result += to_wstring(t->tm_mday); result += L" ";
    result += to_wstring(t->tm_hour); result += L":";
    result += to_wstring(t->tm_min); result += L":";
    result += to_wstring(t->tm_sec);
    return result;
}

wstring GetPW() // 비밀번호 보안성 향상을 위해 * 표시로 입력 받는 함수
{
    wstring PW;
    int index = 0;
    char chpw[256];
    while (true) // 엔터 전까지 무한 반복
    {
        chpw[index] = _getch(); // 한 글자씩 비밀번호 입력
        if (chpw[index] != '\r') {
            if (chpw[index] == 8) {
                if (index > 0) {
                    cout << "\b \b";
                    index--;
                }
            }
            else {
                index++;
                cout << "*";
            }
        }
        else {
            chpw[index] = '\0';
            break;
        }
    }
    int i = 0;
    while (chpw[i] != '\0') {
        PW += (wchar_t)chpw[i++];
    }
    return PW;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    setlocale(LC_ALL, "");

    CODBC DB;
    DB.AllocateHandles();

    // DB 연결 안되면 프로그램 종료
    if (DB.ConnectDataSource((SQLWCHAR*)DNS_name, (SQLWCHAR*)User_name, (SQLWCHAR*)Password) != SQL_SUCCESS) {
        return 1;
    }

    DB_Table tableData;
    wstring Stance = L"Init", ID_Input, PW_Input, sql;
    while (true) {
        system("cls");
        if (Stance == L"Init") {
            wcout << L"Made by 201663021 이경준\n농축수산물 이력제 시스템에 오신것을 환영합니다.\n";
            wcout << L"1. 소비자 민원\n2. 로그인\n3. 제작자\n4. 종료\n입력: ";
            wstring A;
            wcin >> A;
            if (stoi(A) == 1) {
                Stance = L"Customer_Init";
            }
            else if (stoi(A) == 2) {
                Stance = L"Login";
            }
            else if (stoi(A) == 3) {
                Stance = L"Dev_Show";
            }
            else {
                Stance = L"Exit";
            }
        }

        // 제작자 설명
        else if (Stance == L"Dev_Show") {
            wcout << L"안양대학교 컴퓨터공학과 4학년 201663021 이경준 제작\n";
            wcout << L"농수산물 이력제 정보가 담긴 오라클 데이터베이스를 ODBC를 통해 C++과 연동했습니다.\n";
            wcout << L"인터페이스는 콘솔창 형식으로 제공됩니다.\n";
            wcout << L"사용자, 유통자, 판매자, 생산자, 관리자에 따라 다른 권한이 주어집니다.\n";
            wcout << L"로그인을 통해 인증받고 서비스를 이용하세요.";
            Sleep(5000);
            Stance = L"Init";
        }

        // 로그인 상태
        else if (Stance == L"Login") {
            wcout << L"아이디와 비밀번호를 입력해주세요.\n";
            wcout << L"ID: ";
            wcin >> ID_Input;
            wcout << L"PW: ";
            PW_Input = GetPW();

            sql = L"select acc_pw from accout where acc_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            if (tableData.Tuples.empty() || tableData.Tuples[0][0] != PW_Input) {
                wcout << L"\n알 수 없는 ID 또는 비밀번호입니다.\n다시 입력해 주세요.";
                Sleep(1500);
                continue;
            }

            if (ID_Input[0] == L'P') {
                Stance = L"Producer_Init";
            }
            else if (ID_Input[0] == L'W') {
                Stance = L"Wholesaler_Init";
            }
            else if (ID_Input[0] == L'R') {
                Stance = L"Seller_Init";
            }
            else if (ID_Input[0] == L'A') {
                Stance = L"Admin_Init";
            }
        }

        // 고객 메뉴
        else if (Stance == L"Customer_Init") {
            wcout << L"농축수산물 이력제 시스템입니다. 원하시는 기능을 선택해주세요.\n";
            wcout << L"1. 제품 이력조회\n2. 제품 문제 신고\n3. 로그아웃\n입력: ";
            wstring Input;
            wcin >> Input;

            if (stoi(Input) == 1) {
                Stance = L"Customer_Trace";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Customer_Report";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Init";
            }
        }

        // 고객 이력조회
        else if (Stance == L"Customer_Trace") {
            wcout << L"확인하려는 제품이 어디에 속하나요?\n";
            wcout << L"1. 농산물\n2. 축산물\n3. 수산물\n입력: ";
            wstring Input, seller_ph;
            wcin >> Input;
            int classify = stoi(Input);
            wcout << L"조회하려는 제품의 ID를 입력해주세요.\n입력: ";
            wcin >> Input;
            wcout << L"판매자 전화번호를 입력해주세요.\n입력: ";
            wcin >> seller_ph;

            // 농산물, 축산물, 수산물에 따라 다른 sql 실행
            DB_Table prodInfo;
            if (classify == 1) {
                sql = L"select * from agriculture where ag_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodInfo);
            }
            else if (classify == 2) {
                sql = L"select * from livestock where live_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodInfo);
            }
            else if (classify == 3) {
                sql = L"select * from seafood where sea_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodInfo);
            }

            if (prodInfo.Tuples.empty()) {
                wcout << L"찾으시는 농축수산물이 존재하지 않습니다.\n";
                Sleep(2000);
                Stance = L"Customer_Init";
                continue;
            }

            wstring seller_ID, seller_loc, w_ID, w_loc, p_ID, p_loc;
            sql = L"select ret_id, ret_address from retailer where ret_phone = '" + seller_ph + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            seller_ID = tableData.Tuples[0][0];
            seller_loc = tableData.Tuples[0][1];

            sql = L"select wr_wid from wr_recipt where wr_rid = '" + seller_ID + L"' and wr_prodid = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            w_ID = tableData.Tuples[0][0];

            sql = L"select whole_facility from wholesaler where whole_id = '" + w_ID + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            w_loc = tableData.Tuples[0][0];

            wcout << L"\n생산품의 이동경로\n";
            wcout << L"생산지: " << prodInfo.Tuples[0][3] << L"\n|\n|\n|\nV\n"
                << L"유통지: " << w_loc << L"\n|\n|\n|\nV\n"
                << L"판매지: " << seller_loc << L"\n\n";

            DB_Table allprodInfo, pducerInfo;
            sql = L"select * from product where product_id = '" + prodInfo.Tuples[0][2] + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(allprodInfo);

            // 농축수산물 정보 출력
            if (classify == 1) {
                wcout << L"농산품 정보\n";
                wcout << L"농산물 ID: " << prodInfo.Tuples[0][0] << "\n";
                wcout << L"품목: " << allprodInfo.Tuples[0][1] << "\n";
                wcout << L"품목 그룹: " << allprodInfo.Tuples[0][2] << "\n";
                wcout << L"품종: " << allprodInfo.Tuples[0][3] << "\n";
                wcout << L"원산지: " << prodInfo.Tuples[0][3] << "\n";
                wcout << L"생산일: " << prodInfo.Tuples[0][4] << "\n";
                wcout << L"등급: " << prodInfo.Tuples[0][5] << "\n";
                wcout << L"무게: " << prodInfo.Tuples[0][6] << "\n";
                wcout << L"방사능 수치: " << prodInfo.Tuples[0][7] << "\n";
                wcout << L"GAP 인증 유무: " << prodInfo.Tuples[0][8] << "\n";
                wcout << L"GMO 유무: " << prodInfo.Tuples[0][9] << "\n";
            }
            else if (classify == 2) {
                wcout << L"축산품 정보\n";
                wcout << L"축산물 ID: " << prodInfo.Tuples[0][0] << "\n";
                wcout << L"품목: " << allprodInfo.Tuples[0][1] << "\n";
                wcout << L"품목 그룹: " << allprodInfo.Tuples[0][2] << "\n";
                wcout << L"품종: " << allprodInfo.Tuples[0][3] << "\n";
                wcout << L"원산지: " << prodInfo.Tuples[0][3] << "\n";
                wcout << L"구분: " << prodInfo.Tuples[0][4] << "\n";
                wcout << L"등급: " << prodInfo.Tuples[0][5] << "\n";
                wcout << L"무게: " << prodInfo.Tuples[0][6] << "\n";
                wcout << L"방사능 수치: " << prodInfo.Tuples[0][7] << "\n";
                wcout << L"HACCP 인증 유무: " << prodInfo.Tuples[0][8] << "\n";
            }
            else if (classify == 3) {
                wcout << L"수산품 정보\n";
                wcout << L"수산물 ID: " << prodInfo.Tuples[0][0] << "\n";
                wcout << L"품목: " << allprodInfo.Tuples[0][1] << "\n";
                wcout << L"품목 그룹: " << allprodInfo.Tuples[0][2] << "\n";
                wcout << L"품종: " << allprodInfo.Tuples[0][3] << "\n";
                wcout << L"원산지: " << prodInfo.Tuples[0][3] << "\n";
                wcout << L"등급: " << prodInfo.Tuples[0][4] << "\n";
                wcout << L"무게: " << prodInfo.Tuples[0][5] << "\n";
                wcout << L"방사능 수치: " << prodInfo.Tuples[0][6] << "\n";
                wcout << L"HACCP 인증 유무: " << prodInfo.Tuples[0][7] << "\n";
                wcout << L"GMO 유무: " << prodInfo.Tuples[0][8] << "\n";
            }

            sql = L"select * from producer where prod_id = '" + prodInfo.Tuples[0][1] + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"\n최초 생산자 정보\n";
            wcout << L"생산자 이름: " << tableData.Tuples[0][1] << L"\n";
            wcout << L"생산자 전화번호: " << tableData.Tuples[0][3] << L"\n";
            wcout << L"생산자 주소: " << tableData.Tuples[0][2] << L"\n";

            wcout << L"아무 키를 눌러 뒤로가기\n";
            wcin >> Input;
            Stance = L"Init";
        }

        // 고객 제품 신고
        else if (Stance == L"Customer_Report") {
            wstring Input, P_ID;
            wcout << L"제품의 ID를 입력해주세요.\n입력: ";
            wcin >> P_ID;

            // 입력 키 부분에 A,S,L에 따라 다른 sql 수행
            if (P_ID[8] == L'A') {
                sql = L"select * from agriculture where ag_id ='" + P_ID + L"';";
            }
            else if (P_ID[8] == L'S') {
                sql = L"select * from seafood where sea_id ='" + P_ID + L"';";
            }
            else if (P_ID[8] == L'L') {
                sql = L"select * from livestock where live_id ='" + P_ID + L"';";
            }
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            if (tableData.Tuples.empty()) {
                wcout << L"신고하려는 제품이 없습니다.\n";
                Stance = L"Customer_Init";
                continue;
            }

            wcout << L"제품의 어떤 점이 문제인가요? 판매자에 대한 정보도 되도록 설명해주세요.\n입력: ";
            wcin >> Input;

            sql = L"insert into complain values ('" + P_ID + L"','" + Input + L"')";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"제품의 문제가 정상적으로 접수되었습니다!\n";
            Sleep(2000);
            Stance = L"Init";
        }

        // 판매자 메뉴
        else if (Stance == L"Seller_Init") {
            // 자신의 정보 출력
            sql = L"select * from retailer where ret_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            vector<wstring> title = { L"아이디", L"업체 이름", L"주소", L"전화번호" };
            tableData.PrintRecord(title, 0);
            wcout << L"\n";

            wcout << L"이용하실 기능을 선택해주세요.\n1. 정보 수정\n2. 거래 내역 확인\n3. 유통업자와 거래\n4. 생산품 조회\n5. 로그아웃\n입력: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Seller_Modify";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Seller_Receipt";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Seller_Trade";
            }
            else if (stoi(Input) == 4) {
                Stance = L"Seller_Trace";
            }
            else if (stoi(Input) == 5) {
                Stance = L"Init";
            }
        }

        // 판매자 정보 수정
        else if (Stance == L"Seller_Modify") {
            wcout << L"수정하실 내용이 무엇인가요?\n1. 전화번호\n2. 주소\n3. 이름\n4. 비밀번호\n입력: ";
            wstring Input;
            wcin >> Input;
            // update sql 실행
            if (stoi(Input) == 1) {
                wcout << L"수정하실 전화번호를 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update retailer set ret_phone = '" + Input + L"' where ret_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"수정하실 주소를 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update retailer set ret_address = '" + Input + L"' where ret_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 3) {
                wcout << L"수정하실 이름을 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update retailer set ret_name = '" + Input + L"' where ret_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 4) {
                wcout << L"수정하실 비밀번호를 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update accout set acc_pw = '" + Input + L"' where acc_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            wcout << L"정상적으로 수정되었습니다!";
            Sleep(2000);
            Stance = L"Seller_Init";
        }

        // 판매자 거래 내역 조회
        else if (Stance == L"Seller_Receipt") {
            // 거래 내역 테이블 조회 sql
            sql = L"select * from wr_recipt where wr_rid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            DB_Table tableBuffer;
            vector<wstring> Wname, ProdName;

            // 유통업자 이름 구하기
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select whole_name from wholesaler where whole_id = '" + tableData.Tuples[i][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                Wname.push_back(tableBuffer.Tuples[0][0]);
            }

            // 생산품 이름 구하기
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wstring pid = tableData.Tuples[i][2];
                if (pid[8] == L'A') {
                    sql = L"select ag_prodid from agriculture where ag_id = '" + pid + L"';";                    
                }
                else if (pid[8] == L'S') {
                    sql = L"select sea_prodid from seafood where sea_id = '" + pid + L"';";
                }
                else if (pid[8] == L'L') {
                    sql = L"select live_prodid from livestock where live_id = '" + pid + L"';";
                }
                else {
                    continue;
                }
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                sql = L"select product_item from product where product_id = '" + tableBuffer.Tuples[0][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                ProdName.push_back(tableBuffer.Tuples[0][0]);
            }

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"유통업자: " << Wname[i] << L"\n";
                wcout << L"거래 물품: " << ProdName[i] << L"\n";
                wcout << L"거래 날짜: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"단위당 금액: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"단위: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"수량: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"특이사항: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"아무 키를 눌러 뒤로가기\n";
            wstring k;
            wcin >> k;
            Stance = L"Seller_Init";
        }

        // 판매자 유통업자와 거래
        else if (Stance == L"Seller_Trade") {
            
            // 유통업자들 보여주기
            sql = L"select * from wholesaler;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"유통업자 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"유통업자 이름: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"유통업자 주소: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"유통업자 전화번호: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"관리 시설: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            vector<wstring> rec_Inputs;

            wcout << L"거래 할 유통업자 ID를 입력해주세요.\n입력: ";
            wstring Input;
            wcin >> Input;
            rec_Inputs.push_back(Input);
            rec_Inputs.push_back(ID_Input);

            system("cls");

            sql = L"select pw_prodid, pw_cost, pw_remark from pw_recipt where pw_wid = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            // 생산품 이름, 소매 단위 정보 획득
            DB_Table tableBuffer;
            vector<wstring> ProdName, Unit;
            for (int i = 0; i < tableData.Tuples.size(); i++)
            {
                wstring pid = tableData.Tuples[i][0];
                if (pid[8] == L'A') {
                    sql = L"select ag_prodid from agriculture where ag_id = '" + pid + L"';";
                }
                else if (pid[8] == L'S') {
                    sql = L"select sea_prodid from seafood where sea_id = '" + pid + L"';";
                }
                else if (pid[8] == L'L') {
                    sql = L"select live_prodid from livestock where live_id = '" + pid + L"';";
                }
                else {
                    continue;
                }
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);
                
                sql = L"select product_item, product_retail_unit from product where product_id = '" + tableBuffer.Tuples[0][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);
                ProdName.push_back(tableBuffer.Tuples[0][0]);
                Unit.push_back(tableBuffer.Tuples[0][1]);
            }

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"생산품 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"생산품 이름: " << ProdName[i] << L"\n";
                wcout << L"생산자와 거래시 가격: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"거래 단위: " << Unit[i] << L"\n";
                wcout << L"생산자와 거래시 특이사항: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"거래할 생산물 ID를 입력해주세요.\n입력: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // 현재 시각 입력
            rec_Inputs.push_back(GetCurTime());

            wcout << L"거래하실 단위당 금액(단위: 원)을 입력해주세요.\n입력: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // 단위 따오기
            sql = L"select ag_prodid from agriculture where ag_id = '" + rec_Inputs[2] + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            if (tableData.Tuples.empty()) {
                sql = L"select sea_prodid from seafood where sea_id = '" + rec_Inputs[2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);
            }
            if (tableData.Tuples.empty()) {
                sql = L"select live_prodid from livestock where live_id = '" + rec_Inputs[2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);
            }

            sql = L"select product_retail_unit from product where product_id = '" + tableData.Tuples[0][0] + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            rec_Inputs.push_back(tableData.Tuples[0][0]);

            wcout << L"수량을 입력해주세요.\n입력: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            wcout << L"특이사항을 입력해주세요.\n입력: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            sql = L"insert into wr_recipt values('" + rec_Inputs[0] + L"', '"
                + rec_Inputs[1] + L"', '" + rec_Inputs[2] + L"', '" + rec_Inputs[3] + L"', "
                + rec_Inputs[4] + L", '" + rec_Inputs[5] + L"', " + rec_Inputs[6] + L", '"
                + rec_Inputs[7] + L"');";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"정상적으로 거래되었습니다!";
            Sleep(2000);
            Stance = L"Seller_Init";
        }

        // 판매자가 구입할 제품 이력 조회
        else if (Stance == L"Seller_Trace") {
            wcout << L"유통업체 이름을 입력해주세요.\n입력: ";
            wstring Input;
            wcin >> Input;

            sql = L"select * from wholesaler where whole_name = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"유통업자 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"유통업자 이름: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"유통업자 주소: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"유통업자 전화번호: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"관리 시설: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"유통업자 ID를 입력해주세요.\n입력: ";
            wcin >> Input;
            wcout << L"\n";

            // 유통경로 획득
            sql = L"select whole_facility from wholesaler where whole_id = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            wstring fac_loc = tableData.Tuples[0][0];

            // 농축수산물들 출력
            sql = L"select pw_prodid, pw_cost, pw_remark from pw_recipt where pw_wid = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            DB_Table tableBuffer;
            vector<wstring> ProdName, Unit;
            for (int i = 0; i < tableData.Tuples.size(); i++)
            {
                wstring pid = tableData.Tuples[i][0];
                if (pid[8] == L'A') {
                    sql = L"select ag_prodid from agriculture where ag_id = '" + pid + L"';";
                }
                else if (pid[8] == L'S') {
                    sql = L"select sea_prodid from seafood where sea_id = '" + pid + L"';";
                }
                else if (pid[8] == L'L') {
                    sql = L"select live_prodid from livestock where live_id = '" + pid + L"';";
                }
                else {
                    continue;
                }
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                sql = L"select product_item, product_retail_unit from product where product_id = '" + tableBuffer.Tuples[0][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);
                ProdName.push_back(tableBuffer.Tuples[0][0]);
                Unit.push_back(tableBuffer.Tuples[0][1]);
            }

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"생산품 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"생산품 이름: " << ProdName[i] << L"\n";
                wcout << L"생산자와 거래시 가격: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"거래 단위: " << Unit[i] << L"\n";
                wcout << L"생산자와 거래시 특이사항: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"검색하고자 하는 생산물 ID를 입력해주세요.\n입력: ";
            wcin >> Input;
            wcout << L"\n";

            // 축산물, 수산물, 농산물에 따라 다른 출력
            DB_Table prodTable;
            if (Input[8] == L'A') {
                sql = L"select * from agriculture where ag_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);

                sql = L"select product_item, product_kind from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodTable);               

                wcout << L"생산자 ID: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"생산품명: " << prodTable.Tuples[0][0] << L"\n";
                wcout << L"생산품속: " << prodTable.Tuples[0][1] << L"\n";
                wcout << L"생산일: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"등급: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"무게: " << tableData.Tuples[0][6] << L"\n";
                wcout << L"방사능 수치: " << tableData.Tuples[0][7] << L"\n";
                wcout << L"GAP 인증 유무: " << tableData.Tuples[0][8] << L"\n";
                wcout << L"GMO 인증 유무: " << tableData.Tuples[0][9] << L"\n";
            }
            else if (Input[8] == L'S') {
                sql = L"select * from seafood where sea_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);

                sql = L"select product_item, product_group from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodTable);

                wcout << L"생산자 ID: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"생산품명: " << prodTable.Tuples[0][0] << L"\n";
                wcout << L"생산품속: " << prodTable.Tuples[0][1] << L"\n";
                wcout << L"등급: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"무게: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"방사능 수치: " << tableData.Tuples[0][6] << L"\n";
                wcout << L"HACCP 인증 유무: " << tableData.Tuples[0][7] << L"\n";
                wcout << L"GMO 인증 유무: " << tableData.Tuples[0][8] << L"\n";
            }
            else if (Input[8] == L'L') {
                sql = L"select * from livestock where live_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);

                sql = L"select product_item, product_group from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodTable);

                wcout << L"생산자 ID: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"생산품명: " << prodTable.Tuples[0][0] << L"\n";
                wcout << L"생산품속: " << prodTable.Tuples[0][1] << L"\n";
                wcout << L"구분: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"등급: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"무게: " << tableData.Tuples[0][6] << L"\n";
                wcout << L"방사능 수치: " << tableData.Tuples[0][7] << L"\n";
                wcout << L"HACCP 인증 유무: " << tableData.Tuples[0][8] << L"\n";
            }

            wcout << L"\n이동경로\n" << tableData.Tuples[0][3] << L"\n|\n|\n|\nV\n" << fac_loc << L"\n";

            wcout << L"아무 키를 눌러 뒤로가기\n";
            wstring k;
            wcin >> k;
            Stance = L"Seller_Init";
        }

        // 유통자 메뉴
        else if (Stance == L"Wholesaler_Init") {
            // 자신의 정보 출력
            sql = L"select * from wholesaler where whole_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            vector<wstring> title = { L"아이디", L"업체 이름", L"주소", L"전화번호", L"관리시설 주소"};
            tableData.PrintRecord(title, 0);
            wcout << L"\n";

            wcout << L"이용하실 기능을 선택해주세요.\n1. 정보 수정\n2. 거래 내역 확인\n3. 생산자와 거래\n4. 로그아웃\n입력: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Wholesaler_Modify";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Wholesaler_Receipt";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Wholesaler_Trade";
            }
            else if (stoi(Input) == 4) {
                Stance = L"Init";
            }
        }

        // 유통자 수정
        else if (Stance == L"Wholesaler_Modify") {
            wcout << L"수정하실 내용이 무엇인가요?\n1. 전화번호\n2. 주소\n3. 이름\n4. 관리시설 주소\n5. 비밀번호\n입력: ";
            wstring Input;
            wcin >> Input;
            // update sql 수행
            if (stoi(Input) == 1) {
                wcout << L"수정하실 전화번호를 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_phone = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"수정하실 주소를 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_address = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 3) {
                wcout << L"수정하실 이름을 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_name = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 4) {
                wcout << L"수정하실 관리시설의 주소를 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_facility = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 5) {
                wcout << L"수정하실 비밀번호를 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update accout set acc_pw = '" + Input + L"' where acc_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"정상적으로 수정되었습니다!";
            Sleep(2000);
            Stance = L"Wholesaler_Init";
        }

        // 거래 내역 선택
        else if (Stance == L"Wholesaler_Receipt") {
            wcout << L"어떤 거래 내역을 조회하실건가요?\n";
            wcout << L"1. 생산자와의 거래 내역\n2. 판매자와의 거래 내역\n입력: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Wholesaler_Receipt_Producer";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Wholesaler_Receipt_Seller";
            }
        }

        // 판매자와의 거래 내역
        else if (Stance == L"Wholesaler_Receipt_Seller") {
            // 거래 내역 테이블 조회 sql
            sql = L"select * from wr_recipt where wr_wid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            DB_Table tableBuffer;
            vector<wstring> Rname, ProdName;

            // 판매자 이름 구하기
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select ret_name from retailer where ret_id = '" + tableData.Tuples[i][1] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                Rname.push_back(tableBuffer.Tuples[0][0]);
            }

            // 생산품 이름 구하기
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wstring pid = tableData.Tuples[i][2];
                if (pid[8] == L'A') {
                    sql = L"select ag_prodid from agriculture where ag_id = '" + pid + L"';";
                }
                else if (pid[8] == L'S') {
                    sql = L"select sea_prodid from seafood where sea_id = '" + pid + L"';";
                }
                else if (pid[8] == L'L') {
                    sql = L"select live_prodid from livestock where live_id = '" + pid + L"';";
                }
                else {
                    continue;
                }
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                sql = L"select product_item from product where product_id = '" + tableBuffer.Tuples[0][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                ProdName.push_back(tableBuffer.Tuples[0][0]);
            }

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"판매자: " << Rname[i] << L"\n";
                wcout << L"거래 물품: " << ProdName[i] << L"\n";
                wcout << L"거래 날짜: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"단위당 금액: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"단위: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"수량: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"특이사항: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"아무 키를 눌러 뒤로가기\n";
            wstring k;
            wcin >> k;
            Stance = L"Wholesaler_Init";
        }

        // 생산자와의 거래 내역
        else if (Stance == L"Wholesaler_Receipt_Producer") {
             // 거래 내역 테이블 조회 sql
             sql = L"select * from pw_recipt where pw_wid = '" + ID_Input + L"';";
             DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
             DB.GetTableData(tableData);

             DB_Table tableBuffer;
             vector<wstring> Rname, ProdName;

             // 생산자 이름 구하기
             for (int i = 0; i < tableData.Tuples.size(); i++) {
                 sql = L"select prod_name from producer where prod_id = '" + tableData.Tuples[i][1] + L"';";
                 DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                 DB.GetTableData(tableBuffer);

                 Rname.push_back(tableBuffer.Tuples[0][0]);
             }

             // 생산품 이름 구하기
             for (int i = 0; i < tableData.Tuples.size(); i++) {
                 wstring pid = tableData.Tuples[i][2];
                 if (pid[8] == L'A') {
                     sql = L"select ag_prodid from agriculture where ag_id = '" + pid + L"';";
                 }
                 else if (pid[8] == L'S') {
                     sql = L"select sea_prodid from seafood where sea_id = '" + pid + L"';";
                 }
                 else if (pid[8] == L'L') {
                     sql = L"select live_prodid from livestock where live_id = '" + pid + L"';";
                 }
                 else {
                     continue;
                 }
                 DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                 DB.GetTableData(tableBuffer);

                 sql = L"select product_item from product where product_id = '" + tableBuffer.Tuples[0][0] + L"';";
                 DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                 DB.GetTableData(tableBuffer);

                 ProdName.push_back(tableBuffer.Tuples[0][0]);
             }

             wcout << L"------------------------------------------\n";
             for (int i = 0; i < tableData.Tuples.size(); i++) {
                 wcout << L"생산자: " << Rname[i] << L"\n";
                 wcout << L"거래 물품: " << ProdName[i] << L"\n";
                 wcout << L"거래 날짜: " << tableData.Tuples[i][3] << L"\n";
                 wcout << L"단위당 금액: " << tableData.Tuples[i][4] << L"\n";
                 wcout << L"단위: " << tableData.Tuples[i][5] << L"\n";
                 wcout << L"수량: " << tableData.Tuples[i][6] << L"\n";
                 wcout << L"특이사항: " << tableData.Tuples[i][7] << L"\n";
                 wcout << L"------------------------------------------\n";
             }

            wcout << L"아무 키를 눌러 뒤로가기\n";
            wstring k;
            wcin >> k;
            Stance = L"Wholesaler_Init";
        }

        // 유통업자 거래
        else if (Stance == L"Wholesaler_Trade") {
            // 생산자들 보여주기
            sql = L"select * from producer;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"생산자 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"생산자 이름: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"생산자 주소: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"생산자 전화번호: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            vector<wstring> rec_Inputs;

            wcout << L"거래할 생산자 ID를 입력해주세요.\n입력: ";
            wstring Input;
            wcin >> Input;
            rec_Inputs.push_back(ID_Input);
            rec_Inputs.push_back(Input);

            system("cls");

            // 생산자의 모든 보유 농축수산물 출력
            // product id 획득
            DB_Table tableBuffer;
            sql = L"select * from agriculture where ag_pid ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            wcout << L"농산물\n";
            wcout << L"-----------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select product_item, product_kind, product_wholesale_unit from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                wcout << L"농산물 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"농산물종: " << tableBuffer.Tuples[i][0] << L"\n";
                wcout << L"농산물 품목: " << tableBuffer.Tuples[i][1] << L"\n";
                wcout << L"도매 거래 단위: " << tableBuffer.Tuples[i][2] << L"\n";
                wcout << L"원산지: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"수확 날짜: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"등급: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"보유 무게: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"방사능 수치: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"GAP 인증 유무: " << tableData.Tuples[i][8] << L"\n";
                wcout << L"GMO 인증 유무: " << tableData.Tuples[i][9] << L"\n";
                wcout << L"-----------------------------\n";
            }
            sql = L"select * from seafood where sea_pid ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            wcout << L"수산물\n";
            wcout << L"-----------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {               
                sql = L"select product_item, product_kind, product_wholesale_unit from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                wcout << L"수산물 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"수산물종: " << tableBuffer.Tuples[i][0] << L"\n";
                wcout << L"수산물 품목: " << tableBuffer.Tuples[i][1] << L"\n";
                wcout << L"도매 거래 단위: " << tableBuffer.Tuples[i][2] << L"\n";
                wcout << L"원산지: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"등급: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"보유 무게: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"방사능 수치: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"HACCP 인증 유무: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"GMO 인증 유무: " << tableData.Tuples[i][8] << L"\n";
                wcout << L"-----------------------------\n";
            }
            sql = L"select * from livestock where live_pid ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            wcout << L"축산물\n";
            wcout << L"-----------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select product_item, product_kind, product_wholesale_unit from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                wcout << L"축산물 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"축산물종: " << tableBuffer.Tuples[i][0] << L"\n";
                wcout << L"축산물 품목: " << tableBuffer.Tuples[i][1] << L"\n";
                wcout << L"도매 거래 단위: " << tableBuffer.Tuples[i][2] << L"\n";
                wcout << L"원산지: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"구분: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"등급: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"보유 무게: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"방사능 수치: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"HACCP 인증 유무: " << tableData.Tuples[i][8] << L"\n";
                wcout << L"-----------------------------\n";
            }

            wcout << L"거래할 생산물 ID를 입력해주세요.\n입력: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // 현재 시각 입력
            rec_Inputs.push_back(GetCurTime());

            wcout << L"거래하실 단위당 금액(단위: 원)을 입력해주세요.\n입력: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // 단위 따오기
            sql = L"select ag_prodid from agriculture where ag_id = '" + rec_Inputs[2] + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            if (tableData.Tuples.empty()) {
                sql = L"select sea_prodid from seafood where sea_id = '" + rec_Inputs[2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);
            }
            if (tableData.Tuples.empty()) {
                sql = L"select live_prodid from livestock where live_id = '" + rec_Inputs[2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);
            }

            sql = L"select product_wholesale_unit from product where product_id = '" + tableData.Tuples[0][0] + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            rec_Inputs.push_back(tableData.Tuples[0][0]);

            wcout << L"수량을 입력해주세요.\n입력: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            wcout << L"특이사항을 입력해주세요.\n입력: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            sql = L"insert into pw_recipt values('" + rec_Inputs[0] + L"', '"
                + rec_Inputs[1] + L"', '" + rec_Inputs[2] + L"', '" + rec_Inputs[3] + L"', "
                + rec_Inputs[4] + L", '" + rec_Inputs[5] + L"', " + rec_Inputs[6] + L", '"
                + rec_Inputs[7] + L"');";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"정상적으로 거래되었습니다!";
            Sleep(2000);
            Stance = L"Wholesaler_Init";
        }

        // 생산자 메뉴
        else if (Stance == L"Producer_Init") {
            // 자신의 정보 출력
            sql = L"select * from producer where prod_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            vector<wstring> title = { L"아이디", L"이름", L"주소", L"전화번호" };
            tableData.PrintRecord(title, 0);
            wcout << L"\n";

            wcout << L"이용하실 기능을 선택해주세요.\n1. 정보 수정\n2. 거래 내역 확인\n3. 농축수산물 등록\n4. 농축수산물 수정\n5. 로그아웃\n입력: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Producer_Modify";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Producer_Receipt";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Producer_Prod_Register";
            }
            else if (stoi(Input) == 4) {
                Stance = L"Producer_Prod_Modify";
            }
            else if (stoi(Input) == 5) {
                Stance = L"Init";
            }
        }

        // 생산자 정보 수정
        else if (Stance == L"Producer_Modify") {
            wcout << L"수정하실 내용이 무엇인가요?\n1. 전화번호\n2. 주소\n3. 이름\n4. 비밀번호\n입력: ";
            wstring Input;
            wcin >> Input;
            // update sql 실행
            if (stoi(Input) == 1) {
                wcout << L"수정하실 전화번호를 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update producer set prod_phone = '" + Input + L"' where prod_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"수정하실 주소를 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update producer set prod_address = '" + Input + L"' where prod_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 3) {
                wcout << L"수정하실 이름을 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update producer set prod_name = '" + Input + L"' where prod_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 4) {
                wcout << L"수정하실 비밀번호를 적어주세요\n입력: ";
                wcin >> Input;
                sql = L"update accout set acc_pw = '" + Input + L"' where acc_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            wcout << L"정상적으로 수정되었습니다!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        // 생산자 거래 내역
        else if (Stance == L"Producer_Receipt") {
            sql = L"select * from pw_recipt where pw_pid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            DB_Table tableBuffer;
            vector<wstring> Wname, ProdName;

            // 유통업자 이름 구하기
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select whole_name from wholesaler where whole_id = '" + tableData.Tuples[i][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                Wname.push_back(tableBuffer.Tuples[0][0]);
            }

            // 생산품 이름 구하기
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wstring pid = tableData.Tuples[i][2];
                if (pid[8] == L'A') {
                    sql = L"select ag_prodid from agriculture where ag_id = '" + pid + L"';";
                }
                else if (pid[8] == L'S') {
                    sql = L"select sea_prodid from seafood where sea_id = '" + pid + L"';";
                }
                else if (pid[8] == L'L') {
                    sql = L"select live_prodid from livestock where live_id = '" + pid + L"';";
                }
                else {
                    continue;
                }
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                sql = L"select product_item from product where product_id = '" + tableBuffer.Tuples[0][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                ProdName.push_back(tableBuffer.Tuples[0][0]);
            }

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"유통업자: " << Wname[i] << L"\n";
                wcout << L"거래 물품: " << ProdName[i] << L"\n";
                wcout << L"거래 날짜: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"단위당 금액: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"단위: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"수량: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"특이사항: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"아무 키를 눌러 뒤로가기\n";
            wstring k;
            wcin >> k;
            Stance = L"Producer_Init";
        }

        // 생산자 농축수산물 등록
        else if (Stance == L"Producer_Prod_Register") {
            wcout << L"등록할 농축수산물 품종을 적어주세요.\n입력: ";
            wstring Input;
            wcin >> Input;

            sql = L"select * from product where product_item ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"품목 목록\n-----------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++)
            {
                wcout << L"생산물 ID: " << tableData.Tuples[0][0] << L"\n";
                wcout << L"품목명: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"품목 그룹명: " << tableData.Tuples[0][2] << L"\n";
                wcout << L"품종명: " << tableData.Tuples[0][3] << L"\n";
                wcout << L"도매 거래 단위: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"소매 거래 단위: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"-----------------------\n";
            }

            wcout << L"등록할 농축수산물 ID을 적어주세요.\n입력: ";
            wcin >> Input;

            wstring key = GetCurTime(true);
            vector<wstring> rec_info;

            rec_info.push_back(ID_Input);
            rec_info.push_back(Input);

            wcout << L"원산지가 어디인가요?\n입력: ";
            wcin >> Input;
            rec_info.push_back(Input);

            // 농산물, 축산물, 수산물에 따라 다른 정보 요구
            if (rec_info[1][0] == L'A') {
                key += rec_info[1][0];
                sql = L"select ag_id from agriculture where ag_id like '" + key + L"%' order by ag_id desc;";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);
                if (tableData.Tuples.empty()) {
                    key += L"0000";
                }
                else {
                    wstring hkey = tableData.Tuples[0][0];
                    int num = stoi(hkey.substr(9, 4));
                    hkey = to_wstring(++num);
                    while (hkey.length() < 4) {
                        hkey.insert(hkey.begin(), L'0');
                    }
                    key += hkey;
                }
                rec_info.insert(rec_info.begin(), key);

                // 생산날짜 삽입
                rec_info.push_back(GetCurTime());

                Input.clear();
                wcout << L"등급이 어떻게 되나요?\n입력: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"무게는 어떻게 되나요?\n입력: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"방사능 수치는 어떻게 되나요?\n입력: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"GAP 인증을 받았나요?\n1. 예\n2. 아니요\n입력: ";
                wcin >> Input;
                Input = stoi(Input) == 1 ? L"yes" : L"no";
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"GMO 인가요?\n1. 예\n2. 아니요\n입력: ";
                wcin >> Input;
                Input = stoi(Input) == 1 ? L"yes" : L"no";
                rec_info.push_back(Input);

                sql = L"insert into agriculture values('" + rec_info[0] + L"', '" + rec_info[1] + L"', '"
                    + rec_info[2] + L"', '" + rec_info[3] + L"', '" + rec_info[4] + L"', '" + rec_info[5] + L"', '"
                    + rec_info[6] + L"', '" + rec_info[7] + L"', '" + rec_info[8] + L"', '" + rec_info[9] + L"');";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (rec_info[1][0] == L'S') {
                key += rec_info[1][0];
                sql = L"select sea_id from seafood where sea_id like '" + key + L"%' order by sea_id desc;";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);
                if (tableData.Tuples.empty()) {
                    key += L"0000";
                }
                else {
                    wstring hkey = tableData.Tuples[0][0];
                    int num = stoi(hkey.substr(9, 4));
                    hkey = to_wstring(++num);
                    while (hkey.length() < 4) {
                        hkey.insert(hkey.begin(), L'0');
                    }
                    key += hkey;
                }
                rec_info.insert(rec_info.begin(), key);

                Input.clear();
                wcout << L"등급이 어떻게 되나요?\n입력: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"무게는 어떻게 되나요?\n입력: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"방사능 수치는 어떻게 되나요?\n입력: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"HACCP 인증을 받았나요?\n1. 예\n2. 아니요\n입력: ";
                wcin >> Input;
                Input = stoi(Input) == 1 ? L"yes" : L"no";
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"GMO 인가요?\n1. 예\n2. 아니요\n입력: ";
                wcin >> Input;
                Input = stoi(Input) == 1 ? L"yes" : L"no";
                rec_info.push_back(Input);

                sql = L"insert into seafood values('" + rec_info[0] + L"', '"
                    + rec_info[1] + L"', '" + rec_info[2] + L"', '" + rec_info[3] + L"', '" + rec_info[4] + L"', '"
                    + rec_info[5] + L"', '" + rec_info[6] + L"', '" + rec_info[7] + L"', '" + rec_info[8] + L"');";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (rec_info[1][0] == L'L') {
                key += rec_info[1][0];
                sql = L"select live_id from livestock where live_id like '" + key + L"%' order by live_id desc;";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);
                if (tableData.Tuples.empty()) {
                    key += L"0000";
                }
                else {
                    wstring hkey = tableData.Tuples[0][0];
                    int num = stoi(hkey.substr(9, 4));
                    hkey = to_wstring(++num);
                    while (hkey.length() < 4) {
                        hkey.insert(hkey.begin(), L'0');
                    }
                    key += hkey;
                }
                rec_info.insert(rec_info.begin(), key);

                Input.clear();
                wcout << L"구분이 어떻게 되나요?\n입력: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"등급이 어떻게 되나요?\n입력: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"무게는 어떻게 되나요?\n입력: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"방사능 수치는 어떻게 되나요?\n입력: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"HACCP 인증을 받았나요?\n1. 예\n2. 아니요\n입력: ";
                wcin >> Input;
                Input = stoi(Input) == 1 ? L"yes" : L"no";
                rec_info.push_back(Input);

                sql = L"insert into livestock values('" + rec_info[0] + L"', '"
                    + rec_info[1] + L"', '" + rec_info[2] + L"', '" + rec_info[3] + L"', '" + rec_info[4] + L"', '"
                    + rec_info[5] + L"', '" + rec_info[6] + L"', '" + rec_info[7] + L"', '" + rec_info[8] + L"');";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"정상적으로 처리되었습니다!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        // 생산자 농축수산물 수정
        else if (Stance == L"Producer_Prod_Modify") {
            wcout << L"어떤 생산물을 수정할 것인가요?\n1. 농산물\n2. 수산물\n3. 축산물\n입력: ";
            wstring Input;
            wcin >> Input;

            if (stoi(Input) == 1) {
                Stance = L"Producer_Prod_Ag";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Producer_Prod_Sea";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Producer_Prod_Live";
            }
        }

        // 농산물 수정
        else if (Stance == L"Producer_Prod_Ag") {
            wstring Input;
            sql = L"select * from agriculture where ag_pid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"----------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"농산물 ID: " << tableData.Tuples[i][0] << "\n";
                wcout << L"생산품 ID: " << tableData.Tuples[i][2] << "\n";
                wcout << L"원산지: " << tableData.Tuples[i][3] << "\n";
                wcout << L"생산일: " << tableData.Tuples[i][4] << "\n";
                wcout << L"등급: " << tableData.Tuples[i][5] << "\n";
                wcout << L"무게: " << tableData.Tuples[i][6] << "\n";
                wcout << L"방사능 수치: " << tableData.Tuples[i][7] << "\n";
                wcout << L"GAP 인증 유무: " << tableData.Tuples[i][8] << "\n";
                wcout << L"GMO 인증 유무: " << tableData.Tuples[i][9] << "\n";
                wcout << L"----------------------------------\n";
            }

            wstring product_id;
            wcout << L"수정하실 농산물 ID를 입력해 주세요.\n입력: ";
            wcin >> product_id;
            wcout << L"수정하실 내용이 무엇인가요?\n1. 생산일\n2. 무게\n입력: ";
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"현재 날짜로 생산일이 변경됩니다.\n";            
                sql = L"update agriculture set ag_date = '" + GetCurTime() + L"' where ag_id = '" + product_id + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"수정하실 무게를 입력해 주세요.\n입력: ";
                wcin >> Input;
                sql = L"update agriculture set ag_weight = '" + Input + L"' where ag_id = '" + product_id + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"정상적으로 수정되었습니다!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        // 수산물 수정
        else if (Stance == L"Producer_Prod_Sea") {
            wstring Input;
            sql = L"select * from seafood where sea_pid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"----------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"수산물 ID: " << tableData.Tuples[i][0] << "\n";
                wcout << L"생산품 ID: " << tableData.Tuples[i][2] << "\n";
                wcout << L"원산지: " << tableData.Tuples[i][3] << "\n";
                wcout << L"등급: " << tableData.Tuples[i][4] << "\n";
                wcout << L"무게: " << tableData.Tuples[i][5] << "\n";
                wcout << L"방사능 수치: " << tableData.Tuples[i][6] << "\n";
                wcout << L"HACCP 인증 유무: " << tableData.Tuples[i][7] << "\n";
                wcout << L"GMO 인증 유무: " << tableData.Tuples[i][8] << "\n";
                wcout << L"----------------------------------\n";
            }

            wstring product_id;
            wcout << L"수정하실 수산물 ID를 입력해 주세요.\n입력: ";
            wcin >> product_id;
            wcout << L"수정하실 무게를 입력해 주세요.\n입력: ";
            wcin >> Input;
            sql = L"update seafood set sea_weight = '" + Input + L"' where sea_id = '" + product_id + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"정상적으로 수정되었습니다!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        // 축산물 수정
        else if (Stance == L"Producer_Prod_Live") {
            wstring Input;
            sql = L"select * from livestock where live_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"----------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"축산물 ID: " << tableData.Tuples[i][0] << "\n";
                wcout << L"생산품 ID: " << tableData.Tuples[i][2] << "\n";
                wcout << L"원산지: " << tableData.Tuples[i][3] << "\n";
                wcout << L"구분: " << tableData.Tuples[i][4] << "\n";
                wcout << L"등급: " << tableData.Tuples[i][5] << "\n";
                wcout << L"무게: " << tableData.Tuples[i][6] << "\n";
                wcout << L"방사능 수치: " << tableData.Tuples[i][7] << "\n";
                wcout << L"HACCP 인증 유무: " << tableData.Tuples[i][8] << "\n";
                wcout << L"----------------------------------\n";
            }

            wstring product_id;
            wcout << L"수정하실 축산물 ID를 입력해 주세요.\n입력: ";
            wcin >> product_id;
            wcout << L"수정하실 내용이 무엇인가요?\n1. 구분\n2. 무게\n입력: ";
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"수정하실 구분을 입력해 주세요.\n입력: ";
                wcin >> Input;
                sql = L"update livestock set live_div = '" + Input + L"' where live_id = '" + product_id + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"수정하실 무게를 입력해 주세요.\n입력: ";
                wcin >> Input;
                sql = L"update livestock set live_weight = '" + Input + L"' where live_id = '" + product_id + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"정상적으로 수정되었습니다!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        // 관리자 메뉴
        else if (Stance == L"Admin_Init") {
            wcout << L"이용하실 기능을 선택해주세요.\n1. 민원 조회\n2. 농축수산물 추가\n3. 이용자 조회\n4. 로그아웃\n입력: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Admin_Report";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Admin_Product";
            }
            else if (stoi(Input) == 3) {
                Stance = L"Admin_User";
            }
            else if (stoi(Input) == 4) {
                Stance = L"Init";
            }
        }

        // 민원 조회
        else if (Stance == L"Admin_Report") {
            // 신고 테이블 조회
            sql = L"select * from complain;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            DB_Table tableBuffer;
            wcout << L"----------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                if (tableData.Tuples[i][0][8] == L'A') {
                    sql = L"select * from agriculture where ag_id = '" + tableData.Tuples[i][0] + L"';";
                    DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                    DB.GetTableData(tableBuffer);
                    wcout << L"농산물 ID: " << tableBuffer.Tuples[i][0] << "\n";
                    wcout << L"생산품 ID: " << tableBuffer.Tuples[i][2] << "\n";
                    wcout << L"원산지: " << tableBuffer.Tuples[i][3] << "\n";
                    wcout << L"생산일: " << tableBuffer.Tuples[i][4] << "\n";
                    wcout << L"등급: " << tableBuffer.Tuples[i][5] << "\n";
                    wcout << L"무게: " << tableBuffer.Tuples[i][6] << "\n";
                    wcout << L"방사능 수치: " << tableBuffer.Tuples[i][7] << "\n";
                    wcout << L"GAP 인증 유무: " << tableBuffer.Tuples[i][8] << "\n";
                    wcout << L"GMO 인증 유무: " << tableBuffer.Tuples[i][9] << "\n";
                }
                else if (tableData.Tuples[i][0][8] == L'S') {
                    sql = L"select * from agriculture where ag_id = '" + tableData.Tuples[i][0] + L"';";
                    DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                    DB.GetTableData(tableBuffer);
                    wcout << L"수산물 ID: " << tableData.Tuples[i][0] << "\n";
                    wcout << L"생산품 ID: " << tableData.Tuples[i][2] << "\n";
                    wcout << L"원산지: " << tableData.Tuples[i][3] << "\n";
                    wcout << L"등급: " << tableData.Tuples[i][4] << "\n";
                    wcout << L"무게: " << tableData.Tuples[i][5] << "\n";
                    wcout << L"방사능 수치: " << tableData.Tuples[i][6] << "\n";
                    wcout << L"HACCP 인증 유무: " << tableData.Tuples[i][7] << "\n";
                    wcout << L"GMO 인증 유무: " << tableData.Tuples[i][8] << "\n";
                }
                else if (tableData.Tuples[i][0][8] == L'L') {
                    sql = L"select * from agriculture where ag_id = '" + tableData.Tuples[i][0] + L"';";
                    DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                    DB.GetTableData(tableBuffer);
                    wcout << L"축산물 ID: " << tableData.Tuples[i][0] << "\n";
                    wcout << L"생산품 ID: " << tableData.Tuples[i][2] << "\n";
                    wcout << L"원산지: " << tableData.Tuples[i][3] << "\n";
                    wcout << L"구분: " << tableData.Tuples[i][4] << "\n";
                    wcout << L"등급: " << tableData.Tuples[i][5] << "\n";
                    wcout << L"무게: " << tableData.Tuples[i][6] << "\n";
                    wcout << L"방사능 수치: " << tableData.Tuples[i][7] << "\n";
                    wcout << L"HACCP 인증 유무: " << tableData.Tuples[i][8] << "\n";
                }
                wcout << L"특이사항: " << tableData.Tuples[i][1] << "\n";
                wcout << L"----------------------------------\n";
            }
            wcout << L"아무 키를 눌러 뒤로가기\n";
            wstring k;
            wcin >> k;
            Stance = L"Admin_Init";
        }

        // 농축수산물 추가
        else if (Stance == L"Admin_Product") {
            wstring Input;
            vector<wstring> In_data;
            wcout << L"추가할 것이 무엇인지 선택해주세요\n1. 농산물\n2. 수산물\n3. 축산물\n입력: ";
            wcin >> Input;
            if (stoi(Input) == 1) {
                sql = L"select product_id from product where product_id like 'A%' order by product_id desc;";
                In_data.push_back(L"A");
            }
            else if (stoi(Input) == 2) {
                sql = L"select product_id from product where product_id like 'S%' order by product_id desc;";
                In_data.push_back(L"S");
            }
            else if (stoi(Input) == 3) {
                sql = L"select product_id from product where product_id like 'L%' order by product_id desc;";
                In_data.push_back(L"L");
            }
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            int num = stoi(tableData.Tuples[0][0].substr(1));
            In_data[0] += to_wstring(num + 1);
            wcout << L"생산품 이름을 입력해주세요\n입력: ";
            wcin >> Input;
            In_data.push_back(Input);
            wcout << L"생산품 그룹을 입력해주세요\n입력: ";
            wcin >> Input;
            In_data.push_back(Input);
            wcout << L"생산품 품종을 입력해주세요\n입력: ";
            wcin >> Input;
            In_data.push_back(Input);
            wcout << L"도매 거래 단위를 입력해주세요\n입력: ";
            wcin >> Input;
            In_data.push_back(Input);
            wcout << L"소매 거래 단위를 입력해주세요\n입력: ";
            wcin >> Input;
            In_data.push_back(Input);
            sql = L"insert into product values('" + In_data[0] + L"','" + In_data[1] + L"','" + In_data[2] + L"','"
                + In_data[3] + L"','" + In_data[4] + L"','" + In_data[5] + L"');";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"정상적으로 추가되었습니다!";
            Sleep(2000);
            Stance = L"Admin_Init";
        }

        // 이용자 조회
        else if (Stance == L"Admin_User") {
            wstring Input;
            int printID = 1;
            wcout << L"찾으실 사용자의 전화번호나 키를 입력해주세요\n입력: ";
            wcin >> Input;
            if (Input[0] == L'P' || Input[0] == L'p') {
                sql = L"select * from producer where prod_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData); 
                printID = 1;
            }
            else if (Input[0] == L'R' || Input[0] == L'R') {
                sql = L"select * from retailer where ret_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);
                printID = 2;
            }
            else if (Input[0] == L'W' || Input[0] == L'W') {
                sql = L"select * from wholesaler where whole_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);
                printID = 3;
            }
            else {
                printID = 1;
                sql = L"select * from producer where prod_phone = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);
                if (tableData.Tuples.empty()) {
                    sql = L"select * from retailer where ret_phone = '" + Input + L"';";
                    DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                    DB.GetTableData(tableData);
                    printID = 2;
                }
                if (tableData.Tuples.empty()) {
                    sql = L"select * from wholesaler where whole_phone = '" + Input + L"';";
                    DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                    DB.GetTableData(tableData);
                    printID = 3;
                }
            }
            if (printID == 1) {
                wcout << L"생산자 ID: " << tableData.Tuples[0][0] << L"\n";
                wcout << L"생산자 이름: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"생산자 주소: " << tableData.Tuples[0][2] << L"\n";
                wcout << L"생산자 전화번호: " << tableData.Tuples[0][3] << L"\n";
            }
            else if (printID == 2) {
                wcout << L"판매자 ID: " << tableData.Tuples[0][0] << L"\n";
                wcout << L"판매업체: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"판매자 주소: " << tableData.Tuples[0][2] << L"\n";
                wcout << L"판매자 전화번호: " << tableData.Tuples[0][3] << L"\n";
            }
            else {
                wcout << L"유통업자 ID: " << tableData.Tuples[0][0] << L"\n";
                wcout << L"유통업체: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"유통업체 주소: " << tableData.Tuples[0][2] << L"\n";
                wcout << L"유통업체 전화번호: " << tableData.Tuples[0][3] << L"\n";
                wcout << L"관리 시설 주소: " << tableData.Tuples[0][4] << L"\n";
            }
            wcout << L"아무 키를 눌러 뒤로가기\n";
            wstring k;
            wcin >> k;
            Stance = L"Admin_Init";
        }

        // 종료 상태
        else {
            system("cls");
            break;
        }
    }

    DB.DisconnectDataSource();
    return 0;
}