/* 
 *
 * $Id$
 * Copyright (C) 2004 Sebastian Trueg <trueg@k3b.org>
 *
 * This file is part of the K3b project.
 * Copyright (C) 1998-2004 Sebastian Trueg <trueg@k3b.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file "COPYING" for the exact licensing terms.
 */

#include "k3baudiodatasourceviewitem.h"
#include "k3baudiodatasource.h"
#include "k3baudiotrackviewitem.h"
#include "k3baudiozerodata.h"

#include <k3bmsf.h>

#include <kiconloader.h>


K3bAudioDataSourceViewItem::K3bAudioDataSourceViewItem( K3bAudioTrackViewItem* parent, 
							K3bAudioDataSourceViewItem* after, 
							K3bAudioDataSource* source )
  : K3bListViewItem( parent, after ),
    m_trackViewItem( parent ),
    m_source( source ),
    m_animationCounter(1)
{
  // italic type
  QFont f(listView()->font());
  f.setItalic( true );
  setFont( 3, f );

  // greyed out filename
  setForegroundColor( 5, listView()->palette().disabled().foreground() );

  // for zero items we make the length editable
  if( dynamic_cast<K3bAudioZeroData*>( source ) )
    setEditor( 4, MSF );
}


QString K3bAudioDataSourceViewItem::text( int i ) const
{
  switch( i ) {
  case 3:
    return " " + m_source->type() + " ";
  case 4:
    return m_source->length().toString();
  case 5:
    return " " + m_source->sourceComment() + " ";
  default:
    return QString::null;
  }
}


void K3bAudioDataSourceViewItem::setText( int col, const QString& text )
{
  if( col == 4 ) {
    if( K3bAudioZeroData* zero = dynamic_cast<K3bAudioZeroData*>( source() ) ) {
      bool ok;
      K3b::Msf f = K3b::Msf::fromString( text, &ok );
      if( ok )
	zero->setLength( f );
    }
  }

  KListViewItem::setText( col, text );
}


bool K3bAudioDataSourceViewItem::animate()
{
  if( source()->length() == 0 && source()->isValid() ) {
    QString icon = QString( "kde%1" ).arg( m_animationCounter );
    setPixmap( 4, SmallIcon( icon ) );
    m_animationCounter++;
    if ( m_animationCounter > 6 )
      m_animationCounter = 1;
    return true;
  }
  else {
    // set status icon
    setPixmap( 4, ( source()->isValid() ? SmallIcon( "greenled" ) : SmallIcon( "redled" ) ) );
    return false;
  }
}
