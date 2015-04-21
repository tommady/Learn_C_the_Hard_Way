echo "Running unit tests:"
lib = ../build/libex29.so

for i in tests/*_tests
do
	if test -f $i
	then
		if $VALGRIND ./$i $lib print_a_message "hello there" 2>> tests/tests.log
		then
			echo $i PASS
		else
			echo "ERROR in test $i: here's tests/tests.log"
			echo "------"
			tail tests/tests.log
			exit 1
		fi
	fi
done

echo ""
