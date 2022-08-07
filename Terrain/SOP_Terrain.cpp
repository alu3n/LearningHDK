#include "SOP_Terrain.hpp"

#include "SOP_Terrain.proto.h"

#include <GU/GU_Detail.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <PRM/PRM_TemplateBuilder.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <UT/UT_StringHolder.h>
#include <SYS/SYS_Math.h>
#include <limits.h>

//New
#include "TerrainModel/Nutrients.hpp"

using namespace HDK_Sample;

const UT_StringHolder SOP_Terrain::theSOPTypeName("HDKTerrain"_sh);

void
newSopOperator(OP_OperatorTable *table)
{
    table->addOperator(new OP_Operator(
        SOP_Terrain::theSOPTypeName,   // Internal name
        "Star",                     // UI name
        SOP_Terrain::myConstructor,    // How to build the SOP
        SOP_Terrain::buildTemplates(), // My parameters
        0,                          // Min # of sources
        0,                          // Max # of sources
        nullptr,                    // Custom local variables (none)
        OP_FLAG_GENERATOR));        // Flag it as generator
}

static const char *theDsFile = R"THEDSFILE(
{
    parm {
        name    "step"
        label   "Time Step"
        type    integer
        default { "0" }
        export all
    }
}
)THEDSFILE";

PRM_Template*
SOP_Terrain::buildTemplates()
{
    static PRM_TemplateBuilder templ("SOP_Terrain.cpp"_sh, theDsFile);
    return templ.templates();
}

class SOP_TerrainVerb : public SOP_NodeVerb
{
public:
    SOP_TerrainVerb() {}
    virtual ~SOP_TerrainVerb() {}

    virtual SOP_NodeParms *allocParms() const { return new SOP_TerrainParms(); }
    virtual UT_StringHolder name() const { return SOP_Terrain::theSOPTypeName; }

    virtual CookMode cookMode(const SOP_NodeParms *parms) const { return COOK_GENERIC; }

    virtual void cook(const CookParms &cookparms) const;

    static const SOP_NodeVerb::Register<SOP_TerrainVerb> theVerb;
private:
    int * LastFrame = new int(0);
//    int * PointCount = new int(0);
};


const SOP_NodeVerb::Register<SOP_TerrainVerb> SOP_TerrainVerb::theVerb;

const SOP_NodeVerb * SOP_Terrain::cookVerb() const
{
    return SOP_TerrainVerb::theVerb.get();
}

void SOP_TerrainVerb::cook(const SOP_NodeVerb::CookParms &cookparms) const
{
    GU_Detail *detail = cookparms.gdh().gdpNC();
    auto && sopparms = cookparms.parms<SOP_TerrainParms>();

    auto frame = (int)sopparms.getStep();

    if(frame == *LastFrame){
//        return;
        //Here draw cached file
    }
    if(frame-1 == *LastFrame){
//        *PointCount = frame;
        //Here do step
        *LastFrame = *LastFrame + 1;
//        *PointCount = *PointCount + frame;
    }
    else{
        *LastFrame = 0;
        //Here reset sim
    }

//    detail->clearAndDestroy();
//    detail->appendPointBlock(*PointCount);

}
