#include "ps4.h"
#include "patch.h"
#include "ApplicationCache.h"

void writeCacheDB()
{
    size_t len = 0;
    unsigned char* fbuf = base64_decode(ApcStr, sizeof(ApcStr), &len);
	if (len != 0)
	{
    int fid = open("/user/system/webkit/webbrowser/appcache/ApplicationCache.db", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    write(fid, fbuf, len);
    close(fid);
	free(fbuf);
	sceKernelSleep(3);
	systemMessage("PS-Phive! install Complete\n\nBookmark:\nhttp://ps-phive/index.html");
	sceKernelSleep(1);
	openBrowser("http://ps-phive/index.html");
	}
	else
	{
		systemMessage("ERROR:\nNo internal cache found");
	}
}

int _main(struct thread *td) {
	initKernel();
	initLibc();
	syscall(11,patcher,td);
	initSysUtil();
	if (!dir_exists("/user/system/webkit/webbrowser/appcache"))
	{
	    mkdir ("/user/system/webkit/webbrowser/appcache", 0777);
	}
	writeCacheDB();
	return 0;
}
