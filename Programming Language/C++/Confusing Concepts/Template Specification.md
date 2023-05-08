부분 특수화, 명시적 특수화

https://learn.microsoft.com/ko-kr/cpp/cpp/template-specialization-cpp?view=msvc-170



- 템플릿의 템플릿

```c++
template <typename T, template <typename V> class R>
void push_and_pop(std::vector<Node<T>*>& poped, R<T>& st, int num)
{
	for (int i = 0; i < num; i++)
		st.push(i);
	for (int i = 0; i < num; i++)
		poped.push_back(st.pop());
}

template <typename T, template <typename V> class R>
void print_stack_performance(R<T>& st, int stack_size = 8000000)
{
	clock_t start_time, end_time;
	double result = 0;
	std::vector<Node<T>*> poped[8];

	start_time = clock();
	std::vector<std::thread> ths;
	for (int i = 0; i < 8; i++)
		ths.push_back(std::thread(push_and_pop<T, R>, std::ref(poped[i]), std::ref(st), stack_size / 8));
	for (auto& th : ths)
		th.join();
	end_time = clock();
	result = (double)(end_time - start_time) / 1e3;

	std::cout << "Time Spand: " << result << "s\n";
	std::cout << "Stack Size: " << st.size() << "\n";

	for (int i = 0; i < 8; i++)
		for (const auto& ptr : poped[i])
			delete ptr;
}

int main()
{
	lfstack<int> lock_free_st;
	std::cout << "Lock free stack test!\n";
	print_stack_performance(lock_free_st);
}
```