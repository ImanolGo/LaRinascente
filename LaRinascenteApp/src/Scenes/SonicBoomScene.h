/*
 *  SonicBoomScene.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 21/03/16.
 *
 */

#pragma once


#include "ofxScene.h"
#include "ofxPostProcessing.h"
#include "SonicBoomVisual.h"

class SonicBoomScene : public ofxScene {

public:

    //Contructor
    SonicBoomScene();

    //Destructor
    ~SonicBoomScene();

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

    void setupFbos();

    void setupPostProcessing();

    void setupSonicBoom();

    void updateSonicBoom();

    void drawSonicBoom();


private:

    bool                    m_initialized;
    ofFbo                   m_fbo;
    ofxPostProcessing       m_postProcessing;
    SonicBoomVisual         m_sonicBoomVisual;

    ofRectangle             m_drawArea;

};
