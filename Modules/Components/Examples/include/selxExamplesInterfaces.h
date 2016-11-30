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

#ifndef selxExamplesInterfaces_h
#define selxExamplesInterfaces_h

namespace selx
{
// Define the providing interfaces abstractly
class MetricDerivativeInterface
{
public:

  virtual int GetDerivative() = 0;
};

class MetricValueInterface
{
public:

  virtual int GetValue() = 0;
};

class OptimizerUpdateInterface
{
public:

  virtual int Update() = 0;
};

class TransformedImageInterface
{
public:

  virtual int GetTransformedImage() = 0;
};

class ConflictinUpdateInterface
{
public:

  // "error" : member function templates cannot be virtual
  // template <class ConflictinUpdateInterface> virtual int Update() = 0;
  //TODO http://en.cppreference.com/w/cpp/language/member_template

  //TODO solution: http://stackoverflow.com/questions/2004820/inherit-interfaces-which-share-a-method-name
  //TODO better?: http://stackoverflow.com/questions/18398409/c-inherit-from-multiple-base-classes-with-the-same-virtual-function-name
  virtual int Update( ConflictinUpdateInterface * ) = 0;
};

} // end namespace selx

#endif // #define selxExamplesInterfaces_h
