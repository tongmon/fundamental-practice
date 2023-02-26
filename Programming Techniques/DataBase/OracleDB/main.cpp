#include "CODBC.h"
#include <conio.h>
#include <ctime>
using namespace std;

#pragma warning( disable : 4996 )

// 201663021 �̰��� 
// ����깰 �̷��� �����ͺ��̽� C++ ����
// x64 ��Ʈ���� �۵��մϴ�.

#define DNS_name L"trace_DB" // ODBC�� ������ �����ͺ��̽�
#define User_name L"lee" // �����ͺ��̽� ��Ʈ���� ����
#define Password L"1213" // �����ͺ��̽� ��Ʈ���� ���� ��й�ȣ

wstring GetCurTime(bool keytime = false) // ���� �ð��� ȹ���ϴ� �Լ�
{
    wstring result;
    time_t timer;
    struct tm* t;
    timer = time(NULL);
    t = localtime(&timer);
    // keytime üũ ������ ���� �ٸ� ���� ��ȯ�ϰ� ����
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

wstring GetPW() // ��й�ȣ ���ȼ� ����� ���� * ǥ�÷� �Է� �޴� �Լ�
{
    wstring PW;
    int index = 0;
    char chpw[256];
    while (true) // ���� ������ ���� �ݺ�
    {
        chpw[index] = _getch(); // �� ���ھ� ��й�ȣ �Է�
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

    // DB ���� �ȵǸ� ���α׷� ����
    if (DB.ConnectDataSource((SQLWCHAR*)DNS_name, (SQLWCHAR*)User_name, (SQLWCHAR*)Password) != SQL_SUCCESS) {
        return 1;
    }

    DB_Table tableData;
    wstring Stance = L"Init", ID_Input, PW_Input, sql;
    while (true) {
        system("cls");
        if (Stance == L"Init") {
            wcout << L"Made by 201663021 �̰���\n������깰 �̷��� �ý��ۿ� ���Ű��� ȯ���մϴ�.\n";
            wcout << L"1. �Һ��� �ο�\n2. �α���\n3. ������\n4. ����\n�Է�: ";
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

        // ������ ����
        else if (Stance == L"Dev_Show") {
            wcout << L"�Ⱦ���б� ��ǻ�Ͱ��а� 4�г� 201663021 �̰��� ����\n";
            wcout << L"����깰 �̷��� ������ ��� ����Ŭ �����ͺ��̽��� ODBC�� ���� C++�� �����߽��ϴ�.\n";
            wcout << L"�������̽��� �ܼ�â �������� �����˴ϴ�.\n";
            wcout << L"�����, ������, �Ǹ���, ������, �����ڿ� ���� �ٸ� ������ �־����ϴ�.\n";
            wcout << L"�α����� ���� �����ް� ���񽺸� �̿��ϼ���.";
            Sleep(5000);
            Stance = L"Init";
        }

        // �α��� ����
        else if (Stance == L"Login") {
            wcout << L"���̵�� ��й�ȣ�� �Է����ּ���.\n";
            wcout << L"ID: ";
            wcin >> ID_Input;
            wcout << L"PW: ";
            PW_Input = GetPW();

            sql = L"select acc_pw from accout where acc_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            if (tableData.Tuples.empty() || tableData.Tuples[0][0] != PW_Input) {
                wcout << L"\n�� �� ���� ID �Ǵ� ��й�ȣ�Դϴ�.\n�ٽ� �Է��� �ּ���.";
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

        // �� �޴�
        else if (Stance == L"Customer_Init") {
            wcout << L"������깰 �̷��� �ý����Դϴ�. ���Ͻô� ����� �������ּ���.\n";
            wcout << L"1. ��ǰ �̷���ȸ\n2. ��ǰ ���� �Ű�\n3. �α׾ƿ�\n�Է�: ";
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

        // �� �̷���ȸ
        else if (Stance == L"Customer_Trace") {
            wcout << L"Ȯ���Ϸ��� ��ǰ�� ��� ���ϳ���?\n";
            wcout << L"1. ��깰\n2. ��깰\n3. ���깰\n�Է�: ";
            wstring Input, seller_ph;
            wcin >> Input;
            int classify = stoi(Input);
            wcout << L"��ȸ�Ϸ��� ��ǰ�� ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            wcout << L"�Ǹ��� ��ȭ��ȣ�� �Է����ּ���.\n�Է�: ";
            wcin >> seller_ph;

            // ��깰, ��깰, ���깰�� ���� �ٸ� sql ����
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
                wcout << L"ã���ô� ������깰�� �������� �ʽ��ϴ�.\n";
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

            wcout << L"\n����ǰ�� �̵����\n";
            wcout << L"������: " << prodInfo.Tuples[0][3] << L"\n|\n|\n|\nV\n"
                << L"������: " << w_loc << L"\n|\n|\n|\nV\n"
                << L"�Ǹ���: " << seller_loc << L"\n\n";

            DB_Table allprodInfo, pducerInfo;
            sql = L"select * from product where product_id = '" + prodInfo.Tuples[0][2] + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(allprodInfo);

            // ������깰 ���� ���
            if (classify == 1) {
                wcout << L"���ǰ ����\n";
                wcout << L"��깰 ID: " << prodInfo.Tuples[0][0] << "\n";
                wcout << L"ǰ��: " << allprodInfo.Tuples[0][1] << "\n";
                wcout << L"ǰ�� �׷�: " << allprodInfo.Tuples[0][2] << "\n";
                wcout << L"ǰ��: " << allprodInfo.Tuples[0][3] << "\n";
                wcout << L"������: " << prodInfo.Tuples[0][3] << "\n";
                wcout << L"������: " << prodInfo.Tuples[0][4] << "\n";
                wcout << L"���: " << prodInfo.Tuples[0][5] << "\n";
                wcout << L"����: " << prodInfo.Tuples[0][6] << "\n";
                wcout << L"���� ��ġ: " << prodInfo.Tuples[0][7] << "\n";
                wcout << L"GAP ���� ����: " << prodInfo.Tuples[0][8] << "\n";
                wcout << L"GMO ����: " << prodInfo.Tuples[0][9] << "\n";
            }
            else if (classify == 2) {
                wcout << L"���ǰ ����\n";
                wcout << L"��깰 ID: " << prodInfo.Tuples[0][0] << "\n";
                wcout << L"ǰ��: " << allprodInfo.Tuples[0][1] << "\n";
                wcout << L"ǰ�� �׷�: " << allprodInfo.Tuples[0][2] << "\n";
                wcout << L"ǰ��: " << allprodInfo.Tuples[0][3] << "\n";
                wcout << L"������: " << prodInfo.Tuples[0][3] << "\n";
                wcout << L"����: " << prodInfo.Tuples[0][4] << "\n";
                wcout << L"���: " << prodInfo.Tuples[0][5] << "\n";
                wcout << L"����: " << prodInfo.Tuples[0][6] << "\n";
                wcout << L"���� ��ġ: " << prodInfo.Tuples[0][7] << "\n";
                wcout << L"HACCP ���� ����: " << prodInfo.Tuples[0][8] << "\n";
            }
            else if (classify == 3) {
                wcout << L"����ǰ ����\n";
                wcout << L"���깰 ID: " << prodInfo.Tuples[0][0] << "\n";
                wcout << L"ǰ��: " << allprodInfo.Tuples[0][1] << "\n";
                wcout << L"ǰ�� �׷�: " << allprodInfo.Tuples[0][2] << "\n";
                wcout << L"ǰ��: " << allprodInfo.Tuples[0][3] << "\n";
                wcout << L"������: " << prodInfo.Tuples[0][3] << "\n";
                wcout << L"���: " << prodInfo.Tuples[0][4] << "\n";
                wcout << L"����: " << prodInfo.Tuples[0][5] << "\n";
                wcout << L"���� ��ġ: " << prodInfo.Tuples[0][6] << "\n";
                wcout << L"HACCP ���� ����: " << prodInfo.Tuples[0][7] << "\n";
                wcout << L"GMO ����: " << prodInfo.Tuples[0][8] << "\n";
            }

            sql = L"select * from producer where prod_id = '" + prodInfo.Tuples[0][1] + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"\n���� ������ ����\n";
            wcout << L"������ �̸�: " << tableData.Tuples[0][1] << L"\n";
            wcout << L"������ ��ȭ��ȣ: " << tableData.Tuples[0][3] << L"\n";
            wcout << L"������ �ּ�: " << tableData.Tuples[0][2] << L"\n";

            wcout << L"�ƹ� Ű�� ���� �ڷΰ���\n";
            wcin >> Input;
            Stance = L"Init";
        }

        // �� ��ǰ �Ű�
        else if (Stance == L"Customer_Report") {
            wstring Input, P_ID;
            wcout << L"��ǰ�� ID�� �Է����ּ���.\n�Է�: ";
            wcin >> P_ID;

            // �Է� Ű �κп� A,S,L�� ���� �ٸ� sql ����
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
                wcout << L"�Ű��Ϸ��� ��ǰ�� �����ϴ�.\n";
                Stance = L"Customer_Init";
                continue;
            }

            wcout << L"��ǰ�� � ���� �����ΰ���? �Ǹ��ڿ� ���� ������ �ǵ��� �������ּ���.\n�Է�: ";
            wcin >> Input;

            sql = L"insert into complain values ('" + P_ID + L"','" + Input + L"')";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"��ǰ�� ������ ���������� �����Ǿ����ϴ�!\n";
            Sleep(2000);
            Stance = L"Init";
        }

        // �Ǹ��� �޴�
        else if (Stance == L"Seller_Init") {
            // �ڽ��� ���� ���
            sql = L"select * from retailer where ret_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            vector<wstring> title = { L"���̵�", L"��ü �̸�", L"�ּ�", L"��ȭ��ȣ" };
            tableData.PrintRecord(title, 0);
            wcout << L"\n";

            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. ���� ����\n2. �ŷ� ���� Ȯ��\n3. ������ڿ� �ŷ�\n4. ����ǰ ��ȸ\n5. �α׾ƿ�\n�Է�: ";
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

        // �Ǹ��� ���� ����
        else if (Stance == L"Seller_Modify") {
            wcout << L"�����Ͻ� ������ �����ΰ���?\n1. ��ȭ��ȣ\n2. �ּ�\n3. �̸�\n4. ��й�ȣ\n�Է�: ";
            wstring Input;
            wcin >> Input;
            // update sql ����
            if (stoi(Input) == 1) {
                wcout << L"�����Ͻ� ��ȭ��ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update retailer set ret_phone = '" + Input + L"' where ret_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"�����Ͻ� �ּҸ� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update retailer set ret_address = '" + Input + L"' where ret_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 3) {
                wcout << L"�����Ͻ� �̸��� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update retailer set ret_name = '" + Input + L"' where ret_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 4) {
                wcout << L"�����Ͻ� ��й�ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update accout set acc_pw = '" + Input + L"' where acc_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            wcout << L"���������� �����Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Seller_Init";
        }

        // �Ǹ��� �ŷ� ���� ��ȸ
        else if (Stance == L"Seller_Receipt") {
            // �ŷ� ���� ���̺� ��ȸ sql
            sql = L"select * from wr_recipt where wr_rid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            DB_Table tableBuffer;
            vector<wstring> Wname, ProdName;

            // ������� �̸� ���ϱ�
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select whole_name from wholesaler where whole_id = '" + tableData.Tuples[i][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                Wname.push_back(tableBuffer.Tuples[0][0]);
            }

            // ����ǰ �̸� ���ϱ�
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
                wcout << L"�������: " << Wname[i] << L"\n";
                wcout << L"�ŷ� ��ǰ: " << ProdName[i] << L"\n";
                wcout << L"�ŷ� ��¥: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"������ �ݾ�: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"Ư�̻���: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"�ƹ� Ű�� ���� �ڷΰ���\n";
            wstring k;
            wcin >> k;
            Stance = L"Seller_Init";
        }

        // �Ǹ��� ������ڿ� �ŷ�
        else if (Stance == L"Seller_Trade") {
            
            // ������ڵ� �����ֱ�
            sql = L"select * from wholesaler;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"������� ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"������� �̸�: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"������� �ּ�: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"������� ��ȭ��ȣ: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"���� �ü�: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            vector<wstring> rec_Inputs;

            wcout << L"�ŷ� �� ������� ID�� �Է����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;
            rec_Inputs.push_back(Input);
            rec_Inputs.push_back(ID_Input);

            system("cls");

            sql = L"select pw_prodid, pw_cost, pw_remark from pw_recipt where pw_wid = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            // ����ǰ �̸�, �Ҹ� ���� ���� ȹ��
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
                wcout << L"����ǰ ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"����ǰ �̸�: " << ProdName[i] << L"\n";
                wcout << L"�����ڿ� �ŷ��� ����: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"�ŷ� ����: " << Unit[i] << L"\n";
                wcout << L"�����ڿ� �ŷ��� Ư�̻���: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"�ŷ��� ���깰 ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // ���� �ð� �Է�
            rec_Inputs.push_back(GetCurTime());

            wcout << L"�ŷ��Ͻ� ������ �ݾ�(����: ��)�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // ���� ������
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

            wcout << L"������ �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            wcout << L"Ư�̻����� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            sql = L"insert into wr_recipt values('" + rec_Inputs[0] + L"', '"
                + rec_Inputs[1] + L"', '" + rec_Inputs[2] + L"', '" + rec_Inputs[3] + L"', "
                + rec_Inputs[4] + L", '" + rec_Inputs[5] + L"', " + rec_Inputs[6] + L", '"
                + rec_Inputs[7] + L"');";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"���������� �ŷ��Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Seller_Init";
        }

        // �Ǹ��ڰ� ������ ��ǰ �̷� ��ȸ
        else if (Stance == L"Seller_Trace") {
            wcout << L"�����ü �̸��� �Է����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;

            sql = L"select * from wholesaler where whole_name = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"������� ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"������� �̸�: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"������� �ּ�: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"������� ��ȭ��ȣ: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"���� �ü�: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"������� ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            wcout << L"\n";

            // ������ ȹ��
            sql = L"select whole_facility from wholesaler where whole_id = '" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            wstring fac_loc = tableData.Tuples[0][0];

            // ������깰�� ���
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
                wcout << L"����ǰ ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"����ǰ �̸�: " << ProdName[i] << L"\n";
                wcout << L"�����ڿ� �ŷ��� ����: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"�ŷ� ����: " << Unit[i] << L"\n";
                wcout << L"�����ڿ� �ŷ��� Ư�̻���: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"�˻��ϰ��� �ϴ� ���깰 ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            wcout << L"\n";

            // ��깰, ���깰, ��깰�� ���� �ٸ� ���
            DB_Table prodTable;
            if (Input[8] == L'A') {
                sql = L"select * from agriculture where ag_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);

                sql = L"select product_item, product_kind from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodTable);               

                wcout << L"������ ID: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][0] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][1] << L"\n";
                wcout << L"������: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"���: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"����: " << tableData.Tuples[0][6] << L"\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[0][7] << L"\n";
                wcout << L"GAP ���� ����: " << tableData.Tuples[0][8] << L"\n";
                wcout << L"GMO ���� ����: " << tableData.Tuples[0][9] << L"\n";
            }
            else if (Input[8] == L'S') {
                sql = L"select * from seafood where sea_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);

                sql = L"select product_item, product_group from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodTable);

                wcout << L"������ ID: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][0] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][1] << L"\n";
                wcout << L"���: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"����: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[0][6] << L"\n";
                wcout << L"HACCP ���� ����: " << tableData.Tuples[0][7] << L"\n";
                wcout << L"GMO ���� ����: " << tableData.Tuples[0][8] << L"\n";
            }
            else if (Input[8] == L'L') {
                sql = L"select * from livestock where live_id = '" + Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableData);

                sql = L"select product_item, product_group from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(prodTable);

                wcout << L"������ ID: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][0] << L"\n";
                wcout << L"����ǰ��: " << prodTable.Tuples[0][1] << L"\n";
                wcout << L"����: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"���: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"����: " << tableData.Tuples[0][6] << L"\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[0][7] << L"\n";
                wcout << L"HACCP ���� ����: " << tableData.Tuples[0][8] << L"\n";
            }

            wcout << L"\n�̵����\n" << tableData.Tuples[0][3] << L"\n|\n|\n|\nV\n" << fac_loc << L"\n";

            wcout << L"�ƹ� Ű�� ���� �ڷΰ���\n";
            wstring k;
            wcin >> k;
            Stance = L"Seller_Init";
        }

        // ������ �޴�
        else if (Stance == L"Wholesaler_Init") {
            // �ڽ��� ���� ���
            sql = L"select * from wholesaler where whole_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            vector<wstring> title = { L"���̵�", L"��ü �̸�", L"�ּ�", L"��ȭ��ȣ", L"�����ü� �ּ�"};
            tableData.PrintRecord(title, 0);
            wcout << L"\n";

            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. ���� ����\n2. �ŷ� ���� Ȯ��\n3. �����ڿ� �ŷ�\n4. �α׾ƿ�\n�Է�: ";
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

        // ������ ����
        else if (Stance == L"Wholesaler_Modify") {
            wcout << L"�����Ͻ� ������ �����ΰ���?\n1. ��ȭ��ȣ\n2. �ּ�\n3. �̸�\n4. �����ü� �ּ�\n5. ��й�ȣ\n�Է�: ";
            wstring Input;
            wcin >> Input;
            // update sql ����
            if (stoi(Input) == 1) {
                wcout << L"�����Ͻ� ��ȭ��ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_phone = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"�����Ͻ� �ּҸ� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_address = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 3) {
                wcout << L"�����Ͻ� �̸��� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_name = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 4) {
                wcout << L"�����Ͻ� �����ü��� �ּҸ� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update wholesaler set whole_facility = '" + Input + L"' where whole_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 5) {
                wcout << L"�����Ͻ� ��й�ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update accout set acc_pw = '" + Input + L"' where acc_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"���������� �����Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Wholesaler_Init";
        }

        // �ŷ� ���� ����
        else if (Stance == L"Wholesaler_Receipt") {
            wcout << L"� �ŷ� ������ ��ȸ�Ͻǰǰ���?\n";
            wcout << L"1. �����ڿ��� �ŷ� ����\n2. �Ǹ��ڿ��� �ŷ� ����\n�Է�: ";
            wstring Input;
            wcin >> Input;
            if (stoi(Input) == 1) {
                Stance = L"Wholesaler_Receipt_Producer";
            }
            else if (stoi(Input) == 2) {
                Stance = L"Wholesaler_Receipt_Seller";
            }
        }

        // �Ǹ��ڿ��� �ŷ� ����
        else if (Stance == L"Wholesaler_Receipt_Seller") {
            // �ŷ� ���� ���̺� ��ȸ sql
            sql = L"select * from wr_recipt where wr_wid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            DB_Table tableBuffer;
            vector<wstring> Rname, ProdName;

            // �Ǹ��� �̸� ���ϱ�
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select ret_name from retailer where ret_id = '" + tableData.Tuples[i][1] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                Rname.push_back(tableBuffer.Tuples[0][0]);
            }

            // ����ǰ �̸� ���ϱ�
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
                wcout << L"�Ǹ���: " << Rname[i] << L"\n";
                wcout << L"�ŷ� ��ǰ: " << ProdName[i] << L"\n";
                wcout << L"�ŷ� ��¥: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"������ �ݾ�: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"Ư�̻���: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"�ƹ� Ű�� ���� �ڷΰ���\n";
            wstring k;
            wcin >> k;
            Stance = L"Wholesaler_Init";
        }

        // �����ڿ��� �ŷ� ����
        else if (Stance == L"Wholesaler_Receipt_Producer") {
             // �ŷ� ���� ���̺� ��ȸ sql
             sql = L"select * from pw_recipt where pw_wid = '" + ID_Input + L"';";
             DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
             DB.GetTableData(tableData);

             DB_Table tableBuffer;
             vector<wstring> Rname, ProdName;

             // ������ �̸� ���ϱ�
             for (int i = 0; i < tableData.Tuples.size(); i++) {
                 sql = L"select prod_name from producer where prod_id = '" + tableData.Tuples[i][1] + L"';";
                 DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                 DB.GetTableData(tableBuffer);

                 Rname.push_back(tableBuffer.Tuples[0][0]);
             }

             // ����ǰ �̸� ���ϱ�
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
                 wcout << L"������: " << Rname[i] << L"\n";
                 wcout << L"�ŷ� ��ǰ: " << ProdName[i] << L"\n";
                 wcout << L"�ŷ� ��¥: " << tableData.Tuples[i][3] << L"\n";
                 wcout << L"������ �ݾ�: " << tableData.Tuples[i][4] << L"\n";
                 wcout << L"����: " << tableData.Tuples[i][5] << L"\n";
                 wcout << L"����: " << tableData.Tuples[i][6] << L"\n";
                 wcout << L"Ư�̻���: " << tableData.Tuples[i][7] << L"\n";
                 wcout << L"------------------------------------------\n";
             }

            wcout << L"�ƹ� Ű�� ���� �ڷΰ���\n";
            wstring k;
            wcin >> k;
            Stance = L"Wholesaler_Init";
        }

        // ������� �ŷ�
        else if (Stance == L"Wholesaler_Trade") {
            // �����ڵ� �����ֱ�
            sql = L"select * from producer;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"------------------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"������ ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"������ �̸�: " << tableData.Tuples[i][1] << L"\n";
                wcout << L"������ �ּ�: " << tableData.Tuples[i][2] << L"\n";
                wcout << L"������ ��ȭ��ȣ: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            vector<wstring> rec_Inputs;

            wcout << L"�ŷ��� ������ ID�� �Է����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;
            rec_Inputs.push_back(ID_Input);
            rec_Inputs.push_back(Input);

            system("cls");

            // �������� ��� ���� ������깰 ���
            // product id ȹ��
            DB_Table tableBuffer;
            sql = L"select * from agriculture where ag_pid ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            wcout << L"��깰\n";
            wcout << L"-----------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select product_item, product_kind, product_wholesale_unit from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                wcout << L"��깰 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"��깰��: " << tableBuffer.Tuples[i][0] << L"\n";
                wcout << L"��깰 ǰ��: " << tableBuffer.Tuples[i][1] << L"\n";
                wcout << L"���� �ŷ� ����: " << tableBuffer.Tuples[i][2] << L"\n";
                wcout << L"������: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"��Ȯ ��¥: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"���: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"���� ����: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"GAP ���� ����: " << tableData.Tuples[i][8] << L"\n";
                wcout << L"GMO ���� ����: " << tableData.Tuples[i][9] << L"\n";
                wcout << L"-----------------------------\n";
            }
            sql = L"select * from seafood where sea_pid ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            wcout << L"���깰\n";
            wcout << L"-----------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {               
                sql = L"select product_item, product_kind, product_wholesale_unit from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                wcout << L"���깰 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"���깰��: " << tableBuffer.Tuples[i][0] << L"\n";
                wcout << L"���깰 ǰ��: " << tableBuffer.Tuples[i][1] << L"\n";
                wcout << L"���� �ŷ� ����: " << tableBuffer.Tuples[i][2] << L"\n";
                wcout << L"������: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"���: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"���� ����: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"HACCP ���� ����: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"GMO ���� ����: " << tableData.Tuples[i][8] << L"\n";
                wcout << L"-----------------------------\n";
            }
            sql = L"select * from livestock where live_pid ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);
            wcout << L"��깰\n";
            wcout << L"-----------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select product_item, product_kind, product_wholesale_unit from product where product_id = '" + tableData.Tuples[0][2] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                wcout << L"��깰 ID: " << tableData.Tuples[i][0] << L"\n";
                wcout << L"��깰��: " << tableBuffer.Tuples[i][0] << L"\n";
                wcout << L"��깰 ǰ��: " << tableBuffer.Tuples[i][1] << L"\n";
                wcout << L"���� �ŷ� ����: " << tableBuffer.Tuples[i][2] << L"\n";
                wcout << L"������: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"���: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"���� ����: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"HACCP ���� ����: " << tableData.Tuples[i][8] << L"\n";
                wcout << L"-----------------------------\n";
            }

            wcout << L"�ŷ��� ���깰 ID�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // ���� �ð� �Է�
            rec_Inputs.push_back(GetCurTime());

            wcout << L"�ŷ��Ͻ� ������ �ݾ�(����: ��)�� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            // ���� ������
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

            wcout << L"������ �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            wcout << L"Ư�̻����� �Է����ּ���.\n�Է�: ";
            wcin >> Input;
            rec_Inputs.push_back(Input);

            sql = L"insert into pw_recipt values('" + rec_Inputs[0] + L"', '"
                + rec_Inputs[1] + L"', '" + rec_Inputs[2] + L"', '" + rec_Inputs[3] + L"', "
                + rec_Inputs[4] + L", '" + rec_Inputs[5] + L"', " + rec_Inputs[6] + L", '"
                + rec_Inputs[7] + L"');";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"���������� �ŷ��Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Wholesaler_Init";
        }

        // ������ �޴�
        else if (Stance == L"Producer_Init") {
            // �ڽ��� ���� ���
            sql = L"select * from producer where prod_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            vector<wstring> title = { L"���̵�", L"�̸�", L"�ּ�", L"��ȭ��ȣ" };
            tableData.PrintRecord(title, 0);
            wcout << L"\n";

            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. ���� ����\n2. �ŷ� ���� Ȯ��\n3. ������깰 ���\n4. ������깰 ����\n5. �α׾ƿ�\n�Է�: ";
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

        // ������ ���� ����
        else if (Stance == L"Producer_Modify") {
            wcout << L"�����Ͻ� ������ �����ΰ���?\n1. ��ȭ��ȣ\n2. �ּ�\n3. �̸�\n4. ��й�ȣ\n�Է�: ";
            wstring Input;
            wcin >> Input;
            // update sql ����
            if (stoi(Input) == 1) {
                wcout << L"�����Ͻ� ��ȭ��ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update producer set prod_phone = '" + Input + L"' where prod_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"�����Ͻ� �ּҸ� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update producer set prod_address = '" + Input + L"' where prod_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 3) {
                wcout << L"�����Ͻ� �̸��� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update producer set prod_name = '" + Input + L"' where prod_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 4) {
                wcout << L"�����Ͻ� ��й�ȣ�� �����ּ���\n�Է�: ";
                wcin >> Input;
                sql = L"update accout set acc_pw = '" + Input + L"' where acc_id = '" + ID_Input + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            wcout << L"���������� �����Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        // ������ �ŷ� ����
        else if (Stance == L"Producer_Receipt") {
            sql = L"select * from pw_recipt where pw_pid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            DB_Table tableBuffer;
            vector<wstring> Wname, ProdName;

            // ������� �̸� ���ϱ�
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                sql = L"select whole_name from wholesaler where whole_id = '" + tableData.Tuples[i][0] + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                DB.GetTableData(tableBuffer);

                Wname.push_back(tableBuffer.Tuples[0][0]);
            }

            // ����ǰ �̸� ���ϱ�
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
                wcout << L"�������: " << Wname[i] << L"\n";
                wcout << L"�ŷ� ��ǰ: " << ProdName[i] << L"\n";
                wcout << L"�ŷ� ��¥: " << tableData.Tuples[i][3] << L"\n";
                wcout << L"������ �ݾ�: " << tableData.Tuples[i][4] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][5] << L"\n";
                wcout << L"����: " << tableData.Tuples[i][6] << L"\n";
                wcout << L"Ư�̻���: " << tableData.Tuples[i][7] << L"\n";
                wcout << L"------------------------------------------\n";
            }

            wcout << L"�ƹ� Ű�� ���� �ڷΰ���\n";
            wstring k;
            wcin >> k;
            Stance = L"Producer_Init";
        }

        // ������ ������깰 ���
        else if (Stance == L"Producer_Prod_Register") {
            wcout << L"����� ������깰 ǰ���� �����ּ���.\n�Է�: ";
            wstring Input;
            wcin >> Input;

            sql = L"select * from product where product_item ='" + Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"ǰ�� ���\n-----------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++)
            {
                wcout << L"���깰 ID: " << tableData.Tuples[0][0] << L"\n";
                wcout << L"ǰ���: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"ǰ�� �׷��: " << tableData.Tuples[0][2] << L"\n";
                wcout << L"ǰ����: " << tableData.Tuples[0][3] << L"\n";
                wcout << L"���� �ŷ� ����: " << tableData.Tuples[0][4] << L"\n";
                wcout << L"�Ҹ� �ŷ� ����: " << tableData.Tuples[0][5] << L"\n";
                wcout << L"-----------------------\n";
            }

            wcout << L"����� ������깰 ID�� �����ּ���.\n�Է�: ";
            wcin >> Input;

            wstring key = GetCurTime(true);
            vector<wstring> rec_info;

            rec_info.push_back(ID_Input);
            rec_info.push_back(Input);

            wcout << L"�������� ����ΰ���?\n�Է�: ";
            wcin >> Input;
            rec_info.push_back(Input);

            // ��깰, ��깰, ���깰�� ���� �ٸ� ���� �䱸
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

                // ���곯¥ ����
                rec_info.push_back(GetCurTime());

                Input.clear();
                wcout << L"����� ��� �ǳ���?\n�Է�: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"���Դ� ��� �ǳ���?\n�Է�: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"���� ��ġ�� ��� �ǳ���?\n�Է�: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"GAP ������ �޾ҳ���?\n1. ��\n2. �ƴϿ�\n�Է�: ";
                wcin >> Input;
                Input = stoi(Input) == 1 ? L"yes" : L"no";
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"GMO �ΰ���?\n1. ��\n2. �ƴϿ�\n�Է�: ";
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
                wcout << L"����� ��� �ǳ���?\n�Է�: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"���Դ� ��� �ǳ���?\n�Է�: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"���� ��ġ�� ��� �ǳ���?\n�Է�: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"HACCP ������ �޾ҳ���?\n1. ��\n2. �ƴϿ�\n�Է�: ";
                wcin >> Input;
                Input = stoi(Input) == 1 ? L"yes" : L"no";
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"GMO �ΰ���?\n1. ��\n2. �ƴϿ�\n�Է�: ";
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
                wcout << L"������ ��� �ǳ���?\n�Է�: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"����� ��� �ǳ���?\n�Է�: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"���Դ� ��� �ǳ���?\n�Է�: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"���� ��ġ�� ��� �ǳ���?\n�Է�: ";
                wcin >> Input;
                rec_info.push_back(Input);

                Input.clear();
                wcout << L"HACCP ������ �޾ҳ���?\n1. ��\n2. �ƴϿ�\n�Է�: ";
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

            wcout << L"���������� ó���Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        // ������ ������깰 ����
        else if (Stance == L"Producer_Prod_Modify") {
            wcout << L"� ���깰�� ������ ���ΰ���?\n1. ��깰\n2. ���깰\n3. ��깰\n�Է�: ";
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

        // ��깰 ����
        else if (Stance == L"Producer_Prod_Ag") {
            wstring Input;
            sql = L"select * from agriculture where ag_pid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"----------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"��깰 ID: " << tableData.Tuples[i][0] << "\n";
                wcout << L"����ǰ ID: " << tableData.Tuples[i][2] << "\n";
                wcout << L"������: " << tableData.Tuples[i][3] << "\n";
                wcout << L"������: " << tableData.Tuples[i][4] << "\n";
                wcout << L"���: " << tableData.Tuples[i][5] << "\n";
                wcout << L"����: " << tableData.Tuples[i][6] << "\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[i][7] << "\n";
                wcout << L"GAP ���� ����: " << tableData.Tuples[i][8] << "\n";
                wcout << L"GMO ���� ����: " << tableData.Tuples[i][9] << "\n";
                wcout << L"----------------------------------\n";
            }

            wstring product_id;
            wcout << L"�����Ͻ� ��깰 ID�� �Է��� �ּ���.\n�Է�: ";
            wcin >> product_id;
            wcout << L"�����Ͻ� ������ �����ΰ���?\n1. ������\n2. ����\n�Է�: ";
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"���� ��¥�� �������� ����˴ϴ�.\n";            
                sql = L"update agriculture set ag_date = '" + GetCurTime() + L"' where ag_id = '" + product_id + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"�����Ͻ� ���Ը� �Է��� �ּ���.\n�Է�: ";
                wcin >> Input;
                sql = L"update agriculture set ag_weight = '" + Input + L"' where ag_id = '" + product_id + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"���������� �����Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        // ���깰 ����
        else if (Stance == L"Producer_Prod_Sea") {
            wstring Input;
            sql = L"select * from seafood where sea_pid = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"----------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"���깰 ID: " << tableData.Tuples[i][0] << "\n";
                wcout << L"����ǰ ID: " << tableData.Tuples[i][2] << "\n";
                wcout << L"������: " << tableData.Tuples[i][3] << "\n";
                wcout << L"���: " << tableData.Tuples[i][4] << "\n";
                wcout << L"����: " << tableData.Tuples[i][5] << "\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[i][6] << "\n";
                wcout << L"HACCP ���� ����: " << tableData.Tuples[i][7] << "\n";
                wcout << L"GMO ���� ����: " << tableData.Tuples[i][8] << "\n";
                wcout << L"----------------------------------\n";
            }

            wstring product_id;
            wcout << L"�����Ͻ� ���깰 ID�� �Է��� �ּ���.\n�Է�: ";
            wcin >> product_id;
            wcout << L"�����Ͻ� ���Ը� �Է��� �ּ���.\n�Է�: ";
            wcin >> Input;
            sql = L"update seafood set sea_weight = '" + Input + L"' where sea_id = '" + product_id + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"���������� �����Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        // ��깰 ����
        else if (Stance == L"Producer_Prod_Live") {
            wstring Input;
            sql = L"select * from livestock where live_id = '" + ID_Input + L"';";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            DB.GetTableData(tableData);

            wcout << L"----------------------------------\n";
            for (int i = 0; i < tableData.Tuples.size(); i++) {
                wcout << L"��깰 ID: " << tableData.Tuples[i][0] << "\n";
                wcout << L"����ǰ ID: " << tableData.Tuples[i][2] << "\n";
                wcout << L"������: " << tableData.Tuples[i][3] << "\n";
                wcout << L"����: " << tableData.Tuples[i][4] << "\n";
                wcout << L"���: " << tableData.Tuples[i][5] << "\n";
                wcout << L"����: " << tableData.Tuples[i][6] << "\n";
                wcout << L"���� ��ġ: " << tableData.Tuples[i][7] << "\n";
                wcout << L"HACCP ���� ����: " << tableData.Tuples[i][8] << "\n";
                wcout << L"----------------------------------\n";
            }

            wstring product_id;
            wcout << L"�����Ͻ� ��깰 ID�� �Է��� �ּ���.\n�Է�: ";
            wcin >> product_id;
            wcout << L"�����Ͻ� ������ �����ΰ���?\n1. ����\n2. ����\n�Է�: ";
            wcin >> Input;
            if (stoi(Input) == 1) {
                wcout << L"�����Ͻ� ������ �Է��� �ּ���.\n�Է�: ";
                wcin >> Input;
                sql = L"update livestock set live_div = '" + Input + L"' where live_id = '" + product_id + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }
            else if (stoi(Input) == 2) {
                wcout << L"�����Ͻ� ���Ը� �Է��� �ּ���.\n�Է�: ";
                wcin >> Input;
                sql = L"update livestock set live_weight = '" + Input + L"' where live_id = '" + product_id + L"';";
                DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
            }

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"���������� �����Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Producer_Init";
        }

        // ������ �޴�
        else if (Stance == L"Admin_Init") {
            wcout << L"�̿��Ͻ� ����� �������ּ���.\n1. �ο� ��ȸ\n2. ������깰 �߰�\n3. �̿��� ��ȸ\n4. �α׾ƿ�\n�Է�: ";
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

        // �ο� ��ȸ
        else if (Stance == L"Admin_Report") {
            // �Ű� ���̺� ��ȸ
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
                    wcout << L"��깰 ID: " << tableBuffer.Tuples[i][0] << "\n";
                    wcout << L"����ǰ ID: " << tableBuffer.Tuples[i][2] << "\n";
                    wcout << L"������: " << tableBuffer.Tuples[i][3] << "\n";
                    wcout << L"������: " << tableBuffer.Tuples[i][4] << "\n";
                    wcout << L"���: " << tableBuffer.Tuples[i][5] << "\n";
                    wcout << L"����: " << tableBuffer.Tuples[i][6] << "\n";
                    wcout << L"���� ��ġ: " << tableBuffer.Tuples[i][7] << "\n";
                    wcout << L"GAP ���� ����: " << tableBuffer.Tuples[i][8] << "\n";
                    wcout << L"GMO ���� ����: " << tableBuffer.Tuples[i][9] << "\n";
                }
                else if (tableData.Tuples[i][0][8] == L'S') {
                    sql = L"select * from agriculture where ag_id = '" + tableData.Tuples[i][0] + L"';";
                    DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                    DB.GetTableData(tableBuffer);
                    wcout << L"���깰 ID: " << tableData.Tuples[i][0] << "\n";
                    wcout << L"����ǰ ID: " << tableData.Tuples[i][2] << "\n";
                    wcout << L"������: " << tableData.Tuples[i][3] << "\n";
                    wcout << L"���: " << tableData.Tuples[i][4] << "\n";
                    wcout << L"����: " << tableData.Tuples[i][5] << "\n";
                    wcout << L"���� ��ġ: " << tableData.Tuples[i][6] << "\n";
                    wcout << L"HACCP ���� ����: " << tableData.Tuples[i][7] << "\n";
                    wcout << L"GMO ���� ����: " << tableData.Tuples[i][8] << "\n";
                }
                else if (tableData.Tuples[i][0][8] == L'L') {
                    sql = L"select * from agriculture where ag_id = '" + tableData.Tuples[i][0] + L"';";
                    DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());
                    DB.GetTableData(tableBuffer);
                    wcout << L"��깰 ID: " << tableData.Tuples[i][0] << "\n";
                    wcout << L"����ǰ ID: " << tableData.Tuples[i][2] << "\n";
                    wcout << L"������: " << tableData.Tuples[i][3] << "\n";
                    wcout << L"����: " << tableData.Tuples[i][4] << "\n";
                    wcout << L"���: " << tableData.Tuples[i][5] << "\n";
                    wcout << L"����: " << tableData.Tuples[i][6] << "\n";
                    wcout << L"���� ��ġ: " << tableData.Tuples[i][7] << "\n";
                    wcout << L"HACCP ���� ����: " << tableData.Tuples[i][8] << "\n";
                }
                wcout << L"Ư�̻���: " << tableData.Tuples[i][1] << "\n";
                wcout << L"----------------------------------\n";
            }
            wcout << L"�ƹ� Ű�� ���� �ڷΰ���\n";
            wstring k;
            wcin >> k;
            Stance = L"Admin_Init";
        }

        // ������깰 �߰�
        else if (Stance == L"Admin_Product") {
            wstring Input;
            vector<wstring> In_data;
            wcout << L"�߰��� ���� �������� �������ּ���\n1. ��깰\n2. ���깰\n3. ��깰\n�Է�: ";
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
            wcout << L"����ǰ �̸��� �Է����ּ���\n�Է�: ";
            wcin >> Input;
            In_data.push_back(Input);
            wcout << L"����ǰ �׷��� �Է����ּ���\n�Է�: ";
            wcin >> Input;
            In_data.push_back(Input);
            wcout << L"����ǰ ǰ���� �Է����ּ���\n�Է�: ";
            wcin >> Input;
            In_data.push_back(Input);
            wcout << L"���� �ŷ� ������ �Է����ּ���\n�Է�: ";
            wcin >> Input;
            In_data.push_back(Input);
            wcout << L"�Ҹ� �ŷ� ������ �Է����ּ���\n�Է�: ";
            wcin >> Input;
            In_data.push_back(Input);
            sql = L"insert into product values('" + In_data[0] + L"','" + In_data[1] + L"','" + In_data[2] + L"','"
                + In_data[3] + L"','" + In_data[4] + L"','" + In_data[5] + L"');";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            sql = L"commit;";
            DB.ExecuteStatementDirect((SQLWCHAR*)sql.c_str());

            wcout << L"���������� �߰��Ǿ����ϴ�!";
            Sleep(2000);
            Stance = L"Admin_Init";
        }

        // �̿��� ��ȸ
        else if (Stance == L"Admin_User") {
            wstring Input;
            int printID = 1;
            wcout << L"ã���� ������� ��ȭ��ȣ�� Ű�� �Է����ּ���\n�Է�: ";
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
                wcout << L"������ ID: " << tableData.Tuples[0][0] << L"\n";
                wcout << L"������ �̸�: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"������ �ּ�: " << tableData.Tuples[0][2] << L"\n";
                wcout << L"������ ��ȭ��ȣ: " << tableData.Tuples[0][3] << L"\n";
            }
            else if (printID == 2) {
                wcout << L"�Ǹ��� ID: " << tableData.Tuples[0][0] << L"\n";
                wcout << L"�Ǹž�ü: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"�Ǹ��� �ּ�: " << tableData.Tuples[0][2] << L"\n";
                wcout << L"�Ǹ��� ��ȭ��ȣ: " << tableData.Tuples[0][3] << L"\n";
            }
            else {
                wcout << L"������� ID: " << tableData.Tuples[0][0] << L"\n";
                wcout << L"�����ü: " << tableData.Tuples[0][1] << L"\n";
                wcout << L"�����ü �ּ�: " << tableData.Tuples[0][2] << L"\n";
                wcout << L"�����ü ��ȭ��ȣ: " << tableData.Tuples[0][3] << L"\n";
                wcout << L"���� �ü� �ּ�: " << tableData.Tuples[0][4] << L"\n";
            }
            wcout << L"�ƹ� Ű�� ���� �ڷΰ���\n";
            wstring k;
            wcin >> k;
            Stance = L"Admin_Init";
        }

        // ���� ����
        else {
            system("cls");
            break;
        }
    }

    DB.DisconnectDataSource();
    return 0;
}