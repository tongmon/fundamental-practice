# Catch2 라이브러리로 C++에서 Unit Test 하기

일단 Catch2는 C++ 프로젝트의 단위 테스트, 벤치마킹을 도와주는 오픈 소스 라이브러리이다.  
v2 버전까지는 header-only 라이브러리였지만 기능이 많이 추가된 v3 부터는 헤더 파일만 포함해서는 작동하지 않으니 CMake의 FetchContent나 Vcpkg 등을 이용하자.  
사용법은 VSCode_Catch2_Project 프로젝트 구성을 따라 설명하겠다.  
Catch2는 CMake를 구성으로 하는 것을 추천하므로 해당 프로젝트는 VSCode와 CMake를 이용한다.  
해당 프로젝트는 밑과 같이 구성되어 있다.  
```
VSCode_Catch2_Project
|- App
	|- CMakelists.txt
	|- main.cpp
|- Libs
	|- MyBenchMark
		|- CMakelists.txt
		|- mybenchmark.cpp
		|- mybenchmark.h
	|- MyMath
		|- CMakelists.txt
		|- mymath.cpp
		|- mymath.h
	|- CMakelists.txt
|- Tests
	|- BenchmarkTest
		|- CMakelists.txt
		|- main.cpp
	|- UnitTest
		|- CMakelists.txt
		|- main.cpp
	|- CMakelists.txt
|- CMakelists.txt
|- Makefile
```
```App```은 단위 테스트와 상관없는 실제 릴리즈될 프로그램의 메인 exe를 산출한다.  
```Libs```는 라이브러리들의 구성요소가 담겨있는 폴더이다.  
```MyBenchMark```는 Catch2를 통해 벤치마킹 비교를 할 함수들이 정의되어 있다.  
```MyMath```에는 살짝의 오류 케이스가 있는 펙토리얼, 소수 판정 함수가 정의되어 있다.  
```Tests```에는 유닛 테스트를 할 프로젝트들이 담겨있다.  
```UnitTest``` 프로젝트는 Catch2의 REQUIRE를 활용해 단위 테스트를 진행한다.  
```BenchmarkTest``` 프로젝트는 Catch2의 BENCHMARK를 통해 함수의 퍼포먼스를 알아낸다.  
  
VSCode_Catch2_Project 프로젝트를 빌드하기 위해서는 ```clang```, ```ninja```가 사전에 설치되어 있어야 하며 ```CMakePresets.json``` 기반으로 빌드 세팅이 구성되어 있기에 VS Code 사용이 권장된다.  

빌드 후 ```UnitTest``` 타겟을 실행하면 단위 테스트가 수행되고 ```BenchmarkTest``` 타겟을 실행하면 벤치마크가 수행된다.  
  
VSCode_Catch2_Project 프로젝트에서 Catch2를 사용하기 위해 유의할 점만 설명한다.  
나머지 자잘한 CMake C++ 프로젝트에 근본적으로 필요한 부분은 스킵한다.  
  
* ```VSCode_Catch2_Project/CMakelists.txt```에서 볼 점은 밑과 같이 Catch2 라이브러리를 빌드 종속성에 추가하는 것이다.
	```cmake
	Include(FetchContent)

	FetchContent_Declare(
	  Catch2
	  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	  GIT_TAG        v3.2.1
	)

	FetchContent_MakeAvailable(Catch2)
	```

* MyMath 프로젝트를 보면 ```is_prime()``` 함수와 ```factorial()``` 함수가 있다.  
```factorial()``` 함수는 팩토리얼 값을 반환하는데 0이 인자로 주어진 경우 0을 반환하는 결함이 있다.  
```is_prime()``` 함수는 소수 판정 함수인데 짝수를 소수로 판정해버리는 결함이 있다.  
  
* UnitTest 프로젝트는 MyMath 함수들을 테스트하기 위한 코드로 이루어져 있다.  
일단 UnitTest/CMakelists.txt를 보면 ```target_link_libraries(${TEST_MAIN} PUBLIC ${MATH_LIBRARY_NAME} Catch2::Catch2WithMain)``` 부분이 있을 것인데 테스트에 사용할 라이브러리와 Catch2를 종속성으로 추가해야 한다.  
Catch2를 종속성으로 추가할 때 종류가 2가지 있는데 하나는 Catch2::Catch2이고 나머지는 Catch2::Catch2WithMain이다.   
```Catch2::Catch2WithMain```를 사용하면 Catch2의 main 함수를 사용하여 테스트를 진행한다는 것이고 ```Catch2::Catch2```를 사용하면 프로젝트 독자적인 main 함수를 사용하여 테스트 한다는 것이다.  
여기선 따로 main 함수를 구축하지 않고 Catch2의 main 함수를 이용하기 위해 ```Catch2::Catch2WithMain```를 사용한다.  
UnitTest/main.cpp를 보면 Catch2를 사용하기 위해 ```#include <catch2/catch_all.hpp>``` 헤더파일을 포함한다.  
```TEST_CASE("테스트 시 출력될 문구", "[함수 이름]")```으로 테스트 케이스를 구성하고 그 속에 REQUIRE를 통해 함수 테스트를 진행한다.  
UnitTest 프로젝트를 실행해보면 터미널 창에서 Catch2가 ```REQUIRE(factorial(0) == 1);``` 이 부분과 ```REQUIRE(is_prime(4) == false);``` 이 부분을 오류로 잡아낼 것이다.  

* MyBenchmark 프로젝트를 보면 ```is_prime_01()``` 함수와 ```is_prime_02()``` 함수가 있다.  
```is_prime_01()```, ```is_prime_02()``` 모두 소수 판별 함수지만 작동 방식이 다르다.  
보통의 경우 ```is_prime_01()``` 함수가 빠를 것이고 ```is_prime_02()``` 함수는 첫 소수 판별시에만 느리다.  

* BenchmarkTest 프로젝트는 MyBenchMark 함수들의 속도를 비교하기 위한 코드로 이루어져 있다.  
대부분의 내용은 UnitTest의 구성방식과 동일하다.  
BenchmarkTest/main.cpp 부분이 조금 다른데 ```TEST_CASE()``` 내부에 ```BENCHMARK()```를 통해 함수 퍼포먼스를 측정한다. (꼭 return 값이 있는 함수일 필요는 없다.)  
BenchmarkTest 프로젝트를 실행해보면 터미널 창에서 Catch2가 각 ```BENCHMARK()```에 대해서 최소, 최대 수행 시간을 출력해준다.  

더 자세한 사용법은 https://github.com/catchorg/Catch2/tree/devel/docs 여기를 참고하자.  