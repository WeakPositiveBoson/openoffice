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
#include "gConPo.hxx"
#include <iostream>
#include <fstream>
#include <cstdlib>



/*****************************************************************************
 **********************   G C O N P O W R A P . C X X   **********************
 *****************************************************************************
 * This includes the c code generated by flex
 *****************************************************************************/



/************   I N T E R F A C E   I M P L E M E N T A T I O N   ************/
convert_po::convert_po(l10nMem& crMemory) : convert_gen_impl(crMemory) {}
convert_po::~convert_po()                                              {}



/**********************   I M P L E M E N T A T I O N   **********************/
namespace PoWrap
{
#define IMPLptr convert_gen_impl::mcImpl
#define LOCptr ((convert_po *)convert_gen_impl::mcImpl)
#include "gConPo_yy.c"
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_po::execute()
{
  PoWrap::yylex();
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_po::startCollectData(char *syyText)
{
  std::string sCollectedText = copySource(syyText);

//  mbCollectingData = true;
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_po::stopCollectData(char *syyText)
{
  std::string sCollectedText = copySource(syyText);
  std::string useKey;



  if (mbMergeMode)
  {
    // get all languages (includes en-US)
    std::vector<l10nMem_entry *>& cExtraLangauges = mcMemory.getLanguagesForKey(useKey);
    std::string                   sNewLine;
    int                      nL = cExtraLangauges.size();

  writeSourceFile(msCollector + sCollectedText);
    for (int i = 0; i < nL; ++i)
    {
      sNewLine = "<value xml:lang=\"" + cExtraLangauges[i]->msLanguage + "\">" +
             cExtraLangauges[i]->msText + "</value>";
      writeSourceFile(sNewLine);
    }
  }
  else
    mcMemory.setEnUsKey(miLineNo, useKey, std::string("dummy"), sCollectedText);

//  mbCollectingData = false;
  msCollector.clear();
}  
