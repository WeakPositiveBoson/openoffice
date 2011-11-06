/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/


#ifndef _SWLANGHELPER_HXX
#define _SWLANGHELPER_HXX

class SwWrtShell;
class SwView;
class EditEngine;
class EditView;
class OutlinerView;
class SfxItemSet;
struct ESelection;

namespace SwLangHelper
{
	extern sal_uInt16 GetLanguageStatus( OutlinerView* pOLV, SfxItemSet& rSet );
	extern bool SetLanguageStatus( OutlinerView* pOLV, SfxRequest &rReq, SwView &rView, SwWrtShell &rSh );

	extern void SetLanguage( SwWrtShell &rWrtSh, const String &rLangText, bool bIsForSelection, SfxItemSet &rCoreSet );
//	extern void SetLanguage( SwWrtShell &rWrtSh, EditEngine* pEditEngine, ESelection aSelection, const String &rLangText, bool bIsForSelection, SfxItemSet &rCoreSet );
	extern void SetLanguage( SwWrtShell &rWrtSh, OutlinerView* pOLV, ESelection aSelection, const String &rLangText, bool bIsForSelection, SfxItemSet &rCoreSet );
	extern void SetLanguage_None( SwWrtShell &rWrtSh, bool bIsForSelection, SfxItemSet &rCoreSet );
//	extern void SetLanguage_None( SwWrtShell &rWrtSh, EditEngine* pEditEngine, ESelection aSelection, bool bIsForSelection, SfxItemSet &rCoreSet  );
	extern void SetLanguage_None( SwWrtShell &rWrtSh, OutlinerView* pOLV, ESelection aSelection, bool bIsForSelection, SfxItemSet &rCoreSet  );
	extern void ResetLanguages( SwWrtShell &rWrtSh, bool bIsForSelection );
//	extern void ResetLanguages( SwWrtShell &rWrtSh, EditEngine* pEditEngine, ESelection aSelection, bool bIsForSelection );
	extern void ResetLanguages( SwWrtShell &rWrtSh, OutlinerView* pOLV, ESelection aSelection, bool bIsForSelection );
	
	// document
	extern void SelectCurrentPara( SwWrtShell &rWrtSh );
	// EditView
	extern void SelectPara( EditView &rEditView, const ESelection &rCurSel );
	
	extern String GetTextForLanguageGuessing( EditEngine* rEditEngine, ESelection aDocSelection );
	extern String GetTextForLanguageGuessing( SwWrtShell &rSh );
	
	extern LanguageType GetLanguage( SfxItemSet aSet, sal_uInt16 nLangWhichId );
	extern LanguageType GetLanguage( SwWrtShell &rSh, sal_uInt16 nLangWhichId );
	
	extern LanguageType GetCurrentLanguage( SfxItemSet aSet, sal_uInt16 nScriptType );
	extern LanguageType GetCurrentLanguage( SwWrtShell &rSh );
}

#endif
