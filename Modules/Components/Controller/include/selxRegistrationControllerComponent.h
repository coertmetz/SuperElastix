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

#ifndef selxRegistrationControllerComponent_h
#define selxRegistrationControllerComponent_h

#include "selxSuperElastixComponent.h"
//#include "selxInterfaces.h"

#include <string.h>
#include <set>

namespace selx
{
template< bool dummy = true >
class RegistrationControllerComponent :
  public SuperElastixComponent<
  Accepting< RunRegistrationInterface, ReconnectTransformInterface, AfterRegistrationInterface >,
  Providing< RegistrationControllerStartInterface >
  >
{
  // RegistrationControllerComponent is a work-around for broken itk-pipelines.
  // Both the elastix and itkv4 require to connect their transforms *after* execution of the registration.
  // This controller explicitly performs these steps
  // TODO: see if signals-and-slots paradigm is appropriate here.

public:

  /** Standard ITK typedefs. */
  typedef RegistrationControllerComponent Self;
  typedef SuperElastixComponent<
    Accepting< RunRegistrationInterface, ReconnectTransformInterface, AfterRegistrationInterface >,
    Providing< RegistrationControllerStartInterface >
    >                   Superclass;
  typedef std::shared_ptr< Self >       Pointer;
  typedef std::shared_ptr< const Self > ConstPointer;

  RegistrationControllerComponent(const std::string &name, LoggerImpl &logger);
  virtual ~RegistrationControllerComponent();

  // Accepting Interfaces:
  virtual int Accept( RunRegistrationInterface::Pointer ) override;

  virtual int Accept( ReconnectTransformInterface::Pointer ) override;

  virtual int Accept( AfterRegistrationInterface::Pointer ) override;

  // Providing Interfaces:
  virtual void RegistrationControllerStart( void ) override;

  virtual bool MeetsCriterion( const ComponentBase::CriterionType & criterion ) override;

  // override default by not checking accepting connections and always return true.
  // TODO: the controller is a bit odd since it accepts connections, but the providing components require the connections. See if we can reverse the direction of the connection.
  virtual bool ConnectionsSatisfied() override { return true; }

  static const char * GetDescription() { return "RegistrationController Component"; }

private:

  std::set< RunRegistrationInterface::Pointer >    m_RunRegistrationInterfaces;
  std::set< ReconnectTransformInterface::Pointer > m_ReconnectTransformInterfaces;
  std::set< AfterRegistrationInterface::Pointer >  m_AfterRegistrationInterfaces;

protected:

  // return the class name and the template arguments to uniquely identify this component.
  static inline const std::map< std::string, std::string > TemplateProperties()
  {
    return { { keys::NameOfClass, "RegistrationControllerComponent" } };
  }
};
} //end namespace selx
#ifndef ITK_MANUAL_INSTANTIATION
#include "selxRegistrationControllerComponent.hxx"
#endif
#endif // #define selxRegistrationControllerComponent_h
