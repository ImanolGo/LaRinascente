/*
 *  Star.h
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */


#pragma once

#include "ofMain.h"
#include "BasicVisual.h"
#include "TextVisual.h"
#include "ImageVisual.h"


class Star: public BasicVisual {
    
    static const int SIZE;
    
public:
    
    Star(const ofPoint& position, int id);
    
    virtual ~Star();
    
    void draw();
    
    void draw(int width, int height);
    
    int getId() const {return m_id;}
    
    void normalize(const ofRectangle& boundingBox);
    
    void setPixelColor(ofPixels& pixels);
    
    void showId(bool _showId) {m_showId = _showId;}
    
private:
    
    void setup();
    
    void setupImages();
    
    void setupText();
    
private:
    
    int m_id;
    ofPtr<TextVisual>   m_idText;
    ofPtr<ImageVisual>  m_image;
    bool        m_showId;
};




