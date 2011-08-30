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

static void Rized_OpenFLUID_Dummy(SEXP Message);

static void Rized_OpenFLUID_DeleteBlob(SEXP Blob);

static void Rized_OpenFLUID_AddExtraFunctionsPaths(SEXP Paths);

static SEXP Rized_OpenFLUID_RunProject(SEXP Path);
static SEXP Rized_OpenFLUID_NewProject();
static SEXP Rized_OpenFLUID_OpenProject(SEXP Path);
static SEXP Rized_OpenFLUID_RunSimulation(SEXP Blob);


// =====================================================================
// =====================================================================


R_CallMethodDef callEntries[] = {
  { "DeleteBlob", (DL_FUNC) &Rized_OpenFLUID_DeleteBlob, 1},
  { "AddExtraFunctionsPaths", (DL_FUNC) &Rized_OpenFLUID_AddExtraFunctionsPaths, 1},
  { "RunProject", (DL_FUNC) &Rized_OpenFLUID_RunProject, 1},
  { "NewProject", (DL_FUNC) &Rized_OpenFLUID_NewProject, 0},
  { "OpenProject", (DL_FUNC) &Rized_OpenFLUID_OpenProject, 1},
  { "RunSimulation", (DL_FUNC) &Rized_OpenFLUID_RunSimulation, 1},
  { "Dummy", (DL_FUNC) &Rized_OpenFLUID_Dummy, 1},
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


void Rized_OpenFLUID_Dummy(SEXP Message)
{
  Rprintf("[Dummy] %s\n",CHAR(STRING_ELT(Message, 0)));
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


SEXP Rized_OpenFLUID_RunProject(SEXP Path)
{
  SEXP Ret = R_NilValue;

  ROpenFLUID_ExtBlob_t Ptr = (ROpenFLUID_ExtBlob_t*)ROpenFLUID_RunProject(CHAR(STRING_ELT(Path, 0)));

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


SEXP Rized_OpenFLUID_NewProject()
{
  SEXP Ret = R_NilValue;

  ROpenFLUID_ExtBlob_t Ptr = (ROpenFLUID_ExtBlob_t*)ROpenFLUID_NewProject();

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


SEXP Rized_OpenFLUID_RunSimulation(SEXP Blob)
{
  SEXP Ret = R_NilValue;

  ROpenFLUID_ExtBlob_t Ptr = (ROpenFLUID_ExtBlob_t*)ROpenFLUID_RunSimulation(R_ExternalPtrAddr(Blob));

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


