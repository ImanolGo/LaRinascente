/*
 *  StarsScene.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 24/11/17.
 *
 */


#include "StarsScene.h"
#include "AppManager.h"

StarsScene::StarsScene(): ofxScene("STARS"), m_elapsedTime(0)
{
    //Intentionally left empty
}

StarsScene::~StarsScene()
{
    //Intentionally left empty
}


void StarsScene::setup() {
    ofLogNotice(getName() + "::setup");
    this->setupExplosions();
}


void StarsScene::setupExplosions()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_explosionsVisual.setup(width, height);
}

void StarsScene::update()
{
    this->updateExplosions();
}


void StarsScene::updateExplosions()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    auto stars = AppManager::getInstance().getStarsManager().getStars();
    auto star = stars[ofRandom(stars.size())];
    
    auto interval = AppManager::getInstance().getStarsManager().getExplosionsInterval();
    auto time = AppManager::getInstance().getStarsManager().getExplosionsTime();
    m_elapsedTime+=ofGetLastFrameTime();
    if(m_elapsedTime >=interval){
        m_elapsedTime = 0.0;
        ofPoint pos = ofPoint(star->getPosition().x*width, star->getPosition().y*height);
        m_explosionsVisual.addParticle(pos, time);
    }
    
    m_explosionsVisual.update();
}

void StarsScene::draw()
{
    ofBackground(0,0,0);
    AppManager::getInstance().getStarsManager().draw();
    
    ofClear(0, 0, 0);
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
        AppManager::getInstance().getStarsManager().draw();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
        m_explosionsVisual.draw();
    
    ofPopStyle();
    
}


void StarsScene::willFadeIn() {
    ofLogNotice("StarsScene::willFadeIn");
   // AppManager::getInstance().getGuiManager().onColorModeChange("WARM");
}

void StarsScene::willDraw() {
    ofLogNotice("StarsScene::willDraw");
}

void StarsScene::willFadeOut() {
    ofLogNotice("StarsScene::willFadeOut");
}

void StarsScene::willExit() {
}

