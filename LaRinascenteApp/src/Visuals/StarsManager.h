/*
 *  StarsManager.h
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */


#pragma once

#include "Manager.h"
#include "Star.h"


//========================== class StarsManager ==============================
//============================================================================
/** \class StarsManager StarsManager.h
 *	\brief Class managing the Stars
 *	\details It controls the postion and color of the Stars
 */


class StarsManager: public Manager
{

    static const string STARS_LIST_PATH;
    
    public:
    
        typedef vector<int> IntVector;
        typedef vector< ofPtr<Star> > StarVector;
    
    public:

        //! Constructor
        StarsManager();

        //! Destructor
        ~StarsManager();

        //! Setup the Halo Manager
        void setup();

        //! Update the Star Manager
        void update();
    
        //! Draw the Star Manager
        void draw();
    
        //! Draw the Star Manager according to a certain width or height
        void draw(int width, int height);
    
        const StarVector& getStars() const {return m_stars;}
    
        void setPixels(ofPixels& pixels);
    
        void setStarColors(ofPixels& pixels);
    
        int getNumberStars() const {return m_stars.size();}
    
        void addStar(const ofPoint&  position);
    
        void deleteLastStar();
    
        void onSetStarsSize(float &value);
    
        void onSetExplosionsInterval(float &value);
    
        float getExplosionsInterval() const {return m_explosionInterval;}
    
        void showChannels(bool _showChannels);
    
        void onSetStarPosition(int& value);
    
        void increaseCurrentX();
    
        void increaseCurrentY();
    
        void decreaseCurrentX();
    
        void decreaseCurrentY();
    
    private:

        void setupStars();
    
        void readStarsPositions();
    
        void saveStarsPositions();
        
        bool parseStarLine(string& line, ofPoint& position);
    
        void removeCharsFromString( string &str, char* charsToRemove );
    
        void createStar(const ofPoint& position);
    
        void drawStars(int width = 1, int height = 1);
    
    
    
    private:
    
        StarVector      m_stars;
        ofRectangle     m_boundingBox;
        int             m_currentStarInde;
    
        float           m_starsSize;
        float           m_explosionInterval;
    
};



