/*
 * main implementation: use this 'C++' sample to create your own application
 *
 */



#include "derivative.h" /* include peripheral declarations */


class counterclass
{
private:
  	int m_counter;
public:  
	counterclass(void) 
	{
		m_counter = 0;
	};
	void increment(void) 
	{
		m_counter++;
	};  	
};

int main()
{
	counterclass myccounter;
	
	
	
	for(;;) {	
			myccounter.increment();
		}
	
	return 0;
}
