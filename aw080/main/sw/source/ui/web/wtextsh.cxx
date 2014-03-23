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



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_sw.hxx"



#include "hintids.hxx"
#include <sfx2/objface.hxx>
#include <sfx2/app.hxx>
#include <svl/srchitem.hxx> //***
#include <basic/sbxvar.hxx>
#ifndef _SVX_SVXIDS_HRC //autogen
#include <svx/svxids.hrc>
#endif

#include "swtypes.hxx"
#include "cmdid.h"
#include "view.hxx"
#include "wtextsh.hxx"
#include "basesh.hxx"
#include "globals.hrc"
#include "popup.hrc"
#include "shells.hrc"
#include "web.hrc"

#include <unomid.h>


// STATIC DATA -----------------------------------------------------------
#define SwWebTextShell
#define Paragraph
#define HyphenZone
#define TextFont
#define DropCap
#include <sfx2/msg.hxx>
#include "swslots.hxx"


/*--------------------------------------------------------------------
	Beschreibung:
 --------------------------------------------------------------------*/

SFX_IMPL_INTERFACE(SwWebTextShell, SwBaseShell, SW_RES(STR_SHELLNAME_WEBTEXT))
{
	SFX_POPUPMENU_REGISTRATION(SW_RES(MN_TEXT_POPUPMENU));
	SFX_OBJECTBAR_REGISTRATION(SFX_OBJECTBAR_OBJECT, SW_RES(RID_TEXT_TOOLBOX));
	SFX_CHILDWINDOW_REGISTRATION(FN_EDIT_FORMULA);
	SFX_CHILDWINDOW_REGISTRATION(FN_INSERT_FIELD);
}

/*--------------------------------------------------------------------
	Beschreibung:
 --------------------------------------------------------------------*/

SwWebTextShell::SwWebTextShell(SwView &_rView) :
    SwTextShell(_rView)
{
	SetHelpId(SW_WEBTEXTSHELL);
}

/*--------------------------------------------------------------------
	Beschreibung:
 --------------------------------------------------------------------*/


SwWebTextShell::~SwWebTextShell()
{
}


