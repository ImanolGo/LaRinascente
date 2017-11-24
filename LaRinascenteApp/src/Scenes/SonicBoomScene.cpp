/*
 *  SonicBoomScene.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 21/03/16.
 *
 */


#include "AppManager.h"
#include "ContourManager.h"

#include "SonicBoomScene.h"


SonicBoomScene::SonicBoomScene():m_initialized(false)
{

}

SonicBoomScene::~SonicBoomScene()
{
    //Intentionally left empty
}

void SonicBoomScene::setup()
{
    if (m_initialized) {
        return;
    }

    this->setupFbos();

    //this->setupPostProcessing();

    m_initialized = true;

    ofLogNotice("SonicBoomScene::setup");

}

void SonicBoomScene::setupFbos()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);

    m_drawArea = ofRectangle(0, 0, windowsSettings.width, windowsSettings.height);

    m_fbo.allocate(windowsSettings.width, windowsSettings.height);
    m_fbo.begin(); ofClear(0); m_fbo.end();

    m_sonicBoomVisual.setup(windowsSettings.width, windowsSettings.height);
}



void SonicBoomScene::setupPostProcessing()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);

    // Setup post-processing chain
    m_postProcessing.init(windowsSettings.width, windowsSettings.height);
    //m_postProcessing.createPass<FxaaPass>()->setEnabled(true);
    //m_postProcessing.createPass<BloomPass>()->setEnabled(true);

    //ofPtr<ZoomBlurPass> zoomBlurPass =  m_postProcessing.createPass<ZoomBlurPass>();
    //zoomBlurPass->setDensity(0.5);
    //zoomBlurPass->setEnabled(true);

    ofPtr<NoiseWarpPass> noisePass =  m_postProcessing.createPass<NoiseWarpPass>();
    noisePass->setAmplitude(0.01);
    noisePass->setSpeed(0.3);
    noisePass->setFrequency(5);
    noisePass->setEnabled(true);


    //m_postProcessing.createPass<ZoomBlurPass>()->setEnabled(true);
    //m_postProcessing.createPass<NoiseWarpPass>()->setEnabled(true);
}

void SonicBoomScene::update()
{
    this->updateSonicBoom();
}



void SonicBoomScene::updateSonicBoom()
{
    auto windowsSettings = AppManager::getInstance().getSceneManager().getWindowSettings(this);
    ofPoint pos = ofPoint(ofRandom(windowsSettings.width), ofRandom(windowsSettings.height));
    m_sonicBoomVisual.addParticle(pos);
    m_sonicBoomVisual.update();
}

void SonicBoomScene::draw() {

    //ofLogNotice("SonicBoomScene::draw");

    ofClear(0, 0, 0);
    ofPushStyle();
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);

        this->drawSonicBoom();

        ofEnableBlendMode(OF_BLENDMODE_ADD);

    ofPopStyle();

}


void SonicBoomScene::drawSonicBoom()
{
    if (m_sonicBoomVisual.empty()) {
        return;
    }

     m_sonicBoomVisual.draw();
    
//    m_postProcessing.begin();
//    ofPushMatrix();
//        ofScale(1, -1);
//        ofTranslate(0, -m_fbo.getHeight());
//        m_sonicBoomVisual.draw();
//    ofPopMatrix();
//    m_postProcessing.end();
}




void SonicBoomScene::willFadeIn() {
    ofLogNotice("SonicBoomScene::willFadeIn");
    
    AppManager::getInstance().getGuiManager().setHandsOn(true);
    m_sonicBoomVisual.clear();

}

void SonicBoomScene::willDraw() {
    ofLogNotice("SonicBoomScene::willDraw");
}

void SonicBoomScene::willFadeOut() {
    AppManager::getInstance().getGuiManager().setHandsOn(false);
    ofLogNotice("SonicBoomScene::willFadeOut");
}

void SonicBoomScene::willExit() {
    ofLogNotice("SonicBoomScene::willExit");

    m_sonicBoomVisual.clear();
}
