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

#ifndef NetworkBuilderFactory_h
#define NetworkBuilderFactory_h

#include "selxNetworkBuilderFactoryBase.h"

namespace selx
{
template< class ComponentList >
class NetworkBuilderFactory : public NetworkBuilderFactoryBase
{
public:

  NetworkBuilderFactory() {}
  virtual ~NetworkBuilderFactory() {}

  virtual std::unique_ptr< NetworkBuilderBase > New( LoggerImpl & logger, const BlueprintImpl & blueprint );
};
} // end namespace selx

#ifndef ITK_MANUAL_INSTANTIATION
#include "selxNetworkBuilderFactory.hxx"
#endif

#endif // NetworkBuilderFactory_h
