# C++ 빌드를 위한 VS Code 세팅

## VS Code에서 C++ 빌드를 하기 위한 사전 준비

1. Microsoft Store에 들어가서 Windows Terminal을 설치해준다.  

2. Windows Terminal에서 PowerShell 탭을 열고 ```$PSVersionTable``` 명령어를 수행한 뒤에 출력된 PSVersion이 3 이상인지 확인한다. (3이하라면 PowerShell을 업데이트해준다. PowerShell 업데이트 방법은 알아서 찾아라...)  

3. .NET Framework 4.5 버전 이상이 설치되어 있는지 확인한다. (Visual Studio에서 ```.NET 테스크톱 개발``` 항목을 선택하면 알아서 최신버전의 .NET Framework를 설치해준다.)  

4. Windows Terminal을 관리자 모드로 열고 PowerShell 탭을 띄운후에 Get-ExecutionPolicy 명령어를 수행 후에 Restricted인지 확인한다.  
Restricted이라면 Set-ExecutionPolicy AllSigned 명령어를 추가적으로 수행해준다.  

5. ```Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))``` 명령어를 수행해 Chocolatey를 설치해준다.  
  
6. 설치가 끝났으면 Windows Terminal를 관리자 모드로 재시작해주고 PowerShell 탭을 띄우고 choco 명령어를 수행해 Chocolatey가 잘 설치되었는지 확인한다.  
  
7. ```choco install graphviz```, ```choco install git```, ```choco install doxygen.install```, ```choco install python```, ```choco install make```, ```choco install llvm```, ```choco install ninja```, ```choco install cmake``` 명령어를 순차적으로 실행해서 CMake 활용에 필요한 프로그램들을 깔아준다.  
llvm은 clang 컴파일러를 사용하지 않을 것이라면 굳이 안깔아도 된다. (gcc, msvc 등 다른 좋은 컴파일러도 있지만 clang이 설치하기 가장 편하다.)  
make와 ninja는 둘 중 하나만 설치해도 된다. (ninja가 빌드할 때 좀 더 빠르다.)  
여기서 중요한 점은 CMake 시스템 환경변수가 올바르게 등록되었는지를 알아야 한다.  

8. CMake를 설치해도 PowerShell 관리자 모드에서 cmake --version 명령어가 제대로 실행되지 않는다면 환경변수가 제대로 설정되지 않은 것이니 시스템 속성 -> 고급 탭 -> 환경 변수 -> 시스템 변수 -> Path 에 cmake.exe가 위치한 폴더 경로를 추가해주자. (보통 ```C:\Program Files\CMake\bin``` 이거다.)   

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
C++ 디버깅할 때 유용하다.  

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
makefile로 명령어를 묶어 실행해 빌드하는 스타일이라면 꺼놓는 것이 좋다. (**설치 선택**)

1.  C/C++ Include Guard by Akira Miyakoda  
헤더 파일을 생성할 때 자동으로 헤더 가드를 붙여준다. (**설치 선택**)

## VS Code 환경 설정  
C++을 빌드할 수 있는 환경이 다양한 플러그인 설치를 통해 만들어졌다면 이제 실제 코드를 작성하는 경우 생산성을 높여주는 것들에 대해서 알아본다.  
  
1. ```VS Code 설정(좌측 하단 톱니바퀴 아이콘) -> 확장 -> C/C++```에 들어가서 Clang_format_fallback Style에 ```{ BasedOnStyle: LLVM, IndentWidth: 4, ColumnLimit: 0 }```이 녀석을 넣어준다.  
BasedOnStyle의 종류는 다양하니 clang format 종류를 검색해보자.  
Visual Studio를 많이 써왔다면 LLVM 대신 Microsoft가 친근할 것이다.    

2. Clang_format_style에도 ```{ BasedOnStyle: LLVM, IndentWidth: 4, ColumnLimit: 0 }``` 이 녀석을 넣어준다.

3. 취향에 따라 Before Else(else를 새 줄에 배치)와 같은 세부 구성을 설정한다. (써보니 설정한 Clang Format이 나한테 정말 잘 맞다 싶으면 굳이 세부 구성 설정까지 안해도 된다.)

4. ```VS Code 설정(좌측 하단 톱니바퀴 아이콘) -> 텍스트 편집기 -> 서식```에서 Format On Paste, Format On Save, Format On Save Mode를 모두 켜준다.   
세이브를 하거나 세미콜론을 붙이거나(이 경우 해당 줄만) 텍스트를 붙여넣는 경우 지정한 clang format 형식에 맞춰 텍스트를 재조립해준다.  

## CMake 환경설정  
코드를 작성하는 환경이 편해졌으니 이제 빌드 환경을 설정해야 한다.  
  
1. 일단 CMake와 VS Code를 이용해서 빌드하는 방식에는 대략 3가지가 있다.  
     
	1. 첫번째는 CMake를 사용하되 CMake Tools는 사용하지 않고 빌드를 Makefile 혹은 bash 파일을 따로 작성하여 빌드하는 방식이다.  
	이 방식은 빌드 명령어 작성이 편해지지만 디버깅 환경 설정이 불편하고 CMake의 빌드 구성 파일과 코드 간의 연동이 느슨하여 코드에서 실제로 오류가 아닌데 오류라고 뜨는 경우가 많다... 이런 경우 막상 빌드를 하면 잘 되지만 빨간색 오류들이 매우 거슬린다.  
	이러한 이유 때문에 첫번째 방식은 비추천이다.  

   	1. 두번째는 CMake, CMake Tools를 사용하는데 VS Code의 settings.json을 이용하는 방식이다.  
	settings.json을 사용하기 때문에 CMake Tools를 잘 활용할 수 있다.  
	즉 CMake Tools 설치하면 제공되는 VS Code 에디터 하단의 파란색 바에 다양한 빌드 관련 설정 UI 들을 사용할 수가 있다는 것이다.  
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
			            "cacheVariables": {
			                "CMAKE_C_COMPILER": "clang",
			                "CMAKE_CXX_COMPILER": "clang++",
			                "CMAKE_TOOLCHAIN_FILE": "$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
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

			더 자세한 정보는 https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html 이곳에 적혀있다.  
		
		1. 해당 CMakePresets.json을 다 작성했다면 CMake Tools에서 제공하는 하단의 파란색 바에서 적절한 구성, 빌드 프리셋을 선택하고 빌드하면 된다.  

## 디버깅  
디버깅 방식은 굉장히 편하다.  
Visual Studio와 같이 중단점을 찍고 F5로 디버깅을 시작하고 F10과 F11로 코드 라인에 따라 디버깅을 진행한다.  