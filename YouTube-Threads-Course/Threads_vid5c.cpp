// ###################################################################################################
// Video Tutorial and Codes Taken From Varteta Learning Platform on Youtube.
// Playlist Link: https://www.youtube.com/watch?v=yj8fMxWx_4c&list=PLhnN2F9NiVmAmMdwXEkpmSpBIogC8MqT6
// Notes by Ryan Ng, 2021 (Apache 2.0 License)
// ###################################################################################################

#include<Windows.h>
#include<iostream>
using namespace std;

//initialize array for V2, handles and ids
int nArr[10] = { 0, };
HANDLE thReader; HANDLE thWriter;
DWORD readerId; DWORD writerId;

// not recommended
CRITICAL_SECTION cs;

void Reader() {

	EnterCriticalSection(&cs);

	// read from array
	for (int i = 0; i < 10; i++)
	{
		cout << endl << nArr[i];
		Sleep(1000); // sleep for 1 sec
	}

	LeaveCriticalSection(&cs);

}


void Writer() {

	// have to deal with recursion count 
	// Failing to release lock 'cs' in function 'Writer'.VLP_Windows_Prg_Project1	

	EnterCriticalSection(&cs);
	//EnterCriticalSection(&cs);
	//EnterCriticalSection(&cs);

	// write to this arrays
	for (int i = 0; i < 10; i++)
	{
		nArr[i] = (i + 1) * 2;
		cout << endl << "Writing...";
		Sleep(1000); // sleep for 1 sec
	}
	cout << endl << "Done Writing!";
	ResumeThread(thReader);

	LeaveCriticalSection(&cs);
}

int main() {

	InitializeCriticalSection(&cs);


	/*Video 1: Threads Introduction*/

	// changes in every instance
	cout << endl << "The thread identifier (id) of the main thread is: " << GetCurrentThreadId();

	// zero if only one thread
	cout << endl << "The priority of the main thread (int) is: " << GetThreadPriority(GetCurrentThread());
	cout << "\n";

	//=============================================================================================================


	/*Videos 2 and 3: 2 or more threads*/

	// Scenario: reader and writer threads

	// Background
	// -----------
	// - process handle table is created for each running process
	// - handle: INDEX of kernel obj used by process/program in execution (since cannot refer directly to kernel memory)
	// - must close handles (memory leak)

	// main thread is the parent of all threads -> if main is done, rest of the threads are meaningless

	// inherit attributes from user, stack (default), start routine, params, creation flag (can schedule i.e. CREATE_SUSPENDED)
	thWriter = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Writer, NULL, 0, &writerId);
	cout << endl << "The WRITER thread id is:" << writerId;

	Sleep(500);

	thReader = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Reader, NULL, 0, &readerId);
	cout << endl << "The READER thread id is:" << readerId;

	// remove inconsistency
	HANDLE th[2] = { thWriter,thReader };
	//if FALSE, will not wait for threads
	WaitForMultipleObjects(2, th, TRUE, INFINITE);


	/*Video 4: Reader-Writer Synchronization Using Critical Section*/
	// "reserve" critical section from other threads (1 thread for 1 operation)
	// Alternative for CREATE_SUSPENDED -> Add in CriticalSection
	// CRITICAL_SECTION is a user-mode sync object and can only sync threads running under SAME process.

	DeleteCriticalSection(&cs);

	/*Video 5: Critical Section Important Concepts*/
	// avoid using TryEnterCriticalSection()
	// Recursion Count: how many times a thread has acquired a critical section obj (need to release it -> call LeaveCriticalSection() however many times
	// Spin Count -> applies to TryEnterCriticalSection(): how many times TryEnterCriticalSection API will probe if cs object is available 
	// Spin Count can be set tgt with Entering the CriticalSection with EnterCriticalSectionAndSpinCount() API
	return 0;
}
