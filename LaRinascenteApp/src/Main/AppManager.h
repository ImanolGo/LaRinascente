/*
 *  AppManager.h
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */




#pragma once

#include "ofMain.h"

#include "managers.h"

//========================== class AppManager ==============================
//============================================================================
/** \class AppManager AppManager.h
 *	\brief Class managing the whole application
 *	\details it set-ups, updates and renders all the different managers used for the application
 */

class AppManager: public Manager
{
public:

    //! Destructor
    ~AppManager();

    //! Returns the singleton instance.
    static AppManager& getInstance();

    //! Compares two transition objects
    void setup();

    //! updates the logic
    void update();

    //! calls the view manager to draw
    void draw();

    //==========================================================================

    //! Returns the settings manager
    SettingsManager& getSettingsManager() { return m_settingsManager; }
    
    //! Returns the layout manager
    LayoutManager& getLayoutManager() { return m_layoutManager; }
    
    //! Returns the resource manager
    ResourceManager& getResourceManager() { return m_resourceManager; }
    
    //! Returns the view manager
    ViewManager&  getViewManager() { return m_viewManager; }
    
    //! Returns the visual effects manager
    VisualEffectsManager&  getVisualEffectsManager() { return m_visualEffectsManager; }
    
    //! Returns the GUI manager
    GuiManager&   getGuiManager() { return m_guiManager; }
    
    //! Returns the noise manager
    NoiseManager&  getNoiseManager() { return m_noiseManager; }
    
    //! Returns the mask manager
    MaskManager&  getMaskManager() { return m_maskManager; }
    
    //! Returns the stars manager
    StarsManager&  getStarsManager() { return m_starsManager; }
    
    //! Returns the iamges export manager
    ImagesExportManager&  getImagesExportManager() { return m_imagesExportManager; }
    
    //! Returns the scene manager
    SceneManager&  getSceneManager() { return m_sceneManager; }
    

    //==========================================================================
    
    void toggleDebugMode();
    
    void setDebugMode(bool showDebug);
    

private:

     //! Constructor
     AppManager();

	//! Stop the compiler generating methods of copy the object
	 AppManager(AppManager const& copy);              // Don't Implement

    //! Prevent operator= being generated.
     AppManager& operator=(AppManager const& copy);     // Don't implement

    //==========================================================================

    //! Set-up all the managers
    void setupManagers();

    //! Set-up openFrameworks
    void setupOF();

    //! update all the managers
    void updateManagers();

private:


    SettingsManager          m_settingsManager;          ///< Manages the application's settings
    ResourceManager          m_resourceManager;          ///< Manages the application's resources
    ViewManager              m_viewManager;              ///< Manages visuals
    VisualEffectsManager     m_visualEffectsManager;     ///< Manages visual effects
    LayoutManager            m_layoutManager;            ///< Manages the layout
    KeyboardManager          m_keyboardManager;          ///< Manages the keyboard
    GuiManager               m_guiManager;               ///< Manages the graphical user interface
    NoiseManager             m_noiseManager;             ///< Manages the noise generator
    MaskManager              m_maskManager;              ///< Manages all the masks
    StarsManager             m_starsManager;             ///< Manages the stars manager
    ImagesExportManager      m_imagesExportManager;      ///< Manages the image exporter
    SceneManager             m_sceneManager;             ///< Manages the scenes
    
    
    
    bool                     m_debugMode;
    bool                     m_initialized;
};

//==========================================================================


