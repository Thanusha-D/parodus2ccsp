/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#ifndef _WEBPA_RBUS_H_
#define _WEBPA_RBUS_H_

#include <stdio.h>
#include "webpa_adapter.h"
#include <wdmp-c.h>
#include <cimplog.h>
#include <rbus/rbus.h>

#define buffLen 1024
#define maxParamLen 128

#define NUM_WEBPA_ELEMENTS 9
#define COMPONENT_ID_NOTIFY_COMP "writeid_notify"
#define WiFi_FactoryResetRadioAndAp	    "Device.WiFi.X_CISCO_COM_FactoryResetRadioAndAp"

#define DEST_COMP_ID_PSM   "com.cisco.spvtg.ccsp.psm"

// Data elements provided by webpa

#define WEBPA_NOTIFY_PARAM "Device.Webpa.X_RDKCENTRAL-COM_WebPA_Notification"
#define WEBPA_CONNECTED_CLIENT_PARAM "Device.Webpa.X_RDKCENTRAL-COM_Connected-Client"
#define WEBPA_VERSION_PARAM "Device.X_RDKCENTRAL-COM_Webpa.Version"
#define WEBPA_SERVER_URL "Device.X_RDKCENTRAL-COM_Webpa.Server.URL"
#define WEBPA_TOKEN_SERVER_URL "Device.X_RDKCENTRAL-COM_Webpa.TokenServer.URL"
#define WEBPA_DNS_TEXT_URL "Device.X_RDKCENTRAL-COM_Webpa.DNSText.URL"
#define WEBPA_CMC_PARAM "Device.DeviceInfo.Webpa.X_COMCAST-COM_CMC"
#define WEBPA_CID_PARAM "Device.DeviceInfo.Webpa.X_COMCAST-COM_CID"
#define WEBPA_SYNCVERSION_PARAM "Device.DeviceInfo.Webpa.X_COMCAST-COM_SyncProtocolVersion"

#define CCSP_Msg_Bus_OK             100
#define CCSP_Msg_Bus_OOM            101
#define CCSP_Msg_Bus_ERROR          102

#define CCSP_Msg_BUS_CANNOT_CONNECT 190
#define CCSP_Msg_BUS_TIMEOUT        191
#define CCSP_Msg_BUS_NOT_EXIST      192
#define CCSP_Msg_BUS_NOT_SUPPORT    193

rbusError_t rbus_GetValueFromPSMDB( char* paramName, char** paramValue);
rbusError_t rbus_GetValueFromDB( char* paramName, char** paramValue);
rbusError_t rbus_StoreValueIntoDB(char *paramName, char *value);

void getValues_rbus(const char *paramName[], const unsigned int paramCount, int index, money_trace_spans *timeSpan, param_t ***paramArr, int *retValCount, int *retStatus);
DATA_TYPE mapRbusToWdmpDataType(rbusValueType_t rbusType);
int deleteRow_rbus(char *object);
#endif
