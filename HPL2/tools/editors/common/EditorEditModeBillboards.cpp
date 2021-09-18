/*
 * Copyright © 2011-2020 Frictional Games
 *
 * This file is part of Amnesia: A Machine For Pigs.
 *
 * Amnesia: A Machine For Pigs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Amnesia: A Machine For Pigs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Amnesia: A Machine For Pigs.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "EditorEditModeBillboards.h"
#include "EditorWindowBillboards.h"

#include "EntityWrapperBillboard.h"
#include "EditorWorld.h"

//-----------------------------------------------------------------

///////////////////////////////////////////////////////////////////
// CONSTRUCTORS
///////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------

cEditorEditModeBillboards::cEditorEditModeBillboards(iEditorBase* apEditor,
													 iEditorWorld* apEditorWorld) : iEditorEditModeObjectCreator(apEditor,"Billboards",apEditorWorld)
{
}

//-----------------------------------------------------------------

//-----------------------------------------------------------------

///////////////////////////////////////////////////////////////////
// PUBLIC METHODS
///////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------

bool cEditorEditModeBillboards::SetUpCreationData(iEntityWrapperData* apData)
{
	if(iEditorEditModeObjectCreator::SetUpCreationData(apData)==false)
		return false;

	cEditorWindowBillboards* pWin = (cEditorWindowBillboards*)GetEditorWindow();
	apData->SetString(eBillboardStr_Material, cString::To8Char(pWin->GetBBMaterial()));
	apData->SetColor(eBillboardCol_Color, pWin->GetBBColor());

	return true;
}

//-----------------------------------------------------------------

///////////////////////////////////////////////////////////////////
// PROTECTED METHODS
///////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------

void cEditorEditModeBillboards::CreateTypes()
{
	mvTypes.push_back(hplNew(cEntityWrapperTypeBillboard,()));
}
//-----------------------------------------------------------------

iEditorWindow* cEditorEditModeBillboards::CreateSpecificWindow()
{
	return hplNew(cEditorWindowBillboards,(this));
}

//-----------------------------------------------------------------
