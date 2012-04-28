mkdir -p bin
mkdir -p obj
mkdir -p obj/Debug
make --directory=./obj/Debug --makefile=../../Makefile build_flags="-O0 -D_DEBUG" program_name=../../bin/tracing_service_debug
