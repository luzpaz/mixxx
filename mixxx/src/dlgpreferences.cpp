/***************************************************************************
                          dlgpreferences.cpp  -  description
                             -------------------
    begin                : Sun Jun 30 2002
    copyright            : (C) 2002 by Tue & Ken Haste Andersen
    email                : haste@diku.dk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dlgprefrecord.h"
#include "dlgpreferences.h"
#include "dlgprefsound.h"
#include "dlgprefmidi.h"
#include "dlgprefplaylist.h"
#include "dlgprefcontrols.h"
#include "dlgprefmixer.h"
#include "dlgprefbpm.h"
#include "mixxx.h"
#include "track.h"
#include "wtreeview.h"

DlgPreferences::DlgPreferences(MixxxApp *mixxx, MixxxView *view,
                               PlayerProxy *player,
                               Track *, ConfigObject<ConfigValue> *_config) : QTabDialog(mixxx, "")
{
    m_pMixxx = mixxx;

    setCaption("Preferences");
    config = _config;

    // Construct widgets for use in tabs
    wsound = new DlgPrefSound(this, player, config);
    wmidi  = new DlgPrefMidi(this, config);
    wplaylist = new DlgPrefPlaylist(this, config);
    wcontrols = new DlgPrefControls(this, view, mixxx, config);
    wmixer = new DlgPrefMixer(this, config);

#ifdef __EXPERIMENTAL_BPM__
    wbpm = new DlgPrefBPM(this, config);
#endif

#ifdef __EXPERIMENTAL_RECORDING__
    wrecord = new DlgPrefRecord(this, config);
#endif

    // Add tabs
    addTab(wsound,    "Sound output");
    addTab(wmidi,     "Input controllers");
    addTab(wcontrols, "GUI");
    addTab(wplaylist, "Playlists");
    addTab(wmixer,    "Mixer Profile");

#ifdef __EXPERIMENTAL_BPM__
    addTab(wbpm, "BPM");
#endif

#ifdef __EXPERIMENTAL_RECORDING__
    addTab(wrecord,   "Recording");
#endif

    // Add closebutton
    setOkButton("Close");

    // Set size
    resize(QSize(380,520));

    // Install event handler to generate closeDlg signal
    installEventFilter(this);

    // Connections
    connect(this,        SIGNAL(aboutToShow()),          this,      SLOT(slotUpdate()));
    connect(this,        SIGNAL(aboutToShow()),          wsound,    SLOT(slotUpdate()));
    connect(this,        SIGNAL(aboutToShow()),          wmidi,     SLOT(slotUpdate()));
    connect(this,        SIGNAL(aboutToShow()),          wplaylist, SLOT(slotUpdate()));
    connect(this,        SIGNAL(aboutToShow()),          wcontrols, SLOT(slotUpdate()));
    connect(this,	     SIGNAL(aboutToShow()),		     wmixer,    SLOT(slotUpdate()));

#ifdef __EXPERIMENTAL_BPM__
    connect(this,        SIGNAL(aboutToShow()),           wbpm,      SLOT(slotUpdate()));
#endif

#ifdef __EXPERIMENTAL_RECORDING__
    connect(this,	     SIGNAL(aboutToShow()),		     wrecord,   SLOT(slotUpdate()));
#endif
//    connect(this,        SIGNAL(closeDlg()),             wsound,    SLOT(slotApply()));
    connect(this,        SIGNAL(closeDlg()),             wmidi,     SLOT(slotApply()));
    connect(this,        SIGNAL(closeDlg()),             wplaylist, SLOT(slotApply()));
    connect(this,        SIGNAL(closeDlg()),             wcontrols, SLOT(slotApply()));
#ifdef __EXPERIMENTAL_BPM__
    connect(this,        SIGNAL(closeDlg()),             wbpm,      SLOT(slotApply()));
#endif
    connect(this,        SIGNAL(closeDlg()),             this,      SLOT(slotApply()));
    connect(this,	     SIGNAL(closeDlg()),		     wmixer,    SLOT(slotApply()));
#ifdef __EXPERIMENTAL_RECORDING__
   connect(this,	 SIGNAL(closeDlg()),		 wrecord,   SLOT(slotApply()));
#endif
//    if (tracklist->wTree)
//        connect(wplaylist,   SIGNAL(apply(QString,QString)),         tracklist->wTree, SLOT(slotSetDirs(QString,QString)));
    if (view->m_pTreeView)
        connect(wplaylist,   SIGNAL(apply(const QString &)), view->m_pTreeView, SLOT(slotUpdateDir(const QString &)));
}

DlgPreferences::~DlgPreferences()
{
}

bool DlgPreferences::eventFilter(QObject *o, QEvent *e)
{
    // Send a close signal if dialog is closing
    if (e->type() == QEvent::Hide)
        emit(closeDlg());

    // Standard event processing
    return QWidget::eventFilter(o,e);
}

void DlgPreferences::slotUpdate()
{
//    m_pMixxx->releaseKeyboard();
}

void DlgPreferences::slotApply()
{
//    m_pMixxx->grabKeyboard();
}

