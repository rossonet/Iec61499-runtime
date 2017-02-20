/*******************************************************************************
 * Copyright (c) 2016 - 2017 fortiss GmbH
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Ben Schneider
 *      - initial implementation and documentation
 *******************************************************************************/

#include <extevhan.h>
#include <thread.h>
#include <singlet.h>

#include <forte_string.h>
#include <string>

class CROSActionManager : public CExternalEventHandler, private CThread{
  DECLARE_SINGLETON(CROSActionManager)

  public:
    virtual void enableHandler();
    virtual void disableHandler();
    virtual void setPriority(int pa_prio);
    virtual int getPriority() const;

    void startChain(CEventSourceFB *pa_poECStartF);
    std::string ciecStringToStdString(const CIEC_STRING &pa_DataInput);
    CIEC_STRING stdStringToCiecString(const std::string pa_inputString);

  protected:
    virtual void run();

};
