/*
 *
 * Copyright (C) 2003-2008 Sebastian Trueg <trueg@k3b.org>
 * Copyright (C) 2011 Michal Malek <michalm@jabster.pl>
 *
 * This file is part of the K3b project.
 * Copyright (C) 1998-2008 Sebastian Trueg <trueg@k3b.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file "COPYING" for the exact licensing terms.
 */


#ifndef K3B_AUDIO_RIP_THREAD_H
#define K3B_AUDIO_RIP_THREAD_H

#include "k3bmassaudioencodingjob.h"
#include <QtCore/QScopedPointer>


namespace K3b {

    namespace Device {
        class Device;
    }

    class AudioRipJob : public MassAudioEncodingJob
    {
        Q_OBJECT
        
    public:
        AudioRipJob( JobHandler* hdl, QObject* parent );
        ~AudioRipJob();

        // paranoia settings
        void setParanoiaMode( int mode );
        void setMaxRetries( int retries );
        void setNeverSkip( bool b );
        void setUseIndex0( bool b );

        void setDevice( Device::Device* device );

        virtual QString jobDescription() const;
        virtual QString jobSource() const;

        class Private;

    public Q_SLOTS:
        virtual void start();

    private:
        virtual void jobFinished( bool );

        virtual bool init();

        virtual void cleanup();

        virtual Msf trackLength( int trackIndex ) const;

        virtual QIODevice* createReader( int trackIndex ) const;

        virtual void trackStarted( int trackIndex );

        virtual void trackFinished( int trackIndex, const QString& filename );

    private:
        QScopedPointer<Private> d;
    };

} // namespace K3b

#endif
