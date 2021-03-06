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

#include "itkQuadEdgeMesh.h"
#include "itkMeshFileReader.h"
#include "itkMeshFileWriter.h"


#include "itkCleanQuadEdgeMeshFilter.h"

int main( int argc, char* argv[] )
{
  if( argc < 3 )
    {
    std::cout <<"Requires 3 argument: " <<std::endl;
    std::cout <<"1-Input file name " <<std::endl;
    std::cout <<"2-Relative Tolerance " <<std::endl;
    std::cout <<"3-Output file name " <<std::endl;
    return EXIT_FAILURE;
    }

  typedef double        Coord;
  const unsigned int    Dimension = 3;

  typedef itk::QuadEdgeMesh< Coord, Dimension >  MeshType;
  typedef itk::MeshFileReader< MeshType >        ReaderType;
  typedef itk::MeshFileWriter< MeshType >        WriterType;

  ReaderType::Pointer reader = ReaderType::New( );
  reader->SetFileName( argv[1] );

  MeshType::Pointer mesh = reader->GetOutput( );

  Coord tol;
  std::stringstream ssout( argv[2] );
  ssout >>tol;

  typedef itk::CleanQuadEdgeMeshFilter< MeshType, MeshType > CleanFilterType;
  CleanFilterType::Pointer filter = CleanFilterType::New();
  filter->SetInput( mesh );
  filter->SetRelativeTolerance( tol );

  WriterType::Pointer writer = WriterType::New( );
  writer->SetInput( filter->GetOutput( ) );
  writer->SetFileName( argv[3] );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << filter;
  return EXIT_SUCCESS;
}
