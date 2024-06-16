# 자주 까먹거나 자주 쓰이는 기법 정리

* 정렬 비교 구조체  
속도 문제로 왠만하면 const & 를 사용  
```c++
struct Cmp {
	bool operator() (const int& A, const int& B) { return A < B; }
};
sort(K.begin(), K.end(), Cmp());
```
&nbsp;  

* priority queue 사용법
```c++
// 기본 int에서의 사용
priority_queue<int, vector<int>, less<int>> pq; // 큰 것이 가장 위로
priority_queue<int, vector<int>, greater<int>> pq; // 작은 것이 가장 위로

struct Cmp {
	bool operator() (const int& A, const int& B) { return A < B; }
};
priority_queue<int, vector<int>, Cmp> pq; // 구조체 Cmp에 따라 달라짐
```
&nbsp;  

* 정사각 배열 회전  
```c++
void Rotate(vector<vector<int>>& mat) {
	int N = mat.size();
	for (int x = 0; x < N / 2; x++) {
		for (int y = x; y < N - x - 1; y++) {
			int temp = mat[x][y];
			mat[x][y] = mat[y][N - 1 - x];
			mat[y][N - 1 - x] = mat[N - 1 - x][N - 1 - y];
			mat[N - 1 - x][N - 1 - y] = mat[N - 1 - y][x];
			mat[N - 1 - y][x] = temp;
		}
	}
}
```
&nbsp;  

* 최대공약수, 최소공배수  
```c++
int Gcd(int a, int b) {
	int r = a % b;
	if (r == 0)
            return b;
	return Gcd(b, r);
}

int Lcm(int a, int b) {
	return a * b / Gcd(a, b);
}
```
3수의 최소공배수, c <= Lcm(a, b) 라고 가정  
ex. ```Lcm(Lcm(a, b), c)```  
&nbsp;  

* 에라토스테네스의 체 (3000번까지 소수 거르기)  
```c++
bool Prime[3001] = { 1,1,0, };

void Erathos() {
	for (int i = 4; i < 3001; i += 2)
		Prime[i] = 1;
	for (int i = 3; i <= sqrt(3000); i += 2) {
		if (Prime[i]) continue;
		for (int j = i * i; j < 3001; j += i)
			Prime[j] = 1;
	}
}
```
&nbsp;  

* 소수 판정  
```c++
bool IsPrime(int Num) {
    if (Num <= 1)
        return 0;
    if (!(Num % 2))
        return Num == 2;
    for (int i = 3; i <= sqrt(Num); i+=2) {
        if (!(Num % i))
            return 0;
    }
    return 1;
}
```
&nbsp;  

* 이진탐색
```c++
bool BinarySearch(vector<int>& arr, int len, int target){
	int low = 0, high = len - 1;
    
    while(low <= high){
    	int mid = (low + high) / 2;
        if(target == arr[mid])
			return true;
        if(target < arr[mid])
        	high = mid - 1;
        else if(target > arr[mid])
        	low = mid + 1;
    }
    return false;
}
```
&nbsp;  

* 플로이드 와샬, 징검다리 via는 항상 제일 밖의 루프  
```c++
for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
		for (int k = 1; k <= N; k++) 
			if (k != j)
				Dir[j][k] = min(Dir[j][k], Dir[j][i] + Dir[i][k]);
```