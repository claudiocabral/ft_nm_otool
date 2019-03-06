#!/bin/sh

#############

bin_nm_mine=./ft_nm
bin_nm=nm
bin_otool_mine=./ft_otool
bin_otool=otool

##############

IFS=';'

dirs=(\
#"/bin;"\
#"/usr/bin;"\
"/usr/lib/;"\
"/Users/ccabral/local/lib" )

#############
output_mine="mine"
output_theirs="theirs"

##############

function print_result() {
	diff $output_mine $output_theirs
	if [ $? -eq 0 ]; then
		echo "\033[0;32m""√ \t $1""\033[0;0m"
	else
		echo "\033[0;31m""✗ \t $1""\033[0;0m"
		echo $1 >> wrong_results.txt
	fi
}

function check_nm() {
	$bin_nm_mine $1 2>&- > $output_mine
	#if [ $? -eq 0 ] ; then
		$bin_nm $1 > $output_theirs
		print_result $1
	#fi
	rm -rf $output_mine $output_theirs
}

function check_otool() {
	$bin_otool_mine $1 2>&- > $output_mine
	if [ $? -eq 0 ]; then
		$bin_otool -t $1 > $output_theirs
		print_result $1
	fi
	rm -fr $output_mine $output_theirs
}

for dir in $dirs; do
	for file in $dir/* ; do
		check_nm $file
		#check_otool $file
	done
done
