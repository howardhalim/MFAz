



#include "bloom.h"





int bf_check(struct bloom* bloom, char* buffer, int buflen)
{

	int check_result;
	check_result = bloom_check(bloom, buffer, buflen);
	//  printf("%d\n", check_result);
	  /*0 - element is not present
	   * 1 - element is present(or false positive due to collision)
	   * -1 - bloom not initialized*/
	return check_result;
}

int bf_add(struct bloom* bloom, char* buffer, int buflen)
{
	int add_result;
	add_result = bloom_add(bloom, buffer, buflen);
	/*0 - element was not present and was added
		* 1 - element(or a collision) had already been added previously
		* -1 - bloom not initialized*/
	return add_result;
}

