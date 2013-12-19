/*

  This file is part of OpenFLUID software
  Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

  OpenFLUID is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.

*/



#ifndef __ROPENFLUID_H__
#define __ROPENFLUID_H__

#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef void* ROpenFLUID_ExtBlob_t;

void ROpenFLUID_Init();

void ROpenFLUID_DeleteBlob(ROpenFLUID_ExtBlob_t* BlobHandle);

const char* ROpenFLUID_GetVersion();

const char* ROpenFLUID_GetLastError();

void ROpenFLUID_AddExtraSimulatorsPaths(const char* Paths);

char** ROpenFLUID_GetSimulatorsPaths();

unsigned int ROpenFLUID_GetSimulatorsPathsCount();

ROpenFLUID_ExtBlob_t ROpenFLUID_NewDataBlob();

ROpenFLUID_ExtBlob_t ROpenFLUID_OpenDataset(const char* Path);

void ROpenFLUID_SetCurrentOutputDir(const char* Path);

const char* ROpenFLUID_GetSimulationOutputDir(ROpenFLUID_ExtBlob_t* BlobHandle);

ROpenFLUID_ExtBlob_t ROpenFLUID_OpenProject(const char* Path);

unsigned short int ROpenFLUID_RunSimulation(ROpenFLUID_ExtBlob_t* BlobHandle);

void ROpenFLUID_PrintSimulationInfo(ROpenFLUID_ExtBlob_t* BlobHandle);

int ROpenFLUID_GetDeltaT(ROpenFLUID_ExtBlob_t* BlobHandle);

void ROpenFLUID_SetDeltaT(ROpenFLUID_ExtBlob_t* BlobHandle, int DeltaT);

const char* ROpenFLUID_GetPeriodBeginDate(ROpenFLUID_ExtBlob_t* BlobHandle);

const char* ROpenFLUID_GetPeriodEndDate(ROpenFLUID_ExtBlob_t* BlobHandle);

void ROpenFLUID_SetPeriod(ROpenFLUID_ExtBlob_t* BlobHandle, const char* BeginDate, const char* EndDate);

const char* ROpenFLUID_GetSimulatorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* SimID, const char* ParamName);

void ROpenFLUID_SetSimulatorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* SimID, const char* ParamName, const char* ParamVal);

void ROpenFLUID_SetGeneratorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, const char* VarName, const char* ParamName, const char* ParamVal);

const char*  ROpenFLUID_GetGeneratorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, const char* VarName, const char* ParamName);

void ROpenFLUID_SetModelGlobalParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ParamName, const char* ParamVal);

const char*  ROpenFLUID_GetModelGlobalParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ParamName);

char** ROpenFLUID_GetUnitsClasses(ROpenFLUID_ExtBlob_t* BlobHandle);

unsigned int ROpenFLUID_GetUnitsClassesCount(ROpenFLUID_ExtBlob_t* BlobHandle);

int* ROpenFLUID_GetUnitsIDs(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass);

unsigned int ROpenFLUID_GetUnitsIDsCount(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass);

void ROpenFLUID_CreateAttribute(ROpenFLUID_ExtBlob_t* BlobHandle,const char* UnitClass, const char* AttrName, const char* AttrValue);

void ROpenFLUID_SetAttribute(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, int UnitID, const char* AttrName, const char* AttrValue);

const char* ROpenFLUID_GetAttribute(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, int UnitID, const char* AttrName);

void ROpenFLUID_AddVariablesExportAsCSV(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass);


#ifdef __cplusplus
}
#endif

#endif // __ROPENFLUID_H__
