#include "ServiceController.h"


LONG ServiceController::createSvc(CString csBinaryPathName, CString csDisplayName, CString csServiceName) {

	lpszBinaryPathName = (LPCTSTR)csBinaryPathName;
	lpszDisplayName = (LPCTSTR)csDisplayName;
	lpszServiceName = (LPCTSTR)csServiceName;

	schService = CreateService(
		schSCManager,
		lpszServiceName,
		lpszDisplayName,
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		lpszBinaryPathName,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	);
	if (schService == NULL) {
		return GetLastError();
	}
}

LONG ServiceController::startSvc() {


	if (!StartService(schService, 0, NULL)) {
		return GetLastError();
	}

	if (!QueryServiceStatusEx(
		schService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&ssStatus,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded))
	{
		return GetLastError();
	}

	if (ssStatus.dwCurrentState == SERVICE_RUNNING)
	{
		return SERVICE_RUNNING;
	}
	else
	{
		return GetLastError();
	}
}

LONG ServiceController::stopSvc() {

	if (!ControlService(
		schService,
		SERVICE_CONTROL_STOP,
		(LPSERVICE_STATUS)&ssStatus))
	{
		return GetLastError();
	}

	while (ssStatus.dwCurrentState == SERVICE_STOP_PENDING) {
		if (QueryServiceStatusEx(
			schService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssStatus,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded)) {

			if (ssStatus.dwCurrentState == SERVICE_STOPPED) {
				return SERVICE_STOPPED;
			}
			Sleep(1000);
		}
	}

	return GetLastError();

}

LONG ServiceController::sendCustomCtrlMsg(DWORD ctrlMsg) {

	DWORD dwBytesNeeded;

	if (!ControlService(
		schService,
		ctrlMsg,
		(LPSERVICE_STATUS)&ssStatus))
	{
		return GetLastError();
	}
	else {
		return 0;
	}
}