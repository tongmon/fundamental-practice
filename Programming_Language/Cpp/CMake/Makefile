### 정의해놓으면 편한 Windows용 Makefile(컴파일러 경로는 자신의 환경에 알맞게 설정해줘야 한다.) ###
### 항상 최상위 CMakeLists.txt가 있는 위치에서 make 명령어를 수행할 것! ###
### 해당 Makefile을 이용하려면 CMakeLists.txt를 세이브할 때마다 CMake 세팅을 진행해주는 CMake Tools는 꺼놓고 하는게 좋다. (물론 CMake는 켜놔야 한다.) ###

# 명령어 make만 사용시 수행될 디폴트 모드
default_target: build

# 파일 업데이트 할 것이 없더라도 강제 실행
.PHONY: build rebuild prepare

# 특정 타겟
target=all

# C 컴파일러 경로
c_compiler=C:/Program Files/LLVM/bin/clang.exe

# C++ 컴파일러 경로
cxx_compiler=C:/Program Files/LLVM/bin/clang++.exe

# cmake 생성기 (ex. Ninja, Visual Studio 17 2022)
generator=Unix Makefiles

# 빌드 경로
build_path=./Build

# 빌드 타입
build_type=Debug

# 윈도우는 '/' 대신 '\' 이걸 경로 구분자로 쓰기 때문에 따로 정의해서 변형함
windows_build_path=$(subst /,\,$(build_path))

# 빌드 가속을 위한 병렬 빌드 처리 작업 개수
job_num = 12

build: # 빌드
	mkdir "$(windows_build_path)\$(build_type)" | cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE=$(build_type) -DCMAKE_C_COMPILER="$(c_compiler)" -DCMAKE_CXX_COMPILER="$(cxx_compiler)" -S . -B "$(build_path)/$(build_type)" -G "$(generator)" --graphviz="$(build_path)/$(build_type)/Graph_Info/graph.dot"
	dot -Tpng "$(build_path)/$(build_type)/Graph_Info/graph.dot" -o "$(build_path)/Graph_$(build_type).png"
	cmake --build "$(build_path)/$(build_type)" --target "$(target)" -j $(job_num)

rebuild: # 릴리즈용 재빌드
	rmdir /s /q $(windows_build_path)\$(build_type) | mkdir $(windows_build_path)\$(build_type) | cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE=$(build_type) -DCMAKE_C_COMPILER="$(c_compiler)" -DCMAKE_CXX_COMPILER="$(cxx_compiler)" -S . -B "$(build_path)/$(build_type)" -G "$(generator)" --graphviz="$(build_path)/$(build_type)/Graph_Info/graph.dot"
	dot -Tpng "$(build_path)/$(build_type)/Graph_Info/graph.dot" -o "$(build_path)/Graph_$(build_type).png"
	cmake --build "$(build_path)/$(build_type)" --target "$(target)" -j $(job_num)
	
prepare: # cmake 사전 준비
	mkdir "$(windows_build_path)\$(build_type)" | cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE=$(build_type) -DCMAKE_C_COMPILER="$(c_compiler)" -DCMAKE_CXX_COMPILER="$(cxx_compiler)" -S . -B "$(build_path)/$(build_type)" -G "$(generator)" --graphviz="$(build_path)/$(build_type)/Graph_Info/graph.dot"
	dot -Tpng "$(build_path)/$(build_type)/Graph_Info/graph.dot" -o "$(build_path)/Graph_$(build_type).png"
	
install: # ${CMAKE_BINARY_DIR}에서 make install 명령 실행
	$(MAKE) -C "$(build_path)/$(build_type)/" install
	
# 예를들어 터미널에서 make build_type=Release target=SDL2 generator="Visual Studio 17 2022" 를 하면 SDL2만 VS2022 생성기를 통해 Release 모드로 빌드된다.