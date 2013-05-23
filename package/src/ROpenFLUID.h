/*
  This file is part of OpenFLUID software
  Copyright (c) 2007-2010 INRA-Montpellier SupAgro


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
  along with OpenFLUID.  If not, see <http://www.gnu.org/licenses/>.

  In addition, as a special exception, INRA gives You the additional right
  to dynamically link the code of OpenFLUID with code not covered
  under the GNU General Public License ("Non-GPL Code") and to distribute
  linked combinations including the two, subject to the limitations in this
  paragraph. Non-GPL Code permitted under this exception must only link to
  the code of OpenFLUID dynamically through the OpenFLUID libraries
  interfaces, and only for building OpenFLUID plugins. The files of
  Non-GPL Code may be link to the OpenFLUID libraries without causing the
  resulting work to be covered by the GNU General Public License. You must
  obey the GNU General Public License in all respects for all of the
  OpenFLUID code and other code used in conjunction with OpenFLUID
  except the Non-GPL Code covered by this exception. If you modify
  this OpenFLUID, you may extend this exception to your version of the file,
  but you are not obligated to do so. If you do not wish to provide this
  exception without modification, you must delete this exception statement
  from your version and license this OpenFLUID solely under the GPL without
  exception.


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

void ROpenFLUID_CreateInputData(ROpenFLUID_ExtBlob_t* BlobHandle,const char* UnitClass, const char* IDataName, const char* IDataValue);

void ROpenFLUID_SetInputData(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, int UnitID, const char* IDataName, const char* IDataValue);

const char* ROpenFLUID_GetInputData(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, int UnitID, const char* IDataName);

void ROpenFLUID_AddVariablesExportAsCSV(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass);


#ifdef __cplusplus
}
#endif

#endif // __ROPENFLUID_H__
