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

#include "BoxCreator.h"
#include "EditorBaseClasses.h"
#include "EditorEditMode.h"
#include "EditorWindowViewport.h"

//-----------------------------------------------------------

cBoxCreator::cBoxCreator(iEditorEditMode* apEditMode) : iShapeCreator(apEditMode)
{
	mvDefaultSize = 1;
}

//-----------------------------------------------------------

void cBoxCreator::OnViewportMouseDown(int alButtons)
{
	if(alButtons==eGuiMouseButton_Left)
		StoreMousePosition(mvTempPoint);
	else if(alButtons==eGuiMouseButton_Right)
		mvPoints.pop_back();
}

//-----------------------------------------------------------

void cBoxCreator::OnViewportMouseUp(int alButtons)
{
	if(alButtons==eGuiMouseButton_Left && mvPoints.size()<3)
		StoreMousePosition(mvTempPoint);
}

//-----------------------------------------------------------

void cBoxCreator::Draw(cEditorWindowViewport* apViewport, cRendererCallbackFunctions* apFunctions)
{
	apFunctions->SetProgram(NULL);
	apFunctions->SetTextureRange(NULL,0);
	apFunctions->SetMatrix(NULL);

	/*apFunctions->GetLowLevelGfx()->DrawSphere(vDebugPos, 0.1f, cColor(0,0,1,1));
	apFunctions->GetLowLevelGfx()->DrawLine(vDebugPos, vDebugPos-cVector3f(vDebugPos.x,0,0), cColor(1,0,0,1));
	apFunctions->GetLowLevelGfx()->DrawLine(vDebugPos, vDebugPos-cVector3f(0,vDebugPos.y,0), cColor(0,1,0,1));
	apFunctions->GetLowLevelGfx()->DrawLine(vDebugPos, vDebugPos-cVector3f(0,0,vDebugPos.z), cColor(0,0,1,1));
	*/
	if(mvPoints.empty()==false && mbDragging==true)
		apFunctions->GetLowLevelGfx()->DrawBoxMinMax(mvPoints[0], mvTempPoint, cColor(1,1));
}

//-----------------------------------------------------------

void cBoxCreator::OnEditorUpdate()
{
	cEditorWindowViewport* pViewport = mpEditMode->GetEditor()->GetFocusedViewport();
	cEditorGrid* pGrid = pViewport->GetGrid();

	if(mvPoints.size()<2)
	{
		pViewport->GetMouseWorldPosition();
		mvTempPoint = pGrid->GetSnappedPosOnGrid(mpEditMode->GetEditor()->GetPosOnGridFromMousePos(false));
		mvDebugPos = mvTempPoint;
	}
	else
	{
		cVector3f vGridNormal = 0;
		vGridNormal.v[mPlaneNormal] = 1.0f;
		cVector3f vHeightPlaneNormal = cMath::Vector3Cross(vGridNormal, pViewport->GetCamera()->GetRight())*-1;
		vHeightPlaneNormal.Normalize();

		mBoxHeightPlane.FromNormalPoint(vHeightPlaneNormal, mvTempPoint);

		if(cMath::CheckPlaneLineIntersection(mBoxHeightPlane, pViewport->GetUnprojectedStart(), pViewport->GetUnprojectedEnd(), &mvTempPoint, NULL))
		{
			mvDebugPos = mvTempPoint;
			for(int i=0;i<3;++i)
				if(i!=mPlaneNormal) mvTempPoint.v[i] = mvPoints[1].v[i];
		}
		if(pGrid->GetSnapToGrid()) mvTempPoint = pGrid->GetSnappedPosInSpace(mvTempPoint);
	}
}

//-----------------------------------------------------------

bool cBoxCreator::IsDoneCreating()
{
	return mvPoints.size()==3 ||
		(mvPoints.size()==2 && ((mvPoints[0]-mvPoints[1]).Length()<kEpsilonf || mbDragging==false));
}

//-----------------------------------------------------------

void cBoxCreator::Reset()
{
	mvPoints.clear();
}

//-----------------------------------------------------------

cVector3f cBoxCreator::GetBoxCenter()
{
	if(mvPoints.size()==2)
	{
		if(mbDragging) return mvPoints[0];
		else return mvPoints[1];
	}
	else
		return (mvPoints[0]+mvPoints[2])*0.5f;
}

//-----------------------------------------------------------

cVector3f cBoxCreator::GetBoxSize()
{
	if(mbDragging==false || mvPoints.size()==2)
		return mvDefaultSize;

	cVector3f vSize = mvPoints[2]-mvPoints[0];
	if(vSize.Length()<kEpsilonf)
		return mvDefaultSize;

	for(int i=0;i<3;++i)
		vSize.v[i] = cMath::Abs(vSize.v[i]);

    return vSize;
}

//-----------------------------------------------------------

void cBoxCreator::OnStoreMousePosition(const cVector3f& avX)
{
	if(mvPoints.size()==2)
	{
		cEditorWindowViewport* pViewport = mpEditMode->GetEditor()->GetFocusedViewport();
		mPlaneNormal = pViewport->GetGrid()->GetPlaneNormal();
	}
}

//-----------------------------------------------------------
