/*******************************************************************************
 * Copyright (c) 2016 fortiss GmbH
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Jose Cabral - initial API and implementation and/or initial documentation
 *******************************************************************************/
 
#include "fileWriter.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "fileWriter_gen.cpp"
#endif
#include <string.h>
#include <errno.h>

DEFINE_FIRMWARE_FB(fileWriter, g_nStringIdfileWriter);

const CStringDictionary::TStringId fileWriter::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdFILE_NAME, g_nStringIdS1};

const CStringDictionary::TStringId fileWriter::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING};

const CStringDictionary::TStringId fileWriter::scm_anDataOutputNames[] = { g_nStringIdQO, g_nStringIdSTATUS };

const CStringDictionary::TStringId fileWriter::scm_anDataOutputTypeIds[] = { g_nStringIdBOOL, g_nStringIdSTRING };

const TForteInt16 fileWriter::scm_anEIWithIndexes[] = { 0, 3 };
const TDataIOID fileWriter::scm_anEIWith[] = {0, 1, 255, 0, 2, 255};
const CStringDictionary::TStringId fileWriter::scm_anEventInputNames[] = { g_nStringIdINIT, g_nStringIdREQ };


const TDataIOID fileWriter::scm_anEOWith[] = { 0, 1, 255, 0, 1, 255 };
const TForteInt16 fileWriter::scm_anEOWithIndexes[] = { 0, 3, -1 };
const CStringDictionary::TStringId fileWriter::scm_anEventOutputNames[] = { g_nStringIdINITO, g_nStringIdCNF };

const SFBInterfaceSpec fileWriter::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,
  3,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

void fileWriter::executeEvent(int pa_nEIID){ //TODO: manage output and status
  switch (pa_nEIID){
    case scm_nEventINITID:
      if(true == QI()){
        openFile();
      }
      else{
        closeFile();
      }
      sendOutputEvent(scm_nEventINITOID);
      break;
    case scm_nEventREQID:
      QO() = QI();
      if(true == QI()){
        writeFile();
      }
      sendOutputEvent(scm_nEventCNFID);
      break;
  }
}

fileWriter::fileWriter(const CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) :
    CFunctionBlock(pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId, m_anFBConnData, m_anFBVarsData){
  mFile.rdbuf()->pubsetbuf(NULL, 0); //disable buffer to avoid latency
}

bool fileWriter::openFile(){
  int retVal = false;
  std::string sysFileName(FILE_NAME().getValue());
  if(sysFileName.size()){
    mFile.open(sysFileName.c_str(), std::fstream::out); //TODO change this when fully switching to C++11 for LMS EV3
    if(mFile.is_open()){
      retVal = true;
    }
  }
  return retVal;
}

void fileWriter::closeFile(){
  if(mFile.is_open()){
    mFile.close();
  }
}

bool fileWriter::writeFile(){
  bool retVal = false;
  if(mFile.is_open()){
    std::string toWrite(S1().getValue());
    mFile.seekp(0, std::ios::beg);
    mFile << toWrite;
    //TODO check if writing worked
    retVal = true;
  }
  return retVal;
}
