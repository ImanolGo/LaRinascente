/*
 *  ImagesExportManager.h
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */



#pragma once

#include "ofMain.h"
#include "Manager.h"
#include "ofxImageSequenceRecorder.h"

//========================== class ImagesExportManager =======================================
//==============================================================================
/** \class ImagesExportManager ImagesExportManager.h
 *	\brief class for managing the exporting of images
 *	\details It reads from the output buffer and exports every frame as an image
 */


class ImagesExportManager: public Manager
{
    
    static const string IMAGE_FOLDER_PATH;

public:
    //! Constructor
    ImagesExportManager();

    //! Destructor
    virtual ~ImagesExportManager();

    //! setups the export image manager
    void setup();

   //! setups the export image manager
    void update();
    
    void onSetRecording(bool value);
    
    bool isRecording() const {return m_recording;}
    
private:
    
    void setupRecorder();
    
    void updateRecorder();
    
    void updateText();

private:
    
    ofxImageSequenceRecorder m_recorder;
    bool                     m_recording;

};

