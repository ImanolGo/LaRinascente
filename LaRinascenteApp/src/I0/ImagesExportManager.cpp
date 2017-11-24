/*
 *  ImagesExportManager.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */

#include "ImagesExportManager.h"
#include "AppManager.h"

const string ImagesExportManager::IMAGE_FOLDER_PATH = "recording/frame_";

ImagesExportManager::ImagesExportManager(): Manager(), m_recording(false)
{
    //Intentionally left empty
}

ImagesExportManager::~ImagesExportManager()
{
   ofLogNotice() << "ImagesExportManager::destructor";
    m_recorder.waitForThread();
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
    
    m_recorder.setPrefix(ofToDataPath(IMAGE_FOLDER_PATH)); // this directory must already exist
    m_recorder.setFormat("jpg"); // png is really slow but high res, bmp is fast but big, jpg is just right
    
    m_recorder.startThread(false);
}

void ImagesExportManager::update()
{
    this->updateRecorder();
    this->updateText();
}

void ImagesExportManager::updateRecorder()
{
    if(m_recording){
        auto fbo = AppManager::getInstance().getLayoutManager().getFbo();
        ofPixels pixels;
        fbo.readToPixels(pixels);
        //ofLogNotice() <<"ImagesExportManager::updateRecorder -> pixels width =  " << pixels.getWidth();
        m_recorder.addFrame(pixels);
    }
}

void ImagesExportManager::updateText()
{
    string text = "Queue Size: " + ofToString(m_recorder.q.size());
    AppManager::getInstance().getLayoutManager().setFrameText(text);
}   

void ImagesExportManager::onSetRecording(bool value)
{
    m_recording = value;
}













