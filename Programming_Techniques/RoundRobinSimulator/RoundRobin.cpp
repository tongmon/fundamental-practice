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
	char* TaskName; // ���μ��� �̸�
	int CpuCycle; //  ���μ����� ó���Ǳ���� �ʿ��� CpuCycle
	int ArrivalTime; // ���μ��� ���� �ð�
public:
	Task() { TaskName = NULL; CpuCycle = -1; ArrivalTime = -1; } // �⺻ ������
	Task(char* a, int cycle, int time) // ������
	{
		TaskName = new char[strlen(a) + 1];
		strcpy_s(TaskName, strlen(a) + 1, a);
		CpuCycle = cycle;
		ArrivalTime = time;
	}
	~Task() { delete[]TaskName; }
	char* Getname() { return TaskName; } // ���μ��� �̸� ���
	int GetTime() { return ArrivalTime; } // ���μ��� ���� �ð� 
	int GetCycle() { return CpuCycle; } // ���μ��� �̸� ���
	void SetCycle(int a) { CpuCycle = a; } // ���μ��� �̸� ���
};

class ListNode :public Task
{
	friend class RoundRobin; // ���� �κ� ģ�� Ŭ���� ����
	friend class ReadyQueue; // ���� ť ģ�� Ŭ���� ����
private:
	ListNode* next; // ���� ��带 ����Ű�� ������
public:
	ListNode(char* a, int cycle, int time, ListNode* p = NULL) :Task(a, cycle, time) // ������
	{
		next = p;
	}
};

class ReadyQueue
{
	friend class RoundRobin; // ���� �κ� ģ�� Ŭ���� ����
	ListNode* front; // ť�� �� ���� ����Ű�� ��� ������
	ListNode* rear; // ť�� �� �ڸ� ����Ű�� ��� ������
public:
	ReadyQueue() :front(NULL), rear(NULL) {} // ������
	~ReadyQueue() // �Ҹ���
	{
		if (front != NULL)
		{
			// ���� ���� ���� �Ҵ�� ������ �����Ѵ�.
			ListNode* delpointer = front;
			while (front != NULL)
			{
				delpointer = front;
				front = front->next;
				delete delpointer;
			}
		}
	}
	void Insert(char* a, int cycle, int time); // ť ���� �Լ�
	int Qsize() // ���� ť�� ����ִ� ��尡 �� ������ �˾Ƴ��� �Լ�
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
	void Del(); // front�� ����Ű�� ��� ����
	void Del(ListNode* p); // ��� ������ p�� ����Ű�� Ư�� ��� ����
	void RtoR(); // Run to Ready��� ������ Run ���¿� �ִ� front ��带 ť�� �� �ڷ� ���� Ready ���·� ����� �ִ� �Լ��̴�.
};

class RoundRobin
{
	ReadyQueue* RobinQ; // ��� ������ ���μ������� ����ִ� ť(���������� front�� Run���·� ����Ѵ�.)
	ReadyQueue* TaskList; // ���� ReadyQueue�� �������� �ʾ����� ó���� ������ ���μ�����
	int Quantum; // ���� �κ� Ÿ�� ����
public:
	RoundRobin(int b) // Ÿ�� ������ �Է¹޴� ������
	{
		ReadyQueue* ptr = new ReadyQueue;
		RobinQ = ptr;
		ReadyQueue* p = new ReadyQueue;
		TaskList = p;
		Quantum = b;
	}
	~RoundRobin() // �Ҹ���
	{
		delete RobinQ;
		delete TaskList;
	}
	void MakeQ(); // �ܼ� â���� ���μ����� �Է¹޴� �Լ�
	void MakeInTxt(); // �ؽ�Ʈ ���Ͽ��� ���μ��� ������ �о���� �Լ�
	void Execute(); // ���� �κ� �����층���� ���μ��� ó�� ���� �Լ�
};

int main()
{
	int quantum = 0;
	while (1)
	{
		// Time Quantum �Է�
		cout << "���ϴ� Time Quantum�� �Է��Ͻÿ�(������ ms): ";
		cin >> quantum;
		if (quantum > 0)
		{
			break;
		}
		// Time Quantum�� 0 ���ϸ� �ٽ� �Է�
		cout << "Time Quantum�� 0 �̻��̿��� �մϴ�." << endl;
	}
	RoundRobin a(quantum);
	a.MakeInTxt();
	// �ֿܼ��� ���μ����� �Է¹ް� �ʹٸ� a.MakeInTxt()�� �ּ�ó���ϰ� a.MakeQ()�� Ȱ��ȭ
	//a.MakeQ();
	a.Execute();
	return 0;
}

void ReadyQueue::Insert(char* a, int cycle, int time)
{
	if (front == NULL) // ReadyQueue�� ���������
	{
		ListNode* ptr = new ListNode(a, cycle, time); // ������ ��� ����
		front = rear = ptr; // front�� rear�� ��� ���� ������ ���� ����
		return;
	}
	// ReadyQueue�� ���Ұ� �̹� �����ϰ� ������
	ListNode* ptr = new ListNode(a, cycle, time); // ������ ��� ����
	rear->next = ptr; // rear �ڿ� ����
	rear = ptr; // rear�� �� �ڷ� �ٽ� �ٲ��.
}

void ReadyQueue::Del()
{
	ListNode* delpointer = front; // ������ ���� front
	if (front == NULL) // ReadyQueue�� ���������
	{
		cout << "ReadyQueue is empty" << endl;
		return;
	}
	if (front == rear) // ReadyQueue�� ��尡 1����
	{
		front = rear = NULL;
	}
	else // ReadyQueue�� ��尡 2�� �̻��̸�
	{
		front = front->next;
	}
	delete delpointer; // �ش� ��� ����
}

void ReadyQueue::Del(ListNode* p)
{
	if (p == NULL || front == NULL) // p�� front�� NULL�̸� ����
	{
		cout << "Void Deletion" << endl;
		return;
	}
	if (p == front) // p�� front�� Del() ����
	{
		Del();
		return;
	}
	// �� ���ǿ� �ش� ������ ���ٸ� ������ ����� �� ��带 ã�´�.
	ListNode* ptr = front;
	while (ptr->next != p)
	{
		ptr = ptr->next;
	}
	if (p == rear) // ������ ��尡 �� ���̿��ٸ� rear�� ����
	{
		rear = ptr;
	}
	ptr->next = p->next;
	delete p;
}

void ReadyQueue::RtoR()
{
	if (front == NULL) // ReadyQueue�� ���������
	{
		cout << "ReadyQueue is empty" << endl;
		return;
	}
	if (front == rear) // ReadyQueue�� ��尡 1�� ���̸�
	{
		return;
	}
	ListNode* goback = front; // �� �ճ�� ����
	front = front->next; // �� �ճ�尡 �� �ڷ� ����Ǵ� front�� ����
	rear->next = goback; // ���� front�� �� �ڷ� ����ȴ�.
	rear = rear->next; // �� �� ��尡 �ٲ�� rear�� ����
	goback->next = NULL; // �� �� ���� �׻� NULL�� ����Ų��.
}

void RoundRobin::MakeQ()
{
	char name[256] = { 0, }; // ���μ��� �̸�
	int cycle = 0, time = 0; // CpuCycle�� ���� �ð� ���� ����
	while (1) // exit �Ǳ� ������ ���� ����
	{
		cout << "ó���� ���μ��� ������ �Է��մϴ�. ����ÿ� ���μ��� �̸��� exit�� �Է��Ͻÿ�. " << endl;
		cout << "���μ��� �̸�: "; cin >> name;
	back_1:
		if (strcmp(name, "exit") == 0)
		{
			if (TaskList->Qsize() == 0) // ���α׷� ����
			{
				exit(1);
			}
			// ���μ����� ������ ��� �Է� �Ǿ����� while�� Ż��
			system("cls");
			break;
		}
		ListNode* p = TaskList->front;
		while (p != NULL)
		{
			if (strcmp(p->Getname(), name) == 0)
			{
				cout << "�̸��� ���� ���μ����� �ֽ��ϴ�." << endl;
				goto back_1;
			}
			p = p->next;
		}
	back_2:
		cout << "���μ��� ó���ҿ�ð�(ms): "; cin >> cycle;
		if (cycle <= 0) // CpuCycle�� 0���� Ŀ���Ѵ�.
		{
			cout << "�߸��� �Է�!" << endl;
			goto back_2;
		}
		cout << "���μ��� ���� �ð�(ms): "; cin >> time;
		if (time < 0) // ���� �ð��� 0���� ���� �� ����.
		{
			cout << "�߸��� �Է�!" << endl;
			goto back_2;
		}
		/*
		// ���μ��� ���� �ð��� �ߺ��� ����ϰ� ���� �ʴٸ� �� �ּ��� Ȱ��ȭ�ϸ� �ȴ�.
		ListNode* ptr = TaskList->front;
		while (ptr != NULL)
		{
			if (ptr->GetTime() == time)
			{
				cout << "�����ð��� ���� ���μ����� �����մϴ�!" << endl;
				goto back_2;
			}
			ptr = ptr->next;
		}
		*/
		TaskList->Insert(name, cycle, time); // ���μ��� ���� ����
		system("cls"); // ȭ�� �����
	}
}

void RoundRobin::MakeInTxt()
{
	char path[256] = { 0, }; // txt ���� ���
back:
	cout << "ó���� ���μ������� ������ ��� txt���� ���(���� �� exit): ";
	cin >> path;

	if (strcmp("exit", path) == 0) // exit�� ����
	{
		exit(1);
	}

	ifstream robin(path); // path ��δ�� ���� ����
	if (robin.is_open()) // ��������
	{
		int i = 0;
		while (!robin.eof()) // ������ ���� �����ϱ� ���̸�
		{
			char buffer[256]; // ���� �� �� �޾ƿ��� ����
			robin.getline(buffer, 256); // �� �� �޾Ƽ� ���ۿ� ����
			i++;
			if (i > 2) // �ؽ�Ʈ ���Ͽ��� 2���� ���� �������̱⿡ �ǳʶڴ�.  
			{
				int index = 0, k = 0, j = 0;
				char info[3][256]; // info[0]�� ���μ��� �̸�, info[1]�� CpuCycle, info[2]�� ArrivalTime�� ����.
				while (buffer[index] != '\0')
				{
					if (buffer[index] == ' ' || buffer[index] == '	') // ����� ���� �������� ��ū�� ������.
					{
						index++;
					}
					else // ����� ���� �ƴϸ�
					{
						while (buffer[index] != '\0' && buffer[index] != ' ' && buffer[index] != '	')
						{
							info[k][j++] = buffer[index++]; // info ����
						}
						info[k][j] = '\0';
						k++; j = 0;
					}
				}
				// ���μ��� ID �ߺ� üũ
				ListNode* p = TaskList->front;
				while (p != NULL)
				{
					if (strcmp(p->Getname(), info[0]) == 0)
					{
						cout << "�̸��� ���� ���μ����� �ֽ��ϴ�. txt�� �ٽ� �ۼ����ּ���." << endl;
						exit(1);
					}
					p = p->next;
				}
				int cycle = atoi(info[1]); // info[1] ���ڷ� ��ȯ			
				int time = atoi(info[2]); // info[2] ���ڷ� ��ȯ
				if (cycle <= 0 || time < 0)
				{
					cout << "CpuCycle�̳� ArrivalTime�� ���� �ùٸ��� �ʽ��ϴ�. txt�� �ٽ� �ۼ����ּ���." << endl;
					exit(1);
				}
				/*
				// ���μ��� ���� �ð��� �ߺ��� ����ϰ� ���� �ʴٸ� �� �ּ��� Ȱ��ȭ�ϸ� �ȴ�.
				ListNode* ptr = TaskList->front;
				while (ptr != NULL)
				{
					if (ptr->GetTime() == time)
					{
						cout << "���� �ð��� ���� ���μ����� �����մϴ�. txt�� �ٽ� �ۼ����ּ���." << endl;
						exit(1);
					}
					ptr = ptr->next;
				}
				*/
				TaskList->Insert(info[0], cycle, time); // ����
			}
		}
		robin.close(); // ���� �ݱ�
	}
	else // �ƴϸ�
	{
		cout << "ã�� ������ �����ϴ�." << endl;
		goto back;
	}
}

void RoundRobin::Execute()
{
	int Time = 0; // �ð� ����, ������ ms�� �Ѵ�.
	int index = 0; // ��� ��� ������ ��Ÿ���� ���� �迭 �ε���
	int ArySize = TaskList->Qsize(); // ��� ��� ������ ��Ÿ���� ���� �迭 ũ��
	int Qlimit = 0; // Ÿ�� ���� ī����
	int flag = 0; // �ٸ��� ����(���� ���۳� ���ʿ��� ����� ���̱� ���� ���δ�)
	bool idle = true; // cpu�� idle �������� üũ �÷���

	// ���μ������� ó���� ������ ����� ����ϱ� ���� ������ �迭
	char** Name = new char* [ArySize]; // ���μ��� �̸� �迭
	int* ArrivalTime = new int[ArySize]; // ���μ��� ���� �ð� �迭
	int* Cpucycle = new int[ArySize]; // ���μ��� CpuCycle �迭
	int* Turnaround = new int[ArySize]; // Turnaround �迭
	int* WaitingTime = new int[ArySize]; // ��� �ð� �迭
	int* CompletionTime = new int[ArySize]; // �۾� �Ϸ� �ð� �迭
	int* ResponseTime = new int[ArySize]; // ���� �ð� �迭

	// ���� ������ �ʱ�ȭ
	for (int i = 0; i < ArySize; i++)
	{
		Cpucycle[i] = Turnaround[i] = CompletionTime[i] = ResponseTime[i] = WaitingTime[i] = ArrivalTime[i] = 0;
	}

	char filename[30]; // ���� �̸��� ����� �迭
	FileName(filename, 30); // ���� �ð��� �������� ���� �̸� ����
	ofstream result(filename); // �ؽ�Ʈ ���� ����

	// ����� �۾� ����� �۾� ���� �ð��� ���� ���
	result << "ó���� ���μ�����" << endl;
	result << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	while (TaskList->front != NULL) // ���� �ð��� ���� ������ �����ؼ� ��� ���� �迭�� �־��ش�.
	{
		ListNode* q = TaskList->front;
		ListNode* ptr = q;
		flag = q->GetTime();
		while (q != NULL)
		{
			if (flag > q->GetTime())
			{
				flag = q->GetTime(); // ���� ���� ���� �ð��� ����
				ptr = q;
			}
			q = q->next;
		}
		Name[index] = new char[strlen(ptr->Getname()) + 1];
		strcpy_s(Name[index], strlen(ptr->Getname()) + 1, ptr->Getname());
		ArrivalTime[index] = ptr->GetTime();
		Cpucycle[index] = ptr->GetCycle();
		TaskList->Del(ptr);
		// ó���� ���μ����� ���� ���
		result << "���μ���: " << Name[index] << " | " << "Cpu Cycle: " << Cpucycle[index] << "(ms) | " << "���μ��� ���� �ð�: " << ArrivalTime[index] << "(ms)" << endl;
		index++;
	}
	result << "---------------------------------------------------------------------------------------------------------------------------------" << endl;

	result << "\n��Ʈ��Ʈ\n" << endl;
	index = flag = 0;
	// ���� while������ RoundRobin �����층 �۵��Ѵ�. 
	while (index < ArySize || RobinQ->front != NULL) // �迭�� �ε����� ArySize��ŭ ��� RobinQ�� ������ �ǰ� ��� ó���Ǿ� RobinQ�� ����ִ� ���μ����� ������ Ż��
	{
		for (int i = index; index < ArySize; i++) // ���� �ð����� ������ ���ĵ� ���μ������� 
		{
			if (ArrivalTime[i] == Time) // ���� �ð��� �Ǹ� RobinQ�� �������ش�.
			{
				RobinQ->Insert(Name[i], Cpucycle[i], ArrivalTime[i]);
				index++;
			}
			else // ���� �ð� ������ ������ �Ǿ��⿡ ���� �ð��� �ƴϸ� Ż��
			{
				break;
			}
		}
		if (RobinQ->front == NULL) // ��Ʈ ��Ʈ���� Cpu�� Idle������ ��� ����( |    | )���� ǥ���Ͽ���. 
		{
			result << "|    ";
			idle = true;
		}
		else if (RobinQ->front != NULL) // �κ� ť�� �����ϸ�
		{
			if (RobinQ->front->GetCycle() <= 0) // ���μ����� CpuCycle�� 0�� �Ǿ� ó���� ���� �� �̻� ������ 
			{
				for (int i = 0; i < index; i++) // ���� ���� ���μ����̱⿡ ���� ���μ������� ���� �� �ִ� ��� �������� �����Ѵ�. 
				{
					if (strcmp(RobinQ->front->Getname(), Name[i]) == 0) // ���μ��� �̸��� ������
					{
						Turnaround[i] = Time - RobinQ->front->GetTime(); // ���μ����� ���� �ð����� ���� �ð��� �� Turnaround�� ��´�.
						WaitingTime[i] = Turnaround[i] - Cpucycle[i]; // Turnaround���� CpuCycle�� �� ��� �ð��� ��´�.
						CompletionTime[i] = Time; // ���μ����� ���� �ð��� �����Ѵ�.
						break;
					}
				}
				RobinQ->Del(); // ���� ���μ����� ����
				flag = Qlimit = 0; // �÷���, Ÿ�� ���� �ʱ�ȭ
				result << "| " << Time << "(ms)" << " ";
			}
			else if (Qlimit == Quantum) // Ÿ�� ���� �ð��� �Ǿ� �۾��� �ٲپ��ش�.
			{
				RobinQ->RtoR(); // Running ���¿��� Ready ���·� ��ȯ�Ͽ� ť�� �� ������ �Ű��ش�.
				flag = Qlimit = 0; // �÷���, Ÿ�� ���� �ʱ�ȭ
				if (RobinQ->Qsize() != 1) // ��� ������ �۾��� ������ Ÿ�� ������ �Ǿ ��Ʈ��Ʈ�� �ð��� ǥ������ �ʾҴ�.
				{
					result << "| " << Time << "(ms)" << " ";
				}
			}
		}
		if (RobinQ->front != NULL) // �κ� ť�� �����ϸ�
		{
			if (idle == true) // cpu idle ���¿��� ����� �ð��� �����ش�.
			{
				idle = false;
				result << "| " << Time << "(ms)" << " ";
			}
			result << "| " << RobinQ->front->Getname() << " ";
			// ResponseTime�� ���ϱ� ���� front����� ó�� ������ CpuCycle�� ���� CpuCycle�� ������ �˻��Ѵ�.
			for (int i = 0; i < index && flag == 0; i++)
			{
				if (strcmp(RobinQ->front->Getname(), Name[i]) == 0) // ���μ��� �̸��� ����
				{
					flag = 1; // Ÿ�� ���� ���� ������ �ٽ� �˻��� �ʿ䰡 ���� �÷��׸� �ѳ��.
					if (RobinQ->front->GetCycle() == Cpucycle[i]) // CpuCycle�� �ʹ� ���¿� ���ٸ� ó�� ó���Ǵ� ���μ����̴�.
					{
						ResponseTime[i] = Time - ArrivalTime[i]; // ���� �ð����� ���μ��� ���� �ð��� ���־� ResponseTime�� ��´�.
					}
				}
			}
			int Cycle = RobinQ->front->GetCycle() - 1; // ���μ����� ó���Ǳ⿡ ����Ŭ�� �Ѱ�(1ms) �����Ѵ�.
			RobinQ->front->SetCycle(Cycle); // �Ѱ� ������ ����Ŭ�� �ٽ� Set ���ش�.
			Qlimit++; // Ÿ�� ���� ����
		}
		Time++; // �ð� ���� (1ms ����)
	}
	result << "|" << endl;
	double AvgTurnaround = 0; // ��� Turnaround ���� ����
	double AvgWaiting = 0; // ��� ��� �ð� ���� ����
	double AvgResponse = 0; // ��� ���� �ð� ���� ����
	for (int i = 0; i < ArySize; i++) // ����� ���ϱ����� ���Ѵ�.
	{
		AvgTurnaround = AvgTurnaround + Turnaround[i];
		AvgWaiting = AvgWaiting + WaitingTime[i];
		AvgResponse = AvgResponse + ResponseTime[i];
	}
	// ArySize�� ������ �ֱ�
	AvgTurnaround = AvgTurnaround / (double)ArySize;
	AvgWaiting = AvgWaiting / (double)ArySize;
	AvgResponse = AvgResponse / (double)ArySize;

	// ���Ͽ� ��ü ��� ���
	result << "\n���μ��� ó�� �� ���" << endl;
	result << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < ArySize; i++)
	{
		result << "���μ���: " << Name[i] << " | " << "���μ��� �Ϸ� �ð�: " << CompletionTime[i] << "(ms) | " << "Turnaround: " << Turnaround[i] <<
			"(ms) | " << "Waiting Time: " << WaitingTime[i] << "(ms) | " << "Response Time: " << ResponseTime[i] << "(ms)" << endl;
	}
	result << "��� Turnaround: " << AvgTurnaround << "(ms)" << endl;
	result << "��� Waiting Time: " << AvgWaiting << "(ms)" << endl;
	result << "��� Response Time: " << AvgResponse << "(ms)" << endl;
	result << "Time Quantum: " << Quantum << "(ms)" << endl;
	result << "---------------------------------------------------------------------------------------------------------------------------------" << endl;

	// ���� �Ҵ��� ������ ����
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

	cout << "��� ���μ��� ó�� �Ϸ�!" << endl;
	cout << filename << "���� ����� Ȯ���غ�����." << endl;
}

void FileName(char ary[], int size)
{
	if (size < 26) // �̸��� �־��ֱ⿡ �迭�� �ʹ� ������
	{
		cout << "���� �̸��� �����ϱ� ���� �迭 ũ�Ⱑ �ʹ� �۽��ϴ�!" << endl;
		return;
	}
	ary[0] = ary[1] = 'R';
	ary[2] = '_';
	char aryTime[6][6]; // ��, ��, ��, ��, ��, �ʰ� ����� �迭
	int k = 3; // �̹� "RR_"�� �� �ֱ⿡ 3���� ����
	int tk = 0; // aryTime �迭�� �ε���

	time_t Curtime;

	struct tm Time_obj; // �ð� ǥ�ø� ���� ����ü

	Curtime = time(NULL); // 1970�� 1�� 1�� ���� ���ʰ� ���������� ����Ͽ� ����

	// ���� �ð��� �������� tm ����ü�� ���� �ð� ����
	localtime_s(&Time_obj, &Curtime);

	// ��� �ð� �������� char�迭�� ����
	_itoa_s(Time_obj.tm_year + 1900, aryTime[0], 6, 10); // ��
	_itoa_s(Time_obj.tm_mon + 1, aryTime[1], 6, 10); // ��
	_itoa_s(Time_obj.tm_mday, aryTime[2], 6, 10); // ��
	_itoa_s(Time_obj.tm_hour, aryTime[3], 6, 10); // ��
	_itoa_s(Time_obj.tm_min, aryTime[4], 6, 10); // ��
	_itoa_s(Time_obj.tm_sec, aryTime[5], 6, 10); // ��

	for (int i = 0; i < 6; i++)
	{
		tk = 0;
		while (aryTime[i][tk] != '\0') // aryTime�� �о ary�� �ִ´�.
		{
			ary[k++] = aryTime[i][tk++];
		}
		if (i == 2) // ��¥�� �ð��� �����ϱ� ���� ������
		{
			ary[k++] = '_';
		}
		else if (i < 5) // ��, ��, ��, ��, ��, �� ������
		{
			ary[k++] = '-';
		}
	}
	// �������� ".txt" �־��ֱ�
	ary[k++] = '.';
	ary[k++] = 't';
	ary[k++] = 'x';
	ary[k++] = 't';
	ary[k] = '\0';
}