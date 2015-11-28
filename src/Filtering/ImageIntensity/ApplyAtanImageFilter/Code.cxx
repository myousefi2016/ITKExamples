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

#include "itkImage.h"
#include "itkRandomImageSource.h"
#include "itkImageFileWriter.h"
#include "itkAtanImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;
  typedef unsigned char InputPixelType;

  typedef itk::Image< InputPixelType, Dimension >  InputImageType;

  InputImageType::SizeType size;
  size.Fill( 100 );

  typedef itk::RandomImageSource< InputImageType > RandomImageSourceType;

  RandomImageSourceType::Pointer randomImageSource =
    RandomImageSourceType::New();
  randomImageSource->SetNumberOfThreads(1); // to produce non-random results
  randomImageSource->SetSize(size);

  typedef float OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

  typedef itk::AtanImageFilter< InputImageType, OutputImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( randomImageSource->GetOutput() );

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[1] );
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
