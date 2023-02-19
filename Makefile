compiler		=	g++

cpp_standard	=	-std=c++11

my_cpp_files	=	src/main.cpp	\
					src/Gravity.cpp	\
					src/GUI.cpp

framewerke		=	-framework CoreFoundation	\
					-framework OpenGL			\
					-framework Cocoa			\
					-framework IOKit			\
					-framework CoreVideo

libs			=	include/libglfw.3.dylib					\
					include/glad.o

flags			=	-lglfw

deprec_warnings =  -Wdeprecated \
				   -Wreturn-type

final_name		=	app

success: compile
	@echo "-------------------------------------"
	@echo "\tSuccessfully Compiled"
	@echo "-------------------------------------"

compile:
	$(compiler) $(cpp_standard) $(framewerke) $(my_cpp_files) $(libs) $(flags) $(deprec_warnings) -o $(final_name)

run:
	./app
