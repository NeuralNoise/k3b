/***************************************************************************
                          k3bdatajob.h  -  description
                             -------------------
    begin                : Tue May 15 2001
    copyright            : (C) 2001 by Sebastian Trueg
    email                : trueg@informatik.uni-freiburg.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef K3BDATAJOB_H
#define K3BDATAJOB_H

#include "../k3bjob.h"

#include <kprocess.h>
#include <qfile.h>

class K3bDataDoc;
class QString;
class QDataStream;
class K3bAbstractWriter;
class K3bIsoImager;


/**
  *@author Sebastian Trueg
  */

class K3bDataJob : public K3bBurnJob
{
  Q_OBJECT
	
 public:
  K3bDataJob( K3bDataDoc* );
  ~K3bDataJob();
	
  K3bDoc* doc() const;
  K3bDevice* writer() const;
		
 public slots:
  void cancel();
  void start();

 protected slots:
  void slotReceivedIsoImagerData( char* data, int len );
  void slotIsoImagerFinished( bool success );
  void slotDataWritten();
  void slotIsoImagerPercent(int);
  void slotSizeCalculationFinished( int, int );
  void slotWriterJobPercent( int p );
  void slotWriterJobFinished( bool success );
  void slotCollectOutput( KProcess*, char*, int );
  void fetchMultiSessionInfo();
  void slotMsInfoFetched();
  void writeImage();
  void startWriting();
  void prepareWriterJob();
  void cancelAll();
		
 private:
  K3bDataDoc* m_doc;
  KProcess* m_process;

  bool m_imageFinished;

  QString m_msInfo;
  QString m_collectedOutput;

  QFile m_imageFile;
  QDataStream m_imageFileStream;
  K3bAbstractWriter* m_writerJob;
  K3bIsoImager* m_isoImager;
};

#endif
