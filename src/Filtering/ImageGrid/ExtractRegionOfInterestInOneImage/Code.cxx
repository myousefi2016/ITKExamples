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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRegionOfInterestImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 7 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " <start x> <end x> <start y> <end y>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const itk::IndexValueType startx =
    static_cast< itk::IndexValueType >( atoi( argv[3] ) );
  const itk::IndexValueType endx =
    static_cast< itk::IndexValueType >( atoi( argv[4] ) );

  const itk::IndexValueType starty =
    static_cast< itk::IndexValueType >( atoi( argv[5] ) );
  const itk::IndexValueType endy =
    static_cast< itk::IndexValueType >( atoi( argv[6] ) );

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  ImageType::IndexType start;
  start[0] = startx;
  start[1] = starty;

  ImageType::IndexType end;
  end[0] = endx;
  end[1] = endy;

  ImageType::RegionType region;
  region.SetIndex( start );
  region.SetUpperIndex( end );

  typedef itk::RegionOfInterestImageFilter< ImageType, ImageType >
    FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetRegionOfInterest( region );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( filter->GetOutput() );
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
