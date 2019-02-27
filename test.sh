#!/bin/bash

function test_file() {
	echo testing file $1
	diff <(./ft_nm $1) <(nm $1)
	if [ $? = 0 ]
	then
		echo OK
	fi
}

test_file objs/nm/main.o
test_file ft_nm
test_file /usr/bin/audiodevice
test_file ../ft_malloc_tests/ft_malloc/libft_malloc.so
test_file /bin/bash
for i in ../corrupted_binaries/* ; do echo $i; ./ft_nm $i > /dev/null ; done
