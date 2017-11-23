/*
 *  KeyboardManager.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */

#include "KeyboardManager.h"
#include "AppManager.h"


KeyboardManager::KeyboardManager(): Manager()
{
    //Intentionally left empty
}

KeyboardManager::~KeyboardManager()
{
   ofLogNotice() << "KeyboardManager::destructor";
}


//--------------------------------------------------------------

void KeyboardManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"KeyboardManager::initialized" ;
    this->addListeners();
}

void KeyboardManager::addListeners()
{
    ofRegisterKeyEvents(this); // this will enable the InteractiveVisual class to listen to the key events.
}

void KeyboardManager::keyPressed(ofKeyEventArgs &e)
{
    int key = e.key;
    
    //ofLogVerbose() <<"KeyboardManager::keyPressed-> " + ofToString(key);
    
  
    if(key == 'g' || key == 'G') {
        AppManager::getInstance().getGuiManager().toggleGui();
    }
    
    if(key == ' ') {
        //AppManager::getInstance().toggleDebugMode();
        //AppManager::getInstance().getLightSculptureManager().onToggleShowIds();
    }
    
    if(key == OF_KEY_RIGHT) {
        AppManager::getInstance().getStarsManager().increaseCurrentX();
    }
    
    if(key == OF_KEY_LEFT) {
        AppManager::getInstance().getStarsManager().decreaseCurrentX();
    }
    
    if(key == OF_KEY_UP) {
        AppManager::getInstance().getStarsManager().decreaseCurrentY();
    }
    
    if(key == OF_KEY_DOWN) {
        AppManager::getInstance().getStarsManager().increaseCurrentY();
    }
    
    if(key == 'p') {
       AppManager::getInstance().getGuiManager().onPreviousStar();
    }
    
    if(key == 'n') {
        AppManager::getInstance().getGuiManager().onNextStar();
    }
    
}

void KeyboardManager::keyReleased(ofKeyEventArgs &e)
{
    int key = e.key;
    
    //ofLogVerbose() <<"KeyboardManager::keyReleased-> " + ofToString(key);
    
}










