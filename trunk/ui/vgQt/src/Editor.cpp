// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/Editor.hpp"

#include <QDebug>
#include <QAction>

static const int MARGIN_SCRIPT_FOLD_INDEX = 1;

Editor::Editor(QWidget* parent) :
    ScintillaEdit(parent),
    customKeywords("")
{
    styleClearAll();
    setMarginWidthN(0,25); // par défaut la marge 0 est le nombre de ligne
    autoCSetIgnoreCase(true);

    connect(this, SIGNAL(marginClicked(int,int,int)), this, SLOT(onMarginClicked(int,int,int)));
    connect(this, SIGNAL(charAdded(int)), this, SLOT(colourise()));
    connect(this, SIGNAL(charAdded(int)), this, SLOT(showSuggestions()));

    QAction* action = new QAction(this);
    action->setShortcut(QKeySequence(tr("Ctrl+Space") ));
    action->setShortcutContext(Qt::WidgetShortcut);
    addAction(action);

    connect(action, SIGNAL( triggered() ), this, SLOT(showSuggestionsForced()));
}

void Editor::setLanguage( Language language)
{
    switch(language)
    {
    case(CPP):
        setLexerLanguage("cpp");
        setStyleBits(5);

        setProperty("fold", "1");

        setMarginMaskN( MARGIN_SCRIPT_FOLD_INDEX, SC_MASK_FOLDERS);
        setMarginWidthN( MARGIN_SCRIPT_FOLD_INDEX, 20);
        setMarginSensitiveN( MARGIN_SCRIPT_FOLD_INDEX, true);
        markerDefine( SC_MARKNUM_FOLDER, SC_MARK_PLUS);
        markerDefine( SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
        markerDefine( SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
        setFoldFlags(16);

        customKeywords = "and and_eq asm auto bitand bitor bool break" \
                " case catch char class compl const const_cast continue" \
                " default delete do double dynamic_cast else enum explicit export extern false float for" \
                " friend goto if inline int long mutable namespace new not not_eq" \
                " operator or or_eq private protected public" \
                " register reinterpret_cast return short signed sizeof static static_cast struct switch" \
                " template this throw true try typedef typeid typename union unsigned using" \
                " virtual void volatile wchar_t while xor xor_eq";

        setKeyWords(0, customKeywords.c_str());

        styleSetFore(1, 0x007f00); // multiline comment 
        styleSetFore(2, 0x007f00); // comment inline
        styleSetFore(4, 0xff9900); // number
        styleSetFore(5, 0xff0000); // keyword
        styleSetBold(5, true);
        styleSetFore(6, 0x007f00); // string
        styleSetFore(9, 0xff0000); // preprocessor
        styleSetFore(10, 0x1d0ccf); // operator
        styleSetFore(19, 0x0000ff); // global class

        break;


    case(PYTHON):
        setLexerLanguage("python");
        setStyleBits(5);

        setProperty("fold", "1");

        setMarginMaskN( MARGIN_SCRIPT_FOLD_INDEX, SC_MASK_FOLDERS);
        setMarginWidthN( MARGIN_SCRIPT_FOLD_INDEX, 20);
        setMarginSensitiveN( MARGIN_SCRIPT_FOLD_INDEX, true);
        markerDefine( SC_MARKNUM_FOLDER, SC_MARK_PLUS);
        markerDefine( SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
        markerDefine( SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
        markerDefine( SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
        setFoldFlags(16);

        customKeywords = "and as assert break class continue def del elif else except exec" \
                " False finally for from global if import in is lambda None nonlocal" \
                " not or pass print raise return True try while with yield";
        setKeyWords(0, customKeywords.c_str());

        styleSetFore(0, 0x808080);
        styleSetFore(1, 0x007F00);
        styleSetFore(2, 0x7F7F00);
        styleSetFore(3, 0x7F007F);
        styleSetFore(4, 0x7F007F);
        styleSetFore(5, 0x7F0000);
        styleSetBold(5, true);
        styleSetFore(6, 0x00007F);
        styleSetFore(7, 0x00007F);
        styleSetFore(8, 0xFF0000);
        styleSetFore(9, 0x7F7F00);
        styleSetFore(10, 0x1d0ccf);
        styleSetFore(12, 0x7F7F7F);
        styleSetFore(13, 0x000000);
        styleSetFore(14, 0x907040);
        styleSetFore(15, 0x005080);
        styleSetFore(34, 0xFF0000);
        styleSetFore(35, 0x0000FF);

        break;
    case(GLSL):
        setLexerLanguage("cpp");
        setStyleBits(5);
        customKeywords = " abs acos acosh active all all any asin asinh asm atan atanh bool break bvec2 bvec3 bvec4" \
                " case cast ceil centroid clamp class column_major common const continue core cos cosh" \
                " cross default degrees determinant dFdx dFdy disable discard distance do dot double dvec2" \
                " dvec3 dvec4 else EmitVertex enable EndPrimitive enum equal exp exp2 extern external" \
                " faceforward false filter fixed flat float floor for fract fvec2 fvec3 fvec4 fwidth gl_ClipDistance" \
                " gl_DepthRangeParameters gl_FragCoord gl_FragDepth GL_FRAGMENT_PRECISION_HIGH gl_FrontFacing" \
                " gl_InstanceID gl_InvocationID gl_Layer gl_MaxClipDistances gl_MaxCombinedTextureImageUnits gl_MaxDrawBuffers" \
                " gl_MaxFragmentInputComponents gl_MaxFragmentUniformComponents gl_MaxGeometryInputComponents" \
                " gl_MaxGeometryOutputComponents gl_MaxGeometryOutputVertices gl_MaxGeometryTextureImageUnits" \
                " gl_MaxGeometryTotalOutputComponents gl_MaxGeometryUniformComponents gl_MaxGeometryVaryingComponents" \
                " gl_MaxTextureImageUnits gl_MaxVertexAttribs gl_MaxVertexOutputComponents gl_MaxVertexTextureImageUnits" \
                " gl_MaxVertexUniformComponents gl_PerVertex gl_PointCoord gl_PointSize gl_Position gl_PrimitiveID gl_PrimitiveID" \
                " gl_PrimitiveIDIn gl_VertexID goto greaterThan greaterThanEqual half highp hvec2 hvec3 hvec4 if iimage1D iimage1DArray" \
                " iimage2D iimage2DArray iimage3D iimageBuffer iimageCube image1D image1DArray image1DArrayShadow image1DShadow" \
                " image2D image2DArray image2DArrayShadow image2DShadow image3D imageBuffer imageCube in inline inout input" \
                " int interface invariant inverse inversesqrt isampler1D isampler1DArray isampler2D isampler2DArray isampler2DMS" \
                " isampler2DMSArray isampler2DRect isampler3D isamplerBuffer isamplerCube isinf isnan ivec2 ivec3 ivec4 layout" \
                " length lessThan lessThanEqual line_strip lines lines_adjacency log log2 long lowp mat2 mat2x2 mat2x3 mat2x4" \
                " mat3 mat3x2 mat3x3 mat3x4 mat4 mat4x2 mat4x3 mat4x4 matrixCompMult max max_vertices mediump min mix mod" \
                " modf namespace noinline noise1 noise2 noise3 noise4 noperspective normalize not notEqual origin_upper_left" \
                " out outerProduct output packed partition pixel_center_integer points pow precision public radians reflect" \
                " refract require return round roundEven row_major sampler1D sampler1DArray sampler1DArrayShadow sampler1DShadow" \
                " sampler2D sampler2DArray sampler2DArrayShadow sampler2DMS sampler2DMSArray sampler2DRect sampler2DRectShadow" \
                " sampler2DShadow sampler3D sampler3DRect samplerBuffer samplerCube samplerCubeShadow shared short sign sin sinh" \
                " sizeof smooth smoothstep sqrt static std140 step struct superp switch tan tanh template texelFetch texelFetchOffset" \
                " texture textureGrad textureGradOffset textureLod textureLodOffset textureOffset textureProj textureProjGrad" \
                " textureProjGradOffset textureProjLod textureProjLodOffset textureProjOffset textureSize this transpose" \
                " triangle_strip triangles triangles_adjacency true trunc typedef uimage1D uimage1DArray uimage2D uimage2DArray" \
                " uimage3D uimageBuffer uimageCube uint uniform union unsigned usampler1D usampler1DArray usampler2D usampler2DArray" \
                " usampler2DMS usampler2DMSArray usampler2DRect usampler3D usamplerBuffer usamplerCube using uvec2 uvec3 uvec4" \
                " vec2 vec3 vec4 void volatile warn while";

        setKeyWords(0, customKeywords.c_str());
		styleSetFore(1, 0x007f00); // multiline comment 
        styleSetFore(2, 0x007f00); // comment inline
        styleSetFore(4, 0xff9900); // number
        styleSetFore(5, 0xff0000);
        styleSetBold(5, false);
        styleSetFore(6, 0x007f00); // string
        styleSetFore(9, 0xff0000); // preprocessor
        styleSetFore(10, 0x1d0ccf); // operator
        styleSetFore(19, 0x0000ff); // global class

        break;
    }
}

void Editor::onMarginClicked(int position, int modifiers, int margin)
{
    Q_UNUSED(modifiers);
    switch(margin)
    {
        case MARGIN_SCRIPT_FOLD_INDEX:
            const int line = lineFromPosition(position);
            toggleFold(line);
            break;
    }
}

void Editor::colourise()
{
    ScintillaEdit::colourise(0, -1);
}

void Editor::showSuggestions()
{
    int pos = currentPos();
    int lengthEntered = pos - wordStartPosition(pos, true);
    if (lengthEntered > 0)
    {
        autoCShow(lengthEntered, customKeywords.c_str());
    }
}

void Editor::showSuggestionsForced()
{
    int pos = currentPos();
    int lengthEntered = pos - wordStartPosition(pos, true);
    autoCShow(lengthEntered, customKeywords.c_str());
}

/*
#define SCE_C_DEFAULT 0
#define SCE_C_COMMENT 1
#define SCE_C_COMMENTLINE 2
#define SCE_C_COMMENTDOC 3
#define SCE_C_NUMBER 4
#define SCE_C_WORD 5
#define SCE_C_STRING 6
#define SCE_C_CHARACTER 7
#define SCE_C_UUID 8
#define SCE_C_PREPROCESSOR 9
#define SCE_C_OPERATOR 10
#define SCE_C_IDENTIFIER 11
#define SCE_C_STRINGEOL 12
#define SCE_C_VERBATIM 13
#define SCE_C_REGEX 14
#define SCE_C_COMMENTLINEDOC 15
#define SCE_C_WORD2 16
#define SCE_C_COMMENTDOCKEYWORD 17
#define SCE_C_COMMENTDOCKEYWORDERROR 18
#define SCE_C_GLOBALCLASS 19
#define SCE_C_STRINGRAW 20
#define SCE_C_TRIPLEVERBATIM 21
#define SCE_C_HASHQUOTEDSTRING 22
*/
