/***************************************************************************
                          readerextractbeat.h  -  description
                             -------------------
    begin                : Tue Mar 18 2003
    copyright            : (C) 2003 by Tue & Ken Haste Andersen
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

#ifndef READEREXTRACTBEAT_H
#define READEREXTRACTBEAT_H

#include "readerextract.h"
#include "defs.h"
#include <qvaluelist.h>


const CSAMPLE threshold = 5.;

// krist06.wav
const CSAMPLE histMinBPM = 60.;
const CSAMPLE histMaxBPM = 160.;

//const CSAMPLE histMinBPM = 50.;
//const CSAMPLE histMaxBPM = 160.;


const int gaussWidth = 8; // Width of gauss/2

/**
  *@author Tue & Ken Haste Andersen
  */

class ReaderExtractBeat : public ReaderExtract
{
public: 
    ReaderExtractBeat(ReaderExtract *input, int frameSize, int frameStep, int _histSize);
    ~ReaderExtractBeat();
    void reset();
    void *getBasePtr();
    CSAMPLE *getBpmPtr();
    int getRate();
    int getChannels();
    int getBufferSize();
    void *processChunk(const int idx, const int start_idx, const int end_idx);
private:
    /** Buffer indicating if a beat has occoured or not. */
    bool *beatBuffer;
    /** Buffer holding bpm values */
    CSAMPLE *bpmBuffer;
    /** Sorted list of peak indexes in HFC */
    typedef QValueList<int> Tpeaks;
    Tpeaks peaks;
    /** Array containing indexes into peaks list. Each element in the array corresponds to the
      * start of a chunk in the peak list. If the index is -1 no peaks are stored in the list
      * for the given chunk */
    Tpeaks::iterator *peakIt;    
    /** Pointer to histogram */
    CSAMPLE *hist;
    /** Pointer to beat interval vector */
    CSAMPLE *beatIntVector;
    /** Size of histogram */
    int histSize;
    /** Histogram interval size, and min and max interval in seconds*/
    CSAMPLE histInterval, histMinInterval, histMaxInterval;
    int frameNo;
    int framePerChunk;
    /** Pointer to HFC array */
    CSAMPLE *hfc;
};

#endif
