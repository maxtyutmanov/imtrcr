mkdir -p bin/UnitTest
mkdir -p obj
mkdir -p obj/UnitTest
make test="yes" --directory=./obj/UnitTest --makefile=../../Makefile build_flags="-O0 -D_DEBUG" program_name=../../bin/UnitTest/tracing_service_unit_tests
cp misc/test_move_to_output/* bin/UnitTest
cd bin/UnitTest
./tracing_service_unit_tests
