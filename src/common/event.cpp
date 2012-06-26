// * This file is part of the COLOBOT source code
// * Copyright (C) 2001-2008, Daniel ROUX & EPSITEC SA, www.epsitec.ch
// *
// * This program is free software: you can redistribute it and/or modify
// * it under the terms of the GNU General Public License as published by
// * the Free Software Foundation, either version 3 of the License, or
// * (at your option) any later version.
// *
// * This program is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with this program. If not, see  http://www.gnu.org/licenses/.

// event.cpp

#include "common/iman.h"
#include "common/event.h"

#include <string.h>


Event::Event()
{
    event = EVENT_NULL;
    param = 0;
    axeX = 0.0f;
    axeY = 0.0f;
    axeZ = 0.0f;
    keyState = 0;
    rTime = 0.0f;
}


// Object's constructor.

CEvent::CEvent(CInstanceManager* iMan)
{
    m_iMan = iMan;
    m_iMan->AddInstance(CLASS_EVENT, this);

    Flush();
}

// Object's destructor.

CEvent::~CEvent()
{
}


// Empty the FIFO of events.

void CEvent::Flush()
{
    m_head = 0;
    m_tail = 0;
    m_total = 0;
}

// Produces an event.

void CEvent::MakeEvent(Event &event, EventMsg msg)
{
    memset(&event, 0, sizeof(Event));
    event.event = msg;
}

// Adds an event in the FIFO.

bool CEvent::AddEvent(const Event &event)
{
    if ( m_total >= MAXEVENT )  return false;

    m_fifo[m_head++] = event;
    if ( m_head >= MAXEVENT )  m_head = 0;
    m_total ++;

    return true;
}

// Removes an event from the FIFO.

bool CEvent::GetEvent(Event &event)
{
    if ( m_head == m_tail )  return false;

    event = m_fifo[m_tail++];
    if ( m_tail >= MAXEVENT )  m_tail = 0;
    m_total --;

    return true;
}
