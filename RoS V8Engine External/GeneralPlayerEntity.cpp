#include "stdafx.h"

D3DXVECTOR3 tGeneralPlayerEntity::tGeneralPlayerEntityFunctions::GetBonePosition(tDataStructs::tBoneMatrix* BoneMatrix, int BoneNumber)
{
	D3DXVECTOR3 BonePosition;
	BonePosition.x = BoneMatrix->Bones[BoneNumber].x;
	BonePosition.y = BoneMatrix->Bones[BoneNumber].y;
	BonePosition.z = BoneMatrix->Bones[BoneNumber].z;
	return BonePosition;
}

bool tGeneralPlayerEntity::tGeneralPlayerEntityFunctions::IsJumping(byte Flags)
{
	if (Flags == 1 || Flags == 3 || Flags == 5 || Flags == 7)
	{
		return false;
	}
	return true;
}

void tGeneralPlayerEntity::tGeneralPlayerEntityFunctions::GetCurrentLastEntityAdress(tGeneralPlayerEntityInfo* CurrentLastEntityInfo)
{
	pIO.Functions.Read<DWORD>(&CurrentLastEntityInfo->BaseAddress, pIO.ClientModuleBaseAddress + pGlobalVars.Offsets.Client);//Base Entity List  // + (pGlobalVars.Offsets.EntitySize * PlayerNumber));
	if (CurrentLastEntityInfo->BaseAddress)
	{
		pIO.Functions.Read<DWORD>(&CurrentLastEntityInfo->dwEntityStart, CurrentLastEntityInfo->BaseAddress + pGlobalVars.Offsets.m_dwEntityList);
		pIO.Functions.Read<DWORD>(&CurrentLastEntityInfo->dwEntityStart, CurrentLastEntityInfo->dwEntityStart);
		pIO.Functions.Read<DWORD>(&CurrentLastEntityInfo->dwLast, CurrentLastEntityInfo->dwEntityStart + 0x4); //Get Last entity
		pIO.Functions.Read<DWORD>(&CurrentLastEntityInfo->dwEntityStart, CurrentLastEntityInfo->dwEntityStart); //Get entity start
		//pIO.Functions.Read<DWORD>(&CurrentLastEntityInfo->dwLast, CurrentLastEntityInfo->BaseAddress + pGlobalVars.Offsets.m_dwEntityList + 0x0 + 0x4); 
	}
}

void tGeneralPlayerEntity::tGeneralPlayerEntityFunctions::GetGeneralPlayerEntityInfo(tGeneralPlayerEntityInfo* GeneralPlayerEntityInfo, DWORD CurrentEntity)
{
	if (GeneralPlayerEntityInfo)
	{
		GeneralPlayerEntityInfo->Valid = false;
		if (pIO.ClientModuleBaseAddress)
		{
			/*pIO.Functions.Read<DWORD>(&GeneralPlayerEntityInfo->BaseAddress, pIO.ClientModuleBaseAddress + pGlobalVars.Offsets.Client + pGlobalVars.Offsets.m_dwEntityList);//Base Entity List  // + (pGlobalVars.Offsets.EntitySize * PlayerNumber));
			if (GeneralPlayerEntityInfo->BaseAddress)
			{
				pIO.Functions.Read<DWORD>(&GeneralPlayerEntityInfo->CurrentEntity, GeneralPlayerEntityInfo->BaseAddress + CurrentEntity + 0xC);//Current entity
				memmove_s(&GeneralPlayerEntityInfo->CurrentEntity, sizeof(GeneralPlayerEntityInfo->CurrentEntity), &GeneralPlayerEntityInfo->CurrentEntity + 0, sizeof(GeneralPlayerEntityInfo->CurrentEntity));*/
				pIO.Functions.Read<tDataStructs::tDataChunk>(&GeneralPlayerEntityInfo->DataChunk1, CurrentEntity);
				if (GeneralPlayerEntityInfo->DataChunk1.Data)
				{
					/*memmove_s(&GeneralPlayerEntityInfo->Dormant, sizeof(GeneralPlayerEntityInfo->Dormant), &GeneralPlayerEntityInfo->DataChunk1.Data[pGlobalVars.Offsets.m_bDormant], sizeof(GeneralPlayerEntityInfo->Dormant));
					if (!GeneralPlayerEntityInfo->Dormant)
					{
						memmove_s(&GeneralPlayerEntityInfo->LifeState, sizeof(&GeneralPlayerEntityInfo->LifeState), &GeneralPlayerEntityInfo->DataChunk1.Data[pGlobalVars.Offsets.m_lifeState], sizeof(GeneralPlayerEntityInfo->LifeState));
						if (!GeneralPlayerEntityInfo->LifeState)
						{
							pIO.Functions.Read<DWORD>(&GeneralPlayerEntityInfo->GameResourcesBaseAddress, pIO.ClientModuleBaseAddress + pGlobalVars.Offsets.CSPlayerResource);
							if (GeneralPlayerEntityInfo->GameResourcesBaseAddress)
							{
								pIO.Functions.Read<tDataStructs::tDataChunk>(&GeneralPlayerEntityInfo->DataChunk2, GeneralPlayerEntityInfo->GameResourcesBaseAddress);
								if (GeneralPlayerEntityInfo->DataChunk2.Data)
								{
									memmove_s(&GeneralPlayerEntityInfo->Kills, sizeof(&GeneralPlayerEntityInfo->Kills), &GeneralPlayerEntityInfo->DataChunk2.Data[pGlobalVars.Offsets.m_iKills + ((PlayerNumber + 1) * sizeof(GeneralPlayerEntityInfo->Kills))], sizeof(GeneralPlayerEntityInfo->Kills));
									memmove_s(&GeneralPlayerEntityInfo->CompetetiveRankNumber, sizeof(&GeneralPlayerEntityInfo->CompetetiveRankNumber), &GeneralPlayerEntityInfo->DataChunk2.Data[pGlobalVars.Offsets.m_iCompetitiveRanking + ((PlayerNumber + 1) * sizeof(GeneralPlayerEntityInfo->CompetetiveRankNumber))], sizeof(GeneralPlayerEntityInfo->CompetetiveRankNumber));
									memmove_s(&GeneralPlayerEntityInfo->Deaths, sizeof(&GeneralPlayerEntityInfo->Deaths), &GeneralPlayerEntityInfo->DataChunk2.Data[pGlobalVars.Offsets.m_iDeaths + ((PlayerNumber + 1) * sizeof(GeneralPlayerEntityInfo->Deaths))], sizeof(GeneralPlayerEntityInfo->Deaths));
									memmove_s(&GeneralPlayerEntityInfo->HasC4, sizeof(&GeneralPlayerEntityInfo->HasC4), &GeneralPlayerEntityInfo->DataChunk2.Data[pGlobalVars.Offsets.m_iPlayerC4], sizeof(GeneralPlayerEntityInfo->HasC4));
									memmove_s(&GeneralPlayerEntityInfo->HasDefuser, sizeof(&GeneralPlayerEntityInfo->HasDefuser), &GeneralPlayerEntityInfo->DataChunk2.Data[pGlobalVars.Offsets.m_bHasDefuser + ((PlayerNumber + 1) * sizeof(GeneralPlayerEntityInfo->HasDefuser))], sizeof(GeneralPlayerEntityInfo->HasDefuser));
									pIO.Functions.Read<DWORD>(&GeneralPlayerEntityInfo->RadarBaseAddress, pIO.ClientModuleBaseAddress + pGlobalVars.Offsets.m_dwRadarBase);
									if (GeneralPlayerEntityInfo->RadarBaseAddress)
									{
										pIO.Functions.Read<DWORD>(&GeneralPlayerEntityInfo->RadarPointerBaseAddress, GeneralPlayerEntityInfo->RadarBaseAddress + pGlobalVars.Offsets.m_dwRadarBasePointer);
										if (GeneralPlayerEntityInfo->RadarPointerBaseAddress)
										{
											memmove_s(&GeneralPlayerEntityInfo->BoneMatrixBaseAddress, sizeof(GeneralPlayerEntityInfo->BoneMatrixBaseAddress), &GeneralPlayerEntityInfo->DataChunk1.Data[pGlobalVars.Offsets.m_dwBoneMatrix], sizeof(GeneralPlayerEntityInfo->BoneMatrixBaseAddress));*/
											//pIO.Functions.Read<tDataStructs::tEntityType>(&GeneralPlayerEntityInfo->EntityType, GeneralPlayerEntityInfo->RadarPointerBaseAddress + (pGlobalVars.Offsets.RadarName1 * (PlayerNumber + 1) + pGlobalVars.Offsets.RadarName2));
											if (true)//GeneralPlayerEntityInfo->EntityType)//GeneralPlayerEntityInfo->BoneMatrixBaseAddress)
											{
												//pIO.Functions.Read<tDataStructs::tBoneMatrix>(&GeneralPlayerEntityInfo->BoneMatrix, GeneralPlayerEntityInfo->BoneMatrixBaseAddress);
												pIO.Functions.Read<tDataStructs::tPlayerName>(&GeneralPlayerEntityInfo->PlayerName, GeneralPlayerEntityInfo->RadarPointerBaseAddress + (pGlobalVars.Offsets.RadarName1 * (PlayerNumber + 1) + pGlobalVars.Offsets.RadarName2));
												//memmove_s(&GeneralPlayerEntityInfo->Health, sizeof(GeneralPlayerEntityInfo->Health), &GeneralPlayerEntityInfo->DataChunk1.Data[pGlobalVars.Offsets.m_iHealth], sizeof(GeneralPlayerEntityInfo->Health));
												pIO.Functions.Read<DWORD>(&GeneralPlayerEntityInfo->dwFlags, CurrentEntity + 0x4);
												pIO.Functions.Read<DWORD>(&GeneralPlayerEntityInfo->dwFlags, GeneralPlayerEntityInfo->dwFlags + 0xC);
												pIO.Functions.Read<tDataStructs::tEntityType>(&GeneralPlayerEntityInfo->EntityType, GeneralPlayerEntityInfo->dwFlags);
												//memmove_s(&GeneralPlayerEntityInfo->Flags, sizeof(GeneralPlayerEntityInfo->Flags), &GeneralPlayerEntityInfo->DataChunk1.Data[pGlobalVars.Offsets.m_fFlags], sizeof(GeneralPlayerEntityInfo->Flags));
												memmove_s(&GeneralPlayerEntityInfo->Origin, sizeof(GeneralPlayerEntityInfo->Origin), &GeneralPlayerEntityInfo->DataChunk1.Data[pGlobalVars.Offsets.m_vecOrigin], sizeof(GeneralPlayerEntityInfo->Origin));
												//memmove_s(&GeneralPlayerEntityInfo->TeamNumber, sizeof(GeneralPlayerEntityInfo->TeamNumber), &GeneralPlayerEntityInfo->DataChunk1.Data[pGlobalVars.Offsets.m_iTeamNum], sizeof(GeneralPlayerEntityInfo->TeamNumber));
												//memmove_s(&GeneralPlayerEntityInfo->Velocity, sizeof(GeneralPlayerEntityInfo->Velocity), &GeneralPlayerEntityInfo->DataChunk1.Data[pGlobalVars.Offsets.m_vecVelocity], sizeof(GeneralPlayerEntityInfo->Velocity));
												GeneralPlayerEntityInfo->Valid = true;
											}
										/*}
									}
								}
							}
						}
					}*/
				}
			//}
		}
	}
}
