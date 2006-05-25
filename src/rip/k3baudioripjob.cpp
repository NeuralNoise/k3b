/* 
 *
 * $Id: sourceheader 511311 2006-02-19 14:51:05Z trueg $
 * Copyright (C) 2006 Sebastian Trueg <trueg@k3b.org>
 *
 * This file is part of the K3b project.
 * Copyright (C) 1998-2006 Sebastian Trueg <trueg@k3b.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file "COPYING" for the exact licensing terms.
 */

#include "k3baudioripjob.h"
#include "k3baudioripthread.h"

#include <k3bthreadjob.h>
#include <k3binterferingsystemshandler.h>

#include <kdebug.h>
#include <klocale.h>


K3bAudioRipJob::K3bAudioRipJob( K3bJobHandler* hdl, QObject* parent )
  : K3bJob( hdl, parent )
{
  m_thread = new K3bAudioRipThread();
  m_threadJob = new K3bThreadJob( m_thread, this, this );
  m_interferingSystemsHandler = new K3bInterferingSystemsHandler( this, this );
  connect( m_interferingSystemsHandler, SIGNAL(infoMessage(const QString&, int)),
	   this, SIGNAL(infoMessage(const QString&, int)) );
  connectSubJob( m_threadJob,
		 SLOT(slotRippingFinished(bool)),
		 SIGNAL(newTask(const QString&)),
		 SIGNAL(newSubTask(const QString&)),
		 SIGNAL(percent(int)),
		 SIGNAL(subPercent(int)) );
}


K3bAudioRipJob::~K3bAudioRipJob()
{
}


QString K3bAudioRipJob::jobDescription() const
{
  return m_thread->jobDescription();
}


QString K3bAudioRipJob::jobDetails() const
{
  return m_thread->jobDetails();
}


void K3bAudioRipJob::start()
{
  m_interferingSystemsHandler->setDevice( m_thread->m_device );
  m_interferingSystemsHandler->disable();

  m_threadJob->start();
}


void K3bAudioRipJob::cancel()
{
  m_threadJob->cancel();
}


void K3bAudioRipJob::slotRippingFinished( bool success )
{
  m_interferingSystemsHandler->enable();
  jobFinished( success );
}

#include "k3baudioripjob.moc"