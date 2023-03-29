# Iterator Pattern   

복잡한 데이터일수록 순회와 관련된 문제가 발생한다.  
해당 문제를 해결하기 위해 반복자 패턴이 많이 사용된다.  
반복자는 순회를 하기위해 사용되기에 ```다음 항목으로 이동```, ```비교```만 정의해주면 된다.  
따라서 ```++, !=``` 연산자만 재정의해주면 된다.   
&nbsp;  

## 표준 라이브러리 반복자  

```c++
    std::vector<std::string> vec{"tongstar", "gyungjun", "james", "spongebob"};
    std::vector<std::string>::iterator first = vec.begin();

    std::string str_first = *first;

    auto second = ++first;

    auto iter = vec.begin();
    while (iter != vec.end())
    {
        // do something...
        iter++;
    }

    for (auto iter = vec.begin(); iter != vec.end(); iter++)
    {
        // do something...
    }

    for (auto iter = std::begin(vec); iter != std::end(vec); iter++)
    {
        // do something...
    }

    for (auto iter = vec.rbegin(); iter != vec.rend(); iter++)
    {
        // do something...
    }

    std::vector<std::string>::const_iterator const_iter = vec.cbegin();

    std::vector<std::string>::const_reverse_iterator const_rev_iter = vec.crbegin();
```