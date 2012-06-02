mkdir -p bin
mkdir -p obj
mkdir -p obj/Release
make --directory=./obj/Release --makefile=../../Makefile build_flags="-O2 -D_DEBUG" program_name=../../bin/tracing_service_release
