/*
 *  LayoutManager.h
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */



#pragma once

#include "Manager.h"
#include "TextVisual.h"
#include "SvgVisual.h"
#include "ImageVisual.h"
#include "RectangleVisual.h"
#include "ofxMask.h"


//========================== class LayoutManager ==============================
//============================================================================
/** \class LayoutManager LayoutManager.h
 *	\brief Class managing the layout of the application
 *	\details It creates an places al the text and elements regarding the layout
 */


class LayoutManager: public Manager
{
    
public:
    
    static const int MARGIN;
    static const int FRAME_MARGIN;
    static const string LAYOUT_FONT;
    static const string LAYOUT_FONT_LIGHT;

    //! Constructor
    LayoutManager();

    //! Destructor
    ~LayoutManager();

    //! Set-up the layout
    void setup();
    
    //! Update the layout
    void update();
    
    //! Draw the layout
    void draw();
    
    void onFullScreenChange(bool value);
    
    void windowResized(int w, int h);
    
    const ofRectangle& getWindowRect() {return m_windowRect;}
    
    const ofFbo& getFbo(){return m_fbo;}
    
    const ofFbo& getPreviewFbo(){return m_previewFbo;}
    
    void setFrameText(string& text);


private:


    //! Create the text visuals
    void createTextVisuals();

    //! Create the svg visuals
    void createSvgVisuals();

    //! Create the image visuals
    void createImageVisuals();

    //! Create the background Image
    void createBackground();


    //! Add all visuals as overlays
    void addVisuals();
    
    void setupMask();
    
    void setupFbo();
    
    void updateFbos();
    
    void updateOutputFbo();
    
    void updatePreviewFbo();

    void drawOutput();
    
    void drawFbos();
    
    void drawOutputFbo();
    
    void drawPreviewFbo();

    void drawText();
    
    void drawRectangles();
    
    void resetWindowRects();
    
    void resetWindowFrames();
    
    void resetWindowTitles();
    
    void setupWindowFrames();
    
private:


    typedef  map<string, ofPtr<TextVisual> >      TextMap;            ///< defines a map of Text attached to an identifier
    typedef  map<string, ofPtr<SvgVisual>  >      SvgMap;             ///< defines a map of SvgVisual Map attached to an identifier
    typedef  map<string, ofPtr<ImageVisual>  >    ImageMap;           ///< defines a map of ImageVisual Map attached to an identifier
  
    TextMap             m_textVisuals;             ///< map storing the text visuals attached to a name
    SvgMap              m_svgVisuals;              ///< map storing the svg visuals attached to a name
    ImageMap            m_imageVisuals;            ///< map storing the image visuals attached to a name
    
    ofRectangle         m_windowRect;
    RectangleVisual     m_windowFrame;
    RectangleVisual     m_previewWindowFrame;
    ofRectangle         m_previewWindowRect;
    RectangleVisual     m_recordingFrame;

    ofFbo               m_fbo;
     ofFbo               m_previewFbo;
    ofColor             m_color;
    
    ofxMask             m_mask;

};

//==========================================================================


