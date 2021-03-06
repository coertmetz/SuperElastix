/*=========================================================================
*
*  Copyright Leiden University Medical Center, Erasmus University Medical
*  Center and contributors
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/

#include "selxTypeList.h"

//Component group Niftyreg
#include "selxItkToNiftiImageSourceComponent.h"
#include "selxNiftiToItkImageSinkComponent.h"
#include "selxNiftyregf3dComponent.h"
#include "selxNiftyregSplineToDisplacementFieldComponent.h"
#include "selxDisplacementFieldNiftiToItkImageSinkComponent.h"
#include "selxNiftyregAladinComponent.h"


namespace selx
{
using ModuleNiftyregComponents = selx::TypeList<
  ItkToNiftiImageSourceComponent< 2, float >,
  NiftiToItkImageSinkComponent< 2, float >,
  NiftyregSplineToDisplacementFieldComponent< float>,
  DisplacementFieldNiftiToItkImageSinkComponent< 2, float>,
  NiftyregAladinComponent< float >
  >;
}
