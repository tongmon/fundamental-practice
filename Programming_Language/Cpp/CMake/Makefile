### 정의해놓으면 편한 Windows용 Makefile(컴파일러 경로는 자신의 환경에 알맞게 설정해줘야 한다.) ###
### 항상 최상위 CMakeLists.txt가 있는 위치에서 make 명령어를 수행할 것! ###
### 해당 Makefile을 이용하려면 CMakeLists.txt를 세이브할 때마다 CMake 세팅을 진행해주는 CMake Tools는 꺼놓고 하는게 좋다. (물론 CMake는 켜놔야 한다.) ###

# 명령어 make만 사용시 수행될 디폴트 모드
default_target: debug

# 파일 업데이트 할 것이 없더라도 강제 실행
.PHONY: debug release debug_cmake release_cmake

# 특정 타겟
target=all

# C 컴파일러
c_compiler=C:/msys64/mingw64/bin/gcc.exe

# C++ 컴파일러
cxx_compiler=C:/msys64/mingw64/bin/g++.exe

# cmake 생성기 (ex. Ninja, Visual Studio 17 2022)
generator=Unix Makefiles

# 빌드 경로
build_path=./build/

# 윈도우는 '/' 대신 '\' 이걸 경로 구분자로 쓰기 때문에 따로 정의해서 변형함
windows_build_path=$(subst /,\,$(build_path))

# 빌드 가속을 위한 병렬 빌드 처리 작업 개수
job_num = 12

release: # 릴리즈용 빌드
	mkdir $(windows_build_path)\Release | cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=$(c_compiler) -DCMAKE_CXX_COMPILER=$(cxx_compiler) -S . -B $(build_path)/Release -G "$(generator)" --graphviz=$(build_path)/Release/graph_info/graph.dot
	dot -Tpng $(build_path)/Release/graph_info/graph.dot -o $(build_path)/graph_release.png
	cmake --build $(build_path)/Release --target $(target) -j $(job_num)

debug: # 디버그용 빌드
	mkdir $(windows_build_path)\Debug | cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=$(c_compiler) -DCMAKE_CXX_COMPILER=$(cxx_compiler) -S . -B $(build_path)/Debug -G "$(generator)" --graphviz=$(build_path)/Debug/graph_info/graph.dot
	dot -Tpng $(build_path)/Debug/graph_info/graph.dot -o $(build_path)/graph_debug.png
	cmake --build $(build_path)/Debug --target $(target) -j $(job_num)

release_re: # 릴리즈용 재빌드
	rmdir /s /q $(windows_build_path)\Release | mkdir $(windows_build_path)\Release | cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=$(c_compiler) -DCMAKE_CXX_COMPILER=$(cxx_compiler) -S . -B $(build_path)/Release -G "$(generator)" --graphviz=$(build_path)/Release/graph_info/graph.dot
	dot -Tpng $(build_path)/Release/graph_info/graph.dot -o $(build_path)/graph_release.png
	cmake --build $(build_path)/Release --target $(target) -j $(job_num)

debug_re: # 디버그용 재빌드
	rmdir /s /q $(windows_build_path)\Debug | mkdir $(windows_build_path)\Debug | cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=$(c_compiler) -DCMAKE_CXX_COMPILER=$(cxx_compiler) -S . -B $(build_path)/Debug -G "$(generator)" --graphviz=$(build_path)/Debug/graph_info/graph.dot
	dot -Tpng $(build_path)/Debug/graph_info/graph.dot -o $(build_path)/graph_debug.png
	cmake --build $(build_path)/Debug --target $(target) -j $(job_num)
	
release_cmake: # 릴리즈용 CMake 세팅
	mkdir $(windows_build_path)\Release | cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=$(c_compiler) -DCMAKE_CXX_COMPILER=$(cxx_compiler) -S . -B $(build_path)/Release -G "$(generator)" --graphviz=$(build_path)/Release/graph_info/graph.dot
	dot -Tpng $(build_path)/Release/graph_info/graph.dot -o $(build_path)/graph_release.png
	
debug_cmake: # 디버그용 CMake 세팅
	mkdir $(windows_build_path)\Debug | cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=$(c_compiler) -DCMAKE_CXX_COMPILER=$(cxx_compiler) -S . -B $(build_path)/Debug -G "$(generator)" --graphviz=$(build_path)/Debug/graph_info/graph.dot
	dot -Tpng $(build_path)/Debug/graph_info/graph.dot -o $(build_path)/graph_debug.png
	
# 예를들어 터미널에서 make debug target=SDL2 generator="Visual Studio 17 2022" 를 하면 SDL2만 VS2022 생성기를 통해 Debug 모드로 빌드된다.
