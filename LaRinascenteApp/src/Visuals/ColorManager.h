/*
 *  ColorManager.h
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 24/11/17.
 *
 */

#pragma once

#include "Manager.h"

//========================== class ColorManager ==============================
//============================================================================
/** \class ColorManager ColorManager.h
 *	\brief Class managing the colors of all sets
 *	\details It loads and manages the color palette at any moment
 */

class ColorManager: public Manager
{
public:

    //! Constructor
    ColorManager();

    //! Destructor
    ~ColorManager();

    //! Set-up the color manager
    void setup();
    
    //! draw the color manager
    void draw();
    
    //! Changes the color palette according to a name
    bool changeColorPalette(string paletteName);
    
    //! Changes the color palette according to an index
    bool changeColorPalette(int paletteIndex);
    
    const vector< string >& getPaletteNames() const  {return m_paletteNames;}
    
    shared_ptr<ofColor> getColor(int colorIndex);
    
    int getNumberOfColors() const;
    
    int getMaxNumberOfColors() {return m_maxNumberColors;}
    
    //! Returns the index a color palette given a name. It returns -1 if it doesn't find any
    int getIndex(const string& colorPaletteName);
    
    const ofColor& getCurrentColor() const {return m_currentColor;}
    
    ofColor getRandomColor();

private:

    void setupColors();
    
    //! Loads the settings file
    bool loadSettingsFile();
    
    //! Loads all the color palettes
    void loadColorPalettes();
    
    void initializeColorIndexList();
    
    //! Sets a new animation type to be active
    void onSetSelectedTypes(const vector<int>& selected);


private:

    typedef  vector< shared_ptr<ofColor> > ColorPalette;  ///< defines a vector of ofColors

    typedef  map<string, ColorPalette >            PaletteMap;   ///< defines a map of color palettes attached to an identifier
    typedef  vector< string > PaleteNames;          ///< defines a vector of palette names
    typedef  vector<int>      ColorTypes;           ///< defines a vector of color types 
  
    PaletteMap          m_colorPalettes;             ///< map storing the color palettes attached to a name
    
    PaleteNames             m_paletteNames;
    string                  m_currentPaletteName;
    shared_ptr<ofColor>     m_blackColor;
    ColorTypes              m_colorTypes;
    int                     m_maxNumberColors;
    vector< int >           m_colorIndexList;
    
    ofColor             m_currentColor;

    ofXml		        m_xml;          ///< instance of the xml parser

};

//==========================================================================


