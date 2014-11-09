/*******************************************************************************
 * Copyright (c) 2012 protos software gmbh (http://www.protos.de).
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * CONTRIBUTORS:
 * 		Thomas Schuetz (initial contribution)
 *
 *******************************************************************************/

#include "debugging/etMSCLogger.h"
#include "debugging/etLogger.h"

#include "osal/etThread.h"

#ifdef ET_MSC_LOGGER_ACTIVATE
static etFileHandle etMSCLogger_fileHandle = NULL;
static const char* etMSCLogger_objectName = "";
#endif

/*TODO: move or replace ET_MAX_FILENAME_LEN */
#define ET_MAX_FILENAME_LEN 256

void etMSCLogger_open(const char* logPath, const char* mscName){
#ifdef ET_MSC_LOGGER_ACTIVATE
	char path[ET_MAX_FILENAME_LEN];
	sprintf(path, "%s/%s.seq", logPath, mscName);
	etMSCLogger_fileHandle = etLogger_fopen(path, "w+");
#endif
}

void etMSCLogger_close(void){
#ifdef ET_MSC_LOGGER_ACTIVATE
	if (etMSCLogger_fileHandle != NULL){
		etLogger_fclose(etMSCLogger_fileHandle);
	}
#endif
}

void etMSCLogger_setObjectName(const char* objectName){
#ifdef ET_MSC_LOGGER_ACTIVATE
	etMSCLogger_objectName = objectName;
#endif
}

const char* etMSCLogger_getObjectName(void){
#ifdef ET_MSC_LOGGER_ACTIVATE
	return etMSCLogger_objectName;
#endif
}

void etMSCLogger_syncCall(const char* sourceName, const char* messageName, const char* targetName){
#ifdef ET_MSC_LOGGER_ACTIVATE
	if (etMSCLogger_fileHandle != NULL) {
		etLogger_fprintf(etMSCLogger_fileHandle, "%s ==> %s %s(thread=%ld)\n", sourceName, targetName, messageName, etThread_self_id());
	}
#endif
}

void etMSCLogger_syncReturn(const char* sourceName, const char* targetName){
#ifdef ET_MSC_LOGGER_ACTIVATE
	if (etMSCLogger_fileHandle != NULL) {
		etLogger_fprintf(etMSCLogger_fileHandle, "%s <== %s\n", sourceName, targetName);
	}
#endif
}

void etMSCLogger_asyncOut(const char* sourceName, const char* messageName, const char* targetName){
#ifdef ET_MSC_LOGGER_ACTIVATE
	if (etMSCLogger_fileHandle != NULL) {
		etLogger_fprintf(etMSCLogger_fileHandle, "%s >-- %s %s\n", sourceName, targetName, messageName);
	}
#endif
}

void etMSCLogger_asyncIn(const char* sourceName, const char* messageName, const char* targetName){
#ifdef ET_MSC_LOGGER_ACTIVATE
	if (etMSCLogger_fileHandle != NULL) {
		etLogger_fprintf(etMSCLogger_fileHandle, "%s --> %s %s\n", sourceName, targetName, messageName);
	}
#endif
}

void etMSCLogger_setState(const char* objectName, const char* stateName){
#ifdef ET_MSC_LOGGER_ACTIVATE
	if (etMSCLogger_fileHandle != NULL) {
		etLogger_fprintf(etMSCLogger_fileHandle, "%s >>> %s\n", objectName, stateName);
	}
#endif
}
