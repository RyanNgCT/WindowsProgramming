// ###################################################################################################
// Video Tutorial and Codes Taken From Varteta Learning Platform on Youtube.
// Playlist Link: https://www.youtube.com/watch?v=yj8fMxWx_4c&list=PLhnN2F9NiVmAmMdwXEkpmSpBIogC8MqT6
// Notes by Ryan Ng, 2021 (Apache 2.0 License)
// ###################################################################################################

#include<Windows.h>
#include<iostream>
using namespace std;

// GetMessage is a blocking call (will wait)
// PostThreadMessage is NOT a blocking call

HANDLE thReceiver; HANDLE thSender;
DWORD receiverId; DWORD senderId;

#define MESSAGE_ENTER   0
#define MESSAGE_1		1
#define MESSAGE_2		2
#define MESSAGE_3		3
#define MESSAGE_4		4
#define MESSAGE_EXIT	5

const char* messages[6] = {
	"Welcome!",
	"First Msg",
	"Second Msg",
	"Third Msg",
	"Fourth Msg",
	"Last Msg, Goodbye!"
};

void Sender() {
	for (int i = 0; i < 6; i++)
	{
		Sleep(1000);

		// async call (will not care if it is processed)
		PostThreadMessage(receiverId, i, NULL, NULL);

		// receiver does not process first message (index 1)
	}

}

void Receiver() {

	MSG msg; 

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		cout << endl << messages[msg.message];
		
		if (msg.message == MESSAGE_EXIT) {
			break;
		}
	}
}

int main() {

	
	// inherit attributes from user, stack (default), start routine, params, creation flag (can schedule i.e. CREATE_SUSPENDED)
	
	// Receiver created first to receieve incoming msgs
	thReceiver = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Receiver, NULL, 0, &receiverId);
	
	Sleep(1000);

	thSender = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Sender, NULL, 0, &senderId);

	// remove inconsistency
	HANDLE th[2] = {thSender,thReceiver};
	//if FALSE, will not wait for threads
	WaitForMultipleObjects(2, th, TRUE, INFINITE);

	return 0;
}
