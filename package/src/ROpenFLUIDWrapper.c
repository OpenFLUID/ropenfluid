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

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <R_ext/Rdynload.h>
#include <stdio.h>



// =====================================================================
// =====================================================================

static void Rized_OpenFLUID_DeleteBlob(SEXP Blob);

static void Rized_OpenFLUID_PrintSimulationInfo(SEXP Blob);
static SEXP Rized_OpenFLUID_GetSimulationOutputDir(SEXP Blob);
static SEXP Rized_OpenFLUID_GetVersion();

static void Rized_OpenFLUID_AddExtraFunctionsPaths(SEXP Paths);
static SEXP Rized_OpenFLUID_GetFunctionsPaths();

static SEXP Rized_OpenFLUID_NewDataBlob();
static SEXP Rized_OpenFLUID_OpenProject(SEXP Path);
static SEXP Rized_OpenFLUID_OpenDataset(SEXP Path);
static void Rized_OpenFLUID_SetCurrentOutputDir(SEXP Path);
static void Rized_OpenFLUID_RunSimulation(SEXP Blob);

static void Rized_OpenFLUID_SetFunctionParam(SEXP Blob, SEXP FunctionID, SEXP ParamName, SEXP ParamVal);
static SEXP Rized_OpenFLUID_GetFunctionParam(SEXP Blob, SEXP FunctionID, SEXP ParamName);
static void Rized_OpenFLUID_SetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName, SEXP ParamVal);
static SEXP Rized_OpenFLUID_GetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName);
static void Rized_OpenFLUID_SetModelGlobalParam(SEXP Blob, SEXP ParamName, SEXP ParamVal);
static SEXP Rized_OpenFLUID_GetModelGlobalParam(SEXP Blob, SEXP ParamName);

static SEXP Rized_OpenFLUID_CreateInputData(SEXP Blob,SEXP UnitClass, SEXP IDataName, SEXP IDataValue);
static SEXP Rized_OpenFLUID_SetInputData(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP IDataName, SEXP IDataValue);
static SEXP Rized_OpenFLUID_GetInputData(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP IDataName);

static SEXP Rized_OpenFLUID_SetDeltaT(SEXP Blob, SEXP DeltaT);
static SEXP Rized_OpenFLUID_GetDeltaT(SEXP Blob);
static SEXP Rized_OpenFLUID_SetPeriod(SEXP Blob, SEXP Begin, SEXP End);
static SEXP Rized_OpenFLUID_GetPeriodBeginDate(SEXP Blob);
static SEXP Rized_OpenFLUID_GetPeriodEndDate(SEXP Blob);



// =====================================================================
// =====================================================================


R_CallMethodDef callEntries[] = {
  { "DeleteBlob", (DL_FUNC) &Rized_OpenFLUID_DeleteBlob, 1},
  { "PrintSimulationInfo", (DL_FUNC) &Rized_OpenFLUID_PrintSimulationInfo, 1},
  { "GetSimulationOutputDir", (DL_FUNC) &Rized_OpenFLUID_GetSimulationOutputDir, 1},
  { "GetVersion", (DL_FUNC) &Rized_OpenFLUID_GetVersion, 0},
  { "AddExtraFunctionsPaths", (DL_FUNC) &Rized_OpenFLUID_AddExtraFunctionsPaths, 1},
  { "GetFunctionsPaths", (DL_FUNC) &Rized_OpenFLUID_GetFunctionsPaths, 0},
  { "NewDataBlob", (DL_FUNC) &Rized_OpenFLUID_NewDataBlob, 0},
  { "OpenDataset", (DL_FUNC) &Rized_OpenFLUID_OpenDataset, 1},
  { "SetCurrentOutputDir", (DL_FUNC) &Rized_OpenFLUID_SetCurrentOutputDir, 1},
  { "OpenProject", (DL_FUNC) &Rized_OpenFLUID_OpenProject, 1},
  { "RunSimulation", (DL_FUNC) &Rized_OpenFLUID_RunSimulation, 1},
  { "SetFunctionParam", (DL_FUNC) &Rized_OpenFLUID_SetFunctionParam, 4},
  { "GetFunctionParam", (DL_FUNC) &Rized_OpenFLUID_GetFunctionParam, 3},
  { "SetGeneratorParam", (DL_FUNC) &Rized_OpenFLUID_SetGeneratorParam, 5},
  { "GetGeneratorParam", (DL_FUNC) &Rized_OpenFLUID_GetGeneratorParam, 4},
  { "SetModelGlobalParam", (DL_FUNC) &Rized_OpenFLUID_SetModelGlobalParam, 3},
  { "GetModelGlobalParam", (DL_FUNC) &Rized_OpenFLUID_GetModelGlobalParam, 2},
  { "CreateInputData", (DL_FUNC) &Rized_OpenFLUID_CreateInputData, 4},
  { "SetInputData", (DL_FUNC) &Rized_OpenFLUID_SetInputData, 5},
  { "GetInputData", (DL_FUNC) &Rized_OpenFLUID_GetInputData, 4},
  { "SetDeltaT", (DL_FUNC) &Rized_OpenFLUID_SetDeltaT, 2},
  { "GetDeltaT", (DL_FUNC) &Rized_OpenFLUID_GetDeltaT, 1},
  { "SetPeriod", (DL_FUNC) &Rized_OpenFLUID_SetPeriod, 3},
  { "GetPeriodBeginDate", (DL_FUNC) &Rized_OpenFLUID_GetPeriodBeginDate, 1},
  { "GetPeriodEndDate", (DL_FUNC) &Rized_OpenFLUID_GetPeriodEndDate, 1},
  { NULL, NULL, 0}
};


#include "ROpenFLUID.h"

// =====================================================================
// =====================================================================



void R_init_ROpenFLUID(DllInfo* Info)
{
  R_registerRoutines(Info, NULL, callEntries, NULL, NULL);
  ROpenFLUID_Init();
}


void R_unload_ROpenFLUID(DllInfo* Info)
{

}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetVersion()
{
  SEXP Ret = R_NilValue;

  const char* Version = ROpenFLUID_GetVersion();

  if (Version != NULL)
  {
    PROTECT(Ret = allocVector(STRSXP, 1));
    SET_STRING_ELT(Ret, 0, mkChar(Version));
//    free(Version);
    UNPROTECT(1);
  }

  return Ret;
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_PrintSimulationInfo(SEXP Blob)
{
  ROpenFLUID_PrintSimulationInfo(R_ExternalPtrAddr(Blob));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetSimulationOutputDir(SEXP Blob)
{
  SEXP Ret;

  const char* Path = ROpenFLUID_GetSimulationOutputDir(R_ExternalPtrAddr(Blob));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Path));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_DeleteBlob(SEXP Blob)
{
  ROpenFLUID_DeleteBlob(R_ExternalPtrAddr(Blob));
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_AddExtraFunctionsPaths(SEXP Paths)
{
  ROpenFLUID_AddExtraFunctionsPaths(CHAR(STRING_ELT(Paths, 0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetFunctionsPaths()
{
  SEXP Ret;

  unsigned int PathsCount = ROpenFLUID_GetFunctionsPathsCount();

  PROTECT(Ret = allocVector(STRSXP, PathsCount));

  if (PathsCount > 0)
  {
    char** Paths = ROpenFLUID_GetFunctionsPaths();

    for (unsigned int i=0;i<PathsCount;i++)
    {
      SET_STRING_ELT(Ret, i, mkChar(Paths[i]));
    }

    for (unsigned int i=0;i<PathsCount;i++)
       free (Paths[i]);

    free(Paths);
  }

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_NewDataBlob()
{
  SEXP Ret = R_NilValue;

  ROpenFLUID_ExtBlob_t Ptr = (ROpenFLUID_ExtBlob_t*)ROpenFLUID_NewDataBlob();

  if (Ptr)
  {
    PROTECT(Ret = R_MakeExternalPtr(Ptr, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(Ret, (R_CFinalizer_t) Rized_OpenFLUID_DeleteBlob);
    UNPROTECT(1);
  }
  else
  {
    Rf_error(ROpenFLUID_GetLastError());
  }

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_OpenProject(SEXP Path)
{
  SEXP Ret = R_NilValue;

  ROpenFLUID_ExtBlob_t Ptr = (ROpenFLUID_ExtBlob_t*)ROpenFLUID_OpenProject(CHAR(STRING_ELT(Path, 0)));

  if (Ptr)
  {
    PROTECT(Ret = R_MakeExternalPtr(Ptr, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(Ret, (R_CFinalizer_t) Rized_OpenFLUID_DeleteBlob);
    UNPROTECT(1);
  }
  else
  {
    Rf_error(ROpenFLUID_GetLastError());
  }

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_OpenDataset(SEXP Path)
{
  SEXP Ret = R_NilValue;

  ROpenFLUID_ExtBlob_t Ptr = (ROpenFLUID_ExtBlob_t*)ROpenFLUID_OpenDataset(CHAR(STRING_ELT(Path, 0)));

  if (Ptr)
  {
    PROTECT(Ret = R_MakeExternalPtr(Ptr, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(Ret, (R_CFinalizer_t) Rized_OpenFLUID_DeleteBlob);
    UNPROTECT(1);
  }
  else
  {
    Rf_error(ROpenFLUID_GetLastError());
  }

  return Ret;
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_SetCurrentOutputDir(SEXP Path)
{
  ROpenFLUID_SetCurrentOutputDir(CHAR(STRING_ELT(Path, 0)));
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_RunSimulation(SEXP Blob)
{
  if (ROpenFLUID_RunSimulation(R_ExternalPtrAddr(Blob)) != 1)
  {
    Rf_error(ROpenFLUID_GetLastError());
  }
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_SetFunctionParam(SEXP Blob, SEXP FunctionID, SEXP ParamName, SEXP ParamVal)
{
  ROpenFLUID_SetFunctionParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(FunctionID, 0)),CHAR(STRING_ELT(ParamName, 0)),CHAR(STRING_ELT(ParamVal, 0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetFunctionParam(SEXP Blob, SEXP FunctionID, SEXP ParamName)
{
  SEXP Ret;

  const char* Val = ROpenFLUID_GetFunctionParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(FunctionID, 0)),CHAR(STRING_ELT(ParamName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_SetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName, SEXP ParamVal)

{
  ROpenFLUID_SetGeneratorParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)),CHAR(STRING_ELT(VarName, 0)),CHAR(STRING_ELT(ParamName, 0)),CHAR(STRING_ELT(ParamVal, 0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName)

{
  SEXP Ret;

  const char* Val = ROpenFLUID_GetGeneratorParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)),CHAR(STRING_ELT(VarName, 0)),CHAR(STRING_ELT(ParamName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_SetModelGlobalParam(SEXP Blob, SEXP ParamName, SEXP ParamVal)
{
  ROpenFLUID_SetModelGlobalParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(ParamName, 0)),CHAR(STRING_ELT(ParamVal, 0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetModelGlobalParam(SEXP Blob, SEXP ParamName)
{
  SEXP Ret;

  const char* Val = ROpenFLUID_GetModelGlobalParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(ParamName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_CreateInputData(SEXP Blob,SEXP UnitClass, SEXP IDataName, SEXP IDataValue)
{

  Rf_error("under construction");

}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_SetInputData(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP IDataName, SEXP IDataValue)
{

  Rf_error("under construction");

}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetInputData(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP IDataName)
{
  SEXP Ret = R_NilValue;

  Rf_error("under construction");

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_SetDeltaT(SEXP Blob, SEXP DeltaT)
{
  ROpenFLUID_SetDeltaT(R_ExternalPtrAddr(Blob),INTEGER(DeltaT)[0]);
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetDeltaT(SEXP Blob)
{
  SEXP Ret;

  int DeltaT = ROpenFLUID_GetDeltaT(R_ExternalPtrAddr(Blob));

  PROTECT(Ret = allocVector(INTSXP, 1));
  INTEGER(Ret)[0] = DeltaT;
  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_SetPeriod(SEXP Blob, SEXP Begin, SEXP End)
{
  ROpenFLUID_SetPeriod(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(Begin,0)),CHAR(STRING_ELT(End,0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetPeriodBeginDate(SEXP Blob)
{
  SEXP Ret;

  const char* DateStr = ROpenFLUID_GetPeriodBeginDate(R_ExternalPtrAddr(Blob));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(DateStr));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetPeriodEndDate(SEXP Blob)
{
  SEXP Ret;

  const char* DateStr = ROpenFLUID_GetPeriodEndDate(R_ExternalPtrAddr(Blob));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(DateStr));

  UNPROTECT(1);

  return Ret;
}
