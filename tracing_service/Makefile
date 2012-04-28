root_include_dir := include
root_source_dir := src
root_libs_dir := lib
root_libs_include_dir := $(root_libs_dir)
libs_names := tinyxml
source_subdirs := . imaging vectorization
compile_flags := -Wall -MD -pipe
link_flags := -s -pipe
libraries := -lboost_system -lboost_filesystem

#prj/include/imaging/...
relative_include_dirs := $(addprefix ../../, $(root_include_dir) $(root_libs_include_dir))
#prj/src/imaging/...
relative_source_dirs := $(addprefix ../../$(root_source_dir)/, $(source_subdirs))
#prj/obj/Debug|Release/src/imaging/...
objects_dirs := $(addprefix $(root_source_dir)/, $(source_subdirs))
objects := $(patsubst ../../%, %, $(wildcard $(addsuffix /*.cpp, $(relative_source_dirs))))
objects := $(objects:.cpp=.o)

all : $(program_name)

$(program_name) : obj_dirs build_libs $(objects)
	g++ -o $@ $(objects) $(link_flags) $(libraries)

obj_dirs :
	mkdir -p $(objects_dirs)

.PHONY : build_libs
build_libs :
	$(foreach lib_dir, $(relative_libs_dirs), make --directory=$(lib_dir) --makefile=$(lib_dir)/Makefile)

VPATH = ../../

%.o : %.cpp
	g++ -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs))

.PHONY : clean

clean :
	rm -rf bin obj

include $(wildcard $(addsuffix /*.d, $(objects_dirs)))