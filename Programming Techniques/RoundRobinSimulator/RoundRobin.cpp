#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

// Made by tongstar

void FileName(char ary[], int size);

class ReadyQueue; 
class RoundRobin;

class Task
{
	char* TaskName; // 프로세스 이름
	int CpuCycle; //  프로세스가 처리되기까지 필요한 CpuCycle
	int ArrivalTime; // 프로세스 도착 시간
public:
	Task() { TaskName = NULL; CpuCycle = -1; ArrivalTime = -1; } // 기본 생성자
	Task(char* a, int cycle, int time) // 생성자
	{
		TaskName = new char[strlen(a) + 1];
		strcpy_s(TaskName, strlen(a) + 1, a);
		CpuCycle = cycle;
		ArrivalTime = time;
	}
	~Task() { delete[]TaskName; }
	char* Getname() { return TaskName; } // 프로세스 이름 얻기
	int GetTime() { return ArrivalTime; } // 프로세스 도착 시간 
	int GetCycle() { return CpuCycle; } // 프로세스 이름 얻기
	void SetCycle(int a) { CpuCycle = a; } // 프로세스 이름 얻기
};

class ListNode :public Task
{
	friend class RoundRobin; // 라운드 로빈 친구 클래스 선언
	friend class ReadyQueue; // 레디 큐 친구 클래스 선언
private:
	ListNode* next; // 다음 노드를 가리키는 포인터
public:
	ListNode(char* a, int cycle, int time, ListNode* p = NULL) :Task(a, cycle, time) // 생성자
	{
		next = p;
	}
};

class ReadyQueue
{
	friend class RoundRobin; // 라운드 로빈 친구 클래스 선언
	ListNode* front; // 큐의 맨 앞을 가리키는 노드 포인터
	ListNode* rear; // 큐의 맨 뒤를 가리키는 노드 포인터
public:
	ReadyQueue() :front(NULL), rear(NULL) {} // 생성자
	~ReadyQueue() // 소멸자
	{
		if (front != NULL)
		{
			// 차례 차례 동적 할당된 노드들을 해제한다.
			ListNode* delpointer = front;
			while (front != NULL)
			{
				delpointer = front;
				front = front->next;
				delete delpointer;
			}
		}
	}
	void Insert(char* a, int cycle, int time); // 큐 삽입 함수
	int Qsize() // 현재 큐에 들어있는 노드가 몇 개인지 알아내는 함수
	{
		int size = 0;
		ListNode* p = front;
		while (p != NULL)
		{
			p = p->next;
			size++;
		}
		return size;
	}
	void Del(); // front가 가리키는 노드 제거
	void Del(ListNode* p); // 노드 포인터 p가 가리키는 특정 노드 제거
	void RtoR(); // Run to Ready라는 뜻으로 Run 상태에 있는 front 노드를 큐의 맨 뒤로 보내 Ready 상태로 만들어 주는 함수이다.
};

class RoundRobin
{
	ReadyQueue* RobinQ; // 대기 상태의 프로세스들이 담겨있는 큐(예외적으로 front는 Run상태로 취급한다.)
	ReadyQueue* TaskList; // 아직 ReadyQueue에 도착하진 않았지만 처리될 예정인 프로세스들
	int Quantum; // 라운드 로빈 타임 퀀텀
public:
	RoundRobin(int b) // 타임 퀀텀을 입력받는 생성자
	{
		ReadyQueue* ptr = new ReadyQueue;
		RobinQ = ptr;
		ReadyQueue* p = new ReadyQueue;
		TaskList = p;
		Quantum = b;
	}
	~RoundRobin() // 소멸자
	{
		delete RobinQ;
		delete TaskList;
	}
	void MakeQ(); // 콘솔 창에서 프로세스를 입력받는 함수
	void MakeInTxt(); // 텍스트 파일에서 프로세스 정보를 읽어오는 함수
	void Execute(); // 라운드 로빈 스케쥴링으로 프로세스 처리 실행 함수
};

int main()
{
	int quantum = 0;
	while (1)
	{
		// Time Quantum 입력
		cout << "원하는 Time Quantum을 입력하시오(단위는 ms): ";
		cin >> quantum;
		if (quantum > 0)
		{
			break;
		}
		// Time Quantum이 0 이하면 다시 입력
		cout << "Time Quantum은 0 이상이여야 합니다." << endl;
	}
	RoundRobin a(quantum);
	a.MakeInTxt();
	// 콘솔에서 프로세스를 입력받고 싶다면 a.MakeInTxt()를 주석처리하고 a.MakeQ()를 활성화
	//a.MakeQ();
	a.Execute();
	return 0;
}

void ReadyQueue::Insert(char* a, int cycle, int time)
{
	if (front == NULL) // ReadyQueue가 비어있으면
	{
		ListNode* ptr = new ListNode(a, cycle, time); // 새로은 노드 생성
		front = rear = ptr; // front와 rear를 모두 새로 생성한 노드로 지정
		return;
	}
	// ReadyQueue에 원소가 이미 존재하고 있으면
	ListNode* ptr = new ListNode(a, cycle, time); // 새로은 노드 생성
	rear->next = ptr; // rear 뒤에 삽입
	rear = ptr; // rear도 맨 뒤로 다시 바뀐다.
}

void ReadyQueue::Del()
{
	ListNode* delpointer = front; // 지워질 노드는 front
	if (front == NULL) // ReadyQueue가 비어있으면
	{
		cout << "ReadyQueue is empty" << endl;
		return;
	}
	if (front == rear) // ReadyQueue의 노드가 1개면
	{
		front = rear = NULL;
	}
	else // ReadyQueue의 노드가 2개 이상이면
	{
		front = front->next;
	}
	delete delpointer; // 해당 노드 삭제
}

void ReadyQueue::Del(ListNode* p)
{
	if (p == NULL || front == NULL) // p나 front가 NULL이면 오류
	{
		cout << "Void Deletion" << endl;
		return;
	}
	if (p == front) // p가 front면 Del() 실행
	{
		Del();
		return;
	}
	// 위 조건에 해당 사항이 없다면 삭제할 노드의 앞 노드를 찾는다.
	ListNode* ptr = front;
	while (ptr->next != p)
	{
		ptr = ptr->next;
	}
	if (p == rear) // 삭제할 노드가 맨 끝이였다면 rear값 변경
	{
		rear = ptr;
	}
	ptr->next = p->next;
	delete p;
}

void ReadyQueue::RtoR()
{
	if (front == NULL) // ReadyQueue가 비어있으면
	{
		cout << "ReadyQueue is empty" << endl;
		return;
	}
	if (front == rear) // ReadyQueue에 노드가 1개 뿐이면
	{
		return;
	}
	ListNode* goback = front; // 맨 앞노드 설정
	front = front->next; // 맨 앞노드가 맨 뒤로 변경되니 front도 변경
	rear->next = goback; // 예전 front가 맨 뒤로 변경된다.
	rear = rear->next; // 맨 뒤 노드가 바뀌니 rear도 변경
	goback->next = NULL; // 맨 뒷 노드는 항상 NULL을 가리킨다.
}

void RoundRobin::MakeQ()
{
	char name[256] = { 0, }; // 프로세스 이름
	int cycle = 0, time = 0; // CpuCycle과 도착 시간 저장 버퍼
	while (1) // exit 되기 전까지 무한 루프
	{
		cout << "처리할 프로세스 정보를 입력합니다. 종료시에 프로세스 이름에 exit를 입력하시오. " << endl;
		cout << "프로세스 이름: "; cin >> name;
	back_1:
		if (strcmp(name, "exit") == 0)
		{
			if (TaskList->Qsize() == 0) // 프로그램 종료
			{
				exit(1);
			}
			// 프로세스들 정보가 모두 입력 되었으면 while문 탈출
			system("cls");
			break;
		}
		ListNode* p = TaskList->front;
		while (p != NULL)
		{
			if (strcmp(p->Getname(), name) == 0)
			{
				cout << "이름이 같은 프로세스가 있습니다." << endl;
				goto back_1;
			}
			p = p->next;
		}
	back_2:
		cout << "프로세스 처리소요시간(ms): "; cin >> cycle;
		if (cycle <= 0) // CpuCycle은 0보다 커야한다.
		{
			cout << "잘못된 입력!" << endl;
			goto back_2;
		}
		cout << "프로세스 도착 시간(ms): "; cin >> time;
		if (time < 0) // 도착 시간은 0보다 작을 수 없다.
		{
			cout << "잘못된 입력!" << endl;
			goto back_2;
		}
		/*
		// 프로세스 도착 시간의 중복을 허용하고 싶지 않다면 이 주석을 활성화하면 된다.
		ListNode* ptr = TaskList->front;
		while (ptr != NULL)
		{
			if (ptr->GetTime() == time)
			{
				cout << "도착시간이 같은 프로세스가 존재합니다!" << endl;
				goto back_2;
			}
			ptr = ptr->next;
		}
		*/
		TaskList->Insert(name, cycle, time); // 프로세스 정보 삽입
		system("cls"); // 화면 지우기
	}
}

void RoundRobin::MakeInTxt()
{
	char path[256] = { 0, }; // txt 파일 경로
back:
	cout << "처리할 프로세스들의 정보가 담긴 txt파일 경로(종료 시 exit): ";
	cin >> path;

	if (strcmp("exit", path) == 0) // exit면 종료
	{
		exit(1);
	}

	ifstream robin(path); // path 경로대로 파일 열기
	if (robin.is_open()) // 열렸으면
	{
		int i = 0;
		while (!robin.eof()) // 파일의 끝에 도달하기 전이면
		{
			char buffer[256]; // 파일 한 줄 받아오는 버퍼
			robin.getline(buffer, 256); // 한 줄 받아서 버퍼에 저장
			i++;
			if (i > 2) // 텍스트 파일에서 2줄은 정보 제공용이기에 건너뛴다.  
			{
				int index = 0, k = 0, j = 0;
				char info[3][256]; // info[0]은 프로세스 이름, info[1]은 CpuCycle, info[2]는 ArrivalTime이 담긴다.
				while (buffer[index] != '\0')
				{
					if (buffer[index] == ' ' || buffer[index] == '	') // 공백과 탭을 기준으로 토큰이 나뉜다.
					{
						index++;
					}
					else // 공백과 탭이 아니면
					{
						while (buffer[index] != '\0' && buffer[index] != ' ' && buffer[index] != '	')
						{
							info[k][j++] = buffer[index++]; // info 저장
						}
						info[k][j] = '\0';
						k++; j = 0;
					}
				}
				// 프로세스 ID 중복 체크
				ListNode* p = TaskList->front;
				while (p != NULL)
				{
					if (strcmp(p->Getname(), info[0]) == 0)
					{
						cout << "이름이 같은 프로세스가 있습니다. txt를 다시 작성해주세요." << endl;
						exit(1);
					}
					p = p->next;
				}
				int cycle = atoi(info[1]); // info[1] 숫자로 변환			
				int time = atoi(info[2]); // info[2] 숫자로 변환
				if (cycle <= 0 || time < 0)
				{
					cout << "CpuCycle이나 ArrivalTime의 값이 올바르지 않습니다. txt를 다시 작성해주세요." << endl;
					exit(1);
				}
				/*
				// 프로세스 도착 시간의 중복을 허용하고 싶지 않다면 이 주석을 활성화하면 된다.
				ListNode* ptr = TaskList->front;
				while (ptr != NULL)
				{
					if (ptr->GetTime() == time)
					{
						cout << "도착 시각이 같은 프로세스가 존재합니다. txt를 다시 작성해주세요." << endl;
						exit(1);
					}
					ptr = ptr->next;
				}
				*/
				TaskList->Insert(info[0], cycle, time); // 삽입
			}
		}
		robin.close(); // 파일 닫기
	}
	else // 아니면
	{
		cout << "찾는 파일이 없습니다." << endl;
		goto back;
	}
}

void RoundRobin::Execute()
{
	int Time = 0; // 시간 변수, 단위는 ms로 한다.
	int index = 0; // 결과 출력 정보를 나타내기 위한 배열 인덱스
	int ArySize = TaskList->Qsize(); // 결과 출력 정보를 나타내기 위한 배열 크기
	int Qlimit = 0; // 타임 퀀텀 카운터
	int flag = 0; // 다목적 변수(정렬 버퍼나 불필요한 계산을 줄이기 위해 쓰인다)
	bool idle = true; // cpu가 idle 상태인지 체크 플래그

	// 프로세스들의 처리가 끝나고 결과를 출력하기 위한 변수들 배열
	char** Name = new char* [ArySize]; // 프로세스 이름 배열
	int* ArrivalTime = new int[ArySize]; // 프로세스 도착 시각 배열
	int* Cpucycle = new int[ArySize]; // 프로세스 CpuCycle 배열
	int* Turnaround = new int[ArySize]; // Turnaround 배열
	int* WaitingTime = new int[ArySize]; // 대기 시간 배열
	int* CompletionTime = new int[ArySize]; // 작업 완료 시각 배열
	int* ResponseTime = new int[ArySize]; // 반응 시각 배열

	// 동적 변수들 초기화
	for (int i = 0; i < ArySize; i++)
	{
		Cpucycle[i] = Turnaround[i] = CompletionTime[i] = ResponseTime[i] = WaitingTime[i] = ArrivalTime[i] = 0;
	}

	char filename[30]; // 파일 이름이 저장될 배열
	FileName(filename, 30); // 현재 시각을 기준으로 파일 이름 생성
	ofstream result(filename); // 텍스트 파일 생성

	// 저장된 작업 목록을 작업 도착 시각에 따라 출력
	result << "처리할 프로세스들" << endl;
	result << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	while (TaskList->front != NULL) // 도착 시각이 빠른 순으로 정렬해서 결과 정보 배열에 넣어준다.
	{
		ListNode* q = TaskList->front;
		ListNode* ptr = q;
		flag = q->GetTime();
		while (q != NULL)
		{
			if (flag > q->GetTime())
			{
				flag = q->GetTime(); // 가장 빠른 도착 시각을 저장
				ptr = q;
			}
			q = q->next;
		}
		Name[index] = new char[strlen(ptr->Getname()) + 1];
		strcpy_s(Name[index], strlen(ptr->Getname()) + 1, ptr->Getname());
		ArrivalTime[index] = ptr->GetTime();
		Cpucycle[index] = ptr->GetCycle();
		TaskList->Del(ptr);
		// 처리될 프로세스들 정보 출력
		result << "프로세스: " << Name[index] << " | " << "Cpu Cycle: " << Cpucycle[index] << "(ms) | " << "프로세스 도착 시각: " << ArrivalTime[index] << "(ms)" << endl;
		index++;
	}
	result << "---------------------------------------------------------------------------------------------------------------------------------" << endl;

	result << "\n간트차트\n" << endl;
	index = flag = 0;
	// 밑의 while문에서 RoundRobin 스케쥴링 작동한다. 
	while (index < ArySize || RobinQ->front != NULL) // 배열의 인덱스가 ArySize만큼 모두 RobinQ에 삽입이 되고 모두 처리되어 RobinQ에 들어있는 프로세스가 없으면 탈출
	{
		for (int i = index; index < ArySize; i++) // 도착 시각별로 위에서 정렬된 프로세스들을 
		{
			if (ArrivalTime[i] == Time) // 도착 시각이 되면 RobinQ에 삽입해준다.
			{
				RobinQ->Insert(Name[i], Cpucycle[i], ArrivalTime[i]);
				index++;
			}
			else // 도착 시각 순으로 정렬이 되었기에 같은 시각이 아니면 탈출
			{
				break;
			}
		}
		if (RobinQ->front == NULL) // 간트 차트에서 Cpu가 Idle상태일 경우 공백( |    | )으로 표현하였다. 
		{
			result << "|    ";
			idle = true;
		}
		else if (RobinQ->front != NULL) // 로빈 큐가 존재하면
		{
			if (RobinQ->front->GetCycle() <= 0) // 프로세스의 CpuCycle이 0이 되어 처리할 것이 더 이상 없으면 
			{
				for (int i = 0; i < index; i++) // 이제 끝난 프로세스이기에 끝난 프로세스에서 얻을 수 있는 결과 정보들을 저장한다. 
				{
					if (strcmp(RobinQ->front->Getname(), Name[i]) == 0) // 프로세스 이름이 같으면
					{
						Turnaround[i] = Time - RobinQ->front->GetTime(); // 프로세스가 끝난 시각에서 도착 시각을 빼 Turnaround를 얻는다.
						WaitingTime[i] = Turnaround[i] - Cpucycle[i]; // Turnaround에서 CpuCycle을 빼 대기 시간을 얻는다.
						CompletionTime[i] = Time; // 프로세스가 끝난 시각을 저장한다.
						break;
					}
				}
				RobinQ->Del(); // 끝난 프로세스는 제거
				flag = Qlimit = 0; // 플래그, 타임 퀀텀 초기화
				result << "| " << Time << "(ms)" << " ";
			}
			else if (Qlimit == Quantum) // 타임 퀀텀 시간이 되어 작업을 바꾸어준다.
			{
				RobinQ->RtoR(); // Running 상태에서 Ready 상태로 전환하여 큐의 맨 끝으로 옮겨준다.
				flag = Qlimit = 0; // 플래그, 타임 퀀텀 초기화
				if (RobinQ->Qsize() != 1) // 대기 상태인 작업이 없으면 타임 퀀텀이 되어도 간트차트에 시간을 표시하지 않았다.
				{
					result << "| " << Time << "(ms)" << " ";
				}
			}
		}
		if (RobinQ->front != NULL) // 로빈 큐가 존재하면
		{
			if (idle == true) // cpu idle 상태에서 벗어나면 시간을 적어준다.
			{
				idle = false;
				result << "| " << Time << "(ms)" << " ";
			}
			result << "| " << RobinQ->front->Getname() << " ";
			// ResponseTime을 구하기 위해 front노드의 처음 상태의 CpuCycle과 현재 CpuCycle이 같은지 검사한다.
			for (int i = 0; i < index && flag == 0; i++)
			{
				if (strcmp(RobinQ->front->Getname(), Name[i]) == 0) // 프로세스 이름이 같고
				{
					flag = 1; // 타임 퀀텀 범위 내에서 다시 검사할 필요가 없게 플래그를 켜논다.
					if (RobinQ->front->GetCycle() == Cpucycle[i]) // CpuCycle도 초반 상태와 같다면 처음 처리되는 프로세스이다.
					{
						ResponseTime[i] = Time - ArrivalTime[i]; // 현재 시각에서 프로세스 도착 시각을 빼주어 ResponseTime을 얻는다.
					}
				}
			}
			int Cycle = RobinQ->front->GetCycle() - 1; // 프로세스가 처리되기에 사이클이 한개(1ms) 감소한다.
			RobinQ->front->SetCycle(Cycle); // 한개 감소한 사이클로 다시 Set 해준다.
			Qlimit++; // 타임 퀀텀 증가
		}
		Time++; // 시간 증가 (1ms 증가)
	}
	result << "|" << endl;
	double AvgTurnaround = 0; // 평균 Turnaround 저장 변수
	double AvgWaiting = 0; // 평균 대기 시간 저장 변수
	double AvgResponse = 0; // 평균 반응 시각 저장 변수
	for (int i = 0; i < ArySize; i++) // 평균을 구하기위해 더한다.
	{
		AvgTurnaround = AvgTurnaround + Turnaround[i];
		AvgWaiting = AvgWaiting + WaitingTime[i];
		AvgResponse = AvgResponse + ResponseTime[i];
	}
	// ArySize로 나누어 주기
	AvgTurnaround = AvgTurnaround / (double)ArySize;
	AvgWaiting = AvgWaiting / (double)ArySize;
	AvgResponse = AvgResponse / (double)ArySize;

	// 파일에 전체 결과 출력
	result << "\n프로세스 처리 후 결과" << endl;
	result << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < ArySize; i++)
	{
		result << "프로세스: " << Name[i] << " | " << "프로세스 완료 시각: " << CompletionTime[i] << "(ms) | " << "Turnaround: " << Turnaround[i] <<
			"(ms) | " << "Waiting Time: " << WaitingTime[i] << "(ms) | " << "Response Time: " << ResponseTime[i] << "(ms)" << endl;
	}
	result << "평균 Turnaround: " << AvgTurnaround << "(ms)" << endl;
	result << "평균 Waiting Time: " << AvgWaiting << "(ms)" << endl;
	result << "평균 Response Time: " << AvgResponse << "(ms)" << endl;
	result << "Time Quantum: " << Quantum << "(ms)" << endl;
	result << "---------------------------------------------------------------------------------------------------------------------------------" << endl;

	// 동적 할당한 변수들 해제
	for (int i = 0; i < ArySize; i++)
	{
		delete[]Name[i];
	}
	delete[]Name;
	delete[]Turnaround;
	delete[]CompletionTime;
	delete[]ArrivalTime;
	delete[]WaitingTime;
	delete[]ResponseTime;
	delete[]Cpucycle;

	result.close();

	cout << "모든 프로세스 처리 완료!" << endl;
	cout << filename << "에서 결과를 확인해보세요." << endl;
}

void FileName(char ary[], int size)
{
	if (size < 26) // 이름을 넣어주기에 배열이 너무 작으면
	{
		cout << "파일 이름을 생성하기 위한 배열 크기가 너무 작습니다!" << endl;
		return;
	}
	ary[0] = ary[1] = 'R';
	ary[2] = '_';
	char aryTime[6][6]; // 년, 월, 일, 시, 분, 초가 저장될 배열
	int k = 3; // 이미 "RR_"이 들어가 있기에 3부터 시작
	int tk = 0; // aryTime 배열의 인덱스

	time_t Curtime;

	struct tm Time_obj; // 시간 표시를 위한 구조체

	Curtime = time(NULL); // 1970년 1월 1일 이후 몇초가 지났는지를 계산하여 저장

	// 지역 시간을 기준으로 tm 구조체에 현재 시각 저장
	localtime_s(&Time_obj, &Curtime);

	// 모든 시간 변수들을 char배열로 변경
	_itoa_s(Time_obj.tm_year + 1900, aryTime[0], 6, 10); // 년
	_itoa_s(Time_obj.tm_mon + 1, aryTime[1], 6, 10); // 월
	_itoa_s(Time_obj.tm_mday, aryTime[2], 6, 10); // 일
	_itoa_s(Time_obj.tm_hour, aryTime[3], 6, 10); // 시
	_itoa_s(Time_obj.tm_min, aryTime[4], 6, 10); // 분
	_itoa_s(Time_obj.tm_sec, aryTime[5], 6, 10); // 초

	for (int i = 0; i < 6; i++)
	{
		tk = 0;
		while (aryTime[i][tk] != '\0') // aryTime을 읽어서 ary에 넣는다.
		{
			ary[k++] = aryTime[i][tk++];
		}
		if (i == 2) // 날짜와 시각을 구분하기 위한 구분자
		{
			ary[k++] = '_';
		}
		else if (i < 5) // 년, 월, 일, 시, 분, 초 구분자
		{
			ary[k++] = '-';
		}
	}
	// 마지막에 ".txt" 넣어주기
	ary[k++] = '.';
	ary[k++] = 't';
	ary[k++] = 'x';
	ary[k++] = 't';
	ary[k] = '\0';
}