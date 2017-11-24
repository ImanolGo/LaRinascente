/*
 *  ExplosionVisual.h
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 24/11/17.
 *
 */


#pragma once

#include "ofMain.h"
#include "BasicVisual.h"
#include "ImageVisual.h"
#include "SettingsManager.h"


//========================== class ExplosionParticle ==============================
//============================================================================
/** \class ExplosionParticle ExplosionVisual.h
 *	\brief Explosion Particle
 */



class ExplosionParticle: public BasicVisual
{
    
public:
    
    
    //! Constructor
    ExplosionParticle(const ofPoint& pos);
    
    //! Destructor
    ~ExplosionParticle();
    
    //! Setup the Sonic boom particle
    void setup();
    
    //! Update the Sonic boom particle
    void update();
    
    //! Draw the Sonic boom particle
    void draw();
    
    bool isAlive() {return m_live;}

    
private:
    
    float m_initSize;            //Initial size of the particle
    float m_time;                //Time of living
    float m_lifeTime;            //Allowed lifetime
    float m_size;                ///Max size
    bool  m_live;                //Is particle live
    
    ImageVisual  m_image;
};


//========================== class ExplosionVisual ==============================
//============================================================================
/** \class ExplosionVisual ExplosionVisual.h
 *	\brief Class managing the sonic boom particles
 *	\details It creates and destroyes the sonic boom visuals
 */


class ExplosionVisual
 {
    
public:
    
    //! Constructor
    ExplosionVisual();
    
    //! Destructor
    ~ExplosionVisual();
     
    //! set up the Sonic boom visual
    void setup(int width, int height);
    
    //! Draw the Sonic boom visual
    void update();
     
    //! Draw the Sonic boom visual
    void draw();
     
     //! Clear the Sonic boom visual
    void clear();
     
    const ofFbo& getFbo() const {return m_fbo;}
     
    void addParticle(const ofPoint& pos);
     
    bool empty() {return m_particles.empty();}
     
private:
     
     void setupFbos(int width, int height);
     
     void setupShaders();
     
     void updateParticles();
     
     void drawParticles();
     
private:
     
     typedef vector< ofPtr<ExplosionParticle> > ParticlesVector;
     ParticlesVector  m_particles;
     
     ofFbo                  m_fbo;
     
     ofShader               m_shader;
     float                  m_frequency, m_amplitude, m_speed; //shader parameters
     
     double                 m_elapsedTime;
     double                 m_newParticleTime;

};



