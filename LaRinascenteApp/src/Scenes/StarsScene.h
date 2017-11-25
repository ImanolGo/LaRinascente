/*
 *  StarsScene.h
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 24/11/17.
 *
 */

#pragma once

#include "ofxScene.h"
#include "ExplosionVisual.h"

class StarsScene : public ofxScene {
    
public:
    
    //! Constructor
    StarsScene();
    
    //! Destructor
    ~StarsScene();
    
    //! Set up the scene
    void setup();
    
    //! Update the scene
    void update();
    
    //! Draw the scene
    void draw();
    
    //! Called when fading in
    void willFadeIn();
    
    //! Called when to start drawing
    void willDraw();
    
    //! Called fading out
    void willFadeOut();
    
    //! Called when exit
    void willExit();
    
private:
    
    void setupExplosions();
    
    void updateExplosions();
    
    void drawExplosions();

private:
    
    ExplosionVisual         m_explosionsVisual;
    float                   m_elapsedTime;
    
};




