# C++ 빌드를 위한 VS Code 세팅  
일단 VS Code를 C++ 에디터로 사용한다는 것은 크로스 플랫폼을 고려한다는 것이지만 일단 설명은 필자가 사용하고 있는 Windows 10 기준에 중점이 맞춰져 있다.   
Linux나 Mac에서 C++ 빌드 환경을 구성하는 것은 Windows랑 별반 차이가 없을 뿐만 아니라 오히려 더 쉬운 부분이 많다.  
큰 차이점들을 살짝 살펴보자면 Windows에서 choco로 패키지를 설치하는 과정이 Linux에서는 apt-get install 명령어를 써야하는 것, 2023년 1월 13일 기준으로 native Linux를 지원하는 Visual Studio가 없어서 Linux에서는 보통 GCC, Clang 컴파일러를 쓰게 된다는 점, OS 별로 기저에 기본적으로 설치되어 있는 라이브러리들이 가지각색이라 상황에 따라 추가적인 라이브러리들을 설치해줘야 한다는 점 등이 있겠다.  
&nbsp;  

## VS Code에서 C++ 빌드를 하기 위한 사전 준비

1. Microsoft Store에 들어가서 Windows Terminal을 설치해준다. (그냥 깔려져있는 Powershell을 이용해도 되지만 편의성을 위해서 설치해준다.)  

1. Windows Terminal에서 PowerShell 탭을 열고 ```$PSVersionTable``` 명령어를 수행한 뒤에 출력된 PSVersion이 3 이상인지 확인한다. (3이하라면 PowerShell을 업데이트해준다.)  

1. .NET Framework 4.5 버전 이상이 설치되어 있는지 확인한다. (Visual Studio에서 ```.NET 테스크톱 개발``` 항목을 선택하면 알아서 최신버전의 .NET Framework를 설치해준다.)  

1. Windows Terminal을 관리자 모드로 열고 PowerShell 탭을 띄운후에 Get-ExecutionPolicy 명령어를 수행 후에 Restricted인지 확인한다.  
Restricted이라면 Set-ExecutionPolicy AllSigned 명령어를 추가적으로 수행해준다.  

1. ```Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))``` 명령어를 수행해 Chocolatey를 설치해준다.  
  
1. 설치가 끝났으면 Windows Terminal를 관리자 모드로 재시작해주고 PowerShell 탭을 띄우고 choco 명령어를 수행해 Chocolatey가 잘 설치되었는지 확인한다.  
  
1. ```choco install graphviz```, ```choco install git```, ```choco install doxygen.install```, ```choco install python```, ```choco install cmake``` 여기까지는 어떤 컴파일러를 사용하던지 필수적이니 깔아준다.  
   
	* **Visual Studio를 사용하고 싶다.**  
		Visual Studio Installer를 다운받고 C++ 구성요소를 선택하고 Visual Studio를 설치해주면 된다.  
		어떤 버전이든 Visual Studio가 깔려져 있다면 generator와 컴파일러, 디버거까지 모든 것이 갖춰져 있을 것이다.  
		Visual Studio 2022 버전 기준으로 generator는 ```Visual Studio 17 2022```, C/C++ 컴파일러는 ```cl.exe```, 디버거는 ```vsdbg```를 사용하게 된다.  

	* **Clang 컴파일러를 사용하고 싶다.**  
		```choco install llvm```, ```choco install ninja```로 LLVM과 Ninja를 추가적으로 설치해준다.  
		generator로 Ninja말고 Make를 사용하고 싶다면 ```choco install make```로 Unix Makefiles를 설치해준다.  
		이렇게 세팅한다면 generator는 ```Ninja```(혹은 ```Unix Makefiles```), C 컴파일러는 ```clang```, C++ 컴파일러는 ```clang++```, 디버거는 ```lldb```를 사용하게 된다.  
		Clang과 Ninja는 Windows, Linux, Mac에서 잘 작동하기 때문에 크로스 플랫폼 빌드를 추구하는 CMake와 가장 조합이 잘 맞는다.  

	* **GCC 컴파일러를 사용하고 싶다.**  
		자신이 사용하는 플랫폼이 Linux라면 보통 GCC를 사용하게 될 것이다.  
		Windows에서 GCC를 사용하려면 MinGW를 설치해줘야 한다.  
		MinGW 설치 방법은 인터넷에 널렸으니 찾아보고 Windows에서 GCC를 사용할 때 가장 문제점은 x64 비트용 GCC를 설치했다면 x64용 프로그램만 빌드되고 x86용 프로그램은 빌드가 안되어서 결국 x64용 GCC, x86용 GCC 이렇게 두 개를 모두 깔아줘야 해결이 된다...  
		반면에 리눅스에서는 multilib를 설치하면 x64 GCC로 x86용 프로그램을 빌드 할 수 있다.  
		이렇게 세팅한다면 generator는 ```MinGW Makefiles```(혹은 ```Unix Makefiles```), C 컴파일러는 ```gcc```, C++ 컴파일러는 ```g++```, 디버거는 ```gdb```를 사용하게 된다.  	

1. CMake를 설치해도 PowerShell 관리자 모드에서 cmake --version 명령어가 제대로 실행되지 않는다면 환경변수가 제대로 설정되지 않은 것이니 시스템 속성 -> 고급 탭 -> 환경 변수 -> 시스템 변수 -> Path 에 cmake.exe가 위치한 폴더 경로를 추가해주자. (보통 ```C:\Program Files\CMake\bin``` 이거다.)   
&nbsp;  

## VS Code 플러그인  
아래는 VS Code에서 C++ 사용시 유용한 플러그인 이름이 나열된다.  
설명에 **설치 선택**이라는 말이 없으면 그냥 깔자. (플러그인 이름 by 작성자)

1. C/C++ by Microsoft  
VS Code에서 C++ 사용하고 싶으면 그냥 깔자.  
Intellisense, debugging 등 필수적인 요소들을 제공한다.

1. Better C++ Syntax by Jeff Hykin  
VS Code 에디터에서 C++ 코드를 하이라이팅(에러 표시, 매크로 변수 색 표시 등...)하는 것을 도와준다. (글자 색이 잘 눈에 띄기 위해서 Dark+ 테마에서 잘 작동한다고 되어 있다.)

1. Better Comments by Aaron Bond  
주석 표시 색상을 알맞게 바꿔준다.  
예를 들어 "// !" 처럼 느낌표가 붙는 주석은 빨간색, "// ?" 는 진한 파란색, "// TODO: " 는 주황색 등... (json 파일로 커스터마이징이 가능하니 더 많은 정보는 플러그인 설명 참조)

1. CMake by twxs  
VSCode에서 CMake로 C++을 빌드하고 싶다면 깔자. (물론 컴퓨터에 이미 CMake가 깔려있어야 한다.)  
CMake 외에 C++을 VS Code에서 빌드하는 방법은 Makefile 뿐인데... 그냥 CMake가 유일한 선택지라고 생각하자.

1. CMake Tools by Microsoft  
CMake 사용을 편하게 해주고 코드 에러 표시 관련하여 많은 것을 CMake와 연동해준다.
얘를 사용하면 Makefile이나 bash 파일을 따로 만들어서 명령어 묶음을 실행해 빌드를 할 일이 적어지고 무엇보다 코드 디버깅 세팅이 굉장히 편해진다.  

1. CodeLLDB by Vadim Chugunov  
Clang 컴파일러나 MSVC 컴파일러를 이용한 프로그램을 디버깅할 때 필수다.  

1. CodeSnap by adpyke  
코드 내용을 스크린샷 찍을 때 유용하다.  
코드 부분을 마우스로 긁어 원하는 만큼 선택하고 우측클릭하고 CodeSnap을 누르면 된다.

1. Doxygen by Baptist BENOIST  
코드 문서 자동화 Doxygen 프로그램의 .dox 파일을 하이라이팅 해준다.

1. Doxygen Documentation Generator by Christoph Schlosser  
Doxygen 문서를 만드는 데 필요한 주석 형식을 간단히 만들어 준다. (기본적으로 /** + 엔터를 치면 Doxygen 주석 형식이 갖춰진다.)

1. EditorConfig for VS Code by EditorConfig  
.editorconfig 파일에서 프로젝트에 존재하는 파일들을 작성할 때 utf-8로 작성할 것인지, 특정 cpp 파일에서 탭을 공백 몇개로 지정할 것인지 적어서 세팅할 수 있게 해준다. (.editorconfig 파일은 프로젝트 폴더 최상위에 위치해야하며 우측 클릭으로 Generate .editorconfig를 하여 만들 수도 있다.)

1.  Error Lens by Alexander  
VS Code 코드 에디터에서 코드 에러 띄우는 기능을 개선해준다.

1.  Partial Diff by Ryuichi Inagaki  
코드 각 부분의 문자열 비교를 할 때 용이하다.

1.  Path Intellisense by Christian Kohler  
해당 플러그인을 설치하면 코드에서 파일 경로를 치는 경우 자동완성 기능이 제공된다.

1.  C++ Helper by amir  
함수 선언부에 우클릭을 하면 함수 정의부를 만들 수 있는 옵션이 뜬다.  
클릭 몇 번으로 함수 정의부를 만들어 주고 ```ifndef __HEADER_GUARD__``` 와 같은 헤더 가드도 생성해준다.

1.  CMake Tools by Microsoft  
CMake 관련된 작업을 할 때 유용하다.  
명령 팔레트에서 ```CMake: Configure```를 실행하면 VS CODE 파란색 하단 메뉴 목록에서 CMake 빌드 UI가 나타난다.  
makefile로 명령어를 묶어 실행해 빌드하는 스타일이라면 꺼놓는 것이 좋다.  

1.  C/C++ Include Guard by Akira Miyakoda  
헤더 파일을 생성할 때 자동으로 헤더 가드를 붙여준다. (**설치 선택**)  
&nbsp;  

## VS Code 환경 설정  
C++을 빌드할 수 있는 환경이 다양한 플러그인 설치를 통해 만들어졌다면 이제 실제 코드를 작성하는 경우 생산성을 높여주는 것들에 대해서 알아본다.  
  
1. ```VS Code 설정(좌측 하단 톱니바퀴 아이콘) -> 확장 -> C/C++```에 들어가서 Clang_format_fallback Style에  
	```
	{
		BasedOnStyle: Google,
		IndentWidth: 4,
		ColumnLimit: 0 
	}
	```
	위와 같이 넣어준다.  
	만약 자신이 Google 포맷이 싫고 Visual Studio에서 사용하던 formatting에 익숙하다면  
	```
	{
	    BasedOnStyle: LLVM, 
	    UseTab: Never, 
	    IndentWidth: 4, 
	    TabWidth: 4, 
	    BreakBeforeBraces: Allman, 
	    AllowShortIfStatementsOnASingleLine: false, 
	    IndentCaseLabels: false, 
	    ColumnLimit: 0, 
	    AccessModifierOffset: -4, 
	    NamespaceIndentation: All, 
	    FixNamespaceComments: false 
	}
	```
	위와 같은 내용을 집어넣어도 된다.  
	clang-format은 순전히 사용자의 선호도에 따라 세팅이 천차만별이기 때문에 정답은 없다.  

2. Clang_format_style에도 Clang_format_fallback Style와 같은 내용을 넣어준다.  

3. 취향에 따라 Before Else(else를 새 줄에 배치)와 같은 세부 구성을 설정한다. (써보니 설정한 Clang Format이 나한테 정말 잘 맞다 싶으면 굳이 세부 구성 설정까지 안해도 된다.)  

4. ```VS Code 설정(좌측 하단 톱니바퀴 아이콘) -> 텍스트 편집기 -> 서식```에서 Format On Paste, Format On Save, Format On Save Mode를 모두 켜준다.   
세이브를 하거나 세미콜론을 붙이거나(이 경우 해당 줄만) 텍스트를 붙여넣는 경우 지정한 clang format 형식에 맞춰 텍스트를 재조립해준다.  
&nbsp;  

## CMake 환경설정  
코드를 작성하는 환경이 편해졌으니 이제 빌드 환경을 설정해야 한다.  
  
1. 일단 CMake와 VS Code를 이용해서 빌드하는 방식에는 대략 3가지가 있다.  
     
	1. 첫번째는 CMake를 사용하되 CMake Tools는 사용하지 않고 빌드를 Makefile 혹은 bash 파일을 따로 작성하여 빌드하는 방식이다.  
	이 방식은 빌드 명령어 작성이 편해지지만 디버깅 환경 설정이 불편하고 CMake의 빌드 구성 파일과 코드 간의 연동이 느슨하여 코드에서 실제로 오류가 아닌데 오류라고 뜨는 경우가 많다... 이런 경우 막상 빌드를 하면 잘 되지만 빨간색 오류들이 매우 거슬린다.  
	이러한 이유 때문에 첫번째 방식은 비추천이다.  

   	1. 두번째는 CMake, CMake Tools를 사용하는데 VS Code의 settings.json을 이용하는 방식이다.  
	settings.json을 사용하기 때문에 CMake Tools를 잘 활용할 수 있다.  
	즉 CMake Tools 설치하고 명령 팔레트에서 ```CMake: Configure```를 실행하면 제공되는 VS Code 에디터 하단의 파란색 바에 다양한 빌드 관련 설정 UI 들을 사용할 수 있다. 
	두번째 방식을 진행하는 절차는 다음과 같다.    
		1. settings.json을 생성해주기 위해서 VS Code의 명령 팔레트에서 ```Preferences: Open Workspace Settings (JSON)``` 를 실행해준다.  
		이러면 .vscode 폴더 내에 settings.json이 생성될 것이다.  
		
		2. CMake 사용을 위한 settings.json 파일에서 각 요소에 대해 설명하겠다.  
			```json
			{
    			"cmake.sourceDirectory": "${workspaceFolder}",
    			"cmake.buildDirectory": "${workspaceFolder}/Build/${buildType}",
    			"cmake.buildBeforeRun": true,
    			"cmake.saveBeforeBuild": true,
    			"cmake.buildToolArgs": [
    			    // "--target AudioLib"
    			],
    			"cmake.configureArgs": [
    			    // "--graphviz=${command:cmake.buildDirectory}/Graph_Info/graph.dot"
    			],
    			"cmake.configureSettings": {
    			    // "CMAKE_CXX_FLAGS": "-O3 -Wall -m64" // -m32로 32비트용 빌드
    			},
    			"cmake.parallelJobs": 12,
    			"cmake.generator": "Unix Makefiles"
			}
			```
			* cmake.sourceDirectory  
				프로젝트 최상위 CMakeLists.txt가 위치한 경로  

			* cmake.buildDirectory  
				빌드 생성 파일이 위치하게 될 경로  

			* cmake.buildBeforeRun  
				실행 파일 실행 전에 빌드를 수행할 것인지 여부  

			* cmake.saveBeforeBuild  
				빌드 전에 빌드 관련 파일들을 저장할 것인지 여부    

        	* cmake.buildToolArgs   
				CMake 빌드 명령어에 추가할 부가적인 명령 인자들

        	* cmake.configureArgs   
				CMake 구성 명령어에 추가할 부가적인 명령 인자들			 		

        	* cmake.configureSettings   
				CMake 구성시에 변수들 값을 지정하는데 쓰임		

        	* cmake.parallelJobs   
				CMake 빌드 명령어시 "-j"와 같은 역할, 빌드시 동시 수행되는 작업 스레드 개수를 의미함		

        	* cmake.generator   
				Unix Makefiles, Ninja와 같은 CMake generator가 적힘		

        3. settings.json을 알맞게 작성해주었으면 CMake Tools가 제공하는 아래쪽 하단의 파란색 바를 이용해 빌드 구성과 컴파일러, 타켓을 정해주고 빌드해주면 된다.  

	1. 세번째는 가장 추천되는 방법으로 CMakePresets.json을 설정하는 방법이다.  
	해당 방법은 CMake 버전 3.20 이상부터 지원되며 VS Code 외에도 CLion, Qt Creator, Visual Studio에서도 지원된다.  
	가장 추천되는 이유는 구성 단계와 빌드 단계를 분리하여 입맛에 맞게 추가하는 것이 제일 직관적이고 settings.json, task.json 등 부가적인 파일들의 필요성이 적어지기 때문이다.
	세번째 방법을 진행하는 절차는 밑과 같다.  

		1. 일단 최상위 CMakeLists.txt 위치에 CMakePresets.json을 만들어 넣는다.

		1. CMakePresets.json를 작성해줘야 하는데 일단 대략적인 형식은 밑과 같다.  
			```json
			{
			    "version": 4,
			    "cmakeMinimumRequired": {
			        "major": 3,
			        "minor": 23,
			        "patch": 0
			    },
			    "configurePresets": [
			        {
			            "name": "base",
			            "hidden": true,
			            "binaryDir": "${sourceDir}/Build/${presetName}",
			            "installDir": "${sourceDir}/Installed"
			        },
			        {
			            "description": "Windows에서 Unix Makefiles와 Clang 컴파일러 사용",
			            "name": "windows-base",
			            "hidden": true,
			            "generator": "Unix Makefiles",
			            "inherits": "base",
			            "cacheVariables": {
			                "CMAKE_C_COMPILER": "clang",
			                "CMAKE_CXX_COMPILER": "clang++",
			                "CMAKE_TOOLCHAIN_FILE": "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
			            },
			            "condition": {
			                "type": "equals",
			                "lhs": "${hostSystemName}",
			                "rhs": "Windows"
			            }
			        },
			        {
			            "name": "x64-debug",
			            "displayName": "x64 Debug",
			            "inherits": "windows-base",
			            "architecture": {
			                "value": "x64",
			                "strategy": "external"
			            },
			            "cacheVariables": {
			                "VCPKG_TARGET_TRIPLET": "x64-windows-static",
			                "CMAKE_BUILD_TYPE": "Debug"
			            }
			        },
			        {
			            "name": "x64-release",
			            "displayName": "x64 Release",
			            "inherits": "x64-debug",
			            "cacheVariables": {
			                "VCPKG_TARGET_TRIPLET": "x64-windows-static",
			                "CMAKE_CXX_FLAGS": "-O3 -Wall",
			                "CMAKE_BUILD_TYPE": "Release"
			            }
			        },
			        {
			            "name": "x86-debug",
			            "displayName": "x86 Debug",
			            "inherits": "windows-base",
			            "architecture": {
			                "value": "x86",
			                "strategy": "external"
			            },
			            "cacheVariables": {
			                "VCPKG_TARGET_TRIPLET": "x86-windows-static",
			                "CMAKE_BUILD_TYPE": "Debug"
			            }
			        },
			        {
			            "name": "x86-release",
			            "displayName": "x86 Release",
			            "inherits": "x86-debug",
			            "cacheVariables": {
			                "VCPKG_TARGET_TRIPLET": "x86-windows-static",
			                "CMAKE_CXX_FLAGS": "-O3 -Wall",
			                "CMAKE_BUILD_TYPE": "Release"
			            }
			        },
			        {
			            "name": "linux-base",
			            "hidden": true,
			            "generator": "MinGW Makefiles",
			            "inherits": "base",
			            "toolchainFile": "$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
			            "cacheVariables": {
			                "CMAKE_C_COMPILER": "clang",
			                "CMAKE_CXX_COMPILER": "clang++"
			            },
			            "condition": {
			                "type": "equals",
			                "lhs": "${hostSystemName}",
			                "rhs": "Linux"
			            }
			        },
			        {
			            "name": "macos-base",
			            "hidden": true,
			            "generator": "Ninja",
			            "inherits": "base",
			            "cacheVariables": {
			                "CMAKE_C_COMPILER": "clang",
			                "CMAKE_CXX_COMPILER": "clang++",
			                "CMAKE_TOOLCHAIN_FILE": "~/vcpkg/scripts/buildsystems/vcpkg.cmake"
			            },
			            "condition": {
			                "type": "equals",
			                "lhs": "${hostSystemName}",
			                "rhs": "Darwin"
			            }
			        }
			    ],
			    "buildPresets": [
			        {
			            "name": "x64-debug-default",
			            "displayName": "Default",
			            "jobs": 12,
						"targets": [
                			"Graphviz",
                			"AudioLib"
            			],
			            "configurePreset": "x64-debug"
			        },
			        {
			            "name": "x64-release-default",
			            "displayName": "Default",
			            "jobs": 12,
			            "configurePreset": "x64-release"
			        }
			    ],
			    "testPresets": [
			        {
			            "name": "x64-debug-default",
			            "displayName": "Default",
			            "output": {
			                "outputOnFailure": true
			            },
			            "execution": {
			                "noTestsAction": "error",
			                "stopOnFailure": true
			            },
			            "configurePreset": "x64-debug"
			        }
			    ]
			}
			```
			* version  
				CMakePresets.json의 버전이다.  
				보통 4로 해놓고 신경쓰지 않는다.    

			* cmakeMinimumRequired  
				CMake의 최소 지원 버전을 적어준다.    

			* configurePresets  
				CMake 구성에 관련된 프리셋이 적힌다.    

			* description   
				특정 항목에 대한 설명이 들어간다.     

			* name  
				프리셋 이름이다.  
				다른 프리셋의 이름과 같을 순 없다.   
				configurePresets과 buildPresets 등 프리셋 종류가 다른 경우에는 이름이 겹쳐도 상관없다.     

        	* hidden   
				프리셋을 숨길지 여부  

        	* generator   
				Ninja, Unix Makefile과 같은 CMake generator			 		

        	* binaryDir   
				빌드 생성 파일이 위치하게 될 경로		

        	* installDir   
				```CMAKE_INSTALL_PREFIX```에 경로 지정하는 것과 같은 효과		

        	* inherits   
				프리셋을 상속하는데 사용됨   
				문자열 말고 배열로 여러개 상속할 수도 있음	 

			* architecture  
				프로젝트 빌드 대상 아키텍쳐에 대한 정보를 적는다.      

			* cacheVariables  
				CMake 빌드 구성시에 설정할 변수 값들을 넣어준다.      

        	* displayName   
				실제 UI 보이는 이름을 결정한다.  

			* condition  
				특정 조건이 맞는 경우한 프리셋이 보이게 된다.     
				만약 밑과 같은 예시라면  
				```
				"condition": {
			    	"type": "equals",
			    	"lhs": "${hostSystemName}",
			    	"rhs": "Windows"
			    }					
				```  
				type이 equals로 lhs와 rhs에 적힌 스트링을 비교하여 같은 경우를 따지고 있으므로 Windows 플랫폼에서 빌드하는 경우에만 프리셋이 보일 것이다.  

			* buildPresets  
				CMake 빌드와 관련된 프리셋이 적힌다.   
				buildPresets은 무조건 하나 이상의 configurePreset과 매칭되어야 한다.  
				특정 configurePreset이 설정되었을 때 그와 관련된 buildPresets만을 설정할 수가 있다.  
				따라서 hidden 속성이 true인 configurePreset과 buildPresets을 매칭시켰다면 해당 buildPresets은 사용할 수 없는 상태가 되는데 이를 유의하자.  

        	* jobs   
				CMake 빌드 명령어에서 "-j"와 같은 역할이다.  			 		

        	* targets   
				CMake 빌드 명령어에서 --target과 같은 역할이다.  	
				해당 정보가 없는 빌드 프리셋은 CMake Tools에서 제공하는 하단의 파란색 바에서 따로 빌드 타켓을 정해줘야 한다.	

        	* testPresets   
				CTest로 테스르를 진행할 때 사용될 프리셋이다.  
				CTest를 사용하지 않는다면 없어도 무방하다.  		

        	* toolchainFile   
				CMake의 CMAKE_TOOLCHAIN_FILE 변수를 지정하는 것과 동일한 효과지만 이게 더 추천된다.  

			더 자세한 정보는 [이곳](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html)에 적혀있다.  
		
		2. 해당 CMakePresets.json을 다 작성했다면 CMake Tools에서 제공하는 하단의 파란색 바에서 적절한 구성, 빌드 프리셋을 선택하고 빌드하면 된다.  
			파란색 바에서 CMake Tools 옵션들이 안보인다면 명령 팔레트에서 ```CMake: Configure```를 실행해보자.  
&nbsp;  

## 디버깅    
일단 원활할 디버깅을 하려면 컴파일러와 디버거를 맞춰줘야 한다. (clang은 lldb로... msvc는 vsdbg로... gcc는 gdb로...)  
만약에 빌드는 clang으로 했는데 해당 프로그램을 gdb로 디버깅하면 중단점이 작동하지 않는다.  
VS Code에서 디버깅을 하려면 일단 launch.json을 생성해줘야 한다.  
VS Code의 좌측 탭의 ```실행 밑 디버그```에 들어가서 launch.json 파일 만들기를 해보면 .vscode/launch.json을 생성해주는데 CodeLLDB 플러그인이 VS Code에 설치되어 있다면 LLDB 세팅을 처음에 추천할 것이다.  
일단 아무 세팅이나 선택해도 상관없다.  
.vscode/launch.json이 생성되었다면 해당 파일을 구성해야 하는데 일단 LLDB 구성부터 보겠다.  
&nbsp;  

밑은 launch.json 파일의 LLDB 구성이다.
```json
{
    "type": "lldb",
    "request": "launch",
    "name": "LLDB Debug",
    "program": "${command:cmake.launchTargetPath}",
    "args": [],
    "cwd": "${workspaceFolder}"
}
``` 

* type  
lldb를 쓸 것이기에 lldb로 고정한다.  

* request  
디버그 구성형식을 지정한다.  
보통 launch로 구성하고 특수한 경우에만 attach로 설정한다.  

* name  
해당 디버그 구성에 대한 이름을 정하면 된다.  

* program  
디버깅을 진행할 실행 프로그램의 경로를 적어준다.  
VS Code의 CMake Tools이 알아서 지정하도록 위 예시처럼 ```${command:cmake.launchTargetPath}``` 요렇게 선언 해놓는 것이 편하다.  
json에서 사용할 수 있는 command:cmake의 종류는 [이곳](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/cmake-settings.md)에 적혀있다.  

* args  
실행 파일에 전달할 파라메터를 적어준다.  

* cwd  
작업 디렉토리 경로를 적어준다.  
&nbsp;  

밑은 launch.json 파일의 MSVC 디버거 구성이다.
```json
{
    "name": "Visual Studio Debug",
    "type": "cppvsdbg",
    "request": "launch",
    "program": "${command:cmake.launchTargetPath}",
    "args": [],
    "stopAtEntry": false,
    "cwd": "${workspaceFolder}",
    "environment": [],
    "console": "internalConsole"
}
```
같은 내용은 생략하고 새로운 옵션만 설명한다.  

* stopAtEntry   
이 녀석이 true면 디버그 진입점에서 중단점이 설정된 것 마냥 중단된다.  

* environment  
따로 환경 설정 관련해서 변수나 세팅이 존재한다면 여기다 적어준다.  

* console  
디버깅을 어디서 할지 결정한다.  
```internalConsole```면 VS Code 내부 터미널에서 진행되고 ```externalConsole```면 외부 콘솔창이 따로 켜지고 거기서 디버깅이 진행된다.   
&nbsp;  

밑은 launch.json 파일의 GDB 디버거 구성이다.
```json
{
    "name": "GDB Debug",
    "type": "cppdbg",
    "request": "launch",
    "program": "${command:cmake.launchTargetPath}",
    "args": [],
    "stopAtEntry": false,
    "cwd": "${workspaceFolder}",
    "environment": [],
    "externalConsole": false,
    "MIMode": "gdb",
    "miDebuggerPath": "C:/msys64/mingw64/bin/gdb.exe",
    "setupCommands": [
        {
            "description": "gdb에 자동 서식 지정 사용",
            "text": "-enable-pretty-printing",
            "ignoreFailures": false
        },
        {
            "description": "디스어셈블리 버전을 Intel(으)로 설정",
            "text": "-gdb-set disassembly-flavor intel"
        }
    ]
}
```
같은 내용은 생략하고 새로운 옵션만 설명한다.  

* externalConsole  
디버깅을 어디서 진행할지 결정하는 옵션이다.  
true인 경우 외부 콘솔창에서 디버깅이 진행된다.  

* MIMode  
gdb, lldb 둘 중 하나를 선택할 수 있는데 gdb를 사용할 것이니 gdb로 설정한다.  

* miDebuggerPath  
MIMode에 지정된 컴파일러의 경로가 적힌다.  
gdb를 설정하였으니 gdb의 경로로 지정해준다.  

* setupCommands  
gdb 실행시 같이 넘겨줄 인자들을 정의한다.  
&nbsp;  
 
완성된 launch.json의 모습은 밑과 같다.  
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "GDB Debug",
            "type": "cppdbg",
            "request": "launch",
            "program": "${command:cmake.launchTargetPath}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:/msys64/mingw64/bin/gdb.exe",
            "setupCommands": [
                {
                    "description": "gdb에 자동 서식 지정 사용",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": false
                },
                {
                    "description": "디스어셈블리 버전을 Intel(으)로 설정",
                    "text": "-gdb-set disassembly-flavor intel"
                }
            ]
        },
        {
            "name": "Visual Studio Debug",
            "type": "cppvsdbg",
            "request": "launch",
            "program": "${command:cmake.launchTargetPath}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "console": "internalConsole"
        },
        {
	    "name": "LLDB Debug",
            "type": "lldb",
            "request": "launch",
            "program": "${command:cmake.launchTargetPath}",
            "args": [],
            "cwd": "${workspaceFolder}"
        }
    ]
}
```
위 launch.json에서 개별적인 항목을 사용자 환경에 알맞게 수정해서 사용하면 된다.  
디버깅을 시작하고 싶다면 중단점을 찍고 F5를 누르면 된다.   

## Intellisense  

위 항목까지 진행하면 빌드와 실행은 원활하게 잘 될 것이다.  
문제는 VS Code 편집기에서 include path를 분명히 포함했는데 찾지 못한다고 경고 문구가 뜨는 경우가 있다는 것이다.  
이러한 문제를 해결해주기 위해서 c_cpp_properties.json 파일을 추가적으로 작성해줘야 한다.  
c_cpp_properties.json도 다른 json 파일들과 마찬가지로 .vscode 폴더 내부에 위치해야 한다.  

밑은 c_cpp_properties.json 파일 모습이다.  
```json
{
  "configurations": [
    {
      "name": "Win32",
      "includePath": [
        "${workspaceFolder}/**"
      ],
      "compilerPath": "C:/Program Files/Microsoft Visual Studio/2022/Professional/VC/Tools/MSVC/14.16.27023/bin/HostX64/x64/cl.exe",
      "defines": [
        "_DEBUG",
        "UNICODE",
        "_UNICODE"
      ],
      "cStandard": "c11",
      "cppStandard": "c++17",
      "intelliSenseMode": "windows-msvc-x64",
	  "compileCommands": "${command:cmake.buildDirectory}/compile_commands.json",
      "configurationProvider": "ms-vscode.cmake-tools"
    }
  ],
  "version": 4
}
```
각 옵션들에 대한 내용은 밑과 같다.  

* name  
플랫폼을 특정하여 Linux, Mac, Win32 중 선택할 수도 있고 그냥 원하는 데로 적어도 된다.  

* includePath  
Intellisense에 필요한 포함 파일 경로를 지정하면 된다.  
필자는 프로젝트 하위 어떤 폴더든 포함하기 위해 ```${workspaceFolder}/**```로 지정했다.  

* compilerPath  
컴파일러 경로를 적어주면 된다.  
Windows 기준으로 컴파일러에 따라 GCC는 gcc.exe, Clang은 clang.exe, MSVC는 cl.exe를 찾아서 적어주면 된다.  

* defines  
Intellisense에 필요한 프로젝트 전처리기를 지정하면 된다.  
컴파일러에서 지정해준 것과 동일하게 적어주자.  

* cStandard    
Intellisense에 필요한 C언어 버전을 적어주자.  

* cppStandard    
Intellisense에 필요한 C++언어 버전을 적어주자.  

* intelliSenseMode  
compilerPath에서 지정한 컴파일러가 지원하는 Intellisense 모드를 지정할 수 있다.  
```linux-gcc-x86```, ```ios-clang-x64```와 같이 ```<플랫폼>-<컴파일러>-<아키텍쳐>``` 조합에 따라 굉장히 많다.  

* compileCommands  
Intellisense에 필요한 컴파일러 부가 명령에 대한 파일인 compile_commands.json 경로를 적어주는 옵션이다.  
CMake에서 생성한 compile_commands.json를 이용할 것이기에 ```${command:cmake.buildDirectory}/compile_commands.json```로 설정했다.  
compile_commands.json은 CMake의 CMAKE_EXPORT_COMPILE_COMMANDS 옵션을 ON으로 설정하여 생성할 수 있다.  
주의점은 generator가 Ninja, MakeFile인 경우만 작동한다는 것으로 MSVC 컴파일러를 이용한다면 사용할 수 없다.  

* configurationProvider  
Intellisense 구성 제공자에 대한 정보를 넘겨준다.  
```ms-vscode.cmake-tools```로 지정했다면 부가적인 include 파일 정보를 CMake로부터 제공받는다.  
```ms-vscode.cpptools```로 지정했다면 부가적인 include 파일 정보를 c_cpp_properties.json 파일의 ```includePath``` 부분으로부터 제공받는다.  

c_cpp_properties.json 내용이 수정되면 VS Code를 한 번 껏다가 켜야 적용된다.  
c_cpp_properties.json은 빌드 과정에서는 전혀 쓰이지 않고 Intellisense 부분에만 쓰인다는 점을 유의하자.  
&nbsp;  

## Compiler와 Generator 특성  

Compiler와 Generator마다 전달해주는 인자들도 다르고 빌드할 때 생성되는 파일들도 가지각색이라 사용 방식도 모두 다르다.  
각기다른 특성들을 한번 알아보자.  
&nbsp;  

먼저 Compiler부터 알아보자.  

* Visual Studio  
Visual Studio라 하면 통합 빌드툴로 보통 사용하게 되는데 CMake와 함께 사용될 때는 컴파일러와 Generator만 사용하게 된다.  
컴파일러 이름은 cl.exe인데 이렇게 지정해서 쓰는 경우는 거의 없다.  
CMake에서 Visual Studio를 연동해 사용할 때는 직접적인 컴파일러 지정없이 generator만 Visual Studio 관련하여 지정해주면 된다.  
예를 들어 자신이 Visual Studio 2022 버전을 사용한다면 Visual Studio 17 2022이 되고 Visual Studio 2019 버전을 사용한다면 Visual Studio 16 2019이 된다.  
Visual Studio는 다른 컴파일러와 다르게 CMake Config 시간이 아닌 CMake Build 시간에 Release와 Debug가 결정되는 방식을 사용한다.  
따라서 CMake로 빌드를 할 때 Release 모드를 사용하고 싶다면 ```--config Release``` 인자를 같이 넘겨주어야 한다.  
또 빌드 시 유의사항으로는 다중 코어 빌드를 사용하고 싶다면 ```--parallel``` 옵션보다 ```-- /maxcpucount /nologo /verbosity:minimal``` 이렇게 옵션을 주어 Visual Studio에 옵션 인자를 직접 전달해주는 방식이 추천된다.  
CMake Config 시간에는 아키텍쳐를 꼭 지정해주어야 한다.  
예를 들어 자신이 x86 시스템 타겟으로 빌드하고 싶다면 ```-A Win32``` 인자를 같이 넘겨주어야 한다. (x64 타겟은 ```-A x64```)  
컴파일러에 전달하는 인자는 보통 ```/D<변수명>``` 이렇게 사용한다. (ex. ```/D_CRT_SECURE_NO_WARNINGS```)   
보통 사용하게 되는 인자들로는 ```/MP```, ```/EHsc```, ```/permissive-```, ```/JMC```가 있다. (각 인자의 의미는 Visual Studio에서 찾아보자...)  
빌드 타겟을 따로 지정해주지 않았을 경우 기본적으로 생성해주는 타겟은 ALL_BUILD, ZERO_CHECK이 있다.  
ALL_BUILD는 말 그대로 모든 빌드 요소를 다 빌드하는 것이고 ZERO_CHECK는 CMake Configuration을 다시 진행하는 것이다.  

* Clang  
CMake와 가장 조합이 좋은 컴파일러인 Clang이다.  
다른 컴파일러들은 OS에 따라 설치 방식 차이가 많이나서 귀찮은데 Clang은 설치도 간단하고 대표적인 Windows. Mac, Linux 등에서 잘 작동하기 때문에 크로스 플랫폼 프로그램을 개발하고 있다면 앵간해서 Clang 쓰자.  
Clang은 어떤 Generator를 사용하던 상관이 없지만 보통 Ninja를 많이 사용한다.  
컴파일러에 인자를 전달할 때 GCC Style을 보통 사용하는데 중요한 인자로는 x86 빌드할 때 ```-m32```, x64 빌드할 때 ```-m64```, 속도 최적화 ```-O3``` 등이 있다.  
더 많은 인자는 Clang 홈페이지에서 찾아보자.  
Clang은 Config 시간에 빌드 방식이 결정되기 때문에 Release 방식으로 빌드하고 싶다면 CMAKE_BUILD_TYPE 값을 Release로 설정해줘야 한다.  
빌드 타겟을 따로 지정해주지 않았을 경우 기본적으로 생성해주는 타겟은 all이 있다.  
all은 Visual Studio의 ALL_BUILD와 같은 기능을 한다.  

* GCC  
Clang과 대부분의 특성은 모두 똑같은데 가장 큰 차이점이라면 x86 타겟 버전을 빌드하는 것이 굉장히 힘들다.  
GCC로 x86 타켓 프로그램을 빌드하고 싶다면 gcc-multilib, g++-multilib를 설치하거나 x64용 toolchain과 x86용 toolchain을 하나의 GCC에 연결해주거나 아니면 x64용 GCC와 x86용 GCC를 모두 설치해야 한다.  

&nbsp;  
다음은 Generator를 알아보자.  

* Ninja  
CMake와 가장 조합이 좋은 Generator인 Ninja다.  
이 녀석도 마찬가지로 대표적인 Windows. Mac, Linux 등에서 잘 작동하기 때문에 크로스 플랫폼 프로그램을 개발하고 있다면 설치와 설정이 쉬운 Ninja를 사용하자.  
Ninja는 CMake Build 시간에 ```--parallel``` 옵션을 굳이 사용해주지 않아도 알아서 최대 코어를 이용하여 빌드를 수행한다.  

* Makefiles 계열  
MinGW, Unix 등의 Makefiles 계열은 보통 추가적인 설치가 필요없이 컴파일러와 같이 깔리는 경우가 대부분이다.  
병렬 빌드를 사용하고 싶다면 CMake Build 시간에 ```--parallel``` 옵션을 사용해도 되고 ```-- -j```로 Makefiles에 직접 인자를 전달해줘도 된다.   

## 부가적인 세팅  

안해도 되지만 하면 더 좋은 세팅들을 나열한다.  

* 글꼴  
텍스트 에디터에서 글꼴은 생각보다 많이 중요하다.  
필자가 좋아하는 글꼴은 ```Cascadia Code```로 모든 영어, 숫자, 특수 문자의 크기가 동일하기 때문에 가독성이 좋아진다.  
VS Code에서 글꼴 설정은 ```설정 -> 텍스트 편집기 -> 글꼴 -> Font Family```에 위치하며 여러 개를 지정해 줄 수 있는데 순서에 따라 맨 앞 글꼴이 우선적으로 적용된다.  

* 테마  
필자가 선호하는 VS Code 테마는 ```One Dark Pro```이고 그 중에서도 Darker 버전을 좋아한다.  
선호하는 이유는 변수, 함수, 자료형 등의 색이 확연히 구분되어 가독성이 좋으면서 전체적으로 어두워 눈이 덜 아프기 때문이다.   
VS Code 테마를 적용하려면 일단 확장에서 원하는 테마를 설치하고 Ctrl + K,T 를 누르고 설치된 테마를 선택하면 된다.  
색테마 이외의 파일 아이콘 테마나 제품 아이콘 테마 등은 번잡해서 사용하지 않는다.  