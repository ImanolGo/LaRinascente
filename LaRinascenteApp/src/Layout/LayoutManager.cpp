/*
 *  LayoutManager.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */



#include "ofMain.h"

#include "AppManager.h"
#include "SettingsManager.h"
#include "ViewManager.h"


#include "LayoutManager.h"

const int LayoutManager::MARGIN = 20;
const int LayoutManager::FRAME_MARGIN = 2;

const string LayoutManager::LAYOUT_FONT =  "fonts/open-sans/OpenSans-Semibold.ttf";
const string LayoutManager::LAYOUT_FONT_LIGHT =  "fonts/open-sans/OpenSans-Light.ttf";

LayoutManager::LayoutManager(): Manager()
{
	//Intentionally left empty
}


LayoutManager::~LayoutManager()
{
    ofLogNotice() <<"LayoutManager::Destructor";
}


void LayoutManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"LayoutManager::initialized";

	Manager::setup();

    //ofEnableArbTex();
    
    this->createTextVisuals();
    this->createSvgVisuals();
    this->createImageVisuals();
    
    this->setupFbo();
    this->setupMask();
    this->setupWindowFrames();

    //this->addVisuals();
   // ofDisableArbTex();
}


void LayoutManager::setupFbo()
{
    int margin = MARGIN;
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    
    m_fbo.allocate(width, height, GL_RGB);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void LayoutManager::setupMask()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_mask.allocate(width, height, ofxMask::ALPHA);
    
    
    auto image = AppManager::getInstance().getResourceManager().getTexture("FACADE");
    m_mask.beginMask();
    
    m_mask.beginMask();
        image->draw(0,0,width,height);
    m_mask.endMask();
    
    
}

void LayoutManager::resetWindowRects()
{
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    float ratio = width/ height;
    float frame_width = ofGetWidth() - AppManager::getInstance().getGuiManager().getWidth() - 2*MARGIN;
    
    
    m_windowRect.width = frame_width- 4*MARGIN;
    m_windowRect.height =  m_windowRect.width / ratio;
    
    if(m_windowRect.height >= (ofGetHeight() - 4*MARGIN))
    {
         m_windowRect.height =  ofGetHeight() - 4*MARGIN;
         m_windowRect.width =  m_windowRect.height * ratio;
    }
    
    m_windowRect.x = AppManager::getInstance().getGuiManager().getWidth() + MARGIN +(ofGetWidth() -  AppManager::getInstance().getGuiManager().getWidth())*0.5 - m_windowRect.width*0.5;
    m_windowRect.y = ofGetHeight()*0.5 - m_windowRect.height*0.5;
    
}


void LayoutManager::setupWindowFrames()
{
    this->resetWindowRects();
    this->resetWindowFrames();
    
    float width = ofGetScreenWidth();
    float height = ofGetScreenHeight()/80;

    ofColor color = AppManager::getInstance().getSettingsManager().getColor("FrameRectangle");
    m_windowFrame.setColor(color);
}

void LayoutManager::resetWindowFrames()
{
    m_windowFrame.setPosition(ofPoint( m_windowRect.x - FRAME_MARGIN, m_windowRect.y - FRAME_MARGIN, 0));
    m_windowFrame.setWidth(m_windowRect.width + 2*FRAME_MARGIN); m_windowFrame.setHeight(m_windowRect.height + 2*FRAME_MARGIN);
}


void LayoutManager::update()
{
    this->updateFbos();
}


void LayoutManager::updateFbos()
{
    auto image = AppManager::getInstance().getResourceManager().getTexture("FACADE");
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    ofEnableAlphaBlending();
    m_fbo.begin();
        ofClear(0, 0, 0);
        m_mask.begin();
            AppManager::getInstance().getStarsManager().draw();
        m_mask.end();
    
        //m_mask.drawMasker();
        //m_mask.drawMaskee();
    
        AppManager::getInstance().getStarsManager().draw();
        image->draw(0,0,width,height);
    
    m_fbo.end();
    ofDisableAlphaBlending();
}


void LayoutManager::createTextVisuals()
{
    float size = 20;
    float w = size*50;
    float h = size;
    float x =  m_windowRect.x + m_windowRect.getWidth()*0.5;
    float y =  m_windowRect.y - h -MARGIN;
    ofPoint pos = ofPoint(x, y);
    string text = "Preview";
    string fontName = LAYOUT_FONT_LIGHT;
    
    auto textVisual = ofPtr<TextVisual>(new TextVisual(pos,w,h,true));
    textVisual->setText(text, fontName, size, ofColor::white);
    m_textVisuals[text] = textVisual;
    
}


void LayoutManager::resetWindowTitles()
{
    float x =  m_windowRect.x + m_windowRect.getWidth()*0.5;
    float y =  m_windowRect.y -  m_textVisuals["Preview"]->getHeight()*0.2;
    ofPoint pos = ofPoint(x, y);
    m_textVisuals["Preview"]->setPosition(pos);
    
}


void LayoutManager::createSvgVisuals()
{
    ///To implement in case we have text visuals
}


void LayoutManager::createImageVisuals()
{
    //this->createBackground();
}

void LayoutManager::createBackground()
{
}

void LayoutManager::addVisuals()
{
    int depthLevel = -1;
    for(SvgMap::iterator it = m_svgVisuals.begin(); it!= m_svgVisuals.end(); ++it){
        AppManager::getInstance().getViewManager().addOverlay(it->second,depthLevel);
    }
    
    for(TextMap::iterator it = m_textVisuals.begin(); it!= m_textVisuals.end(); ++it){
        AppManager::getInstance().getViewManager().addOverlay(it->second,depthLevel);
    }
    
    for(ImageMap::iterator it = m_imageVisuals.begin(); it!= m_imageVisuals.end(); ++it){
        AppManager::getInstance().getViewManager().addOverlay(it->second,depthLevel);
    }
}

void LayoutManager::onFullScreenChange(bool value)
{
    if(value){
        ofSetWindowShape(ofGetScreenWidth(),ofGetScreenHeight());
    }
    else{
        
        float width = 4*MARGIN + 2*AppManager::getInstance().getGuiManager().getWidth();
        float height = AppManager::getInstance().getGuiManager().getHeight() + 2*MARGIN;
        ofSetWindowShape(width,height);
    }
}


void LayoutManager::draw()
{
    if(!m_initialized)
        return;
    
    this->drawFbos();
    this->drawText();
}

void LayoutManager::drawText()
{
    for(auto textVisual: m_textVisuals){
        textVisual.second->draw();
    }
}

void LayoutManager::drawFbos()
{
    m_windowFrame.draw();
    m_fbo.draw(m_windowRect.x,m_windowRect.y,m_windowRect.width,m_windowRect.height);
}

void LayoutManager::windowResized(int w, int h)
{
    if(!m_initialized){
        return;
    }
    
    this->resetWindowRects();
    this->resetWindowFrames();
    this->resetWindowTitles();
}





