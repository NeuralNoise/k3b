/* 
 *
 * $Id$
 * Copyright (C) 2003 Sebastian Trueg <trueg@k3b.org>
 *
 * This file is part of the K3b project.
 * Copyright (C) 1998-2003 Sebastian Trueg <trueg@k3b.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file "COPYING" for the exact licensing terms.
 */


#include "k3bapplication.h"

#include <device/k3bdevicemanager.h>
#include <tools/k3bexternalbinmanager.h>
#include <tools/k3bdefaultexternalprograms.h>
#include <tools/k3bglobals.h>

#include <klocale.h>
#include <kconfig.h>


K3bApplication::K3bApplication()
  : KApplication()
{
}


K3bApplication::~K3bApplication()
{
}


void K3bApplication::init()
{
  emit initializationInfo( i18n("Reading Options...") );

  KConfig globalConfig( K3b::globalConfig() );

  // external bin manager
  // ===============================================================================
  emit initializationInfo( i18n("Searching for external programs...") );

  K3b::addDefaultPrograms( K3bExternalBinManager::self() );
  K3bExternalBinManager::self()->search();

  if( globalConfig.hasGroup("External Programs") ) {
    globalConfig.setGroup( "External Programs" );
    K3bExternalBinManager::self()->readConfig( &globalConfig );
  }

  if( config()->hasGroup("External Programs") ) {
    config()->setGroup( "External Programs" );
    K3bExternalBinManager::self()->readConfig( config() );
  }

  // ===============================================================================


  // device manager
  // ===============================================================================
  emit initializationInfo( i18n("Scanning for CD devices...") );

  if( !K3bDeviceManager::self()->scanbus() )
    kdDebug() << "No Devices found!" << endl;

  if( globalConfig.hasGroup("Devices") ) {
    globalConfig.setGroup( "Devices" );
    K3bDeviceManager::self()->readConfig( &globalConfig );
  }

  if( config()->hasGroup("Devices") ) {
    config()->setGroup( "Devices" );
    K3bDeviceManager::self()->readConfig( config() );
  }

  K3bDeviceManager::self()->printDevices();
  // ===============================================================================

  //  emit initializationInfo( i18n("Initializing CD view...") );

  // ===============================================================================
//   emit initializationInfo( i18n("Reading local CDDB database...") );
//   config()->setGroup("Cddb");
//   QString filename = config()->readEntry("songlistPath", locateLocal("data", "k3b") + "/songlist.xml");
//   m_songManager = new K3bSongManager();
//   m_songManager->load( filename );
}

#include "k3bapplication.moc"
