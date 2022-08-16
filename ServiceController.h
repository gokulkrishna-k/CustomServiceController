#include<Windows.h>
#include<atlstr.h>


class ServiceController {

	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	SERVICE_STATUS_PROCESS ssStatus;

	LPCTSTR lpszBinaryPathName;
	LPCTSTR lpszDisplayName;
	LPCTSTR lpszServiceName;

	DWORD dwBytesNeeded;

public:

	ServiceController(CString csServiceName,BOOL createSevice = FALSE, CString csBinaryPathName = _T(""), CString csDisplayName = _T("")) {

		lpszServiceName = (LPCTSTR)csServiceName;

		schSCManager = OpenSCManager(
			NULL,
			NULL,
			SC_MANAGER_ALL_ACCESS
		);

		schService = OpenService(
			schSCManager,
			lpszServiceName,
			SERVICE_ALL_ACCESS);
		
		if (!schService && GetLastError() == ERROR_SERVICE_DOES_NOT_EXIST && createSevice == TRUE) {
			createSvc(csBinaryPathName, csDisplayName, csServiceName);
		}
	}

	~ServiceController() {
		CloseServiceHandle(schSCManager);
		CloseServiceHandle(schService);
	}

	LONG createSvc(CString csBinaryPathName, CString csDisplayName, CString csServiceName);

	LONG startSvc();

	LONG stopSvc();

	LONG sendCustomCtrlMsg(DWORD ctrlMsg);

};

