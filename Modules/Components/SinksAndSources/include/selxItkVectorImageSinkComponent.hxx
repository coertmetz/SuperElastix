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

#include "selxItkVectorImageSinkComponent.h"
#include "selxCheckTemplateProperties.h"

namespace selx
{
template< int Dimensionality, class TPixel >
ItkVectorImageSinkComponent< Dimensionality, TPixel >
::ItkVectorImageSinkComponent(const std::string & name, LoggerImpl & logger ) : Superclass( name, logger ),
                                                                                m_MiniPipelineOutputVectorImage( nullptr ),
                                                                                m_NetworkBuilderOutputVectorImage( nullptr )
{
}


template< int Dimensionality, class TPixel >
ItkVectorImageSinkComponent< Dimensionality, TPixel >
::~ItkVectorImageSinkComponent()
{
}


template< int Dimensionality, class TPixel >
int
ItkVectorImageSinkComponent< Dimensionality, TPixel >::Accept( ItkVectorImagePointer other )
{
  //if( this->m_NetworkBuilderOutputImage == nullptr )
  //{
  //  throw std::runtime_error( "SinkComponent needs to be initialized by SetMiniPipelineOutput()" );
  //}

  // Store pointer to MiniPipelineOutputImage for later grafting onto NetworkBuilder output.
  this->m_MiniPipelineOutputVectorImage = other->GetItkDisplacementField();
  //this->m_MiniPipelineOutputImage->Graft(other->GetItkImage());
  // Graft NetworkBuilder output onto MiniPipelineOutputImage.
  //this->m_MiniPipelineOutputImage->Graft(this->m_NetworkBuilderOutputImage);
  return 0;
}


template< int Dimensionality, class TPixel >
void
ItkVectorImageSinkComponent< Dimensionality, TPixel >::SetMiniPipelineOutput( itk::DataObject::Pointer NetworkBuilderOutput )
{
  /** Tries to cast the NetworkBuilderOutput to an image (data object) and stores the result.
   *  The resulting output image will be grafted into when the sink component is connected to an other component.
   * */
  //
  this->m_NetworkBuilderOutputVectorImage = dynamic_cast< ItkVectorImageType * >( NetworkBuilderOutput.GetPointer() );
  if( this->m_NetworkBuilderOutputVectorImage == nullptr )
  {
    throw std::runtime_error( "SinkComponent cannot cast the NetworkBuilder's Output to the required type" );
  }
}


template< int Dimensionality, class TPixel >
typename itk::DataObject::Pointer
ItkVectorImageSinkComponent< Dimensionality, TPixel >::GetMiniPipelineOutput()
{
  return this->m_MiniPipelineOutputVectorImage.GetPointer();
}


template< int Dimensionality, class TPixel >
typename AnyFileWriter::Pointer
ItkVectorImageSinkComponent< Dimensionality, TPixel >::GetOutputFileWriter()
{
  // Instanstiate an image file writer, decorated such that it can be implicitly cast to an AnyFileWriterType
  return DecoratedWriterType::New().GetPointer();
}


template< int Dimensionality, class TPixel >
typename itk::DataObject::Pointer
ItkVectorImageSinkComponent< Dimensionality, TPixel >::GetInitializedOutput()
{
  return ItkVectorImageType::New().GetPointer();
}


template< int Dimensionality, class TPixel >
bool
ItkVectorImageSinkComponent< Dimensionality, TPixel >::MeetsCriterion( const ComponentBase::CriterionType & criterion )
{
  bool hasUndefinedCriteria( false );
  bool meetsCriteria( false );
  auto status = CheckTemplateProperties( this->TemplateProperties(), criterion );
  if( status == CriterionStatus::Satisfied )
  {
    return true;
  }
  else if( status == CriterionStatus::Failed )
  {
    return false;
  } // else: CriterionStatus::Unknown

  return meetsCriteria;
}
} //end namespace selx
