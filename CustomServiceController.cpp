#include<windows.h>
#include<iostream>
#include<tchar.h>
#include<atlstr.h>
#include "ServiceController.h";


//CString lpszBinaryPathName = "D:\\ProjectService\\x64\\Debug\\ProjectService.exe";
CString lpszBinaryPathName = "D:\\ProcessMonitorService\\Debug\\ProcessMonitorService.exe";

CString lpszDisplayName = "ProcessMontiorService";
CString lpszServiceName = "ProcessMontiorService";
DWORD CUSTOM_SERVICE_CONTROL_MESSAGE = 128;

void _tmain(int argc, TCHAR* argv[]) {

	ServiceController svc = ServiceController(lpszServiceName, TRUE, lpszBinaryPathName, lpszDisplayName);

	int ch;
	do {
		std::cout << "\n1. CREATE\n2. START\n3. CUSTOM MESSAGE\n4. STOP\n";
		std::cout << "Enter your choice : ";

		std::cin >> ch;

		switch(ch) {
			case 1:
				svc.createSvc(lpszBinaryPathName, lpszDisplayName, lpszServiceName);
				break;
			case 2:
				svc.startSvc();
				break;
			case 3:
				svc.sendCustomCtrlMsg(CUSTOM_SERVICE_CONTROL_MESSAGE);
				break;
			case 4:
				svc.stopSvc();
				break;
		}
	} while (ch != -1);
}