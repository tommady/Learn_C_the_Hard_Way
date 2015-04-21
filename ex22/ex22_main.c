#include "ex22.h"
#include "dbg.h"

/*
char * 宣告一個char型別的指標指向一個普通的字元或陣列(也就是字串),指向的位址可以換,字元字串內容也可以改
const char * 宣告一個const char型別的指標指向一個常數char字元或常數字串(也就是字元或字串內容不能動但指標指的位址可以改)
char const * 同const char *
char * const 剛好跟const char *相反,指的位址不能動,但是位址裡的字元或字串不是const可以改
const char * const 不論是指的位址或是位址裡的字元或字串都是const不能更動

http://stackoverflow.com/questions/583076/c-c-changing-the-value-of-a-const
http://stackoverflow.com/questions/13185751/what-is-the-difference-between-static-const-and-const
*/

const char* MY_NAME = "Lindroos Hsu";

void scope_demo(int count)
{
	log_info("count is: %d", count);
	
	if(count > 10)
	{
		int count = 100; //BAD! BUGS!
		
		log_info("count in this scope is %d", count);
	}
	
	log_info("count is at exit: %d", count);
	
	count = 3000;
	
	log_info("count after assign: %d", count);
}

int main(int argc, char *argv[])
{
	//test out THE_AGE accessors
	log_info("My name: %s, age: %d", MY_NAME, get_age());
	
	set_age(100);
	
	log_info("My age is now: %d", get_age());
	
	//test out THE_SIZE extern
	log_info("THE_SIZE is: %d", THE_SIZE);
	print_size();
	
	THE_SIZE = 9;
	
	log_info("THE SIZE is now: %d", THE_SIZE);
	print_size();
	
	//test the ratio function static
	log_info("Ratio at first: %lf", update_ratio(2.0));
	log_info("Ratio again: %lf", update_ratio(10.0));
	log_info("Ratio once more: %lf", update_ratio(300.0));
	
	//test the scope demo
	int count = 4;
	scope_demo(count);
	scope_demo(count * 20);
	
	log_info("count after calling scope_demo: %d", count);
	
	return 0;
}
