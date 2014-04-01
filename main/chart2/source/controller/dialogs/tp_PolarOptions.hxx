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


#ifndef _CHART2_TP_POLAROPTIONS_HXX
#define _CHART2_TP_POLAROPTIONS_HXX

#include <sfx2/tabdlg.hxx>
#include <vcl/fixed.hxx>
#include <vcl/button.hxx>
#include <vcl/field.hxx>
#include <svx/dialcontrol.hxx>

//.............................................................................
namespace chart
{
//.............................................................................

class PolarOptionsTabPage : public SfxTabPage
{

public:
    PolarOptionsTabPage(Window* pParent, const SfxItemSet& rInAttrs );
    virtual ~PolarOptionsTabPage();

    static SfxTabPage* Create(Window* pParent, const SfxItemSet& rInAttrs);
    virtual sal_Bool FillItemSet(SfxItemSet& rOutAttrs);
    virtual void Reset(const SfxItemSet& rInAttrs);
	
private:
    CheckBox         m_aCB_Clockwise;
    FixedLine        m_aFL_StartingAngle;
    svx::DialControl m_aAngleDial;
    FixedText        m_aFT_Degrees;
    NumericField     m_aNF_StartingAngle;

    FixedLine        m_aFL_PlotOptions;
    CheckBox         m_aCB_IncludeHiddenCells;
};

//.............................................................................
} //namespace chart
//.............................................................................

#endif