/***************************************************************************
                           trackcollection.h
                              -------------------
     begin                : 10/27/2008
     copyright            : (C) 2008 Albert Santoni
     email                : gamegod \a\t users.sf.net
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TRACKCOLLECTION_H
#define TRACKCOLLECTION_H

#include <QtSql>

class TrackInfoObject;
class BpmDetector;
class QSqlDatabase;

/**
   @author Albert Santoni
*/
class TrackCollection : public QObject
{
    Q_OBJECT
    public:
    TrackCollection();
    ~TrackCollection();
    /** Add a track to the database */
    void addTrack(TrackInfoObject *pTrack);
    void addTrack(QString location);
    /** Removes a track from the library track collection. */
    void removeTrack(QString location);

    /** Get a track from the database, identified by id. Returns 0 if the track was
      * not found */
    //TrackInfoObject *getTrack(int id);

    /** Get a track from the database, identified by pathname. Returns 0 if
      * the track was not found. If the track is not in the database, a TIO is
      * created and added to the database */
    TrackInfoObject* getTrack(QString location);
	int getSize();

 	void scanPath(QString path);
 	bool trackExistsInDatabase(QString file_location);
 
 	QList<TrackInfoObject*> dumpDB();
 	
 	QSqlDatabase getDatabase();
 
public slots:
 	bool checkForTables();
 	/** Saves a track's info back to the database */
 	void updateTrackInDatabase(TrackInfoObject*);
 
 	TrackInfoObject *getTrackFromDB(QSqlQuery &query);
 	
 	void slotCancelLibraryScan();
 
signals:
 	void startedLoading();
 	void progressLoading(QString path);
 	void finishedLoading();
 
private:
    BpmDetector* m_pBpmDetector;
    QSqlDatabase m_db;
    /** Flag to raise when library scan should be cancelled */
    int bCancelLibraryScan;
};

#endif
