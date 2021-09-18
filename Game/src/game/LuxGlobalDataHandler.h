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

#ifndef LUX_GLOBAL_DATA_HANDLER_H
#define LUX_GLOBAL_DATA_HANDLER_H

//----------------------------------------------

#include "LuxBase.h"

//----------------------------------------------

class cLuxGlobalDataHandler : public iLuxUpdateable
{
friend class cLuxGlobalDataHandler_SaveData;
public:
	cLuxGlobalDataHandler();
	~cLuxGlobalDataHandler();

	void LoadAndInitGlobalScript();
	void OnGameStart();
	void OnStart();
	void Update(float afTimeStep);
	void Reset();

	void OnMapEnter(cLuxMap *apMap);
	void OnMapLeave(cLuxMap *apMap);

	void LoadScript();
	bool RecompileScript(tString *apOutput);

	void RunScript(const tString& asCommand);

	cLuxScriptVar* GetVar(const tString &asName);

	/////////////////////////////
	// AI
	bool GetEnemyActivateSoundAllowed();
	void SetEnemyActivateSoundMade();


	/////////////////////////////
	// Misc settings
	float GetLightLampMaxInfectionIncrease(){return mfLightLampMaxInfectionIncrease;}
	float GetLightLampMinInfectionIncrease(){return mfLightLampMinInfectionIncrease;}

private:
	tLuxScriptVarMap m_mapVars;
	iScript *mpScript;

	float mfEnemyActivateSoundCount;

	float mfLightLampMaxInfectionIncrease;
	float mfLightLampMinInfectionIncrease;
};

//----------------------------------------------


#endif // LUX_GLOBAL_DATA_HANDLER_H
