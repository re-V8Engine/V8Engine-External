#include "stdafx.h"

tGlobalVars::tGlobalVars()
{
    this->IOSettings.ClientModuleName = L"ros.exe";
    this->IOSettings.EngineModuleName = L"engine.dll";
    this->IOSettings.TargetProcessName = L"ros.exe";
    this->IOSettings.SettingsPath = L"C:\\PP-Multi\\Settings.txt";
    this->OverlayWindowSettings.OverlayWindowName = L"Puddin Poppin CSGO Multi-Hack";
    this->OverlayWindowSettings.ReferenceWindowName = L"Rules of Survival 1.138505.140439";
}