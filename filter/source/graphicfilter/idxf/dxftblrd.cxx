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
#include "precompiled_filter.hxx"

#include <string.h>
#include <dxftblrd.hxx>

//----------------------------------DXFLType-----------------------------------

DXFLType::DXFLType()
{
	pSucc=NULL;
	sName[0]=0;
	nFlags=0;
	sDescription[0]=0;
	nDashCount=0;
}

void DXFLType::Read(DXFGroupReader & rDGR)
{
	long nDashIndex=-1;

	while (rDGR.Read()!=0)
	{
		switch (rDGR.GetG())
		{
			case  2: strncpy( sName, rDGR.GetS(), DXF_MAX_STRING_LEN + 1 ); break;
			case 70: nFlags=rDGR.GetI(); break;
			case  3: strncpy( sDescription, rDGR.GetS(), DXF_MAX_STRING_LEN + 1 ); break;
			case 73:
				if (nDashIndex!=-1) {
					rDGR.SetError();
					return;
				}
				nDashCount=rDGR.GetI();
				if (nDashCount>DXF_MAX_DASH_COUNT)
					nDashCount=DXF_MAX_DASH_COUNT;
				nDashIndex=0;
				break;
			case 40: fPatternLength=rDGR.GetF(); break;
			case 49:
				if (nDashCount==-1) {
					rDGR.SetError();
					return;
				}
				if (nDashIndex<nDashCount)
					fDash[nDashIndex++]=rDGR.GetF();
				break;
		}
	}
}

//----------------------------------DXFLayer-----------------------------------

DXFLayer::DXFLayer()
{
	pSucc=NULL;
	sName[0]=0;
	nFlags=0;
	nColor=-1;
	sLineType[0]=0;
}

void DXFLayer::Read(DXFGroupReader & rDGR)
{
	while (rDGR.Read()!=0) {
		switch(rDGR.GetG()) {
			case  2: strncpy( sName, rDGR.GetS(), DXF_MAX_STRING_LEN + 1 ); break;
			case 70: nFlags=rDGR.GetI(); break;
			case 62: nColor=rDGR.GetI(); break;
			case  6: strncpy( sLineType, rDGR.GetS(), DXF_MAX_STRING_LEN + 1 ); break;
		}
	}
}

//----------------------------------DXFStyle-----------------------------------

DXFStyle::DXFStyle()
{
	pSucc=NULL;
	sName[0]=0;
	nFlags=0;
	fHeight=0.0;
	fWidthFak=1.0;
	fOblAngle=0.0;
	nTextGenFlags=0;
	fLastHeightUsed=0.0;
	sPrimFontFile[0]=0;
	sBigFontFile[0]=0;
}

void DXFStyle::Read(DXFGroupReader & rDGR)
{
	while (rDGR.Read()!=0) {
		switch(rDGR.GetG()) {
			case  2: strncpy( sName, rDGR.GetS(), DXF_MAX_STRING_LEN + 1 ); break;
			case 70: nFlags=rDGR.GetI(); break;
			case 40: fHeight=rDGR.GetF(); break;
			case 41: fWidthFak=rDGR.GetF(); break;
			case 50: fOblAngle=rDGR.GetF(); break;
			case 71: nTextGenFlags=rDGR.GetI(); break;
			case 42: fLastHeightUsed=rDGR.GetF(); break;
			case  3: strncpy( sPrimFontFile, rDGR.GetS(), DXF_MAX_STRING_LEN + 1 ); break;
			case  4: strncpy( sBigFontFile, rDGR.GetS(), DXF_MAX_STRING_LEN + 1 ); break;
		}
	}
}

//----------------------------------DXFVPort-----------------------------------

DXFVPort::DXFVPort()
{
	pSucc=NULL;

	sName[0]=0;
	nFlags=0;
	fMinX=0;
	fMinY=0;
	fMaxX=0;
	fMaxY=0;
	fCenterX=0;
	fCenterY=0;
	fSnapBaseX=0;
	fSnapBaseY=0;
	fSnapSapcingX=0;
	fSnapSpacingY=0;
	fGridX=0;
	fGridY=0;
	aDirection=DXFVector(0,0,1);
	aTarget=DXFVector(0,0,0);
	fHeight=0;
	fAspectRatio=0;
	fLensLength=0;
	fFrontClipPlane=0;
	fBackClipPlane=0;
	fTwistAngle=0;
	nStatus=0;
	nID=0;
	nMode=0;
	nCircleZoomPercent=0;
	nFastZoom=0;
	nUCSICON=0;
	nSnap=0;
	nGrid=0;
	nSnapStyle=0;
	nSnapIsopair=0;
}

void DXFVPort::Read(DXFGroupReader & rDGR)
{
	while (rDGR.Read()!=0) {
		switch(rDGR.GetG()) {
			case  2: strncpy( sName, rDGR.GetS(), DXF_MAX_STRING_LEN + 1); break;
			case 70: nFlags=rDGR.GetI(); break;
			case 10: fMinX=rDGR.GetF(); break;
			case 20: fMinY=rDGR.GetF(); break;
			case 11: fMaxX=rDGR.GetF(); break;
			case 21: fMaxY=rDGR.GetF(); break;
			case 12: fCenterX=rDGR.GetF(); break;
			case 22: fCenterY=rDGR.GetF(); break;
			case 13: fSnapBaseX=rDGR.GetF(); break;
			case 23: fSnapBaseY=rDGR.GetF(); break;
			case 14: fSnapSapcingX=rDGR.GetF(); break;
			case 24: fSnapSpacingY=rDGR.GetF(); break;
			case 15: fGridX=rDGR.GetF(); break;
			case 25: fGridY=rDGR.GetF(); break;
			case 16: aDirection.fx=rDGR.GetF(); break;
			case 26: aDirection.fy=rDGR.GetF(); break;
			case 36: aDirection.fz=rDGR.GetF(); break;
			case 17: aTarget.fx=rDGR.GetF(); break;
			case 27: aTarget.fy=rDGR.GetF(); break;
			case 37: aTarget.fz=rDGR.GetF(); break;
			case 40: fHeight=rDGR.GetF(); break;
			case 41: fAspectRatio=rDGR.GetF(); break;
			case 42: fLensLength=rDGR.GetF(); break;
			case 43: fFrontClipPlane=rDGR.GetF(); break;
			case 44: fBackClipPlane=rDGR.GetF(); break;
			case 51: fTwistAngle=rDGR.GetF(); break;
			case 68: nStatus=rDGR.GetI(); break;
			case 69: nID=rDGR.GetI(); break;
			case 71: nMode=rDGR.GetI(); break;
			case 72: nCircleZoomPercent=rDGR.GetI(); break;
			case 73: nFastZoom=rDGR.GetI(); break;
			case 74: nUCSICON=rDGR.GetI(); break;
			case 75: nSnap=rDGR.GetI(); break;
			case 76: nGrid=rDGR.GetI(); break;
			case 77: nSnapStyle=rDGR.GetI(); break;
			case 78: nSnapIsopair=rDGR.GetI(); break;
		}
	}
}

//----------------------------------DXFTables----------------------------------


DXFTables::DXFTables()
{
	pLTypes=NULL;
	pLayers=NULL;
	pStyles=NULL;
	pVPorts=NULL;
}


DXFTables::~DXFTables()
{
	Clear();
}


void DXFTables::Read(DXFGroupReader & rDGR)
{
	DXFLType * * ppLT, * pLT;
	DXFLayer * * ppLa, * pLa;
	DXFStyle * * ppSt, * pSt;
	DXFVPort * * ppVP, * pVP;

	ppLT=&pLTypes;
	while(*ppLT!=NULL) ppLT=&((*ppLT)->pSucc);

	ppLa=&pLayers;
	while(*ppLa!=NULL) ppLa=&((*ppLa)->pSucc);

	ppSt=&pStyles;
	while(*ppSt!=NULL) ppSt=&((*ppSt)->pSucc);

	ppVP=&pVPorts;
	while(*ppVP!=NULL) ppVP=&((*ppVP)->pSucc);

	for (;;) {
		while (rDGR.GetG()!=0) rDGR.Read();
		if (strcmp(rDGR.GetS(),"EOF")==0 ||
			strcmp(rDGR.GetS(),"ENDSEC")==0) break;
		else if (strcmp(rDGR.GetS(),"LTYPE")==0) {
			pLT=new DXFLType;
			pLT->Read(rDGR);
			*ppLT=pLT;
			ppLT=&(pLT->pSucc);
		}
		else if (strcmp(rDGR.GetS(),"LAYER")==0) {
			pLa=new DXFLayer;
			pLa->Read(rDGR);
			*ppLa=pLa;
			ppLa=&(pLa->pSucc);
		}
		else if (strcmp(rDGR.GetS(),"STYLE")==0) {
			pSt=new DXFStyle;
			pSt->Read(rDGR);
			*ppSt=pSt;
			ppSt=&(pSt->pSucc);
		}
		else if (strcmp(rDGR.GetS(),"VPORT")==0) {
			pVP=new DXFVPort;
			pVP->Read(rDGR);
			*ppVP=pVP;
			ppVP=&(pVP->pSucc);
		}
		else rDGR.Read();
	}
}


void DXFTables::Clear()
{
	DXFLType * pLT;
	DXFLayer * pLa;
	DXFStyle * pSt;
	DXFVPort * pVP;

	while (pStyles!=NULL) {
		pSt=pStyles;
		pStyles=pSt->pSucc;
		delete pSt;
	}
	while (pLayers!=NULL) {
		pLa=pLayers;
		pLayers=pLa->pSucc;
		delete pLa;
	}
	while (pLTypes!=NULL) {
		pLT=pLTypes;
		pLTypes=pLT->pSucc;
		delete pLT;
	}
	while (pVPorts!=NULL) {
		pVP=pVPorts;
		pVPorts=pVP->pSucc;
		delete pVP;
	}
}


DXFLType * DXFTables::SearchLType(const char * pName) const
{
	DXFLType * p;
	for (p=pLTypes; p!=NULL; p=p->pSucc) {
		if (strcmp(pName,p->sName)==0) break;
	}
	return p;
}


DXFLayer * DXFTables::SearchLayer(const char * pName) const
{
	DXFLayer * p;
	for (p=pLayers; p!=NULL; p=p->pSucc) {
		if (strcmp(pName,p->sName)==0) break;
	}
	return p;
}


DXFVPort * DXFTables::SearchVPort(const char * pName) const
{
	DXFVPort * p;
	for (p=pVPorts; p!=NULL; p=p->pSucc) {
		if (strcmp(pName,p->sName)==0) break;
	}
	return p;
}


