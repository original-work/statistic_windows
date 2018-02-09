/*
* =====================================================================================
*
*       Filename:  writefileThread.cpp
*
*    Description:
*
*        Version:  1.0
*        Created:  2017/8/7 10:00:00
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  wangxx
*        contact:  winer632@qq.com
*
* =====================================================================================
* ============================== CHANGE REPORT HISTORY ================================
* |   VERSION   |   UPDATE DATE   |   UPDATED BY   |   DESCRIPTION OF CHANGE   |*

* =========================== END OF CHANGE REPORT HISTORY ============================
*/
#include "writefileThread.hpp"

using namespace std;

writefileThread::writefileThread()
{
}

writefileThread::~writefileThread()
{
}

int writefileThread::open(void *args)
{
	all_stopped_ = false;

	if (start() == -1)
	{
		return -1;
	}

	return 0;
}

int writefileThread::svc()
{
	for (;;)
	{
		if (test_cancel_thread() == 1)
		{
			all_stopped_ = true;
			break;
		}
		else
		{
			loop_process();
			Sleep(2);
		}
	}
	return 0;
}

		

void writefileThread::writefile(Point2d pos, double conArea)
{
	
	GetLocalTime(&time_);
	sprintf(filename_, "D:\\%u-%02u-%02u-%02u.stat", time_.wYear, time_.wMonth, time_.wDay,
		time_.wHour);
	printf("filename is %s   strlen(filename_) is %zu\n", filename_, strlen(filename_));
   	outfile_.open(filename_, ios::app);
	sprintf(time_s_, "%u/%02u/%02u %02u:%02u:%02u", time_.wYear, time_.wMonth, time_.wDay,
			time_.wHour, time_.wMinute, time_.wSecond);
	outfile_ << "time:" << time_s_ << "#x:" << pos.x << "#y:" << pos.y << "#area:" << conArea <<endl;
	outfile_.close();
}

void writefileThread::loop_process()
{
	while(1){
		Sleep(1000);
	}
}

int writefileThread::stop()
{
	cancel_thread();
	while (!all_stopped_) {
		Sleep(1);
	}
	return 0;
}

