root_include_dir := include
root_source_dir := src
root_libs_dir := lib
root_libs_include_dir := $(root_libs_dir)
libs_names := tinyxml sqlite3
source_subdirs := imaging vectorization utils soap_service
compile_flags := -Wall -MD -pipe
link_flags := -s -pipe
libraries := -lboost_system -lboost_filesystem -lpthread -ldl

ifeq ($(test),yes)
  source_subdirs := $(source_subdirs) unit_tests
  libraries := $(libraries) -lboost_unit_test_framework
else
  source_subdirs := $(source_subdirs) .
endif

#prj/include/imaging/...
relative_include_dirs := $(addprefix ../../, $(root_include_dir) $(root_libs_include_dir))
#prj/src/imaging/...
relative_source_dirs := $(addprefix ../../$(root_source_dir)/, $(source_subdirs))
relative_libs_dirs := $(addprefix ../../$(root_libs_dir)/, $(libs_names))
#prj/obj/Debug|Release/src/imaging/...
objects_dirs := $(addprefix $(root_source_dir)/, $(source_subdirs))
objects := $(patsubst ../../%, %, $(wildcard $(addsuffix /*.cpp, $(relative_source_dirs))))
objects := $(objects:.cpp=.o)
libs_archives := $(addprefix ../../$(root_libs_dir)/lib, $(libs_names))
libs_archives := $(addsuffix .a, $(libs_archives))

all : $(program_name)

$(program_name) : obj_dirs $(libs_archives) $(objects)
	g++ -o $@ $(objects) $(link_flags) $(libs_archives) $(libraries)

obj_dirs :
	mkdir -p $(objects_dirs)

$(libs_archives) :
	$(foreach lib_dir, $(relative_libs_dirs), make --directory=$(lib_dir) create_archive)

VPATH = ../../

%.o : %.cpp
	g++ -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs) $(patsubst ../../src/%, ../../include/%, $(dir $<))) $(libs_archives)

.PHONY : clean

clean :
	rm -rf bin obj
	$(foreach lib_dir, $(addprefix $(root_libs_dir)/, $(lib_names)), make --directory=$(lib_dir) clean)

include $(wildcard $(addsuffix /*.d, $(objects_dirs)))