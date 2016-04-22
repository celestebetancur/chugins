//-----------------------------------------------------------------------------
// Entaro ChucK Developer!
// This is a Chugin boilerplate, generated by chugerate!
//-----------------------------------------------------------------------------

// this should align with the correct versions of these ChucK files
#include "chuck_dl.h"
#include "chuck_def.h"

// general includes
#include <stdio.h>
#include <limits.h>
#include <math.h>

// class definition for internal Chugin data
class PanN
{
public:
    // constructor
    PanN( t_CKFLOAT fs, t_CKUINT chans ) :
    m_chans(chans)
    {
        m_pan = 0.5;
        m_channel_map = new t_CKUINT[m_chans];
    }
    
    // for Chugins extending UGen
    void tick( SAMPLE * in, SAMPLE * out, int nframes )
    {
        int c_l = ((int)floorf(m_pan))%m_chans;
        int c_r = ((int)ceilf(m_pan))%m_chans;
        if(c_l == c_r) c_r = (c_l+1)%m_chans;
        float mod = m_pan - floorf(m_pan);
        
        float g_l = cosf(ONE_PI/2.0*mod);
        float g_r = sinf(ONE_PI/2.0*mod);
        
        memset(out, 0, sizeof(SAMPLE)*m_chans*nframes);
        
        for(int i = 0; i < nframes; i++)
        {
            out[i*m_chans+m_channel_map[c_l]] = g_l * in[i*m_chans];
            out[i*m_chans+m_channel_map[c_r]] = g_r * in[i*m_chans];
        }
    }
    
    // set parameter example
    float setPan( t_CKFLOAT p )
    {
        m_pan = p;
        
        // int c_l = ((int)floorf(m_pan))%m_chans;
        // int c_r = ((int)ceilf(m_pan))%m_chans;
        // float mod = m_pan - floorf(m_pan);
        // 
        // float g_l = cosf(ONE_PI/2.0*mod);
        // float g_r = sinf(ONE_PI/2.0*mod);
        // 
        // fprintf(stderr, "**** c_l, c_r: %i, %i; mod, g_l, g_r: %f, %f, %f ****\n", c_l, c_r, mod, g_l, g_r);
        
        return p;
    }
    
    // get parameter example
    float getPan() { return m_pan; }
    
protected:
    // instance data
    const t_CKUINT m_chans;
    t_CKFLOAT m_pan;
    t_CKUINT * m_channel_map;
};


// class definition for internal Chugin data
class Pan4 : public PanN
{
public:
    // constructor
    Pan4( t_CKFLOAT fs ) : PanN(fs, 4)
    {
        // default channel map: alternate left then right from front to back
        m_channel_map[0] = 0;
        m_channel_map[1] = 1;
        m_channel_map[2] = 3;
        m_channel_map[3] = 2;
    }
};


// class definition for internal Chugin data
class Pan8 : public PanN
{
public:
    // constructor
    Pan8( t_CKFLOAT fs ) : PanN(fs, 8)
    {
        // default channel map: alternate left then right from front to back
        m_channel_map[0] = 0;
        m_channel_map[1] = 1;
        m_channel_map[2] = 3;
        m_channel_map[3] = 5;
        m_channel_map[4] = 7;
        m_channel_map[5] = 6;
        m_channel_map[6] = 4;
        m_channel_map[7] = 2;
    }
};


// class definition for internal Chugin data
class Pan16 : public PanN
{
public:
    // constructor
    Pan16( t_CKFLOAT fs ) : PanN(fs, 16)
    {
        // default channel map: alternate left then right from front to back
        m_channel_map[0] = 0;
        m_channel_map[1] = 1;
        m_channel_map[2] = 3;
        m_channel_map[3] = 5;
        m_channel_map[4] = 7;
        m_channel_map[5] = 9;
        m_channel_map[6] = 11;
        m_channel_map[7] = 13;
        m_channel_map[8] = 15;
        m_channel_map[9] = 14;
        m_channel_map[10] = 12;
        m_channel_map[11] = 10;
        m_channel_map[12] = 8;
        m_channel_map[13] = 6;
        m_channel_map[14] = 4;
        m_channel_map[15] = 2;
    }
};


// declaration of chugin constructor
CK_DLL_CTOR(pan4_ctor);
// declaration of chugin desctructor
CK_DLL_DTOR(pan4_dtor);
// for Chugins extending UGen, this is mono synthesis function for 1 sample
CK_DLL_TICKF(pan4_tickf);
// example of getter/setter
CK_DLL_MFUN(pan4_setPan);
CK_DLL_MFUN(pan4_getPan);
// this is a special offset reserved for Chugin internal data
t_CKINT pan4_data_offset = 0;

// declaration of chugin constructor
CK_DLL_CTOR(pan8_ctor);
// declaration of chugin desctructor
CK_DLL_DTOR(pan8_dtor);
// for Chugins extending UGen, this is mono synthesis function for 1 sample
CK_DLL_TICKF(pan8_tickf);
// example of getter/setter
CK_DLL_MFUN(pan8_setPan);
CK_DLL_MFUN(pan8_getPan);
// this is a special offset reserved for Chugin internal data
t_CKINT pan8_data_offset = 0;


// declaration of chugin constructor
CK_DLL_CTOR(pan16_ctor);
// declaration of chugin desctructor
CK_DLL_DTOR(pan16_dtor);
// for Chugins extending UGen, this is mono synthesis function for 1 sample
CK_DLL_TICKF(pan16_tickf);
// example of getter/setter
CK_DLL_MFUN(pan16_setPan);
CK_DLL_MFUN(pan16_getPan);
// this is a special offset reserved for Chugin internal data
t_CKINT pan16_data_offset = 0;


// query function: chuck calls this when loading the Chugin
CK_DLL_QUERY( PanN )
{
    // hmm, don't change this...
    QUERY->setname(QUERY, "PanN");
    
    
    
    
    // begin the class definition
    QUERY->begin_class(QUERY, "Pan4", "UGen");
    QUERY->doc_class(QUERY, "Four-channel equal-power panner. ");
    
    // register the constructor (probably no need to change)
    QUERY->add_ctor(QUERY, pan4_ctor);
    // register the destructor (probably no need to change)
    QUERY->add_dtor(QUERY, pan4_dtor);
    
    // for UGen's only: add tick function
    QUERY->add_ugen_funcf(QUERY, pan4_tickf, NULL, 4, 4);
    
    // example of adding setter method
    QUERY->add_mfun(QUERY, pan4_setPan, "float", "pan");
    // example of adding argument to the above method
    QUERY->add_arg(QUERY, "float", "arg");
    QUERY->doc_class(QUERY, "Pan position [0-4]. ");
    
    // example of adding getter method
    QUERY->add_mfun(QUERY, pan4_getPan, "float", "pan");
    QUERY->doc_class(QUERY, "Pan position [0-4]. ");
    
    // this reserves a variable in the ChucK internal class to store
    // referene to the c++ class we defined above
    pan4_data_offset = QUERY->add_mvar(QUERY, "int", "@p4_data", false);
    
    // end the class definition
    // IMPORTANT: this MUST be called!
    QUERY->end_class(QUERY);
    
    
    
    // begin the class definition
    QUERY->begin_class(QUERY, "Pan8", "UGen");
    
    // register the constructor (probably no need to change)
    QUERY->add_ctor(QUERY, pan8_ctor);
    // register the destructor (probably no need to change)
    QUERY->add_dtor(QUERY, pan8_dtor);
    
    // for UGen's only: add tick function
    QUERY->add_ugen_funcf(QUERY, pan8_tickf, NULL, 8, 8);
    
    // example of adding setter method
    QUERY->add_mfun(QUERY, pan8_setPan, "float", "pan");
    // example of adding argument to the above method
    QUERY->add_arg(QUERY, "float", "arg");
    
    // example of adding getter method
    QUERY->add_mfun(QUERY, pan8_getPan, "float", "pan");
    
    // this reserves a variable in the ChucK internal class to store
    // referene to the c++ class we defined above
    pan8_data_offset = QUERY->add_mvar(QUERY, "int", "@p8_data", false);
    
    // end the class definition
    // IMPORTANT: this MUST be called!
    QUERY->end_class(QUERY);
    
    
    
    // begin the class definition
    QUERY->begin_class(QUERY, "Pan16", "UGen");
    
    // register the constructor (probably no need to change)
    QUERY->add_ctor(QUERY, pan16_ctor);
    // register the destructor (probably no need to change)
    QUERY->add_dtor(QUERY, pan16_dtor);
    
    // for UGen's only: add tick function
    QUERY->add_ugen_funcf(QUERY, pan16_tickf, NULL, 16, 16);
    
    // example of adding setter method
    QUERY->add_mfun(QUERY, pan16_setPan, "float", "pan");
    // example of adding argument to the above method
    QUERY->add_arg(QUERY, "float", "arg");
    
    // example of adding getter method
    QUERY->add_mfun(QUERY, pan16_getPan, "float", "pan");
    
    // this reserves a variable in the ChucK internal class to store
    // referene to the c++ class we defined above
    pan16_data_offset = QUERY->add_mvar(QUERY, "int", "@p16_data", false);
    
    // end the class definition
    // IMPORTANT: this MUST be called!
    QUERY->end_class(QUERY);
    
    
    
    
    // wasn't that a breeze?
    return TRUE;
}


// implementation for the constructor
CK_DLL_CTOR(pan4_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, pan4_data_offset) = 0;
    
    // instantiate our internal c++ class representation
    Pan4 * bcdata = new Pan4(API->vm->get_srate());
    
    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, pan4_data_offset) = (t_CKINT) bcdata;
}


// implementation for the destructor
CK_DLL_DTOR(pan4_dtor)
{
    // get our c++ class pointer
    Pan4 * bcdata = (Pan4 *) OBJ_MEMBER_INT(SELF, pan4_data_offset);
    // check it
    if( bcdata )
    {
        // clean up
        delete bcdata;
        OBJ_MEMBER_INT(SELF, pan4_data_offset) = 0;
        bcdata = NULL;
    }
}


// implementation for tick function
CK_DLL_TICKF(pan4_tickf)
{
    // get our c++ class pointer
    Pan4 * c = (Pan4 *) OBJ_MEMBER_INT(SELF, pan4_data_offset);
    
    if(c) c->tick(in, out, nframes);
    
    // yes
    return TRUE;
}


// example implementation for setter
CK_DLL_MFUN(pan4_setPan)
{
    // get our c++ class pointer
    PanN * pNdata = (PanN *) OBJ_MEMBER_INT(SELF, pan4_data_offset);
    // set the return value
    RETURN->v_float = pNdata->setPan(GET_NEXT_FLOAT(ARGS));
}


// example implementation for getter
CK_DLL_MFUN(pan4_getPan)
{
    // get our c++ class pointer
    PanN * pNdata = (PanN *) OBJ_MEMBER_INT(SELF, pan4_data_offset);
    // set the return value
    RETURN->v_float = pNdata->getPan();
}






// implementation for the constructor
CK_DLL_CTOR(pan8_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, pan8_data_offset) = 0;
    
    // instantiate our internal c++ class representation
    Pan8 * bcdata = new Pan8(API->vm->get_srate());
    
    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, pan8_data_offset) = (t_CKINT) bcdata;
}


// implementation for the destructor
CK_DLL_DTOR(pan8_dtor)
{
    // get our c++ class pointer
    Pan8 * bcdata = (Pan8 *) OBJ_MEMBER_INT(SELF, pan8_data_offset);
    // check it
    if( bcdata )
    {
        // clean up
        delete bcdata;
        OBJ_MEMBER_INT(SELF, pan8_data_offset) = 0;
        bcdata = NULL;
    }
}


// implementation for tick function
CK_DLL_TICKF(pan8_tickf)
{
    // get our c++ class pointer
    Pan8 * c = (Pan8 *) OBJ_MEMBER_INT(SELF, pan8_data_offset);
    
    if(c) c->tick(in, out, nframes);
    
    // yes
    return TRUE;
}


// example implementation for setter
CK_DLL_MFUN(pan8_setPan)
{
    // get our c++ class pointer
    PanN * pNdata = (PanN *) OBJ_MEMBER_INT(SELF, pan8_data_offset);
    // set the return value
    RETURN->v_float = pNdata->setPan(GET_NEXT_FLOAT(ARGS));
}


// example implementation for getter
CK_DLL_MFUN(pan8_getPan)
{
    // get our c++ class pointer
    PanN * pNdata = (PanN *) OBJ_MEMBER_INT(SELF, pan8_data_offset);
    // set the return value
    RETURN->v_float = pNdata->getPan();
}






// implementation for the constructor
CK_DLL_CTOR(pan16_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, pan16_data_offset) = 0;
    
    // instantiate our internal c++ class representation
    Pan16 * bcdata = new Pan16(API->vm->get_srate());
    
    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, pan16_data_offset) = (t_CKINT) bcdata;
}


// implementation for the destructor
CK_DLL_DTOR(pan16_dtor)
{
    // get our c++ class pointer
    Pan16 * bcdata = (Pan16 *) OBJ_MEMBER_INT(SELF, pan16_data_offset);
    // check it
    if( bcdata )
    {
        // clean up
        delete bcdata;
        OBJ_MEMBER_INT(SELF, pan16_data_offset) = 0;
        bcdata = NULL;
    }
}


// implementation for tick function
CK_DLL_TICKF(pan16_tickf)
{
    // get our c++ class pointer
    Pan16 * c = (Pan16 *) OBJ_MEMBER_INT(SELF, pan16_data_offset);
    
    if(c) c->tick(in, out, nframes);
    
    // yes
    return TRUE;
}

// example implementation for setter
CK_DLL_MFUN(pan16_setPan)
{
    // get our c++ class pointer
    PanN * pNdata = (PanN *) OBJ_MEMBER_INT(SELF, pan16_data_offset);
    // set the return value
    RETURN->v_float = pNdata->setPan(GET_NEXT_FLOAT(ARGS));
}


// example implementation for getter
CK_DLL_MFUN(pan16_getPan)
{
    // get our c++ class pointer
    PanN * pNdata = (PanN *) OBJ_MEMBER_INT(SELF, pan16_data_offset);
    // set the return value
    RETURN->v_float = pNdata->getPan();
}


