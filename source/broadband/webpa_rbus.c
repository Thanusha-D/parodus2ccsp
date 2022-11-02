#include <stdbool.h>
#include <string.h>

#include <stdlib.h>
#include <wdmp-c.h>
#include <cimplog.h>
#include "webpa_rbus.h"

static rbusHandle_t rbus_handle;
static bool isRbus = false;

bool isRbusEnabled()
{
	if(RBUS_ENABLED == rbus_checkStatus())
	{
		isRbus = true;
	}
	else
	{
		isRbus = false;
	}
	WalInfo("Webpa RBUS mode active status = %s\n", isRbus ? "true":"false");
	return isRbus;
}

bool isRbusInitialized()
{
    return rbus_handle != NULL ? true : false;
}

WDMP_STATUS webpaRbusInit(const char *pComponentName)
{
	int ret = RBUS_ERROR_SUCCESS;

	WalInfo("rbus_open for component %s\n", pComponentName);
	ret = rbus_open(&rbus_handle, pComponentName);
	if(ret != RBUS_ERROR_SUCCESS)
	{
		WalError("webpaRbusInit failed with error code %d\n", ret);
		return WDMP_FAILURE;
	}
	WalInfo("webpaRbusInit is success. ret is %d\n", ret);
	return WDMP_SUCCESS;
}

static void webpaRbus_Uninit()
{
    rbus_close(rbus_handle);
}

rbusError_t setTraceContext(char* traceParent, char* traceState)
{
	WalInfo("Called setTraceContext function\n");
	return rbusHandle_SetTraceContextFromString(rbus_handle, traceParent, traceState);

}	
