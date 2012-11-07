# Virtual Memory Manager “virtualmem” in C/C++ on a UNIX-based platform.



### SYNOPSIS:
To run this program:
*virtualmem [−h] [-f available-frames] [−r replacement-policy] [−i input_file]*


### DESCRIPTION:
_virtualmem_ is a simple virtual memory manager. It takes a sequence of page
references as an input, as well as the number of available frames. It performs the placement of
these pages to the available frames using the page replacement policy specified by the user.


### OPTIONS:
*−h : Print a usage summary with all options and exit.
*−f available-frames : Set the number of available frames. By default it should be 5.
*−r replacement-policy : Set the page replacement policy. It can be either:
	*FIFO (First-in-first-out)
	*LFU (Least-frequently-used)
	*LRU-STACK (Least-recently-used stack implementation)
	*LRU-CLOCK (Least-recently-used clock implementation –second chance algo)
	*LRU-REF8 (Least-recently-used Reference-bitImplementation, using 8 reference bits)
_The default will be FIFO._
*−i input file : Read the page reference sequence from a specified file. If not given,the sequence should be read from STDIN (ended with ENTER).


### OUTPUT:
>Also implemented the Optimal page replacement algorithm, and compared the performance of the replacement-policy chosen by the user (above) to the Optimal algorithm, in terms of number of page replacements for the given string. i.e:

	$ virtualmem –f 10 –r LFU –i myinputfile
	# of page replacements with LFU : 118
	# of page replacements with Optimal : 85
	% page replacement penalty using LFU : 38.8%
	
	Total time to run LFU algorithm : 1214 msec
	Total time to run Optimal algorithm : 1348 msec
	LFU is 9.9% faster than Optimal algorithm.
