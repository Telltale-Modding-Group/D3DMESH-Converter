#pragma once
#ifndef T3_EFFECT_TYPE_H
#define T3_EFFECT_TYPE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>

//|||||||||||||||||||||||||||||||||||||||| T3 EFFECT TYPE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3 EFFECT TYPE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3 EFFECT TYPE ||||||||||||||||||||||||||||||||||||||||
//NOTE: This is a regular int enum

/// <summary>
/// [ENUM] 
/// </summary>
enum T3EffectType
{
	eEffect_Mesh = 0x0,
	eEffect_Particle = 0x1,
	eEffect_ParticleGlow = 0x2,
	eEffect_ParticleForceLinearDepth = 0x3,
	eEffect_Particle_Xbox_Instanced = 0x4,
	eEffect_DeferredDecalGBuffer = 0x5,
	eEffect_DeferredDecalEmissive = 0x6,
	eEffect_DeferredDecalGlow = 0x7,
	eEffect_SceneSimple = 0x8,
	eEffect_SceneSimple_Texture = 0x9,
	eEffect_SceneSimple_Cone = 0x0A,
	eEffect_SceneNPRLinesCS_Rasterize = 0x0B,
	eEffect_SceneNPRLinesCS_ForceLinearDepth = 0x0C,
	eEffect_ScenePreZ = 0x0D,
	eEffect_ScenePreZLines = 0x0E,
	eEffect_ForceLinearDepth = 0x0F,
	eEffect_SceneShadowMap = 0x10,
	eEffect_SceneGlow = 0x11,
	eEffect_SceneGBuffer = 0x12,
	eEffect_SceneGBufferLines = 0x13,
	eEffect_SceneToonOutline = 0x14,
	eEffect_SceneToonOutline2 = 0x15,
	eEffect_SceneToonOutline2_GBuffer = 0x16,
	eEffect_FX_GlowPrepare = 0x17,
	eEffect_FX_Glow = 0x18,
	eEffect_FX_DepthOfFieldPrepare = 0x19,
	eEffect_FX_GaussianBlur = 0x1A,
	eEffect_FX_GaussianBlur_Glow = 0x1B,
	eEffect_FX_GaussianBlur_Outline = 0x1C,
	eEffect_FX_BlurUp = 0x1D,
	eEffect_FX_MotionBlur = 0x1E,
	eEffect_FX_MergeColorDepth = 0x1F,
	eEffect_FX_PostColor = 0x20,
	eEffect_DynamicLightMap = 0x21,
	eEffect_FX_RadialBlur = 0x22,
	eEffect_FX_FXAA = 0x23,
	eEffect_FX_SMAA_EdgeDetect = 0x24,
	eEffect_FX_SMAA_BlendWeight = 0x25,
	eEffect_FX_SMAA_Final = 0x26,
	eEffect_FX_GBufferResolve = 0x27,
	eEffect_FX_GBufferDownSample = 0x28,
	eEffect_FX_LinearDepthDownSample = 0x29,
	eEffect_FX_DepthDownSample = 0x2A,
	eEffect_FX_StencilMaskRestore = 0x2B,
	eEffect_FX_OcclusionFilter = 0x2C,
	eEffect_FX_Null = 0x2D,
	eEffect_FX_Copy = 0x2E,
	eEffect_FX_CopyDepth = 0x2F,
	eEffect_FX_CompositeAlpha = 0x30,
	eEffect_FX_CompositeQuarter = 0x31,
	eEffect_FX_CreateOutlineSrc = 0x32,
	eEffect_FX_CreateOutline = 0x33,
	eEffect_FX_BrushOutline = 0x34,
	eEffect_FX_BrushOutline_Simple = 0x35,
	eEffect_FX_BrushOffsetApply = 0x36,
	eEffect_FX_BrushOutlineBlurPrepare = 0x37,
	eEffect_FX_BrushOutlineBlur = 0x38,
	eEffect_FX_ApplyModulatedShadow = 0x39,
	eEffect_FX_FinalResolve = 0x3A,
	eEffect_FX_FinalDebugOverlay = 0x3B,
	eEffect_SceneText = 0x3C,
	eEffect_SceneSimple_Texture_AlphaOnly = 0x3D,
	eEffect_SceneHLSMovieYUV = 0x3E,
	eEffect_SceneHLSMovieRGB = 0x3F,
	eEffect_DirectionalLightShadow = 0x40,
	eEffect_DirectionalLightShadow_High = 0x41,
	eEffect_ProjectedTextureShadow = 0x42,
	eEffect_ProjectedTextureColor = 0x43,
	eEffect_EnvLightShadowMark_Point = 0x44,
	eEffect_EnvLightShadowMark_Spot = 0x45,
	eEffect_EnvLightShadowApply_Point = 0x46,
	eEffect_EnvLightShadowApply_Spot = 0x47,
	eEffect_EnvLightShadowApply_Directional = 0x48,
	eEffect_EnvLightShadowApply_DirectionalFade = 0x49,
	eEffect_EnvLightShadowApply_DirectionalBlend = 0x4A,
	eEffect_EnvLightShadowApply_SDSM_Directional = 0x4B,
	eEffect_EnvLightShadowApply_SDSM_DirectionalFade = 0x4C,
	eEffect_ShadowMark_SDSM = 0x4D,
	eEffect_ShadowVolumeApply = 0x4E,
	eEffect_ShadowTrace = 0x4F,
	eEffect_ShadowTrace_HBAOLow = 0x50,
	eEffect_ShadowTrace_HBAOMid = 0x51,
	eEffect_ShadowTrace_HBAOHigh = 0x52,
	eEffect_ShadowTrace_MSAA = 0x53,
	eEffect_ShadowTrace_HBAOLow_MSAA = 0x54,
	eEffect_ShadowTrace_HBAOMid_MSAA = 0x55,
	eEffect_ShadowTrace_HBAOHigh_MSAA = 0x56,
	eEffect_FX_DeferredFilter_Light = 0x57,
	eEffect_FX_DeferredFilter_Shadow = 0x58,
	eEffect_FX_DeferredFilter_LightShadow = 0x59,
	eEffect_FX_CreateOutlineSrcQuarter = 0x5A,
	eEffect_FX_NewGlowH1x = 0x5B,
	eEffect_FX_NewGlowV1x = 0x6B,
	eEffect_FX_NewGlowPresent = 0x7B,
	eEffect_FX_NewDepthOfFieldPreparE, alf = 0x7C,
	eEffect_FX_DepthOfFieldBlurH1x = 0x7D,
	eEffect_FX_DepthOfFieldBlurV1x = 0x7E,
	eEffect_FX_DepthOfFieldBlurH = 0x7F,
	eEffect_FX_DepthOfFieldBlurV = 0x80,
	eEffect_FX_DepthOfFieldBlurHNear = 0x81,
	eEffect_FX_DepthOfFieldBlurHFar = 0x82,
	eEffect_FX_DepthOfFieldBlurVNear = 0x83,
	eEffect_FX_DepthOfFieldBlurVFar = 0x84,
	eEffect_FX_ShadowFilter_Pass0 = 0x85,
	eEffect_FX_ShadowFilter_Pass0_TAA = 0x86,
	eEffect_FX_ShadowFilter_Blur0 = 0x87,
	eEffect_FX_ShadowFilter_Blur1 = 0x88,
	eEffect_FX_HBAOLowestQuality = 0x89,
	eEffect_FX_HBAOLowQuality = 0x8A,
	eEffect_FX_HBAOMediumQuality = 0x8B,
	eEffect_FX_HBAOHighQuality = 0x8C,
	eEffect_FX_HBAOHighestQuality = 0x8D,
	eEffect_FX_HBAODeinterleaveDepth = 0x8E,
	eEffect_FX_HBAODeinterleaveNormals = 0x8F,
	eEffect_FX_HBAOReinterleave = 0x90,
	eEffect_FX_SSLines = 0x91,
	eEffect_FX_SSLinesResolve_1x_Pass0 = 0x92,
	eEffect_FX_SSLinesResolve_1x_Pass1 = 0x93,
	eEffect_FX_SSLinesResolve_2x_Pass0 = 0x94,
	eEffect_FX_SSLinesResolve_2x_Pass1 = 0x95,
	eEffect_FX_SSLinesResolve_3x_Pass0 = 0x96,
	eEffect_FX_SSLinesResolve_3x_Pass1 = 0x97,
	eEffect_FX_SSLinesResolve_4x_Pass0 = 0x98,
	eEffect_FX_SSLinesResolve_4x_Pass1 = 0x99,
	eEffect_FX_MSAAResolve_2x = 0x9A,
	eEffect_FX_MSAAResolve_4x = 0x9B,
	eEffect_FX_MSAAResolve_8x = 0x9C,
	eEffect_FX_MSAASceneResolve_2x = 0x9D,
	eEffect_FX_MSAASceneResolve_4x = 0x9E,
	eEffect_FX_MSAASceneResolve_8x = 0x9F,
	eEffect_FX_SceneResolve_TAA = 0x0A0,
	eEffect_FX_MSAASceneResolve_TAA_2x = 0x0A1,
	eEffect_FX_MSAASceneResolve_TAA_4x = 0x0A2,
	eEffect_FX_MSAASceneResolve_TAA_8x = 0x0A3,
	eEffect_FX_MSAAGBufferResolve_2x = 0x0A4,
	eEffect_FX_MSAAGBufferResolve_4x = 0x0A5,
	eEffect_FX_MSAAGBufferResolve_8x = 0x0A6,
	eEffect_MakeMipLevel = 0x0A7,
	eEffect_MakeMipLevel_BlurH = 0x0A8,
	eEffect_MakeMipLevel_BlurV = 0x0A9,
	eEffect_MakeMipLevel_Array = 0x0AA,
	eEffect_CS_ComputeTest = 0x0AB,
	eEffect_CS_ApplySkinning_0Normal = 0x0AC,
	eEffect_CS_ApplySkinning_1Normal = 0x0AD,
	eEffect_CS_ApplySkinning_2Normal = 0x0AE,
	eEffect_CS_ApplySkinning_3Normal = 0x0AF,
	eEffect_CS_ApplySkinning_Float3Position_0Normal = 0x0B0,
	eEffect_CS_ApplySkinning_Float3Position_1Normal = 0x0B1,
	eEffect_CS_ApplySkinning_Float3Position_2Normal = 0x0B2,
	eEffect_CS_ApplySkinning_Float3Position_3Normal = 0x0B3,
	eEffect_CS_LineGeneration = 0x0B4,
	eEffect_CS_ClearIndirectDraw = 0x0B5,
	eEffect_CS_LightClustering2D = 0x0B6,
	eEffect_CS_LightClustering3D = 0x0B7,
	eEffect_CS_ShadowCascadeDistances_Manual = 0x0B8,
	eEffect_CS_ShadowCascadeDistances_Auto = 0x0B9,
	eEffect_CS_ShadowCascadeBounds_Pass0 = 0x0BA,
	eEffect_CS_ShadowCascadeBounds_PassN = 0x0BB,
	eEffect_CS_ShadowCascades = 0x0BC,
	eEffect_CS_ShadowCascades_ComputedBounds = 0x0BD,
	eEffect_CS_CullShadowCasters = 0x0BE,
	eEffect_CS_EnvLightMakeEVSM_Linear_Blur0 = 0x0BF,
	eEffect_CS_EnvLightMakeEVSM_Linear_Blur3x3 = 0x0C0,
	eEffect_CS_EnvLightMakeEVSM_Linear_Blur9x9 = 0x0C1,
	eEffect_CS_EnvLightMakeEVSM_NonLinear_Blur0 = 0x0C2,
	eEffect_CS_EnvLightMakeEVSM_NonLinear_Blur3x3 = 0x0C3,
	eEffect_CS_EnvLightMakeEVSM_NonLinear_Blur9x9 = 0x0C4,
	eEffect_CS_DepthReduction_Pass0_8x8 = 0x0C5,
	eEffect_CS_DepthReduction_Pass0_16x16 = 0x0C6,
	eEffect_CS_DepthReduction_PassN = 0x0C7,
	eEffect_CS_DepthReduction_PassFinal = 0x0C8,
	eEffect_CS_BokE, Sprites = 0x0C9,
	eEffect_FX_RasterizeBokeh = 0x0CA,
	eEffect_CS_EnlightenMakeDusters_Point = 0x0CB,
	eEffect_CS_EnlightenMakeDusters_Spot = 0x0CC,
	eEffect_CS_EnlightenMakeDusters_Directional = 0x0CD,
	eEffect_CS_WaveformMonitor = 0x0CE,
	eEffect_CS_EnvLightApplyDeferred = 0x0CF,
	eEffect_CS_EnvLightApplyDeferred_LowRes = 0x0D0,
	eEffect_BakeObjectNormals_Tool = 0x0D1,
	eEffect_BakeObjectNormals_NormalMap_Tool = 0x0D2,
	eEffect_BakeTangentNormals_Tool = 0x0D3,
	eEffect_BakeLighting_Tool = 0x0D4,
	eEffect_CS_LightmapBlurH_Tool = 0x0D5,
	eEffect_CS_LightmapBlurV_Tool = 0x0D6,
	eEffect_CS_LightmapFilter_Tool = 0x0D7,
	eEffect_CS_LightmapConvert_Tool = 0x0D8,
	eEffect_CS_BakeShadowVolume_Tool = 0x0D9,
	eEffect_CS_ComputeAsyncTest = 0x0DA,
	eEffect_Count = 0x0DB,
	eEffect_None = 0x0FFFFFFFF,
};

//|||||||||||||||||||||||||||||||||||||||| T3 EFFECT TYPE STRINGS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3 EFFECT TYPE STRINGS ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3 EFFECT TYPE STRINGS ||||||||||||||||||||||||||||||||||||||||

static std::string GetT3EffectTypeName(T3EffectType value)
{
	switch (value)
	{
	case eEffect_Mesh:
		return "eEffect_Mesh";
	case eEffect_Particle:
		return "eEffect_Particle";
	case eEffect_ParticleGlow:
		return "eEffect_ParticleGlow";
	case eEffect_ParticleForceLinearDepth:
		return "eEffect_ParticleForceLinearDepth";
	case eEffect_Particle_Xbox_Instanced:
		return "eEffect_Particle_Xbox_Instanced";
	case eEffect_DeferredDecalGBuffer:
		return "eEffect_DeferredDecalGBuffer";
	case eEffect_DeferredDecalEmissive:
		return "eEffect_DeferredDecalEmissive";
	case eEffect_DeferredDecalGlow:
		return "eEffect_DeferredDecalGlow";
	case eEffect_SceneSimple:
		return "eEffect_SceneSimple";
	case eEffect_SceneSimple_Texture:
		return "eEffect_SceneSimple_Texture";
	case eEffect_SceneSimple_Cone:
		return "eEffect_SceneSimple_Cone";
	case eEffect_SceneNPRLinesCS_Rasterize:
		return "eEffect_SceneNPRLinesCS_Rasterize";
	case eEffect_SceneNPRLinesCS_ForceLinearDepth:
		return "eEffect_SceneNPRLinesCS_ForceLinearDepth";
	case eEffect_ScenePreZ:
		return "eEffect_ScenePreZ";
	case eEffect_ScenePreZLines:
		return "eEffect_ScenePreZLines";
	case eEffect_ForceLinearDepth:
		return "eEffect_ForceLinearDepth";
	case eEffect_SceneShadowMap:
		return "eEffect_SceneShadowMap";
	case eEffect_SceneGlow:
		return "eEffect_SceneGlow";
	case eEffect_SceneGBuffer:
		return "eEffect_SceneGBuffer";
	case eEffect_SceneGBufferLines:
		return "eEffect_SceneGBufferLines";
	case eEffect_SceneToonOutline:
		return "eEffect_SceneToonOutline";
	case eEffect_SceneToonOutline2:
		return "eEffect_SceneToonOutline2";
	case eEffect_SceneToonOutline2_GBuffer:
		return "eEffect_SceneToonOutline2_GBuffer";
	case eEffect_FX_GlowPrepare:
		return "eEffect_FX_GlowPrepare";
	case eEffect_FX_Glow:
		return "eEffect_FX_Glow";
	case eEffect_FX_DepthOfFieldPrepare:
		return "eEffect_FX_DepthOfFieldPrepare";
	case eEffect_FX_GaussianBlur:
		return "eEffect_FX_GaussianBlur";
	case eEffect_FX_GaussianBlur_Glow:
		return "eEffect_FX_GaussianBlur_Glow";
	case eEffect_FX_GaussianBlur_Outline:
		return "eEffect_FX_GaussianBlur_Outline";
	case eEffect_FX_BlurUp:
		return "eEffect_FX_BlurUp";
	case eEffect_FX_MotionBlur:
		return "eEffect_FX_MotionBlur";
	case eEffect_FX_MergeColorDepth:
		return "eEffect_FX_MergeColorDepth";
	case eEffect_FX_PostColor:
		return "eEffect_FX_PostColor";
	case eEffect_DynamicLightMap:
		return "eEffect_DynamicLightMap";
	case eEffect_FX_RadialBlur:
		return "eEffect_FX_RadialBlur";
	case eEffect_FX_FXAA:
		return "eEffect_FX_FXAA";
	case eEffect_FX_SMAA_EdgeDetect:
		return "eEffect_FX_SMAA_EdgeDetect";
	case eEffect_FX_SMAA_BlendWeight:
		return "eEffect_FX_SMAA_BlendWeight";
	case eEffect_FX_SMAA_Final:
		return "eEffect_FX_SMAA_Final";
	case eEffect_FX_GBufferResolve:
		return "eEffect_FX_GBufferResolve";
	case eEffect_FX_GBufferDownSample:
		return "eEffect_FX_GBufferDownSample";
	case eEffect_FX_LinearDepthDownSample:
		return "eEffect_FX_LinearDepthDownSample";
	case eEffect_FX_DepthDownSample:
		return "eEffect_FX_DepthDownSample";
	case eEffect_FX_StencilMaskRestore:
		return "eEffect_FX_StencilMaskRestore";
	case eEffect_FX_OcclusionFilter:
		return "eEffect_FX_OcclusionFilter";
	case eEffect_FX_Null:
		return "eEffect_FX_Null";
	case eEffect_FX_Copy:
		return "eEffect_FX_Copy";
	case eEffect_FX_CopyDepth:
		return "eEffect_FX_CopyDepth";
	case eEffect_FX_CompositeAlpha:
		return "eEffect_FX_CompositeAlpha";
	case eEffect_FX_CompositeQuarter:
		return "eEffect_FX_CompositeQuarter";
	case eEffect_FX_CreateOutlineSrc:
		return "eEffect_FX_CreateOutlineSrc";
	case eEffect_FX_CreateOutline:
		return "eEffect_FX_CreateOutline";
	case eEffect_FX_BrushOutline:
		return "eEffect_FX_BrushOutline";
	case eEffect_FX_BrushOutline_Simple:
		return "eEffect_FX_BrushOutline_Simple";
	case eEffect_FX_BrushOffsetApply:
		return "eEffect_FX_BrushOffsetApply";
	case eEffect_FX_BrushOutlineBlurPrepare:
		return "eEffect_FX_BrushOutlineBlurPrepare";
	case eEffect_FX_BrushOutlineBlur:
		return "eEffect_FX_BrushOutlineBlur";
	case eEffect_FX_ApplyModulatedShadow:
		return "eEffect_FX_ApplyModulatedShadow";
	case eEffect_FX_FinalResolve:
		return "eEffect_FX_FinalResolve";
	case eEffect_FX_FinalDebugOverlay:
		return "eEffect_FX_FinalDebugOverlay";
	case eEffect_SceneText:
		return "eEffect_SceneText";
	case eEffect_SceneSimple_Texture_AlphaOnly:
		return "eEffect_SceneSimple_Texture_AlphaOnly";
	case eEffect_SceneHLSMovieYUV:
		return "eEffect_SceneHLSMovieYUV";
	case eEffect_SceneHLSMovieRGB:
		return "eEffect_SceneHLSMovieRGB";
	case eEffect_DirectionalLightShadow:
		return "eEffect_DirectionalLightShadow";
	case eEffect_DirectionalLightShadow_High:
		return "eEffect_DirectionalLightShadow_High";
	case eEffect_ProjectedTextureShadow:
		return "eEffect_ProjectedTextureShadow";
	case eEffect_ProjectedTextureColor:
		return "eEffect_ProjectedTextureColor";
	case eEffect_EnvLightShadowMark_Point:
		return "eEffect_EnvLightShadowMark_Point";
	case eEffect_EnvLightShadowMark_Spot:
		return "eEffect_EnvLightShadowMark_Spot";
	case eEffect_EnvLightShadowApply_Point:
		return "eEffect_EnvLightShadowApply_Point";
	case eEffect_EnvLightShadowApply_Spot:
		return "eEffect_EnvLightShadowApply_Spot";
	case eEffect_EnvLightShadowApply_Directional:
		return "eEffect_EnvLightShadowApply_Directional";
	case eEffect_EnvLightShadowApply_DirectionalFade:
		return "eEffect_EnvLightShadowApply_DirectionalFade";
	case eEffect_EnvLightShadowApply_DirectionalBlend:
		return "eEffect_EnvLightShadowApply_DirectionalBlend";
	case eEffect_EnvLightShadowApply_SDSM_Directional:
		return "eEffect_EnvLightShadowApply_SDSM_Directional";
	case eEffect_EnvLightShadowApply_SDSM_DirectionalFade:
		return "eEffect_EnvLightShadowApply_SDSM_DirectionalFade";
	case eEffect_ShadowMark_SDSM:
		return "eEffect_ShadowMark_SDSM";
	case eEffect_ShadowVolumeApply:
		return "eEffect_ShadowVolumeApply";
	case eEffect_ShadowTrace:
		return "eEffect_ShadowTrace";
	case eEffect_ShadowTrace_HBAOLow:
		return "eEffect_ShadowTrace_HBAOLow";
	case eEffect_ShadowTrace_HBAOMid:
		return "eEffect_ShadowTrace_HBAOMid";
	case eEffect_ShadowTrace_HBAOHigh:
		return "eEffect_ShadowTrace_HBAOHigh";
	case eEffect_ShadowTrace_MSAA:
		return "eEffect_ShadowTrace_MSAA";
	case eEffect_ShadowTrace_HBAOLow_MSAA:
		return "eEffect_ShadowTrace_HBAOLow_MSAA";
	case eEffect_ShadowTrace_HBAOMid_MSAA:
		return "eEffect_ShadowTrace_HBAOMid_MSAA";
	case eEffect_ShadowTrace_HBAOHigh_MSAA:
		return "eEffect_ShadowTrace_HBAOHigh_MSAA";
	case eEffect_FX_DeferredFilter_Light:
		return "eEffect_FX_DeferredFilter_Light";
	case eEffect_FX_DeferredFilter_Shadow:
		return "eEffect_FX_DeferredFilter_Shadow";
	case eEffect_FX_DeferredFilter_LightShadow:
		return "eEffect_FX_DeferredFilter_LightShadow";
	case eEffect_FX_CreateOutlineSrcQuarter:
		return "eEffect_FX_CreateOutlineSrcQuarter";
	case eEffect_FX_NewGlowH1x:
		return "eEffect_FX_NewGlowH1x";
	case eEffect_FX_NewGlowV1x:
		return "eEffect_FX_NewGlowV1x";
	case eEffect_FX_NewGlowPresent:
		return "eEffect_FX_NewGlowPresent";



	case eEffect_FX_NewDepthOfFieldPreparE:
		return "eEffect_FX_NewDepthOfFieldPreparE";



	case eEffect_FX_DepthOfFieldBlurH1x:
		return "eEffect_FX_DepthOfFieldBlurH1x";
	case eEffect_FX_DepthOfFieldBlurV1x:
		return "eEffect_FX_DepthOfFieldBlurV1x";
	case eEffect_FX_DepthOfFieldBlurH:
		return "eEffect_FX_DepthOfFieldBlurH";
	case eEffect_FX_DepthOfFieldBlurV:
		return "eEffect_FX_DepthOfFieldBlurV";
	case eEffect_FX_DepthOfFieldBlurHNear:
		return "eEffect_FX_DepthOfFieldBlurHNear";
	case eEffect_FX_DepthOfFieldBlurHFar:
		return "eEffect_FX_DepthOfFieldBlurHFar";
	case eEffect_FX_DepthOfFieldBlurVNear:
		return "eEffect_FX_DepthOfFieldBlurVNear";
	case eEffect_FX_DepthOfFieldBlurVFar:
		return "eEffect_FX_DepthOfFieldBlurVFar";
	case eEffect_FX_ShadowFilter_Pass0:
		return "eEffect_FX_ShadowFilter_Pass0";
	case eEffect_FX_ShadowFilter_Pass0_TAA:
		return "eEffect_FX_ShadowFilter_Pass0_TAA";
	case eEffect_FX_ShadowFilter_Blur0:
		return "eEffect_FX_ShadowFilter_Blur0";
	case eEffect_FX_ShadowFilter_Blur1:
		return "eEffect_FX_ShadowFilter_Blur1";
	case eEffect_FX_HBAOLowestQuality:
		return "eEffect_FX_HBAOLowestQuality";
	case eEffect_FX_HBAOLowQuality:
		return "eEffect_FX_HBAOLowQuality";
	case eEffect_FX_HBAOMediumQuality:
		return "eEffect_FX_HBAOMediumQuality";
	case eEffect_FX_HBAOHighQuality:
		return "eEffect_FX_HBAOHighQuality";
	case eEffect_FX_HBAOHighestQuality:
		return "eEffect_FX_HBAOHighestQuality";
	case eEffect_FX_HBAODeinterleaveDepth:
		return "eEffect_FX_HBAODeinterleaveDepth";
	case eEffect_FX_HBAODeinterleaveNormals:
		return "eEffect_FX_HBAODeinterleaveNormals";
	case eEffect_FX_HBAOReinterleave:
		return "eEffect_FX_HBAOReinterleave";
	case eEffect_FX_SSLines:
		return "eEffect_FX_SSLines";
	case eEffect_FX_SSLinesResolve_1x_Pass0:
		return "eEffect_FX_SSLinesResolve_1x_Pass0";
	case eEffect_FX_SSLinesResolve_1x_Pass1:
		return "eEffect_FX_SSLinesResolve_1x_Pass1";
	case eEffect_FX_SSLinesResolve_2x_Pass0:
		return "eEffect_FX_SSLinesResolve_2x_Pass0";
	case eEffect_FX_SSLinesResolve_2x_Pass1:
		return "eEffect_FX_SSLinesResolve_2x_Pass1";
	case eEffect_FX_SSLinesResolve_3x_Pass0:
		return "eEffect_FX_SSLinesResolve_3x_Pass0";
	case eEffect_FX_SSLinesResolve_3x_Pass1:
		return "eEffect_FX_SSLinesResolve_3x_Pass1";
	case eEffect_FX_SSLinesResolve_4x_Pass0:
		return "eEffect_FX_SSLinesResolve_4x_Pass0";
	case eEffect_FX_SSLinesResolve_4x_Pass1:
		return "eEffect_FX_SSLinesResolve_4x_Pass1";
	case eEffect_FX_MSAAResolve_2x:
		return "eEffect_FX_MSAAResolve_2x";
	case eEffect_FX_MSAAResolve_4x:
		return "eEffect_FX_MSAAResolve_4x";
	case eEffect_FX_MSAAResolve_8x:
		return "eEffect_FX_MSAAResolve_8x";
	case eEffect_FX_MSAASceneResolve_2x:
		return "eEffect_FX_MSAASceneResolve_2x";
	case eEffect_FX_MSAASceneResolve_4x:
		return "eEffect_FX_MSAASceneResolve_4x";
	case eEffect_FX_MSAASceneResolve_8x:
		return "eEffect_FX_MSAASceneResolve_8x";
	case eEffect_FX_SceneResolve_TAA:
		return "eEffect_FX_SceneResolve_TAA";
	case eEffect_FX_MSAASceneResolve_TAA_2x:
		return "eEffect_FX_MSAASceneResolve_TAA_2x";
	case eEffect_FX_MSAASceneResolve_TAA_4x:
		return "eEffect_FX_MSAASceneResolve_TAA_4x";
	case eEffect_FX_MSAASceneResolve_TAA_8x:
		return "eEffect_FX_MSAASceneResolve_TAA_8x";
	case eEffect_FX_MSAAGBufferResolve_2x:
		return "eEffect_FX_MSAAGBufferResolve_2x";
	case eEffect_FX_MSAAGBufferResolve_4x:
		return "eEffect_FX_MSAAGBufferResolve_4x";
	case eEffect_FX_MSAAGBufferResolve_8x:
		return "eEffect_FX_MSAAGBufferResolve_8x";
	case eEffect_MakeMipLevel:
		return "eEffect_MakeMipLevel";
	case eEffect_MakeMipLevel_BlurH:
		return "eEffect_MakeMipLevel_BlurH";
	case eEffect_MakeMipLevel_BlurV:
		return "eEffect_MakeMipLevel_BlurV";
	case eEffect_MakeMipLevel_Array:
		return "eEffect_MakeMipLevel_Array";
	case eEffect_CS_ComputeTest:
		return "eEffect_CS_ComputeTest";
	case eEffect_CS_ApplySkinning_0Normal:
		return "eEffect_CS_ApplySkinning_0Normal";
	case eEffect_CS_ApplySkinning_1Normal:
		return "eEffect_CS_ApplySkinning_1Normal";
	case eEffect_CS_ApplySkinning_2Normal:
		return "eEffect_CS_ApplySkinning_2Normal";
	case eEffect_CS_ApplySkinning_3Normal:
		return "eEffect_CS_ApplySkinning_3Normal";
	case eEffect_CS_ApplySkinning_Float3Position_0Normal:
		return "eEffect_CS_ApplySkinning_Float3Position_0Normal";
	case eEffect_CS_ApplySkinning_Float3Position_1Normal:
		return "eEffect_CS_ApplySkinning_Float3Position_1Normal";
	case eEffect_CS_ApplySkinning_Float3Position_2Normal:
		return "eEffect_CS_ApplySkinning_Float3Position_2Normal";
	case eEffect_CS_ApplySkinning_Float3Position_3Normal:
		return "eEffect_CS_ApplySkinning_Float3Position_3Normal";
	case eEffect_CS_LineGeneration:
		return "eEffect_CS_LineGeneration";
	case eEffect_CS_ClearIndirectDraw:
		return "eEffect_CS_ClearIndirectDraw";
	case eEffect_CS_LightClustering2D:
		return "eEffect_CS_LightClustering2D";
	case eEffect_CS_LightClustering3D:
		return "eEffect_CS_LightClustering3D";
	case eEffect_CS_ShadowCascadeDistances_Manual:
		return "eEffect_CS_ShadowCascadeDistances_Manual";
	case eEffect_CS_ShadowCascadeDistances_Auto:
		return "eEffect_CS_ShadowCascadeDistances_Auto";
	case eEffect_CS_ShadowCascadeBounds_Pass0:
		return "eEffect_CS_ShadowCascadeBounds_Pass0";
	case eEffect_CS_ShadowCascadeBounds_PassN:
		return "eEffect_CS_ShadowCascadeBounds_PassN";
	case eEffect_CS_ShadowCascades:
		return "eEffect_CS_ShadowCascades";
	case eEffect_CS_ShadowCascades_ComputedBounds:
		return "eEffect_CS_ShadowCascades_ComputedBounds";
	case eEffect_CS_CullShadowCasters:
		return "eEffect_CS_CullShadowCasters";
	case eEffect_CS_EnvLightMakeEVSM_Linear_Blur0:
		return "eEffect_CS_EnvLightMakeEVSM_Linear_Blur0";
	case eEffect_CS_EnvLightMakeEVSM_Linear_Blur3x3:
		return "eEffect_CS_EnvLightMakeEVSM_Linear_Blur3x3";
	case eEffect_CS_EnvLightMakeEVSM_Linear_Blur9x9:
		return "eEffect_CS_EnvLightMakeEVSM_Linear_Blur9x9";
	case eEffect_CS_EnvLightMakeEVSM_NonLinear_Blur0:
		return "eEffect_CS_EnvLightMakeEVSM_NonLinear_Blur0";
	case eEffect_CS_EnvLightMakeEVSM_NonLinear_Blur3x3:
		return "eEffect_CS_EnvLightMakeEVSM_NonLinear_Blur3x3";
	case eEffect_CS_EnvLightMakeEVSM_NonLinear_Blur9x9:
		return "eEffect_CS_EnvLightMakeEVSM_NonLinear_Blur9x9";
	case eEffect_CS_DepthReduction_Pass0_8x8:
		return "eEffect_CS_DepthReduction_Pass0_8x8";
	case eEffect_CS_DepthReduction_Pass0_16x16:
		return "eEffect_CS_DepthReduction_Pass0_16x16";
	case eEffect_CS_DepthReduction_PassN:
		return "eEffect_CS_DepthReduction_PassN";
	case eEffect_CS_DepthReduction_PassFinal:
		return "eEffect_CS_DepthReduction_PassFinal";
	case eEffect_CS_BokE:
		return "eEffect_CS_BokE";
	case eEffect_FX_RasterizeBokeh:
		return "eEffect_FX_RasterizeBokeh";
	case eEffect_CS_EnlightenMakeDusters_Point:
		return "eEffect_CS_EnlightenMakeDusters_Point";
	case eEffect_CS_EnlightenMakeDusters_Spot:
		return "eEffect_CS_EnlightenMakeDusters_Spot";
	case eEffect_CS_EnlightenMakeDusters_Directional:
		return "eEffect_CS_EnlightenMakeDusters_Directional";
	case eEffect_CS_WaveformMonitor:
		return "eEffect_CS_WaveformMonitor";
	case eEffect_CS_EnvLightApplyDeferred:
		return "eEffect_CS_EnvLightApplyDeferred";
	case eEffect_CS_EnvLightApplyDeferred_LowRes:
		return "eEffect_CS_EnvLightApplyDeferred_LowRes";
	case eEffect_BakeObjectNormals_Tool:
		return "eEffect_BakeObjectNormals_Tool";
	case eEffect_BakeObjectNormals_NormalMap_Tool:
		return "eEffect_BakeObjectNormals_NormalMap_Tool";
	case eEffect_BakeTangentNormals_Tool:
		return "eEffect_BakeTangentNormals_Tool";
	case eEffect_BakeLighting_Tool:
		return "eEffect_BakeLighting_Tool";
	case eEffect_CS_LightmapBlurH_Tool:
		return "eEffect_CS_LightmapBlurH_Tool";
	case eEffect_CS_LightmapBlurV_Tool:
		return "eEffect_CS_LightmapBlurV_Tool";
	case eEffect_CS_LightmapFilter_Tool:
		return "eEffect_CS_LightmapFilter_Tool";
	case eEffect_CS_LightmapConvert_Tool:
		return "eEffect_CS_LightmapConvert_Tool";
	case eEffect_CS_BakeShadowVolume_Tool:
		return "eEffect_CS_BakeShadowVolume_Tool";
	case eEffect_CS_ComputeAsyncTest:
		return "eEffect_CS_ComputeAsyncTest";
	case eEffect_Count:
		return "eEffect_Count";
	case eEffect_None:
		return "eEffect_None";
	default:
		return "NULL";
	}
}

#endif