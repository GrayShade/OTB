/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkWatershedRelabeler.h,v $
  Language:  C++
  Date:      $Date: 2009-04-23 03:53:38 $
  Version:   $Revision: 1.12 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __otbWatershedRelabeler_h
#define __otbWatershedRelabeler_h

#include "itkEquivalencyTable.h"
#include "itkWatershedSegmentTree.h"
#include "otbWatershedSegmenter.h"
#include "itkImage.h"

namespace otb
{
namespace watershed
{

/** \class Relabeler
 *
 * This filter implements the final step in the watershed segmentation
 * algorithm.  It is responsible for relabeling a segmented image according to
 * a specified saliency level (flood level) in a merge tree.  (See
 * itk::WatershedImageFilter for information on terminology used in this
 * documentation.)
 *
 * \par Inputs
 * There are two inputs to this filter.  The first input is a labeled image of 
 * unsigned long integers, such as is produced by itk::watershed::Segmenter.
 * The second input is an itk::watershed::SegmentTree, which is the merge tree 
 * data structure produced by the itk::watershed::SegmentTreeGenerator
 * filter.  The merge tree represents the hierarchy of merges among adjacent
 * segments in the initial segmentation image.
 *
 * \par Output
 * The output of this filter is a relabeled image of unsigned long integers of 
 * dimension and size matching the input.
 *
 * \par Parameters
 * There is a single parameter FloodLevel for this filter.  FloodLevel is
 * given in percentage points (0.0 - 1.0) of the maximum saliency found in the 
 * merge tree.  A FloodLevel of 0.0 will produce an output in which no
 * segments are relabeled (merged).  A FloodLevel of 1.0 will produce an
 * output in which all the entries in the merge tree are used to relabel the
 * image.  FloodLevel controls which level in the segmentation hierarchy to
 * produce on the output.
 *
 * \ingroup WatershedSegmentation
 * \sa itk::WatershedImageFilter
 * \sa itk::EquivalencyTable
 * \sa itk::watershed::SegmentTree  */
template <class TScalarType, unsigned int TImageDimension>
class ITK_EXPORT Relabeler
  : public itk::ProcessObject
{
public:
  /** Define smart pointers for this object */
  typedef Relabeler                     Self;
  typedef itk::ProcessObject            Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  itkNewMacro(Self);
  itkTypeMacro(WatershedRelabeler, ProcessObject);

  /** Expose the ImageDimension template parameter at run time */
  itkStaticConstMacro(ImageDimension, unsigned int,TImageDimension);
  
  /** Some convenient typedefs */
  typedef TScalarType                                    ScalarType;
  typedef itk::Image<unsigned long, TImageDimension>     ImageType;
  typedef itk::watershed::SegmentTree<ScalarType>        SegmentTreeType;
  typedef Segmenter<itk::Image<ScalarType, TImageDimension> > SegmenterType;
  typedef itk::DataObject::Pointer                       DataObjectPointer;

  /** Standard itk::ProcessObject subclass method. */
  virtual DataObjectPointer MakeOutput(unsigned int idx);
  
  /** Set/Get the input image */
  void SetInputImage(ImageType *img)
    {
      this->itk::ProcessObject::SetNthInput(0, img);
    }
  ImageType * GetInputImage(void)
    {
    return static_cast<ImageType *>
      (this->itk::ProcessObject::GetInput(0) );
    }

  /** Set/Get the output image */
  void SetOutputImage(ImageType * img)
    {
      this->itk::ProcessObject::SetNthOutput(0,img);
    }
  ImageType * GetOutputImage(void)
    {
    return static_cast<ImageType *>
      (this->itk::ProcessObject::GetOutput(0) );
    }

  /** Set/Get the input tree that defines segment merges */
  void SetInputSegmentTree(SegmentTreeType *et)
    {
      this->itk::ProcessObject::SetNthInput(1, et);
    }
  SegmentTreeType * GetInputSegmentTree(void)
    {
    return static_cast<SegmentTreeType *>
      (this->itk::ProcessObject::GetInput(1));
    }

  /** Standard non-threaded pipeline method */
  void GenerateData();

  /** Set/Get the percentage of the maximum saliency level
   * to merge to. */
  itkSetClampMacro(FloodLevel, double, 0.0, 1.0);
  itkGetConstMacro(FloodLevel, double);

  /** Standard ProcessObject method used in implementing mini-pipelines */
  void GraftOutput(ImageType *graft);
  void GraftNthOutput(unsigned int idx, ImageType *graft);
  
protected:
  Relabeler();
  virtual ~Relabeler() {}
  Relabeler(const Self&) {}
  void operator=(const Self&) {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const;
  
  double m_FloodLevel;
  void GenerateOutputRequestedRegion(itk::DataObject *output);
  void GenerateInputRequestedRegion();
};
  
}// end namespace watershed
}// end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbWatershedRelabeler.txx"
#endif

#endif