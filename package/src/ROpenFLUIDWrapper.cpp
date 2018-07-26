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


#define R_USE_C99_IN_CXX 1

#include <openfluid/utils/Binding.hpp>

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Print.h>
#include <stdio.h>


// =====================================================================
// =====================================================================


class ROutErr : public openfluid::utils::BindingAbstractOutErr
{
  public:

    void printfOut(const char* fmt, ... ) const
    {
      va_list args;
      va_start(args,fmt);
      Rvprintf(fmt,args);
      va_end(args);
    }

    void printfErr(const char* fmt, ... ) const
    {
      va_list args;
      va_start(args,fmt);
      REvprintf(fmt,args);
      va_end(args);
    }
};


OPENFLUID_BINDING_DEFINE(ROutErr);


// =====================================================================
// =====================================================================


#ifdef __cplusplus
extern "C" {
#endif


void ROpenFLUID_DeleteBlob(SEXP Blob);

void ROpenFLUID_PrintSimulationInfo(SEXP Blob);
SEXP ROpenFLUID_GetSimulationOutputDir(SEXP Blob);
SEXP ROpenFLUID_GetVersion();

void ROpenFLUID_AddExtraSimulatorsPaths(SEXP Paths);
void ROpenFLUID_ResetExtraSimulatorsPaths();
SEXP ROpenFLUID_GetSimulatorsPaths();
SEXP ROpenFLUID_GetExtraSimulatorsPaths();
void ROpenFLUID_AddExtraObserversPaths(SEXP Paths);
void ROpenFLUID_ResetExtraObserversPaths();
SEXP ROpenFLUID_GetObserversPaths();
SEXP ROpenFLUID_GetExtraObserversPaths();

SEXP ROpenFLUID_NewBlob();
SEXP ROpenFLUID_OpenProject(SEXP Path);
SEXP ROpenFLUID_OpenDataset(SEXP Path);
void ROpenFLUID_SetCurrentOutputDir(SEXP Path);
void ROpenFLUID_RunSimulation(SEXP Blob, SEXP Verbose);

void ROpenFLUID_SetSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName, SEXP ParamVal);
SEXP ROpenFLUID_GetSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName);
void ROpenFLUID_RemoveSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName);
void ROpenFLUID_SetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName, SEXP ParamVal);
SEXP ROpenFLUID_GetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName);
void ROpenFLUID_SetModelGlobalParam(SEXP Blob, SEXP ParamName, SEXP ParamVal);
SEXP ROpenFLUID_GetModelGlobalParam(SEXP Blob, SEXP ParamName);
void ROpenFLUID_RemoveModelGlobalParam(SEXP Blob, SEXP ParamName);
void ROpenFLUID_SetObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName, SEXP ParamVal);
SEXP ROpenFLUID_GetObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName);
void ROpenFLUID_RemoveObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName);

SEXP ROpenFLUID_GetUnitsClasses(SEXP Blob);
SEXP ROpenFLUID_GetUnitsIDs(SEXP Blob, SEXP UnitClass);

SEXP ROpenFLUID_GetGeneratorsVarNames(SEXP Blob, SEXP UnitClass);
SEXP ROpenFLUID_GetSimulatorsIDs(SEXP Blob);
SEXP ROpenFLUID_GetObserversIDs(SEXP Blob);

SEXP ROpenFLUID_GetModelGlobalParamNames(SEXP Blob);
SEXP ROpenFLUID_GetGeneratorParamNames(SEXP Blob, SEXP UnitClass, SEXP VarName);
SEXP ROpenFLUID_GetSimulatorParamNames(SEXP Blob, SEXP SimID);
SEXP ROpenFLUID_GetObserverParamNames(SEXP Blob, SEXP ObsID);

SEXP ROpenFLUID_GetAttributesNames(SEXP Blob, SEXP UnitClass);

void ROpenFLUID_CreateAttribute(SEXP Blob,SEXP UnitClass, SEXP AttrName, SEXP AttrValue);
void ROpenFLUID_SetAttribute(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP AttrName, SEXP AttrValue);
SEXP ROpenFLUID_GetAttribute(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP AttrName);
void ROpenFLUID_RemoveAttribute(SEXP Blob, SEXP UnitClass, SEXP AttrName);

SEXP ROpenFLUID_SetDefaultDeltaT(SEXP Blob, SEXP DeltaT);
SEXP ROpenFLUID_GetDefaultDeltaT(SEXP Blob);
SEXP ROpenFLUID_SetPeriod(SEXP Blob, SEXP Begin, SEXP End);
SEXP ROpenFLUID_GetPeriodBeginDate(SEXP Blob);
SEXP ROpenFLUID_GetPeriodEndDate(SEXP Blob);

SEXP ROpenFLUID_AddVariablesExportAsCSV(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP VarName, SEXP Prec);



// =====================================================================
// =====================================================================


static R_CallMethodDef callEntries[] = {
  { "DeleteBlob", (DL_FUNC) &ROpenFLUID_DeleteBlob, 1},
  { "PrintSimulationInfo", (DL_FUNC) &ROpenFLUID_PrintSimulationInfo, 1},
  { "GetSimulationOutputDir", (DL_FUNC) &ROpenFLUID_GetSimulationOutputDir, 1},
  { "GetVersion", (DL_FUNC) &ROpenFLUID_GetVersion, 0},
  { "AddExtraSimulatorsPaths", (DL_FUNC) &ROpenFLUID_AddExtraSimulatorsPaths, 1},
  { "ResetExtraSimulatorsPaths", (DL_FUNC) &ROpenFLUID_ResetExtraSimulatorsPaths, 0},
  { "GetSimulatorsPaths", (DL_FUNC) &ROpenFLUID_GetSimulatorsPaths, 0},
  { "GetExtraSimulatorsPaths", (DL_FUNC) &ROpenFLUID_GetExtraSimulatorsPaths, 0},
  { "AddExtraObserversPaths", (DL_FUNC) &ROpenFLUID_AddExtraObserversPaths, 1},
  { "ResetExtraObserversPaths", (DL_FUNC) &ROpenFLUID_ResetExtraObserversPaths, 0},
  { "GetObserversPaths", (DL_FUNC) &ROpenFLUID_GetObserversPaths, 0},
  { "GetExtraObserversPaths", (DL_FUNC) &ROpenFLUID_GetExtraObserversPaths, 0},
  { "NewBlob", (DL_FUNC) &ROpenFLUID_NewBlob, 0},
  { "OpenDataset", (DL_FUNC) &ROpenFLUID_OpenDataset, 1},
  { "SetCurrentOutputDir", (DL_FUNC) &ROpenFLUID_SetCurrentOutputDir, 1},
  { "OpenProject", (DL_FUNC) &ROpenFLUID_OpenProject, 1},
  { "RunSimulation", (DL_FUNC) &ROpenFLUID_RunSimulation, 2},
  { "SetSimulatorParam", (DL_FUNC) &ROpenFLUID_SetSimulatorParam, 4},
  { "GetSimulatorParam", (DL_FUNC) &ROpenFLUID_GetSimulatorParam, 3},
  { "RemoveSimulatorParam", (DL_FUNC) &ROpenFLUID_RemoveSimulatorParam, 3},
  { "SetGeneratorParam", (DL_FUNC) &ROpenFLUID_SetGeneratorParam, 5},
  { "GetGeneratorParam", (DL_FUNC) &ROpenFLUID_GetGeneratorParam, 4},
  { "SetModelGlobalParam", (DL_FUNC) &ROpenFLUID_SetModelGlobalParam, 3},
  { "GetModelGlobalParam", (DL_FUNC) &ROpenFLUID_GetModelGlobalParam, 2},
  { "RemoveModelGlobalParam", (DL_FUNC) &ROpenFLUID_RemoveModelGlobalParam, 2},
  { "SetObserverParam", (DL_FUNC) &ROpenFLUID_SetObserverParam, 4},
  { "GetObserverParam", (DL_FUNC) &ROpenFLUID_GetObserverParam, 3},
  { "RemoveObserverParam", (DL_FUNC) &ROpenFLUID_RemoveObserverParam, 3},
  { "GetUnitsClasses", (DL_FUNC) &ROpenFLUID_GetUnitsClasses, 1},
  { "GetUnitsIDs", (DL_FUNC) &ROpenFLUID_GetUnitsIDs, 2},
  { "GetGeneratorsVarNames", (DL_FUNC) &ROpenFLUID_GetGeneratorsVarNames, 2},
  { "GetSimulatorsIDs", (DL_FUNC) &ROpenFLUID_GetSimulatorsIDs, 1},
  { "GetObserversIDs", (DL_FUNC) &ROpenFLUID_GetObserversIDs, 1},
  { "GetModelGlobalParamNames", (DL_FUNC) &ROpenFLUID_GetModelGlobalParamNames, 1},
  { "GetGeneratorParamNames", (DL_FUNC) &ROpenFLUID_GetGeneratorParamNames, 3},
  { "GetSimulatorParamNames", (DL_FUNC) &ROpenFLUID_GetSimulatorParamNames, 2},
  { "GetObserverParamNames", (DL_FUNC) &ROpenFLUID_GetObserverParamNames, 2},
  { "GetAttributesNames", (DL_FUNC) &ROpenFLUID_GetAttributesNames, 2},
  { "CreateAttribute", (DL_FUNC) &ROpenFLUID_CreateAttribute, 4},
  { "SetAttribute", (DL_FUNC) &ROpenFLUID_SetAttribute, 5},
  { "GetAttribute", (DL_FUNC) &ROpenFLUID_GetAttribute, 4},
  { "RemoveAttribute", (DL_FUNC) &ROpenFLUID_RemoveAttribute, 3},
  { "SetDefaultDeltaT", (DL_FUNC) &ROpenFLUID_SetDefaultDeltaT, 2},
  { "GetDefaultDeltaT", (DL_FUNC) &ROpenFLUID_GetDefaultDeltaT, 1},
  { "SetPeriod", (DL_FUNC) &ROpenFLUID_SetPeriod, 3},
  { "GetPeriodBeginDate", (DL_FUNC) &ROpenFLUID_GetPeriodBeginDate, 1},
  { "GetPeriodEndDate", (DL_FUNC) &ROpenFLUID_GetPeriodEndDate, 1},
  { "AddVariablesExportAsCSV", (DL_FUNC) &ROpenFLUID_AddVariablesExportAsCSV, 5},
  { NULL, NULL, 0}
};


// =====================================================================
// =====================================================================


void R_init_ROpenFLUID(DllInfo* Info)
{
  R_registerRoutines(Info, NULL, callEntries, NULL, NULL);

  openfluid::utils::Binding::init();
}


void R_unload_ROpenFLUID(DllInfo* Info)
{

}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetVersion()
{
  SEXP Ret = R_NilValue;

  const char* Version = openfluid::utils::Binding::getVersion();

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


void ROpenFLUID_PrintSimulationInfo(SEXP Blob)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->printSimulationInfo();
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetSimulationOutputDir(SEXP Blob)
{
  SEXP Ret;

  const char* Path = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->getSimulationOutputDir();

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Path));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_DeleteBlob(SEXP Blob)
{
  openfluid::utils::Binding::destroy(reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob)));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_AddExtraSimulatorsPaths(SEXP Paths)
{
  openfluid::utils::Binding::addExtraSimulatorsPaths(CHAR(STRING_ELT(Paths, 0)));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_ResetExtraSimulatorsPaths()
{
  openfluid::utils::Binding::resetExtraSimulatorsPaths();
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetSimulatorsPaths()
{
  SEXP Ret;

  unsigned int PathsCount = openfluid::utils::Binding::getSimulatorsPathsCount();

  PROTECT(Ret = allocVector(STRSXP, PathsCount));

  if (PathsCount > 0)
  {
    char** Paths = openfluid::utils::Binding::getSimulatorsPaths();

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


SEXP ROpenFLUID_GetExtraSimulatorsPaths()
{
  SEXP Ret;

  unsigned int PathsCount = openfluid::utils::Binding::getExtraSimulatorsPathsCount();

  PROTECT(Ret = allocVector(STRSXP, PathsCount));

  if (PathsCount > 0)
  {
    char** Paths = openfluid::utils::Binding::getExtraSimulatorsPaths();

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


void ROpenFLUID_AddExtraObserversPaths(SEXP Paths)
{
  openfluid::utils::Binding::addExtraObserversPaths(CHAR(STRING_ELT(Paths, 0)));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_ResetExtraObserversPaths()
{
  openfluid::utils::Binding::resetExtraObserversPaths();
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetObserversPaths()
{
  SEXP Ret;

  unsigned int PathsCount = openfluid::utils::Binding::getObserversPathsCount();

  PROTECT(Ret = allocVector(STRSXP, PathsCount));

  if (PathsCount > 0)
  {
    char** Paths = openfluid::utils::Binding::getObserversPaths();

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


SEXP ROpenFLUID_GetExtraObserversPaths()
{
  SEXP Ret;

  unsigned int PathsCount = openfluid::utils::Binding::getExtraObserversPathsCount();

  PROTECT(Ret = allocVector(STRSXP, PathsCount));

  if (PathsCount > 0)
  {
    char** Paths = openfluid::utils::Binding::getExtraObserversPaths();

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


SEXP ROpenFLUID_NewBlob()
{
  SEXP Ret = R_NilValue;

  openfluid::utils::Binding* Ptr = openfluid::utils::Binding::make();

  if (Ptr)
  {
    PROTECT(Ret = R_MakeExternalPtr(Ptr, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(Ret, (R_CFinalizer_t) ROpenFLUID_DeleteBlob);
    UNPROTECT(1);
  }
  else
  {
    Rf_error(openfluid::utils::Binding::getLastError());
  }

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_OpenProject(SEXP Path)
{
  SEXP Ret = R_NilValue;

  openfluid::utils::Binding* Ptr = openfluid::utils::Binding::openProject(CHAR(STRING_ELT(Path, 0)));

  if (Ptr)
  {
    PROTECT(Ret = R_MakeExternalPtr(Ptr, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(Ret, (R_CFinalizer_t) ROpenFLUID_DeleteBlob);
    UNPROTECT(1);
  }
  else
  {
    Rf_error(openfluid::utils::Binding::getLastError());
  }

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_OpenDataset(SEXP Path)
{
  SEXP Ret = R_NilValue;

  openfluid::utils::Binding* Ptr = openfluid::utils::Binding::openDataset(CHAR(STRING_ELT(Path, 0)));

  if (Ptr)
  {
    PROTECT(Ret = R_MakeExternalPtr(Ptr, R_NilValue, R_NilValue));
    R_RegisterCFinalizer(Ret, (R_CFinalizer_t) ROpenFLUID_DeleteBlob);
    UNPROTECT(1);
  }
  else
  {
    Rf_error(openfluid::utils::Binding::getLastError());
  }

  return Ret;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetCurrentOutputDir(SEXP Path)
{
  openfluid::utils::Binding::setCurrentOutputDir(CHAR(STRING_ELT(Path, 0)));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RunSimulation(SEXP Blob, SEXP Verbose)
{
  if (reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->runSimulation(asLogical(Verbose)) != 1)
  {
    Rf_error(openfluid::utils::Binding::getLastError());
  }
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName, SEXP ParamVal)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      setSimulatorParam(CHAR(STRING_ELT(SimulatorID, 0)),CHAR(STRING_ELT(ParamName, 0)),CHAR(STRING_ELT(ParamVal, 0)));
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getSimulatorParam(CHAR(STRING_ELT(SimulatorID, 0)),CHAR(STRING_ELT(ParamName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveSimulatorParam(SEXP Blob, SEXP SimulatorID, SEXP ParamName)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      removeSimulatorParam(CHAR(STRING_ELT(SimulatorID, 0)),CHAR(STRING_ELT(ParamName, 0)));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName, SEXP ParamVal)

{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      setGeneratorParam(CHAR(STRING_ELT(UnitClass, 0)),CHAR(STRING_ELT(VarName, 0)),
                        CHAR(STRING_ELT(ParamName, 0)),CHAR(STRING_ELT(ParamVal, 0)));
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetGeneratorParam(SEXP Blob, SEXP UnitClass, SEXP VarName, SEXP ParamName)

{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getGeneratorParam(CHAR(STRING_ELT(UnitClass, 0)),CHAR(STRING_ELT(VarName, 0)),CHAR(STRING_ELT(ParamName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetModelGlobalParam(SEXP Blob, SEXP ParamName, SEXP ParamVal)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      setModelGlobalParam(CHAR(STRING_ELT(ParamName, 0)),CHAR(STRING_ELT(ParamVal, 0)));
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetModelGlobalParam(SEXP Blob, SEXP ParamName)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getModelGlobalParam(CHAR(STRING_ELT(ParamName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveModelGlobalParam(SEXP Blob, SEXP ParamName)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      removeModelGlobalParam(CHAR(STRING_ELT(ParamName, 0)));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName, SEXP ParamVal)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      setObserverParam(CHAR(STRING_ELT(ObserverID, 0)),CHAR(STRING_ELT(ParamName, 0)),CHAR(STRING_ELT(ParamVal, 0)));
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getObserverParam(CHAR(STRING_ELT(ObserverID, 0)),CHAR(STRING_ELT(ParamName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveObserverParam(SEXP Blob, SEXP ObserverID, SEXP ParamName)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      removeObserverParam(CHAR(STRING_ELT(ObserverID, 0)),CHAR(STRING_ELT(ParamName, 0)));
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetUnitsClasses(SEXP Blob)
{
  SEXP Ret;

  unsigned int ClassesCount = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getUnitsClassesCount();

  PROTECT(Ret = allocVector(STRSXP, ClassesCount));

  if (ClassesCount > 0)
  {
    char** Classes = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
        getUnitsClasses();

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


SEXP ROpenFLUID_GetUnitsIDs(SEXP Blob, SEXP UnitClass)
{
  SEXP Ret;

  unsigned int IDsCount = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getUnitsIDsCount(CHAR(STRING_ELT(UnitClass, 0)));

  PROTECT(Ret = allocVector(INTSXP, IDsCount));

  if (IDsCount > 0)
  {
    int* IDs = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
        getUnitsIDs(CHAR(STRING_ELT(UnitClass, 0)));

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


SEXP ROpenFLUID_GetGeneratorsVarNames(SEXP Blob, SEXP UnitClass)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getGeneratorsVarNames(CHAR(STRING_ELT(UnitClass, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetSimulatorsIDs(SEXP Blob)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getSimulatorsIDs();

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetObserversIDs(SEXP Blob)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getObserversIDs();

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetModelGlobalParamNames(SEXP Blob)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getModelGlobalParamNames();

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetGeneratorParamNames(SEXP Blob,SEXP UnitsClass, SEXP VarName)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getGeneratorParamNames(CHAR(STRING_ELT(UnitsClass, 0)),CHAR(STRING_ELT(VarName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetSimulatorParamNames(SEXP Blob, SEXP SimID)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getSimulatorParamNames(CHAR(STRING_ELT(SimID, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetObserverParamNames(SEXP Blob, SEXP ObsID)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getObserverParamNames(CHAR(STRING_ELT(ObsID, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetAttributesNames(SEXP Blob, SEXP UnitClass)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getAttributesNames(CHAR(STRING_ELT(UnitClass, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_CreateAttribute(SEXP Blob,SEXP UnitClass, SEXP AttrName, SEXP AttrValue)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      createAttribute(CHAR(STRING_ELT(UnitClass, 0)),CHAR(STRING_ELT(AttrName, 0)),CHAR(STRING_ELT(AttrValue, 0)));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetAttribute(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP AttrName, SEXP AttrValue)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      setAttribute(CHAR(STRING_ELT(UnitClass, 0)),INTEGER(UnitID)[0],
                   CHAR(STRING_ELT(AttrName, 0)),CHAR(STRING_ELT(AttrValue, 0)));
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetAttribute(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP AttrName)
{
  SEXP Ret;

  const char* Val = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getAttribute(CHAR(STRING_ELT(UnitClass, 0)),INTEGER(UnitID)[0],CHAR(STRING_ELT(AttrName, 0)));

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(Val));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveAttribute(SEXP Blob, SEXP UnitClass, SEXP AttrName)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      removeAttribute(CHAR(STRING_ELT(UnitClass, 0)),CHAR(STRING_ELT(AttrName, 0)));
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_SetDefaultDeltaT(SEXP Blob, SEXP DeltaT)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      setDefaultDeltaT(INTEGER(DeltaT)[0]);
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetDefaultDeltaT(SEXP Blob)
{
  SEXP Ret;

  int DeltaT = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->getDefaultDeltaT();

  PROTECT(Ret = allocVector(INTSXP, 1));
  INTEGER(Ret)[0] = DeltaT;
  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_SetPeriod(SEXP Blob, SEXP Begin, SEXP End)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      setPeriod(CHAR(STRING_ELT(Begin,0)),CHAR(STRING_ELT(End,0)));
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetPeriodBeginDate(SEXP Blob)
{
  SEXP Ret;

  const char* DateStr = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getPeriodBeginDate();

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(DateStr));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_GetPeriodEndDate(SEXP Blob)
{
  SEXP Ret;

  const char* DateStr = reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      getPeriodEndDate();

  PROTECT(Ret = allocVector(STRSXP, 1));

  SET_STRING_ELT(Ret, 0, mkChar(DateStr));

  UNPROTECT(1);

  return Ret;
}


// =====================================================================
// =====================================================================


SEXP ROpenFLUID_AddVariablesExportAsCSV(SEXP Blob, SEXP UnitClass, SEXP UnitID, SEXP VarName, SEXP Prec)
{
  reinterpret_cast<openfluid::utils::Binding*>(R_ExternalPtrAddr(Blob))->
      addVariablesExportAsCSV("ropenfluid",
                              CHAR(STRING_ELT(UnitClass, 0)),CHAR(STRING_ELT(UnitID, 0)),
                              CHAR(STRING_ELT(VarName, 0)),INTEGER(Prec)[0]);
}


#ifdef __cplusplus
}
#endif
