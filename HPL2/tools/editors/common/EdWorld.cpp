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

#include "EdWorld.h"

//-----------------------------------------------------------------------

iTypeNode::iTypeNode(iEdWorld* apWorld, int alID, const tWString& asName, iTypeNode* apParentType)
{
	mpWorld = apWorld;
	mlID = alID;
	msName = cString::ToLowerCaseW(asName);
	mpParentType = apParentType;
	if(mpParentType) mpParentType->AddChildType(this);
}

//-----------------------------------------------------------------------

tWString iTypeNode::GetFullName()
{
	tWString sFullName;
	if(mpParentType)
		sFullName = mpParentType->GetFullName();

	sFullName += _W(".") + GetName();

	return sFullName;
}

//-----------------------------------------------------------------------

bool iTypeNode::IsA(int alID)
{
	if(mlID==alID)
		return true;
	else if(mpParentType)
		return mpParentType->IsA(alID);
	else
		return false;
}

bool iTypeNode::IsA(const tWString& asTypeName)
{
	if(msName==asTypeName)
		return true;
	else if(mpParentType)
		return mpParentType->IsA(asTypeName);
	else
		return false;
}

//-----------------------------------------------------------------------

iTypeNode* iTypeNode::GetTypeByName(const tWString& asName)
{
	if(msName==asName)
		return this;

	for(int i=0; i<(int)mvChildTypes.size(); ++i)
	{
		iTypeNode* pChild = mvChildTypes[i];

		iTypeNode* pType = pChild->GetTypeByName(asName);
		if(pType) return pType;
	}

	return NULL;
}

iTypeNode* iTypeNode::GetTypeByID(int alID)
{
	if(mlID==alID)
		return this;

	for(int i=0; i<(int)mvChildTypes.size(); ++i)
	{
		iTypeNode* pChild = mvChildTypes[i];

		iTypeNode* pType = pChild->GetTypeByID(alID);
		if(pType) return pType;
	}

	return NULL;
}

iTypeNode* iTypeNode::GetTypeByXmlElement(cXmlElement* apElement)
{
	// TODO: Implement !!
	return NULL;
}

//-----------------------------------------------------------------------

bool iTypeNode::AddChildType(iTypeNode* apType)
{
	if(apType)
	{
		mvChildTypes.push_back(apType);
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

iEdWorld::iEdWorld(iEditor* apEditor, const tWString& asName, const tWString& asFileExt, iTypeNode* apRootType)
{
	mpEditor = apEditor;
	msName = asName;
	msFileExt = asFileExt;
	mpRootType = apRootType;
}

//-----------------------------------------------------------------------

iTypeNode* iEdWorld::GetTypeByName(const tWString& asName)
{
	return mpRootType ?
			mpRootType->GetTypeByName(asName) :
			NULL;
}

iTypeNode* iEdWorld::GetTypeByID(int alID)
{
	return mpRootType ?
			mpRootType->GetTypeByID(alID) :
			NULL;
}

iTypeNode* iEdWorld::GetTypeByXmlElement(cXmlElement* apElement)
{
	return mpRootType ?
			mpRootType->GetTypeByXmlElement(apElement) :
			NULL;
}

//-----------------------------------------------------------------------


