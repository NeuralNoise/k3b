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

#include "k3bvideodvdrippingview.h"
#include "k3bvideodvdrippingtitlelistview.h"
#include "k3bvideodvdrippingdialog.h"

#include <k3bvideodvd.h>
#include <k3btoolbox.h>
#include <k3bthememanager.h>

#include <qcursor.h>
#include <qlayout.h>
#include <qlabel.h>

#include <kapplication.h>
#include <kmessagebox.h>
#include <klocale.h>
#include <kaction.h>



K3bVideoDVDRippingView::K3bVideoDVDRippingView( QWidget* parent, const char * name )
  : K3bCdContentsView( true, parent, name )
{
  QGridLayout* mainGrid = new QGridLayout( mainWidget() );

  // toolbox
  // ----------------------------------------------------------------------------------
  QHBoxLayout* toolBoxLayout = new QHBoxLayout( 0, 0, 0, "toolBoxLayout" );
  m_toolBox = new K3bToolBox( mainWidget() );
  toolBoxLayout->addWidget( m_toolBox );
  QSpacerItem* spacer = new QSpacerItem( 10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum );
  toolBoxLayout->addItem( spacer );
  m_labelLength = new QLabel( mainWidget() );
  m_labelLength->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );
  toolBoxLayout->addWidget( m_labelLength );


  // the title view
  // ----------------------------------------------------------------------------------
  m_titleView = new K3bVideoDVDRippingTitleListView( mainWidget() );

//   connect( m_titleView, SIGNAL(contextMenu(KListView*, QListViewItem*, const QPoint&)),
// 	   this, SLOT(slotContextMenu(KListView*, QListViewItem*, const QPoint&)) );

  // general layout
  // ----------------------------------------------------------------------------------
  mainGrid->addLayout( toolBoxLayout, 0, 0 );
  mainGrid->addWidget( m_titleView, 1, 0 );


  // init actions
  // ----------------------------------------------------------------------------------
  KActionCollection* actionCollection = new KActionCollection( this );
  KAction* actionStartRip = new KAction( i18n("Start Ripping"), "gear", 0, this,
					 SLOT(slotStartRipping()), actionCollection, "start_rip" );
  actionStartRip->setToolTip( i18n("Open the Video DVD ripping dialog") );

  m_toolBox->addButton( actionStartRip );

  setLeftPixmap( K3bTheme::MEDIA_LEFT );
  setRightPixmap( K3bTheme::MEDIA_VIDEO );
}


K3bVideoDVDRippingView::~K3bVideoDVDRippingView()
{
}


void K3bVideoDVDRippingView::setMedium( const K3bMedium& medium )
{
  QApplication::setOverrideCursor( QCursor(Qt::WaitCursor) );

  if( m_dvd.open( medium.device() ) ) {
    setTitle( medium.beautifiedVolumeId() + " (" + i18n("Video DVD") + ")" );
    m_labelLength->setText( i18n("%n title", "%n titles", m_dvd.numTitles() ) );
    m_titleView->setVideoDVD( m_dvd );
    QApplication::restoreOverrideCursor();
  }
  else {
    QApplication::restoreOverrideCursor();
    KMessageBox::error( this, i18n("Unable to read Video DVD contents.") );
  }
}


void K3bVideoDVDRippingView::slotStartRipping()
{
  QValueList<int> titles;
  int i = 1;
  for( QListViewItemIterator it( m_titleView ); *it; ++it, ++i )
    if( static_cast<K3bCheckListViewItem*>( *it )->isChecked() )
      titles.append( i );

  K3bVideoDVDRippingDialog dlg( m_dvd, titles, this );
  dlg.exec();
}

#include "k3bvideodvdrippingview.moc"