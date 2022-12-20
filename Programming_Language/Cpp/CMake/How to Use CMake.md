# Windows 10 이상에서 CMake를 사용하는 법

&NewLine;
## CMakeLists.txt 문법
&NewLine;

* **주석처리**  
CMakeLists.txt에서 주석은 #으로 달아준다.  
ex. ```# 이건 CMake 파일이다!!```

* **cmake_minimum_required**  
CMake의 최소 사용 버전을 설정해준다.  
ex. ```cmake_minimum_required(VERSION 3.16)```  

* **project**  
현재 프로젝트의 속성과 관련된 정보를 적는다.  
예를 들어 ```project(CppProjectTemplate VERSION 1.0.0 LANGUAGES C CXX)``` 이렇게 적혔다면 프로젝트 이름은 CppProjectTemplate이고 해당 프로젝트의 버전은 1.0.0이며 프로젝트에서 쓰이는 언어는 C 또는 CXX(C++)이다.  
ex. ```project(CppProjectTemplate VERSION 1.0.0 LANGUAGES C CXX)```

* **add_executable**   
실행 파일을 만드는데 사용되는 모든 파일들(.cpp만)을 적는다.  
꼭 앞에 실행 파일의 이름을 적어주어야 한다.  
```add_executable(MyExecutable main.cpp)``` 이렇게 하면 MyExecutable.exe를 만들겠다는 것이다.  
ex. ```add_executable(MyExecutable main.cpp sdl_drawer.cpp)```

* **add_library**  
라이브러리를 만들기 위한 명령이다.  
현재 프로젝트에 종속될 라이브러리와 관련된 파일들(.cpp만)을 적는다.  
꼭 앞에 생성될 라이브러리 이름과 링크 방식을 적어야 한다.  
예를 들어 ```add_library(MyLibrary STATIC my_lib.cpp)``` 이렇게 적었다면 정적 링크(STATIC)할 MyLibrary 이름을 가진 라이브러리를 생성하는데 필요한 파일은 my_lib.cpp라는 것이다.  
ex. ```add_library(MyLibrary STATIC my_lib.cpp my_math.cpp)```

> **위에 서술한 ```add_library()``` 함수를 올바르게 사용하려면 3가지 옵션에 대한 설명을 알아야 한다.**  
> - STATIC 옵션  
> 정적 라이브러리를 생성하기 위한 옵션이다.  
> 크로스 플랫폼 개발이라면 해당 옵션이 좋다.  
> 보통 .lib, .a 확장자가 붙는다.
>   
> - SHARED 옵션  
> 공유 라이브러리를 생성하기 위한 옵션이다.
> 라이브러리 코드를 재사용하기 쉬워 좋다.
> 어플리케이션이 메모리에 로드되는 시점에 링크된다.
> 보통 .dll, .so 확장자가 붙는다. 
>   
> - MODULE 옵션   
> 공유 라이브러리와 유사하지만 특정 플랫폼에서 링커로 링크할 수 없다.  
> ```dlopen``` 기능을 사용하여 런타임에 동적으로 로드할 수는 있다.  
> Windows 플랫폼에서는 그냥 .dll로 작동한다.  

* **link_libraries**  
링크할 라이브러리 파일 목록을 정의한다.  
CMakeList에서 빌드된 라이브러리의 경우 .lib와 같은 확장자를 떼고 사용해도 된다.  
ex. ```link_libraries(MyLib.lib MyLib2)```

* **link_directories** 
링크할 라이브러리 포함 폴더 위치를 정의한다.  
ex. ```link_directories(../lib ../lib2)```

* **include_directories**   
헤더파일 포함 폴더 위치를 정의한다.  
ex. ```include_directories(../include ../include2)```

> 타겟이 따로 지정되지 않은 경우 설정하는 ```link_libraries()```, ```link_directories()```, ```include_directories()``` 함수들 말고 밑에 서술할 target이 정해져 있는 ```target_link_libraries()```, ```target_link_directories()```, ```target_include_directories()``` 함수들이 Modern CMake에서 추천된다.

* **target_link_libraries**  
실행 파일이 원활하게 실행될 수 있게 관련된 라이브러리를 링크 시키기 위한 명령이다.  
예를 들어 ```target_link_libraries(MyExecutable PUBLIC MyLibrary)```를 하면 MyExecutable 실행 파일에 MyLibrary 라이브러리가 PUBLIC으로 링크된다.  
ex. ```target_link_libraries(MyExecutable PUBLIC MyLibrary)```

> **위에 서술한 ```target_link_libraries()``` 함수를 올바르게 사용하려면 3가지 옵션에 대한 설명을 알아야 한다. 클래스 상속 관계와 유사하다.**  
> - PUBLIC 옵션  
> PUBLIC으로 종속된 라이브러리는 상위 어디든 사용이 가능하다.  
> ```<---```는 종속 순서를 의미한다.   
> 즉 ```target_link_libraries(MyLib0 PUBLIC MyLib1)```이면 ```MyLib0 <--- MyLib1[PUBLIC]```이다.  
> ex. ```MyLib0 <--- MyLib1[PUBLIC | PRIVATE | INTERFACE] <--- MyLib2[PUBLIC]``` => MyLib0은 MyLib2 사용 가능  
> 
> - PRIVATE 옵션  
> PRIVATE으로 종속된 라이브러리는 PRIVATE로 종속하는 경우에만 사용이 가능하다.   
> ex. ```MyLib0 <--- MyLib1[PRIVATE] <--- MyLib2[PRIVATE]``` => MyLib0은 MyLib2 사용 가능  
> ex. ```MyLib0 <--- MyLib1[PUBLIC | INTERFACE] <--- MyLib2[PRIVATE]``` => MyLib0은 MyLib2 사용 불가  
> 
> - INTERFACE 옵션  
> 헤더 파일로만 구성된 라이브러리를 종속할 때 사용된다.  
> 그 외에는 PUBLIC으로 작동할 때랑 똑같다.  

* **target_link_directories**
종속 라이브러리들을 정의하기 손쉽게 하기 위해 사용하는 명령이다.  
어떤 라이브러리를 생성하는 ```add_library(MyLibrary 어쩌구저쩌구...)```가 있다고 하자.  
여기서 ```target_link_directories(MyLibrary PUBLIC "C:/CMakeProject/lib")```도 추가적으로 있다고 하면 MyLibrary를 종속하는 모든 빌드 모듈은 ```link_directories("C:/CMakeProject/lib")```를 한 효과를 지닌다.  
ex. ```target_link_directories(MyLibrary PUBLIC "C:/CMakeProject/lib")```

* **target_include_directories**   
헤더 파일을 정의하기 손쉽게 하기 위해 사용하는 명령이다.  
어떤 라이브러리를 생성하는 ```add_library(MyLibrary 어쩌구저쩌구...)```가 있다고 하자.  
여기서 ```target_include_directories(MyLibrary PUBLIC "C:/CMakeProject/include")```도 추가적으로 있다고 하면 MyLibrary를 종속하는 모든 빌드 모듈은 ```include_directories("C:/CMakeProject/include")```를 한 효과를 지닌다.  
ex. ```target_include_directories(MyLibrary PUBLIC "C:/CMakeProject/include")```

* **add_dependencies**   
직접적으로 의존성을 정의한다.  
target_link_libraries로도 충분하기 때문에 잘 안쓴다.  
정 써야한다면 exe간의 의존성을 정의할 때나 CMake 내부에서 의존성 파악이 어려운 파일들에 사용할 수는 있다.  
ex. ```add_dependencies(<Target_이름> <의존_대상> <의존_대상> ...)```

* **add_subdirectory**  
하위 폴더에 빌드 관련 CMakeLists.txt가 있는 경우 이를 인식하도록 상위 폴더의 CMakeLists.txt에 add_subdirectory를 해주어야 한다.  
CMake가 파일을 타고 타고 내려갈 때 꼭 필요한 명령이기 때문에 파일이 따로 없고 폴더만 포함하는 폴더에도 CMakeLists.txt 파일을 만들어 줘야 한다.  
그리고 더 중요한 것은 add_subdirectory 명령의 순서이다.  
만약 app 폴더 내부에 있는 파일들이 MyExecutable이라는 실행 파일을 만드는데 해당 실행 파일이 MyLibrary라는 라이브러리를 요구한다고 해보자.  
근데 MyLibrary는 src 폴더 내부에 있는 파일들을 통해 생성된다.  
이 경우 app 폴더와 src 폴더를 모두 가지고 있는 상위 폴더에서는 MyLibrary가 먼저 만들어져야 한다는 것을 알고 ```add_subdirectory(src)``` 후에 ```add_subdirectory(app)``` 를 해줘야 한다.  
이미 add_subdirectory로 추가했던 폴더를 중복해서 또 추가하면 오류가 나니 주의해야한다.  
ex. ```add_subdirectory(src)```

* **set**   
cmake에서 변수를 지정할 때 사용된다.  
예를 들어 ```set(LIBRARY_NAME "MyLibrary")``` 라고 하면 C++로 따지면 ```std::string LIBRARY_NAME = "MyLibrary";``` 이거랑 똑같은 것이다.  
만약에 ```set(LIBRARY_NAME MyLibrary)``` 이렇게 "를 때고 변수 지정을 한다면 CMake가 적절한 변수 형태를 유추해서 저장을 한다.  
이 경우에는 MyLibrary가 문자열이니 문자형으로 저장을 할 것이다.  
배열형도 가능한데 ```set(LIBRARY_SOURCES "my_lib.cc" "my_lib_2.cc" "my_lib_3.cc")``` 이렇게 해주면 LIBRARY_SOURCES 이 녀석은 배열이다.  
set은 단순히 변수를 저장할 때도 쓰이지만 CMake 자체에 내장되어 있는 변수들의 값을 바꿀 때도 사용된다.  
예를 들어 프로젝트에서 C++ 17을 사용하고 싶다면 ```set(CMAKE_CXX_STANDARD 17)``` 이렇게 해주면 된다.  
변수명을 지을 때 주의할 점은 모두 대문자로 지어야 한다는 것이다.   
변수명을 사용할 때는 ```${LIBRARY_NAME}``` 이렇게 사용한다.  
보통 ```add_library(MyLibrary "my_lib.cc" "my_lib_2.cc" "my_lib_3.cc")를 add_library(MyLibrary ${LIBRARY_SOURCES})``` 이렇게 줄이는 곳에 많이 쓰인다.  
ex. ```set(CMAKE_CXX_STANDARD 17)```

* **option**  
CMake에서 bool형 변수를 생성할 때 사용된다.    
변수명, 변수 설명, 디폴트 값 순으로 정의한다.  
ex. ```option(COMPILE_EXECUTABLE "This is COMPILE_EXECUTABLE hint!" OFF)```

* **add_definitions**   
전처리기에 매크로를 전달할 때 사용된다.  
매크로를 정의만 할거면 -D<매크로이름> 이렇게 쓰고 값까지 지정하려면 -D<매크로>=값 이렇게 사용한다.  
ex. ```add_definitions(-DTHIS_IS_MACRO -DSET_THE_VALUE=2)```

* **if(조건)**  
CMake에도 if문이 존재한다.   
if문을 사용했으면 endif()로 꼭 닫아줘야 한다.   
else문, else if문은 else(), elseif()로 사용한다.  
밑은 간단한 예시이다.  
```
if(COMPILE_EXECUTABLE)
  set(CMAKE_CXX_STANDARD 17)
endif()
```

* **message**  
```message("문자열")```로 사용한다.   
빌드 시점이 아니라 CMake 세팅 시점에 출력된다.   
ex. ```message("Compile Warning")```

* **configure_file** 
빌드 시점에 동적으로 헤더 파일을 만들어 줄 때 사용된다.  
살짝 설명이 길어질텐데 어떻게 사용하냐면 일단 밑과 같은 config.h.in 파일이 존재한다고 하자. (확장자는 .h,.cpp를 제외하고 뭐를 사용하던 상관없다. 근데 앵간하면 .in으로 사용하자.)
```c++
#pragma once

#include <cstdint>
#include <string_view>

static constexpr std::string_view project_name = "@PROJECT_NAME@";
static constexpr std::string_view project_version = "@PROJECT_VERSION@";

static constexpr std::int32_t project_version_major{@PROJECT_VERSION_MAJOR@};
static constexpr std::int32_t project_version_minor{@PROJECT_VERSION_MINOR@};
static constexpr std::int32_t project_version_patch{@PROJECT_VERSION_PATCH@};
```
해당 .in 파일이 있는 곳 CMakeLists.txt 파일에 ```configure_file("config.h.in" "${CMAKE_BINARY_DIR}/configured_files/include/config.h" ESCAPE_QUOTES)``` 해당 함수가 있으면 빌드 시점에 CMake가 ```빌드_경로/configure_file/include/``` 경로에 config.h.in에서 .in을 떼고 config.h을 만들어 주는데 특이한 점은 @로 감싸고 있는 문자열을 CMake가 가지고 있던 값으로 모두 치환해준다.  
ESCAPE_QUOTES 옵션은 ```"@PROJECT_NAME@"``` 이 녀석을 치환할 때 실제로 \\"치환 값\\" 이렇게 "를 \\"로 안전하게 바꿔 .h 파일을 생성하도록 한다.  
예를 들어 최상위 CMakeLists.txt에 ```project(CppProjectTemplate VERSION 1.2.3 LANGUAGES C CXX)``` 이러한 내용이 있다면 @PROJECT_NAME@ -> CppProjectTemplate, @PROJECT_VERSION@ -> 1.2.3 등으로 치환된다.  
생성된 config.h 모양은 밑과 같다.  
```c++
#pragma once

#include <cstdint>
#include <string_view>
 
static constexpr std::string_view project_name = "CppProjectTemplate";
static constexpr std::string_view project_version = "1.2.3";

static constexpr std::int32_t project_version_major{1};
static constexpr std::int32_t project_version_minor{2};
static constexpr std::int32_t project_version_patch{3};
```
생성된 헤더 파일을 가지고 소스 파일에서 project_name 변수를 사용할 수 있다. (빌드 시점에서 동적으로 생성되는 헤더 파일이기에 config.h 헤더가 존재하지 않고 project_name 변수도 없다고 VS Code의 Intellisense에서 오류라고 판단할 수 있는데 막상 빌드해보면 오류 표시가 없어지면서 빌드가 잘 된다.)  
ex. ```configure_file("config.h.in" "${CMAKE_BINARY_DIR}/configured_files/include/config.h" ESCAPE_QUOTES)```

* **file** 
파일 이름을 변수로 저장할 때 사용된다.  
예를 들어 ```file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ./SourceFile/*.cpp)``` 이렇게 하면 SourceFile 폴더 내부를 돌면서 확장자가 cpp인 파일들을 SRC_FILES 리스트 변수에 추가한다.  
GLOB_RECURSE 옵션도 지정되었으니 SourceFile 파일 하위 폴더까지 돌면서 조사한다.  
CONFIGURE_DEPENDS이 설정되면 SourceFile 폴더 내부에 새로운 파일이 추가, 삭제된 경우에 CMake 빌드 명령어만 수행해도 CMake 세팅이 자동으로 된다.  
ex. ```file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ./SourceFile/*.cpp)```

* **add_compile_options**  
컴파일 옵션 인자를 넣어줄 수 있다.  
ex. ```add_compile_options(-g -Wall -std=c++11)```

&NewLine;
## CMakeLists.txt 사전변수  
&NewLine;

### - **CMAKE_CXX_STANDARD** 
> C++ 표준 버전 정의  
> [ex. ```set(CMAKE_CXX_STANDARD 17)```]  

### - **CMAKE_CXX_STANDARD_REQUIRED** 
> C++ 표준 버전 정의된 것을 필수로 요구할 것이냐 아니냐를 따지는 옵션이다.  
> 만약 프로젝트 빌드 유저의 환경이 C++17을 지원하지 않는 경우 CMAKE_CXX_STANDARD_REQUIRED 변수가 OFF로 되어 있으면 CMAKE_CXX_STANDARD가 17로 정의되어 있더라도 프로젝트 빌드 유저 환경에 맞는 다른 C++ 버전이 채택되어 그걸로 빌드된다.  
> [ex. ```set(CMAKE_CXX_STANDARD_REQUIRED ON)```]

### - **CMAKE_CXX_EXTENSIONS** 
> 특정 컴파일러 확장 기능을 사용하냐 안하냐를 결정한다.  
> msvc만의 기능이 있고 gcc만의 기능이 있는데 이러한 특수한 기능을 사용할 것이냐를 물어보는 것이다.  
> 크로스 플랫폼 빌드가 빌요한 프로젝트에서는 걍 사용하지 말자.  
> [ex. ```set(CMAKE_CXX_EXTENSIONS OFF)```]

### - **CMAKE_SOURCE_DIR** 
> 프로젝트 최상위 경로, set()으로도 바뀌지 않음.

### - **CMAKE_BINARY_DIR** 
> 빌드 산출물이 생성되는 위치의 최상위 경로, set()으로도 바뀌지 않음.

### - **CMAKE_CURRENT_SOURCE_DIR** 
> 현재 처리하고 있는 CMakeLists.txt의 경로, 타겟 CMakeLists.txt가 바뀔 때마다 계속 변동 된다.

### - **CMAKE_BUILD_TYPE** 
> 빌드 타입 (Debug, Release 등...)

### - **CMAKE_INSTALL_PREFIX** 
> 최종 생성물을 복사하여 저장할 경로가 저장되어 있는 변수.

### - **RUNTIME_OUTPUT_DIRECTORY** 
> 빌드 완료한 실행 바이너리를 저장할 디렉토리가 저장되어 있는 변수.

### - **LIBRARY_OUTPUT_DIRECTORY** 
> 빌드 완료한 라이브러리를 저장할 디렉토리가 저장되어 있는 변수.

### - **ARCHIVE_OUTPUT_DIRECTORY** 
> 빌드 완료한 Static 라이브러리를 저장할 디렉토리가 저장되어 있는 변수.(Archive를 다른 말로 Static 라이브러리라고도 한다.)

&NewLine;
## CMake 명령어 문법  
&NewLine;

자세한 명령어 내용은 https://runebook.dev/ko/docs/cmake/ 이곳에서 찾아보자.  
세팅은 빌드 전 cmake 환경 설정을 한다고 생각하면 되고 빌드는 말 그대로 코드 산출물이 발생되는 것이다.  
CMake 세팅을 할 때는 파일 경로를 적는 일이 잦은데 경로 구분자는 '\'요게 아니라 '/'이거다.  
그니까 예를 들어 ```C:\MyDir\HelloWorld.txt``` 이거는 에러인데 ```C:/MyDir/HelloWorld.txt``` 이거는 정상이다.  

&NewLine;
### - **세팅 옵션**
&NewLine;

* _-S_  
-S 옵션은 프로젝트의 root directory 경로가 위치해야 한다. (보통 첫 CMakeLists.txt가 위치하는 곳, 프로젝트 폴더 최상위 경로)

* _-B_  
-B 옵션은 빌드 후 생성되는 파일들이 위치할 폴더 경로가 적혀야 한다.  
예를 들어 ```C:/VS_CODE_PROJECTS/HelloWorld/CMakeLists.txt``` 이렇게 위치하고 있다면 ```cmake -S C:/VS_CODE_PROJECTS/HelloWorld -B C:/VS_CODE_PROJECTS/HelloWorld/build``` 명령어를 수행해 cmake 프로젝트를 세팅해주면 된다.

* _-D_  
-D 옵션은 CMakeLists.txt에 정의된 변수를 커맨드 라인으로 세팅할 때 사용된다.  
예를 들어 CMake 환경 세팅을 진행할 때 C++14 버전으로 빌드 설정을 하고싶다면 ```cmake .. -DCMAKE_CXX_STANDARD=14``` 이러한 명령어를 입력하면 된다. 주의할 점은 -D와 특정 변수명 사이에 띄어쓰기가 없이 붙여써야 한다는 것이다.

* _-G_  
-G 옵션은 CMake가 빌드 구성 파일을 만들 수 있도록 도와주는 생성기를 지정하는 곳에 쓰인다.  
그러면 생성기가 뭐냐고 물어볼 수 있는데 CMake는 혼자서 링크 종속성에 대한 정보를 컴파일러에게 전달하지 못한다.  
이유는 링크 종속성을 전달하는 방식이 플랫폼마다 다르기 때문인데 Mac과 같은 Unix 기반에서는 Unix Makefiles가 생성기 역할을 해주고 Windows에서는 Visual Studio가 이 역할을 해준다.  
물론 Ninja와 같이 크로스 플랫폼 생성기도 있지만 프로젝트가 돌아가는 컴퓨터에 Ninja가 깔려있을 것이라는 보장이 없지 않은가? 따라서 자신이 빌드할 때 특정한 생성기를 이용하여 빌드하고 싶다면 -G 옵션을 사용하면 된다.   
예를 들어 ```cmake -S .. -B . -G "Visual Studio 16 2019"``` 이렇게 하면 CMake관련 빌드 구성 파일들이 Visual Studio 2019를 통해 생성된다.  
생성기에 대한 자세한 답변은 https://stackoverflow.com/questions/25941536/what-is-a-cmake-generator 요기에 잘 설명되어 있다.

* _--graphviz_  
--graphviz 옵션은 dot이라는 모듈 종속성 그리기 프로그램이 설치되어 있어야 사용이 가능하다. (```choco install graphviz```를 했다면 사용이 가능하다.)  
사용법은 ```cmake -S . -B build --graphviz=graph.dot``` 이렇게 빌드 세팅을 진행할 때 ```--graphviz=graph.dot``` 이 녀석을 붙여주면 된다.  
이렇게 하면 종속성 정보가 그래프로 그려지는 데 필요한 graph.dot 파일이 생성되는데 이 녀석을 .png 파일로 생성하려면 ```dot -Tpng graph.dot -o graph.png``` 명령어를 실행하면 된다.

* _--no-warn-unused-cli_  
--no-warn-unused-cli 옵션을 사용하게 되면 CMake 명령줄에 관련한 경고가 뜨지 않고 명령줄에 선언되었지만 실제 CMakeLists.txt에는 존재하지 않는 변수가 있더라도 경고가 뜨지 않는다.  
보통의 경우 사용된다.

&NewLine;
### - **빌드 옵션**
&NewLine;

* _--build_  
--build 옵션은 프로젝트를 빌드할 때 수행하는 명령어다.  
"--build 특정 경로"로 사용하면 된다. (여기서 특정 경로는 빌드 산출물이 생성되어 위치할 경로를 뜻한다.)

* _--target_  
--target 옵션은 특정 타겟을 정해서 해당 타겟만 빌드할 수 있다.  
예를 들어 CMakeLists.txt에 MyLibrary라는 라이브러리가 정의되어 있다면 ```cmake --build . --target MyLibrary```를 하면 MyLibrary와 그 라이브러리에 종속된 모듈들만 빌드된다.

* _-j_  
-j 옵션은 빌드 속도를 가속하기 위한 병렬 처리를 세팅하기 위해 필요하다.  
"-j 12"이면 테스크를 12개 유지하면서 빌드를 한다는 것이다. (CPU가 겁나 돌아가는 소리를 들을 수 있을 것이다...)

&NewLine;
## CMake에서 Makefile 활용법  
&NewLine;

보통 명령어를 축약해서 사용할 때 활용한다.  
예를 들어 터미널에서 CMake를 빌드할 때마다 ```mkdir build, cd build, cmake -S .. -B . -G "Ninja"``` 이런거 계속 치기 귀찮기 때문에 Makefile에 미리 정의해놓고 쓰게 된다.  
윈도우, 리눅스, MAC 모두 명령어가 살짝 다르기 때문에 빌드 환경에 따라 다른 명령어를 사용해야 한다.  
밑은 윈도우 환경에서 예시이고 파일 이름은 꼭 Makefile이여야 하며 프로젝트 최상위 폴더에 위치하는 것이 좋다.  
```
rebuild:
	mkdir build | rmdir /s /q build
	mkdir build
	cmake -S . -B build --graphviz=build/graph.dot
	dot -Tpng build/graph.dot -o graph.png
	cmake --build build
```
위와 같은 내용의 Makefile이 있다면 터미널에서 단지 make rebuild 명령만 수행해도 CMake가 세팅되고 재빌드가 수행된다.

&NewLine;
## CMake에서 External Library 추가하는 방법  
&NewLine;

해당 방법은 여러가지가 존재한다. git, vcpkg, conan 등등... 각각의 방법에 대해 예시를 들어 절차적으로 설명하겠다.
&NewLine;
### - **CMake와 Git을 통해 외부 라이브러리 추가**  
&NewLine;
> #### 1. 자신이 진행할 프로젝트를 VS Code로 연다.
&NewLine;
> #### 2. 프로젝트 최상위 위치에서 외부 라이브러리들이 담길 external 폴더를 만든다. (다른 이름으로 해도 되지만 그냥 여기서는 external로 한다.)
&NewLine;
> #### 3. 프로젝트 터미널에서 git init 명령어를 실행하여 프로젝트에 git을 활성화한다. (해당 명령어를 수행할 때 위치는 프로젝트 최상위 폴더여야 한다.)
&NewLine;
> #### 4. https://github.com/nlohmann/json 라이브러리를 추가하려고 한다.  
> #### 프로젝트 터미널에서 ```git submodule add https://github.com/nlohmann/json external/json``` 명령어를 한다. (해당 명령어를 수행할 때 위치는 프로젝트 최상위 폴더여야 한다.)  
> #### 만약 수행이 안된다면 VS Code를 재실행하고 해당 명령어를 수행한다.
> #### 명령어에서 external/json 부분이 있는데 해당 경로에서 json 폴더명은 사용자가 원하는 이름으로 해도 되지만 여기서는 json으로 한다.
&NewLine;
> #### 5. 프로젝트 최상위 위치에서 cmake라는 폴더를 만든다.  
> #### 해당 폴더는 이제 CMake에서 쓰일 커스텀 함수 구현부 파일이 들어갈 것이다.
&NewLine;
> #### 6. cmake 폴더 내에 AddGitSubmodule.cmake 파일을 만든다.  
> #### 해당 파일의 내용은 밑과 같아야 한다.
> ```
> function(add_git_submodule dir)
>     find_package(Git REQUIRED)
>
>     if (NOT EXISTS ${dir}/CMakeLists.txt)
>         execute_process(COMMAND ${GIT_EXECUTABLE}
>             submodule update --init --recursive -- ${dir}
>             WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
>     endif()
> 
>     add_subdirectory(${dir})
> endfunction(add_git_submodule)
> ```
> #### 해당 내용을 분석해보면 function([함수 이름] [함수 인자]), endfunction([함수 이름]) 이고 find_package에서 Git 패키지와 관련된 데이터들을 추가해준다.  
> #### 그니까 find_package(Git REQUIRED)를 했다면 Git의 실행파일 경로가 저장되어 있는 GIT_EXECUTABLE 와 같은 매크로들을 이제 사용할 수 있다.  
> #### if문 부분 로직을 보면 만약 dir 경로에 CMakeLists.txt 파일이 존재하지 않으면 execute_process 명령을 통해 명령어를 실행하는데 해당 명령어는 ```submodule update --init --recursive -- ${dir}``` 이다.  
> #### 그리고 프로젝트의 최상위 위치는 WORKING_DIRECTORY 인자로 넘겨야 하는데 해당 인자는 최상위 위치가 정의되어 있는 PROJECT_SOURCE_DIR 매크로로 넘겨준다. 즉 dir 경로에 CMakeLists.txt 파일이 존재하지 않으면 ${dir}에 위치한 레포지토리를 업데이트하라는 것이다.
> #### 그리고 해당 레포지토리 폴더를 프로젝트의 최상위 CMakeLists.txt 파일과 연결해줘야 하기에 add_subdirectory(${dir}) 명령을 수행한다.
&NewLine;
> #### 7. 프로젝트의 최상위 CMakeLists.txt 파일에 가서 밑의 명령들을 추가해준다.
> ```
> set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
> include(AddGitSubmodule)
> add_git_submodule(external/json)
> ```
> #### 각 명령에 대해 설명해보자면 CMAKE_MODULE_PATH 매크로는 CMake 커스텀 함수 파일들이 위치하는 경로를 담고 있어야 하는데 지금 커스텀 함수 파일인 AddGitSubmodule.cmake가 존재하는 곳이 ```"${PROJECT_SOURCE_DIR}/cmake/"```이기에 ```set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")``` 이렇게 세팅해준다.  
> #### 커스텀 함수 파일 이름이 AddGitSubmodule.cmake이기에 해당 파일에 정의되어 있는 커스텀 함수를 CMake에서 사용해주기 위해 ```include(AddGitSubmodule)```로 AddGitSubmodule.cmake 파일을 포함시켜준다.  
> #### 외부 라이브러리 경로는 최상위 프로젝트 폴더부터 ```external/json```에 존재하니 AddGitSubmodule 파일에서 정의한 함수인 ```add_git_submodule(external/json)```를 하여 해당 라이브러리의 CMakeLists.txt와 프로젝트 최상위 CMakeLists.txt를 연동해준다.  
&NewLine;
> #### 8. 마지막으로 해당 외부 라이브러리를 사용하는 모듈에 적절하게 외부 라이브러리 종속성을 추가해준다. 지금 추가하려는 라이브러리 이름은 nlohmann_json(라이브러리 이름은 특정 라이브러리 내의 CMakeLists.txt에 project() 속에 쓰여있다.)이니 예를 들어 ```target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME} nlohmann_json)``` 요렇게 넣어주면 된다.
&NewLine;
### - **CMake의 FetchContent 기능을 이용하여 Git을 통해 외부 라이브러리 추가**
&NewLine;
> #### 1. 최상위 CMakeLists.txt에 include(FetchContent) 명령을 적는다. 이러면 FetchContent와 관련된 함수들을 이용할 수 있다.
&NewLine;
> #### 2. FetchContent_Declare 명령을 이용한다.  
> #### ```FetchContent_Declare(<라이브러리 이름> GIT_REPOSITORY <레포지토리 주소 + .git> GIT_TAG <다운 받고자 하는 레포지토리 태그>)``` 
> #### 예를들어 굉장히 유명한 C++ 전용 로깅 라이브러리인 spdlog를 사용하고 싶다면 다음과 같이 명령을 선언하면 된다.  
> #### ```FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.11.0)```  
> #### GIT_TAG를 주의해야 하는데 태그 주소를 보고 적어야 한다. (https://github.com/gabime/spdlog/releases/tag/v1.11.0이면 v1.11.0 이 녀석을 적는다.)  
&NewLine;
> #### 3. FetchContent_Declare 바로 밑에  ```FetchContent_MakeAvailable(<라이브러리 이름>)```을 적는다.
&NewLine;
> #### 4. 마지막으로 해당 외부 라이브러리를 사용하는 모듈에 적절하게 외부 라이브러리 종속성을 추가해준다.
&NewLine;
> #### 5. 해당 방법의 장점은 특정 라이브러리만 빌드 타겟으로 정해 그것만 빌드할 수 있다는 것이다.  
> #### 단점은 재빌드를 수행할 때 외부 라이브러리들까지 모두 빌드하기 때문에 빌드 시간이 오래걸린다는 것도 있고 GitHub에 공개되어 있지 않거나 CMake를 사용하여 빌드하지 않는 오픈 소스 라이브러리들은 사용이 불가능하다.
&NewLine;
### - **Conan과 CMake를 사용하여 외부 라이브러리 추가**
&NewLine;
> #### 1. 일단 패키지 관리툴인 Conan을 설치해야 한다. 이미 설치했다면 3번 항목부터 봐라.
&NewLine;
> #### 2. PowerShell에 들어가 pip install conan을 하여 설치한다.
&NewLine;
> #### 3. https://conan.io/center/ 에서 사용하고 싶은 라이브러리 이름을 검색한다. 여기선 예시로 catch2 라이브러리로 하겠다.
&NewLine;
> #### 4. 검색하면 ```catch2/특정 버전``` 옆에 클립보드로 복사하는 버튼이 있을 텐데 이걸 누른다.
&NewLine;
> #### 5. 프로젝트의 최상위 CMakeLists.txt가 위치한 곳에 conanfile.txt를 만들고 밑과 같은 내용을 담는다.  
> ```
> [requires]
> 
> [generators]
> cmake
> ```
&NewLine;
> #### 6. conanfile.txt의 ```[requires]``` 밑에 아까 클립보드로 복사한 라이브러리 내용을 붙여넣는다. (ex. ```catch2/3.2.1```)
> &NewLine;
>> #### 6.1 이건 선택사항인데 conanfile.txt 파일에 추가적으로 밑과 같이 설정하면  
>> ```
>> [imports]
>> bin, *.dll -> ./build/debug/bin
>> lib, *.lib -> ./build/debug/lib
>> ```
>> #### 빌드 후 종속성에 있는 모든 dll은 conanfile.txt 파일 경로를 기준으로 "./build/debug/bin" 경로에,  모든 lib는 "./build/debug/lib" 경로에 위치한다.  
>> #### 그리고 conan의 디폴트 링크 방식은 static 방식이기에 따로 dll을 생성하지 않는다. 이를 수정하려면 conanfile.txt에 밑과 같이  
>> ```
>> [options]
>> catch2:shared=True
>> ```
>> #### 이렇게 추가해줘야 한다. (여기선 예시로 catch2 라이브러리를 사용했지만 형식은 "패키지이름:shared=True" 아니면 "패키지이름:shared=False"이다.)  
>> #### 더 자세한 내용은 https://docs.conan.io/en/latest/using_packages/conanfile_txt.html 이곳에 쓰여있다.
&NewLine;
> #### 7. conan이 설치된 폴더에 들어가야 한다. (보통 "C:\Users\<사용자 데스크탑 이름>\.conan"에 위치한다.)  
> #### 설치 폴더에 profiles라는 폴더가 있고 그 내부에 default 파일이 있을 것이다.  
> #### 해당 녀석에 수정이 필요할 수도 있는데 보통 밑과 같이 되어있을 것이다.
> ```
> [settings]
> os=Windows
> os_build=Windows
> arch=x86_64
> arch_build=x86_64
> compiler=Visual Studio
> compiler.version=17
> build_type=Release
> [options]
> [build_requires]
> [env]
> ```
> #### 만약 자신이 VS Code에서 빌드할 때 컴파일러를 Visual Studio의 MSVC를 사용하면 상관이 없지만 gcc나 clang을 사용한다면 바꿔줘야 한다.
> #### Windows, Mac, Linux에서 모두 사용할 수 있는 gcc를 사용하는 경우에 대해서만 예시를 들면 밑과 같이 바뀌어야 한다.
> ```
> [settings]
> os=Windows
> os_build=Windows
> arch=x86_64
> arch_build=x86_64
> compiler=gcc
> compiler.version=12
> compiler.libcxx=libstdc++11
> build_type=Release
> [env]
> CC=C:/msys64/mingw64/bin/gcc.exe
> CXX=C:/msys64/mingw64/bin/g++.exe
> [options]
> [build_requires]
> ```
> #### 물론 compiler.version, CC, CXX에 대한 값은 빌드 환경마다 달라지기 때문에 적절하게 바꿔서 넣어줘야 한다.
&NewLine;
> #### 8. VS Code에서 원활한 Intellisense를 사용하기 위해 ```.vscode/c_cpp_properties.json```의 includePath에 ```~/.conan/data/**``` 경로를 추가해야 특정 라이브러리가 제공하는 헤더를 include할 때 편집기에서 빨간 밑줄이 안 그어진다. (사실 빨간 줄만 그어질 뿐이지 실제로 에러는 아니기에 빌드, 실행은 잘 된다.)
&NewLine;
> #### 9. 터미널에서 ```conan install <conanfile.txt가 있는 경로 위치> -if <conanbuildinfo.cmake가 만들어질 경로>``` 명령어를 수행한다. 이러면 conan이 설치되어 있는 곳에 연동할 라이브러리 dll들이 설치되고 해당 경로가 프로젝트와 연동된다. (ex. ```conan install . -if ./build```)
&NewLine;
> #### 10. 최상위 CMakeLists.txt에 ```include(<conanbuildinfo.cmake가 위치한 폴더>/conanbuildinfo.cmake)```와 ```conan_basic_setup()```을 추가해준다.
&NewLine;
> #### 11. 그리고 해당 라이브러리가 쓰이는 곳 CMakeLists.txt에 target_link_libraries 함수가 있을 텐데 여기에 ```${CONAN_대문자로된라이브러리이름} or CONAN_PKG::라이브러리이름```을 추가해주면 된다. 
> #### 단 ```${CONAN_대문자로된라이브러리이름}```를 이용하여 라이브러리를 추가하면 해당 라이브러리에 한하여 graphviz가 작동 안한다. (ex. ```target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${CONAN_CATCH2})```)
&NewLine;
### - **vcpkg와 CMake를 사용하여 외부 라이브러리 추가**
&NewLine;
> #### 1. vcpkg를 먼저 설치해야 한다. 관리자 모드로 터미널이나 PowerShell을 연다.
&NewLine;
> #### 2. vcpkg 설치를 원하는 위치로 cd 명령을 수행해 이동하고 ```git clone https://github.com/microsoft/vcpkg``` 명령을 수행한다.
&NewLine;
> #### 3. 다음에 bootstrap-vcpkg.bat를 실행하여 vcpkg를 설치한다.
&NewLine;
> #### 4. 관리자 모드로 PowerShell을 켜고 vcpkg 폴더 내로 들어가 ```.\vcpkg integrate install``` 와 ```.\vcpkg integrate powershell``` 명령을 수행하고 터미널이나 PowerShell 창을 재시작한다.
&NewLine;
> #### 5. 자신의 프로젝트로 가서 .vscode/settings.json에 cmake.configureSettings 내용으로 CMAKE_TOOLCHAIN_FILE 경로를 지정해주어야 한다. 추가하면 대략 밑과 같은 모습이 될 것이다.
> ```
> {
>   "C_Cpp_Runner.cCompilerPath": "gcc",
>   "C_Cpp_Runner.cppCompilerPath": "g++",
>   ....
>   ....
>   "cmake.configureSettings": {
> 	"CMAKE_TOOLCHAIN_FILE": "<vcpkg가 설치된 폴더 경로>/scripts/buildsystems/vcpkg.cmake"
>   }
> }
> ```
> #### 아니면 그냥 settings.json 수정없이 cmake 세팅 명령어를 수행할 때 -DCMAKE_TOOLCHAIN_FILE=<vcpkg가 설치된 폴더 경로>/scripts/buildsystems/vcpkg.cmake 이걸 추가해줘도 된다.
&NewLine;
> #### 6. vcpkg는 vcpkg.json라는 파일로 종속성 관리를 한다. 프로젝트 최상위 CMakeLists.txt가 있는 곳에 vcpkg.json 파일을 생성해준다.
&NewLine;
> #### 7. vcpkg.json 작성법을 약간 숙지해야 하는데 방법은 https://github.com/microsoft/vcpkg/blob/master/docs/users/manifests.md 이곳에 자세하게 나와있다. 
> #### 여기서는 필수적인 내용만 간략히 설명한다.
> #### 일단 예시로 밑과 같은 내용이 있다고 하자.
> ```
> {
>   "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg/master/scripts/vcpkg.schema.json",
>   "name": "project-name",
>   "version": "1.0.0",
>   "builtin-baseline":"4e368f63904b784e19401e08cbc15ca8f06eb92a",
>   "dependencies": [
> 	"fmt", 
> 	{
> 		"name": "zlib", 
> 		"version>=": "1.2.11"
> 	},
> 	{
> 		"name": "arrow",
> 		"default-features": false,
> 		"features": [ "json", "filesystem" ]
> 	},
> 	{
> 		"name": "sdl2", 
> 		"platform": "!windows"
> 	}
>   ],
>   "overrides": [
>     { 
> 		"name": "fmt", 
> 		"version": "6.0.0" 
> 	}
>   ]
> }
> ```
> * ```$schema```  
> ```$schema```는 Json 작성할 때 자동완성을 도와주는 스키마를 정의한다.  
> 정의 안해도 되지만 하면 vcpkg.json 작성할 때 편하다.  
>    
> * ```name```   
> ```name```은 프로젝트 이름인데 주의점은 프로젝트 이름은 모두 영문 소문자만 가능하고 '.', 공백 등 글자가 아닌 것들은 모두 '-'로 대체해주어야 한다.   
> 예를 들어 SDL.Sample이면 sdl-sample이 되어야 한다.  
>    
> * ```version```  
> ```version```은 프로젝트 버전이다.
>    
> * ```dependencies```  
> ```dependencies```은 프로젝트가 사용하는 라이브러리 리스트이다.   
> 위에서는 zlib, fmt 라이브러리를 프로젝트에서 사용한다고 되어있다. 
> vcpkg.json의 "dependencies"를 작성하기 전에 꼭 터미널로 vcpkg가 설치된 경로로 이동한 뒤 ".\vcpkg.exe search <사용할 라이브러리 이름>" 명령을 수행해 해당 라이브러리를 vcpkg가 지원하는지 확인하자.
>   
> * ```builtin-baseline```  
> ```builtin-baseline```은 밑에서 서술할 ```version>=```, ```overrides``` 등을 사용할 때 정의해 놓아야 한다.  
> 해당 값은 vcpkg가 설치되어 있는 폴더로 들어가 ```git rev-parse HEAD``` 명령어를 수행하면 출력되는 값으로 설정하면 된다.  
> vcpkg를 업데이트할 때마다 갱신해줘야 한다.  
> ```builtin-baseline```를 추가하는 또 다른 방법은 프로젝트 최상위 폴더 위치의 터미널에서 ```vcpkg x-update-baseline --add-initial-baseline```를 수행하는 것이다.  
> 해당 명령어는 baseline 업데이트는 물론 baseline 항목이 vcpkg.json에 없다면 새로 추가도 해준다. (물론 사전에 vcpkg.json 파일에 프로젝트 최상위 폴더에 존재해야한다.)
>   
> * ```version>=```  
> ```version>=```은 사용할 라이브러리의 최하위 버전을 정의한다.  
> vcpkg는 최하위 버전이 존재하면 해당 버전을 우선순위로 받는다.  
> 위 예시에서는 zlib의 최하위 버전은 ```1.2.11```라고 되어있다.  
> 정의한 버전이 존재하지 않을 경우 버전 리스트들이 터미널에 출력되면서 오류가 난다.
>   
> * ```default-features```  
> ```default-features```는 기본적으로 true이지만 가끔 false를 사용할 때가 있는데 이 경우 특정 ```features```를 이용하기 위해서이다.
>   
> * ```features```  
> ```features```는 라이브러리의 디폴트 값을 사용하지 않고 특정 기능을 사용할 때 정의하게 된다.  
> 위 예시에서는 arrow 라이브러리에 "features"가 json으로 되어있다.  
> 이것이 무슨 의미인지 확인하기 위해서 ```.\vcpkg.exe search arrow```를 해보면 여러가지 arrow 라이브러리들이 출력되는데 arrow[csv] 얘는 csv를 지원하는 arrow, arrow[filesystem] 얘는 파일 시스템을 지원하는 arrow, arrow[json] 얘는 json을 지원하는 arrow 등 많은데 여기서 json과 filesystem을 지원하는 arrow 라이브러리만 가져오기 위해서 vcpkg.json 파일에  ```"features": [ "json", "filesystem" ]``` 라고 선언한 것이다.
>   
> * ```overrides```  
> ```overrides```는 ```dependencies```에 정의된 라이브러리의 버전을 고정시킨다. 
> 라이브러리의 ```version>=```이 이미 정의되어 있어도 해당 라이브러리의 ```overrides``` 버전 정보가 존재한다면 ```overrides```의 버전이 우선적으로 적용된다.
>    
> * ```platform```  
> ```platform```은 라이브러리를 특정 플랫폼에서만 사용할 때 정의한다.  
> ```!windows```, ```windows & linux```, ```(windows & arm64) | (linux & x64)``` 등 여러 방식으로 사용할 수 있고 OS 계열에는 windows, uwp, linux, osx, android, emscripten가 있고 아키텍쳐 계열에는 x86, x64, wasm32, arm64, arm가 있다.
&NewLine;
> #### 8. 라이브러리를 사용할 CMakeLists.txt에서 ```find_package(<라이브러리 이름> REQUIRED)```을 해준다. (find_package에도 다양한 옵션이 있으니 찾아보자.)
&NewLine;
> #### 9. 라이브러리가 쓰이는 곳 CMakeLists.txt에 target_link_libraries 함수가 있을 텐데 여기에 라이브러리 이름을 추가해주면 된다. (ex. ```target_link_libraries(${EXECUTABLE_NAME} PUBLIC Boost::boost)```)
&NewLine;
> #### 10.  만약 8번 9번에서 라이브러리 이름이 잘못되었거나 8번에서 CONFIG REQUIRED인데 그냥 REQUIRED로 적었거나 하면 오류가 나면서 터미널에 어떻게 고쳐야 하는지 출력되니 그걸 따라서 CMakeLists.txt 내용을 바꾸면 된다.

&NewLine;
## CMake와 Doxygen 같이 사용하기
&NewLine;

> ### 1. 당연히 Doxygen은 설치가 되어 있어야 한다.
&NewLine;
> ### 2. 설명을 추가할 함수 위에서 /**Enter키를 차례대로 누르면 Doxygen 주석 형식이 갖춰진다. 
> ### 대략 밑과 같이 생겼다.
> ```
> /**
>  * @brief 이 함수는 어쩌구 저쩌구 ...
>  * @param 이 인자는 어쩌구 저쩌구 ...
>  *
>  *
>  */
> ```
&NewLine;
> ### 3. @brief는 함수 설명, @param은 함수의 파라메터에 대한 설명, @return은 함수의 반환 값에 대한 설명 그 외 @details, @author, @date, @version, @throws 등 다양하게 있으니 자세한 정보는 https://www.doxygen.nl/manual/index.html 여기서 확인하자. 
&NewLine;
> ### 4. 프로젝트 최상위에서 docs라는 폴더를 만들자. (이름이 꼭 docs일 필요는 없다.)
&NewLine;
> ### 5. docs 폴더 내부에 Doxyfile 이라는 파일을 만들고 내부 내용을 다음과 같이 채워준다.
> ```
> #---------------------------------------------------------------------------
> # Project related configuration options
> #---------------------------------------------------------------------------
> DOXYFILE_ENCODING      = UTF-8
> PROJECT_NAME           = "C++ Project Template"
> PROJECT_NUMBER         = 1.0.0
> PROJECT_BRIEF          = "C++ Project Template"
> PROJECT_LOGO           =
> OUTPUT_DIRECTORY       = ./
> OUTPUT_LANGUAGE        = English
> MARKDOWN_SUPPORT       = YES
> 
> #---------------------------------------------------------------------------
> # Build related configuration options
> #---------------------------------------------------------------------------
> EXTRACT_ALL             = YES
> RECURSIVE               = YES
> GENERATE_HTML           = YES
> GENERATE_LATEX          = NO
> 
> #---------------------------------------------------------------------------
> # Configuration options related to the input files
> #---------------------------------------------------------------------------
> 
> INPUT                  = ../src
> INPUT_ENCODING         = UTF-8
> FILE_PATTERNS          = *.c \
>                          *.cc \
>                          *.cxx \
>                          *.cpp \
>                          *.h \
>                          *.hh \
>                          *.hpp \
>                          *.hxx
> ```
> ### 각 옵션들이 하는 기능은 뜻을 읽어보면 직관적으로 알 수 있다.  
> ### 사용자의 프로젝트에 따라 옵션을 알맞게 수정하면 된다.  
> ### 가장 중요한 옵션은 INPUT인데 여기에 Doxygen 주석 설명이 달려있는 코드 위치들을 적어야 한다.  
> ### Doxygen 결과 파일인 index.html이 생성되는 위치가 적혀있는 OUTPUT_DIRECTORY 옵션도 중요하다.  
&NewLine;
> ### 6. Doxyfile이 있는 곳에서 터미널로 doxygen 명령을 수행하면 OUTPUT_DIRECTORY 옵션에 정의된 위치에 결과 파일이 생성되고 생성 파일 중에 index.html 파일을 웹으로 열어보면 주석 정보가 문서화되어 정리된 페이지를 볼 수 있다.


