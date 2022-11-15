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
	rbusError_t ret = RBUS_ERROR_SUCCESS;
	WalInfo("Called setTraceContext function with value traceParent - %s, traceState - %s\n", traceParent, traceState);
	ret = rbusHandle_SetTraceContextFromString(rbus_handle, traceParent, traceState);
        return ret;
}

rbusError_t getTraceContext(char* traceContext[])
{
        rbusError_t ret = RBUS_ERROR_SUCCESS;
        char traceParent[512] = {'\0'};
        char traceState[512] = {'\0'};
        ret =  rbusHandle_GetTraceContextAsString(rbus_handle, traceParent, sizeof(traceParent), traceState, sizeof(traceState));
	WalInfo("After getTraceContext function value traceParent - %s, traceState - %s\n", traceParent, traceState);
	if(strlen(traceParent) > 0 && strlen(traceState) > 0) {
		traceContext[0] = strdup(traceParent);
		traceContext[1] = strdup(traceState);
        }
	WalInfo("After strdup to traceContext value traceParent - %s, traceState - %s\n", traceContext[0], traceContext[1]);
        return ret;
}

