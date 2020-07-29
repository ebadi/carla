// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "Carla.h"
#include "Carla/Sensor/SemanticSegmentationCamera.h"

#include "Carla/Sensor/PixelReader.h"

FActorDefinition ASemanticSegmentationCamera::GetSensorDefinition()
{
  return UActorBlueprintFunctionLibrary::MakeCameraDefinition(TEXT("semantic_segmentation"));
}

ASemanticSegmentationCamera::ASemanticSegmentationCamera(
    const FObjectInitializer &ObjectInitializer)
  : Super(ObjectInitializer)
{
  AddPostProcessingMaterial(
      TEXT("Material'/Carla/PostProcessingMaterials/PhysicLensDistortion.PhysicLensDistortion'"));
  AddPostProcessingMaterial(
      TEXT("Material'/Carla/PostProcessingMaterials/GTMaterial.GTMaterial'"));

  Offset = carla::sensor::SensorRegistry::get<ASemanticSegmentationCamera*>::type::header_offset;
}

void ASemanticSegmentationCamera::SendPixels()
{
#if !UE_BUILD_SHIPPING
  ACarlaGameModeBase* GameMode = Cast<ACarlaGameModeBase>(GetWorld()->GetAuthGameMode());
  if(!GameMode->IsCameraStreamEnabled()) return;
#endif

  SendPixelsInStream(*this);
}
