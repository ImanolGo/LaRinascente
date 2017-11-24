/*
 *  StarsScene.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 24/11/17.
 *
 */


#include "StarsScene.h"
#include "AppManager.h"

StarsScene::StarsScene(): ofxScene("STARS")
{
    //Intentionally left empty
}

StarsScene::~StarsScene()
{
    //Intentionally left empty
}


void StarsScene::setup() {
    ofLogNotice(getName() + "::setup");
}



void StarsScene::update()
{
    //Empty
}

void StarsScene::draw()
{
    ofBackground(0,0,0);
    AppManager::getInstance().getStarsManager().draw();
}


void StarsScene::willFadeIn() {
    ofLogNotice("StarsScene::willFadeIn");
}

void StarsScene::willDraw() {
    ofLogNotice("StarsScene::willDraw");
}

void StarsScene::willFadeOut() {
    ofLogNotice("StarsScene::willFadeOut");
}

void StarsScene::willExit() {
}

