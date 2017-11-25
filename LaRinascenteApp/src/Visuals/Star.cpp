/*
 *  Star.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */

#include "Star.h"


const int Star::SIZE = 20;

Star::Star(const ofPoint& position, int id): BasicVisual(position, SIZE, SIZE), m_id(id), m_showId(false)
{
    this->setup();
}

Star::~Star()
{
    //Intentionaly left empty
}

void Star::setup()
{
    this->setupImages();
    this->setupText();
}


void Star::setupImages()
{
    ofVec3f position(0,0);
    string resourceName = "STAR";
    m_image = ofPtr<ImageVisual> (new ImageVisual(m_position,resourceName, true));
}

void Star::setupText()
{
    
    ofVec3f position(0,0);
    float fontSize = m_width;
    string text = ofToString(m_id);
    string fontName ="fonts/open-sans/OpenSans-Bold.ttf";
    ofColor textColor = ofColor::white;
    
    m_idText = ofPtr<TextVisual> (new TextVisual(position,2*m_width,m_height, true));
    m_idText->setText(text,fontName,fontSize,textColor);
    
}


void Star::draw()
{
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(m_position);
    ofScale(m_scale.x, m_scale.y);
    //ofTranslate(-m_width*0.5,-m_width*0.5);
    
    ofRotateX(m_rotation.x);
    ofRotateY(m_rotation.y);
    
    m_image->setWidth(this->getWidth(),true);
    m_image->draw();
    
    ofPopStyle();
    
    if(m_showId){
        m_idText->draw();
    }
    ofPopMatrix();
}

void Star::draw(int width, int height)
{
    
    ofPushMatrix();
    ofTranslate(m_position.x * width, m_position.y * height);
    this->draw();
    ofPopMatrix();
}

void Star::normalize(const ofRectangle& boundingBox)
{
    m_position.x = (m_position.x - boundingBox.getX()) / boundingBox.getWidth();
    m_position.y = (m_position.y - boundingBox.getY()) / boundingBox.getHeight();
}


void Star::setPixelColor(ofPixels& pixels)
{
    auto color = pixels.getColor(m_position.x * pixels.getWidth(), m_position.y * pixels.getHeight());
    //int brightness = ofMap(color.getBrightness(), 0, 255, 0, 255);
   // int brightness = color.getBrightness();
    int brightness = 100;
    //m_color = ofColor( 255, 194, 0);
    //m_color = ofColor::white;
    m_color.setBrightness(brightness);
    m_image->setColor(m_color);
    //m_color = ofColor(brightness);
}

