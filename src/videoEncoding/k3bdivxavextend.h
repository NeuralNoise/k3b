/***************************************************************************
                          k3bdvdavextend.h  -  description
                             -------------------
    begin                : Mon Apr 1 2002
    copyright            : (C) 2002 by Sebastian Trueg
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

#ifndef K3BDVDAVEXTEND_H
#define K3BDVDAVEXTEND_H

#include <qgroupbox.h>

class QWidget;
class QCheckBox;
class QSlider;
class QLabel;
class KRestrictedLine;
class KComboBox;
class K3bDivxCodecData;

/**
  *@author Sebastian Trueg
  */

class K3bDivxAVExtend : public QGroupBox  {
   Q_OBJECT
public: 
    K3bDivxAVExtend( K3bDivxCodecData *data, QWidget *parent=0, const char *name=0);
    ~K3bDivxAVExtend();
    void updateView();
    void init();
private:
    QCheckBox *m_checkResample;
    KRestrictedLine *m_editKeyframes;
    QCheckBox *m_checkYuv;
    KComboBox *m_comboDeinterlace;
    KComboBox *m_comboLanguage;
    QSlider *m_sliderCrispness;
    QLabel *m_labelCrispness;
    //KRestrictedLine *m_editAudioGain;
    K3bDivxCodecData *m_data;

    void setupGui();
private slots:
    void slotKeyframes( const QString& );
    void slotAudioGain( const QString& );
    void slotCrispness( int );
    void slotResample( int );
    void slotYuv( int );
    void slotDeinterlace( int );
    void slotAudioLanguage( int );
};

#endif
