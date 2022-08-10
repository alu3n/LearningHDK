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
#include "TerrainModel/TerrainSimulation.hpp"

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
    TerrainSimulation * terrainSimulation = new TerrainSimulation();
//    int * PointCount = new int(0);
    void DrawCached() const{

    }
};


const SOP_NodeVerb::Register<SOP_TerrainVerb> SOP_TerrainVerb::theVerb;

const SOP_NodeVerb * SOP_Terrain::cookVerb() const
{
    return SOP_TerrainVerb::theVerb.get();
}

void SOP_TerrainVerb::cook(const SOP_NodeVerb::CookParms &cookparms) const
{
    //Parameters to create:
    // Water as of now... pscale, water amount, position

    GU_Detail *detail = cookparms.gdh().gdpNC();
    auto && sopparms = cookparms.parms<SOP_TerrainParms>();

    auto frame = (int)sopparms.getStep();


    if(frame == *LastFrame){
        return;
    }
    if(frame-1 == *LastFrame){
        *LastFrame = *LastFrame + 1;
//        DrawCached();
        terrainSimulation->Tick(frame);
    }
    else{
        *LastFrame = 0;
        terrainSimulation->Reset();
        detail->clearAndDestroy();
        return;
    }

//    TerrainFormation T = TerrainFormation();
    detail->clearAndDestroy();

//    auto T* = terrainSimulation->T;

    detail->appendPointBlock(terrainSimulation->T.Storage.Count(CellType::UG)+terrainSimulation->T.Storage.Count(CellType::AG));

    detail->addFloatTuple(GA_ATTRIB_POINT,"pscale",1);
    detail->addFloatTuple(GA_ATTRIB_POINT,"water",1);

    GA_Attribute *pscaleAttrib = detail->findFloatTuple(GA_ATTRIB_POINT,"pscale",1);
    GA_Attribute *waterAttrib = detail->findFloatTuple(GA_ATTRIB_POINT,"water",1);

    const GA_AIFTuple *pscaleTuple = pscaleAttrib->getAIFTuple();
    const GA_AIFTuple *waterTuple = waterAttrib->getAIFTuple();

    auto fullVolume = TerrainSettings::VoxelSize*TerrainSettings::VoxelSize*TerrainSettings::VoxelSize;

    auto sizeAG = terrainSimulation->T.Storage.Count(CellType::AG);
    auto sizeUG = terrainSimulation->T.Storage.Count(CellType::UG);

    for(int i = 0; i < sizeAG; ++i){
        auto P = terrainSimulation->T.Storage.WorldCords(i);
        UT_Vector3 pos(P.X,P.Y,P.Z);
        detail->setPos3(i,pos);
        auto W = terrainSimulation->T.Storage.CellAG(i).W.Volume;
        waterTuple->set(waterAttrib,i,W/fullVolume);
    }

    for(int i = sizeAG; i < sizeAG+sizeUG; ++i){
        auto P = terrainSimulation->T.Storage.WorldCords(i);
        UT_Vector3 pos(P.X,P.Y,P.Z);
        detail->setPos3(i,pos);
        auto W = terrainSimulation->T.Storage.CellUG(i).W.Volume;
        waterTuple->set(waterAttrib,i,W/fullVolume);
    }

    //TODO: Create constructor with top layer AGs

//    for(int i = 0; i < terrainSimulation->T.Storage.Count(CellType::UG); ++i){
//        auto P = terrainSimulation->T.Storage.WorldCords(i);
//        UT_Vector3 pos(P.X,P.Y,P.Z);
//        detail->setPos3(i,pos);
//        auto W = terrainSimulation->T.Storage.CellUG(i).W.Volume;
//        waterTuple->set(waterAttrib,i,W/fullVolume);
//    }

//    for(int i = terrainSimulation->T.Storage.Count(CellType::AG);;++i){
//
//    }


//    for(int i = 0; i < T->AgentCount();++i){
//        auto P = T->GetPosition({CellType::UG,i});
//        UT_Vector3 pos(get<0>(P),get<1>(P),get<2>(P));
//        UT_Vector3 pscale(VoxelSize,0,0);
//        UT_Vector3 water(T->UnderGroundCells[i].W.Volume,0,0);
////        UT_Vector3 water((float)frame,0,0);
//
//        pscaleTuple->set(pscaleAttrib,i,pscale.data(),3);
//        waterTuple->set(waterAttrib,i,water.data(),3);
//        detail->setPos3(i,pos);
////        detail->setpscale1(i,0);
//    }
}
