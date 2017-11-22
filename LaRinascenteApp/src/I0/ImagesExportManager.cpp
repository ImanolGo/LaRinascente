/*
 *  ImagesExportManager.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */

#include "ImagesExportManager.h"
#include "AppManager.h"

const string ImagesExportManager::IMAGE_FOLDER_PATH = "recording/frames";

ImagesExportManager::ImagesExportManager(): Manager(), m_recording(false)
{
    //Intentionally left empty
}

ImagesExportManager::~ImagesExportManager()
{
   ofLogNotice() << "ImagesExportManager::destructor";
}


//--------------------------------------------------------------

void ImagesExportManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"ImagesExportManager::initialized" ;
    this->setupRecorder();
}

void ImagesExportManager::setupRecorder()
{
    string path = IMAGE_FOLDER_PATH;
    ofDirectory dir(path);
    if(!dir.exists()){
        dir.create(true);
    }
    
    m_recorder.setPrefix(ofToDataPath(IMAGE_FOLDER_PATH)); // this directory must already exist
    m_recorder.setFormat("jpg"); // png is really slow but high res, bmp is fast but big, jpg is just right
}

void ImagesExportManager::update()
{
    this->updateRecorder();
}

void ImagesExportManager::updateRecorder()
{
    if(m_recording){
        auto fbo = AppManager::getInstance().getLayoutManager().getFbo();
        ofPixels pixels;
        fbo.readToPixels(pixels);
        m_recorder.addFrame(pixels);
    }
}

void ImagesExportManager::onSetRecording(bool & value)
{
    m_recording = value;
    
    if(m_recording)
    {
        m_recorder.stopThread();
        m_recorder.startThread(false, true);
    }
    else{
         m_recorder.stopThread();
    }
}













