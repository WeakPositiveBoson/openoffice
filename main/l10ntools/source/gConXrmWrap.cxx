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
#include "gConXrm.hxx"
#include <iostream>
#include <fstream>
#include <cstdlib>


/*****************************************************************************
 *********************   G C O N X R M W R A P . C X X   *********************
 *****************************************************************************
 * This includes the c code generated by flex
 *****************************************************************************/



/************   I N T E R F A C E   I M P L E M E N T A T I O N   ************/
convert_xrm::convert_xrm(l10nMem& crMemory)
                        : convert_gen_impl(crMemory),
                          mbNoCollectingData(true),
                          mbIsTag(false),
                          mbIsLang(false)
{
}



/************   I N T E R F A C E   I M P L E M E N T A T I O N   ************/
convert_xrm::~convert_xrm()
{
}



/**********************   I M P L E M E N T A T I O N   **********************/
namespace XrmWrap
{
#define IMPLptr convert_gen_impl::mcImpl
#define LOCptr ((convert_xrm *)convert_gen_impl::mcImpl)
#include "gConXrm_yy.c"
}


/**********************   I M P L E M E N T A T I O N   **********************/
void convert_xrm::execute()
{
  XrmWrap::yylex();

  // write last part of file.
  if (mbMergeMode)
    writeSourceFile(msCollector);
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_xrm::setId(char *yytext)
{
  std::string& sText = copySource(yytext, mbNoCollectingData);
  int          nL, nE;


  if (mbIsTag)
  {
    nL = sText.find("\"");
    nE = sText.find("\"", nL+1);
    if (nL == (int)std::string::npos || nE == (int)std::string::npos)
      return;

    msKey = sText.substr(nL+1, nE - nL -1);
  }
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_xrm::setLang(char *yytext)
{
  std::string& sText = copySource(yytext, mbNoCollectingData);
  std::string  sLang;
  int          nL, nE;


  if (mbIsTag)
  {
    nL = sText.find("\"");
    nE = sText.find("\"", nL+1);
    if (nL == (int)std::string::npos || nE == (int)std::string::npos)
      return;

    sLang = sText.substr(nL+1, nE - nL -1);
    if (sLang == "en-US")
      mbIsLang = true;
    else
      showError((char *)(sLang + " is no en-US language").c_str());
  }
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_xrm::setTag(char *yytext)
{
  copySource(yytext);

  msKey.clear();
  mbIsLang = false;
  mbIsTag  = true;
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_xrm::startCollectData(char *yytext)
{
  copySource(yytext, mbNoCollectingData);

  if (mbIsTag && mbIsLang && msKey.size())
    mbNoCollectingData = false;

  mbIsTag = mbIsLang = false;
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_xrm::stopCollectData(char *yytext)
{
  if (!mbNoCollectingData)
  {
    msKey = msKey + "." + msKey;
    mcMemory.setEnUsKey(miLineNo, msKey, std::string("text"), msCollector);
    mbNoCollectingData = true;
    msKey.clear();
  }
  copySource(yytext);
}  
