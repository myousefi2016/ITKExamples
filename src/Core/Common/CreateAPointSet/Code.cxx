/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkPoint.h"
#include "itkPointSet.h"

int main(int, char* [])
{
  typedef float PixelType;
  const unsigned int Dimension = 3;

  typedef itk::PointSet< PixelType, Dimension >   PointSetType;
  PointSetType::Pointer  PointSet = PointSetType::New();

  typedef PointSetType::PointsContainerPointer PointsContainerPointer;
  PointsContainerPointer  points = PointSet->GetPoints();

  // Create points
  typedef PointSetType::PointType PointType;
  PointType p0, p1, p2;

  p0[0]=  0.0; p0[1]= 0.0; p0[2]= 0.0;
  p1[0]=  0.1; p1[1]= 0.0; p1[2]= 0.0;
  p2[0]=  0.0; p2[1]= 0.1; p2[2]= 0.0;

  points->InsertElement(0, p0);
  points->InsertElement(1, p1);
  points->InsertElement(2, p2);

  return EXIT_SUCCESS;
}
