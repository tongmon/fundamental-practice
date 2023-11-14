부분 특수화, 명시적 특수화

https://learn.microsoft.com/ko-kr/cpp/cpp/template-specialization-cpp?view=msvc-170



- 템플릿 템플릿 파라미터 예시들

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

인자가 여러개인 경우

```
template <typename K, typename V, template <typename...> class R>
inline std::vector<std::wstring> GetFilteredData(const std::wstring &target, const R<K, V> &data)
{
    std::vector<std::wstring> ret;
    auto lower = data.lower_bound(target);
    for (auto iter = lower; iter != data.end(); iter++)
    {
        std::wstring_view searched = iter->first;

        if (target.size() > searched.size())
            break;
        for (int i = 0; i < target.size(); i++)
        {
            if (target[i] != searched[i])
                return ret;
        }
        ret.emplace_back(searched);
    }
    return ret;
}
```
