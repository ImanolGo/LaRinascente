/*
 *  SceneManager.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 24/11/17.
 *
 */

#include "ofMain.h"


#include "SceneManager.h"
#include "scenes.h"


#include "AppManager.h"

SceneManager::SceneManager(): Manager()
{
	//Intentionally left empty
}


SceneManager::~SceneManager()
{
    ofLogNotice() <<"SceneManager::Destructor";
}


void SceneManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();

    this->createScenes();
    this->setupFbo();

    ofLogNotice() <<"SceneManager::initialized";

}


void SceneManager::createScenes()
{
    m_mySceneManager.setTransitionDissolve();
    
    ofPtr<ofxScene> scene;

    //Create Stars Scene
    scene = ofPtr<ofxScene> (new StarsScene());
    m_mySceneManager.addScene(scene);
    
    //Create Blank Scene
    scene = ofPtr<ofxScene> (new BlankScene());
    m_mySceneManager.addScene(scene);
    
   
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();

    m_mySceneManager.run(width, height);
    this->onTransitionTimeChange(2.0);
}


void SceneManager::setupFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    //float width = ofGetWidth();
    //float height = ofGetHeight();

    m_fbo.allocate(width, height, GL_RGBA);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void SceneManager::update()
{
    this->updateScenes();
    
    m_fbo.begin();
        ofClear(0);
        ofPushStyle();
        ofSetColor(255);
        ofEnableAlphaBlending();
        m_mySceneManager.draw();
        ofDisableAlphaBlending();
        ofPopStyle();
    m_fbo.end();
}

void SceneManager::updateScenes()
{
    m_mySceneManager.update();
}


void SceneManager::draw()
{
    m_fbo.draw(0,0);
}

void SceneManager::draw(const ofRectangle& rect)
{
    m_fbo.draw(rect.x,rect.y,rect.width,rect.height);
}


void SceneManager::changeScene(string sceneName)
{
    m_mySceneManager.changeScene(sceneName);
}

void SceneManager::changeScene(int sceneIndex)
{
     m_mySceneManager.changeScene(sceneIndex);
}


void SceneManager::onTransitionTimeChange(float value)
{
   m_mySceneManager.setSceneDuration(value,value);
}

string SceneManager::getSceneName(int sceneIndex)
{
    string name = "";
    if(sceneIndex < 0 || sceneIndex >= m_mySceneManager.scenes.size()){
        return name;
    }
    
    return m_mySceneManager.scenes[sceneIndex]->getName();
   
}

int SceneManager::getIndex(const string& sceneName)
{
    for(int i = 0; i< m_mySceneManager.scenes.size(); i++){
        if(m_mySceneManager.scenes[i]->getName() == sceneName){
            return i;
        }
    }
    
    return -1;
}



