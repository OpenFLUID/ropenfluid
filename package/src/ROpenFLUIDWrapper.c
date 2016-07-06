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

static void Rized_OpenFLUID_AddExtraSimulatorsPaths(SEXP Paths);
static void Rized_OpenFLUID_ResetExtraSimulatorsPaths();
static SEXP Rized_OpenFLUID_GetSimulatorsPaths();
static SEXP Rized_OpenFLUID_GetExtraSimulatorsPaths();
static void Rized_OpenFLUID_AddExtraObserversPaths(SEXP Paths);
static void Rized_OpenFLUID_ResetExtraObserversPaths();
static SEXP Rized_OpenFLUID_GetObserversPaths();
static SEXP Rized_OpenFLUID_GetExtraObserversPaths();

static SEXP Rized_OpenFLUID_NewDataBlob();
static SEXP Rized_OpenFLUID_OpenProject(SEXP Path);
static SEXP Rized_OpenFLUID_OpenDataset(SEXP Path);
static void Rized_OpenFLUID_SetCurrentOutputDir(SEXP Path);
static void Rized_OpenFLUID_RunSimulation(SEXP Blob, SEXP Verbose);

static void Rized_OpenFLUID_SetSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName, SEXP ParamVal);
static SEXP Rized_OpenFLUID_GetSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName);
static void Rized_OpenFLUID_RemoveSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName);
static void Rized_OpenFLUID_SetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName, SEXP ParamVal);
static SEXP Rized_OpenFLUID_GetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName);
static void Rized_OpenFLUID_SetModelGlobalParam(SEXP Blob, SEXP ParamName, SEXP ParamVal);
static SEXP Rized_OpenFLUID_GetModelGlobalParam(SEXP Blob, SEXP ParamName);
static void Rized_OpenFLUID_RemoveModelGlobalParam(SEXP Blob, SEXP ParamName);
static void Rized_OpenFLUID_SetObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName, SEXP ParamVal);
static SEXP Rized_OpenFLUID_GetObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName);
static void Rized_OpenFLUID_RemoveObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName);

static SEXP Rized_OpenFLUID_GetUnitsClasses(SEXP Blob);
static SEXP Rized_OpenFLUID_GetUnitsIDs(SEXP Blob, SEXP UnitClass);

static void Rized_OpenFLUID_CreateAttribute(SEXP Blob,SEXP UnitClass, SEXP AttrName, SEXP AttrValue);
static void Rized_OpenFLUID_SetAttribute(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP AttrName, SEXP AttrValue);
static SEXP Rized_OpenFLUID_GetAttribute(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP AttrName);
static void Rized_OpenFLUID_RemoveAttribute(SEXP Blob, SEXP UnitClass, SEXP AttrName);

static SEXP Rized_OpenFLUID_SetDefaultDeltaT(SEXP Blob, SEXP DeltaT);
static SEXP Rized_OpenFLUID_GetDefaultDeltaT(SEXP Blob);
static SEXP Rized_OpenFLUID_SetPeriod(SEXP Blob, SEXP Begin, SEXP End);
static SEXP Rized_OpenFLUID_GetPeriodBeginDate(SEXP Blob);
static SEXP Rized_OpenFLUID_GetPeriodEndDate(SEXP Blob);

static SEXP Rized_OpenFLUID_AddVariablesExportAsCSV(SEXP Blob, SEXP UnitClass);



// =====================================================================
// =====================================================================


R_CallMethodDef callEntries[] = {
  { "DeleteBlob", (DL_FUNC) &Rized_OpenFLUID_DeleteBlob, 1},
  { "PrintSimulationInfo", (DL_FUNC) &Rized_OpenFLUID_PrintSimulationInfo, 1},
  { "GetSimulationOutputDir", (DL_FUNC) &Rized_OpenFLUID_GetSimulationOutputDir, 1},
  { "GetVersion", (DL_FUNC) &Rized_OpenFLUID_GetVersion, 0},
  { "AddExtraSimulatorsPaths", (DL_FUNC) &Rized_OpenFLUID_AddExtraSimulatorsPaths, 1},
  { "ResetExtraSimulatorsPaths", (DL_FUNC) &Rized_OpenFLUID_ResetExtraSimulatorsPaths, 0},
  { "GetSimulatorsPaths", (DL_FUNC) &Rized_OpenFLUID_GetSimulatorsPaths, 0},
  { "GetExtraSimulatorsPaths", (DL_FUNC) &Rized_OpenFLUID_GetExtraSimulatorsPaths, 0},
  { "AddExtraObserversPaths", (DL_FUNC) &Rized_OpenFLUID_AddExtraObserversPaths, 1},
  { "ResetExtraObserversPaths", (DL_FUNC) &Rized_OpenFLUID_ResetExtraObserversPaths, 0},
  { "GetObserversPaths", (DL_FUNC) &Rized_OpenFLUID_GetObserversPaths, 0},
  { "GetExtraObserversPaths", (DL_FUNC) &Rized_OpenFLUID_GetExtraObserversPaths, 0},
  { "NewDataBlob", (DL_FUNC) &Rized_OpenFLUID_NewDataBlob, 0},
  { "OpenDataset", (DL_FUNC) &Rized_OpenFLUID_OpenDataset, 1},
  { "SetCurrentOutputDir", (DL_FUNC) &Rized_OpenFLUID_SetCurrentOutputDir, 1},
  { "OpenProject", (DL_FUNC) &Rized_OpenFLUID_OpenProject, 1},
  { "RunSimulation", (DL_FUNC) &Rized_OpenFLUID_RunSimulation, 2},
  { "SetSimulatorParam", (DL_FUNC) &Rized_OpenFLUID_SetSimulatorParam, 4},
  { "GetSimulatorParam", (DL_FUNC) &Rized_OpenFLUID_GetSimulatorParam, 3},
  { "RemoveSimulatorParam", (DL_FUNC) &Rized_OpenFLUID_RemoveSimulatorParam, 3},
  { "SetGeneratorParam", (DL_FUNC) &Rized_OpenFLUID_SetGeneratorParam, 5},
  { "GetGeneratorParam", (DL_FUNC) &Rized_OpenFLUID_GetGeneratorParam, 4},
  { "SetModelGlobalParam", (DL_FUNC) &Rized_OpenFLUID_SetModelGlobalParam, 3},
  { "GetModelGlobalParam", (DL_FUNC) &Rized_OpenFLUID_GetModelGlobalParam, 2},
  { "RemoveModelGlobalParam", (DL_FUNC) &Rized_OpenFLUID_RemoveModelGlobalParam, 2},
  { "SetObserverParam", (DL_FUNC) &Rized_OpenFLUID_SetObserverParam, 4},
  { "GetObserverParam", (DL_FUNC) &Rized_OpenFLUID_GetObserverParam, 3},
  { "RemoveObserverParam", (DL_FUNC) &Rized_OpenFLUID_RemoveObserverParam, 3},
  { "GetUnitsClasses", (DL_FUNC) &Rized_OpenFLUID_GetUnitsClasses, 1},
  { "GetUnitsIDs", (DL_FUNC) &Rized_OpenFLUID_GetUnitsIDs, 2},
  { "CreateAttribute", (DL_FUNC) &Rized_OpenFLUID_CreateAttribute, 4},
  { "SetAttribute", (DL_FUNC) &Rized_OpenFLUID_SetAttribute, 5},
  { "GetAttribute", (DL_FUNC) &Rized_OpenFLUID_GetAttribute, 4},
  { "RemoveAttribute", (DL_FUNC) &Rized_OpenFLUID_RemoveAttribute, 3},
  { "SetDefaultDeltaT", (DL_FUNC) &Rized_OpenFLUID_SetDefaultDeltaT, 2},
  { "GetDefaultDeltaT", (DL_FUNC) &Rized_OpenFLUID_GetDefaultDeltaT, 1},
  { "SetPeriod", (DL_FUNC) &Rized_OpenFLUID_SetPeriod, 3},
  { "GetPeriodBeginDate", (DL_FUNC) &Rized_OpenFLUID_GetPeriodBeginDate, 1},
  { "GetPeriodEndDate", (DL_FUNC) &Rized_OpenFLUID_GetPeriodEndDate, 1},
  { "AddVariablesExportAsCSV", (DL_FUNC) &Rized_OpenFLUID_AddVariablesExportAsCSV, 2},
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


void Rized_OpenFLUID_AddExtraSimulatorsPaths(SEXP Paths)
{
  ROpenFLUID_AddExtraSimulatorsPaths(CHAR(STRING_ELT(Paths, 0)));
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_ResetExtraSimulatorsPaths()
{
  ROpenFLUID_ResetExtraSimulatorsPaths();
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetSimulatorsPaths()
{
  SEXP Ret;

  unsigned int PathsCount = ROpenFLUID_GetSimulatorsPathsCount();

  PROTECT(Ret = allocVector(STRSXP, PathsCount));

  if (PathsCount > 0)
  {
    char** Paths = ROpenFLUID_GetSimulatorsPaths();

    unsigned int i;

    for (i=0;i<PathsCount;i++)
    {
      SET_STRING_ELT(Ret, i, mkChar(Paths[i]));
    }

    for (i=0;i<PathsCount;i++)
       free (Paths[i]);

    free(Paths);
  }

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetExtraSimulatorsPaths()
{
  SEXP Ret;

  unsigned int PathsCount = ROpenFLUID_GetExtraSimulatorsPathsCount();

  PROTECT(Ret = allocVector(STRSXP, PathsCount));

  if (PathsCount > 0)
  {
    char** Paths = ROpenFLUID_GetExtraSimulatorsPaths();

    unsigned int i;
    for (i=0;i<PathsCount;i++)
    {
      SET_STRING_ELT(Ret, i, mkChar(Paths[i]));
    }

    for (i=0;i<PathsCount;i++)
       free (Paths[i]);

    free(Paths);
  }

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_AddExtraObserversPaths(SEXP Paths)
{
  ROpenFLUID_AddExtraObserversPaths(CHAR(STRING_ELT(Paths, 0)));
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_ResetExtraObserversPaths()
{
  ROpenFLUID_ResetExtraObserversPaths();
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetObserversPaths()
{
  SEXP Ret;

  unsigned int PathsCount = ROpenFLUID_GetObserversPathsCount();

  PROTECT(Ret = allocVector(STRSXP, PathsCount));

  if (PathsCount > 0)
  {
    char** Paths = ROpenFLUID_GetObserversPaths();

    unsigned int i;
    for (i=0;i<PathsCount;i++)
    {
      SET_STRING_ELT(Ret, i, mkChar(Paths[i]));
    }

    for (i=0;i<PathsCount;i++)
       free (Paths[i]);

    free(Paths);
  }

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetExtraObserversPaths()
{
  SEXP Ret;

  unsigned int PathsCount = ROpenFLUID_GetExtraObserversPathsCount();

  PROTECT(Ret = allocVector(STRSXP, PathsCount));

  if (PathsCount > 0)
  {
    char** Paths = ROpenFLUID_GetExtraObserversPaths();

    unsigned int i;
    for (i=0;i<PathsCount;i++)
    {
      SET_STRING_ELT(Ret, i, mkChar(Paths[i]));
    }

    for (i=0;i<PathsCount;i++)
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


void Rized_OpenFLUID_RunSimulation(SEXP Blob, SEXP Verbose)
{
  if (ROpenFLUID_RunSimulation(R_ExternalPtrAddr(Blob),asLogical(Verbose)) != 1)
  {
    Rf_error(ROpenFLUID_GetLastError());
  }
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_SetSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName, SEXP ParamVal)
{
  ROpenFLUID_SetSimulatorParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(SimulatorID, 0)),
                               CHAR(STRING_ELT(ParamName, 0)),CHAR(STRING_ELT(ParamVal, 0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName)
{
  SEXP Ret;

  const char* Val = ROpenFLUID_GetSimulatorParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(SimulatorID, 0)),
                                                 CHAR(STRING_ELT(ParamName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_RemoveSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName)
{
  ROpenFLUID_RemoveSimulatorParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(SimulatorID, 0)),
                                  CHAR(STRING_ELT(ParamName, 0)));
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_SetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName, SEXP ParamVal)

{
  ROpenFLUID_SetGeneratorParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)),CHAR(STRING_ELT(VarName, 0)),
                               CHAR(STRING_ELT(ParamName, 0)),CHAR(STRING_ELT(ParamVal, 0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName)

{
  SEXP Ret;

  const char* Val = ROpenFLUID_GetGeneratorParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)),
                                                 CHAR(STRING_ELT(VarName, 0)),CHAR(STRING_ELT(ParamName, 0)));

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


void Rized_OpenFLUID_RemoveModelGlobalParam(SEXP Blob, SEXP ParamName)
{
  ROpenFLUID_RemoveModelGlobalParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(ParamName, 0)));
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_SetObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName, SEXP ParamVal)
{
  ROpenFLUID_SetObserverParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(ObserverID, 0)),
                              CHAR(STRING_ELT(ParamName, 0)),CHAR(STRING_ELT(ParamVal, 0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName)
{
  SEXP Ret;

  const char* Val = ROpenFLUID_GetObserverParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(ObserverID, 0)),
                                                CHAR(STRING_ELT(ParamName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_RemoveObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName)
{
  ROpenFLUID_RemoveObserverParam(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(ObserverID, 0)),
                                 CHAR(STRING_ELT(ParamName, 0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetUnitsClasses(SEXP Blob)
{
  SEXP Ret;

  unsigned int ClassesCount = ROpenFLUID_GetUnitsClassesCount(R_ExternalPtrAddr(Blob));

  PROTECT(Ret = allocVector(STRSXP, ClassesCount));

  if (ClassesCount > 0)
  {
    char** Classes = ROpenFLUID_GetUnitsClasses(R_ExternalPtrAddr(Blob));

    unsigned int i;

    for (i=0;i<ClassesCount;i++)
    {
      SET_STRING_ELT(Ret, i, mkChar(Classes[i]));
    }

    for (i=0;i<ClassesCount;i++)
       free (Classes[i]);

    free(Classes);
  }

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetUnitsIDs(SEXP Blob, SEXP UnitClass)
{
  SEXP Ret;

  unsigned int IDsCount = ROpenFLUID_GetUnitsIDsCount(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)));

  PROTECT(Ret = allocVector(INTSXP, IDsCount));

  if (IDsCount > 0)
  {
    int* IDs = ROpenFLUID_GetUnitsIDs(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)));

    unsigned int i;

    for (i=0;i<IDsCount;i++)
      INTEGER(Ret)[i] = IDs[i];

    free(IDs);
  }

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_CreateAttribute(SEXP Blob,SEXP UnitClass, SEXP AttrName, SEXP AttrValue)
{
  ROpenFLUID_CreateAttribute(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)),
                             CHAR(STRING_ELT(AttrName, 0)),CHAR(STRING_ELT(AttrValue, 0)));
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_SetAttribute(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP AttrName, SEXP AttrValue)
{
  ROpenFLUID_SetAttribute(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)),INTEGER(UnitID)[0],
                          CHAR(STRING_ELT(AttrName, 0)),CHAR(STRING_ELT(AttrValue, 0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetAttribute(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP AttrName)
{
  SEXP Ret;

  const char* Val = ROpenFLUID_GetAttribute(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)),INTEGER(UnitID)[0],
                                            CHAR(STRING_ELT(AttrName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void Rized_OpenFLUID_RemoveAttribute(SEXP Blob, SEXP UnitClass, SEXP AttrName)
{
  ROpenFLUID_RemoveAttribute(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)),CHAR(STRING_ELT(AttrName, 0)));
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_SetDefaultDeltaT(SEXP Blob, SEXP DeltaT)
{
  ROpenFLUID_SetDefaultDeltaT(R_ExternalPtrAddr(Blob),INTEGER(DeltaT)[0]);
}


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_GetDefaultDeltaT(SEXP Blob)
{
  SEXP Ret;

  int DeltaT = ROpenFLUID_GetDefaultDeltaT(R_ExternalPtrAddr(Blob));

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


// =====================================================================
// =====================================================================


SEXP Rized_OpenFLUID_AddVariablesExportAsCSV(SEXP Blob, SEXP UnitClass)
{
  ROpenFLUID_AddVariablesExportAsCSV(R_ExternalPtrAddr(Blob),CHAR(STRING_ELT(UnitClass, 0)));
}

