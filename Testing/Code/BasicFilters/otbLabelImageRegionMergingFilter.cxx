/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "itkMacro.h"
#include "otbImage.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbMeanShiftImageFilter2.h"
#include "otbLabelImageRegionMergingFilter.h"

int otbLabelImageRegionMergingFilter(int argc, char * argv[])
{
  if (argc != 9)
    {
    std::cerr << "Usage: " << argv[0] <<
    " infname spectralfname labelfname labelmergedfname spatialBandwidth rangeBandwidth threshold maxiterationnumber"
              << std::endl;
    return EXIT_FAILURE;
    }

  const char *       infname                   = argv[1];
  const char *       spectralfname             = argv[2];
  const char *       labelfname                = argv[3];
  const char *       labelmergedfname          = argv[4];
  const double       spatialBandwidth          = atof(argv[5]);
  const double       rangeBandwidth            = atof(argv[6]);
  const double       threshold                 = atof(argv[7]);
  const unsigned int maxiterationnumber        = atoi(argv[8]);
  /* maxit - threshold */

  const unsigned int Dimension = 2;
  typedef float                                            PixelType;
  typedef double                                           KernelType;
  typedef otb::VectorImage<PixelType, Dimension>           ImageType;
  typedef otb::ImageFileReader<ImageType>                  ReaderType;
  typedef otb::ImageFileWriter<ImageType>                  WriterType;
  typedef otb::MeanShiftImageFilter2<ImageType, ImageType> FilterType;
  typedef FilterType::OutputLabelImageType                 LabelImageType;
  typedef otb::ImageFileWriter<LabelImageType>             LabelWriterType;

  typedef otb::LabelImageRegionMergingFilter<LabelImageType, ImageType> MergeFilterType;

  // Instantiating object
  FilterType::Pointer filter = FilterType::New();
  ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName(infname);

  // Set filter parameters
  filter->SetSpatialBandwidth(spatialBandwidth);
  filter->SetRangeBandwidth(rangeBandwidth);
  filter->SetThreshold(threshold);
  filter->SetMaxIterationNumber(maxiterationnumber);
  filter->SetInput(reader->GetOutput());
  //filter->SetNumberOfThreads(1);
  WriterType::Pointer writer2 = WriterType::New();
  LabelWriterType::Pointer writer5 = LabelWriterType::New();

  writer2->SetFileName(spectralfname);
  writer5->SetFileName(labelfname);

  writer2->SetInput(filter->GetRangeOutput());
  writer5->SetInput(filter->GetLabelOutput());

  MergeFilterType::Pointer mergeFilter = MergeFilterType::New();
  mergeFilter->SetInputLabelImage(filter->GetLabelOutput());
  mergeFilter->SetInputSpectralImage(filter->GetRangeOutput());
  mergeFilter->SetRangeBandwidth(rangeBandwidth);
  LabelWriterType::Pointer mergeWriter = LabelWriterType::New();
  mergeWriter->SetFileName(labelmergedfname);
  mergeWriter->SetInput(mergeFilter->GetOutput());


  writer2->Update();
  writer5->Update();
  mergeWriter->Update();

  return EXIT_SUCCESS;
}