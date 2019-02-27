#!/bin/bash

function test_nm() {
	echo testing file $1
	diff <(nm $1) <(./ft_nm $1)
	if [ $? = 0 ]
	then
		echo OK
	fi
}

function test_otool() {
	echo testing file $1
	diff <(otool -t $1) <(./ft_otool -t $1)
	if [ $? = 0 ]
	then
		echo OK
	fi
}

echo TESTING NM CORRUPTED
for i in ../corrupted_binaries/* ; do test_nm $i > /dev/null; done
echo TESTING OTOOL CORRUPTED
for i in ../corrupted_binaries/* ; do test_otool $i > /dev/null; done

echo TESTING NM
test_nm objs/nm/main.o
test_nm ft_nm
test_nm /usr/bin/audiodevice
test_nm ../ft_malloc_tests/ft_malloc/libft_malloc.so
test_nm /bin/bash

echo TESTING OTOOL
test_otool objs/nm/main.o
test_otool ft_nm
test_otool /usr/bin/audiodevice
test_otool ../ft_malloc_tests/ft_malloc/libft_malloc.so
test_otool /bin/bash
